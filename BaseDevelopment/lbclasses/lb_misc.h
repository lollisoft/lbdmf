/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.6 $
 * $Name:  $
 * $Id: lb_misc.h,v 1.6 2001/07/11 16:04:34 lolli Exp $
 * $Log: lb_misc.h,v $
 * Revision 1.6  2001/07/11 16:04:34  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.5  2001/05/04 17:14:43  lolli
 * Use of MACRO DECLARE_FUNCTOR works
 *
 * Revision 1.4  2001/05/01 15:51:52  lolli
 * First instance could be loaded over the new module management
 *
 * Revision 1.3  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.2  2001/02/06 20:38:18  lolli
 * Commit for backup the data
 *
 * Revision 1.1  2000/07/06 06:19:40  lolli
 * Readded (possibly to new location)
 *
 * Revision 1.6  2000/03/16 08:58:07  lolli
 * Version crashes
 *
 * Revision 1.5  2000/01/18 21:13:17  lolli
 * Current version
 *
 * Revision 1.4  1999/10/12 06:34:47  Lothar_Behrens
 * Added logging / and a new class for debug via log
 *
 **************************************************************/
/*...e*/

#ifndef _MISC_
#define _MISC_

/*...sincludes:0:*/
#include <time.h>
#include <string.h>
#include <iostream.h>
#include <stdio.h>

#include <lbInterfaces.h>
/*...e*/


/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/
void lb_sleep(int ms);

DECLARE_FUNCTOR(instanceOfLogger)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#define TRUE 1
#define FALSE 0

class lbMutex;



extern lbCritSect sect;

#endif
