


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.9 $
 * $Name:  $
 * $Id: lbcontainer.h,v 1.9 2001/07/11 16:04:35 lolli Exp $
 * $Log: lbcontainer.h,v $
 * Revision 1.9  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.8  2001/06/23 07:18:54  lolli
 * Interface repository now works with the basic test
 *
 * Revision 1.7  2001/06/21 06:32:55  lolli
 * Using IMPLEMENT_FUNCTOR(instanceOfContainer, lbContainer)
 *
 * Revision 1.6  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
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


/*...sclass lbContainer:0:*/
class lbContainer : 	public lb_I_Container
{

public:
    lbContainer(const lb_I_Container* c);
    lb_I_Container* operator= (const lb_I_Container* c);

public:

    lbContainer();
    virtual ~lbContainer();

    DECLARE_LB_UNKNOWN()

// This may be a string container

    DECLARE_LB_I_CONTAINER_IMPL()

};
/*...e*/


extern lbCritSect critsect;

/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/
DECLARE_FUNCTOR(instanceOfContainer)
/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif //LB_CONTAINER
