<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1"  xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2009  Lothar Behrens (lothar.behrens@lollisoft.de)

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
-->
<xsl:import href="../include/exsl.xsl"/>
<xsl:output method="text" indent="no"/>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$OrginalApplicationName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
<!-- here is the template that does the replacement -->
<xsl:template name="SubstringReplace">
	<xsl:param name="stringIn"/>
	<xsl:param name="substringIn"/>
	<xsl:param name="substringOut"/>
	<xsl:choose>
		<xsl:when test="contains($stringIn,$substringIn)">
			<xsl:value-of select="concat(substring-before($stringIn,$substringIn),$substringOut)"/>
			<xsl:call-template name="SubstringReplace">
				<xsl:with-param name="stringIn" select="substring-after($stringIn,$substringIn)"/>
				<xsl:with-param name="substringIn" select="$substringIn"/>
				<xsl:with-param name="substringOut" select="$substringOut"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$stringIn"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template name="MapTypeObject">
<xsl:variable name="DatatypeID">
	<xsl:value-of select="./type/@xmi:idref"/>
</xsl:variable>
<xsl:if test="./type/@xmi:idref!=''">
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@xmi:type='uml:DataType'">
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@name!='ForeignKey'">
<xsl:value-of select="//packagedElement[@xmi:id=$DatatypeID]/@name"/>
</xsl:if>
</xsl:if>
</xsl:if>
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@name='ForeignKey'">
<xsl:if test="./type/@xmi:type='uml:Class'">lb_I_Integer</xsl:if>
</xsl:if>
<xsl:if test="//packagedElement[@xmi:id=$DatatypeID]/@name!='ForeignKey'">
<xsl:if test="./type/@xmi:type='uml:Class'">lb_I_Container</xsl:if>
</xsl:if>
<xsl:if test="./type/@xmi:type='uml:PrimitiveType'">
	<xsl:choose>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Boolean'">lb_I_Boolean</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#String'">lb_I_String</xsl:when>
		<xsl:when test="./type/@href='http://schema.omg.org/spec/UML/2.1/uml.xml#Integer'">lb_I_Integer</xsl:when>
		<xsl:otherwise>-- Unknown: <xsl:value-of select="./type/@href"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:if>
</xsl:template>

<xsl:template name="lookupEntityName">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FormularID"/>
	<xsl:choose>
		<xsl:when test="./xmi:Extension/stereotype/@name='form'">
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Dependency'][@client=$FormularID]">
			<xsl:variable name="SupplyerClassID" select="@supplier"/>
			<xsl:variable name="SupplierClassStereoType" select="//packagedElement[@xmi:id=$SupplyerClassID]/xmi:Extension/stereotype/@name"/>
			<xsl:if test="$SupplierClassStereoType='entity'">
				<xsl:variable name="DependencyToEntity" select="//packagedElement[@xmi:id=$SupplyerClassID]/@name"/>
				<xsl:value-of select="$DependencyToEntity"/>
			</xsl:if>
		</xsl:for-each>

		</xsl:when>
		<xsl:otherwise><xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FormularID]/@name"/></xsl:otherwise>
</xsl:choose>

	</xsl:template>

<xsl:template name="storage_plugin.cpp">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>/*...sLicence:0:*/
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
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

#ifdef WINDOWS
#include &lt;windows.h&gt;
#include &lt;io.h&gt;
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include &lt;conio.h&gt;

#ifdef __WATCOMC__
#include &lt;ctype.h&gt;
#endif
#ifdef __cplusplus
}
#endif

#include &lt;stdio.h&gt;
#ifndef OSX
#ifndef USE_MPATROL
#include &lt;malloc.h&gt;
#endif
#endif
#ifdef OSX
#include &lt;sys/malloc.h&gt;
#endif

#ifndef LBDMF_PREC
#include &lt;lbConfigHook.h&gt;
#endif

