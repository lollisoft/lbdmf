


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: lbelement.h,v 1.2 2000/10/05 22:56:45 lothar Exp $
 * $Log: lbelement.h,v $
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

/**
 * lbContainer represents the interface to all containers used.
 * 
 *
 *
 *
 */

class lbKeyBase;
class lbObject;

class DLLEXPORT lbElement {
public:
    lbElement(const lb_I_Object &o, const lb_I_KeyBase &_key, lbElement *_next=NULL);
    lbElement(const lbElement &e) { next = e.getNext(); }
    virtual ~lbElement();

    lbElement* getNext() const {return next; }
    void setNext(lbElement *e){ next = e; }
    lb_I_Object* getObject() const;

//    lbKeyBase &getKey() const { return *key; }
    lb_I_KeyBase *getKey() const
    {
        if (!key) printf("Key in lbElement is null\n");
        return key;
    }

    int operator == (const lbElement &a) const;

    int operator == (const lb_I_KeyBase &key) const;

private:

    lbElement* next;
    lb_I_Object* data;
    lb_I_KeyBase* key;
};
#endif //LB_ELEMENT
