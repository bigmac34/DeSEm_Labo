#include "desenet/sensor/net.h"
#include "abstractapplication.h"
#include "networkentity.h"

using desenet::sensor::AbstractApplication;

// TODO: Uncomment for students.
//#error READ THE COMMENT HERE!
/*********************************************************************************************************
* TODO: Implement the protected methods of the AbstractApplication class here. From these you have to    *
* call the different methods on your DESENET Controller Entity implementation...                         *
*********************************************************************************************************/

// Default implementations.

void AbstractApplication::svSyncRequest()
{
	NetworkEntity::instance().svSyncRequest(this);
}

bool AbstractApplication::svPublishRequest(SvGroup group)
{
	NetworkEntity::instance().svPublishRequest(this, group);
	return false;
}

void AbstractApplication::evPublishRequest(EvId id, const SharedByteBuffer & evData)
{
}

/**
 * Default callback method for syncs
 */
void AbstractApplication::svSyncIndication(desenet::NetworkTime)
{
	// Appeler pour faire la mesure
}

/**
 * Default callback method for SV publishes
 */
SharedByteBuffer::sizeType AbstractApplication::svPublishIndication(SvGroup, SharedByteBuffer &)
{
	return 0;
}
