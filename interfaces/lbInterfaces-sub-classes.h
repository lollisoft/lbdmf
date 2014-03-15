/*...sLicense:0:*/
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
            Ginsterweg 4
            
            65760 Eschborn (germany)
*/
/*...e*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.106.2.4 $
 * $Name:  $
 * $Id: lbInterfaces-sub-classes.h,v 1.106.2.4 2014/03/15 06:30:32 lollisoft Exp $
 *
 * $Log: lbInterfaces-sub-classes.h,v $
 * Revision 1.106.2.4  2014/03/15 06:30:32  lollisoft
 * Some new features.
 *
 * Revision 1.106.2.3  2013/09/16 09:23:08  lollisoft
 * Changed implementation of makefile bootstrapping for Mac OS X. Added relevant code for it and other changes.
 *
 * Revision 1.106.2.2  2012/08/31 11:25:54  lollisoft
 * Changes to replace UAP with template based smart pointer.
 *
 * Revision 1.106.2.1  2012/05/12 21:16:25  lollisoft
 * Added documentation to string interface.
 *
 * Revision 1.106  2011/10/15 16:33:26  lollisoft
 * Removed some unused code and no more required code. Current version does not compile at all.
 *
 * Revision 1.105  2011/10/15 13:13:37  lollisoft
 * Decided to make a hash cut and removed stuff that everywhere was the cause for crashes on Mac.
 * Currently the code crashes on windows, but lets see how it is working on Mac.
 *
 * Revision 1.104  2011/09/25 11:47:02  lollisoft
 * There are still random crashes, but with a new trace function to try log the crash at a null pointer in a string, the crashes again get more rare. Probably still need more cppcheck runs.
 *
 * Revision 1.103  2011/09/25 09:30:14  lollisoft
 * Many bugfixes like missing variable initialization. Used CppCheck for this to get rid of the random crashes.
 * Only lbHook, lbModule, lbclasses and the Basetypes regression test (including headers and interfaces) are
 * fixed. Other modules will follow.
 *
 * Revision 1.102  2011/09/21 06:44:18  lollisoft
 * Changed some log messages to become error log messages.
 *
 * Revision 1.101  2011/07/10 06:13:36  lollisoft
 * Added stroring database query objects into the parameter container. Not yet tested.
 *
 * Revision 1.100  2011/06/18 17:29:55  lollisoft
 * Changed all char* to const char* where a corresponding warning was generated.
 *
 * Revision 1.99  2011/04/21 11:49:26  lollisoft
 * Many changes regarding UML activity stuff. But the placeholder replacement code is not yet stable and causes a out of memory error due to recursive placeholder replacements.
 *
 * Revision 1.98  2011/04/02 10:44:17  lollisoft
 * Now the UML based activities are reworked and they work while testing it against postbooks database.
 *
 * Revision 1.97  2011/02/27 10:30:36  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.96  2011/02/20 09:29:53  lollisoft
 * Made skip list log messages verbose only.
 *
 * Revision 1.95  2010/05/17 05:41:46  lollisoft
 * More method or constructor reordering.
 *
 * Revision 1.94  2010/04/29 06:56:05  lollisoft
 * Removed ctor and dtor.
 *
 * Revision 1.93  2010/04/25 21:37:10  lollisoft
 * Successfully ported lbHook to MINGW compiler. There were only two issues
 * I have identified: The enum problem as reported from Michal Necasek having
 * different sizes and the interface ordering to be equal to implementing class
 * declaration. But this only belongs to my UnitTest code yet.
 *
 * Aim of this is the ability to mix in MINGW modules for features Open Watcom
 * didn't support yet and let me do this with minimal effort.
 *
 * Revision 1.92  2010/04/03 00:15:56  lollisoft
 * Changes to properly mix up compilers (OW and MinGW). Tested in UnitTests with is actually testing some functions of the lbString class.
 *
 * Revision 1.91  2010/03/28 19:21:02  lollisoft
 * Added a function to find substring from right.
 *
 * Revision 1.90  2010/03/20 22:56:30  lollisoft
 * Corrected folding.
 *
 * Revision 1.89  2010/02/24 17:07:12  lollisoft
 * Partly reactivated socket and threading classes. But functionality is not ready to use.
 *
 * Revision 1.88  2010/01/15 18:48:48  lollisoft
 * Interceptor logic works as long as one database form is
 * not closed when another is opened and then the
 * interceptor walks through the list of intercepted event
 * handlers.
 *
 * This is due to the fact that wxWidgets deletes the instance, but the container with a reference is not notified to remove the instance (without deletion).
 *
 * This is tricky.
 *
 * Revision 1.87  2010/01/12 19:45:41  lollisoft
 * Mostly completed plugin based interceptor functionality for events.
 *
 * Revision 1.86  2009/11/12 07:55:33  lollisoft
 * Corrected the core macros and functions to reduce deprecated const string warning.
 *
 * Revision 1.85  2009/09/09 17:45:40  uid108140
 * Added substitutePlaceholder function. Some more docs.
 *
 * Revision 1.84  2009/08/07 21:23:27  lollisoft
 * Added a parameter to enable case insensitive replacements.
 *
 * Revision 1.83  2009/06/17 20:37:18  lollisoft
 * Implemented non linear actions. These are 'flow' controlled action steps that could be modelled in UML activity diagrams. Export is not yet implemented but import from UML works.
 *
 * Revision 1.82  2009/06/10 11:43:02  lollisoft
 * Added functions to enable position in the container to enable 'jumps'.
 *
 * Revision 1.81  2008/10/03 14:32:27  lollisoft
 * Added a functionality to refresh the database forms.
 * This may be usefull when a database lock occures.
 *
 * Revision 1.80  2008/07/25 16:43:50  lollisoft
 * Fixed application crash at exit.
 *
 * Revision 1.79  2008/07/24 20:53:36  lollisoft
 * These changes let the application run on Mac OS X 10.5 (Leopard). But crashes at exit, propably due to changed cleanup logic or changed default variable values (not correctly initialized).
 *
 * Revision 1.78  2008/02/12 21:36:27  lollisoft
 * Added code that allows to store parameter sets into the meta application file.
 *
 * Revision 1.77  2007/08/08 19:48:50  lollisoft
 * Changes to allow using BLOB data fields. Not completely finished.
 *
 * Revision 1.76  2007/05/14 19:19:17  lollisoft
 * Unfinished changes. Go to Linux.
 *
 * Revision 1.75  2007/05/12 17:44:02  lollisoft
 * Added equal operators to lb_I_String interface.
 *
 * Revision 1.74  2007/04/22 13:43:37  lollisoft
 * Many changes relating threads and client server code.
 *
 * Revision 1.73  2007/02/03 11:04:36  lollisoft
 * Implemented directory location property handler. This is used in lbMetaApplication.
 *
 * Revision 1.72  2007/01/15 23:37:30  lollisoft
 * Changed code that valgrind mentioned as using uninitialized variable in boolean expression
 *
 * Revision 1.71  2006/10/22 18:34:36  lollisoft
 * Many memory leaks resolved, but they were caused by small errors :-(
 * This is also a sync.
 *
 * Revision 1.70  2006/07/17 17:40:41  lollisoft
 * Changes dueto bugfix in plugin getModuleInstance(). Repeadable iterator problem.
 * Not correctly finished the iteration, thus plugins in the same DLL wouldn't
 * be found any more after first query.
 *
 * Code works well with improved trmem library, but there is still a crash in
 * database classes (pgODBC library).
 *
 * Revision 1.69  2006/07/02 13:06:31  lollisoft
 * Added feature to not clone objects when inserting into a container.
 *
 * Revision 1.68  2006/06/03 06:16:58  lollisoft
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
 * Revision 1.67  2006/02/21 19:35:52  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.66  2006/02/18 19:12:18  lollisoft
 * Not so much log messages.
 *
 * Revision 1.65  2006/02/17 23:57:17  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.64  2006/01/30 15:54:15  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.63  2006/01/21 23:50:11  lollisoft
 * Added new member to ask the user for a file. And some
 * more initial member documentation.
 *
 * Revision 1.62  2005/12/30 11:20:44  lollisoft
 * New function (toLower).
 *
 * Revision 1.61  2005/12/13 23:42:14  lollisoft
 * Code may work properly, but doesn't compile well. Compiler bug ?
 * I know about a macro bug when missing one backslash, but I haven't
 * created one in my last changes - I think.
 *
 * Revision 1.60  2005/12/09 15:57:59  lollisoft
 * Things work more properly under Mac OS X.
 *
 * Added stristr member function in lb_I_String.
 * Added setWhereClause/addWhereClause in lb_I_Query.
 *
 * All that needed to fix a bug in master / detail forms on
 * SQL queries with order by clauses.
 *
 * Revision 1.59  2005/11/20 17:26:14  lollisoft
 * Local TRMem count.
 *
 * Revision 1.58  2005/11/16 20:55:33  lollisoft
 * Less log messages and added preload member in lbModule.
 *
 * Revision 1.57  2005/11/11 22:51:30  lollisoft
 * Memory leaks removed. There are currently only 4 chunks leaky.
 * These may be false positives, because one of them is an allocated
 * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
 * wxMenuBar gets an owner (see wxWidgets documentation).
 *
 * Revision 1.56  2005/10/31 19:37:55  lollisoft
 * This version compiles and ends without a crash at exit. I have added a simple
 * string class to store places of queryInterface calls and setModuleManager calls.
 * This may change the layout to let the application not crash at exit.
 *
 * Revision 1.55  2005/08/21 23:16:47  lollisoft
 * Minor change to show the class name of container element, that would not
 * deleted.
 *
 * Revision 1.54  2005/06/02 21:13:12  lollisoft
 * Small problem with backslash and space.
 *
 * Revision 1.53  2005/06/01 11:07:03  lollisoft
 * Added detach function.
 *
 * Revision 1.52  2005/05/17 22:59:19  lollisoft
 * Bugfix in reference counting.
 *
 * Storing windows in a selfdeleting (UAP) container would
 * crash. This has been overcome since the bugfix for the
 * containers self has been taken.
 *
 * The wxWidgets controls or windows are not reference
 * counted, or have its own one. So they should not be stored
 * simply in a container of my framework.
 *
 * Special reference increment is done for the specific dialogs.
 *
 * Revision 1.51  2005/05/14 18:13:14  lollisoft
 * Added operators += and = to the string interface.
 *
 * Revision 1.50  2005/05/11 13:19:40  lollisoft
 * Bugfix for reference count error and changed back any _CL_LOG messages to be _CL_VERBOSE only
 *
 * Revision 1.49  2005/05/01 21:16:16  lollisoft
 * lb_I_Element implementation macro changed due to memory leak tests.
 * My old reference counting system is no more used.
 *
 * Revision 1.48  2005/04/18 18:55:49  lollisoft
 * Added trim
 *
 * Revision 1.47  2005/03/31 09:08:35  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.46  2005/03/19 16:50:00  lollisoft
 * Changed i18n interface.
 *
 * Revision 1.45  2005/03/14 18:59:04  lollisoft
 * Various changes and additions to make plugins also work with database forms
 *
 * Revision 1.44  2005/02/13 19:01:50  lollisoft
 * Skiplist element does not check for data NULL pointer.
 *
 * Revision 1.43  2005/01/05 13:44:39  lollisoft
 * New dynamic application code works
 *
 * Revision 1.42  2004/12/14 16:08:05  lollisoft
 * An attempt for i18n.
 *
 * Revision 1.41  2004/08/16 05:09:16  lollisoft
 * New locale interface
 *
 * Revision 1.40  2004/08/01 21:34:03  lollisoft
 * More documentation
 *
 * Revision 1.39  2004/07/26 22:20:35  lollisoft
 * Some problems with Power++ solved ?
 *
 * Revision 1.38  2004/07/16 20:17:53  lollisoft
 * lb_I_String changed non const to const parameter
 *
 * Revision 1.37  2004/06/16 22:15:33  lollisoft
 * More interface code for database forms
 *
 * Revision 1.36  2004/06/09 07:06:25  lollisoft
 * Did I need protected constructor and destructor in pure abstract classes ?
 *
 * Revision 1.35  2004/01/24 16:48:20  lollisoft
 * Added access to makeInstance (lbMetaApplication)
 *
 * Revision 1.34  2003/12/13 10:56:26  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.33  2003/08/22 17:42:35  lollisoft
 * Added UAP integer parameter
 *
 * Revision 1.32  2003/07/10 21:17:18  lollisoft
 * Added parameter interface
 *
 * Revision 1.31  2003/01/15 22:42:38  lothar
 * Compiles with MSC
 *
 * Revision 1.30  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.29  2002/10/28 18:38:07  lothar
 * Current version works
 *
 * Revision 1.28  2002/10/04 16:53:12  lothar
 * Replaced old LOG macro with the new
 * _CL_LOG << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.27  2002/10/01 19:23:12  lothar
 * Broken
 *
 * Revision 1.26  2002/08/21 18:53:07  lothar
 * New direct container access implementation
 *
 * Revision 1.25  2002/07/23 17:54:52  lothar
 * Current version runs
 *
 * Revision 1.24  2002/06/18 17:47:52  lothar
 * More logging information
 *
 * Revision 1.23  2002/05/30 17:53:47  lothar
 * Current development seems to run
 *
 * Revision 1.22  2002/05/01 14:17:11  lothar
 * This version does not compile
 *
 * Revision 1.21  2002/04/15 18:25:16  lothar
 * Huge changes - works good
 *
 * Revision 1.20  2002/02/27 21:00:35  lothar
 * Unused code
 *
 * Revision 1.19  2002/02/25 06:18:31  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 * Revision 1.18  2001/12/15 18:19:39  lothar
 * ZThread not on windows
 *
 * Revision 1.17  2001/12/12 17:27:54  lothar
 * Hehe - runs under linux
 *
 * Revision 1.16  2001/10/06 11:20:54  lothar
 * Compiles module lbHook under linux now
 *
 * Revision 1.15  2001/10/04 19:29:15  lothar
 * Current version seems to work good (without big memory holes)
 *
 * Revision 1.14  2001/08/18 07:38:55  lothar
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.13  2001/07/18 05:52:57  lothar
 * Seems to work now (lbDOMNode::parent - refcount must be corrected)
 *
 * Revision 1.12  2001/07/11 16:03:13  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.11  2001/06/21 06:41:56  lothar
 * Changed lb_I_String base
 *
 * Revision 1.10  2001/05/08 20:55:12  lothar
 * Change of lb_I_KeyBase interface
 *
 * Revision 1.9  2001/05/01 15:51:49  lothar
 * First instance could be loaded over the new module management
 *
 * Revision 1.8  2001/04/27 18:57:32  lothar
 * Commit for removing some getch()'s
 *
 * Revision 1.7  2001/04/13 07:39:27  lothar
 * Commit for backup
 *
 **************************************************************/
