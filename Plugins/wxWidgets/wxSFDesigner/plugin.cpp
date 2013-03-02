
/* Base class for fixed database formular
 *  lbDMFManager
 */

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
#include <lbInterfaces.h>

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#ifdef __GNUG__
#pragma implementation "plugin.cpp"
#pragma interface "plugin.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wizard.h>
#include <wx/image.h>

// Include base class definition
#include <plugin.h>

//#include <wxSFDesignerBase.h>

// Plugin module code

class lbPluginModulewxSFDesignerBase : public lb_I_PluginModule {
public:

	lbPluginModulewxSFDesignerBase();
	virtual ~lbPluginModulewxSFDesignerBase();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModulewxSFDesignerBase)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModulewxSFDesignerBase)

BEGIN_PLUGINS(lbPluginModulewxSFDesignerBase)

	ADD_PLUGIN(lbPluginAnwendungen, FixedForm_SFDesigner_Anwendungen)
	ADD_PLUGIN(lbPluginFormulare, FixedForm_SFDesigner_Formulare)

END_PLUGINS()

lbPluginModulewxSFDesignerBase::lbPluginModulewxSFDesignerBase() {
	_CL_VERBOSE << "lbPluginModulewxSFDesignerBase::lbPluginModulewxSFDesignerBase() called." LOG_
}

lbPluginModulewxSFDesignerBase::~lbPluginModulewxSFDesignerBase() {
	_CL_VERBOSE << "lbPluginModulewxSFDesignerBase::~lbPluginModulewxSFDesignerBase() called." LOG_
}

