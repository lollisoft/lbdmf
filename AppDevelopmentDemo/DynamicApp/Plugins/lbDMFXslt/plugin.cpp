/*...sLicence:0:*/
/*


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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
#ifndef DEBUG_MALLOC
#include <malloc.h>
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif


/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "plugin.cpp"
#pragma interface "plugin.cpp"
#endif

/*...e*/

/*...sclass lbPluginModuleTest:0:*/
class lbPluginModule : public lb_I_PluginModule {
public:

	lbPluginModule();
	virtual ~lbPluginModule();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL install();

	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModuleTest implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModule)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModule)

BEGIN_PLUGINS(lbPluginModule)
	// Project manager
	ADD_PLUGIN(lbPluginDMFXslt, XsltTransformer)
END_PLUGINS()

lbPluginModule::lbPluginModule() {
	
	_LOGVERBOSE << "lbPluginModule::lbPluginModule() lbPluginDMFXslt with namespace XsltTransformer called." LOG_
}

lbPluginModule::~lbPluginModule() {
	_LOGVERBOSE << "lbPluginModule::~lbPluginModule() lbPluginDMFXslt with namespace XsltTransformer called." LOG_
}

// The failure code is not late binding the columns, thus a primary key
// later on seems not to get handled proper when I try to set it readonly.
//#define FAILURE_CODE

// The query does not cause the stack corrupption either failure or not
//#define FAILURE_QUERY

void LB_STDCALL lbPluginModule::initialize() {
	lbErrCodes err = ERR_NONE;

	_LOGVERBOSE << "lbPluginModule::initialize() lbPluginDMFXslt called." LOG_
	enumPlugins();
}

void LB_STDCALL lbPluginModule::install() {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Database, database)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	char* dbbackend = meta->getSystemDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOGVERBOSE << "Using plugin database backend for lbPluginModule::initialize() operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		
		if (database == NULL) {
			_LOG << "Error: Database couldn't loaded. Maybe ODBC components are not installed." LOG_
			return;
		}
		
		_LOGVERBOSE << "Using built in database backend for lbPluginModule::initialize() operation..." LOG_
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

	UAP(lb_I_Query, q)
	UAP(lb_I_Query, query_actions)
	UAP(lb_I_Query, query_action_steps)
	UAP(lb_I_Query, formularquery)
	UAP(lb_I_Query, formularactions)
	UAP(lb_I_Query, applicationparameterquery)
	UAP(lb_I_Query, applicationquery)
	UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
	q = database->getQuery("lbDMF", 0);
	query_actions = database->getQuery("lbDMF", 0);
	query_action_steps = database->getQuery("lbDMF", 0);
	formularquery = database->getQuery("lbDMF", 0);
	formularactions = database->getQuery("lbDMF", 0);
	applicationparameterquery = database->getQuery("lbDMF", 0);
	applicationquery = database->getQuery("lbDMF", 0);

#ifdef FAILURE_QUERY
	*sql = "select id, bezeichnung, action_handler, module from action_types where module = 'lbDMFXslt' and action_handler = 'instanceOflbDMFXslt'";
#endif
#ifndef FAILURE_QUERY
	*sql = "select id, action_handler, module, bezeichnung from action_types where module = 'lbDMFXslt' and action_handler = 'instanceOflbDMFXslt'";
#endif

	q->skipFKCollecting();
	query_actions->skipFKCollecting();
	query_action_steps->skipFKCollecting();
	formularquery->skipFKCollecting();
	formularactions->skipFKCollecting();
	applicationquery->skipFKCollecting();

#ifdef FAILURE_CODE
	err = q->query(sql->charrep());
#endif
#ifndef FAILURE_CODE
	err = q->query(sql->charrep(), false);
	q->setReadonly("id");
    q->bind();
