/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Rosmarinstr. 3
            
            40235 D�sseldorf (germany)
*/
/*...e*/

/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.20 $
 * $Name:  $
 * $Id: lbobject.h,v 1.20 2004/07/16 20:21:40 lollisoft Exp $
 * $Log: lbobject.h,v $
 * Revision 1.20  2004/07/16 20:21:40  lollisoft
 * Changed parameter from non const to const
 *
 * Revision 1.19  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.18  2003/08/22 17:35:09  lollisoft
 * Implemented UAP integer for parameter values
 *
 * Revision 1.17  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.16  2003/07/17 19:42:31  lollisoft
 * removed some log messages
 *
 * Revision 1.15  2003/07/10 21:14:35  lollisoft
 * Implemented parameter class
 *
 * Revision 1.14  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.13  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.12  2002/02/25 06:14:43  lolli
 * Much changes
 * Program seems to run, but performance is very slow
 *
 * Revision 1.11  2001/08/18 07:34:48  lolli
 * Current version runs again. Module management is not ready.
 *
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

#ifdef bla
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
#endif

/*...sclass lbParameter:0:*/
class lbParameter : public lb_I_Parameter {
public:
	lbParameter() {}
	virtual ~lbParameter() {}

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL setUAPString(lb_I_String*& parameter, lb_I_String*& p);
	virtual lbErrCodes LB_STDCALL getUAPString(lb_I_String*& parameter, lb_I_String*& p);

	virtual void LB_STDCALL setUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p);
	virtual lbErrCodes LB_STDCALL getUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p);
protected:

	UAP(lb_I_Container, parameters, __FILE__, __LINE__)
};
/*...e*/
/*...sclass lbReference:0:*/
class lbReference : public lb_I_Reference {
public:
	lbReference() { _r = NULL; }
	virtual ~lbReference() {}

	DECLARE_LB_UNKNOWN()
	
	virtual lbErrCodes LB_STDCALL set(lb_I_Unknown* r);
	virtual lbErrCodes LB_STDCALL get(lb_I_Unknown*& r);
	
protected:
	UAP(lb_I_Unknown, _r, __FILE__, __LINE__)
};
/*...e*/
/*...sclass lbString:0:*/
class lbString : public lb_I_String
{
public:
	lbString();
	virtual ~lbString();

	DECLARE_LB_UNKNOWN()

public:	
	virtual void LB_STDCALL setData(char const * p);
	virtual char* LB_STDCALL getData() const;

	DECLARE_LB_KEYBASE()

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
	
	DECLARE_LB_KEYBASE()
	
	virtual void LB_STDCALL setData(int p);
	virtual int LB_STDCALL getData() const;
	
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

	DECLARE_LB_KEYBASE()
	
	virtual void LB_STDCALL setData(long p);
	virtual long LB_STDCALL getData() const;
	
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
DECLARE_FUNCTOR(instanceOfReference)

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
