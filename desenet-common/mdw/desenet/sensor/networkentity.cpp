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

    // initialisation des publishRequest
    for (int group=0; group<16; ++group)
    {
    	pub[group] = nullptr;
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

	// TODO: Add your code here
	// Test la validité de la frame
	if(frame.isValid())
	{
		// Test sur la frame est un Beacon
		if(frame.type() == FrameType::Beacon)
		{
			Beacon beacon(frame);

			Trace::outln(frame.toString());

			SharedByteBuffer buffer(7);		//
			uint8_t size;	//

			// Lancer les timing
			_pTimeSlotManager->onBeaconReceived(beacon.slotDuration());

			// Synchronisation de toutes les app inscrites
		    for(ApplicationSyncList::iterator itApp = syncApps.begin(); itApp!=syncApps.end(); ++itApp)
		    {
		    	// Indication à l'AbstractApplication de faire la mesure
		    	(*itApp)->svSyncIndication(beacon.networkTime());

		    }

		    // Demande des valeurs
		    for(ApplicationSyncList::iterator itApp = syncApps.begin(); itApp!=syncApps.end(); ++itApp)
		    {
		    	size = (*itApp)->svPublishIndication(SVGROUP_ACCELEROMETER, buffer);

		    	// Creation SV PDU
		    	mpdu.addSVePDU(SVGROUP_ACCELEROMETER, &buffer, size); // group
		    }
		}
	}
}

void NetworkEntity::svSyncRequest(AbstractApplication* theApp)
{
	syncApps.push_front(theApp);
}

bool NetworkEntity::svPublishRequest(AbstractApplication* theApp, SvGroup group)
{
	bool valRet = false;
	if(pub[group] == nullptr)
	{
		valRet = true;
		pub[group] = theApp;
		Trace::outln("-- svPublishRequest -- : %x", theApp);
		Trace::outln("-- AppGroup -- : %d", group);
	}
	return valRet;
}
// Add event to the list of that
void NetworkEntity::evPublishRequest(EvId id, SharedByteBuffer & evData)
{
	EventElement	eventElement(id, evData);
	events.push_back(eventElement);
}

void NetworkEntity::onTimeSlotSignal(const ITimeSlotManager & timeSlotManager, const ITimeSlotManager::SIG & signal)
{

	switch ( signal ) {
	case ITimeSlotManager::SIG::CYCLE_START:
	  break;
	case ITimeSlotManager::SIG::CYCLE_FINISH:
	  break;
	case ITimeSlotManager::SIG::OWN_SLOT_START:

		 for(EventElementList::iterator itEvent = events.begin(); itEvent!=events.end(); ++itEvent)
		{
			// Creation EV PDU
			mpdu.addEVePDU((*itEvent).id,&(*itEvent).data, (*itEvent).data.length()); // group
		}
		events.clear();

		// Sample Values
		mpdu.truncate();
		Trace::outln(mpdu.toString());
		*_pTransceiver << mpdu;
		//mpdu.truncate();
		mpdu.reset();

		// Events

	  break;
	case ITimeSlotManager::SIG::OWN_SLOT_FINISH:
	  break;
	default:
	  break;
	}
}
