<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
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

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>


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


<xsl:template name="CreateDataViewModelBaseclass">

<exsl:document href="{$basedir}/{$appexecutedir}/{$ApplicationName}/{$ApplicationName}Base.h" method="text">
/* Base class for data view models
 *  <xsl:value-of select="$ApplicationName"/>
 */
 
#ifndef DATA_VIEW_MODEL_<xsl:value-of select="$ApplicationName"/>
#define DATA_VIEW_MODEL_<xsl:value-of select="$ApplicationName"/>

class DataViewBase :
	public wxDataViewListModel {
public:
	DataViewBase();
	virtual ~DataViewBase();

	virtual bool InitModel() = 0;
	virtual long GetLongField(unsigned int col, unsigned int row ) = 0;
	virtual wxString GetStringField(unsigned int col, unsigned int row ) = 0;
	virtual bool GetBoolField(unsigned int col, unsigned int row ) = 0;
	virtual wxDateTime GetDateField(unsigned int col, unsigned int row ) = 0;

	virtual unsigned int GetNumberOfRows();
	virtual unsigned int GetNumberOfCols();
	virtual wxString GetColType( unsigned int col );
	virtual void GetValue( wxVariant &variant, unsigned int col, unsigned int row );
	virtual bool SetValue( wxVariant &value, unsigned int col, unsigned int row );

private:
	wxArrayString m_columnTypes;

	// Column names are orginally not here, but may be needed.
	//wxArrayString m_columnNames;

	// The primary identifer
	wxArrayLong m_columnID;
};

// Predefined classes
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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
class <xsl:value-of select="$FormularName"/>;
</xsl:for-each>

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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
#include &lt;lbDMFManager<xsl:value-of select="$FormularName"/>Implementation.h&gt;
</xsl:for-each>



#endif //DATA_VIEW_MODEL_<xsl:value-of select="$ApplicationName"/>
</exsl:document>

<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/{$ApplicationName}Base.cpp" method="text">
/* Base class for data view models
 *  <xsl:value-of select="$ApplicationName"/>
 */

/////////////////////////////////////////////////////////////////////////////
// Name:        <xsl:value-of select="$ApplicationName"/>.cpp
// Purpose:     DataViewCtrl wxWidgets baseclass for application <xsl:value-of select="$ApplicationName"/>
// Author:      Lothar Behrens
// Modified by:
// Created:     2008/09/14 (Template)
// RCS-ID:      $Id: lbDMFDataViewModelBaseclass.xsl,v 1.2 2011/02/27 10:34:00 lollisoft Exp $
// Copyright:   (c) Lothar Behrens
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/datetime.h"

#ifndef __WXMSW__
    #include "../sample.xpm"
#endif

#include "null.xpm"

#include "wx/dataview.h"


// Include base class definition
#include &lt;<xsl:value-of select="$ApplicationName"/>Base.h&gt;

// Begin implementation code


WX_DECLARE_LIST(wxDateTime,wxArrayDate);
#include <wx/listimpl.cpp>
WX_DEFINE_LIST(wxArrayDate)


DataViewBase::DataViewBase()
{
	if (!InitModel()) {
		// Handle this error anyhow ...
	}
}

DataViewBase::~DataViewBase()
{

}

unsigned int DataViewBase::GetNumberOfRows()
{
	return m_columnID.Count();
}

unsigned int DataViewBase::GetNumberOfCols()
{
	return m_columnTypes.Count();
}

// as reported by wxVariant
wxString DataViewBase::GetColType( unsigned int col )
{
	return m_columnTypes[col];
}

void DataViewBase::GetValue( wxVariant &variant, unsigned int col, unsigned int row )
{

}

bool DataViewBase::SetValue( wxVariant &value, unsigned int col, unsigned int row )
{
	return true;
}








// Plugin module code

class lbPluginModule<xsl:value-of select="$ApplicationName"/> : public lb_I_PluginModule {
public:

	lbPluginModule<xsl:value-of select="$ApplicationName"/>();
	virtual ~lbPluginModule<xsl:value-of select="$ApplicationName"/>();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModule<xsl:value-of select="$ApplicationName"/>)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModule<xsl:value-of select="$ApplicationName"/>)

BEGIN_PLUGINS(lbPluginModule<xsl:value-of select="$ApplicationName"/>)
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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
	ADD_PLUGIN(lbPlugin<xsl:value-of select="$FormularName"/>, FixedDBForm_<xsl:value-of select="$FormularName"/>)
</xsl:for-each>
	ADD_PLUGIN(lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>, Installer)
END_PLUGINS()

