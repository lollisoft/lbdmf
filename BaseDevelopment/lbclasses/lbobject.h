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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/

/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.44 $
 * $Name:  $
 * $Id: lbobject.h,v 1.44 2008/11/23 09:13:54 lollisoft Exp $
 * $Log: lbobject.h,v $
 * Revision 1.44  2008/11/23 09:13:54  lollisoft
 * If there would be created a big string in small steps, this is an attempt to
 * reduce the overhead of calling strlen and malloc each time by using a
 * bigger allocation size.
 *
 * Revision 1.43  2008/02/12 21:36:27  lollisoft
 * Added code that allows to store parameter sets into the meta application file.
 *
 * Revision 1.42  2008/01/17 19:28:31  lollisoft
 * Shortcircuit the translation when no database is available.
 *
 * Revision 1.41  2007/08/08 19:48:50  lollisoft
 * Changes to allow using BLOB data fields. Not completely finished.
 *
 * Revision 1.40  2007/07/09 12:07:12  lollisoft
 * Removed unnessesary strcpy usage.
 *
 * Revision 1.39  2007/06/14 20:49:36  lollisoft
 * Improvements in memory allocations.
 *
 * Revision 1.38  2007/05/14 19:19:15  lollisoft
 * Unfinished changes. Go to Linux.
 *
 * Revision 1.37  2007/05/12 17:46:51  lollisoft
 * Added equal operators to lb_I_String implementation.
 *
 * Revision 1.36  2007/02/03 11:04:36  lollisoft
 * Implemented directory location property handler. This is used in lbMetaApplication.
 *
 * Revision 1.35  2006/07/02 13:22:22  lollisoft
 * Added support for preloaded translation data model.
 *
 * Revision 1.34  2006/06/03 06:16:57  lollisoft
 * Changes against new Datamodel classes.
 * These are used instead spread SQL commands.
 *
 * Currently, the SQL commands are for fallback issues,
 * if there is no data in the config files.
 *
 * Later the planned fallback SQL commands are replaced by
 * a controlled visitor operation.
 *
 * Work is in process.
 *
 * Revision 1.33  2006/02/21 19:35:51  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.32  2006/02/17 23:57:16  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.31  2006/01/30 15:54:15  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.30  2005/12/30 11:20:03  lollisoft
 * New function (toLower).
 *
 * Revision 1.29  2005/12/09 15:57:58  lollisoft
 * Things work more properly under Mac OS X.
 *
 * Added stristr member function in lb_I_String.
 * Added setWhereClause/addWhereClause in lb_I_Query.
 *
 * All that needed to fix a bug in master / detail forms on
 * SQL queries with order by clauses.
 *
 * Revision 1.28  2005/12/02 00:28:43  lollisoft
 * Deleting a row works for some tests. Deleting data in join queries is not tested
 * and would propably not work. This is at least due to lack of creating a delete
 * statement per related table.
 *
 * Now this deleting also includes the ability to reopen the query as needed.
 * Form code is adopted to the case if there are no peek aheads are done
 * while fetching new data.
 *
 * Code cleanup would be done later.
 *
 * Revision 1.27  2005/11/06 19:25:33  lollisoft
 * All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
 *
 * Revision 1.26  2005/05/14 18:13:50  lollisoft
 * Added operators += and = to the string interface.
 *
 * Revision 1.25  2005/04/19 19:17:25  lollisoft
 * Bugfix
 *
 * Revision 1.24  2005/04/18 19:03:08  lollisoft
 * Added trim.
 *
 * Revision 1.23  2005/03/31 09:02:44  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.22  2005/03/19 16:39:25  lollisoft
 * Implemented i18n.
 *
 * Revision 1.21  2005/01/05 13:41:36  lollisoft
 * New dynamic application implementation works
 *
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

/*...sclass lbLocale:0:*/
class lbLocale : public lb_I_Locale
{
public:
        lbLocale();
        virtual ~lbLocale();

        DECLARE_LB_UNKNOWN()

        void LB_STDCALL setLanguage(char const * lang);

		void LB_STDCALL translate(char ** text, char const * to_translate);
		void LB_STDCALL setTranslationData(lb_I_Unknown* uk);

        UAP(lb_I_Translations, translations)
        char* _lang;
		bool  dbAvailable;
};
/*...e*/


/*...sclass lbParameter:0:*/
class lbParameter : public lb_I_Parameter {
public:
	lbParameter() {
		cloning = true;
		ref = STARTREF;
	}
	virtual ~lbParameter() {}

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL setUAPString(lb_I_String*& parameter, lb_I_String*& p);
	virtual lbErrCodes LB_STDCALL getUAPString(lb_I_String*& parameter, lb_I_String*& p);

