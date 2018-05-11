#ifndef XF_H
#define XF_H


#ifdef TC_MESHSIM /***************************************************************************************************/

#include <QtWidgets/QApplication>

/**
 * Macro used when working with Qt (TC_MESHSIM). MUST be called in the first line in function main().
 */
#define XF_PREPARE QApplication application( argc , argv )

#elif defined(TC_QTCONSOLE)

#include <QCoreApplication>

#define XF_PREPARE QCoreApplication application( argc , argv );

#else /***************************************************************************************************************/

#define XF_PREPARE

#endif /**************************************************************************************************************/


#include "xfthread.h"

/** 
 * @mainpage PTR Execution Framework Documentation
 * Link to @ref xf "XF module".
 */

/**
 * @defgroup xf XF
 * @{
 *
 * @section xf_cd Class Diagram
 * The XF (eXecution Framework) enables the implementation of complex finite state machines. The class diagram looks
 * like this:
 * @image html XF.png
 * For more details have a look into the documentation...
 *
 * - XF Version: 0.4 (2015-03-02)
 *  + sth: XFTimoutManager now returns timeouts with same value correctly
 * - XF Version: 0.3 (2011-04-13)
 *  + sth: Added more critical sections in XFTimeoutManager
 *  + sth: Fixed  bug in XFTimeoutManager::removeTimeouts
 * - XF Version: 0.2 (2011-03-07)
 *  + sth: Fixed bug in XFTimeoutManager::addTimeout method
 * - XF Version: 0.1 (2010-11-26)
 *  + sth: First release
 */

#ifndef NULL
#	define NULL 0
#endif

/**
 * Static class grouping the basic methods for the XF together.
 */
class XF
{
public:
	static void init(int timeInterval = 10);


#ifdef TC_STM32 /*****************************************************************************************************/

	static void start();

#elif defined( TC_MESHSIM ) /*****************************************************************************************/

	static inline void start() __attribute__(( always_inline )) { QApplication::exec(); }

#elif defined( TC_QTCONSOLE ) /***************************************************************************************/

	static inline void start() __attribute__(( always_inline )) { QCoreApplication::exec(); }

#endif /**************************************************************************************************************/


	static XFThread * getMainThread();	///< Returns pointer the main thread.

protected:
	static bool _bInitialized;			///< Changes from false to true after calling method init(int). Used to handle multiple calls to init(int).
	static XFThread _mainThread;		///< Main thread executing the main loop

};


/** @} */
#endif // XF_H
