#include "platform-config.h"
#include "board/usb-vcom/vcom.h"
#include "trace/trace.h"
#include "xf/xfevent.h"
#include "desenet/multipdu.h"
#include "desenet/gateway/networkentity.h"
#include "controller.h"

#if (DESENET_GATEWAY_NODE != 0)

using serialcon::Controller;
using desenet::gateway::NetworkEntity;

Controller * Controller::_pInstance(nullptr);

Controller::Controller()
 : _currentState(STATE_UNKOWN)
{
	assert(!_pInstance);
	_pInstance = this;
}

Controller::~Controller()
{
}

void Controller::initialize()
{
	driver().initialize();

	driver().subscribe(*this);	// Want to receive data send via the virtual com port
}

void Controller::registerCmdCallback(CmdReceptionHandler cmdhandler)
{
	_cmdReceiveCallbackHandler = cmdhandler;
}

void Controller::registerBeaconCallback(BeaconReceptionHandler beaconHandler)
{
	_beaconReceiveCallbackHandler = beaconHandler;
}

void Controller::start()
{
	startBehavior();
}

/**
 * Queues a MultiPdu received over the wireless communication
 * and enqueues it into the queue to transmit it further to the host
 * over the serial connection.
 * Received MultiPdu is queued only if the host is connected to
 * the serial line.
 */
bool Controller::transmitMpdu(const desenet::MultiPdu & mpdu)
{
	//Trace::outln("Rxed Mpdu from Sensor");
	if (driver().isOpen())	// Queue only if com port is open
	{
		const bool notifyStateMachine = _txQueue.empty();
		const desenet::NetworkTime networkTime = NetworkEntity::instance().networkTime();

		//Trace::outln("NWT: %d (diff: %d)", networkTime, networkTime - NetworkEntity::instance().beaconNetworkTime());
		_txQueue.push(Msg(networkTime, mpdu));

		if (notifyStateMachine)
		{
			GEN(XFEvent(EV_TX_MSG_id));		// Tell state machine new message(s) to transmit
		}
		return true;
	}
	return false;
}
/*
bool Controller::transmit(const uint8_t * const buffer, const size_t length)
{
	const bool notifyStateMachine = _txQueue.empty();

	_txQueue.push(Msg(buffer, length));

	if (notifyStateMachine)
	{
		GEN(XFEvent(EV_TX_MSG_id));		// Tell state machine new message(s) to transmit
	}
	return true;
}
*/
uint32_t Controller::rxByteCountLevel(Vcom & driver)
{
	UNUSED(driver);
	return serialcon::HEADER_SIZE;
}

void Controller::onRxData(Vcom & driver)
{	// Called within ISR!

	static XFEvent evRxData(EV_RX_DATA_id);

	UNUSED(driver);

	evRxData.setShouldDelete(false);

	XFReactive::pushEvent(&evRxData);	// Calls doProcessRxedData() in the state machine
}

bool Controller::isMessageComplete(Vcom & driver, uint32_t & messageSize)
{
	const uint32_t bytesAvailable = driver.bytesAvailable();
	Vcom::MessageEvaluateDelegate::Buffer & rxBuffer = MessageEvaluateDelegate::getRxBuffer(driver);

	messageSize = 0;	// Reset message size

	if (bytesAvailable < (serialcon::HEADER_SIZE + serialcon::TRAILER_SIZE))
	{
		return false;	// Still not enough data for a complete message
	}

	// Be sure that the first byte is the SOF
	if (rxBuffer.size() > 0)
	{
		if (rxBuffer[0] != serialcon::SOF)
		{
			// Search SOF
			for (size_t i = 1; i < rxBuffer.size(); i++)
			{
				if (rxBuffer[i] == serialcon::SOF)
				{
#if (SERIALCON_CONTROLLER_VERBOSE != 0)
					Trace::outln("Con: Rem rubbish: %d", i);
#endif
					// Got it. Remove previous characters
					rxBuffer.popMultiple(NULL, i);
					break;
				}
			}

			// Check if we got any SOF in buffer. If not empty the whole buffer
			if (!rxBuffer.empty() &&			// Is something in the buffer?
				rxBuffer[0] != serialcon::SOF) 	// Is first byte an SOF?

			{	// We did not get any SOF in buffer!
#if (SERIALCON_CONTROLLER_VERBOSE != 0)
				Trace::outln("Con: No SOF in buffer found!");
				Trace::outln("Con: Purging RX buffer");
#endif
				rxBuffer.clear();
			}
		}
	}

	if (rxBuffer[0] == serialcon::SOF &&
		rxBuffer.size() >= 3)
	{	// Enough data to read length in message

		uint16_t payloadSize = 0;

		payloadSize = rxBuffer[2];

#if (SERIALCON_CONTROLLER_VERBOSE != 0)
		Trace::outln("Con: payloadSize: %d", payloadSize);
#endif
		if (rxBuffer.size() >= (size_t)(serialcon::HEADER_SIZE + payloadSize + serialcon::TRAILER_SIZE))
		{
			messageSize = serialcon::HEADER_SIZE + payloadSize + serialcon::TRAILER_SIZE;
			return true;
		}
		else
		{
#if (SERIALCON_CONTROLLER_VERBOSE != 0)
		Trace::outln("Con: Msg not completely arrived");
#endif
			// Check if Vcom RX buffer is full
			if (rxBuffer.count() == rxBuffer.maxBufferSize())
			{
				rxBuffer.clear();	// Emtpy buffer
			}
		}
	}
	return false;
}

