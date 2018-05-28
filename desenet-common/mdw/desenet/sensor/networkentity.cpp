#include <assert.h>
#include <array>
#include <list>
#include <map>
#include <vector>
#include <utility>
#include "platform-config.h"
#include "desenet/frame.h"
#include "desenet/beacon.h"
#include "abstractapplication.h"
#include "factory.h"
#include "networkentity.h"
#include "board/ledcontroller.h"

using std::array;
using std::list;
using std::map;
using std::make_pair;
using std::bind;
using std::pair;
using std::vector;

using desenet::sensor::NetworkEntity;

NetworkEntity * NetworkEntity::_pInstance(nullptr);		// Instantiation of static attribute

NetworkEntity::NetworkEntity()
 : _pTimeSlotManager(nullptr),
   _pTransceiver(nullptr)
{
	assert(!_pInstance);		// Only one instance allowed
	_pInstance = this;
}

NetworkEntity::~NetworkEntity()
{
}

void NetworkEntity::initialize()
{
}

void NetworkEntity::initializeRelations(ITimeSlotManager & timeSlotManager, NetworkInterfaceDriver & transceiver)
{
	_pTimeSlotManager = &timeSlotManager;
    _pTransceiver = &transceiver;

    _pTimeSlotManager->setObserver(*this);

    // Initialize the publishRequest
    for (int group=0; group<16; ++group)
    {
    	pubApps[group] = nullptr;
    }

     // Set the receive callback between transceiver and network. Bind this pointer to member function
    transceiver.setReceptionHandler(std::bind(&NetworkEntity::onReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

/**
 * This method does not automatically create an instance if there is none created so far.
 * It is up the the developer to create an instance of this class prior to access the instance() method.
 */
//static
NetworkEntity & NetworkEntity::instance()
{
	assert(_pInstance);
	return *_pInstance;
}

/**
 * Called by the NetworkInterfaceDriver (layer below) after reception of a new frame
 */
void NetworkEntity::onReceive(NetworkInterfaceDriver & driver, const uint32_t receptionTime, const uint8_t * const buffer, size_t length)
{
	UNUSED(driver);
	UNUSED(receptionTime);
	Frame frame = Frame::useBuffer(buffer, length);

	Factory::instance().ledController().flashLed(0);

	// Test of the frame validity
	if(frame.isValid())
	{
		// Test if the frame is a Beacon
		if(frame.type() == FrameType::Beacon)
		{
			Beacon beacon(frame);

			SharedByteBuffer buffer(7);		// 8 bytes: Maximum size of the data
			uint8_t size;

			// Start the timing
			_pTimeSlotManager->onBeaconReceived(beacon.slotDuration());

			// Synchronization of all registered applications
		    for(ApplicationSyncList::iterator itApp = syncApps.begin(); itApp!=syncApps.end(); ++itApp)
		    {
		    	// Indication to the AbstractApplication to make the measurement
		    	(*itApp)->svSyncIndication(beacon.networkTime());

		    }

		    // Requesting values to all registered applications
		    for(ApplicationSyncList::iterator itApp = syncApps.begin(); itApp!=syncApps.end(); ++itApp)
		    {
		    	size = (*itApp)->svPublishIndication(SVGROUP_ACCELEROMETER, buffer);

		    	// Add SV PDU to the frame
		    	mpdu.addSVePDU(SVGROUP_ACCELEROMETER, &buffer, size);
		    }
		}
	}
}

/*
 * Application Registration
 */
void NetworkEntity::svSyncRequest(AbstractApplication* theApp)
{
	syncApps.push_front(theApp);
}

/*
 * Request for permission to publish data
 */
bool NetworkEntity::svPublishRequest(AbstractApplication* theApp, SvGroup group)
{
	bool valRet = false;
	// Test if the group is free for registration
	if(pubApps[group] == nullptr)
	{
		valRet = true;
		pubApps[group] = theApp;
	}
	return valRet;
}

/*
 * Add event to the list of events
 */
void NetworkEntity::evPublishRequest(EvId id, SharedByteBuffer & evData)
{
	EventElement	eventElement(id, evData);
	// Using Push_back so that if the joystick and pressed and released in less than one cycle time
	// the release is taken into account after the press.
	events.push_back(eventElement);
}

/*
 * Timings management
 */
void NetworkEntity::onTimeSlotSignal(const ITimeSlotManager & timeSlotManager, const ITimeSlotManager::SIG & signal)
{
	switch ( signal ) {
	case ITimeSlotManager::SIG::CYCLE_START:
	  break;
	case ITimeSlotManager::SIG::CYCLE_FINISH:
	  break;
	// When MulitPDUs can be sent
	case ITimeSlotManager::SIG::OWN_SLOT_START:

		// Browse the list of events
		for(EventElementList::iterator itEvent = events.begin(); itEvent!=events.end(); ++itEvent)
		{
			// Adding EV PDUs to the MultiPDU Frame
			mpdu.addEVePDU((*itEvent).id,&(*itEvent).data, (*itEvent).data.length()); // group
		}

		events.clear();				// Empty the list of events
		mpdu.truncate();			// Shorten the MultiPDU frame
		//Trace::outln(mpdu.toString());
		*_pTransceiver << mpdu;		// Send the frame
		mpdu.reset();				// Cleaning the frame

	  break;
	case ITimeSlotManager::SIG::OWN_SLOT_FINISH:
	  break;
	default:
	  break;
	}
}