#include &lt;lbInterfaces-sub-security.h&gt;

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include &lt;lbpluginmanager-module.h&gt;
/*...e*/

/*...e*/

/*...sclass lbPluginModuleDynamicAppStorage:0:*/
class lbPluginModuleDynamicAppStorage : public lb_I_PluginModule {
public:

	lbPluginModuleDynamicAppStorage();
	virtual ~lbPluginModuleDynamicAppStorage();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	
	void LB_STDCALL install();
	
	/** \brief Checks for availability of a database.
	 * This function does the work to check, if any known database is available.
	 * The check includes testing for an ODBC database named 'lbDMF' and for the
	 * Sqlite version with this name.
	 *
	 * It returns false if no one is available.
	 */
	bool					LB_STDCALL checkForDatabases();
	
	/** \brief Installs a database.
	 * This function installs the database.
	 */
	bool					LB_STDCALL installDatabase();

	DECLARE_PLUGINS()
	
	UAP(lb_I_MetaApplication, meta)
	int _check_for_databases_failure_step;
	
	enum {
		META_DB_FAILURE_SYS_DB_BACKEND = 1,
		META_DB_FAILURE_SYS_DB_INITIALIZE,
		META_DB_FAILURE_SYS_DB_CONNECT,
		META_DB_FAILURE_SYS_DB_SCHEMA, // The schema is not initialized
		META_DB_FAILURE_SYS_DB_SCHEMAINSTALL, // Installation of the schema failed
		META_DB_FAILURE_APP_DB_BACKEND,
		META_DB_FAILURE_APP_DB_INITIALIZE,
		META_DB_FAILURE_APP_DB_CONNECT,
		META_DB_FAILURE_APP_DB_SCHEMA, // The schema is not initialized
		META_DB_FAILURE_APP_DB_SCHEMAINSTALL // Installation of the schema failed
	};
	
	
};
/*...e*/

/*...sclass lbPluginModuleDynamicAppStorage implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleDynamicAppStorage)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleDynamicAppStorage)

<xsl:variable name="V" select="//lbDMF/@applicationversion"/>
<xsl:variable name="tempFormularName"><xsl:choose><xsl:when test="$V!=''"><xsl:value-of select="$V"/></xsl:when><xsl:otherwise>2.0</xsl:otherwise></xsl:choose></xsl:variable>
<xsl:variable name="ApplicationVersion">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'.'"/>
		<xsl:with-param name="substringOut" select="'_'"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="'_'"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="'_'"/>
	</xsl:call-template>
</xsl:variable>

BEGIN_PLUGINS(lbPluginModuleDynamicAppStorage)
	ADD_PLUGIN(lbPluginDynamicAppInternalStorage,	lbDynAppInternalFormat_v<xsl:value-of select="$ApplicationVersion"/>)
	ADD_PLUGIN(lbPluginDynamicAppXMLStorage,		lbDynAppXMLFormat_v<xsl:value-of select="$ApplicationVersion"/>)
	ADD_PLUGIN(lbPluginDynamicAppBoUMLImport,		lbDynAppUMLImport_v<xsl:value-of select="$ApplicationVersion"/>)
END_PLUGINS()

/*
 * For each application should be a database setup plugin available.
 *
 * If no
 */
