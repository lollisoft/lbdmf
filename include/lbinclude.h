#ifndef LB_INCLUDE
#define LB_INCLUDE

#include <windows.h>

#include <lb_misc.h> // Helpers collected here

#include <lbObject.h>
#include <lbKey.h>

// Global definitions like GUITypes and so on
#include <lbGlobal.h>

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
#endif

#ifdef LB_CLASSES_DLL_INC
#include <lbObject.h>
#include <lbKey.h>
#include <lbContainer.h>
#include <lbThread.h>
#endif

#ifdef LB_CS_DLL_INC
#include <lbObject.h>
#include <appcs.h>
#include <transfer.h>
#include <appbus.h>
#include <lbthread.h>
#endif
#endif
