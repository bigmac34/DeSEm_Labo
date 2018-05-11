#ifndef SERIALCON_GW_CONTROLLER_H
#define SERIALCON_GW_CONTROLLER_H

#include <queue>
#include "platform-config.h"
#include "xf/xfreactive.h"
#include "desenet/multipdu.h"
#include "serialcon/serialcon.h"
#include "serialcon/msg.h"
#include "board/usb-vcom/vcom.h"

#if (DESENET_GATEWAY_NODE != 0)

namespace serialcon
{

/**
 * @brief Gateway nodes serialcon controller.
 *
 * This serialcon controller manages the communication to the host PC on the Gateway node.
 * It receives messages/commands from the PC and processes them accordingly. The
 * Controller also provides some transmit methods to send information to the PC.
 */
class Controller : public XFReactive,
				   public Vcom::Observer,
				   public Vcom::MessageEvaluateDelegate
{
public:
    /**
     * @brief Callback function to be defined by the observer of the Controller class to receive information from the host PC.
     *
     * It is important to be aware that the buffer given in this method belongs to the caller. This means that you should **never** keep a pointer to
     * the buffer outside the actual context of the called object. If you need to save the frame or a part of the frame for later use, make a copy.
     *
     * Take care to not add infinite loops in this method neither do eternal computations.
     *
     * @param controller    Reference to the driver that is actually calling the function object.
     * @param buffer    Pointer to the frame data buffer.
     * @param length    The actual size of the buffer in bytes.
     */
    typedef std::function<void (Controller & controller, CmdType cmd, uint32_t cmdData)> CmdReceptionHandler;

    /**
     * @brief Callback function to be defined by the observer of the Controller class to receive beacons from the host PC.
     */
    typedef std::function<void (Controller & controller,
    							const desenet::Address & destinationAddress,
    							uint32_t networkTime,
								desenet::CycleDuration cycleDuration,
								desenet::SlotDuration slotDuration,
								uint16_t svGroupMask)> BeaconReceptionHandler;

public:
	Controller();
	virtual ~Controller();

	void initialize();
	void registerCmdCallback(CmdReceptionHandler cmdhandler);
	void registerBeaconCallback(BeaconReceptionHandler beaconHandler);

	void start();

	static Controller & instance() { assert(_pInstance); return *_pInstance; }

	bool transmitMpdu(const desenet::MultiPdu & mpdu);					///< Sends MPDU over the serial connection to the host.
//	bool transmit(const uint8_t * const buffer, const size_t length);	///< Sends message over the serial connection.

	// Vcom::Observer implementation
protected:
	virtual uint32_t rxByteCountLevel(Vcom & driver);
	virtual void onRxData(Vcom & driver);

	// Vcom::MessageEvaluateDelegate implementation
protected:
	virtual bool isMessageComplete(Vcom & driver, uint32_t & messageSize);

	// XFReactive implementation
protected:
	virtual EventStatus processEvent();		///< Implements the state machine.

protected:	// State machine stuff
	/**
	 * Event identifier(s) for this state machine.
	 */
	typedef enum
	{
		EV_TX_MSG_id = 1,	///< New messages in TX queue to transmit.
		EV_RX_DATA_id = 2
	} eEventId;

	/**
	 * Enumeration used to have a unique identifier for every
	 * state in the state machine.
	 */
	typedef enum
	{
		STATE_UNKOWN = 0,			///< Unknown state
		STATE_INITIAL = 1,			///< Initial state
		STATE_ROOT = 2				///< State where to wait for further events
	} eMainState;

	eMainState _currentState;		///< Attribute indicating currently active state

protected:
	inline Vcom & driver() const { return Vcom::instance(); }
	void doProcessTxMsgQueue();		///< Called by the state machine. Initiates a message transmission.
	void doProcessRxedData();		///< Called by the state machine after reception of data over the serialcon driver.
	void _write(Msg & msg);			///< Passes a message to transmit to the underlaying driver.

protected:
	static Controller * _pInstance;							///< Pointer to single instance.
	std::queue<serialcon::Msg> _txQueue;					///< Queue holding messages to transmit.
	CmdReceptionHandler _cmdReceiveCallbackHandler;			///< Member function pointer to call when receiving a command from the host.
	BeaconReceptionHandler _beaconReceiveCallbackHandler;	///< Member function pointer to call when receiving a beacon from the host.
};

} // serialcon
#endif // DESENET_GATEWAY_NODE
#endif // SERIALCON_GW_CONTROLLER_H