EventStatus Controller::processEvent()
{
	eMainState newState = _currentState;

	switch (_currentState)
	{
	case STATE_UNKOWN:
	case STATE_INITIAL:
		if (getCurrentEvent()->getEventType() == IXFEvent::Initial)
		{
			newState = STATE_ROOT;	// Move to state ROOT
		}
		break;
	case STATE_ROOT:
		if (getCurrentEvent()->getEventType() == IXFEvent::Event &&
			getCurrentEvent()->getId() == EV_TX_MSG_id)
		{
			newState = STATE_ROOT;	// Stay in state

			doProcessTxMsgQueue();
		}
		if (getCurrentEvent()->getEventType() == IXFEvent::Event &&
			getCurrentEvent()->getId() == EV_RX_DATA_id)
		{
			newState = STATE_ROOT;	// Stay in state

			doProcessRxedData();
		}
		break;
	}

	_currentState = newState;		// Save new state to actual

	return EventStatus::Consumed;	// We consume all given events/timeouts
}

void Controller::doProcessTxMsgQueue()
{
	if (!_txQueue.empty())
	{
		Msg & msg = _txQueue.front();

		_write(msg);

		_txQueue.pop();
	}

	if (!_txQueue.empty())
	{
		// Still remaining message to transmit.
		GEN(XFEvent(EV_TX_MSG_id));
	}
}

void Controller::doProcessRxedData()
{
	uint32_t messageSize = 0;

	while (driver().isMessageComplete(*this, messageSize))
	{
		Msg msg(driver().read(messageSize).data(), messageSize);
		const uint8_t crc = msg.calculateCrc();

		// Check CRC
		if (msg.crc() == crc ||
			(msg.type() == MsgType::CMD && msg.cmd() == CmdType::NETWORK_TIME && msg.crc() == 0xFF))	// Close an eye if network time comes with a CRC of 0xFF
		{
			switch(msg.type())
			{
			case MsgType::CMD:	// Received a command from the host
				{
					Trace::outln("Con: Received a CMD");

					assert(_cmdReceiveCallbackHandler);
					// Give command to to next layer
					_cmdReceiveCallbackHandler(*this, msg.cmd(), msg.cmdData());
				}
				break;
			case MsgType::BEACON:
				{
					desenet::Address destinationAddress;
					uint32_t networkTime;
					desenet::CycleDuration cycleDuration;
					desenet::SlotDuration slotDuration;
					uint16_t svGroupMask;

#if (SERIALCON_CONTROLLER_VERBOSE != 0)
					Trace::outln("Con: Received a BEACON");
#endif

					msg.beaconFields(destinationAddress, networkTime, cycleDuration, slotDuration, svGroupMask);

					assert(_beaconReceiveCallbackHandler);
					// Give command to to next layer
					_beaconReceiveCallbackHandler(*this, destinationAddress, networkTime, cycleDuration, slotDuration, svGroupMask);
				}
				break;
			default:
				Trace::outln("Con: Received an unknown Msg");
				break;
			}
		}
		else
		{
			Trace::outln("Con: Discarding received message with wrong CRC(0x%02x). Should be 0x%02x!", msg.crc(), crc);
		}
	}
}

void Controller::_write(Msg & msg)
{
	if (!msg.isValid())
	{
		msg.setCrc(msg.calculateCrc());	// Set CRC field
	}

	assert(msg.isValid());

	if (driver().isOpen())	// Write only if com port is open
	{
		driver().write(msg.buffer(), msg.length());
	}
}

#endif // DESENET_GATEWAY_NODE