/*...e*/
/*...sDocumentation for file:0:*/
/**
 *  \file lbInterfaces-sub-classes.h
 *  \brief Some basic interfaces.
 *
 *  This file contains interfaces like lb_I_String, lb_I_Parameter and so on.
 */
/*...e*/

#ifndef __LB_INTERFACES_SUB_CLASSES__
#define __LB_INTERFACES_SUB_CLASSES__

/*...sclass lb_I_KeyBase:0:*/
/**
 * \brief Interface for any class, that should be comparable.
 *
 * A key could be a string, an integer, or anything else that
 * is used for lookup stuff.
 */
class lb_I_KeyBase : public lb_I_Unknown {
public:

	virtual int LB_STDCALL operator == (const lb_I_KeyBase* _key) const = 0;
	virtual int LB_STDCALL operator > (const lb_I_KeyBase* _key) const = 0;
	virtual int LB_STDCALL operator < (const lb_I_KeyBase* _key) const = 0;

	virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const = 0;
	virtual int LB_STDCALL greater(const lb_I_KeyBase* _key) const = 0;
	virtual int LB_STDCALL lessthan(const lb_I_KeyBase* _key) const = 0;

	/**
	 * Returns the type of this key.
	 */
	virtual char const* LB_STDCALL getKeyType() const = 0;

	/**
	 * Char representation of the key.
	 */
	virtual char* LB_STDCALL charrep() const = 0;

// Mixing MINGW and Open Watcom code (MINGW Executable - unittest, Opwn Watcom SUT - lbclasses - lbString) will fail.
// This is due to implementation in header, I think.

//#define USE_PRIVATE_INTERFACE_CTOR_DTOR
#ifdef USE_PRIVATE_INTERFACE_CTOR_DTOR
protected:
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        lb_I_KeyBase() {}
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        virtual ~lb_I_KeyBase() {}
#endif
};