bool LB_STDCALL lbPluginModuleDynamicAppStorage::checkForDatabases() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, sysSchemaQuery)
	UAP(lb_I_Database, database)
	
	UAP(lb_I_Query, appSchemaQuery)
	UAP(lb_I_Database, app_database)
	
	// Currently unimplemented.
	
	// Too unsave now (Sqlite check fails on selecting sysadmin account)
	//return true;
	
	if (_check_for_databases_failure_step == -2) return false; // Failed prior. Outer loop must break.
	
	if (database == NULL) {
		char* dbbackend = meta-&gt;getSystemDatabaseBackend();
		if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG &lt;&lt; "lb_MetaApplication::checkForDatabases() Using plugin database backend for system database setup test..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG &lt;&lt; "lb_MetaApplication::checkForDatabases() Using built in database backend for system database setup test..." LOG_
		}
		
		if (database == NULL) {
			_LOGERROR &lt;&lt; "lb_MetaApplication::checkForDatabases() Error: Could not load database backend for system db, either plugin or built in version." LOG_
			
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_BACKEND;
			
			return false;
		}
		if (database-&gt;init() != ERR_NONE) {
			_LOGERROR &lt;&lt; "lb_MetaApplication::checkForDatabases() Failed to initialize database." LOG_
			
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
			
			return false;
		}
	}
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	if ((database != NULL) &amp;&amp; (database-&gt;connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
		_LOGERROR &lt;&lt; "lb_MetaApplication::checkForDatabases() Failed to connect to system database." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_CONNECT;
		
		return false;
	}
	
	// Check. if the system database schema is initialized.
	sysSchemaQuery = database-&gt;getQuery("lbDMF", 0);
	
	if (sysSchemaQuery != NULL) {
		if (sysSchemaQuery-&gt;query("select * from \"users\" where \"userid\"='user'") == ERR_NONE) {
			if (((err = sysSchemaQuery-&gt;first()) == ERR_NONE) || (err == WARN_DB_NODATA)) {
				return true;
			} else {
				_LOGERROR &lt;&lt; "lb_MetaApplication::checkForDatabases() Error: No sysadmin account created." LOG_
				_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_SCHEMA;
				return false;
			}
		} else {
			_LOGERROR &lt;&lt; "lb_MetaApplication::checkForDatabases() Error: Query for sysadmin account failed." LOG_
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_SCHEMA;
			return false;
		}
	} else {
		_LOGERROR &lt;&lt; "lb_MetaApplication::checkForDatabases() Error: Could not get query instance for sysadmin account test." LOG_
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_BACKEND;
		return false;
	}
	
	return true;
}

bool LB_STDCALL lbPluginModuleDynamicAppStorage::installDatabase() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, sysSchemaQuery)
	UAP(lb_I_Database, database)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, testSQLFile)
	UAP_REQUEST(getModuleInstance(), lb_I_String, initialDatabaseLocation)
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	char* home = getenv("HOME");
	
	bool  localInitialisation = false;
	
#ifdef WINDOWS
	*testSQLFile = ".\\Database\\lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile-&gt;charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = ".\\Database\\";
	} else {
	        *testSQLFile = "..\\Database\\lbDMF-Sqlite-SystemDB.sql";
        	localInitialisation = FileExists(testSQLFile-&gt;charrep());
        	if (localInitialisation) {
        		*initialDatabaseLocation = "..\\Database\\";
       		} else {
			_LOGERROR &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
			return false;
		}
	}
#endif
#ifdef OSX
	*testSQLFile = home;
	*testSQLFile += "/.lbDMF/lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile-&gt;charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = home;
		*initialDatabaseLocation += "/.lbDMF/";
	} else {
		/// \todo Check if bundle is always as expected.
		// The application could be renamed.
		
		*testSQLFile = "./wxWrapper.app/Contents/Resources/lbDMF-Sqlite-SystemDB.sql";
		if (FileExists(testSQLFile-&gt;charrep())) {
			*initialDatabaseLocation = "./wxWrapper.app/Contents/Resources/";
		} else {
			_LOGERROR &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
			return false;
		}
	}
