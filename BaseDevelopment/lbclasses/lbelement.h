


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.7 $
 * $Name:  $
 * $Id: lbelement.h,v 1.7 2001/08/18 07:34:48 lolli Exp $
 * $Log: lbelement.h,v $
 * Revision 1.7  2001/08/18 07:34:48  lolli
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.6  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
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

#include <stdlib.h>
#include <lbInterfaces-sub-classes.h>

class lbKeyBase;
class lbObject;

class DLLEXPORT lbElement : public lb_I_Element {
private:

public:
    lbElement() { 
    	ref = STARTREF; 
    	next = NULL; 
    	data = NULL; 
    	key = NULL; 
    	manager = NULL;
    }
    virtual ~lbElement();
	
    lbElement(const lb_I_Element &e) { 
    	ref = STARTREF; 
    	next = e.getNext(); 
	manager = NULL;
    }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

    lb_I_Unknown* getObject() const;

    int operator == (const lb_I_Element &a) const;

    int operator == (const lb_I_KeyBase &key) const;

};
#endif //LB_ELEMENT