	virtual void LB_STDCALL setUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p);
	virtual lbErrCodes LB_STDCALL getUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p);
	
	virtual void LB_STDCALL setUAPFileLocation(lb_I_String*& parameter, lb_I_FileLocation*& p);
	virtual lbErrCodes LB_STDCALL getUAPFileLocation(lb_I_String*& parameter, lb_I_FileLocation*& p);
	
	virtual void LB_STDCALL setUAPDirLocation(lb_I_String*& parameter, lb_I_DirLocation*& p);
	virtual lbErrCodes LB_STDCALL getUAPDirLocation(lb_I_String*& parameter, lb_I_DirLocation*& p);
	
	virtual void LB_STDCALL setUAPBoolean(lb_I_String*& parameter, lb_I_Boolean*& p);
	virtual lbErrCodes LB_STDCALL getUAPBoolean(lb_I_String*& parameter, lb_I_Boolean*& p);
	
	virtual void LB_STDCALL setUAPParameter(lb_I_String*& parameter, lb_I_Parameter*& p);
	virtual lbErrCodes LB_STDCALL getUAPParameter(lb_I_String*& parameter, lb_I_Parameter*& p);
	
	virtual void LB_STDCALL setUAPLong(lb_I_String*& parameter, lb_I_Long*& p);
	virtual lbErrCodes LB_STDCALL getUAPLong(lb_I_String*& parameter, lb_I_Long*& p);
	
	virtual void LB_STDCALL setUAPContainer(lb_I_String*& parameter, lb_I_Container*& p);
	virtual lbErrCodes LB_STDCALL getUAPContainer(lb_I_String*& parameter, lb_I_Container*& p);
	
	virtual int LB_STDCALL Count();
	virtual lb_I_Container* LB_STDCALL getParameterList();

	void LB_STDCALL setCloning(bool doClone=true);
	
	void LB_STDCALL delParameter(lb_I_String*& parameter);
protected:
	bool cloning;
	UAP(lb_I_Container, parameters)
};
/*...e*/
/*...sclass lbReference:0:*/
#ifndef _MSC_VER
class lbReference : public lb_I_Reference {
public:
	lbReference() { _r = NULL; }
	virtual ~lbReference() {}

	DECLARE_LB_UNKNOWN()
	
	virtual lbErrCodes LB_STDCALL set(lb_I_Unknown* r);
	virtual lbErrCodes LB_STDCALL get(lb_I_Unknown*& r);
	
protected:
	UAP(lb_I_Unknown, _r)
};
#endif
/*...e*/
/*...sclass lbString:0:*/
class lbString : public lb_I_String
{
public:
	lbString();
	virtual ~lbString();

	DECLARE_LB_UNKNOWN()

public:	

	char* LB_STDCALL stristr(const char *String, const char *Pattern);

	void LB_STDCALL trim();
	void LB_STDCALL toLower();
	void LB_STDCALL setData(char const * p);
	char* LB_STDCALL getData() const;
	
	lb_I_String& LB_STDCALL operator += (const char* toAppend);
	lb_I_String& LB_STDCALL operator = (const char* toAppend);

	lb_I_String& LB_STDCALL operator += (const lb_I_String* toAppend);
	lb_I_String& LB_STDCALL operator = (const lb_I_String* toAppend);

	int LB_STDCALL operator == (const char* toCompare) const;
	int LB_STDCALL operator == (const lb_I_String* toCompare) const;
	
	lb_I_String& LB_STDCALL replace(const char* toReplace, const char* with);
 
	DECLARE_LB_KEYBASE()

private:

	char keyType[10];
	char* stringdata;
	/// \brief Size of the buffer, not the length of the string.
	long buffersize;
	/// \brief The current length of the string. 
	long stringsize;
	/// \brief Minimum allocation size.
	long allocationsize;
};
/*...e*/
/*...sclass lbFileLocation:0:*/
class lbFileLocation : public lb_I_FileLocation
{
public:
	lbFileLocation();
	virtual ~lbFileLocation();

	DECLARE_LB_UNKNOWN()
	
	DECLARE_LB_KEYBASE()
	
	virtual void LB_STDCALL setData(char* path);
	virtual char* LB_STDCALL getData() const;
	
private:

    char keyType[10];
    char* _path;
};
/*...e*/
/*...sclass lbDirLocation:0:*/
class lbDirLocation : public lb_I_DirLocation
{
public:
	lbDirLocation();
	virtual ~lbDirLocation();

	DECLARE_LB_UNKNOWN()
	
	DECLARE_LB_KEYBASE()
	
	virtual void LB_STDCALL setData(char* path);
	virtual char* LB_STDCALL getData() const;
	
private:

    char keyType[10];
    char* _path;
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
    char* key;
    int integerdata;
};
/*...e*/
/*...sclass lbBoolean:0:*/
class lbBoolean : public lb_I_Boolean
{
public:
	lbBoolean();
	virtual ~lbBoolean();

	DECLARE_LB_UNKNOWN()
	
	DECLARE_LB_KEYBASE()
	
	virtual void LB_STDCALL setData(bool p);
	virtual bool LB_STDCALL getData() const;
	
private:

    char keyType[10];
    char* key;
    bool integerdata;
};
/*...e*/
class lbBinaryData : public lb_I_BinaryData
{
public:
	lbBinaryData();
	virtual ~lbBinaryData();

	DECLARE_LB_UNKNOWN()
	
	lbErrCodes LB_STDCALL append(void* value, long len);
	lbErrCodes LB_STDCALL setData(void* value, long len);
	void* LB_STDCALL getData() const;
	long LB_STDCALL getSize() const;

private:	
	void* blob;
	long size;
};
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
    char* key;
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
DECLARE_FUNCTOR(instanceOfBinaryData)
DECLARE_FUNCTOR(instanceOfFileLocation)
DECLARE_FUNCTOR(instanceOfDirLocation)
DECLARE_FUNCTOR(instanceOfLong)
DECLARE_FUNCTOR(instanceOfBoolean)
DECLARE_FUNCTOR(instanceOfString)
DECLARE_FUNCTOR(instanceOfReference)
DECLARE_FUNCTOR(instanceOfLocale)

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