#endif
#ifdef SOLARIS
	*testSQLFile = home;
	*testSQLFile += "/.lbDMF/lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile-&gt;charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = home;
		*initialDatabaseLocation += "/.lbDMF/";
	} else {
		///\todo Implement correct installation path.
		*testSQLFile = "../Database/lbDMF-Sqlite-SystemDB.sql";
		localInitialisation = FileExists(testSQLFile-&gt;charrep());
		if (localInitialisation) {
			*initialDatabaseLocation = "../Database/";
		} else {
			// There is no execution path set on the solaris desktop symbol. Therefore use the development environment at my machine
			*testSQLFile = home;
			*testSQLFile += "/develop/Projects/CPP/Database/lbDMF-Sqlite-SystemDB.sql";
			localInitialisation = FileExists(testSQLFile-&gt;charrep());
			if (localInitialisation) {
				*initialDatabaseLocation = home;
				*initialDatabaseLocation += "/develop/Projects/CPP/Database/";
			} else {
				/// \todo Implement lookup of bundle.
				// Try resource directory in bundle.
				_LOGERROR &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
				_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
				return false;
			}
		}
	}
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
	*testSQLFile = home;
	*testSQLFile += "/.lbDMF/lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile-&gt;charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = home;
		*initialDatabaseLocation += "/.lbDMF/";
	} else {
		/// \todo Implement lookup correctly for other cases.
		
		if (FileExists("../Database/lbDMF-Sqlite-SystemDB.sql")) {
			*initialDatabaseLocation = "../Database/";
		} else
			if (FileExists("/usr/share/lbdmf/database/lbDMF-Sqlite-SystemDB.sql")) {
				*initialDatabaseLocation = "/usr/share/lbdmf/database/";
			} else
				if (FileExists("/usr/local/share/lbdmf/database/lbDMF-Sqlite-SystemDB.sql")) {
					*initialDatabaseLocation = "/usr/local/share/lbdmf/database/";
				} else {
					_LOGERROR &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
					_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
					return false;
				}
	}