#endif

	if (err == ERR_NONE) {
		err = q->first();
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			_LOGVERBOSE << "Plugin lbPluginDMFXslt with XsltTransformer already installed." LOG_
		} else {
			if (meta->askYesNo("Plugin for XSLT transformation actions available.\n\nWould you enable that plugin ?")) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, columnname)
				UAP_REQUEST(getModuleInstance(), lb_I_String, module)
				UAP_REQUEST(getModuleInstance(), lb_I_String, action_handler)
				UAP_REQUEST(getModuleInstance(), lb_I_String, bezeichnung)
				UAP_REQUEST(getModuleInstance(), lb_I_String, id)
				UAP_REQUEST(getModuleInstance(), lb_I_Long, action_type_id)

				// If loading is set to file, overwrite.
				meta->setLoadFromDatabase(true);

				*module = "lbDMFXslt";
				*action_handler = "instanceOflbDMFXslt";
				*bezeichnung = "Perform XSLT transformation";
				*id = "1";

				*columnname = "module";
				q->setString(*&columnname, *&module);
				*columnname = "id";
				q->setString(*&columnname, *&id);
				*columnname = "action_handler";
				q->setString(*&columnname, *&action_handler);
				*columnname = "bezeichnung";
				q->setString(*&columnname, *&bezeichnung);

				q->add();
				*columnname = "id";
				q->setString(*&columnname, *&id);
				*columnname = "module";
				q->setString(*&columnname, *&module);
				*columnname = "action_handler";
				q->setString(*&columnname, *&action_handler);
				*columnname = "bezeichnung";
				q->setString(*&columnname, *&bezeichnung);

#ifdef FAILURE_CODE
                q->setReadonly("id");
#endif
				q->update();

				q->last();
				action_type_id = q->getAsLong(1);

				// Action to generate code at the level of Application
				{
					query_actions->query("insert into actions (name, typ, source, target) values('Code generieren', 1, 'name', 0)");
                    _LOG << "Initialize lbDMFXSLT module. Step 4" LOG_

					UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
					UAP(lb_I_Long, actionid)

					if (query_actions->query("select id from actions where name = 'Code generieren'") == ERR_NONE) {
						err = query_actions->first();
						if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
							actionid = query_actions->getAsLong(1);

							*sql = "insert into action_steps (actionid, type, bezeichnung, a_order_nr) values (";
							*sql += actionid->charrep();
							*sql += ", ";
							*sql += action_type_id->charrep();
							*sql += ", 'Translate XML file with XSLT template', 1)";
							query_action_steps->query(sql->charrep());

							*sql = "select id from formulare where name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager')";

							if (formularquery->query(sql->charrep()) == ERR_NONE) {
								err = formularquery->first();
								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									UAP(lb_I_String, formid)

									formid = formularquery->getAsString(1);

									*sql = "insert into formular_actions (formular, action, event) values (";
									*sql += formid->charrep();
									*sql += ", ";
									*sql += actionid->charrep();
									*sql += ", 'evtGenerateCode')";

									formularactions->query(sql->charrep());
								}
							}
						}
					}
				}
				// Action to generate XSLT template at the level of Templates
#ifdef bla
				{
					query_actions->query("insert into actions (name, typ, source, target) values('generate XSLT template', 1, 'name', 0)");

					UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
					UAP(lb_I_Long, actionid)

					if (query_actions->query("select id from actions where name = 'generate XSLT template'") == ERR_NONE) {
						err = query_actions->first();
						if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
							actionid = query_actions->getAsLong(1);

							*sql = "insert into action_steps (actionid, type, bezeichnung, a_order_nr) values (";
							*sql += actionid->charrep();
							*sql += ", ";
							*sql += action_type_id->charrep();
							*sql += ", 'Create  XSLT template file set based on template definition', 1)";
							query_action_steps->query(sql->charrep());

							*sql = "select id from formulare where name = 'Templates' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager')";

							if (formularquery->query(sql->charrep()) == ERR_NONE) {
								err = formularquery->first();
								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									UAP(lb_I_String, formid)

									formid = formularquery->getAsString(1);

									*sql = "insert into formular_actions (formular, action, event) values (";
									*sql += formid->charrep();
									*sql += ", ";
									*sql += actionid->charrep();
									*sql += ", 'evtGenerateXSLTTemplate')";

									formularactions->query(sql->charrep());
								}
							}
						}
					}
				}
#endif
			}
		}
	}
}

lbErrCodes LB_STDCALL lbPluginModule::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModuleTest::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
