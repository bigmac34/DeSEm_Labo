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

namespace desenet
{
	MultiPDU::MultiPDU() : Frame(MultiPDU::SIZE)
	{
		memset(buffer() + HEADER_SIZE, 0, 1);	// Mise à zero du 1er byte
	    setDestination(GATEWAY_ADDRESS);		// Adresse

		MultiPDU::reset();						// Nettoyage de la trame
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

    	if(HEADER_SIZE + offset + length + FOOTER_SIZE <= SIZE)
    	{
    		// Incrementation du compteur de ePDU
    		ePDUCount++;

    		// Création de l'header ePDU
    		HEADER_EPDU header;
    		header.length = length;		// length (bits 0-2)
    		header.sVGroup = svGroup;	// svGroup (bits 3-6)
    		header.ePDUType = 0;		// ePDU Type = 0 (bit 7)

			// Mise à jour du counter d'ePDU
			memcpy(buffer() + HEADER_SIZE + 1, &ePDUCount, sizeof(ePDUCount));

    		// Ajout de l'header et des datas à la trame
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset, &header, sizeof(header));
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset + 1, sharedBuffer->data(), length); // sizeof(data)

    	    // Incrementation de l'offset
    	    offset += length + 1;

    	    valRet = true;
    	}
    	return valRet;
    }

    bool MultiPDU::addEVePDU(EvId evid, SharedByteBuffer *event, SharedByteBuffer::sizeType length)
    {
    	bool valRet = false;

    	if(HEADER_SIZE + offset + length + FOOTER_SIZE <= SIZE)
    	{
    		// Incrementation du compteur de ePDU
    		ePDUCount++;

    		// Creation de l'header
			HEADER_EPDU header;
			header.length = length;		// length (bits 0-2)
			header.sVGroup = evid;		// svGrevidoup (bits 3-6)
			header.ePDUType = 1;		// ePDU Type = 1 (bit 7)

			// Mise à jour du counter d'ePDU
			memcpy(buffer() + HEADER_SIZE + 1, &ePDUCount, sizeof(ePDUCount));

    		// Ajout de l'header et des datas à la trame
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset, &header, sizeof(header));
    	    memcpy(buffer() + HEADER_SIZE + 2 + offset + 1, event, length);

    	    // Incrementation de l'offset
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

    	// Remise de la trame à sa taille maximale
    	detruncate();

    	// Mise à 0 de tout les champs après le header
    	for(int i = 0; i < 32; ++i)
    	{
    		memcpy(buffer() + HEADER_SIZE + i, &empty, sizeof(empty));
    	}

    	// Initialisation du début de la trame
    	setDestination(GATEWAY_ADDRESS);
    	//setSensorID(DESENET_SLOT_NUMBER);
    	setSensorID(1);
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
