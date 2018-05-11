#ifndef SERIALCON_H
#define SERIALCON_H

/*
 * @brief Namespace serialcon (appreviation of serial connection.
 *
 * Defines a simple point-to-point protocol.
 */
namespace serialcon {

//
// Serialcon message format:
//
//    1B      1B           1B             payload size bytes        1B
// +-------------------------------------------------------------------+
// | SOF | MSG type | Payload Size |              ...            | CRC |
// +-------------------------------------------------------------------+
//
// CRC is calculated from SOF to the end of payload data.
// Refer to the calculateCrc() method on how to calculate the CRC.
//

	/**
	 * Defines the messages types exchanged between the
	 * two endpoints.
	 */
	typedef enum
	{
		UNKNOWN_MSGTYPE = 0x00,
		CMD = 0x01,										// host -> gateway
		BEACON = 0x02,									// host -> gateway
		MPDU = 0x03,									// host <- gateway
		TRACE = 0x04,									// host <- gateway
		ERROR = 0x05									// host <- gateway
	} MsgType;

	/**
	 * Commands available to send from host to gateway
	 */
	typedef enum
	{
		UNKNOWN_CMDTYPE = 0x00,
		OPERATION_MODE = 0x01,			///< See OperationMode
		NETWORK_TIME = 0x02,			///< Network time for the desenet protocol
		CYCLE_DURATION = 0x03,			///< Time between beacons [ms]
		SLOT_DURATION = 0x04			///< Slot duration [ms]
	} CmdType;

	/**
	 * @brief The operation modes of the gateway.
	 *
	 * @see desenet::gateway:NetworkEntity
	 */
	typedef enum
	{
		GATEWAY = 0x01,			///< Host takes control and is sending beacons
		AUTONOMOUS = 0x02		///< Gateway works independently and sends beacons itself
	} OperationMode;

	static const char SOF = 0x7F;							// Constant value used for SOF (Start of Frame delimiter)
	static const unsigned char HEADER_SIZE = 3;				// Size in byte of the serialcon header (1 byte SOF, 1 bytes payload size, 1 byte message type)
	static const unsigned char TRAILER_SIZE = 1;			// Size in byte if the serialcon trailer (1 byte CRC)
	static const unsigned char MSG_TYPE_FIELD_SIZE = 1;		// Size in byte of the message type field.
} // namespace
#endif // SERIALCON_H
