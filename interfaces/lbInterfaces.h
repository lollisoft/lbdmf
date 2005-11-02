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
            Rosmarinstr. 3

            40235 Duesseldorf (germany)
*/
/*...e*/

/**
 *  \file lbInterfaces.h
 *  Main include file for all interfaces.
 *
 *  lbConfigHook.h includes this file for you.
 */

/*...sMain page documentation:0:*/
/** \mainpage Distributed Multiplatform Framework
 * \section intro_sec Introduction to DMF - Distributed Multiplatform Framework
 *
 * This is the introduction for the users of DMF after the first installation.
 * Here the post installation will be explained in short and other important things,
 * that have to do with installation and different usage as of databases.
 *
 * To start programming, you could start \ref Quickstart "here".
 *
 * The main sample application and it's documentation will be found \ref PrototypeGUI "here".
 *
 * Prerequirements:
 *
 * My latest version of binary build tools. <a href="http://sourceforge.net/project/showfiles.php?group_id=70545&package_id=69806">Binary Build Tools</a>
 *
 * Open Watcom compiler, at least version 1.2. <a href="http://www.openwatcom.org">Open Watcom</a>
 * 
 * The wxWidgets source code. Tested version is 2.4.2. <a href="http://www.wxwidgets.org">wxWidgets</a>
 *
 * I have included <a href="http://www.daily.de/RepWrt/">wxReportWriter</a>. This project allows me to create database
 * reports on the fly. But this feature doesn't work under Linux yet. Currently these files have minimal changes compared
 * to the orginal version. 
 * 
 * One of the following databases: <a href="http://www.mysql.com">MySQL</a>, <a href="http://www.postgresql.org">PostgreSQL</a> or <a href="http://www.sybase.com">Sybase</a>.
 * Other databases may be possible, but there is not yet a SQL script to setup the database.
 *
 * \ref Postsetup "Post setup instructions."
 */
/*...e*/

/*...sQuickstart page documentation:0:*/
/** \page Quickstart Beginning programming in DMF environment.
 *
 * \section Introduction
 * Here we will learn to create simple console applications.
 *
 * \section HelloWorld A simple application like the famous Hello world application.
 * As the most programming environments, showing a first sample application, I will do the same.
 * We will start to create a new simple Hello world application, showing a 'Hello world' text.
 * But we do not use prinf's or cout's.
 *
 * We would use the console logging feature of DMF and a string class that will be loaded from
 * anywhere else using an interface.
 *
 * At first, you will see the code:
 * \ref FirstSample "Hello world."
 *
 */
/*...e*/

/*...sPost setup documentation:0:*/
/** \page Postsetup Post setup instructions.
 *
 * \section Introduction
 * You do need to post setup your installation. These includes minimal changes in files, installing
 * software, databases, ODBC drivers and setup ODBC configurations.
 *
 * \section PSetup1 Post setup
 *
 *	The post setup uses a scenary of an installation to drive D: where afterwards a directory lbDMF exists.
 *
 * \section PSetup2 lbDMF Develop link
 *
 *	If you start the lbDMF Develop link on the desktop, you get opened a text file with
 *	a hint text. It explains once to read these instructions for post installation.
 *
 *	If you don't have downloaded the source distribution yet, do this before continuing.
 *
 * \section PSetup3 Drive letter
 *
 *	If you have installed lbDMF to C:\\lbDMF, you can skip this step.
 *
 *	Right click on lbDMF Develop symbol to edit it. Change the drive letter, pointing to
 *	your actual installation. Sample here would drive D: and not the standard C: drive letter.
 *	In this sample installation scenario, simply change the lines set DEVLW=<driveletter> to DEVLW=D:
 *
 *	Note: There are two locations of setting DEVLW. Change the line after :DISTMODE
 *
 * \section PSetup4 Setup wxWidgets
 *
 *	Install the wxWidgets distribution into [C/D]:\\lbDMF\\Develop\\wxwin\\wx.
 *
 *	After installation: Check, if inside exists a src directory and all else of the distribution.  
 *
 * \section PSetup5 Setup Open Watcom
 *
 *	Install the Open Watcom distribution into [C/D]:\\lbDMF\\Develop\\tools\\watcom.
 *
 *	After installation: Check, if inside exists a src directory and all else of the distribution.  
 *
 * \section PSetup6 Make wxWidgets (2.4.x) source tree
 *
 *	If you like to have a static library, skip that lines, that copy makefile.env and makefile.wat.
 *
 *	Start a normal MSDOS console (cmd) and type these lines (C:):
 *
 *	\code
 *	set DRIVE=C:
 *	set WXWIN=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXWIN%\src\msw
 *	copy /Y %WXWIN%\include\wx\msw\setup.h %WXWIN%\include\wx
 *	copy /Y %WXWIN%\..\..\Projects\CPP\makewat.env %WXWIN%\src
 *	copy /Y %WXWIN%\..\..\Projects\CPP\makefile.wat %WXWIN%\src\msw
 *	wmake -f makefile.wat all
 *	\endcode
 *
 *	or
 *
 *	Start a normal MSDOS console (cmd) and type these lines (D:):
 *
 *	\code
 *	set DRIVE=D:
 *	set WXWIN=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXWIN%\src\msw
 *	copy /Y %WXWIN%\include\wx\msw\setup.h %WXWIN%\include\wx
 *	copy /Y %WXWIN%\..\..\Projects\CPP\makewat.env %WXWIN%\src
 *	copy /Y %WXWIN%\..\..\Projects\CPP\makefile.wat %WXWIN%\src\msw
 *	wmake -f makefile.wat all
 *	\endcode
 *
 * \section PSetup61 Make wxWidgets (2.6.x) source tree
 *
 *	Bevore you build the library, decide to build a static library or a shared library (DLL).
 *	If you like to have a DLL, modify the following file: config.wat in the build/msw directory.
 *
 *	# What type of library to build? [0,1]
 *	SHARED = 1
 *
 *	There is also a switch for debug or release builds:
 *
 *	# Type of compiled binaries [debug,release]
 *	BUILD = release
 *
 *	Start a normal MSDOS console (cmd) and type these lines (C:):
 *
 *	\code
 *	set DRIVE=C:
 *	set WXWIN=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXWIN%\build\msw
 *	copy /Y %WXWIN%\include\wx\msw\setup.h %WXWIN%\include\wx
 *	wmake -f makefile.wat all
 *	\endcode
 *
 *	or
 *
 *	Start a normal MSDOS console (cmd) and type these lines (D:):
 *
 *	\code
 *	set DRIVE=D:
 *	set WXWIN=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXWIN%\build\msw
 *	copy /Y %WXWIN%\include\wx\msw\setup.h %WXWIN%\include\wx
 *	wmake -f makefile.wat all
 *	\endcode
 *
 *	This should start compiling the wxWidgets code.
 *
 *	After you have built wxWitgets, you must copy the created DLL to the place where it should be
 *	installed:
 *
 * \section PSetup62 Copy DLL/library for wxWidgets 2.4.x/2.6.x:
 *
 *	From drive C:
 *
 *	\code
 *	set DRIVE=C:
 *	set WXWIN=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXWIN%\src\msw
 *	mkdir %WXWIN%\..\..\Projects\dll\libs
 *	copy /Y %WXWIN%\lib\wat_dll\wxmsw*.dll %WXWIN%\..\..\Projects\dll
 *	copy /Y %WXWIN%\lib\wat_dll\wxmsw*.lib %WXWIN%\..\..\Projects\dll\libs
 *	copy /Y %WXWIN%\lib\wxmsw*.dll %WXWIN%\..\..\Projects\dll
 *	copy /Y %WXWIN%\lib\\wxmsw*.lib %WXWIN%\..\..\Projects\dll\libs
 *	\endcode
 *
 *	From Drive D:
 *
 *	\code
 *	set DRIVE=D:
 *	set WXWIN=%DRIVE%\lbDMF\Develop\wxwin\wx
 *	%DRIVE%
 *	cd %WXWIN%\src\msw
 *      mkdir %WXWIN%\..\..\Projects\dll\libs
 *	copy /Y %WXWIN%\lib\wat_dll\wxmsw*.dll %WXWIN%\..\..\Projects\dll
 *      copy /Y %WXWIN%\lib\wat_dll\wxmsw*.lib %WXWIN%\..\..\Projects\dll\libs
 *      copy /Y %WXWIN%\lib\wxmsw*.dll %WXWIN%\..\..\Projects\dll
 *      copy /Y %WXWIN%\lib\\wxmsw*.lib %WXWIN%\..\..\Projects\dll\libs
 *	\endcode
 *
 * \section PSetup7 Start compiling lbDMF source tree
 *
 *	If you have done this, you can restart the lbDMF Develop link and a simple console window
 *	starts.
 *
 *	Type make
 *
 * \section PSetup8 Database setup
 *
 *	To be able to run the sample applications, you need to create at least one database.
 *	Do this with the tools, provided from the database vendors.
 *	
 *	The first database, needed should be named lbdmf and a correct ODBC configuration should
 *	be set up.
 *
 *	The database scripts are located in [C/D]:\\lbDMF\\Develop\\Projects\\CPP\\Database.
 *
 *	Create at least an user to have rights to change data. For the PostgreSQL database, create
 *	the user and create the tables with that user logged on. If you set up the tables with the
 *	database system user, your user has not the correct rigths.
 *
 *	Set the environment variables to connect with the correct user and password. If not, default values from
 *	my private database are used:
 *
 *	set lbDMFUser=<User>
 *
 *	set lbDMFpasswd=<Password>
 *
 * \section PSetup9 Run the sample GUI application
 *
 *	Simply after compiling the sources, let the build window open and type wxwrapper. Go to menu
 *	File->Login and login as behrens over the wizard and use password as the password.
 *
 *	After successfull login you should be able to select an application. Choose lbDMF Manager.
 *
 */
/*...e*/

/*...sDatabase Prototype GUI:0:*/
/** \page PrototypeGUI Database prototype GUI documentation
 *
 * \section Introducion
 *
 * The main sample application, distributed also as binary sample, is aimed to be a prototype
 * for any kind of database applications. You could define forms and related information in a
 * configuration database.
 *
 * If you have a target database model for a specific application, then it is easy to build up
 * a prototype for it in minutes.
 *
 * \section Application
 *
 * Let us start with an application - say - we have a small CD collection database.
 *
 * \section Database Setup
 *
 * The CD collection database will consist interprets, album and and title tables. To create
 * the database, please copy the SQL code below to your database query editor.
 *
 * \code
 	CREATE TABLE interpret (
 		id SERIAL,
 		name CHAR(50),
 		country CHAR(3),
 		PRIMARY KEY (id)
 	);
 	
 	CREATE TABLE album (
 		id SERIAL,
 		interpretid INT,
 		name CHAR(50),
 		go_public_date DATETIME,
 		PRIMARY KEY (id)
 	);
 	
 	CREATE TABLE title (
 		id SERIAL,
 		albumid INT,
 		songid INT,
 		name CHAR(50),
 		time TIME,
 		PRIMARY KEY (id)
 	);
 * \endcode
 */
