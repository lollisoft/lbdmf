


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.5 $
 * $Name:  $
 * $Id: lbcontainer.h,v 1.5 2001/03/04 18:30:25 lolli Exp $
 * $Log: lbcontainer.h,v $
 * Revision 1.5  2001/03/04 18:30:25  lolli
 * Compiles now with interface support
 *
 * Revision 1.4  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.3  2000/06/24 21:32:08  lolli
 * Socket bugfix
 *
 * Revision 1.2  2000/04/27 01:36:24  lolli
 * Commit in order of data GAU
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  1999/12/14 21:07:38  lolli
 * Many changes, also bugfixes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/

#ifndef LB_CONTAINER
#define LB_CONTAINER

/*...sDLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/


#include <lbInterfaces-sub-classes.h>

/**
 * lbContainer represents the interface to all containers used.
 * 
 *
 *
 *
 */

class lbObject; // THE base class
class lbElement; // Container for one lbObject
class lbKey; // Search criteria

extern lbCritSect critsect;

lbErrCodes DLLEXPORT instanceOf_lb_I_Container(lb_I_Container*& inst);

#endif //LB_CONTAINER