#endif
#endif
#endif
	
	_LOGERROR &lt;&lt; "Have path to initial database files: " &lt;&lt; initialDatabaseLocation-&gt;charrep() LOG_
	
	char* dbbackend = meta-&gt;getSystemDatabaseBackend();
	if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) {
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOG &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Using plugin database backend for system database setup test..." LOG_
		
        	lbDMFPasswd = getenv("lbDMFPasswd");
        	lbDMFUser   = getenv("lbDMFUser");
		
        	if (!lbDMFUser) lbDMFUser = "dba";
        	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		_LOG &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Using built in database backend for system database setup test..." LOG_
		
	        lbDMFPasswd = getenv("lbDMFPasswd");
	        lbDMFUser   = getenv("lbDMFUser");
		
	        if (!lbDMFUser) lbDMFUser = "dba";
	        if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
	}
	
	if (database == NULL) {
		_LOGERROR &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Error: Could not load database backend for system db, either plugin or built in version." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_BACKEND;
		
		return false;
	}

	if (database-&gt;init() != ERR_NONE) {
		_LOGERROR &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Failed to initialize database." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
		
		return false;
	}
	
	
	if ((database != NULL) &amp;&amp; (database-&gt;connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
		_LOGERROR &lt;&lt; "lbPluginModuleDynamicAppStorage::installDatabase() Failed to connect to system database. " &lt;&lt;
			"Please set internal default user 'dba' and password 'trainres' or set the environment " &lt;&lt;
			"variables to those used by the database (lbDMFUser, lbDMFPasswd)." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_CONNECT;
		
		return false;
	}
	
	// Check. if the system database schema is initialized.
	sysSchemaQuery = database-&gt;getQuery("lbDMF", 0);
	
	if (sysSchemaQuery != NULL) {
		// Here it goes on with installation.
		UAP(lb_I_String, SQL)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, inputApp)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, inputSys)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, systemDatabaseName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, applicationDatabaseName)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, dataDir)
		*dataDir = initialDatabaseLocation-&gt;charrep();
		
		*applicationDatabaseName = dataDir-&gt;charrep();
		
		if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) {
#ifdef WINDOWS
			*applicationDatabaseName = "..\\Database\\lbDMF-Sqlite-ApplicationDB.sql";
#endif
#ifdef OSX
			// Create data directory, if not available
			*applicationDatabaseName += "lbDMF-Sqlite-ApplicationDB.sql";
#endif
#ifdef SOLARIS
			// Create data directory, if not available
			*applicationDatabaseName += "lbDMF-Sqlite-ApplicationDB.sql";
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
			// Create data directory, if not available
			*applicationDatabaseName += "lbDMF-Sqlite-ApplicationDB.sql";
#endif
#endif
#endif
			_LOGALWAYS &lt;&lt; "Apply the SQL file to the lbDMF application database: " &lt;&lt; applicationDatabaseName-&gt;charrep() LOG_
			inputApp-&gt;setFileName(applicationDatabaseName-&gt;charrep());
			
			if (!inputApp-&gt;open()) {
#ifdef WINDOWS
				// Try the path for a typical Windows installation
				inputApp-&gt;setFileName("Database\\lbDMF-Sqlite-ApplicationDB.sql");
				if (!inputApp-&gt;open()) {
					meta-&gt;msgBox("Info", "Installation of builtin database failed.");
					return false;
				}
#endif
			}
			
			SQL = inputApp-&gt;getAsString();
			sysSchemaQuery-&gt;skipFKCollecting();
			if (sysSchemaQuery-&gt;query(SQL-&gt;charrep()) != ERR_NONE) {
				_LOGERROR &lt;&lt; "lb_MetaApplication::installDatabase() Failed to install initial system database." LOG_
				return false;
			}
			
			*systemDatabaseName = dataDir-&gt;charrep();
			
#ifdef WINDOWS
			*systemDatabaseName = "..\\Database\\lbDMF-Sqlite-SystemDB.sql";
#endif
#ifdef OSX
			*systemDatabaseName += "lbDMF-Sqlite-SystemDB.sql";
#endif
#ifdef SOLARIS
			*systemDatabaseName += "lbDMF-Sqlite-SystemDB.sql";
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
			*systemDatabaseName += "lbDMF-Sqlite-SystemDB.sql";
#endif
#endif
#endif
			_LOGALWAYS &lt;&lt; "Apply the SQL file to the lbDMF system database: " &lt;&lt; systemDatabaseName-&gt;charrep() LOG_
		
			inputSys-&gt;setFileName(systemDatabaseName-&gt;charrep());
			
			if (!inputSys-&gt;open()) {
#ifdef WINDOWS
				// Try the path for a typical Windows installation
				inputSys-&gt;setFileName("Database\\lbDMF-Sqlite-SystemDB.sql");
				if (!inputSys-&gt;open()) {
					_LOGERROR &lt;&lt; "lb_MetaApplication::installDatabase() Failed to install initial system database. File not found." LOG_
					meta-&gt;msgBox("Info", "Installation of builtin database failed.");
					return false;
				}
#endif
			}
			SQL = inputSys-&gt;getAsString();
			sysSchemaQuery-&gt;skipFKCollecting();
			if (sysSchemaQuery-&gt;query(SQL-&gt;charrep()) != ERR_NONE) {
				_LOGERROR &lt;&lt; "lb_MetaApplication::installDatabase() Failed to install initial system database." LOG_
				return false;
			}
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_String, systemDatabaseName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, applicationDatabaseName)
			
			char* home = getenv("HOME");
			UAP_REQUEST(getModuleInstance(), lb_I_String, dataDir)
			*dataDir = initialDatabaseLocation-&gt;charrep();
			
			*applicationDatabaseName = dataDir-&gt;charrep();
			
#ifdef WINDOWS
			*applicationDatabaseName = "..\\Database\\lbDMF-PostgreSQL.sql";
#endif
#ifdef OSX
			*applicationDatabaseName = "lbDMF-PostgreSQL.sql";
#endif
#ifdef SOLARIS
			*applicationDatabaseName = "lbDMF-PostgreSQL.sql";
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
			*applicationDatabaseName = "lbDMF-PostgreSQL.sql";