/*...e*/

#ifdef _MSC_VER

#pragma warning( disable: 4275 )
#pragma warning( disable: 4101 )
#pragma warning( disable: 4102 )
#pragma warning( disable: 4172 )
#pragma warning( disable: 4251 )

#endif

#ifdef __WATCOMC__
#pragma warning 14 9;
#endif

/*...sdocu:0:*/
/**
 * For all Interfaces are factories needed. How should I design these
 * factories ?
 */
 
/*...e*/

/*...sbasics:0:*/
/*...sincludes and definitions:0:*/
/**
 * All classes, that anounce callbacks, must implement the interface for
 * lb_I_CallbackManager. The callback manager did not need to handle its
 * own table, more it may delegate this to the static (singleton) handler.
 */


#ifndef __LB_INTERFACES__
#define __LB_INTERFACES__

// If NULL is undefined, let it define by stddef.h
#ifndef NULL
#include <stddef.h>
#endif

#include <lbErrcodes.h>

//#define LB_STDCALL

#ifndef FALSE
#define FALSE false
#endif

// KDevelop: Problems to set these variable :-)
#ifdef TVISION
 #ifndef LB_STDCALL
  #ifdef WINDOWS
   #define LB_STDCALL __cdecl
   //__attribute__((cdecl))
  #endif
  #ifndef WINDOWS
   #define LB_STDCALL
  #endif
 #endif
#endif

#ifndef _MSC_VER
 #ifndef LB_STDCALL
  #ifdef WINDOWS
   #define LB_STDCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_STDCALL
  #endif
 #endif

 #ifndef LB_FUNCTORCALL
  #ifdef WINDOWS
   #define LB_FUNCTORCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_FUNCTORCALL
  #endif
 #endif
#endif

#ifdef _MSC_VER
 #ifndef LB_STDCALL
  #ifdef WINDOWS
   #define LB_STDCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_STDCALL
  #endif
 #endif

 #ifndef LB_FUNCTORCALL
  #ifdef WINDOWS
   #define LB_FUNCTORCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_FUNCTORCALL
  #endif
 #endif
#endif

#ifdef __WATCOMC__
#define LB_DLLEXPORT __declspec(dllexport)
#endif

#ifndef __WATCOMC__
#define LB_DLLEXPORT __declspec(dllexport)
#endif

#ifdef __WATCOMC__
#define LB_DLLIMPORT __declspec(dllimport)
#endif

#ifndef __WATCOMC__
#define LB_DLLIMPORT __declspec(dllimport)
#endif

#ifndef DLLEXPORT
// Default to import. Modules redefine this in general.
#ifdef WINDOWS
#define DLLEXPORT
#endif
#ifdef LB_DMF_POWER
#define DLLEXPORT
#endif
#ifdef LINUX
#define DLLEXPORT
#endif
#endif

#ifndef __BASE_TYPES_DEFINED__
#define __BASE_TYPES_DEFINED__
/*...sbase types:0:*/
#ifndef __WATCOMC__
#ifndef _MSC_VER
#ifndef TVISION
typedef unsigned short byte;
typedef unsigned short u_short;
#endif
#endif
#endif
#ifdef __POWERPP
typedef unsigned short byte;
typedef unsigned short u_short;
#endif

typedef unsigned long DWORD;

typedef unsigned short LB_DATA;
typedef unsigned short u_short;
/*...e*/
#endif // __BASE_TYPES_DEFINED__

class lb_I_CallbackTarget;
class lb_I_ProtocolTarget;

#include <lbInterfaces-sub-transfer.h>
/*...e*/

/*...sforward class decl\39\s:0:*/
/**
 * The base interface, that currently implements only release.
 * A query interface should be added. But is M$'s solution usable ?
 */
 
class lb_I_gcManager;
class lb_I_Unknown;
class lb_I_Module;

class lb_I_Container;
class lb_I_Event;
class lb_I_EventSink;

class lb_I_Dispatcher;
class lb_I_EventManager;
class lb_I_EventHandler;

class lb_I_ConfigObject;

class lb_I_Frame;
/*...e*/

/*...scallback \47\ handler typedefs:0:*/
/**
 * This is a base class for all callback able objects
 */
///////////////////////////////////////////////////////////////
// Type for lb protocol callback functions. This should be an interface.
typedef lbErrCodes (lb_I_ProtocolTarget::*lbProtocolCallback)( lb_I_Transfer_Data const &, lb_I_Transfer_Data&);
typedef lbErrCodes (lb_I_CallbackTarget::*lbMemberCallback)( const char* handlername, lb_I_Transfer_Data&);



typedef lbErrCodes (lb_I_EventSink::*lb_I_EventCallback)(lb_I_Unknown* question, lb_I_Unknown* answer); 


#ifndef TVISION
typedef lbErrCodes (LB_STDCALL lb_I_EventHandler::*lbEvHandler)(lb_I_Unknown* uk);
#endif
#ifdef TVISION
typedef lbErrCodes ( lb_I_EventHandler::*lbEvHandler)(lb_I_Unknown* uk);
#endif
/*...e*/

/*
	CL_LOG("Releasing instance"); \
*/
/*...sdefine RELEASE\40\instance\41\:0:*/
#define RELEASE(instance) \
	{ lbErrCodes err; \
		if ((err = instance->release(__FILE__, __LINE__)) != ERR_NONE) { \
			if (err == ERR_REFERENCE_COUNTING ) { \
				_CL_LOG << "RELEASE(...) Reference count mismatch at " << __LINE__ << " in " << __FILE__ LOG_ \
			} else { \
			} \
		} else { \
			instance = NULL; \
		} \
	}

