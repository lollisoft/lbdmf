#ifndef __LB_MODULE__
#define __LB_MODULE__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.6 $
 * $Name:  $
 * $Id: lbModule.h,v 1.6 2001/06/23 07:18:53 lothar Exp $
 *
 * $Log: lbModule.h,v $
 * Revision 1.6  2001/06/23 07:18:53  lothar
 * Interface repository now works with the basic test
 *
 **************************************************************/
/*...e*/

#include <iostream.h>

/*...sDLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/


/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

lbErrCodes DLLEXPORT LB_STDCALL getlb_ModuleInstance(lb_I_Module*& inst);
lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst);

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif // __LB_MODULE__
