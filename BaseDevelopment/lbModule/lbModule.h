#ifndef __LB_MODULE__
#define __LB_MODULE__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.10 $
 * $Name:  $
 * $Id: lbModule.h,v 1.10 2001/12/15 17:57:01 lothar Exp $
 *
 * $Log: lbModule.h,v $
 * Revision 1.10  2001/12/15 17:57:01  lothar
 * Minor changes
 *
 * Revision 1.9  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.8  2001/07/18 05:49:13  lothar
 * minor changes
 *
 * Revision 1.7  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.6  2001/06/23 07:18:53  lothar
 * Interface repository now works with the basic test
 *
 **************************************************************/
/*...e*/

#include <iostream.h>

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst);
DECLARE_FUNCTOR(getlb_ModuleInstance)

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_MODULE__
