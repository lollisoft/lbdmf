#ifndef __LB_MODULE__
#define __LB_MODULE__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.7 $
 * $Name:  $
 * $Id: lbModule.h,v 1.7 2001/07/11 16:04:33 lothar Exp $
 *
 * $Log: lbModule.h,v $
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

DECLARE_FUNCTOR(getlb_ModuleInstance)
//lbErrCodes DLLEXPORT LB_STDCALL getlb_ModuleInstance(lb_I_Module*& inst);
lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst);

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif // __LB_MODULE__
