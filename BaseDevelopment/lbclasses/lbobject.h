


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.10 $
 * $Name:  $
 * $Id: lbobject.h,v 1.10 2001/07/11 16:04:35 lolli Exp $
 * $Log: lbobject.h,v $
 * Revision 1.10  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.9  2001/06/21 06:35:15  lolli
 * Added lbInteger and lbLong
 *
 * Revision 1.8  2001/03/04 18:30:43  lolli
 * Compiles now with interface support
 *
 * Revision 1.7  2001/02/06 20:38:18  lolli
 * Commit for backup the data
 *
 * Revision 1.6  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.5  2000/08/01 05:54:50  lolli
 * Currently runs with new interface
 *
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

/*...sbla:0:*/
#ifdef bla
#undef DLLEXPORT
#ifdef LB_LOADTIME_LINK
/*...sDLLEXPORT:0:*/

#ifdef LB_CLASSES_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_CLASSES_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/
#endif
#ifdef LB_RUNTIME_LINK
#define DLLEXPORT
#endif
#endif
/*...e*/

#include <stdio.h>
#include <lbInterfaces.h>


/*...sclass lbObject:0:*/
class lbObject : public lb_I_Object {
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


    DECLARE_LB_UNKNOWN()
    DECLARE_LB_OBJECT()

	/**
	 * The type of an object
	 */

    ObjectTyp getType() const;

	/**
	 * A object has a name
	 */
    void setName(const char* d);
    const char* getName() const;

	/**
	 * Abstract functions
	 */
//	virtual void setType() = 0;
//	virtual lb_I_Unknown* clone() const = 0;

	

protected:

  //  char *name;
//	ObjectTyp OTyp;
};
/*...e*/


/*...sclass lbString:0:*/
class lbString : public lb_I_String
{
public:
	lbString();
	virtual ~lbString();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL setData(char* p);
	virtual char* LB_STDCALL getData() const;



	// Must be implemented
	virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const;
	virtual int LB_STDCALL greater(const lb_I_KeyBase* _key) const;

	virtual char* LB_STDCALL getKeyType();

	virtual char* LB_STDCALL charrep();
private:

	char keyType[10];
	char* key;    
	char* stringdata;
};
/*...e*/
/*...sclass lbInteger:0:*/
class lbInteger : public lb_I_Integer
{
public:
	lbInteger();
	virtual ~lbInteger();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL setData(int p);
	virtual int LB_STDCALL getData() const;
	
    // Must be implemented
    virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const;
    virtual int LB_STDCALL greater(const lb_I_KeyBase* _key) const;

    virtual char* LB_STDCALL getKeyType();

    virtual char* LB_STDCALL charrep();
private:

    char keyType[10];
    int key;
    int integerdata;
};
/*...e*/
/*...sclass lbLong:0:*/
class lbLong : public lb_I_Long
{
public:
	lbLong();
	virtual ~lbLong();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL setData(long p);
	virtual long LB_STDCALL getData() const;
	
    // Must be implemented
    virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const;
    virtual int LB_STDCALL greater(const lb_I_KeyBase* _key) const;

    virtual char* LB_STDCALL getKeyType();

    virtual char* LB_STDCALL charrep();
private:

    char keyType[10];
    unsigned long key;
	long longdata;
};
/*...e*/
#ifdef bla
/*...sclass lbStringList:0:*/
class lbStringList : public lbObject {
public:
        lbStringList();
        virtual ~lbStringList();

        virtual void setType();
        virtual lb_I_Unknown* clone() const;

	void insert(lb_I_String* s);
	int remove(const lb_I_String* s);
	int exists(const lb_I_String* s);
	
	int hasMoreElements();
	lb_I_String* nextElement();
private:
	lb_I_Container* list;
	int count;
};
/*...e*/
#endif
/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_FUNCTOR(instanceOfInteger)
DECLARE_FUNCTOR(instanceOfString)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/


/*...sbla:0:*/
#ifdef bla
/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

lbErrCodes DLLEXPORT __cdecl queryInterface(lb_I_Unknown*& inst, const char* _name);
lbErrCodes DLLEXPORT __cdecl releaseInstance(lb_I_Unknown * inst);

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/
#endif
/*...e*/

#endif //LB_OBJECT