#define DECLARE_LB_KEYBASE() \
public: \
    virtual int LB_STDCALL operator == (const lb_I_KeyBase* _key) const { \
    	if (strcmp(this->getKeyType(), _key->getKeyType()) != 0) return 0; \
        return this->equals(_key); \
    } \
    virtual int LB_STDCALL operator > (const lb_I_KeyBase* _key) const { \
    	if (strcmp(this->getKeyType(), _key->getKeyType()) != 0) return 0; \
        return this->greater(_key); \
    } \
    virtual int LB_STDCALL operator < (const lb_I_KeyBase* _key) const { \
    	if (strcmp(this->getKeyType(), _key->getKeyType()) != 0) return 0; \
        return this->lessthan(_key); \
    } \
    virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const; \
    virtual int LB_STDCALL greater(const lb_I_KeyBase* _key) const; \
    virtual int LB_STDCALL lessthan(const lb_I_KeyBase* _key) const; \
\
    virtual char const* LB_STDCALL getKeyType() const; \
\
    virtual char* LB_STDCALL charrep() const;
/*...e*/

/*...sSome comments:0:*/
/*
        Must have a type information of the key, because a string could not be compared
        with an integer (directly). For a key, it is simply one type of interface, that
        will be returned as their type information.
        
        Here, for keys, a key can be compared with another key of the same type. It is
        simple to implement the compare function, having the type of the object.
        
        Where to define the type information function ?
        
        I tent to use a type check in the lb_I_KeyBase interface. So it is not neccesary
        to implement a typecheck for each equals/greater function.
*/
/*...e*/
/*...sclass lb_I_Object:0:*/
/*...sdefinition of object types may cange:0:*/
    enum ObjectTyp { LB_OBJECT, 
                     LB_STRING,
                     LB_STRINGLIST,
                     LB_GUIOBJECT, 
                     LB_WXGUIOBJECT, 
                     LB_DATA_TRANSFER_OBJECT,
                     LB_CONNECTION,
                     LB_APPBUSCLIENT,
                     LB_APPCLIENT_DISPATCH_FN,
                     LB_APPSERVER_DISPATCH_PROTO,
                     LB_EVENT,
                     LB_DOM_NODE,
                     LB_DOM_ATTRIBUTE
    };
/*...e*/

/*...sclass lb_I_Object:0:*/
/**
 * \brief Olt base class now declared as interface.
 * \deprecated use lb_I_Unknown.
 */
class lb_I_Object {
protected:
    lb_I_Object() {}
    lb_I_Object(const lb_I_Object &o) {
                //setName(o.getName());
        }
    
    virtual ~lb_I_Object() {}

public:

    virtual ObjectTyp LB_STDCALL getType() const = 0;

    virtual void LB_STDCALL setName(const char* d) = 0;
    virtual const char* LB_STDCALL getName() const = 0;

    virtual void LB_STDCALL setType() = 0;
};
/*...e*/

/*...sDECLARE_LB_OBJECT\40\classname\41\:0:*/
#define DECLARE_LB_OBJECT(classname) \
    virtual ObjectTyp LB_STDCALL getType() const; \
\
    virtual void LB_STDCALL setName(const char* d); \
    virtual const char* LB_STDCALL getName() const; \
\
    virtual void LB_STDCALL setType(); \
    virtual lb_I_Unknown* LB_STDCALL clone() const; \
protected: \
    char* name; \
    ObjectTyp OTyp;
/*...e*/
/*...sIMPLEMENT_LB_OBJECT\40\classname\44\ classtype\41\:0:*/
#define IMPLEMENT_LB_OBJECT(classname, classtype)    \
void LB_STDCALL classname::setName(const char* d) { \
        if (name != NULL) delete name;    \
    name = strdup(d);                     \
}                                         \
\
const char* LB_STDCALL classname::getName() const { \
    return name;                          \
}                                         \
\
ObjectTyp LB_STDCALL classname::getType() const {   \
        if (OTyp == LB_OBJECT) {          \
                _CL_LOG << "Derived object has not been initialized correctly!" LOG_ \
        }                                 \
        return OTyp;                      \
}                                         \
void LB_STDCALL classname::setType() {              \
        OTyp = classtype;                 \
}                                         \

/*...e*/
/*...e*/

/*...sclass lb_I_Locale:0:*/
/**
 * An attempt for i18n.
 *
 * It should be implemented as a singleton functor to be sure have the right
 * language set once.
 */
class lb_I_Locale : public lb_I_Unknown {
public:
	
	/** 
	 * Set the desired language. English is assumed as default.
	 * The orginal texts should be stored in a default field, because
	 * there may be developers not aware of english.
	 */
	virtual void LB_STDCALL setLanguage(char const * lang) = 0;
	
	/**
	 * Translate the given text.
	 *
	 * The given text would be handled as the default text and therefore the
	 * key for searching.
	 */
	virtual void LB_STDCALL translate(char ** text, char const * to_translate) = 0;
	
	/** \brief Set the data model for translations.
	 *
	 * If this is given, locale uses that as memory based version instead of SQL calls per every translate call.
	 */
	virtual void LB_STDCALL setTranslationData(lb_I_Unknown* uk) = 0;
};
/*...e*/

/*...sclass lb_I_BinaryData:0:*/
class lb_I_BinaryData : public lb_I_Unknown {
public:
	/** \brief Append data chunk.
	 *
	 */
	virtual lbErrCodes LB_STDCALL append(void*, long) = 0;

	/** \brief Set binary data.
	 */
	virtual lbErrCodes LB_STDCALL setData(void*, long) = 0;

	/** \brief Get binary data.
	 */
	virtual void* LB_STDCALL getData() const = 0;

	/** \brief Get binary data.
	 */
	virtual long LB_STDCALL getSize() const = 0;
};
/*...e*/

// Keyable interfaces
/*...sclass lb_I_String:0:*/
/**
 * \brief A basic string class.
 *
 * This is a set of base interfaces that are compatible to the lb_I_Container interface.
 */
class lb_I_String : public lb_I_KeyBase {
public:
	/** \brief Trim trailing spaces.
	 *
	 * Removes the spaces in the string at the end (default).
	 */
	virtual void LB_STDCALL trim(bool fromright = true) = 0;

	/** \brief Set all characters to lower. 
	 *
	 */
	virtual void LB_STDCALL toLower() = 0;

	/** \brief Get case insensitive substr.
	 *
	 */
	virtual char* LB_STDCALL stristr(const char* String, const char* Pattern) = 0;

	virtual char* LB_STDCALL strristr(const char* String, const char* Pattern) = 0;

        /**
         * \brief Set the string data from char*
         * 
         * \param p Input char const * data .
         */
        virtual void LB_STDCALL setData(const char* p) = 0;
        
        /**
         * \brief Return char* representation.
         *
         * \return char* value.
         */
        virtual char* LB_STDCALL getData() const = 0;

	/** \brief Adds the given char* array.
	 *
	 */
	virtual lb_I_String& LB_STDCALL operator += (const char* toAppend) = 0;
	
	virtual lb_I_String& LB_STDCALL operator = (const char* toAppend) = 0;

	virtual lb_I_String& LB_STDCALL operator += (const lb_I_String* toAppend) = 0;
		
	virtual lb_I_String& LB_STDCALL operator = (const lb_I_String* toAppend) = 0;

	virtual int LB_STDCALL operator == (const char* toCompare) const = 0;

	virtual int LB_STDCALL operator == (const lb_I_String* toCompare) const = 0;

	/** \brief Replace a substring.
	 * This function changes the content of this instance.
	 */
	virtual lb_I_String& LB_STDCALL replace(const char* toReplace, const char* with, bool nocase = false) = 0;
	
	virtual lb_I_String* LB_STDCALL left(int until) = 0;
	virtual lb_I_String* LB_STDCALL right(int from) = 0;
	
	/** \brief Returns the position from 0 or -1 if not found.
	 */
	virtual int LB_STDCALL strpos(const char* with) = 0;
	
	/** \brief Returns the position from 0 or -1 if not found.
	 */
	virtual int LB_STDCALL rstrpos(const char* with) = 0;
	
	/** \brief Replace all occurences of placeholders with their values from params.
	 * This function changes the content of this instance on success.
	 */
	virtual lb_I_String& LB_STDCALL substitutePlaceholder(lb_I_Parameter* params) = 0;

	virtual lb_I_Container* LB_STDCALL split(const char split_char) = 0;

        /**
         * \brief Set data from other lb_I_String instance.
         *
         * This member is used in lb_I_Container implementation via clone.
         */
    virtual lbErrCodes LB_STDCALL setData( lb_I_Unknown * uk) = 0;
};
/*...e*/
/*...sclass lb_I_FileLocation:0:*/
/**
 * \brief A file location class.
 *
 * This is a set of base interfaces that are compatible to the lb_I_Container interface.
 * The file location class is used to store the location of a file to distinguish from a normal
 * string.
 */