/*...e*/
/*...sdefine QI\40\source\44\ interface\44\ target\44\ file\44\ line\41\:0:*/
#define QI(source, interface, target, file, line) \
	target.setFile(file); \
	target.setLine(line); \
	{ \
		char* iface = (char*) malloc(strlen(#interface)+1); \
		strcpy(iface, #interface); \
	 	err = source->queryInterface(iface, (void**) &target, file, line); \
	 	free(iface); \
	 	iface = NULL; \
	}

#define _QI(source, interface, target) \
	target.setFile(file); \
	target.setLine(line); \
 	err = source->queryInterface(#interface, (void**) &target, __FILE__, __LINE__);
/*...e*/
/*...e*/

// UNKNOWN_AUTO_PTR was tested, use it.

#define USE_UAP

class miniString {
public:
	miniString() {
		ptr = (char*) malloc(1);
		ptr[0] = 0;
	}

	virtual ~miniString() {
		if (ptr) free(ptr);
	}

	char* get() {
		return ptr;
	}

	void set(char* p) {
		if (p) {
			if (ptr) free(ptr);
			
			ptr = (char*) malloc(strlen(p)+1);
			ptr[0] = 0;
			strcpy(ptr, p);
		}
	}

protected:
	char* ptr;
};

	/* setData must check the type of this ! */
	/* = may also be possible */
/*...sclass lb_I_Unknown:0:*/
#define STARTREF 0


/*...sclass lb_I_Unknown:0:*/
/**
 * \brief Similar to IUnknown aka Microsoft COM.
 *
 * lb_I_Unknown is the base class for all other classes, that are used in the framework.
 * All classes, that needs to be loaded dynamically, must inherid from this class.
 */
class lb_I_Unknown {

private:
	/**
	 * Hide this operator to prevent usage. Effect ??
	 */
	lb_I_Unknown& operator=(const lb_I_Unknown& rhs);
	
	/**
	 * Hide this operator to prevent usage. Effect ??
	 */
	lb_I_Unknown* operator=(const lb_I_Unknown* rhs);
	
public:
	/**
	 * Call this, when you no longer use an instance of any classes, that have
	 * this as a base class.
	 *
	 * This decrements the internal reference counter and if zero, it destroys
	 * it self. The pointer, you have in use, is undefined afterwards. You should set
	 * it to NULL.
	 */
	virtual lbErrCodes LB_STDCALL release(char* file, int line) = 0;

	/**
	 * This function returns it's location of creation. The creation of this instance
	 * would be set with setModuleManager.
	 */
	virtual char* LB_STDCALL getCreationLoc() const = 0;
	
	/**
	 * Indicator, to determine, if the instance has no more references.
	 * The instance would be deleted at next release.
	 */
	virtual int LB_STDCALL deleteState() = 0;
	
	/**
	 * Activate or deactivate debug informations.
	 */
	virtual void LB_STDCALL setDebug(int i) = 0;
	
	/**
	 * Returns the number of references to this instance.
	 */
	virtual int LB_STDCALL getRefCount() = 0;
	
	/**
	 * Returns the classname of this instance. It should be a hint to determine
	 * the real type of this instance. This is not a way to determine the interface
	 * of this class. The class in use can provide more than one interface to be used.
	 *
	 * It is not clear, how to implement that.
	 */
	virtual char* LB_STDCALL getClassName() = 0;

	/**
	 * Set the module manager. This is the - so called - object hook to get new
	 * instances of any kint of interface.
	 */
	virtual void LB_STDCALL setModuleManager(lb_I_Module* m, char* file, int line) = 0;
	
	/**
	 * This returns the module manager, if you like to use it. It may not be set up
	 * in this instance. Better use the global function getModuleInstance().
	 */
	virtual lb_I_Module*   LB_STDCALL getModuleManager() = 0;
		
	/**
	 * Query this instance for any interfaces it may support. A real implementation, derived
	 * from this, has a supported interface.
	 *
	 * There is a list interface functionality missing. I do not know, how to implement
	 * this in the macros.
	 *
	 * An idea may be a dummy call to it at any point after instantiation and include code
	 * to register all defined interfaces one per livetime.
	 */
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown, char* file, int line) = 0;

	/**
	 * This is an attempt to resolve any dangling references. As yet tried, a release on another
	 * place don't help, because the reference ID would include the place of creation.
	 *
	 * (__FILE__, __LINE__)
	 *
	 * With the help of UAP, it may be possible, because it can hold such an ID for each reference.
	 */
	virtual char* LB_STDCALL _queryInterface(char* name, void** unknown, char* file, int line) = 0;
        
        /**
         * This was used yet for put an object in a container. After inserting the object
         * into the container, there are two instances (not two references).
         * So the cloning is generaly a good way to make copies of an object.
         *
         * But remark:	The cloned object returned is not the instance in general.
         *		It is the *FIRST* lb_I_Unknown* reference to it.
         *		Putting an object in a container, you have your instance
         *		with the same reference count as before.
         *		
         *		The clone() method does not and is not able to make deep clones.
         *		It does not know how !
         *
         *		It creates a new instance with the normal constructor. But it calls
         *		the method setData with the this pointer.
         *		You must provide this method to be able to make a copy of your data.
	 *
         *
         *		return uk;
         */
        virtual lb_I_Unknown* LB_STDCALL clone(char* file, int line) const = 0;
        
        /**
         * This member must be implemented by the programmer of each class. setData is called
         * from the clone member to get a correct copy of the cloned instance.
         */
        virtual lbErrCodes LB_STDCALL setData(lb_I_Unknown* u) = 0;

//friend class lb_I_gcManager;	
};
/*...e*/


/*...sAutoPointer:0:*/
/** \def UAP(interface, Unknown_Reference, file, line)
 *  \brief An automatic pointer implementation via macro.
 */

#define UAP(interface, Unknown_Reference, file, line) \
		class UAP##Unknown_Reference { \
\
		char* my_strdup(char* s) { \
			if (s == NULL) return NULL; \
			char* temp = (char*) malloc(strlen(s)+1); \
			temp[0] = 0; \
			strcpy(temp, s); \
			return temp; \
		} \
		public: \
	        UAP##Unknown_Reference() { \
	        	_autoPtr = NULL; \
	        	_line = -1; \
	        	_file = NULL; \
	        	attachedClassName = NULL; \
	        	allowDelete = 1; \
	        	initialized = false; \
		} \
		\
		UAP##Unknown_Reference(const UAP##Unknown_Reference& _ref) { \
			attachedClassName = NULL; \
			initialized = false; \
			if ((_ref != NULL) && (_ref->getClassName() != NULL)) \
				attachedClassName = my_strdup(_ref->getClassName()); \
			else \
				attachedClassName = my_strdup(""); \
			if (_file != NULL) delete [] _file; \
			_file = NULL; \
			if (_ref._file) { \
				_file = new char [strlen(_ref._file) + 1]; \
				_file = strcpy(_file, _ref._file); \
			} \
			_line = _ref._line; \
			_autoPtr = NULL; \
		} \
		void operator=(const UAP##Unknown_Reference& _ref) { \
			if (_file != NULL) { \
				delete [] _file; \
				if (_ref._file) { \
					_file = new char [strlen(_ref._file) + 1]; \
					_file = strcpy(_file, _ref._file); \
				} \
			} \
			if (attachedClassName) { \
				free(attachedClassName); \
			} \
			initialized = false; \
			if ((_ref != NULL) && (_ref->getClassName() != NULL)) \
			        attachedClassName = my_strdup(_ref->getClassName()); \
		        else \
		                attachedClassName = my_strdup(""); \
			_line = _ref._line; \
			_autoPtr = _ref._autoPtr; \
		} \
		\
		virtual ~UAP##Unknown_Reference() { \
			if (_file) delete [] _file; \
			if (attachedClassName != NULL) free(attachedClassName); \
			if (_autoPtr != NULL) { \
				if (allowDelete != 1) { \
					if (_autoPtr->deleteState() == 1) { \
						printf("Error: Instance would be deleted, but it's not allowed !!\n"); \
					} \
				} \
				if (_line == -1) { \
				} \
				_autoPtr->release(_file, _line); \
				_autoPtr = NULL; \
			} \
		} \
		void LB_STDCALL setFile(char* __file) { \
			if (_file != NULL) { \
				delete [] _file; \
				_file = NULL; \
			} \
			if (__file != NULL) { \
				_file = new char [strlen(__file) + 1]; \
				strcpy(_file, __file); \
			} \
		} \
		void LB_STDCALL setLine(int __line) { \
			_line = __line; \
		} \
		\
		interface* LB_STDCALL getPtr() const { return _autoPtr; } \
		void LB_STDCALL resetPtr() { \
			_autoPtr = NULL; \
		} \
		void LB_STDCALL setPtr(interface*& source) { \
			if (_autoPtr != NULL) { \
				_CL_LOG << "Error: UAP object still initialized!" LOG_ \
			} \
			_autoPtr = source; \
		} \
		\
		interface& LB_STDCALL operator * () { \
		return *_autoPtr; } \
		interface* LB_STDCALL operator -> () const { \
			if (_autoPtr == NULL) { \
			} \
			return _autoPtr; \
		} \
		interface* LB_STDCALL operator -> () { \
			if ((initialized == false) && (_autoPtr != NULL) && (_autoPtr->getClassName() != NULL)) { \
				char* className = _autoPtr->getClassName(); \
				int len = strlen(className)+1; \
				initialized = true; \
				if (attachedClassName != NULL) free(attachedClassName); \
				attachedClassName = (char*) malloc(len); \
				attachedClassName[0] = 0; \
			        strcpy(attachedClassName, className); \
			} \
			return _autoPtr; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator++(int) { \
			interface* temp = NULL; \
			_autoPtr->queryInterface(#interface, (void**) &temp, file, line); \
			return *this; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator--(int) { \
			interface* temp = NULL; \
			if (_autoPtr->release(file, line) == ERR_RELEASED) _autoPtr = NULL; \
			return *this; \
		} \
		interface ** LB_STDCALL operator & () { \
			return &_autoPtr; \
		} \
		\
		UAP##Unknown_Reference& LB_STDCALL operator = (interface* autoPtr) { \
			if (_autoPtr != NULL) { \
				_autoPtr->release(file, line); \
			} \
			_autoPtr = autoPtr; \
			if (attachedClassName) { \
				free(attachedClassName); \
			} \
			if ((autoPtr != NULL) && (autoPtr->getClassName() != NULL)) \
				attachedClassName = my_strdup(autoPtr->getClassName()); \
			else \
				attachedClassName = my_strdup(""); \
			return *this; \
		} \
		int LB_STDCALL operator == (const interface* b) const { \
			return _autoPtr == b; \
		} \
		int LB_STDCALL operator != (const interface* b) const { \
			return _autoPtr != b; \
		} \
		void LB_STDCALL setDelete(int _allow) { allowDelete = _allow; } \
		\
		protected: \
	        interface* _autoPtr; \
	        int _line; \
	        char* _file; \
	        int allowDelete; \
	        bool initialized; \
	        char* attachedClassName; \
		}; \
	\
        interface* _UAP##Unknown_Reference; \
        UAP##Unknown_Reference Unknown_Reference;


/*...sbla \40\geht nicht\41\:0:*/
#ifdef bla
#define UNKNOWN_AUTO_PTR(interface, Unknown_Referene) \
	interface* Unknown_Referene = NULL; \
	UAP UAP##Unknown_Referene((lb_I_Unknown**) &Unknown_Referene);
#endif
/*...e*/
/*...e*/

#ifdef bla
/*...sDebug AutoPointer:0:*/
/** \def DEBUG_UAP(interface, Unknown_Reference, file, line)
 * \brief An automatic pointer implementation via macro. Debug version.
 */

#define DEBUG_UAP(interface, Unknown_Reference, file, line) \
		class UAP##Unknown_Reference { \
\
		private: \
		UAP##Unknown_Reference(UAP##Unknown_Reference& from) { \
		} \
		public: \
	        UAP##Unknown_Reference() { \
	        	_autoPtr = NULL; \
	        	_line = -1; \
	        	_file = NULL; \
	        	allowDelete = 1; \
		} \
		UAP##Unknown_Reference(const UAP##Unknown_Reference& _ref) { \
	        	_file = NULL; \
		        if (_ref._file) { \
		                _file = new char [strlen(_ref._file) + 1]; \
		                _file = strcpy(_file, _ref._file); \
		        } \
		        _line = _ref._line; \
		} \
		void operator=(const UAP##Unknown_Reference& _ref) { \
		        if (_file != NULL) { \
		                delete [] _file; \
		                if (_ref._file) { \
		                        _file = new char [strlen(_ref._file) + 1]; \
		                        _file = strcpy(_file, _ref._file); \
		                } \
		        } \
		        _line = _ref._line; \
		} \
		\
		virtual ~UAP##Unknown_Reference() { \
			_CL_LOG << "UAP destructor ~UAP" << #Unknown_Reference << "() at " << _file << " called" LOG_ \
			if (_autoPtr != NULL) { \
				if (allowDelete != 1) { \
					if (_autoPtr->deleteState() == 1) { \
						_CL_LOG << "Error: Instance would be deleted, but it's not allowed !!" LOG_ \
					} \
				} \
				if (_line == -1) { \
					_CL_LOG << "Warning: No reference has been taken in " << #Unknown_Reference << " at " << _line << " (UAP is in " << file << " at " << line LOG_ \
				} \
				_autoPtr->release(_file, _line); \
				if (_file) delete [] _file; \
			} \
			_CL_VERBOSE << "UAP destructor ~UAP" << #Unknown_Reference << "() ready" LOG_ \
		} \
		void LB_STDCALL setFile(char* __file) { \
			if (_file != NULL) { \
				delete [] _file; \
				_file = NULL; \
			} \
			if (__file != NULL) { \
				_file = new char [strlen(__file) + 1]; \
				_file = strcpy(_file, __file); \
			} \
		} \
		void LB_STDCALL setLine(int __line) { \
			_line = __line; \
		} \
		\
		interface* LB_STDCALL getPtr() const { return _autoPtr; } \
		void LB_STDCALL setPtr(interface*& source) { \
			if (_autoPtr != NULL) { \
				_CL_LOG << "Error: UAP object still initialized!" LOG_ \
			} \
			_autoPtr = source; \
		} \
		\
		interface& LB_STDCALL operator * () { \
		_LOG << "Warning: Using reference to UAP pointer in " << file << " at " <<  line LOG_ \
		return *_autoPtr; } \
		interface* LB_STDCALL operator -> () const { \
			if (_autoPtr == NULL) { \
				_CL_LOG << "Error: UAP pointer (" << #Unknown_Reference << ") for interface " << #interface << " is NULL!" LOG_ \
			} \
			return _autoPtr; \
		} \
		interface* LB_STDCALL operator -> () { \
			if (_autoPtr == NULL) { \
				_CL_LOG << "Error: UAP pointer (" << #Unknown_Reference << ") for interface " << #interface << " is NULL!" LOG_ \
			} \
			return _autoPtr; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator++(int) { \
			interface* temp = NULL; \
			_autoPtr->queryInterface(#interface, (void**) &temp, file, line); \
			return *this; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator--(int) { \
			interface* temp = NULL; \
			if (_autoPtr->release(file, line) == ERR_RELEASED) _autoPtr = NULL; \
			return *this; \
		} \
		interface ** LB_STDCALL operator & () { \
			return &_autoPtr; \
		} \
		\
		UAP##Unknown_Reference& LB_STDCALL operator = (interface* autoPtr) { \
			_autoPtr = autoPtr; \
			return *this; \
		} \
		int LB_STDCALL operator == (const interface* b) const { \
			return _autoPtr == b; \
		} \
		int LB_STDCALL operator != (const interface* b) const { \
			return _autoPtr != b; \
		} \
		void LB_STDCALL setDelete(int _allow) { allowDelete = _allow; } \
		\
		protected: \
	        interface* _autoPtr; \
	        int _line; \
	        char* _file; \
	        int allowDelete; \
		}; \
	\
        interface* _UAP##Unknown_Reference; \
        UAP##Unknown_Reference Unknown_Reference;


/*...sbla \40\geht nicht\41\:0:*/
#ifdef bla
#define UNKNOWN_AUTO_PTR(interface, Unknown_Referene) \
	interface* Unknown_Referene = NULL; \
	UAP UAP##Unknown_Referene((lb_I_Unknown**) &Unknown_Referene);
#endif
/*...e*/
/*...e*/
#endif

/*...sREQUEST Use this for a predefined UAP\46\:0:*/
// Use this for a predefined UAP. It will automatically deleted, if scope is gone.

/** \def REQUEST(mm, interface, variable)
 *  \brief Requester macro for getting an instance of given interface.
 *
 *  Makes it simpler to instantiate any kint of object.
 */

#define REQUEST(mm, interface, variable) \
  	UAP(lb_I_Unknown, uk##variable, __FILE__, __LINE__) \
  	mm->request(#interface, &uk##variable); \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__); \
	uk##variable.setFile(__FILE__); \
	uk##variable.setLine(__LINE__);


/** \def DEBUG_REQUEST(mm, interface, variable)
 *  \brief Requester macro for getting an instance of given interface.
 *  Makes it simpler to instantiate any kint of object. Debug version.
 */

#define DEBUG_REQUEST(mm, interface, variable) \
  	UAP(lb_I_Unknown, uk##variable, __FILE__, __LINE__) \
	printf("Step 1\n"); \
  	mm->request(#interface, &uk##variable); \
	printf("Step 2\n"); \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
	printf("Step 3\n"); \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__); \
	printf("Step 4\n"); \
	uk##variable.setFile(__FILE__); \
	printf("Step 5\n"); \
	uk##variable.setLine(__LINE__);

/*...e*/

/*...sUAP_REQUEST Use this for an stack like environment\46\:0:*/
// Use this for an stack like environment. It will automatically deleted, if scope is gone.

/** \def UAP_REQUEST(mm, interface, variable)
 *  \brief Variable and instantiation of any interface.
 *  This is usefull in functions, if the object should automatically
 *  destroyed, if the scope is left.
 */

#define UAP_REQUEST(mm, interface, variable) \
  	UAP(lb_I_Unknown, uk##variable, __FILE__, __LINE__) \
  	if (mm->request(#interface, &uk##variable) == ERR_MODULE_NO_INTERFACE) _CL_LOG << "Error: Interface not defined" LOG_ \
  	UAP(interface, variable, __FILE__, __LINE__) \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__);

/*...e*/

/*...sSTATIC_REQUEST\40\mm\44\ interface\44\ variable\41\:0:*/
/** \def STATIC_REQUEST(mm, interface, variable)
 *  \brief Non automatic destroying variant of UAP_REQUEST. This could be used to return the created instance over their interface.
 */
#define STATIC_REQUEST(mm, interface, variable) \
  	lb_I_Unknown* uk##variable; \
  	mm->request(#interface, &uk##variable); \
  	_CL_LOG << "STATIC_REQUEST: Have an instance" LOG_ \
  	interface* variable; \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
  	_CL_LOG << "STATIC_REQUEST: Set module manager" LOG_ \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__);

/*...e*/

/*...sDECLARE_LB_UNKNOWN\40\\41\:0:*/
/** \def DECLARE_LB_UNKNOWN() To be used in any interface implementation.
 *  This has to be used for each class definition, when deriving from lb_I_Unknown.
 */

 
 
#define DECLARE_LB_UNKNOWN() \
private: \
	UAP(lb_I_Module, manager, __FILE__, __LINE__) \
	int ref; \
	lb_I_Unknown* data; \
	int debug_macro; \
	int further_lock; \
	volatile int instance_counted; \
	miniString lastQIFile; \
	int        lastQILine; \
	miniString lastSMFile; \
	int        lastSMLine; \
protected: \
public: \
	virtual void 		LB_STDCALL setFurtherLock(int state) { \
	    further_lock = state; \
	} \
	virtual void 		LB_STDCALL setModuleManager(lb_I_Module* m, char* file, int line); \
	virtual lb_I_Module*    LB_STDCALL getModuleManager(); \
	virtual void 		LB_STDCALL resetRefcount(); \
	virtual void 		LB_STDCALL setDebug(int i = 1) { debug_macro = i; } \
	virtual lbErrCodes 	LB_STDCALL release(char* file, int line); \
	virtual char* 		LB_STDCALL getClassName(); \
	virtual char*           LB_STDCALL getCreationLoc() const; \
	virtual int 		LB_STDCALL deleteState(); \
	virtual char* 		LB_STDCALL _queryInterface(char* name, void** unknown, char* file, int line); \
	virtual lbErrCodes 	LB_STDCALL queryInterface(char* name, void** unknown, char* file, int line); \
	virtual lb_I_Unknown* 	LB_STDCALL clone(char* file, int line) const; \
	virtual lbErrCodes 	LB_STDCALL setData(lb_I_Unknown* u); \
	virtual int 		LB_STDCALL getRefCount() { return ref; }

/*...e*/

/*...sBEGIN_IMPLEMENT_LB_UNKNOWN:0:*/
/** \def BEGIN_IMPLEMENT_LB_UNKNOWN Implements the memberfunctions of lb_I_Unknown.
 *  This must be used to begin the interface declaration of your class.
 *  It implements the mechanisms of the component system.
 */

#define BEGIN_IMPLEMENT_LB_UNKNOWN(classname) \
char* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
char* LB_STDCALL classname::_queryInterface(char* name, void** unknown, char* file, int line) { \
	char* ID = new char[strlen(name)+strlen(#classname)+strlen(file)+1]; \
	ID[0] = 0; \
	strcat(ID, name); \
	strcat(ID, #classname); \
	strcat(ID, file); \
	lbErrCodes err = ERR_NONE; \
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) { \
		_CL_LOG <<"Error: queryInterface failed (in _queryInterface)!" LOG_ \
		return ""; \
	} \
	\
	return ID; \
} \
lb_I_Module* LB_STDCALL classname::getModuleManager() { \
		lbErrCodes err = ERR_NONE; \
		UAP(lb_I_Module, _mm, __FILE__, __LINE__) \
		if (manager == NULL) { \
			_CL_LOG << "Error: Can't return module manager. Call setModuleManager(...) on me first!" LOG_ \
			return NULL; \
		} \
		QI(manager, lb_I_Module, _mm, __FILE__, __LINE__) \
		return _mm.getPtr(); \
} \
\
void LB_STDCALL classname::setModuleManager(lb_I_Module* m, char* file, int line) { \
	lastSMFile.set(file); \
	lastSMLine = line; \
	if (m == NULL) { \
		_CL_LOG << "Error: Set module manager with a NULL pointer in " << #classname << " while setModuleManager(...)!" LOG_ \
		return; \
	} \
	\
	further_lock = 0; \
	if (m != manager.getPtr()) { \
	    if (m != NULL) m->queryInterface("lb_I_Module", (void**) &manager, file, line); \
	} \
	manager.setLine(__LINE__); \
	manager.setFile(__FILE__); \
	\
	\
	if (manager != NULL) { \
		char *datei = strrchr(file, '\\'); \
		if (datei == NULL) \
			datei = file; \
		else \
			datei++; \
		m->notify_create(this, #classname, datei, line); \
	} else { \
		_CL_LOG << "Error: Query interface failed for manager in " << #classname << " while setModuleManager(...)!" LOG_ \
	} \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = STARTREF; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == STARTREF) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() const { \
	char buf[20] = ""; \
	sprintf(buf, "%p", (void*) this); \
	if (manager != NULL) return manager->getCreationLoc(buf); \
	return strdup("Have no manager - location can't be found"); \
} \
lbErrCodes LB_STDCALL classname::release(char* file, int line) { \
	if (TRMemValidate(this)) { \
	_CL_VERBOSE << #classname << "::release(" << __FILE__ << ", " << line << ") with ref = " << ref << " called." LOG_ \
	ref--; \
	char ptr[20] = ""; \
	sprintf(ptr, "%p", this); \
	if (((lb_I_Unknown*) manager.getPtr() == (lb_I_Unknown*) this) && (getRefCount() == STARTREF+1)) { \
		manager--; \
	} \
        if (manager != NULL) { \
        	manager->notify_release(this, #classname, file, line); \
        } \
	\
        if (ref == STARTREF) { \
        	if (manager != NULL) { \
        		if (manager->can_delete(this, #classname) == 1)	{ \
        			manager->notify_destroy(this, #classname, file, line); \
        			\
        			if (instance_counted == 112233) { \
        				InstanceCount(-1); \
        			} else { \
        				_CL_LOG << "There may be a problem with the instance count system !" LOG_ \
        			} \
        			_CL_VERBOSE << "Delete instance '" << #classname << "'" LOG_ \
        			delete this; \
        			_CL_VERBOSE << "Deleted" LOG_ \
        			return ERR_RELEASED; \
        		} \
        		else { \
        			printf("Error: Instance %s has been deleted prior!\n", #classname); \
        			_CL_LOG << "Error: Instance has been deleted prior!" LOG_ \
        		} \
        	} \
        	return ERR_NONE; \
        } \
        if (ref < STARTREF) { \
        	_CL_LOG << "Error: Reference count of instance " << ptr << " in last query interface " << \
        	lastQIFile.get() << " at " << lastQILine << " and in last setModuleManager in " << \
        	lastSMFile.get() << " at " << lastSMLine << \
        	" of object type " << #classname << " is less than " << STARTREF << " (" << ref << ") !!!" LOG_ \
        	return ERR_REFERENCE_COUNTING; \
        } \
        } else { \
        	printf("Error: Instance %p of object type %s was deleted prior !!!", this, #classname); \
        } \
        return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(char* file, int line) const { \
\
	classname* cloned = new classname(); \
	cloned->setDebug(0); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	cloned->setFurtherLock(0); \
	if (manager == NULL) { \
		_CL_LOG << #classname << "::clone() can't be used because manager is a NULL pointer!" LOG_ \
	} \
	cloned->setModuleManager(manager.getPtr(), file, line); \
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting interface" LOG_ \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	if (manager != NULL) { \
		lb_I_Unknown* that = (lb_I_Unknown*) cloned; \
	        manager->notify_add(that, cloned->getClassName(), file, line); \
	} \
        else \
		if (debug_macro == 1) { \
                	_CL_LOG << "Module manager was not set!" LOG_ \
		} \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting unknown interface of cloned object" LOG_ \
	} \
\
	if (uk->getRefCount() > 1) { \
		_CL_LOG << "Cloned object has %d references" << uk->getRefCount() LOG_ \
	} \
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char* name, void** unknown, char* file, int line) { \
	char buf[1000] = ""; \
	char _classname[100] = #classname; \
	lastQIFile.set(file); \
	lastQILine = line; \
	_CL_VERBOSE << #classname << "::queryInterface(" << file << ", " << line << ") with ref = " << ref << " called." LOG_ \
	\
	if (instance_counted != 112233) { \
		instance_counted = 112233; \
		InstanceCount(1); \
	} \
	\
	if (further_lock == 1) { \
		_CL_LOG <<"Error: Object has been locked due to missing module manager (call setModuleManager(...) on me first)!" LOG_ \
		return ERR_STATE_FURTHER_LOCK; \
	} else { \
	} \
	if (unknown == NULL) { \
		_CL_LOG << "Error: Got NULL pointer reference while queryInterface() called for " << \
		name << " ! Did you coded it this way: (void**) &variable ?" LOG_ \
	} \
\
        if (strcmp(name, "lb_I_Unknown") == 0) { \
        	if (ref < STARTREF) { \
        		_CL_LOG << "Reference count error in queryInterface (" #classname ")" LOG_ \
        	} \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                if (manager != NULL) { \
                	lb_I_Unknown* that = (lb_I_Unknown*) this; \
		        manager->notify_add(that, _classname, file, line); \
		} \
		else { \
	        	setFurtherLock(1); \
	        	_CL_LOG << "Lock object due to missing manager!" LOG_ \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

/*...e*/
/*...sBEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN:0:*/
/** \def BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN Implements the memberfunctions of lb_I_Unknown.
 *  This must be used to begin the interface declaration of your class.
 *  It implements the mechanisms of the component system.
 *
 *  This could be used, if only one instance should be used per process.
 */

#define BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(classname) \
char* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
char* LB_STDCALL classname::_queryInterface(char* name, void** unknown, char* file, int line) { \
	char* ID = new char[strlen(name)+strlen(#classname)+strlen(file)+1]; \
	ID[0] = 0; \
	strcat(ID, name); \
	strcat(ID, #classname); \
	strcat(ID, file); \
	lbErrCodes err = ERR_NONE; \
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) { \
		_CL_LOG <<"Error: queryInterface failed (in _queryInterface)!" LOG_ \
		return ""; \
	} \
	\
	return ID; \
} \
lb_I_Module* LB_STDCALL classname::getModuleManager() { \
		lbErrCodes err = ERR_NONE; \
		UAP(lb_I_Module, _mm, __FILE__, __LINE__) \
		if (manager == NULL) { \
			_CL_LOG << "Error: Can't return module manager. Call setModuleManager(...) on me first!" LOG_ \
			return NULL; \
		} \
		QI(manager, lb_I_Module, _mm, __FILE__, __LINE__) \
		return _mm.getPtr(); \
} \
\
void LB_STDCALL classname::setModuleManager(lb_I_Module* m, char* file, int line) { \
	if (m == NULL) { \
		_CL_LOG << "Error: Set module manager with a NULL pointer in " << #classname << " while setModuleManager(...)!" LOG_ \
		return; \
	} \
	\
	further_lock = 0; \
	if (debug_macro == 1) { \
		_CL_LOG << "Warning: setModuleManager() must be enhanced by module manager use" LOG_ \
	} \
	if (m != manager.getPtr()) { \
	    if (m != NULL) m->queryInterface("lb_I_Module", (void**) &manager, file, line); \
	} \
	manager.setLine(__LINE__); \
	manager.setFile(__FILE__); \
	\
	if (manager != NULL) { \
		char *datei = strrchr(file, '\\'); \
		if (datei == NULL) \
			datei = file; \
		else \
			datei++; \
		manager->notify_create(this, #classname, datei, line); \
	} else { \
		_CL_LOG << "Error: Query interface failed for manager in " << #classname << " while setModuleManager(...)!" LOG_ \
	} \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = STARTREF; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == STARTREF) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() const { \
	char buf[20] = ""; \
	sprintf(buf, "%p", (void*) this); \
	if (manager != NULL) return manager->getCreationLoc(buf); \
	return strdup("Have no manager - location can't be found"); \
} \
lbErrCodes LB_STDCALL classname::release(char* file, int line) { \
	if (TRMemValidate(this)) { \
        ref--; \
	char ptr[20] = ""; \
	sprintf(ptr, "%p", this); \
        if (manager != NULL) { \
        	manager->notify_release(this, #classname, file, line); \
        } \
	\
        if (ref == STARTREF) { \
        	if (manager != NULL) { \
        		if (manager->can_delete(this, #classname) == 1)	{ \
        			manager->notify_destroy(this, #classname, file, line); \
        			printf("WARNING: Refcount goes to %d. Singleton instances can't be destroyed by release.\n", STARTREF); \
        			ref++; \
        			return ERR_RELEASED; \
        		} \
        		else \
        			_CL_LOG << "Error: Instance has been deleted prior!" LOG_ \
        	} \
        	return ERR_NONE; \
        } \
        if (ref < STARTREF) { \
        	printf("Error: Reference count of instance %p of object type %s is less than %d (%d) !!!", ptr, #classname, STARTREF, ref); \
        	return ERR_REFERENCE_COUNTING; \
        } \
        } else { \
        	printf("Error: Instance %p of object type %s was deleted prior !!!", this, #classname); \
        } \
        return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(char* file, int line) const { \
\
	classname* cloned = new classname(); \
	cloned->setDebug(0); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	cloned->setFurtherLock(0); \
	if (manager == NULL) _CL_LOG << #classname << "::clone() can't be used because manager is a NULL pointer!" LOG_ \
	cloned->setModuleManager(manager.getPtr(), file, line); \
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting interface" LOG_ \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	if (manager != NULL) { \
		lb_I_Unknown* that = (lb_I_Unknown*) cloned; \
	        manager->notify_add(that, cloned->getClassName(), file, line); \
	} \
        else \
		if (debug_macro == 1) { \
                	_CL_LOG << "Module manager was not set!" LOG_ \
		} \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting unknown interface of cloned object" LOG_ \
	} \
\
	if (uk->getRefCount() > 1) { \
		_CL_LOG << "Cloned object has %d references" << uk->getRefCount() LOG_ \
	} \
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char* name, void** unknown, char* file, int line) { \
	char buf[1000] = ""; \
	char _classname[100] = #classname; \
	if (further_lock == 1) { \
		_CL_LOG <<"Error: Object has been locked due to missing module manager (call setModuleManager(...) on me first)!" LOG_ \
		return ERR_STATE_FURTHER_LOCK; \
	} \
	if (unknown == NULL) { \
		_CL_LOG << "Error: Got NULL pointer reference while queryInterface() called for " << \
		name << " ! Did you coded it this way: (void**) &variable ?" LOG_ \
	} \
\
        if (strcmp(name, "lb_I_Unknown") == 0) { \
        	if (ref < STARTREF) { \
        		_CL_LOG << "Reference count error in queryInterface (" #classname ")" LOG_ \
        	} \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                if (manager != NULL) { \
                	lb_I_Unknown* that = (lb_I_Unknown*) this; \
		        manager->notify_add(that, _classname, file, line); \
		} \
		else { \
	        	setFurtherLock(1); \
	        	_CL_LOG << "Lock object due to missing manager!" LOG_ \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

/*...e*/
	
/** \def ADD_INTERFACE Adds support for a specific interface.
 *  This could be used multiple times for having more than one interface.
 */
#define ADD_INTERFACE(interfaceName) \
	buf[0] = 0; \
\
        if (strcmp(name, #interfaceName) == 0) { \
                ref++; \
                *unknown = (interfaceName*) this; \
                if (manager != NULL) { \
                	interfaceName* that = (interfaceName*) this; \
                	lb_I_Unknown* uk = (lb_I_Unknown*) this; \
                	manager->notify_add(uk, _classname, file, line); \
                } \
		else { \
		        setFurtherLock(1); \
		        _CL_LOG << "Error: QueryInterface can't add a reference. No manager. File: " << \
		        file << ", Line: " << line LOG_ \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

#define END_IMPLEMENT_LB_UNKNOWN() \
	_CL_LOG << "Error: Requested interface '" << name << "' not found! File: " << file << " Line: " << line LOG_ \
	return ERR_NO_INTERFACE; \
}

/*...e*/

/*...sstandard functor:0:*/
/**
 * Base of all instances - the functor
 */

extern "C" { 
typedef lbErrCodes (LB_FUNCTORCALL *T_pLB_GET_UNKNOWN_INSTANCE) (lb_I_Unknown**, lb_I_Module* m, char* file, int line);
}

/** \def DECLARE_FUNCTOR Declares a functor in a header file.
 * This must be used once per class.
 *
 * Idea: To ensure, that the object gets the module manager, it is locked until
 * setModuleManager is called with a correct value.
 * queryInterface can at first time do it's work, store the data, that has to
 * be stored in module manager and lock the instance for further use.
 */

#define DECLARE_FUNCTOR(name) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line); \
}

/** \def IMPLEMENT_FUNCTOR Implements the functor in a cpp file.
 * Use this once per class.
 */
#define IMPLEMENT_FUNCTOR(name, clsname) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line) { \
\
	lbErrCodes err = ERR_NONE; \
	clsname* instance = new clsname(); \
        *uk = NULL; \
        instance->setFurtherLock(0); \
        if (m != NULL) { \
        	instance->setModuleManager(m, __FILE__, __LINE__); \
        } else { \
        	_CL_LOG << "Error: Functor gets no manager. This is only possible for a manager it self." LOG_ \
        } \
        \
        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
                _CL_LOG << "Failed to create unknown reference to instance of " << \
                #clsname << ". Errcode is " << err LOG_ \
                if (err == ERR_STATE_FURTHER_LOCK) { \
                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
                	return err; \
                } \
                return ERR_FUNCTOR; \
        } \
\
        return ERR_NONE; \
} \
}

/** \def DECLARE_SINGLETON_FUNCTOR Declares a singleton functor in a header file.
 * This must be used once per class.
 */
#define DECLARE_SINGLETON_FUNCTOR(name) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line); \
} 

/** \def IMPLEMENT_SINGLETON_FUNCTOR Implements the singleton functor in a cpp file.
 * Use this once per class.
 */
#define IMPLEMENT_SINGLETON_FUNCTOR(name, clsname) \
class singletonHolder_##name { \
public: \
	singletonHolder_##name() { \
		singleton = NULL; \
	} \
	virtual ~singletonHolder_##name() { \
		if (singleton != NULL) { \
			if (TRMemValidate(singleton)) \
				delete singleton; \
			else \
				printf("ERROR: Sinleton object has been deleted prior!\n"); \ 
		} else { \
			printf("Warning: singletonHolder_" #name " has an invalid pointer.\n"); \
		} \
	} \
	void set(clsname* _singleton) { \
		lb_I_Unknown* temp; \
		lbErrCodes err = ERR_NONE; \
		err = _singleton->queryInterface("lb_I_Unknown", (void**) &temp, __FILE__, __LINE__); \
		singleton = _singleton; \
	} \
	\
	clsname* get() { \
		return singleton; \
	} \
	\
	clsname* singleton; \
}; \
\
singletonHolder_##name singleton_##name; \
\
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line) { \
\
	lbErrCodes err = ERR_NONE; \
	if (singleton_##name.get() == NULL) { \
	        clsname* instance = new clsname(); \
	        *uk = NULL; \
	        char buf[100] = ""; \
	        track_Object(instance, "IMPLEMENT_SINGLETON_FUNCTOR - Instantiating"); \
	        \
	        instance->setFurtherLock(0); \
	        if (m != NULL) { \
	        	instance->setModuleManager(m, __FILE__, __LINE__); \
	        } else { \
	        	if (strcmp(instance->getClassName(), "lbModule") != 0) { \
	        		_CL_LOG << "Error: Functor gets no manager. This is only possible for a manager it self." LOG_ \
	        	} \
	        } \
	        \
	        singleton_##name.set(instance); \
	        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
	                _CL_LOG << "Failed to create unknown reference to singleton instance of " << \
	                #clsname << ". Errcode is " << err LOG_ \
	                if (err == ERR_STATE_FURTHER_LOCK) { \
	                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
	                	return err; \
	                } \
	                return ERR_FUNCTOR; \
	        } \
        } else { \
	        track_Object(singleton_##name.get(), "IMPLEMENT_SINGLETON_FUNCTOR - queryInterface()"); \
	        if ((err = singleton_##name.get()->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
	                _CL_LOG << "Failed to create unknown reference to singleton instance of " << \
	                #clsname << ". Errcode is " << err LOG_ \
	                if (err == ERR_STATE_FURTHER_LOCK) { \
	                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
	                	return err; \
	                } \
	                return ERR_FUNCTOR; \
	        } \
        } \
\
        return ERR_NONE; \
} \
}
/*...e*/

/*...sclass lb_I_Reference:0:*/
/**
 * \brief This should be a class to be used as a 'smart' pointer.
 *
 * Currently I use the UAP macros as smart pointer implementations.
 * The UAP solution has no base class. This would be one, but it would
 * bite it self indirectly into the whife.
 *
 * This is because UAP is a 'normal' class. It can't and shouldn't be created by the lbDMF system.
 *
 * If it could be created by REQUEST, the UAP_REQUEST macro - requesting an instance for a particular
 * interface - must also request the base class of it self to have the UAP class.
 */
class lb_I_Reference : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL set(lb_I_Unknown* r) = 0;
	virtual lbErrCodes LB_STDCALL get(lb_I_Unknown*& r) = 0;
};
/*...e*/

/*...sclass lb_I_gcManager:0:*/
/**
 * \brief An attempt to create garbage collection classes.
 */
class lb_I_gcManager {
protected:
	lb_I_gcManager() {}
	virtual ~lb_I_gcManager() {}
	
public:
	virtual lbErrCodes toTrash(lb_I_Unknown * inst) = 0;
};
/*...e*/

// What about exceptions ?

/*...sclass lb_I_Exception:0:*/
/**
 * \brief An attempt for exceptions.
 */
class lb_I_Exception {
public:
	virtual lbErrCodes getMessage(char*& msg) = 0;
};
/*...e*/
/*...sclass lb_I_ErrorDescription:0:*/
/**
 * \brief An attempt for error descriptions.
 */
class lb_I_ErrorDescription {// Every interface may produce errors
public:
	virtual lbErrCodes getLastError(char* description, int len) = 0;
};
/*...e*/


/*...sclass lb_I_Requestable:0:*/
/*...sdocu  lb_I_Requestable:0:*/
/**
 * \deprecated Have lb_I_EventHandler for this.
 *
 * lb_I_Requestable is intented to implement a class that can be called
 * for any requests. This may be the 'Meta' Application.
 * The Meta Application did not need to provide an interface for dispatching.
 * This is because, the client of Meta *must* not call any dispatchning -
 * members.
 */
/*...e*/
class lb_I_Requestable {
public:
	virtual lbErrCodes LB_STDCALL initialize() = 0;
	virtual lbErrCodes LB_STDCALL request(const char* request, lb_I_Unknown** result) = 0;
	virtual lbErrCodes LB_STDCALL uninitialize() = 0;
};
/*...e*/

/*...sclass lb_I_CallbackManager:0:*/
/** \brief An attempt for registering callbacks.
 */
class lb_I_CallbackManager {
public:
/*...sdocu:0:*/
	
	/**
	 * Implement this in your class implementing callback handling
	 */
	
	 
/*...e*/
	virtual lbErrCodes addCallbackHandler(const char* handlername, lbMemberCallback cbFn) = 0;
	virtual lbErrCodes delCallbackHandler(const char* handlername) = 0;
};
/*...e*/
/*...sclass lb_I_CallbackDispatcher dispatches over names:0:*/
/** \brief An attempt to dispatch a request.
 */
class lb_I_CallbackDispatcher {
public:
	virtual lbErrCodes dispatch(const char* request, lb_I_Transfer_Data& result) = 0;
};
/*...e*/
/*...sclass lb_I_CallbackTarget:0:*/
/** \brief An attempt to let classes register their callbacks.
 */
class lb_I_CallbackTarget {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in the derived class for your functions
	 * to be called back.
	 */
	  
/*...e*/
	virtual lbErrCodes registerCallbacks() = 0; 
};
/*...e*/

/*...sdocu:0:*/
/**
 * This interface must be used to register or deregister
 * protocol callbacks, if an implementation is a callback target.
 */

/*...e*/
/*...sclass lb_I_ProtocolManager:0:*/
/** \brief An attempt for a protocol based callback manager.
 */
class lb_I_ProtocolManager {
public:
/*...sdocu:0:*/
	
	/**
	 * Implement this in your class implementing callback handling
	 */
	
	 
/*...e*/
	virtual lbErrCodes addProtocolHandler(const char* handlername, lbProtocolCallback cbFn) = 0;
	virtual lbErrCodes delProtocolHandler(const char* handlername) = 0;
};
/*...e*/
/*...sclass lb_I_ProtocolDispatcher dispatches over protocol haeder:0:*/
/** \brief An attempt for a protocol based dispatcher.
 */
class lb_I_ProtocolDispatcher {
public:
	virtual lbErrCodes dispatch(const lb_I_Transfer_Data& request, lb_I_Transfer_Data& result) = 0;
};
/*...e*/
/*...sdocu:0:*/
/**
 * This is used by a server instance, that implements some protocols.
 */
/*...e*/
/*...sclass lb_I_ProtocolTarget:0:*/
/** \brief An attempt for a protocol based callback handler.
 */
class lb_I_ProtocolTarget {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in the derived class for your functions
	 * to be called back.
	 */
	  
/*...e*/
	virtual lbErrCodes registerProtocols() = 0; 
};
/*...e*/

/*...sclass lb_I_EventConnector:0:*/
/** \brief ???
 */
class lb_I_EventConnector {
public:
	virtual lbErrCodes LB_STDCALL getConnectorEventList(lb_I_Container* c) = 0;
};
/*...e*/
/*...sclass lb_I_EventSource:0:*/
/// A Menu ??
class lb_I_EventSource {
public:
	virtual lbErrCodes LB_STDCALL getSourceEventList(lb_I_Container* c) = 0;
};
/*...e*/
/*...sclass lb_I_EventSink:0:*/
/// A Frame ??
class lb_I_EventSink {
public:
	virtual lb_I_EventCallback LB_STDCALL getEventFunction(char* name) = 0;
	virtual lbErrCodes LB_STDCALL Connect(char* evName, lb_I_EventCallback evFn) = 0;
	virtual lbErrCodes LB_STDCALL getSinkEventList(lb_I_Container* c) = 0;

	/**
	 * The events are compareable, that is, the connector says the same events
	 * than the sink. If that is so, then the registration will succeed.
	 * 
	 * But what is about the event source. When and where are these created ?
	 */
	virtual lbErrCodes LB_STDCALL registerEvents(lb_I_EventConnector* object) = 0;
	
	/**
	 * This function will be called in the scope of application initializion.
	 * That is in an instance of lb_I_EventConnector. This instance says wich
	 * events should be implemented. This events are registered before and then
	 * the event source can be made.
	 */
	virtual lbErrCodes LB_STDCALL createEventsource(lb_I_EventConnector* object) = 0;
	virtual lb_I_Unknown* LB_STDCALL getEventsource(lb_I_EventConnector* object) = 0;	
	
};
/*...e*/

/*...sclass lb_I_EventMapper:0:*/
/// ???
class lb_I_EventMapper : public lb_I_Unknown {
public:
	/**
	 * If handler is NULL, then the event manager knows, that the requesting
	 * instance has a dispatcher and therefore handles it self. You must register
	 * the dispatcher after all requested id's for your events.
	 */
	virtual lbErrCodes LB_STDCALL setEvent(char* name, lbEvHandler handler = NULL) = 0;
	/**
	 * Get the id back.
	 */
	virtual int LB_STDCALL getID() = 0;

protected:
	virtual char* LB_STDCALL getName() = 0;
	virtual void LB_STDCALL setID(int id) = 0;
	
	friend class lb_I_EventManager;
};
/*...e*/

//	virtual lbErrCodes LB_STDCALL setDiapatcher(lb_I_Dispatcher* disp) = 0;
//	virtual lb_I_Dispatcher* LB_STDCALL getDispatcher() = 0;
	
/*...sclass lb_I_EventManager:0:*/
/**
 * \brief An event ID manager. It reserves ID's for symbolic event names.
 * 
 * This is used to create event ID numbers, that - for sample - are used in my
 * GUI sample application. wxWidgets usually defines those ID's per define. Here,
 * I am capable to manage those ID's dynamically.
 *
 * You are able to write a plugin module and insert menu entries dynamically to
 * the wx application and let the app resolve that event ID correctly to the module
 * by forwarding all those events to a OnDispatch handler. This handler forwards
 * the event to my own event handling mechanism.
 *
 * This does not interfer the two different mechanisms of wx and my own.
 *
 * \note A class of this interface must be singleton.
 */
class lb_I_EventManager : public lb_I_Unknown {
public:

	/**
	 * Register a symbolic event name and get back their ID.
	 * \param EvName The symbolic name of the event. This could be a #define EVENTXY "eventXY".
	 * \param EvNr The ID, generated inside of this implementation.
	 */
	virtual lbErrCodes LB_STDCALL registerEvent(char* EvName, int & EvNr) = 0;
	
	/**
	 * Get the ID of a registered symbolic event name. Parameters as above described.
	 */
	virtual lbErrCodes LB_STDCALL resolveEvent(char* EvName, int & evNr) = 0;

	virtual char* LB_STDCALL reverseEvent(int evNr) = 0;

protected:

	friend class lb_I_Dispatcher;
};
/*...e*/
/*...sclass lb_I_EvHandler:0:*/
/**
 * \brief An event handler entity.
 *
 * An event handler entity is an instance for a class, that has one or more event handlers.
 */
class lb_I_EvHandler : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler) = 0;
	virtual lbEvHandler LB_STDCALL getHandler() = 0;
	virtual lb_I_EventHandler* LB_STDCALL getHandlerInstance() = 0;
		
	virtual lbErrCodes LB_STDCALL call(lb_I_Unknown* evData, lb_I_Unknown** evResult) = 0; 
};
/*...e*/

/*...sclass lb_I_DispatchRequest:0:*/
/**
 * \brief An attempt to create a request packet, that could be predefined.
 *
 * Idea: You do not need to build up a more complex event every time. Predefine
 * it as a class and instantiate it over REQUEST or directly and use it later.
 */
class lb_I_DispatchRequest : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL setRequestName(char* name) = 0;
};
/*...e*/
/*...sclass lb_I_DispatchResponce:0:*/
/**
 * \brief An attempt to create a request packet response, that could be predefined.
 *
 * Idea: You do not need to build up a more complex response every time. Predefine
 * it as a class and instantiate it over REQUEST or directly at start time and use it later.
 */
class lb_I_DispatchResponse : public lb_I_Unknown {
public:
	virtual int LB_STDCALL isOk() = 0;
};
/*...e*/
/*...sclass lb_I_Dispatcher:0:*/
/**
 * \brief Dispatcher contains all registered event handlers.
 *
 * Dispatcher is used to hold all registered event handlers. If an event has been fired,
 * one of it's dispatch members are called to forward that event to the desired handler.
 */
class lb_I_Dispatcher : public lb_I_Unknown {
public:
	/**
	 * Set an event manager. Dispatcher stores the handlers per event ID's. It needs
	 * a manager, if it gets a symbolic event, to resolve the ID.
	 *
	 * \param EvManager The event manager.
	 */
	virtual lbErrCodes LB_STDCALL setEventManager(lb_I_EventManager* EvManager) = 0;
	
/*...sevent handler management:8:*/

	/**
	 * Register an event handler function under it's name. If the name is not registered, the
	 * function will fail. The dispatcher is not responsible for registering event names or id's.
	 */
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, char* EvName) = 0;
	
	/**
	 * Register an event handler function under it's id. If the id is not registered, the
	 * function will fail. The dispatcher is not responsible for registering event names or id's.
	 */
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr) = 0;
/*...e*/
	
/*...scascade management:8:*/
	/**
	 * Add a dispatcher, if it is not my self (singleton). This enables cascaded
	 * dispatching and complete replacement of a dispatcher.
	 *
	 * You could forward events to a separate dispatcher, if the main dispatcher
	 * does not contain the registered handler. So a group of handlers could be
	 * replaced by some contect of an application.
	 *
	 * Sample: Some event handlers goes to a remote host due to some extend.
	 * The separate dispatcher is build up and the remote handlers are also
	 * build up before replacing a local decentand.
	 */
	virtual lbErrCodes LB_STDCALL addDispatcher(lb_I_Dispatcher* disp) = 0;
	
	/**
	 * Delete a decentand dispatcher.
	 *
	 * \note You must implement thread savetiness in your replace code.
	 *
	 * \param disp Deprecated. Why holding more than one decentand dispatcher ?
	 */
	virtual lbErrCodes LB_STDCALL delDispatcher(lb_I_Dispatcher* disp) = 0;
/*...e*/

/*...sdispatching:8:*/
	/**
	 * Any dispatch function should provided with the information of what type to be dispatched.
	 * An input is required - possibly NULL.
	 * A result will be generated, if succeeded.
	 *
	 */
	virtual lbErrCodes LB_STDCALL dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;
	virtual lbErrCodes LB_STDCALL dispatch(char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;
	
	/**
	 * lb_I_DispatchRequest variant. Parameter contains all needed data for the dispatch request.
	 */
	virtual lb_I_DispatchResponse* LB_STDCALL dispatch(lb_I_DispatchRequest* req) = 0; 
/*...e*/
};
/*...e*/

/*...sclass lb_I_EventHandler:0:*/
/**
 * \brief An event handler class. It handles one or more events.
 *
 * The event handler registers all it's handlers by get a call of registerEventHandler.
 * It get's an external dispatcher, to don't need to provide it's own dispatcher.
 */
class lb_I_EventHandler {
public:
	/**
	 * Register all the handlers by this class to the given dispatcher.
	 */
	virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp) = 0;
};
/*...e*/

class lb_I_DatabaseForm;
class lb_I_GUI;
class lb_I_Form;
class lb_I_String;

/*...sclass lb_I_Frame:0:*/
/**
 * It seems, that this is the factory class for any GUI elements. It also knows about any instance.
 */
class lb_I_Frame :
public lb_I_Unknown
{
public:
	virtual lb_I_Unknown* LB_STDCALL createFrame() = 0;
//	virtual lbErrCodes registerEvent(char* evName, int evType, frame->getDispatcherFn())

};
/*...e*/
/*...sclass lb_I_MetaApplication:0:*/
/**
 * \brief Interface from a wrapper and lbDMF
 *
 * The meta application is an attempt to provide an interface for the
 * application developer. It hides the real framework like MFC or others
 * from the developer.
 */
class lb_I_MetaApplication : public lb_I_Unknown {
public:

	/**
	 * Set the graphical user interface instance that is the wrapper side.
	 */
	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* gui) = 0;

	virtual lbErrCodes LB_STDCALL setUserName(char* user) = 0;
	virtual lbErrCodes LB_STDCALL setApplicationName(char* app) = 0;
	
	/**
	 * Initialize the application module. Optionally, provide user and application name.
	 */
	virtual lbErrCodes LB_STDCALL Initialize(char* user = NULL, char* app = NULL) = 0;
	
	/**
	 * \brief Run the application
	 *
	 * This lets the GUI 'start' some threads in the background or run the app without
	 * a GUI.
	 */
	virtual lbErrCodes LB_STDCALL run() = 0;

	/**
	 * \brief Get the GUI instance.
	 */	
	virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** gui) = 0;

	virtual lbErrCodes LB_STDCALL getUserName(lb_I_String** user) = 0;
	virtual lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app) = 0;
	
	/**
	 * Get access to the main event manager, so all parts can initialize event handlers
	 * and then initialize Actors for still initialized event handlers.
	 */
	virtual lb_I_EventManager* getEVManager() = 0;


	virtual lbErrCodes LB_STDCALL loadApplication(char* user, char* app) = 0;

	/**
	 * Basic functions to be used for a UI application
	 */

	virtual lbErrCodes LB_STDCALL addMenuBar(char* name, char* after) = 0;
	virtual lbErrCodes LB_STDCALL addMenu(char* name) = 0;
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL) = 0;
	virtual lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) = 0;
	virtual lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) = 0;
	virtual lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) = 0;
};
/*...e*/

class lb_I_Plugin;
class lb_I_PluginImpl;
class lb_I_PluginModule;

/** \brief The plugin manager
 *
 * The plugin manager should handle automatic loading of exsisting plugins and optionally
 * unload plugins by a plugin management dialog.
 */
/*...sclass lb_I_PluginManager:0:*/
class lb_I_PluginManager : public lb_I_Unknown {
public:

	/** \brief Starts initializing plugins.
	 *
	 * This function reads out the plugin directory and tries to load
	 * it by the standard plugin module functor. If it exists, it will
	 * succeed. If not, the module will be ignored.
	 */
	virtual void LB_STDCALL initialize() = 0;

	/** \brief Unload plugins.
	 *
	 * Use this function to clean up all loaded plugin modules.
	 * This is nessesary due to dependencies of the modules and the
	 * order of system unload order of the plugins.
	 */
	virtual void LB_STDCALL unload() = 0;

	/** \brief Starts listing of plugins.
	 *
	 * As of lb_I_Container interface, this is similar to the beginning of
	 * enumerating its objects.
	 */
	virtual bool LB_STDCALL beginEnumPlugins() = 0;
	
	/** \brief Get the next plugin.
	 *
	 * Gets the next plugin handle instance. This does not
	 * load an instance of the plugin implementation. But it
	 * loads the module.
	 *
	 * To finally use the plugin, you must attach to it.
	 */
	virtual lb_I_Plugin* LB_STDCALL nextPlugin() = 0;

	/** \brief Find first matching plugin.
	 *
	 * This function searches for a plugin, that matches the match string.
	 *
	 * The match string could be a functor name, an interface name or partial of them.
	 * The order, in that this function will search is decided by the match string.
	 */
	virtual lb_I_Plugin* LB_STDCALL getFirstMatchingPlugin(char* match, char* _namespace) = 0;
	
	/** \brief Put in a plugin (via DnD as an example).
	 *
	 * Attach the plugin implementation to the plugin handle.
	 * After attaching the plugin, you will be able to init
	 * the plugin via the initialize() function.
	 */
	virtual bool LB_STDCALL attach(lb_I_PluginModule* toAttach) = 0;
	
	/** 
	 * Detach it. If it returns true, it could be destroyed or
	 * stored permanently for replacing with other implementation.
	 */
	virtual bool LB_STDCALL detach(lb_I_PluginModule* toAttach) = 0;
};
/*...e*/

/** \brief Plugin module
 *
 * The plugin module is a class per module, that should list all included plugins for one
 * module. This should be similar to the BEGIN_IMPLEMENT_UNKNOWN and ADD_INTERFACE macros.
 */
/*...sclass lb_I_PluginModule:0:*/
class lb_I_PluginModule : public lb_I_Unknown {
public:
	/**
	 * Set the name of the module. Typically the path and name to the shared library.
	 */
	 
	virtual void LB_STDCALL setModule(char* module) = 0; 

	/**
	 * Get the list of plugins for the current plugin module.
	 */
	virtual lb_I_Container* LB_STDCALL getPlugins() = 0;
	
	/**
	 * This function must be called once per instance of this
	 * module. It internally generates the list of plugins
	 * implemented in this module.
	 */
	virtual void LB_STDCALL initialize() = 0;

protected:
	/**
	 * Used internally in the macros to build the plugin list.
	 */
	virtual void LB_STDCALL enumPlugins() = 0;
};


#define DECLARE_PLUGINS() \
	virtual void LB_STDCALL setModule(char* module); \
	virtual lb_I_Container* LB_STDCALL getPlugins(); \
	virtual void LB_STDCALL enumPlugins(); \
	UAP(lb_I_Container, Plugins, __FILE__, __LINE__) \
	UAP(lb_I_String, _module, __FILE__, __LINE__)

#define BEGIN_PLUGINS(cls) \
\
void LB_STDCALL cls::setModule(char* module) { \
	_CL_LOG << #cls << "::setModule(" << module << ") called." LOG_ \
	if (_module == NULL) { \
		REQUEST(manager.getPtr(), lb_I_String, _module) \
	} \
	_module->setData(module); \
} \
lb_I_Container* cls::getPlugins() { \
	Plugins++; \
	return Plugins.getPtr(); \
} \
void LB_STDCALL cls::enumPlugins() { \
	lbErrCodes err = ERR_NONE; \
	REQUEST(manager.getPtr(), lb_I_Container, Plugins)

#define ADD_PLUGIN(plugin, namespace) \
	UAP_REQUEST(manager.getPtr(), lb_I_Plugin, P##plugin##namespace) \
	\
	P##plugin##namespace->setModule(_module->getData()); \
	P##plugin##namespace->setName(#plugin); \
	P##plugin##namespace->setNamespace(#namespace); \
	\
	UAP_REQUEST(manager.getPtr(), lb_I_String, s##plugin##namespace) \
	UAP(lb_I_KeyBase, Key##plugin##namespace, __FILE__, __LINE__) \
	UAP(lb_I_Unknown, ukPlugin##plugin##namespace, __FILE__, __LINE__) \
	\
	s##plugin##namespace->setData(#plugin); \
	QI(s##plugin##namespace, lb_I_KeyBase, Key##plugin##namespace, __FILE__, __LINE__) \
	QI(P##plugin##namespace, lb_I_Unknown, ukPlugin##plugin##namespace, __FILE__, __LINE__) \
	Plugins->insert(&ukPlugin##plugin##namespace, &Key##plugin##namespace); \
	\
	UAP(lb_I_Unknown, ukPl##plugin##namespace, __FILE__, __LINE__) \
	UAP(lb_I_Plugin, Pl##plugin##namespace, __FILE__, __LINE__) \
	ukPl##plugin##namespace = Plugins->getElement(&Key##plugin##namespace); \
	QI(ukPl##plugin##namespace, lb_I_Plugin, Pl##plugin##namespace, __FILE__, __LINE__) \
	Pl##plugin##namespace->setModule(_module->getData()); \
	Pl##plugin##namespace->setName(#plugin); \
	Pl##plugin##namespace->setNamespace(#namespace);


#define END_PLUGINS() }

/*...e*/

/**
 * \brief Interface for single plugin (forwarder). 
 *
 * This should be a wrapper to the plugin implementation.
 */
/*...sclass lb_I_Plugin:0:*/
class lb_I_Plugin : public lb_I_Unknown {
public:

	/** \brief Forwarder for initializion.
	 *
	 * Initialize the plugin. This function can only be called, if it has been
	 * attached by the plugin manager. If this hasn't been made, nothing happens.
	 *
	 * If the plugin is correctly set up, initialize can forward its call to the
	 * underlying plugin implementation.
	 */
	virtual void LB_STDCALL initialize() = 0;

	/** \brief Forwarder for running the plugin.
	 *
	 * Let the plugin implementation run.
	 */
	virtual bool LB_STDCALL run() = 0;

	/** \brief Check for given interface.
	 *
	 * This function instantiate the underlying implementation and
	 * checks, if it contains the requested interface. If this is true,
	 * the instance will stay alive. If not, it will be released.
	 */
	virtual bool LB_STDCALL hasInterface(char* name) = 0;
	
	/** \brief Returns the underlying implementation as unknown instance.
	 *
	 * This function returns the instance of the implementation and left the
	 * owning by the caller. It does not clean up the instance by it self.
	 */
	 
	virtual lb_I_Unknown* LB_STDCALL getImplementation() = 0; 

/*...slb_I_Plugin management API:0:*/
	/**
	 * The plugin must know of the plugin manager to self detach at cleanup due to
	 * release calls.
	 * This function is called prior to setAttached.
	 */
	virtual void LB_STDCALL setPluginManager(lb_I_PluginManager* plM) = 0; 

	/**
	 * Called by attach/detach function from plugin manager.
	 * If the parameter is NULL, the plugin should uninitialize before
	 * really detaching.
	 */
	virtual void LB_STDCALL setAttached(lb_I_PluginImpl* impl = NULL) = 0;

	/**
	 * This function should uninitialize all handlers, that are registered.
	 */
	virtual void LB_STDCALL uninitialize() = 0;

	/**
	 * Set the name of the module where the plugin is in.
	 */
	virtual void LB_STDCALL setModule(char* module) = 0;
	
	/**
	 * Set the name of the plugin. This would be the functor name for
	 * an instance of the plugin.
	 */
	virtual void LB_STDCALL setName(char* name) = 0;
	
	/**
	 * The scope identifies the area of usage. If the scope is GUI, it
	 * would only be usable in graphical user environment. If it is UI,
	 * it would be usable in textual user interfaces as well. If it is
	 * NONE, it could also be used in non user interface centric apps.
	 *
	 * This means, propably a server, where no user interaction is available.
	 */
	virtual void LB_STDCALL setNamespace(char* __namespace) = 0;
	
	
	virtual char* LB_STDCALL getModule() = 0;
	virtual char* LB_STDCALL getName() = 0;
	virtual char* LB_STDCALL getNamespace() = 0;

/*...e*/
	
};
/*...e*/

/**
 * \brief This interface must be used for each plugin implementation.
 */
/*...sclass lb_I_PluginImpl:0:*/
class lb_I_PluginImpl : public lb_I_Unknown {
public:

	/**
	 * Let the plugin initialize it self.
	 */
	virtual void LB_STDCALL initialize() = 0;
	
	/**
	 * Run the plugin.
	 */
	virtual bool LB_STDCALL run() = 0;

	/** \brief Creates an instance once.
	 *
	 * This function creates an instance once and holds it created until getImplementation
	 * is called. This enables checking for interfaces before real usage.
	 */
	virtual lb_I_Unknown* LB_STDCALL peekImplementation() = 0;

	/**
	 * \brief Release unused implementation.
	 *
	 * This function i'must be used to release the temporary instance.
	 *
	 * It has been occured, that a wxDialog based window - or even wxWindow,
	 * that will not be used by the program, eg. later Destroyed, will hang
	 * the application at exit.
	 *
	 * The lb_I_PluginImpl implementation then should call Destroy in the case
	 * of a wxWindow based class.
	 */
	virtual void LB_STDCALL releaseImplementation() = 0;
	
	/** \brief Get the internal implementation.
	 *
	 * Returns the implementation class as an unknown interface. Internally it releases the
	 * instance to be able to create new instances.
	 */
	virtual lb_I_Unknown* LB_STDCALL getImplementation() = 0; 
};
/*...e*/

class lb_I_Parameter;

/**
 * \brief This interface is intended as a way to delegate actions.
 * 
 * Actions may be issued with buttons, validations or any other source like
 * timer events. The goal of this attempt is to abstract the action so it can
 * be simply used in a form without knowing the type of the action target.
 */
class lb_I_Action : public lb_I_Unknown {
public:

	/** \brief Execute the action with the given parameter list.
	 */
	virtual void LB_STDCALL execute(lb_I_Parameter* params) = 0;
	
	/** \brief What is my action (from the database).
	 */
	virtual void LB_STDCALL setActionID(char* id) = 0;
};

/**
 * \brief This interface is intended as a way to delegate action steps.
 *
 * Means, that the main action (lb_I_Action) could have multiple steps,
 * to be performed for one action, that may be visible with a button for
 * example.
 */
class lb_I_DelegatedAction : public lb_I_Unknown {
public:
	/** \brief The delegated action
	 */
	virtual void LB_STDCALL execute(lb_I_Parameter* params) = 0;
	virtual void LB_STDCALL setActionID(char* id) = 0;
};

#include <lbInterfaces-sub-xml.h>
#include <lbInterfaces-sub-classes.h>	
#include <lbInterfaces-sub-ui.h>
#include <lbInterfaces-sub-db.h>
#include <lbInterfaces-sub-wxWrapper.h>
#endif // __LB_INTERFACES__
