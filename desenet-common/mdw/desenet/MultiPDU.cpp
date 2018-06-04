#include <algorithm>
#include <cstring>
#include "platform-config.h"
#include "MultiPDU.h"

using std::string;
using std::uint32_t;
using std::uint8_t;
using std::size_t;
using std::min;
using std::memcpy;
using std::memset;
using std::bitset;

extern desenet::SlotNumber __SLOT_NUMBER;

namespace desenet
{
	MultiPDU::MultiPDU() : Frame(MultiPDU::SIZE)
	{
		memset(buffer() + HEADER_SIZE, 0, 1);	// Reset first byte
	    setDestination(GATEWAY_ADDRESS);		// Set Address

		MultiPDU::reset();						// Reset the trame
	}

	MultiPDU::MultiPDU(const Frame & frame) : Frame(frame)
	{
		MultiPDU::reset();
	}

    void MultiPDU::setDestinationAddress(Address destinationAddress)
    {
    	Frame::setDestination(destinationAddress);
    }

    void MultiPDU::setSensorID(uint8_t sensorID)
    {
    	memcpy(buffer() + HEADER_SIZE, &sensorID, sizeof(sensorID));
    }

    void MultiPDU::increPDUCount()
    {
	    uint8_t count = 0;
	    memcpy(&count, buffer() + HEADER_SIZE + 1, sizeof(count));
	    count ++;
	    memcpy(buffer() + HEADER_SIZE + 1, &count, sizeof(count));
    }

    bool MultiPDU::addSVePDU(SvGroup svGroup, SharedByteBuffer *sharedBuffer, uint8_t length)
    {
    	bool valRet = false;

    	// Test if there is enough space in the frame
    	if((HEADER_SIZE + offset + length + FOOTER_SIZE + 2) < SIZE)
    	{
    		// Increment the ePDU counter
    		ePDUCount++;

    		// Create the ePDU header
    		HEADER_EPDU header;
    		header.length = length;		// length (bits 0-2)
    		header.sVGroup = svGroup;	// svGroup (bits 3-6)
    		header.ePDUType = 0;		// ePDU Type = 0 (bit 7)

			// Refresh ePDU counter
			memcpy(buffer() + HEADER_SIZE + 1, &ePDUCount, sizeof(ePDUCount));

    		// Add header and data to the frame
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset, &header, sizeof(header));
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset + 1, sharedBuffer->data(), length);

    	    // Increment the offset
    	    offset += length + 1;

    	    valRet = true;
    	}
    	return valRet;
    }

    bool MultiPDU::addEVePDU(EvId evid, SharedByteBuffer *event, SharedByteBuffer::sizeType length)
    {
    	bool valRet = false;

    	// Test if there is enough space in the frame
    	if((HEADER_SIZE + offset + length + FOOTER_SIZE + 2) < SIZE)
    	{
    		// Increment the ePDU counter
    		ePDUCount++;

    		// Create the header
			HEADER_EPDU header;
			header.length = length;		// length (bits 0-2)
			header.sVGroup = evid;		// svGrevidoup (bits 3-6)
			header.ePDUType = 1;		// ePDU Type = 1 (bit 7)

			// Refresh ePDU counter
			memcpy(buffer() + HEADER_SIZE + 1, &ePDUCount, sizeof(ePDUCount));

    		// Add header and data to the frame
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset, &header, sizeof(header));
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset + 1, event, length);

    	    // Increment offset
    	    offset += length + 1;

    	    valRet =  true;
    	}
    	return valRet;
    }

    void MultiPDU::setOffset(uint8_t newOffset)
    {
    	offset = newOffset;
    }

    uint8_t MultiPDU::getOffset() const
    {
    	return offset;
    }

    void MultiPDU::reset()
    {
    	uint8_t empty = 0;

    	// Expend frame to the maximum size
    	detruncate();

    	// Reset all the header
    	for(int i = 0; i < 32; ++i)
    	{
    		memcpy(buffer() + HEADER_SIZE + i, &empty, sizeof(empty));
    	}

    	// Initialize the begin of the frame
    	setDestination(GATEWAY_ADDRESS);
    	setSensorID(__SLOT_NUMBER);
    	setType(FrameType::MPDU);
    	setOffset(0);
    	ePDUCount = 0;

    }

    void MultiPDU::truncate()
    {
    	setLength(Frame::HEADER_SIZE + 2 + offset);
    }

    void MultiPDU::detruncate()
    {
    	setLength(Frame::HEADER_SIZE + 32 + Frame::FOOTER_SIZE);
    }
} /* namespace desenet */