class lb_I_FileLocation : public lb_I_KeyBase {
public:
		/** 
	 	 * \brief Set path as the file location.
		 *
		 * \param path string value to be set.
		 */        
        virtual void LB_STDCALL setData(const char* path) = 0;
        
        /**
         * \brief Get the path value.
         */
        virtual char* LB_STDCALL getData() const = 0;
	
        /**
         * \brief Set data from other lb_I_FileLocation instance.
         *
         * This member is used in lb_I_Container implementation via clone.
         */
		virtual lbErrCodes LB_STDCALL setData( lb_I_Unknown * uk) = 0;        
};
/*...e*/
/*...sclass lb_I_DirLocation:0:*/
/**
 * \brief A dir location class.
 *
 * This is a set of base interfaces that are compatible to the lb_I_Container interface.
 * The dir location class is used to store file path and to distinguish from a normal
 * string.
 *
 * It will be used in my lb_I_MetaApplication implementation to store a default directory
 * for icon files.
 */
class lb_I_DirLocation : public lb_I_KeyBase {
public:
		/** 
	 	 * \brief Set path as the file location.
		 *
		 * \param path string value to be set.
		 */        
        virtual void LB_STDCALL setData(const char* path) = 0;
        
        /**
         * \brief Get the path value.
         */
        virtual char* LB_STDCALL getData() const = 0;
	
        /**
         * \brief Set data from other lb_I_FileLocation instance.
         *
         * This member is used in lb_I_Container implementation via clone.
         */
		virtual lbErrCodes LB_STDCALL setData( lb_I_Unknown * uk) = 0;        
};
/*...e*/

/*...sclass lb_I_Integer:0:*/
/**
 * \brief A basic integer class.
 *
 * This is a set of base interfaces that are compatible to the lb_I_Container interface.
 */
class lb_I_Integer : public lb_I_KeyBase {
public:
	/** 
	 * \brief Set p as the int value.
	 *
	 * \param p Integer value to be set.
	 */        
        virtual void LB_STDCALL setData(int p) = 0;
        
        /**
         * \brief Get the integer value.
         */
        virtual int LB_STDCALL getData() const = 0;
	
        /**
         * \brief Set data from other lb_I_Integer instance.
         *
         * This member is used in lb_I_Container implementation via clone.
         */
	virtual lbErrCodes LB_STDCALL setData( lb_I_Unknown * uk) = 0;        
};
/*...e*/
/*...sclass lb_I_Boolean:0:*/
/**
 * \brief A basic boolean class.
 *
 * This is a set of base interfaces that are compatible to the lb_I_Container interface.
 */
class lb_I_Boolean : public lb_I_KeyBase {
protected:
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        lb_I_Boolean() {}
	/**
	 * \deprecated Pure abstract class has no ctor/dtor's
	 */
        virtual ~lb_I_Boolean() {}

public:
	/** 
	 * \brief Set p as the int value.
	 *
	 * \param p Boolean value to be set.
	 */        
        virtual void LB_STDCALL setData(bool p) = 0;
        
        /**
         * \brief Get the integer value.
         */
        virtual bool LB_STDCALL getData() const = 0;
	
        /**
         * \brief Set data from other lb_I_Boolean instance.
         *
         * This member is used in lb_I_Container implementation via clone.
         */
	virtual lbErrCodes LB_STDCALL setData( lb_I_Unknown * uk) = 0;        
};
/*...e*/
/*...sclass lb_I_Long:0:*/
/**
 * \brief A basic long class.
 *
 * This is a set of base interfaces that are compatible to the lb_I_Container interface.
 */
class lb_I_Long : public lb_I_KeyBase {
protected:
        lb_I_Long() {}
        virtual ~lb_I_Long() {}

public:
        
        virtual void LB_STDCALL setData(long p) = 0;
        virtual long LB_STDCALL getData() const = 0;
	virtual lbErrCodes LB_STDCALL setData( lb_I_Unknown * uk) = 0;        
};
/*...e*/

/*...sclass lb_I_Parameter:0:*/
/**
 * \brief A parameter interface. Set of parameter - value pairs.
 *
 * This interface is used in build up dynamic commands to be issued to
 * event handlers (lb_I_EventHandler, lb_I_EvHandler).
 */
class lb_I_Parameter : public lb_I_Unknown {
public:
#ifdef bla        
        /**
         * Integer parameter
         */
        virtual void LB_STDCALL setInt(const char* parameter, int p) = 0;
        virtual int LB_STDCALL getInt(const char* parameter) const = 0;
        
        /**
         * char* parameter
         */
        virtual void LB_STDCALL setChar(const char* parameter, int p) = 0;
        virtual lbErrCodes LB_STDCALL getChar(const char* parameter, char** buffer, int length) = 0;
        
        /**
         * Hopefully the better variant for char arrays.
         */
         
        virtual void LB_STDCALL setString(lb_I_String* parameter, lb_I_String* p) = 0;
        virtual lbErrCodes LB_STDCALL getString(lb_I_String* parameter, lb_I_String* p) = 0;
#endif        
        /**
         * \brief Set a String as a parameter.
         *
         * \param parameter This is the name of the parameter.
         * \param p         This is the value for the given name.
         */ 
        virtual void LB_STDCALL setUAPString(lb_I_String*& parameter, lb_I_String*& p) = 0;
        
        /**
         * \brief Get a String as a parameter.
         *
         * \param parameter This is the name of the parameter.
         * \param p         This is the value for the given name.
         *
         * Here is a sample how to implement an event handler for creating a menu entry,
         * wich in turn routes the event ID to the general OnDispatch member of a wxFrame:
         *
         * \code
		_LOG << "MyApp::lbEvHandler3 called" LOG_
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance().getPtr(), lb_I_EventManager, ev_getModuleInstance())
		UAP_REQUEST(getModuleInstance().getPtr(), lb_I_String, parameter)
		UAP_REQUEST(getModuleInstance().getPtr(), lb_I_String, menubar)
		UAP_REQUEST(getModuleInstance().getPtr(), lb_I_String, menuname)
		UAP_REQUEST(getModuleInstance().getPtr(), lb_I_String, handlername)
	
		UAP(lb_I_Parameter, param)

		QI(uk, lb_I_Parameter, param)

		parameter->setData("menubar");
		param->getUAPString(*&parameter, *&menubar);
	
		parameter->setData("menuname");
		param->getUAPString(*&parameter, *&menuname);
	
		parameter->setData("handlername");
		param->getUAPString(*&parameter, *&handlername);
	
		int EvNr = 0;
		ev_getModuleInstance()->resolveEvent(handlername->getData(), EvNr);

		wxMenuBar* mbar = frame_peer->getMenuBar();
		wxMenu* menu = mbar->GetMenu(mbar->FindMenu(wxString(menubar->getData())));

		menu->Append(EvNr, menuname->getData());

		((wxFrame*) frame_peer)->Connect( EvNr,  -1, wxEVT_COMMAND_MENU_SELECTED,
	          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
	          &lb_wxFrame::OnDispatch );
         * \endcode
         */ 
	virtual lbErrCodes LB_STDCALL getUAPString(lb_I_String*& parameter, lb_I_String*& p) = 0; 

