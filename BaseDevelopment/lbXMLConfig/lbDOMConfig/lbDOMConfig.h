/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.5 $
 * $Name:  $
 * $Id: lbDOMConfig.h,v 1.5 2002/05/30 17:53:02 lothar Exp $
 *
 * $Log: lbDOMConfig.h,v $
 * Revision 1.5  2002/05/30 17:53:02  lothar
 * Current development seems to run
 *
 * Revision 1.4  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.3  2001/12/08 11:51:12  lothar
 * Modified line 896 due to compilation errors
 *
 * Revision 1.2  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.1  2000/10/20 04:24:52  lothar
 * Initial
 *
 **************************************************************/

/*...e*/

#ifndef __LB_DOM_CONFIG__
#define __LB_DOM_CONFIG__

#pragma warning( disable : C4101 )


/*...sincludes:0:*/
#include <lbErrcodes.h>
#include <lbInterfaces.h>
/*...e*/


/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
#ifdef WINDOWS
extern "C" {
#endif
#endif
/*...e*/

DECLARE_FUNCTOR(getlbDOMConfigInstance)

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
#ifdef WINDOWS
}
#endif
#endif
/*...e*/

#endif
