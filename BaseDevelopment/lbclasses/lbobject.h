


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.4 $
 * $Name:  $
 * $Id: lbobject.h,v 1.4 2000/07/06 06:10:12 lolli Exp $
 * $Log: lbobject.h,v $
 * Revision 1.4  2000/07/06 06:10:12  lolli
 * Added classtype for dispatcher function container object
 *
 * Revision 1.3  2000/06/24 21:32:08  lolli
 * Socket bugfix
 *
 * Revision 1.2  2000/04/27 01:36:25  lolli
 * Commit in order of data GAU
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  2000/01/23 14:35:04  lolli
 * Corrected error in revision conflict
 *
 * Revision 1.1  1999/10/08 21:27:01  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/

#ifndef _LB_OBJECT_
#define _LB_OBJECT_

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


#include <stdio.h>

//class lbKeyBase;
class lbComponentDictionary;


/*...sclass DLLEXPORT lbObject:0:*/
class DLLEXPORT lbObject {
public:
    lbObject() {
		name = NULL;
		// Set to undefined state
		OTyp = LB_OBJECT;
	}

	lbObject(const lbObject &o) {
		setName(o.getName());
	}
    
    virtual ~lbObject() {}

	/**
	 * The type of an object
	 */
	enum ObjectTyp { LB_OBJECT, 
	                 LB_STRING,
                         LB_STRINGLIST,
	                 LB_GUIOBJECT, 
	                 LB_WXGUIOBJECT, 
	                 LB_DATA_TRANSFER_OBJECT,
	                 LB_CONNECTION,
	                 LB_APPBUSCLIENT,
	                 LB_APPSERVER_DISPATCH_FN,
	                 LB_EVENT };

	ObjectTyp getType() const;

	/**
	 * A object has a name
	 */
    void setName(const char* d);
    const char* getName() const;

	/**
	 * Abstract functions
	 */
	virtual void setType() = 0;
	virtual lbObject* clone() const = 0;

	

protected:

    char *name;
	ObjectTyp OTyp;
};
/*...e*/

/*...sclass DLLEXPORT lbString:0:*/
class DLLEXPORT lbString : public lbObject {
public:
	lbString();
	virtual ~lbString();
	
	virtual void setType();
	virtual lbObject* clone() const;

	void setData(char* p);
	char* getData() const;
	
private:
	char* stringdata;
};
/*...e*/

/*...sclass DLLEXPORT lbStringList:0:*/
class DLLEXPORT lbStringList : public lbObject {
public:
        lbStringList();
        virtual ~lbStringList();

        virtual void setType();
        virtual lbObject* clone() const;

	void insert(lbString &s);
	int remove(const lbString &s);
	int exists(const lbString &s);
	
	int hasMoreElements();
	lbString* nextElement();
private:
	lbComponentDictionary* list;
	int count;
};
/*...e*/
#endif //LB_OBJECT