	virtual void LB_STDCALL setUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p) = 0;
	
	virtual void LB_STDCALL setUAPDirLocation(lb_I_String*& parameter, lb_I_DirLocation*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPDirLocation(lb_I_String*& parameter, lb_I_DirLocation*& p) = 0;
	
	virtual void LB_STDCALL setUAPFileLocation(lb_I_String*& parameter, lb_I_FileLocation*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPFileLocation(lb_I_String*& parameter, lb_I_FileLocation*& p) = 0;
	
	virtual void LB_STDCALL setUAPBoolean(lb_I_String*& parameter, lb_I_Boolean*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPBoolean(lb_I_String*& parameter, lb_I_Boolean*& p) = 0;
	
	virtual void LB_STDCALL setUAPContainer(lb_I_String*& parameter, lb_I_Container*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPContainer(lb_I_String*& parameter, lb_I_Container*& p) = 0;

	virtual void LB_STDCALL setUAPParameter(lb_I_String*& parameter, lb_I_Parameter*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPParameter(lb_I_String*& parameter, lb_I_Parameter*& p) = 0;

	virtual void LB_STDCALL setUAPLong(lb_I_String*& parameter, lb_I_Long*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPLong(lb_I_String*& parameter, lb_I_Long*& p) = 0;
	
	virtual void LB_STDCALL setUAPQuery(lb_I_String*& parameter, lb_I_Query*& p) = 0;
	virtual lbErrCodes LB_STDCALL getUAPQuery(lb_I_String*& parameter, lb_I_Query*& p) = 0;
	
	/**
	 * /brief Returns the number of parameters
	 *
	 */
	virtual int LB_STDCALL Count() = 0;
	
	/** \brief Get the list of parameters as a container.
	 *
	 */
	virtual lb_I_Container* LB_STDCALL getParameterList() = 0;
	
	virtual	void LB_STDCALL setCloning(bool doClone=true) = 0;
	
	virtual void LB_STDCALL delParameter(lb_I_String*& parameter) = 0;

	virtual void LB_STDCALL copyFrom(lb_I_Parameter* source) = 0;
};
/*...e*/

/*...sclass lb_I_Element:0:*/
class lb_I_Element : public lb_I_Unknown {
protected:
        lb_I_Element() {}
        virtual ~lb_I_Element() {}

public:

        virtual lb_I_Element* LB_STDCALL getNext() const = 0;
        virtual void LB_STDCALL setNext(lb_I_Element *e) = 0;
        virtual lb_I_Unknown* LB_STDCALL getObject() const = 0;
        
        /**
         * Do a full compare. Data and key must be equal.
         */
        virtual int LB_STDCALL equals(const lb_I_Element* a) const = 0;
        /**
         * Do a key compare.
         */
        virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const = 0;
	virtual int LB_STDCALL lessthan(const lb_I_KeyBase* _key) const = 0;

	virtual void LB_STDCALL detachData() = 0;

        virtual lb_I_KeyBase* LB_STDCALL getKey() const = 0;

        int LB_STDCALL operator == (const lb_I_Element* a) const {
                return this->equals(a);
        }

        int LB_STDCALL operator == (const lb_I_KeyBase* _key) const {
                return this->equals(_key);
        }

        int LB_STDCALL operator < (const lb_I_KeyBase* _key) const {
        	return this->lessthan(_key);
        }
};

#define DECLARE_LB_ELEMENT(classname) \
classname(const lb_I_Unknown* o, const lb_I_KeyBase* _key, bool doClone, lb_I_Element *_next = NULL); \
lb_I_Element* LB_STDCALL getNext() const; \
void LB_STDCALL setNext(lb_I_Element *e); \
lb_I_Unknown* LB_STDCALL getObject() const; \
int LB_STDCALL equals(const lb_I_Element* a) const; \
int LB_STDCALL equals(const lb_I_KeyBase* _key) const; \
int LB_STDCALL lessthan(const lb_I_KeyBase* _key) const; \
void LB_STDCALL detachData(); \
lb_I_KeyBase* LB_STDCALL getKey() const; \
private: \
\
    lb_I_Unknown* data; \
    lb_I_Element* next; \
    lb_I_KeyBase* key;

#define IMPLEMENT_LB_ELEMENT(classname) \
\
void LB_STDCALL classname::detachData() { \
	data = NULL; \
} \
classname::classname(const lb_I_Unknown* o, const lb_I_KeyBase* _key, bool doClone, lb_I_Element *_next) { \
	data = NULL; \
    next = _next; \
    if (_next != NULL) { \
        _next->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__); \
    } \
    if (o == NULL) _CL_LOG << "Error! Can't clone a NULL pointer" << __FILE__ ":" << __LINE__ LOG_ \
    if (o != NULL) { \
		if (doClone) { \
			data = o->clone(__FILE__, __LINE__); \
			if (data->getRefCount() > 1) { \
				_CL_VERBOSE << "Warning: Refcount of data after cloning is more than 1 !!!" LOG_ \
			} \
		} else { \
			o->queryInterface("lb_I_Unknown", (void**) &data, __FILE__, __LINE__); \
		\
		} \
    } \
    lb_I_Unknown* uk_key = NULL; \
    key = (lb_I_KeyBase*) _key->clone(__FILE__, __LINE__); \
	_CL_VERBOSE << "Added an element with key value of " << key->charrep() LOG_ \
    if (key != NULL) { \
    	if (key->getRefCount() > 1) { \
    	        _CL_VERBOSE << "Warning: Refcount of key after cloning is more than 1 !!!" LOG_ \
        } \
    } \
    if (key == NULL) _CL_LOG << "Key cloning in constructor failed. May be a memory problem" LOG_ \
} \
\
classname::~classname() { \
	if (key != NULL) { \
		if (key->getRefCount() > 1) { \
			_CL_VERBOSE << "Warning: Key wouldn't deleted in container element! (References: " << key->getRefCount() << ")(" << key->charrep() << ")" LOG_ \
		} \
		if (key->deleteState() != 1) { \
			_CL_VERBOSE << "Warning: Key wouldn't deleted in container element! (References: " << key->getRefCount() << ")(" << key->charrep() << ")" LOG_ \
		} \
		RELEASE(key); \
	} \
	if (data != NULL) { \
		if (data->getRefCount() > 1) { \
			_CL_VERBOSE << "Warning: Data wouldn't deleted in container element! (References: " << data->getRefCount() << ")" LOG_ \
		} \
		if (data->deleteState() != 1) { \
			_CL_VERBOSE << "Warning: Data wouldn't deleted in container element! (References: " << data->getRefCount() << ")" LOG_ \
		} \
		RELEASE(data); \
	} \
	key = NULL; \
	data = NULL; \
} \
\
lb_I_Unknown* classname::getObject() const { \
    lb_I_Unknown* uk = NULL; \
    if(data == NULL) { \
    	_LOGERROR << "FATAL: Element has no data. Could not return from NULL pointer!!" LOG_ \
    	return NULL; \
    } \
    if(!_TRMemValidate(data)) { \
    	char buf[20] = ""; \
    	sprintf(buf, "%p", data); \
    	_LOGERROR << "Error: Skiplist element data pointer is invalid! (" << buf << ", classname: " << data->getClassName() << ")" LOG_ \
    } \
    data->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); \
    if(uk == NULL) { \
    	_LOGERROR << #classname "::getObject() FATAL: Data instance given, but can't get a reference!!" LOG_ \
    } \
    return uk; \
} \
\
lb_I_KeyBase* LB_STDCALL classname::getKey() const { \
	lb_I_KeyBase* kbase = NULL; \
	if(key == NULL) _CL_LOG << "ERROR: Element has no key. Could not return from NULL pointer!!" LOG_ \
	key->queryInterface("lb_I_KeyBase", (void**) &kbase, __FILE__, __LINE__); \
	_CL_VERBOSE << "Key of " << key->getClassName() << " has " << key->getRefCount() << " references. Value is " << kbase->charrep() LOG_ \
	key->release(__FILE__, __LINE__); \
	return kbase; \
} \
\
void LB_STDCALL classname::setNext(lb_I_Element *e) { \
	e->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__); \
} \
\
lb_I_Element* LB_STDCALL classname::getNext() const { \
	return next; \
} \
int LB_STDCALL classname::equals(const lb_I_Element* a) const { \
	return 0; \
} \
\
int LB_STDCALL classname::equals(const lb_I_KeyBase* _key) const { \
	return (*key == _key); \
} \
int LB_STDCALL classname::lessthan(const lb_I_KeyBase* _key) const { \
	return (*key < _key); \
}
/*...e*/
/*...sclass lb_I_Container:0:*/
/** \brief Storage for other objects.
 *
 * A container can store other objects. It is filled while making a copy of
 * the object to be inserted! 
 *
 * Note: The documention is not complete!
 */
class lb_I_Container : public lb_I_Unknown {
public:
	/** \brief Number of objects in the container.
	 *
	 */
    virtual int LB_STDCALL Count() = 0;

	/** \brief Insert an object.
	 * 
	 * Creates a copy of the given object and holds it in the container.
	 * To identify it, it is passed in conjunction with a key object.
	 *
	 * The key may be a lb_I_KeyBase instance.
	 */
    virtual lbErrCodes LB_STDCALL insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) = 0;

	/** \brief Remove by given key.
	 *
	 * Remove an object having the given key. It may be that there are multible objects
	 * with that key. Remove affects only one of them. Not sure, if this is really so.
	 */
    virtual lbErrCodes LB_STDCALL remove(lb_I_KeyBase** const key) = 0;

	/** \brief Existence check for an object by key.
	 *
	 * Checks, if an object with the given key is in the container.
	 */
    virtual int LB_STDCALL exists(lb_I_KeyBase** const e) = 0;

	/** \brief Returns 1 if elements are iterable.
	 *
	 */
    virtual int LB_STDCALL hasMoreElements() = 0;

	/** \brief Get next element.
	 *
	 */
    virtual lb_I_Unknown* LB_STDCALL nextElement() = 0;

	/** \brief Stops the iteration modus, begun with hasMoreElements.
	 *
	 * Use this function to stop the iteration. You must use this function to
	 * be able to restart iteration. If hasMoreElements returns 0, the
	 * iteration is finished automatically.
	 */
    virtual void LB_STDCALL finishIteration() = 0;
	
	/** \brief Prosition the iterator by key.
	 * Searches an element by key and sets the iterator at found position.
	 */
	virtual int LB_STDCALL position(lb_I_KeyBase** const key) = 0;

	/** \brief Prosition the iterator by index.
	 * Positions the iterator at the given index. Starts at 0.
	 */
	virtual int LB_STDCALL position(int i) = 0;
	
	/** \brief Get element at given position. Starts at 0.
	 */
    virtual lb_I_Unknown* LB_STDCALL getElementAt(int i) = 0;
	
	/** \brief Get key at given position. Starts at 0.
	 */
    virtual lb_I_KeyBase* LB_STDCALL getKeyAt(int i) = 0;

    /**
     * Direct access over key
     */
    virtual lb_I_Unknown* LB_STDCALL getElement(lb_I_KeyBase** const key) = 0;
    virtual void LB_STDCALL setElement(lb_I_KeyBase** key, lb_I_Unknown** const e) = 0;

	/** \brief Delete all container entries.
	 *
	 * This deletes all entries of the container.
	 * 
	 * Note: In my wxWidgets sample application are stored database dialogs. These would be deleted
	 * by the destructor cleanup code. So they must be removed, not deleted.
	 *
	 * This is because of the special handling of open and hidden dialogs. 
	 */
    virtual void LB_STDCALL deleteAll() = 0;
    
    /** \brief Elements would not deleted from container.
     *
     * Use this function to avoid cleanup through the container.
     */
    virtual void LB_STDCALL detachAll() = 0;
	
	/** \brief Get current key based on iterator position.
	 *
	 */
	virtual lb_I_KeyBase* LB_STDCALL currentKey() = 0;
	
	/** \brief Use to avoid copying while insert.
	 *
	 * Disabling cloning with doClone=false.
	 */
	virtual void LB_STDCALL setCloning(bool doClone=true) = 0;
};

/*...sDECLARE_LB_I_CONTAINER_IMPL_CO \40\co_Interface\41\:0:*/
#define DECLARE_LB_I_CONTAINER_IMPL_CO(co_Interface) \
        virtual lb_I_Unknown* LB_STDCALL nextObject(); \
        virtual int LB_STDCALL hasMoreElements(); \
        virtual int LB_STDCALL exists(const lb_I_KeyBase* e); \
        virtual int LB_STDCALL Count(); \
        \
        virtual lbErrCodes LB_STDCALL insert(const co_Interface* e, const lb_I_KeyBase* key); \
        virtual lbErrCodes LB_STDCALL _insert(const lb_I_Unknown* e, const lb_I_KeyBase* key); \
        virtual lbErrCodes LB_STDCALL insert(const lb_I_Unknown* e, const lb_I_KeyBase* key); \
        \
        virtual lbErrCodes LB_STDCALL remove(const lb_I_KeyBase* key); \
        \
        virtual lb_I_Unknown* LB_STDCALL getElement(const lb_I_KeyBase* key); \
        virtual lb_I_Unknown* LB_STDCALL nextElement(); \
        \
	virtual lb_I_Unknown* LB_STDCALL getElementAt(int i); \
	virtual lb_I_Unknown* LB_STDCALL getKeyAt(int i); \
        \
        virtual void LB_STDCALL setElement(lb_I_KeyBase* key, const co_Interface* e); \
        virtual void LB_STDCALL setElement(lb_I_KeyBase* key, const lb_I_Unknown* e); \
        \
        virtual void LB_STDCALL deleteAll(); \
protected: \
    int count; \
    int iteration; \
    lb_I_Element* iterator;
/*...e*/
/*...sDECLARE_LB_I_CONTAINER_IMPL \40\\41\:0:*/
#define DECLARE_LB_I_CONTAINER_IMPL() \
        virtual int LB_STDCALL hasMoreElements(); \
        virtual int LB_STDCALL exists(lb_I_KeyBase** const e); \
        virtual int LB_STDCALL Count(); \
        \
        virtual lbErrCodes LB_STDCALL _insert(lb_I_Unknown** const e, lb_I_KeyBase** const key); \
        virtual lbErrCodes LB_STDCALL insert(lb_I_Unknown** const e, lb_I_KeyBase** const key); \
        \
        virtual lbErrCodes LB_STDCALL remove(lb_I_KeyBase** const key); \
        virtual lbErrCodes LB_STDCALL _remove(lb_I_KeyBase** const key); \
        \
        virtual lb_I_Unknown* LB_STDCALL getElement(lb_I_KeyBase** const key); \
        virtual lb_I_Unknown* LB_STDCALL nextElement(); \
	virtual void LB_STDCALL finishIteration(); \
	virtual int LB_STDCALL position(lb_I_KeyBase** const key); \
	virtual int LB_STDCALL position(int i); \
       \
	virtual lb_I_Unknown* LB_STDCALL getElementAt(int i); \
	virtual lb_I_KeyBase* LB_STDCALL getKeyAt(int i); \
        \
        virtual void LB_STDCALL setElement(lb_I_KeyBase** key, lb_I_Unknown** const e); \
        \
        virtual void LB_STDCALL deleteAll(); \
        virtual void LB_STDCALL detachAll(); \
		virtual void LB_STDCALL setCloning(bool doClone=true); \
		virtual lb_I_KeyBase* LB_STDCALL currentKey(); \
protected: \
    int count; \
	bool cloning; \
    int iteration; \
    lb_I_Element* iterator; \
    bool canDeleteObjects; \
    lb_I_Element* container_data;
/*...e*/

/**
 * The second interface name is the requested interface, that must be implemented for an implementation.
 * This macro implements the interface handling. It makes no sense, wrapping an implementation down to an
 * unknown element. All Implementations must implement the unknown interface. Then it is possible to ask
 * for the needed interface that can be stored in this container.
 */

/*...sIMPLEMENT_LB_I_CONTAINER_IMPL_CO base \40\classname\44\ co_Interface\41\:0:*/
#define IMPLEMENT_LB_I_CONTAINER_IMPL_CO(classname, co_Interface) \
classname::classname() { \
    iteration = 0; \
    ref = 0; \
    iterator = NULL; \
    count = 0; \
} \
\
lb_I_Unknown* LB_STDCALL classname::getElementAt(int i) { \
	_LOG << #classname << "::getElementAt(int i) not implemented" LOG_ \
	return NULL; \
} \
lb_I_Unknown* LB_STDCALL getKeyAt(int i) { \
	_LOG << #classname << "::getKeyAt(int i) not implemented" LOG_ \
	return NULL; \
} \
classname::~classname() { \
} \
int classname::Count() { \
        return count; \
} \
lbErrCodes classname::insert(const co_Interface* e, const lb_I_KeyBase* key) { \
        lbErrCodes err = ERR_NONE; \
\
        if ((err = insert((lb_I_Unknown*) e, key)) != ERR_NONE) { \
                _CL_LOG << "lbContainer::insert(...) Failed!" LOG_ \
                return err; \
        } \
\
        count++; \
        return err; \
} \
\
lbErrCodes classname::insert(const lb_I_Unknown* e, const lb_I_KeyBase* key) { \
        lbErrCodes err = ERR_NONE; \
\
        if ((err = _insert(e, key)) != ERR_NONE) { \
                _CL_LOG << "lbContainer::insert(...) Failed!" LOG_ \
                return err; \
        } \
\
        count++; \
        return err; \
} \
\
lbErrCodes classname::remove(const lb_I_KeyBase* key) { \
        lbErrCodes err = ERR_NONE; \
\
        if ((err = _remove(key)) != ERR_NONE) { \
                _CL_LOG << "lbContainer::remove(...) Failed!" LOG_ \
                return err; \
        } \
\
        count--; \
        return err; \
} \
\
int classname::hasMoreElements() { \
    if (iteration == 0) { \
                iteration = 1; \
        iterator = data; \
    } \
\
    if (iterator == NULL) { \
        iteration = 0; \
        return 0; \
    } \
\
    return 1; \
} \
\
lb_I_KeyBase* classname::currentKey() { \
	if (iterator == NULL) return NULL; \
	return iterator->getKey(); \
} \
\
lb_I_Unknown* classname::nextElement() { \
    lb_I_Element *temp = iterator; \
    iterator = iterator->getNext(); \
\
    if (temp == NULL) _CL_LOG << "Temporary iterator object is NULL!" LOG_ \
\
    lb_I_Object *o = temp->getObject(); \
\
    if (o == NULL) _CL_LOG << "Temporary object o is NULL!" LOG_ \
\
    return temp->getObject(); \
} \
\
lb_I_Unknown* classname::getElement(const co_Key* key) { \
    lb_I_Element* temp = data; \
    while (temp) { \
        if ((temp) && (*(temp->getKey()) == key)) { \
          lb_I_Unknown *o = temp->getObject(); \
          if (o == NULL) _CL_LOG << "Temporary object o is NULL!") LOG_ \
          return o; \
        } \
\
        temp = temp->getNext(); \
    } \
    return NULL; \
} \
\
void classname::setElement(co_Key* key, co_Interface const* e) { \
    remove(key); \
    insert(e, key); \
} \


