#include "platform-config.h"
#include "desenet/multipdu.h"
#include "msg.h"

#if (DESENET_GATEWAY_NODE != 0) || defined(DESENET_TESTBENCH)

using serialcon::Msg;

Msg::Msg(const uint8_t * const buffer, size_t length)
: _headerPrepared(false),
  _buffer(length)
{
	// Copy data into internal buffer
	memcpy(_buffer.data(), buffer, length);

	if (_buffer[0] == serialcon::SOF &&		// SOF correctly set
		_buffer.length() == serialcon::HEADER_SIZE + (size_t)payloadSize() + serialcon::TRAILER_SIZE)	// Internal buffer has correct size
	{
		// Apart from the CRC (should not be check here) the message seems to be OK.
		_headerPrepared = true;
	}
}

Msg::Msg(const Msg & msg)
{
	_headerPrepared = msg._headerPrepared;
	_buffer = msg._buffer;
}

Msg::Msg(const desenet::NetworkTime & networkTime, const desenet::MultiPdu & mpdu)
 : _buffer(serialcon::HEADER_SIZE + sizeof(desenet::NetworkTime) + mpdu.length() + serialcon::TRAILER_SIZE)
{
	::hei::SharedByteBuffer::pointer pNextFreeBufferSpace = _buffer.data() + serialcon::HEADER_SIZE;

	prepareHeader(serialcon::MPDU, sizeof(desenet::NetworkTime) + mpdu.length());

	// Copy frame header into buffer
	memcpy(pNextFreeBufferSpace, mpdu.buffer(), Frame::HEADER_SIZE + 1);	// Frame header + Frametype and Sensor ID
	pNextFreeBufferSpace += Frame::HEADER_SIZE + 1;	// Move pointer to next free space

	// Copy network time right afer
	memcpy(pNextFreeBufferSpace, &networkTime, sizeof(desenet::NetworkTime));	// Network time
	pNextFreeBufferSpace += sizeof(desenet::NetworkTime);	// Move pointer to next free space

	// Copy remaining part of MPDU and EOF into buffer (ePDU Count and following fields)
	memcpy(pNextFreeBufferSpace, mpdu.buffer() + Frame::HEADER_SIZE + 1, mpdu.length() - (Frame::HEADER_SIZE + 1));
	//pNextFreeBufferSpace += mpdu.length() - (Frame::HEADER_SIZE + 1);		// Move pointer to next free space
}

Msg::~Msg()
{
}

bool Msg::isValid() const
{
	return (_headerPrepared &&			// Header needs to be initialized
			_buffer.length() == serialcon::HEADER_SIZE + (size_t)payloadSize() + serialcon::TRAILER_SIZE &&		// Internal buffer needs to have to right size
			crc() == calculateCrc());	// CRC needs to be set correctly
}

const Msg & Msg::operator=(const Msg & msg)
{
	if (this != &msg)
	{
		_headerPrepared = msg._headerPrepared;
		_buffer = msg._buffer;
	}
	return msg;
}

serialcon::MsgType Msg::type() const
{
	return static_cast<MsgType>(_buffer[1]);
}

uint8_t Msg::payloadSize() const
{
	return _buffer[2];
}

const uint8_t * Msg::payloadData() const
{
	return &_buffer[3];
}

void Msg::setCrc(uint8_t crc)
{
	assert(_headerPrepared);	// For CRC field access, the message header needs to be initialized!

	_buffer[serialcon::HEADER_SIZE + payloadSize()] = crc;
}

uint8_t Msg::crc() const
{
	assert(_headerPrepared);	// For CRC field access, the message header needs to be initialized!

	return _buffer[serialcon::HEADER_SIZE + payloadSize()];
}

uint8_t Msg::calculateCrc() const
{
	uint8_t crc = 0;
	const uint16_t byteCount = serialcon::HEADER_SIZE + payloadSize();

	assert(_headerPrepared);	// For CRC field access, the message header needs to be initialized!

	for (uint16_t i = 0; i < byteCount; i++)
	{
		crc += _buffer[i];
	}

	return 0xFF - crc;
}

serialcon::CmdType Msg::cmd() const
{
	assert(type() == CMD);
	return static_cast<CmdType>(*payloadData());	// Cmd is first byte of payload data
}

uint32_t Msg::cmdData() const
{
	uint32_t cmdData = 0;

	assert(type() == CMD);

	if (payloadSize() == 5)
	{
		// CMD data size is 4 bytes
		memcpy(&cmdData, payloadData() + 1, 4);
	}
	else if (payloadSize() == 2)
	{
		// CMD data size is 1 byte
		cmdData = payloadData()[1];
	}
	else
	{
		assert(payloadSize() == 1);		// Cmd without data
		cmdData = 0;
	}

	return cmdData;
}

bool Msg::beaconFields(desenet::Address & destinationAddress,
					   uint32_t & networkTime,
					   desenet::CycleDuration & cycleDuration,
					   desenet::SlotDuration & slotDuration,
					   uint16_t & svGroupMask) const
{
	assert(type() == BEACON);	// Method must only be called if message type is a beacon

	if (payloadSize() == 12 + desenet::Frame::HEADER_SIZE)
	{
		const uint8_t * data = payloadData();

		// First field is the destination address. Copy them
		destinationAddress.copyFrom(data);
		data += desenet::Frame::HEADER_SIZE;
		data += 1; // Omit byte containing Frametype field

		memcpy(&networkTime, data, 4);
		data += 4;

		cycleDuration = 0;
		memcpy(&cycleDuration, data, 3);
		data += 3;

		memcpy(&slotDuration, data, 2);
		data += 2;

		memcpy(&svGroupMask, data, 2);
		//data += 2;

		return true;
	}

	return false;
}

void Msg::prepareHeader(MsgType msgType, uint8_t payloadSize)
{
	_headerPrepared = true;

	_buffer[0] = serialcon::SOF;
	_buffer[1] = msgType;
	_buffer[2] = payloadSize;
}
#endif // DESENET_GATEWAY_NODE