#endif
#endif
#endif
			_LOGALWAYS &lt;&lt; "Apply the SQL file to the lbDMF application database: " &lt;&lt; applicationDatabaseName-&gt;charrep() LOG_

			inputApp-&gt;setFileName(applicationDatabaseName-&gt;charrep());
			if (!inputApp-&gt;open()) {
#ifdef WINDOWS
				inputApp-&gt;setFileName("Database\\lbDMF-PostgreSQL.sql");
#endif
				if (!inputApp-&gt;open()) {
					_LOGERROR &lt;&lt; "lb_MetaApplication::installDatabase() Failed to install initial system database. File not found." LOG_
					meta-&gt;msgBox("Info", "Installation of builtin database failed.");
					return false;
				}
			}
			SQL = inputApp-&gt;getAsString();
			sysSchemaQuery-&gt;skipFKCollecting();
			if (sysSchemaQuery-&gt;query(SQL-&gt;charrep()) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
				_LOGERROR &lt;&lt; "lb_MetaApplication::installDatabase() Failed to install initial system database." LOG_
				*msg = "Installation of system database failed. Check the permissions of the user '";
				*msg += lbDMFUser;
				*msg += "'.";
				meta-&gt;msgBox("Info", msg-&gt;charrep());
				return false;
			}
			sysSchemaQuery-&gt;close();
			database-&gt;close();
		}
	}
#ifdef LINUX
	UAP_REQUEST(getModuleInstance(), lb_I_String, installdir)
	home =
#if defined(WINDOWS)
	getenv("USERPROFILE");
#endif
#if defined(UNIX) || defined(LINUX) || defined(OSX)
	getenv("HOME");
#endif
	*installdir = home;
	*installdir += "/develop/Projects/CPP/Test/GUI/wxWrapper";
	meta-&gt;setDirLocation(installdir-&gt;charrep());
#endif

	// Also the application requires an authenticated user
	UAP(lb_I_SecurityProvider, securityManager)
	AQUIRE_PLUGIN(lb_I_SecurityProvider, Default, securityManager, "No security provider found.")

	if (securityManager != NULL) {
		securityManager-&gt;login("user", "TestUser"); // A fresh installed database should have this default user.
	
		UAP(lb_I_Unknown, uk)
		
		UAP(lb_I_Container, apps)
		apps = securityManager-&gt;getApplications();
		
		apps-&gt;finishIteration();
		while (apps-&gt;hasMoreElements() == 1)
		{
			UAP(lb_I_String, name)
			uk = apps-&gt;nextElement();
			QI(uk, lb_I_String, name)
			
			if (*name == "lbDMF Manager") {
				UAP(lb_I_Long, id)
				UAP(lb_I_KeyBase, key)
				key = apps-&gt;currentKey();
				QI(key, lb_I_Long, id)
				securityManager-&gt;setCurrentApplicationId(id-&gt;getData());
			}
		}
		
	
	
		meta-&gt;msgBox("Info",
			   "This application is running the first time on this computer,\n"
			   "or your prior configured database is not available anyhow.\n\n"
			   "Please inform your administrator, if the database is not available.\n\n"
			   "Otherwise, you currently work in a local initial database version.\n\n"
			   "And you are automatically logged in as an 'administrator'.\n\n"
			   "For security considerations please change the password for\n"
			   "your user account, wich is currently the default 'user'.");

		// While the plugin get's initialized meta-&gt;load() must have been called to enable the following two functions.
		meta-&gt;setUserName("user");
		meta-&gt;setApplicationName("lbDMF Manager");
		
		meta-&gt;setAutoload(true);
		meta-&gt;setGUIMaximized(true); // Otherwise the toolbar is bigger than frame width. Default size should be changed.
		meta-&gt;save(); // Save, because otherwise the usage of DatabaseLayerGateway gets overwritten by created standard version of first try of loading the file.
	} else {
		meta-&gt;msgBox("Info",
			   "The security module responsible to provide login functionality could not be loaded. "
			   "Only applications without user management are possible. Automatic application load "
			   "will also not be possible.");

		meta-&gt;setGUIMaximized(true); // Otherwise the toolbar is bigger than frame width. Default size should be changed.
		meta-&gt;save(); // Save, because otherwise the usage of DatabaseLayerGateway gets overwritten by created standard version of first try of loading the file.
	}
	return true;
}