void LB_STDCALL lbPluginModulewxSFDesignerBase::install() {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Database, database)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	char* dbbackend = meta->getSystemDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOG << "Using plugin database backend for lbPluginModule::initialize() operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		
		if (database == NULL) {
			_LOG << "Error: Database couldn't loaded. Maybe ODBC components are not installed." LOG_
			return;
		}
		
		_LOG << "Using built in database backend for lbPluginModule::initialize() operation..." LOG_
	}
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->init();
	if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
		_LOG << "Error: Could not connect to given database: '" << "lbDMF" << "'" LOG_
		
		return;
	}
	
	
	
	{
		UAP(lb_I_Query, q)
		UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
		q = database->getQuery("lbDMF", 0);
		
		// Refactor to method per values in formulartypen table.
		
		*sql = "select id, handlerinterface, namespace, beschreibung from formulartypen where namespace = '";
		*sql += "FixedForm_SFDesigner_Anwendungen'";
		
		q->skipFKCollecting();
		err = q->query(sql->charrep());
		
		if (err == ERR_DB_NODATA) {
			err = q->first();
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				_LOG << "No modification to dynamic formular 'Anwendungsdesigner' definition needed." LOG_
			} else {
				// Install custom form
				_LOGALWAYS << "Modification to dynamic formular 'Anwendungsdesigner' definition needed." LOG_
				q->query("insert into formulartypen (namespace, beschreibung, handlerinterface) values ('FixedForm_SFDesigner_Anwendungen', 'Designer for applications and related forms', 'lb_I_Form')");
				
				q = database->getQuery("lbDMF", 0);
				q->skipFKCollecting();
				
				if (q->query(sql->charrep()) == ERR_NONE) {
					UAP(lb_I_String, ID)
					UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
					err = q->first();
					_LOGALWAYS << "Try to add designer for 'Anwendungen'." LOG_
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						ID = q->getAsString(2);
						
						*SQL = "insert into formulare ('name', 'menuname', 'menuhilfe', 'eventname', 'toolbarimage', 'typ', 'anwendungid') values (";
						*SQL += "'Designer (Anwendungen)', 'Anwendungsdesigner', 'DSL Anwendungsdesigner', 'designAnwendungen', 'newApplication.png', (select ID from formulartypen where namespace = 'FixedForm_SFDesigner_Anwendungen'), (select ID from 'Anwendungen' where name = 'lbDMF Manager')";
						*SQL += ")";
						
						_LOG << "Install custom formular 'DesignAnwendungen'." LOG_
						
						err = q->query(SQL->charrep());
						
						if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
							_LOGALWAYS << "Installation of custom formular 'Anwendungen' failed." LOG_
						} else {
							*SQL = "insert into anwendungen_formulare ('anwendungid', 'formularid') values (";
							*SQL += "(select ID from anwendungen where name = 'lbDMF Manager'), (select ID from formulare where name = 'Designer (Anwendungen)')";
							*SQL += ")";
							
							_LOGALWAYS << "Install custom formular association." LOG_
							
							err = q->query(SQL->charrep());
							
							if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
								_LOGALWAYS << "Installation of custom formular 'DesignAnwendungen' failed." LOG_
							}
						}

					} else {
						_LOG << "Failed to re-read the ID for the currently inserted formular type ('Anwendungen') ! Query: " << sql->charrep() LOG_
					}
				} else {
					_LOG << "Failed to re-read the ID for the currently inserted formular type ('Anwendungen') !" LOG_
				}
			}
		}

		*sql = "select id, handlerinterface, namespace, beschreibung from formulartypen where namespace = '";
		*sql += "FixedForm_SFDesigner_Formulare'";
		
		q->skipFKCollecting();
		err = q->query(sql->charrep());
		
		if (err == ERR_DB_NODATA) {
			err = q->first();
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				_LOG << "No modification to dynamic formular 'Formularedesigner' definition needed." LOG_
			} else {
				// Install custom form
				_LOGALWAYS << "Modification to dynamic formular 'Formularedesigner' definition needed." LOG_
				q->query("insert into formulartypen (namespace, beschreibung, handlerinterface) values ('FixedForm_SFDesigner_Formulare', 'Designer for formulars and related fields', 'lb_I_Form')");
				
				q = database->getQuery("lbDMF", 0);
				q->skipFKCollecting();
				
				if (q->query(sql->charrep()) == ERR_NONE) {
					UAP(lb_I_String, ID)
					UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
					err = q->first();
					_LOGALWAYS << "Try to add designer for 'Formulare'." LOG_
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						ID = q->getAsString(2);
						
						*SQL = "insert into formulare ('name', 'menuname', 'menuhilfe', 'eventname', 'toolbarimage', 'typ', 'anwendungid') values (";
						*SQL += "'Designer (Formulare)', 'Formularedesigner', 'DSL Formularedesigner', 'designFormulare', 'kpersonalizer.png', (select ID from formulartypen where namespace = 'FixedForm_SFDesigner_Formulare'), (select ID from 'Anwendungen' where name = 'lbDMF Manager')";
						*SQL += ")";
						
						_LOG << "Install custom formular 'DesignFormulare'." LOG_
						
						err = q->query(SQL->charrep());
						
						if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
							_LOGALWAYS << "Installation of custom formular 'Formulare' failed." LOG_
						} else {
							*SQL = "insert into anwendungen_formulare ('anwendungid', 'formularid') values (";
							*SQL += "(select ID from anwendungen where name = 'lbDMF Manager'), (select ID from formulare where name = 'Designer (Formulare)')";
							*SQL += ")";
							
							_LOGALWAYS << "Install custom formular association." LOG_
							
							err = q->query(SQL->charrep());
							
							if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
								_LOGALWAYS << "Installation of custom formular 'DesignFormulare' failed." LOG_
							}
						}

					} else {
						_LOG << "Failed to re-read the ID for the currently inserted formular type ('Anwendungen') ! Query: " << sql->charrep() LOG_
					}
				} else {
					_LOG << "Failed to re-read the ID for the currently inserted formular type ('Anwendungen') !" LOG_
				}
			}
		}

	}
}

void LB_STDCALL lbPluginModulewxSFDesignerBase::initialize() {
	lbErrCodes err = ERR_NONE;
	char ptr[20] = "";
	sprintf(ptr, "%p", this);

	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModulewxSFDesignerBase::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModulewxSFDesignerBase::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

