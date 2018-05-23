#pragma once
#include <string>
#include "frame.h"
#include "types.h"

namespace desenet
{

class MultiPDU : public Frame
{
private:

	struct HEADER_EPDU
	{
		uint8_t length : 3;
		uint8_t sVGroup : 4;
		uint8_t ePDUType : 1;
	};

	union HESDER_EPDU_UINT8
	{
		uint8_t byte;
		HEADER_EPDU headerPDU;
	};

public:
	static const uint8_t SIZE = Frame::Mtu;			// Maximum frame size

	/**
     * @brief Constructs a new MultiPDU frame.
     *
     * Allocates a new frame and default values for all fields.
     *
     */
	MultiPDU(void);

    /**
     * @brief Constructs a MultiPDU from the frame data.
     *
     * Note that the constructor does not fail if the actual data in the frame is not a MultiPDU frame. Use the type() method and ensure that it returns
     * MultiPDU in order to check if the MultiPDU data is valid.
     *
     * @param frame		The frame to use to get the MultiPDU data.
     */
	MultiPDU(const Frame & frame);

    /**
     * @brief Sets the destination address.
     */
    void setDestinationAddress(Address destinationAddress);

    /**
     * @brief Sets the Sensor ID field.
     *
     * @param sensorID	sensor ID.
     */
    void setSensorID(uint8_t sensorID);

    /**
     * @brief Increment the ePDU count
     */
    void increPDUCount();

    /**
     * @brief add SV ePDU to the MultiPDU
     *
     * @param 	svGroup	the number of the SV Group
     *        	data		Pointer of the data
     * 		  	size		Size of the data
     *
     * @return 	fail : false
     */
    bool addSVePDU(SvGroup svGroup, SharedByteBuffer *data, uint8_t length);

    /**
     * @brief add SV ePDU to the MultiPDU
     *
     * @param svGroup	the number of the SV Group
     *        ePDU		Pointer of the event
     * 		  size		Size of the event
     *
     * @return 	fail : false
     */
    bool addEVePDU(EvId evid, SharedByteBuffer *event, SharedByteBuffer::sizeType length);

    /**
     * @brief set offset
     *
     * @param newOffset	New value or the offset
     */
    void setOffset(uint8_t newOffset);

    /**
     * @brief get offset
     *
     * @return value of the offset
     */
    uint8_t getOffset() const;

    /**
     * @brief reset mpdu
     *
     */
    void reset();

    void truncate();
    void detruncate();

private:
    uint8_t offset;	// Position of the end of the last ePDU
    MultiPDU mpdu();
    uint8_t ePDUCount;
};

} /* namespace desenet */
