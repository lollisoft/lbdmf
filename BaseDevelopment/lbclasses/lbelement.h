


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.5 $
 * $Name:  $
 * $Id: lbelement.h,v 1.5 2001/06/21 06:33:40 lolli Exp $
 * $Log: lbelement.h,v $
 * Revision 1.5  2001/06/21 06:33:40  lolli
 * Removed some members
 *
 * Revision 1.4  2001/04/13 07:39:29  lolli
 * Commit for backup
 *
 * Revision 1.3  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.2  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  1999/12/14 21:09:02  lolli
 * Bugfixes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/

#ifndef LB_ELEMENT
#define LB_ELEMENT

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


#include <stdlib.h>
#include <lbInterfaces-sub-classes.h>

class lbKeyBase;
class lbObject;

class DLLEXPORT lbElement : public lb_I_Element {
private:

public:
    lbElement() { next = NULL; data = NULL; key = NULL; }
    virtual ~lbElement();
	
    lbElement(const lb_I_Element &e) { next = e.getNext(); }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

    lb_I_Unknown* getObject() const;

    int operator == (const lb_I_Element &a) const;

    int operator == (const lb_I_KeyBase &key) const;

};
#endif //LB_ELEMENT
