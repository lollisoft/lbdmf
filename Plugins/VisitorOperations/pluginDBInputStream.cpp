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
            
            40235 Duesseldorf (germany)
*/
/*...e*/
/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#include <lbConfigHook.h>

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
//#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
/*...e*/

/*...slbDatabaseInputStream:0:*/
/** \brief Implementation of input stream.
 *
 * Implements lb_I_Aspect to allow getting calls from objects, I support.
 * Implements lb_I_FileOperation to specify, that this operation has to do
 * with files. Here loading from file.
 */
class lbDatabaseInputStream : 
	public lb_I_DatabaseOperation {
public:
	lbDatabaseInputStream();
	virtual ~lbDatabaseInputStream();
	
	DECLARE_LB_UNKNOWN()

/*...sUnimplemented visitors:8:*/
	void LB_STDCALL visit(lb_I_LogonHandler*) { _CL_LOG << "visit(lb_I_LogonHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonPage*) { _CL_LOG << "visit(lb_I_LogonPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_AppSelectPage*) { _CL_LOG << "visit(lb_I_AppSelectPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUI*) { _CL_LOG << "visit(lb_I_GUI*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUIApp*) { _CL_LOG << "visit(lb_I_GUIApp*)" LOG_ }
	void LB_STDCALL visit(lb_I_Frame*) { _CL_LOG << "visit(lb_I_Frame*)" LOG_ }
	void LB_STDCALL visit(lb_I_KeyBase*) { _CL_LOG << "visit(lb_I_KeyBase*)" LOG_ } 
	void LB_STDCALL visit(lb_I_String*) { _CL_LOG << "visit(lb_I_String*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Integer*) { _CL_LOG << "visit(lb_I_Integer*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Long*) { _CL_LOG << "visit(lb_I_Long*)" LOG_ }
	void LB_STDCALL visit(lb_I_Container*) { _CL_LOG << "visit(lb_I_Container*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Database*) { _CL_LOG << "visit(lb_I_Database*)" LOG_ } 
	void LB_STDCALL visit(lb_I_ColumnBinding*) { _CL_LOG << "visit(lb_I_ColumnBinding*)" LOG_ } 
	void LB_STDCALL visit(lb_I_BoundColumn*) { _CL_LOG << "visit(lb_I_BoundColumn*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Query*) { _CL_LOG << "visit(lb_I_Query*)" LOG_ } 
	void LB_STDCALL visit(lb_I_MVC_View*) { _CL_LOG << "visit(lb_I_MVC_View*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Connection*) { _CL_LOG << "visit(lb_I_Connection*)" LOG_ } 
	void LB_STDCALL visit(lb_I_InterfaceRepository*) { _CL_LOG << "visit(lb_I_InterfaceRepository*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Element*) { _CL_LOG << "visit(lb_I_Element*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Module*) { _CL_LOG << "visit(lb_I_Module*)" LOG_ } 
	void LB_STDCALL visit(lb_I_FunctorEntity*) { _CL_LOG << "visit(lb_I_FunctorEntity*)" LOG_ }
	void LB_STDCALL visit(lb_I_InstanceReference*) { _CL_LOG << "visit(lb_I_InstanceReference*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventHandler*) { _CL_LOG << "visit(lb_I_EventHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventManager*) { _CL_LOG << "visit(lb_I_EventManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventMapper*) { _CL_LOG << "visit(lb_I_EventMapper*)" LOG_ }
	void LB_STDCALL visit(lb_I_EvHandler*) { _CL_LOG << "visit(lb_I_EvHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_Dispatcher*) { _CL_LOG << "visit(lb_I_Dispatcher*)" LOG_ }
	void LB_STDCALL visit(lb_I_InputStream*) { _CL_LOG << "visit(lb_I_InputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_OutputStream*) { _CL_LOG << "visit(lb_I_OutputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileOperation*) { _CL_LOG << "visit(lb_I_FileOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_Locale*) { _CL_LOG << "visit(lb_I_Locale*)" LOG_ }
	void LB_STDCALL visit(lb_I_Parameter*) { _CL_LOG << "visit(lb_I_Parameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_Reference*) { _CL_LOG << "visit(lb_I_Reference*)" LOG_ }
	void LB_STDCALL visit(lb_I_Log*) { _CL_LOG << "visit(lb_I_Log*)" LOG_ }
	void LB_STDCALL visit(lb_I_Plugin*) { _CL_LOG << "visit(lb_I_Plugin*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginImpl*) { _CL_LOG << "visit(lb_I_PluginImpl*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginManager*) { _CL_LOG << "visit(lb_I_PluginManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginModule*) { _CL_LOG << "visit(lb_I_PluginModule*)" LOG_ }
	void LB_STDCALL visit(lb_I_wxFrame*) { _CL_LOG << "visit(lb_I_wxFrame*)" LOG_ }
	void LB_STDCALL visit(lb_I_Window*) { _CL_LOG << "visit(lb_I_Window*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action*) { _CL_LOG << "visit(lb_I_Action*)" LOG_ }
	void LB_STDCALL visit(lb_I_DelegatedAction*) { _CL_LOG << "visit(lb_I_DelegatedAction*)" LOG_ }
	void LB_STDCALL visit(lb_I_Form*) { _CL_LOG << "visit(lb_I_Form*)" LOG_ }
	void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) { _CL_LOG << "visit(lb_I_MasterDetailFormDefinition*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseReport*) { _CL_LOG << "visit(lb_I_DatabaseReport*)" LOG_ }
	void LB_STDCALL visit(lb_I_CodeGenerator*) { _CL_LOG << "visit(lb_I_CodeGenerator*)" LOG_ }
	void LB_STDCALL visit(lb_I_Boolean*) { _CL_LOG << "visit(lb_I_Boolean*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseOperation*) { _CL_LOG << "visit(lb_I_DatabaseOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_ParameterTable*) { _CL_LOG << "visit(lb_I_ParameterTable*)" LOG_ }

/*...e*/

	void LB_STDCALL visit(lb_I_Streamable*);
	void LB_STDCALL visit(lb_I_Application*);
	void LB_STDCALL visit(lb_I_MetaApplication*);
	void LB_STDCALL visit(lb_I_UserAccounts*);
	void LB_STDCALL visit(lb_I_Applications*);
	void LB_STDCALL visit(lb_I_User_Applications*);
	void LB_STDCALL visit(lb_I_Formulars*);
	
	void LB_STDCALL visit(lb_I_ApplicationParameter*);
	void LB_STDCALL visit(lb_I_FormularParameter*);

	bool LB_STDCALL begin(const char* DBName, const char* DBUser, const char* DBPass);
	bool LB_STDCALL begin(lb_I_Database* _db);
	void LB_STDCALL end();

//	lb_I_Stream* LB_STDCALL getStream();

	UAP(lb_I_Database, db)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseInputStream)
	ADD_INTERFACE(lb_I_DatabaseOperation)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseInputStream, lbDatabaseInputStream)


/*...slbErrCodes LB_STDCALL lbDatabaseInputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseInputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbDatabaseInputStream::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabaseInputStream\58\\58\lbDatabaseInputStream\40\\41\:0:*/
lbDatabaseInputStream::lbDatabaseInputStream() 
{
	_CL_LOG << "lbDatabaseInputStream::lbDatabaseInputStream() called." LOG_
	ref = STARTREF;
}
/*...e*/
/*...slbDatabaseInputStream\58\\58\\126\lbDatabaseInputStream\40\\41\:0:*/
lbDatabaseInputStream::~lbDatabaseInputStream() {
	_CL_LOG << "lbDatabaseInputStream::~lbDatabaseInputStream() called." LOG_
}
/*...e*/

bool LB_STDCALL lbDatabaseInputStream::begin(const char* DBName, const char* DBUser, const char* DBPass) {
	REQUEST(manager.getPtr(), lb_I_Database, db)
	
	bool ret = false;
	
	
	
	return ret;
}

bool LB_STDCALL lbDatabaseInputStream::begin(lb_I_Database* _db) {
	lbErrCodes err = ERR_NONE;
	if (_db != NULL) {
		QI(_db, lb_I_Database, db)
		bool ret = _db->isConnected();

		if (!ret) {
			_CL_LOG << "lbDatabaseInputStream::begin(lb_I_Database* _db) Error: Must have a database connection." LOG_
		}
		
		return ret;
	} else {
		_CL_LOG << "lbDatabaseInputStream::begin(lb_I_Database* _db) Error: Uninitialized database onject (NULL pointer)!" LOG_
	}
	
	return false;
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Streamable* pm) {
	if (db != NULL) {
		/*
		   How to implement private database 'streams' ?

		   Theoretically, the database must inherid from a lb_I_Streamable interface.
		   Additionally, the function called here, must distinguish between file operations
		   and database operations.
		*/
		pm->load(db.getPtr());
	} else {
		_CL_LOG << "lbDatabaseInputStream::visit(lb_I_ProjectManager* pm) Error: No input stream available. Could not read from stream!" LOG_
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_UserAccounts* users) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, userid, passwort from Users") != ERR_NONE) {
		_LOG << "Error: Access to user table failed. Read user accounts would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No user accounts found. All accounts may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_String, qUID)
		UAP(lb_I_String, qPWD)
		
		qID = q->getAsLong(1);
		qUID = q->getAsString(2);
		qPWD = q->getAsString(3);
		
		users->addAccount(qUID->charrep(), qPWD->charrep(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qUID = q->getAsString(2);
			qPWD = q->getAsString(3);
		
			users->addAccount(qUID->charrep(), qPWD->charrep(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_FormularParameter* params) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, parametername, parametervalue, formularid from Formular_Parameters") != ERR_NONE) {
		_LOG << "Error: Access to Formular_Parameters table failed. Read Formular_Parameters would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formular_Parameters found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qFID)
		UAP(lb_I_String, qV)
		UAP(lb_I_String, qN)
		
		qID = q->getAsLong(1);
		qN = q->getAsString(2);
		qV = q->getAsString(3);
		qFID = q->getAsLong(4);
		
		params->addParameter(qN->charrep(), qV->charrep(), qFID->getData(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qN = q->getAsString(2);
			qV = q->getAsString(3);
			qFID = q->getAsLong(4);
			
			params->addParameter(qN->charrep(), qV->charrep(), qFID->getData(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_ApplicationParameter* params) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, parametername, parametervalue, anwendungid from Anwendungs_Parameter") != ERR_NONE) {
		_LOG << "Error: Access to Anwendungs_Parameters table failed. Read Anwendungs_Parameters would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Anwendungs_Parameters found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qAID)
		UAP(lb_I_String, qV)
		UAP(lb_I_String, qN)
		
		qID = q->getAsLong(1);
		qN = q->getAsString(2);
		qV = q->getAsString(3);
		qAID = q->getAsLong(4);
		
		params->addParameter(qN->charrep(), qV->charrep(), qAID->getData(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qN = q->getAsString(2);
			qV = q->getAsString(3);
			qAID = q->getAsLong(4);
			
			params->addParameter(qN->charrep(), qV->charrep(), qAID->getData(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Formulars* forms) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, name, menuname, eventname, menuhilfe, anwendungid, typ from formulare") != ERR_NONE) {
		_LOG << "Error: Access to formular table failed. Read formulars would be skipped." LOG_
		return;
	}
	
	err = q->first(); 

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No formulars found. All formulars may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, FormularID)
		UAP(lb_I_Long, AnwendungID)
		UAP(lb_I_Long, Typ)
		UAP(lb_I_String, FormularName)
		UAP(lb_I_String, MenuName)
		UAP(lb_I_String, MenuHilfe)
		UAP(lb_I_String, EventName)

		FormularID = q->getAsLong(1);
		FormularName = q->getAsString(2);
		MenuName = q->getAsString(3);
		EventName = q->getAsString(4);		
		MenuHilfe = q->getAsString(5);
		AnwendungID = q->getAsLong(6);
		Typ = q->getAsLong(7);
		
		forms->addFormular(FormularName->charrep(), MenuName->charrep(), EventName->charrep(), MenuHilfe->charrep(), AnwendungID->getData(), Typ->getData(), FormularID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			FormularID = q->getAsLong(1);
			FormularName = q->getAsString(2);
			MenuName = q->getAsString(3);
			EventName = q->getAsString(4);		
			MenuHilfe = q->getAsString(5);
			AnwendungID = q->getAsLong(6);
			Typ = q->getAsLong(7);
			
			forms->addFormular(FormularName->charrep(), MenuName->charrep(), EventName->charrep(), MenuHilfe->charrep(), AnwendungID->getData(), Typ->getData(), FormularID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Applications* applications) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();

	if (q->query("select id, Name, Titel, ModuleName, Functor, Interface from Anwendungen") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read applications would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No applications found. All applications may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_String, qName)
		UAP(lb_I_String, qTitel)
		UAP(lb_I_String, qModuleName)
		UAP(lb_I_String, qFunctor)
		UAP(lb_I_String, qInterface)
		
		qID = q->getAsLong(1);
		qName = q->getAsString(2);
		qTitel = q->getAsString(3);
		qModuleName = q->getAsString(4);
		qFunctor = q->getAsString(5);
		qInterface = q->getAsString(6);
		
		applications->addApplication(qName->charrep(), qTitel->charrep(), qModuleName->charrep(), qFunctor->charrep(), qInterface->charrep(), qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qName = q->getAsString(2);
			qTitel = q->getAsString(3);
			qModuleName = q->getAsString(4);
			qFunctor = q->getAsString(5);
			qInterface = q->getAsString(6);
		
			applications->addApplication(qName->charrep(), qTitel->charrep(), qModuleName->charrep(), qFunctor->charrep(), qInterface->charrep(), qID->getData());
		}

	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_User_Applications* user_applications) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();

	if (q->query("select id, userid, anwendungenid from user_anwendungen") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read applications would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No applications found. All applications may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qUserID)
		UAP(lb_I_Long, qAppID)
		
		qID = q->getAsLong(1);
		qUserID = q->getAsLong(2);
		qAppID = q->getAsLong(3);
		
		user_applications->addRelation(qAppID->getData(), qUserID->getData(), qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qUserID = q->getAsLong(2);
			qAppID = q->getAsLong(3);
		
			user_applications->addRelation(qAppID->getData(), qUserID->getData(), qID->getData());
		}

	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_MetaApplication* app) {
	_CL_LOG << "lbDatabaseInputStream::visit(): Read data of meta application." LOG_

	char* temp = NULL;
	bool  b;
	int   count = 0;
	lbErrCodes err = ERR_NONE;
	
/* // No local settings in the database...	
	*iStream >> b;
	app->setAutorefreshData(b);
	
	*iStream >> temp;
	app->setApplicationName(temp);
	
	*iStream >> temp;
	app->setUserName(temp);

	*iStream >> b;
	app->setAutoload(b);
	
	*iStream >> b;
	app->setAutoselect(b);

	*iStream >> b;
	app->setGUIMaximized(b);
*/

	// Number of users
	//*iStream >> count;
	
	
	// Number of applications
	//*iStream >> count;
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Application*) {
	_CL_LOG << "lbDatabaseInputStream::visit(): Read data of application." LOG_
}

void LB_STDCALL lbDatabaseInputStream::end() {

}
/*
lb_I_Stream* LB_STDCALL lbDatabaseInputStream::getStream() {
	lbErrCodes err = ERR_NONE;
	
        UAP(lb_I_Stream, s)
        QI(iStream, lb_I_Stream, s)
        s++;

        return s.getPtr();
}
*/
/*...e*/

/*...sclass lbPluginDatabaseInputStream implementation:0:*/
/*...slbPluginDatabaseInputStream:0:*/
class lbPluginDatabaseInputStream : public lb_I_PluginImpl {
public:
	lbPluginDatabaseInputStream();
	
	virtual ~lbPluginDatabaseInputStream();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()

private:
	UAP(lb_I_Unknown, impl)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabaseInputStream)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabaseInputStream, lbPluginDatabaseInputStream)

/*...slbErrCodes LB_STDCALL lbPluginDatabaseInputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabaseInputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDatabaseInputStream::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabaseInputStream::lbPluginDatabaseInputStream() {
	_CL_VERBOSE << "lbPluginDatabaseInputStream::lbPluginDatabaseInputStream() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDatabaseInputStream::~lbPluginDatabaseInputStream() {
	_CL_VERBOSE << "lbPluginDatabaseInputStream::~lbPluginDatabaseInputStream() called.\n" LOG_
}

void LB_STDCALL lbPluginDatabaseInputStream::initialize() {
}
	
bool LB_STDCALL lbPluginDatabaseInputStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseInputStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseInputStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbDatabaseInputStream* InputStream = new lbDatabaseInputStream();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseInputStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseInputStream::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
	
		lbDatabaseInputStream* InputStream = new lbDatabaseInputStream();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabaseInputStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/
