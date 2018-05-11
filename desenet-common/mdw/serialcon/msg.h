#ifndef SERIALCON_MSG_H
#define SERIALCON_MSG_H

#include <stdint.h>
#include "platform-config.h"
#include "containers/SharedByteBuffer"
#include "serialcon.h"

#if (DESENET_GATEWAY_NODE != 0) || defined(DESENET_TESTBENCH)

namespace desenet {
	class MultiPdu;
}

namespace serialcon
{

/**
 * @brief Message send over serialcon communication.
 */
class Msg
{
	friend class Controller;

public:
	Msg(const uint8_t * const buffer, size_t length);	///< buffer contains an already well formatted message (not just the payload for a message).
	Msg(const Msg & msg);
	Msg(const desenet::NetworkTime & networkTime, const desenet::MultiPdu & mpdu);
	virtual ~Msg();

	bool isValid() const;						///< Returns true if the message is well formatted.

	const Msg & operator=(const Msg & msg);		///< Copy operator.

	MsgType type() const;						///< Returns the message type located in the message header.
	uint8_t payloadSize() const;				///< Returns the payload size located in the message header.
	const uint8_t * payloadData() const;

	void setCrc(uint8_t crc);					///< Sets the CRC in the trailer of the message.
	uint8_t crc() const;						///< Returns the CRC in the trailer of the message.
	uint8_t calculateCrc() const;				///< Calculates the CRC (from SOF to end of payload data).

	CmdType cmd() const;						///< If message type is a CMD returns the CMD field.
	uint32_t cmdData() const;					///< If message type is a CMD returns the optional data field.

	bool beaconFields(desenet::Address & destinationAddress,
					  uint32_t & networkTime,
					  desenet::CycleDuration & cycleDuration,
					  desenet::SlotDuration & slotDuration,
					  uint16_t & svGroupMask) const;

protected:
	void prepareHeader(MsgType msgType, uint8_t payloadSize);		///< Initializes the message header.

	uint8_t * buffer() { return _buffer.data(); }					///< Returns a pointer to the buffer.
	const std::uint8_t * buffer() const { return _buffer.data(); }	///< Returns a read-only pointer to the buffer.
	size_t length() const { return _buffer.length(); }				///< Returns the message size in bytes.

protected:
	bool _headerPrepared;					///< Set to true after message header is initialized
	::hei::SharedByteBuffer _buffer;		///< Internal buffer holding the message.
};

} // namespace serialcon
#endif // DESENET_GATEWAY_NODE
#endif // SERIALCON_MSG_H