/*...e*/

/*...sIMPLEMENT_LB_I_CONTAINER_IMPL base \40\classname\41\ \47\\47\ only base lb_I_Unknown:0:*/
#define IMPLEMENT_LB_I_CONTAINER_IMPL(classname) \
int LB_STDCALL classname::Count() { \
        return count; \
} \
\
lb_I_Unknown* LB_STDCALL classname::getElementAt(int i) { \
        int ii = 0; \
        lb_I_Element* temp = container_data; \
        while (temp != NULL) { \
                if (ii == i) return temp->getObject(); \
                temp = temp->getNext(); \
        } \
        return NULL; \
} \
lb_I_KeyBase* LB_STDCALL classname::getKeyAt(int i) { \
	int ii = 0; \
	lb_I_Element* temp = container_data; \
	while (temp != NULL) { \
		if (ii == i) return temp->getKey(); \
		temp = temp->getNext(); \
        } \
        return NULL; \
} \
void LB_STDCALL classname::deleteAll() { \
\
    if (container_data == NULL) { \
        _CL_LOG << "Error: Can't remove from empty container!" LOG_ \
        return ;\
    } \
\
    lb_I_Element* pre = NULL; \
\
    while (container_data->getNext() != NULL) { \
        pre = container_data; \
        container_data = container_data->getNext(); \
        RELEASE(pre); \
    } \
    RELEASE(container_data); \
\
} \
void LB_STDCALL classname::detachAll() { canDeleteObjects = false; } \
\
int LB_STDCALL classname::exists(lb_I_KeyBase** const key) { \
    if (getElement(key) == NULL) return 0; \
    return 1; \
} \
\
lbErrCodes LB_STDCALL classname::insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { \
        lbErrCodes err = ERR_NONE; \
\
        if ((err = _insert(e, key)) != ERR_NONE) { \
                _CL_LOG << "lbContainer::insert(...) Failed!" LOG_ \
                return err; \
        } \
\
        count++; \
        return err; \
} \
\
lbErrCodes LB_STDCALL classname::remove(lb_I_KeyBase** const key) { \
        lbErrCodes err = ERR_NONE; \
\
        if ((err = _remove(key)) != ERR_NONE) { \
                _CL_LOG  << "lbContainer::remove(...) Failed!" LOG_ \
                return err; \
        } \
\
        count--; \
        return err; \
} \
\
lbErrCodes LB_STDCALL classname::_insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { \
\
    if (container_data == NULL) { \
        lbElement* _data = new lbElement(*e, *key, cloning); \
\
        _data->queryInterface("lb_I_Element", (void**) &container_data, __FILE__, __LINE__); \
        if (container_data == NULL) _CL_LOG << "Could not get unknown interface of lbElement!" LOG_ \
\
        lb_I_Unknown* uk_o = NULL; \
        if ((uk_o = container_data->getObject()) == NULL) { \
                _CL_LOG << "Failed to insert first element in classname::insert" LOG_ \
                return ERR_CONTAINER_INSERT; \
        } else RELEASE(uk_o); \
    } \
    else { \
        lb_I_Element* temp; \
        for (temp = container_data; temp != NULL; temp = temp->getNext()) { \
            lb_I_Element* next = temp->getNext(); \
\
            if (next != NULL) { \
                if (next->getKey() < *key) { \
                    lbElement* el = new lbElement(*e, *key, cloning, next); \
                    temp->setNext(el); \
                    return ERR_NONE; \
                } \
            } \
            else { \
            	lbElement* el = new lbElement(*e, *key, cloning, next); \
                temp->setNext(el); \
                return ERR_NONE; \
            } \
        } \
    } \
    return ERR_NONE; \
} \
lbErrCodes LB_STDCALL classname::_remove(lb_I_KeyBase** const key) { \
\
    if (container_data == NULL) { \
        _CL_LOG << "Error: Can't remove from empty container!" LOG_ \
        return ERR_CONTAINER_REMOVE; \
    } \
\
    lb_I_Element* pre = container_data; \
    container_data = container_data->getNext(); \
\
    if (pre->getKey() == *key) { \
        RELEASE(pre); \
        return ERR_NONE; \
    } \
\
    for (lb_I_Element* temp = container_data; temp != NULL; temp = container_data->getNext()) { \
        if (temp->getKey() == *key) { \
            pre->setNext(temp->getNext()); \
            RELEASE(temp); \
            return ERR_NONE; \
        } \
    } \
    _CL_LOG << "Error: No object with that key" LOG_ \
    return ERR_CONTAINER_REMOVE; \
} \
\
void LB_STDCALL classname::finishIteration() { \
	iterator = NULL; \
	iteration = 0; \
} \
int LB_STDCALL classname::hasMoreElements() { \
    if (iteration == 0) { \
                iteration = 1; \
        iterator = container_data; \
    } \
\
    if (iterator == NULL) { \
        iteration = 0; \
        return 0; \
    } \
\
    return 1; \
} \
lb_I_KeyBase* classname::currentKey() { \
	if (iterator == NULL) return NULL; \
	return iterator->getKey(); \
} \
\
lb_I_Unknown* LB_STDCALL classname::nextElement() { \
    lb_I_Element *temp = iterator; \
    if (temp == NULL) { \
        _CL_LOG << "Error: Please call hasMoreElements first to check if any elements are available!" LOG_ \
        return NULL; \
    } \
    iterator = iterator->getNext(); \
\
    if (temp == NULL) _CL_LOG << "Temporary iterator object is NULL!" LOG_ \
\
    lb_I_Unknown *o = temp->getObject(); \
\
    if (o == NULL) _CL_LOG << "Temporary object o is NULL!" LOG_ \
\
    return o; \
} \
\
lb_I_Unknown* LB_STDCALL classname::getElement(lb_I_KeyBase** const key) { \
    lb_I_Element* temp = container_data; \
    while (temp) { \
        if ((temp) && (*(temp->getKey()) == *key)) { \
          lb_I_Unknown *o = temp->getObject(); \
          return o; \
        } \
\
        temp = temp->getNext(); \
    } \
    return NULL; \
} \
\
void LB_STDCALL classname::setElement(lb_I_KeyBase** key, lb_I_Unknown ** const e) { \
    remove(key); \
    insert(e, key); \
}
/*...e*/

