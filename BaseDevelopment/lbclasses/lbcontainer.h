


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.4 $
 * $Name:  $
 * $Id: lbcontainer.h,v 1.4 2000/10/05 22:56:45 lothar Exp $
 * $Log: lbcontainer.h,v $
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

/*...sclass DLLEXPORT lbContainer:0:*/
class DLLEXPORT lbContainer : public
			lb_I_Container
{

private:
    lbContainer(const lbContainer & c);
    lb_I_Container& operator= (const lbContainer & c);

public:

    lbContainer();
    virtual ~lbContainer();

    int Count();

    lbErrCodes insert(const lb_I_Object &e, const lb_I_KeyBase &key);
    lbErrCodes remove(const lb_I_KeyBase &key);
    
	/**
	 * General functions needed for storage (key driven)
	 */
    virtual lbErrCodes _insert(const lb_I_Object &e, const lb_I_KeyBase &key) = 0;
    virtual lbErrCodes _remove(const lb_I_KeyBase &key) = 0;
    virtual int exists(const lb_I_KeyBase& e) = 0;

	/**
	 * Iterator (forward only)
	 */
    virtual int hasMoreElements() = 0;
    virtual lb_I_Object* nextObject() = 0;

protected:
    /**
     * This should be used internally only
     */
    virtual lbElement* nextElement() = 0;

public:

	/**
	 * Direct access over key
	 */
    virtual lb_I_Object* getElement(const lb_I_KeyBase &key) = 0;
    virtual void setElement(lb_I_KeyBase &key, const lb_I_Object &e) = 0;

    virtual lb_I_Container* clone() = 0;

    virtual void deleteAll() = 0;

protected:
    int count;
    int iteration; // This shows, if iteration has begun
    lbElement* iterator;

    lbCritSect critsect;
    int ref;
};
/*...e*/

/*...sclass DLLEXPORT lbComponentDictionary:0:*/
class DLLEXPORT lbComponentDictionary: public lbContainer {

private:
    lbComponentDictionary(const lbComponentDictionary & c);
    lbComponentDictionary& operator= (const lbComponentDictionary & c);

public:

    lbComponentDictionary();
    virtual ~lbComponentDictionary();
    
    virtual lbErrCodes _insert(const lb_I_Object &e, const lb_I_KeyBase &key);
    virtual lbErrCodes _remove(const lb_I_KeyBase &key);
    
    virtual int exists(const lb_I_KeyBase &key);

    virtual int hasMoreElements();
    virtual lb_I_Object* nextObject();
    virtual lbElement* nextElement();

    virtual lb_I_Container* clone();

    virtual void deleteAll();

    virtual lb_I_Object* getElement(const lb_I_KeyBase &key);
    virtual void setElement(lb_I_KeyBase &key, const lb_I_Object &e);
    virtual lb_I_Object* getObject();

private:

    lbElement* data;    
};
/*...e*/

extern lbCritSect critsect;

lbErrCodes DLLEXPORT getContainerInstance(lb_I_Container*& inst, const char* type);

#endif //LB_CONTAINER
