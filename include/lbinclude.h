#ifndef LB_INCLUDE
#define LB_INCLUDE

/*...sdefine VERBOSE switches for modules:0:*/
//#define SOCKET_VERBOSE
//#define TRANSFER_VERBOSE

//#define CLASSES_VERBOSE
//#define THREAD_VERBOSE


//#define APPCS_VERBOSE

//#define APPBUS_VERBOSE
//#define APPBUS_SVR_VERBOSE
//#define APPBUS_CLT_VERBOSE
/*...e*/


#include <windows.h>

// Global definitions like GUITypes and so on
#include <lbGlobal.h>
#include <lbErrcodes.h>


#include <lbthread.h>
#include <lb_misc.h> // Helpers collected here

#include <lbObject.h>
#include <lbKey.h>


/**
 * LB_CS_DLL_INC needs LB_CLASSES_DLL_INC and LB_TRANSFER_DLL_INC
 *
 * so include it also
 */

#ifdef LB_CS_DLL_INC
#define LB_CLASSES_DLL_INC
#define LB_TRANSFER_DLL_INC
#endif

/**
 * For a LB_WX_APP_INC no LB_TRANSFER_DLL_INC needed to be declared.
 * So declare LB_CS_DLL_INC behind the above block.
 */

#ifdef LB_WX_APP_INC
#define LB_CLASSES_DLL_INC
// Include only lb_I_wxGUI.h
#define LB_WX_I_INC
//#define LB_CS_DLL_INC
#endif

/**
 * LB_TRANSFER_DLL_INC needs LB_CLASSES_DLL_INC
 *
 * so include it also
 */

#ifdef LB_TRANSFER_DLL_INC
#define LB_CLASSES_DLL_INC
#endif


/**
 * Currently all dlls need LB_TOOLS_DLL_INC
 */ 
 
#define LB_TOOLS_DLL_INC
 

#ifdef LB_TRANSFER_DLL_INC
#include <transfer.h>
#include <socket.h>
// Defines general interfaces
#include <lbInterfaces.h>
#endif

#ifdef LB_CLASSES_DLL_INC
#include <lbObject.h>
#include <lbKey.h>
#include <lbContainer.h>
#include <lbElement.h>
#endif

#ifdef LB_CS_DLL_INC
#include <lbObject.h>
#include <appcs.h>
#include <transfer.h>
#include <lbInterfaces.h>
#include <appbus.h>
#endif
#endif