lbPluginModule<xsl:value-of select="$ApplicationName"/>::lbPluginModule<xsl:value-of select="$ApplicationName"/>() {
	ref = STARTREF;
	_CL_VERBOSE &lt;&lt; "lbPluginModule<xsl:value-of select="$ApplicationName"/>::lbPluginModule<xsl:value-of select="$ApplicationName"/>() called." LOG_
}

lbPluginModule<xsl:value-of select="$ApplicationName"/>::~lbPluginModule<xsl:value-of select="$ApplicationName"/>() {
	_CL_VERBOSE &lt;&lt; "lbPluginModule<xsl:value-of select="$ApplicationName"/>::~lbPluginModule<xsl:value-of select="$ApplicationName"/>() called." LOG_
}

void LB_STDCALL lbPluginModule<xsl:value-of select="$ApplicationName"/>::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModule<xsl:value-of select="$ApplicationName"/>::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "lbPluginModule<xsl:value-of select="$ApplicationName"/>::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE &lt;&lt; "Cloning object with " &lt;&lt; uk->getRefCount() &lt;&lt; " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

class InstallMenuEntry<xsl:value-of select="$ApplicationName"/> : 
	public lb_I_Unknown,
	public lb_I_LogonHandler,
	public lb_I_EventHandler {
public:
		InstallMenuEntry<xsl:value-of select="$ApplicationName"/>();
		virtual ~InstallMenuEntry<xsl:value-of select="$ApplicationName"/>();

		DECLARE_LB_UNKNOWN()

		lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
		lbErrCodes LB_STDCALL runInstallMenuEntry<xsl:value-of select="$ApplicationName"/>(lb_I_Unknown* uk);
		
		wxWizard *wizard;
		wxWizardPageSimple *page1;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(InstallMenuEntry<xsl:value-of select="$ApplicationName"/>)
	ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &amp;InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::runInstallMenuEntry<xsl:value-of select="$ApplicationName"/>, "RunInstallMenuEntry<xsl:value-of select="$ApplicationName"/>");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::runInstallMenuEntry<xsl:value-of select="$ApplicationName"/>(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	char ptr[20] = "";
	sprintf(ptr, "%p", this);

	UAP(lb_I_Database, database)
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	
	char* dbbackend = meta->getApplicationDatabaseBackend();
	if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOG &lt;&lt; "Using plugin database backend for UML import operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		_LOG &lt;&lt; "Using built in database backend for UML import operation..." LOG_
	}

	
	database->init();
	if (database->connect("lbDMF", "lbDMF", "dba", "trainres") != ERR_NONE) {
		_LOG &lt;&lt; "Error: Could not connect to given database: '" &lt;&lt; "lbDMF" &lt;&lt; "'" LOG_

		return ERR_NONE;
	}


<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
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
	{
		UAP(lb_I_Query, q)
		UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
		q = database->getQuery("lbDMF", 0);
		
		if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) 
			*sql = "--SkipRewrite\n";
		else
			*sql = "";
		*sql += "select id, handlerinterface, namespace, beschreibung from formulartypen where namespace = '";
		*sql += "FixedDBForm_<xsl:value-of select="$FormularName"/>'";
		
		q->skipFKCollecting();
		err = q->query(sql->charrep());
		
		if (err == ERR_NONE) {
			err = q->first();
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				_LOG &lt;&lt; "No modification to dynamic formular '<xsl:value-of select="$FormularName"/>' definition needed." LOG_
			} else {
				// Install custom form
				_LOG &lt;&lt; "Modification to dynamic formular '<xsl:value-of select="$FormularName"/>' definition needed." LOG_
				if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) 
					*sql = "--SkipRewrite\n";
				else
					*sql = "";
				*sql += "insert into formulartypen (namespace, beschreibung, handlerinterface) values ('FixedDBForm_<xsl:value-of select="$FormularName"/>', 'Fest verdrahtetes <xsl:value-of select="$FormularName"/> Formular', 'lb_I_FixedDatabaseForm')";
				q->query(sql->charrep());
				
				q = database->getQuery("lbDMF", 0);
				q->skipFKCollecting();
				
				if (q->query(sql->charrep()) == ERR_NONE) {
					UAP(lb_I_String, ID)
					UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
					err = q->first();
					_LOG &lt;&lt; "Try to get new type ID for '<xsl:value-of select="$FormularName"/>'." LOG_
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						ID = q->getAsString(1);
						
						if (dbbackend != NULL &amp;&amp; strcmp(dbbackend, "") != 0) 
							*SQL = "--SkipRewrite\n";
						else
							*SQL = "";
						*SQL += "update formulare set typ = ";
						*SQL += ID->charrep();
						*SQL += " where name = '<xsl:value-of select="$tempFormularName"/>' and anwendungid = <xsl:value-of select="$ApplicationID"/>";

						_LOG &lt;&lt; "Install custom formular '<xsl:value-of select="$FormularName"/>'." LOG_

						q = database->getQuery("lbDMF", 0);
						q->skipFKCollecting();
						
						if (q->query(SQL->charrep()) != ERR_NONE) {
							_LOG &lt;&lt; "Installation of custom formular '<xsl:value-of select="$FormularName"/>' failed." LOG_
						}
					} else {
						_LOG &lt;&lt; "Failed to re-read the ID for the currently inserted formular type ('<xsl:value-of select="$FormularName"/>') ! Query: " &lt;&lt; sql->charrep() LOG_
					}
				} else {
					_LOG &lt;&lt; "Failed to re-read the ID for the currently inserted formular type ('<xsl:value-of select="$FormularName"/>') !" LOG_
				}
			}
		}
	}