lbPluginModuleDynamicAppStorage::lbPluginModuleDynamicAppStorage() {
	
	// Nothing checked yet.
	_check_for_databases_failure_step = -1;

	REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
}

lbPluginModuleDynamicAppStorage::~lbPluginModuleDynamicAppStorage() {
	_CL_VERBOSE &lt;&lt; "lbPluginModuleDynamicAppStorage::~lbPluginModuleDynamicAppStorage() called." LOG_
}

void LB_STDCALL lbPluginModuleDynamicAppStorage::initialize() {
	_CL_VERBOSE &lt;&lt; "lbPluginModuleDynamicAppStorage::initialize() called." LOG_
	enumPlugins();
	
}

void LB_STDCALL lbPluginModuleDynamicAppStorage::install() {
	// The check may have several rounds.
	while (!checkForDatabases()) {
		if (_check_for_databases_failure_step == -2) break; //
		
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_BACKEND) {
			//meta-&gt;msgBox("Error", "No system database backed available. Please check your installation and logfile!");
			meta-&gt;setSystemDatabaseBackend("DatabaseLayerGateway");
            meta-&gt;setApplicationDatabaseBackend("DatabaseLayerGateway");
            meta-&gt;useSystemDatabaseBackend(true);
            meta-&gt;useApplicationDatabaseBackend(true);
			
			if (!installDatabase()) {
				meta-&gt;msgBox("Error", "Fallback to local database variant failed too!");
				break;
			}
			
			break;
		}
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_INITIALIZE) {
			meta-&gt;msgBox("Error", "Initialize system database backend failed. Please check your installation and logfile!");
			
			break;
		}
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_CONNECT) {
            // Assume no database available. Use local Sqlite variant.
            meta-&gt;setSystemDatabaseBackend("DatabaseLayerGateway");
            meta-&gt;setApplicationDatabaseBackend("DatabaseLayerGateway");
            meta-&gt;useSystemDatabaseBackend(true);
            meta-&gt;useApplicationDatabaseBackend(true);
			
			if (!installDatabase()) {
				meta-&gt;msgBox("Error", "Connect to system database backend failed and fallback to local database variant failed too!");
				break;
			}
		}
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_SCHEMA) {
			if (!installDatabase()) {
                if (meta-&gt;askYesNo(
							 "The ODBC system database is reachable and a login was successfull,\n"
							 "but is not properly setup. A try to install the database failed.\n\n"
							 "Do you like to use a local Sqlite database instead?"))
                {
                    meta-&gt;setSystemDatabaseBackend("DatabaseLayerGateway");
                    meta-&gt;setApplicationDatabaseBackend("DatabaseLayerGateway");
                    meta-&gt;useSystemDatabaseBackend(true);
                    meta-&gt;useApplicationDatabaseBackend(true);
					
                    if (!installDatabase()) {
                        meta-&gt;msgBox("Error", "Fallback to local database variant failed too!");
                        _check_for_databases_failure_step = -2;
                    }
                } else {
                    _check_for_databases_failure_step = -2;
                }
			}
		}
	}
	
	if (_check_for_databases_failure_step == -2) {
		meta-&gt;msgBox("Error", "Setup of databases, required by this application failed!");
	}
}

lbErrCodes LB_STDCALL lbPluginModuleDynamicAppStorage::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "lbPluginModuleDynamicAppStorage::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_LOG &lt;&lt; "Cloning object with " &lt;&lt; uk-&gt;getRefCount() &lt;&lt; " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
</xsl:template>
</xsl:stylesheet>