/*...e*/


/** \brief Enumbering directories and their files.
 * This class returns a list of files or directories found in a given path.
 * The result is not recursively. This has to be done by the user.
 */
class lb_I_DirectoryBrowser : public lb_I_VisitableHelper {
public:
	/** \brief Get a list of directories.
	 * The container is keyed by integers that are simply incremented for each found item.
	 */
	virtual lb_I_Container* LB_STDCALL getDirectories(lb_I_String* path) = 0;
	
	/** \brief Get a list of directories.
	 * The container is keyed by integers that are simply incremented for each found item.
	 */
	virtual lb_I_Container* LB_STDCALL getDirectories(const char* path) = 0;
	
	/** \brief Get a list of files.
	 * The container is keyed by integers that are simply incremented for each found item.
	 */
	virtual lb_I_Container* LB_STDCALL getFiles(lb_I_String* path) = 0;
	
	/** \brief Get a list of files.
	 * The container is keyed by integers that are simply incremented for each found item.
	 */
	virtual lb_I_Container* LB_STDCALL getFiles(const char* path) = 0;
};

/*...sclass lb_I_Instance:0:*/
class lb_I_Instance : public lb_I_KeyBase {

/*...sprotected:0:*/
protected:

    lb_I_Instance() {}
    virtual ~lb_I_Instance() {}

/*...e*/

public:

