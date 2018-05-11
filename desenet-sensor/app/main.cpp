#include "platform-config.h"
#include "xf/xf.h"
#include "factory.h"

int main(int argc, char ** argv)
{
	XF_PREPARE;

	Factory factory(argc, argv);

	XF::init(10);	// Initialize XF

	// Create and initialize objects
	factory.buildApplication();

	XF::start();	// StartXF

	return 0;
}
