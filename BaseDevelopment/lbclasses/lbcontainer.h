


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.3 $
 * $Name:  $
 * $Id: lbcontainer.h,v 1.3 2000/06/24 21:32:08 lolli Exp $
 * $Log: lbcontainer.h,v $
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
class DLLEXPORT lbContainer {

private:
    lbContainer(const lbContainer & c);
    lbContainer& operator= (const lbContainer & c);

public:

    lbContainer();
    virtual ~lbContainer();

    int Count();

    lbErrCodes insert(const lbObject &e, const lbKeyBase &key);
    lbErrCodes remove(const lbKeyBase &key);
    
	/**
	 * General functions needed for storage (key driven)
	 */
    virtual lbErrCodes _insert(const lbObject &e, const lbKeyBase &key) = 0;
    virtual lbErrCodes _remove(const lbKeyBase &key) = 0;
    virtual int exists(const lbKeyBase& e) = 0;

	/**
	 * Iterator (forward only)
	 */
    virtual int hasMoreElements() = 0;
    virtual lbObject* nextObject() = 0;
    virtual lbElement* nextElement() = 0;

	/**
	 * Direct access over key
	 */
    virtual lbObject* getElement(const lbKeyBase &key) = 0;
    virtual void setElement(lbKeyBase &key, const lbObject &e) = 0;

    virtual lbContainer* clone() = 0;

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
    
    virtual lbErrCodes _insert(const lbObject &e, const lbKeyBase &key);
    virtual lbErrCodes _remove(const lbKeyBase &key);
    
    virtual int exists(const lbKeyBase &key);

    virtual int hasMoreElements();
    virtual lbObject* nextObject();
    virtual lbElement* nextElement();

    virtual lbContainer* clone();

    virtual void deleteAll();

    virtual lbObject* getElement(const lbKeyBase &key);
    virtual void setElement(lbKeyBase &key, const lbObject &e);
    virtual lbObject* getObject();

private:

    lbElement* data;    
};
/*...e*/

extern lbCritSect critsect;

#endif //LB_CONTAINER