	virtual char* LB_STDCALL getAddress() = 0;
	virtual char* LB_STDCALL getInstanceClassname() = 0;
	virtual char* LB_STDCALL getFile() = 0;
	virtual int LB_STDCALL getLine() = 0;
	
	virtual void LB_STDCALL setAddress(const char* a) = 0;
	virtual void LB_STDCALL setClassname(const char* c) = 0;
	virtual void LB_STDCALL setFile(const char* f) = 0;
	virtual void LB_STDCALL setLine(int l) = 0;


	/**
	 * Build a string with classname + _ + file + _ + line as a key for the reference.
	 * If the release function is used directly, it shows me an unregistered reference,
	 * so I will find all non UAP pointers.
	 */
	virtual void LB_STDCALL addReference(const char* classname, const char* file, int line) = 0;
	virtual void LB_STDCALL delReference(const char* classname, const char* file, int line) = 0;
};
/*...e*/
/*...sclass lb_I_InstanceReference:0:*/
class lb_I_InstanceReference :
public lb_I_Unknown
{
public:
        virtual char* LB_STDCALL getFile() = 0;
        virtual int LB_STDCALL getLine() = 0;
        virtual int LB_STDCALL getCount() = 0;

        virtual void LB_STDCALL setFile(const char* f) = 0;
        virtual void LB_STDCALL setLine(int l) = 0;
        virtual void LB_STDCALL setCount(int c) = 0;

};
/*...e*/
/*...sclass lb_I_Log:0:*/
class lb_I_Log : public lb_I_Unknown {
public:

// This order does not work with visual C++ !!??
//    virtual void LB_STDCALL log(const char *msg, long line, char* file) = 0;
    virtual void		LB_STDCALL logdirect(const char *msg, const char *f, int level) = 0;
// Take it here...    
    virtual void		LB_STDCALL log(const char *msg, long line, const char* file) = 0;
    virtual void		LB_STDCALL log(int log) = 0;
    virtual void		LB_STDCALL enable(const char *where) = 0;
    virtual void		LB_STDCALL disable(const char *where) = 0;
    virtual void		LB_STDCALL event_begin(const char *event) = 0;
    virtual void		LB_STDCALL event_end(const char *event) = 0;
    virtual void		LB_STDCALL setPrefix(const char* p) = 0;
    
    
    virtual lb_I_Log&	LB_STDCALL operator<< (const int i) = 0;
    virtual lb_I_Log&	LB_STDCALL operator<< (const long i) = 0;
    virtual lb_I_Log&	LB_STDCALL operator<< (const char c) = 0;
    virtual lb_I_Log&	LB_STDCALL operator<< (const char* string) = 0;
    virtual void		LB_STDCALL setCustomLogFile(const char* name) = 0;
};
/*...e*/
/*...sZThread interfaces:0:*/
#ifndef WINDOWS
class lb_I_Runnable : public lb_I_Unknown {
protected:
    lb_I_Runnable() {}
    virtual ~lb_I_Runnable() {}

public:
    virtual lbErrCodes run() = 0;
};    

class lb_I_ZThread : public lb_I_Runnable {
protected:
    lb_I_ZThread() {}
    virtual ~lb_I_ZThread() {}
    
public:
    virtual lb_I_ZThread* operator->() = 0;
    virtual bool equals(const lb_I_ZThread* t) const = 0;
    virtual bool operator==(const lb_I_ZThread* t) const = 0;
    virtual lbErrCodes kill() = 0;
    virtual lbErrCodes join() = 0;
    virtual lbErrCodes run(lb_I_Runnable* target) = 0;
    virtual lbErrCodes interrupt() = 0;
    // The set/getPriority functions are not implemented yet
    virtual bool isInterrupted() = 0;
    virtual bool isKilled() = 0;
    virtual bool isDaemon() = 0;
    virtual lbErrCodes setDaemon(bool flag) = 0;
    virtual lbErrCodes setNotify(bool flag) = 0;
    virtual bool wantNotify() = 0;
    virtual lbErrCodes sleep(unsigned long s) = 0;
    virtual lbErrCodes yield() = 0;
    // current is not implemented yet
    // FastThreadLocal is not implemented yet
};
#endif
/*...e*/
/*...sclass lb_I_ThreadImplementation:0:*/
class lb_I_ThreadImplementation;
class lb_I_Thread;

typedef void (LB_STDCALL lb_I_ThreadImplementation::*lbThreadFunction)(lb_I_Thread* threadHost);

class lb_I_ThreadImplementation : public lb_I_Unknown {
public:
	/** \brief The function, that represents the thread.
	 * This function should be used to run the thread.
	 * Each new thread may have the same function pointer,
	 * but this could be changed by the thread implementation
	 * on behalf of logic.
	 */
	virtual lbThreadFunction LB_STDCALL getThreadFunction() = 0;
	
	/** \brief Indicator for done thread.
	 * This function indicates, if a thread has been finished.
	 */
	virtual bool LB_STDCALL isFinished() = 0;
};
/*...e*/

/*...sclass lb_I_ApplicationServerThread:0:*/
class lb_I_ApplicationServerThread :
	public lb_I_ThreadImplementation,
	public lb_I_ProtocolManager,
	public lb_I_ProtocolDispatcher {
public:	
	virtual bool LB_STDCALL isConnected(lb_I_Transfer_Data* request) = 0;
	virtual lbErrCodes LB_STDCALL init(lb_I_Transfer* _clt, lb_I_ApplicationServer* _server) = 0;
};
/*...e*/

/*...sclass lb_I_ProtocolThread:0:*/
class lb_I_ProtocolThread :
	public lb_I_ThreadImplementation {
public:
	virtual lbErrCodes LB_STDCALL init(lb_I_Transfer* _clt, lb_I_ApplicationServerThread* _parentthread) = 0;
};
/*...e*/

/*...sclass lb_I_Thread:0:*/
class lb_I_Thread : public lb_I_Unknown {
public: 

	virtual lb_I_ThreadImplementation* LB_STDCALL getThreadImplementation() = 0; 
	virtual lbErrCodes LB_STDCALL setThreadImplementation(lb_I_ThreadImplementation* impl) = 0; 

        virtual lbErrCodes LB_STDCALL create() = 0;

        virtual lbErrCodes LB_STDCALL run() = 0; 
        virtual lbErrCodes LB_STDCALL stop() = 0;
        
        virtual lbErrCodes LB_STDCALL pause() = 0;
        virtual lbErrCodes LB_STDCALL resume() = 0;
};
/*...e*/
/*...sclass lb_I_Mutex:0:*/
class lb_I_Mutex : public lb_I_Unknown {
public:
        virtual void createMutex(int name) = 0;
        virtual void deleteMutex(int name) = 0;
        virtual void enter() = 0;
        virtual void release() = 0;
        
};
/*...e*/

class lb_I_Lock;
/*...sclass lb_I_CriticalSection:0:*/
class lb_I_CriticalSection : public lb_I_Unknown {
protected:
        virtual lbErrCodes enter() = 0;
        virtual lbErrCodes leave() = 0;
        
        friend class lb_I_Lock;
};
/*...e*/
/*...sclass lb_I_Lock:0:*/
class lb_I_Lock : public lb_I_Unknown {
public:
	virtual void LB_STDCALL with(lb_I_CriticalSection* _cso, char* _name) = 0;
};
/*...e*/


/*...sthread stuff:0:*/
#ifdef bla
/*...sclass lb_I_Mutex:0:*/
/*...e*/

class DLLEXPORT lbCritSect : public lb_I_Unknown {
public:
        lbCritSect();
        virtual ~lbCritSect();

private:
        //lbCritSect(const lbCritSect&) {}

protected:
        lbErrCodes enter();
        lbErrCodes leave();
        
        void* critsect; 
        
        friend class lbLock;
};

class DLLEXPORT lbLock {
public:
        lbLock(lbCritSect& _cso, char* _name);
        virtual ~lbLock();
private:
        lbLock() {}
        lbLock(const lbLock&) {}

        char* name;
        lbCritSect* cso;
};

#endif // bla
/*...e*/

#endif // __LB_INTERFACES_SUB_CLASSES__

