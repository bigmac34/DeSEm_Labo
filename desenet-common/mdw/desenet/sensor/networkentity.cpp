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
			// Synchronisation de toutes les app inscrites
		    for(ApplicationSyncList::iterator itApp = syncApps.begin(); itApp!=syncApps.end(); ++itApp)
		    {
		    	// Indication à l'AbstractApplication de faire la mesure
		    	(*itApp)->svSyncIndication(receptionTime);

		    	// Lancer les timing
		    	_pTimeSlotManager->onBeaconReceived(receptionTime);
		    	// encore des trucs a faire mais pas encore compris

		    }
		}
	}

}

void NetworkEntity::svSyncRequest(AbstractApplication* theApp)
{
	syncApps.push_front(theApp);
}

void NetworkEntity::svPublishRequest(AbstractApplication* theApp, SvGroup group)
{
	// A completer pour le sampled values publishing
}

void NetworkEntity::onTimeSlotSignal(const ITimeSlotManager & timeSlotManager, const ITimeSlotManager::SIG & signal)
{
	// A compléter mais pas sur que c'est la bonnne fonction par rapport a l'observateur
}