</xsl:for-each>

	return ERR_NONE;
}

InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::InstallMenuEntry<xsl:value-of select="$ApplicationName"/>() {
	ref = STARTREF;
}

InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::~InstallMenuEntry<xsl:value-of select="$ApplicationName"/>() {
	_CL_VERBOSE &lt;&lt; "InstallMenuEntry<xsl:value-of select="$ApplicationName"/>::~InstallMenuEntry<xsl:value-of select="$ApplicationName"/>() called." LOG_
}



class lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/> :
	public lb_I_PluginImpl
{
public:

	lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>();
	virtual ~lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>();

	DECLARE_LB_UNKNOWN()
	
	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	/** \brief Init the menu emtries.
	 *
	 * This connects the login feature to a menu.
	 */
	virtual void LB_STDCALL initialize();
	
	/** \brief Run the login manually.
	 *
	 * This let the login wizard appear manually without invoking it from
	 * the menu entry. You could use this to start the login wizard automatically.
	 */
	virtual bool LB_STDCALL run();

	/** \brief Get the underlying implementation.
	 *
	 * Not needed in this implementation. This implementation has no separate
	 * class with the implementation. This is due to the not existing problem
	 * of multible base class inheritation of lb_I_Unknown.
	 *
	 * If multible intarfaces could be queried, then each
	 */
	virtual lb_I_Unknown* LB_STDCALL getImplementation();

	virtual lb_I_Unknown* LB_STDCALL peekImplementation();
	void LB_STDCALL releaseImplementation();
	
	UAP(lb_I_Unknown, loginHandler)
};	

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>, lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>)

lbErrCodes LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>() {
	ref = STARTREF;
}

lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::~lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>() {
	_CL_VERBOSE &lt;&lt; "lbPluginLoginWizard::~lbPluginLoginWizard() called." LOG_
}

bool LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::autorun() {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev)
	
	int lEvent;
	
	ev->registerEvent("RunInstallMenuEntry<xsl:value-of select="$ApplicationName"/>", lEvent);

	UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, disp)
	
	InstallMenuEntry<xsl:value-of select="$ApplicationName"/>* hdl = new InstallMenuEntry<xsl:value-of select="$ApplicationName"/>();
	hdl->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	QI(hdl, lb_I_Unknown, loginHandler)
	
	hdl->registerEventHandler(*&amp;disp);

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	char* file = strdup(_trans("&amp;Plugins"));
	char* entry = strdup(_trans("Install Fixed formulars for <xsl:value-of select="$ApplicationName"/>"));
	
	meta->addMenu(file);
	meta->addMenuEntry(file, entry, "RunInstallMenuEntry<xsl:value-of select="$ApplicationName"/>", "");
	
	free(file);
	free(entry);

	return err;
}

/*...svoid LB_STDCALL lbPluginLoginWizard\58\\58\initialize\40\\41\:0:*/
void LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::initialize() {
}
/*...e*/

/*...sbool LB_STDCALL lbPluginLoginWizard\58\\58\run\40\\41\:0:*/
bool LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::run() {
	return true;
}
/*...e*/

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginLoginWizard\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	return this;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginLoginWizard\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::getImplementation() {
	lbErrCodes err = ERR_NONE;

	return this;
}
/*...e*/
void LB_STDCALL lbPluginInstallMenuEntry<xsl:value-of select="$ApplicationName"/>::releaseImplementation() {
	_CL_VERBOSE &lt;&lt; "lbPluginLoginWizard::releaseImplementation() called." LOG_
}



</exsl:document>

</xsl:template>

</xsl:stylesheet>
