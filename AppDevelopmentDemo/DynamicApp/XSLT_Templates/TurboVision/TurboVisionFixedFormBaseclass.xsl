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


<xsl:template name="CreateFixedFormBaseclass">

<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/{$ApplicationName}Base.h" method="text">
/* Base class for fixed database formular header file
 *  <xsl:value-of select="$ApplicationName"/>
 */
 
#ifndef FIXED_FORMULAR_<xsl:value-of select="$ApplicationName"/>
#define FIXED_FORMULAR_<xsl:value-of select="$ApplicationName"/>

class FixedFormularBase :
	public lb_I_FixedDatabaseForm,
	public wxPanel {
public:
	FixedFormularBase();
	virtual ~FixedFormularBase();

	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);
	char*	   LB_STDCALL getFormName() { return formName; }

	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	lbErrCodes LB_STDCALL addOwnerDrawn(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	void LB_STDCALL create(int parentId);
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() {
	    if (_created) Destroy();
		_created = false;
	};
	
	char* LB_STDCALL getQuery();

	void LB_STDCALL setFilter(char* filter);
	
	const lb_I_String* LB_STDCALL getControlValue(char* name);

	int LB_STDCALL getPrimaryColumns();
	
	const lb_I_String* LB_STDCALL getControlValue(int pos);
	int LB_STDCALL getControls();
	
	lb_I_String* LB_STDCALL getPrimaryColumn(int pos);
	   
	int LB_STDCALL getForeignColumns(char* primaryTable);
	
	lb_I_String* LB_STDCALL getForeignColumn(int pos);
	   
	bool LB_STDCALL isCharacterColumn(char* name);

	lb_I_String* LB_STDCALL getTableName(char* columnName);
	
	lb_I_String* LB_STDCALL getColumnName(int pos);

	virtual lbErrCodes LB_STDCALL lbDBUpdate() = 0;
	virtual lbErrCodes LB_STDCALL lbDBClear() = 0;
	virtual lbErrCodes LB_STDCALL lbDBRead() = 0;

	lbErrCodes LB_STDCALL lbDBDelete(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbDBFirst(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL lbDBNext(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL lbDBPrev(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL lbDBLast(lb_I_Unknown* uk);

	void OnDispatch(wxCommandEvent&amp; event);
	void OnImageButtonClick(wxCommandEvent&amp; event);
	void OnMouseMove(wxMouseEvent&amp; evt);

	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)
	UAP(lb_I_String, SQLString)
	UAP(lb_I_String, SQLWhere)

	UAP(lb_I_String, _DBName)
	UAP(lb_I_String, _DBUser)
	UAP(lb_I_String, _DBPass)
	
	UAP(lb_I_Container, ComboboxMapperList)
	UAP(lb_I_Container, ImageButtonMapperList)
	
	UAP(lb_I_Container, actions)

	UAP(lb_I_String, app)
	UAP(lb_I_String, masterForm)
	UAP(lb_I_String, detailForm)
	UAP(lb_I_String, SourceFieldName)
	UAP(lb_I_String, SourceFieldValue)
	UAP(lb_I_String, DBName)
	UAP(lb_I_String, DBUser)
	UAP(lb_I_String, DBPass)
	UAP(lb_I_Container, MasterDetailRelationData)

	long l;
	
	wxWindow* firstButton;
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
	wxWindow* deleteButton;
	wxWindow* addingButton;

	bool allNaviDisabled;	
	bool noDataAvailable;
	bool isAdding;
	bool _created;
	
	char* base_formName;
	char* formName;
	char* untranslated_formName;
};


#define DISABLE_EOF() \
	if (allNaviDisabled == false) { \
		nextButton-&gt;Disable(); \
		lastButton-&gt;Disable(); \
		firstButton-&gt;Enable(); \
		prevButton-&gt;Enable(); \
		deleteButton-&gt;Enable(); \
	} \
	allNaviDisabled = false;


#define DISABLE_BOF() \
	if (allNaviDisabled == false) { \
		prevButton-&gt;Disable(); \
		firstButton-&gt;Disable(); \
		lastButton-&gt;Enable(); \
		nextButton-&gt;Enable(); \
		deleteButton-&gt;Enable(); \
	} \
	allNaviDisabled = false;


#define DISABLE_FOR_ONE_DATA() \
	prevButton-&gt;Disable(); \
	firstButton-&gt;Disable(); \
	lastButton-&gt;Disable(); \
	nextButton-&gt;Disable();


#define DISABLE_FOR_NO_DATA() \
	DISABLE_FOR_ONE_DATA() \
	deleteButton-&gt;Disable(); \
	allNaviDisabled = true;


<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
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

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
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



#endif //FIXED_FORMULAR_<xsl:value-of select="$ApplicationName"/>
</exsl:document>

<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/{$ApplicationName}Base.cpp" method="text">
/* Base class for fixed database formular
 *  <xsl:value-of select="$ApplicationName"/>
 */

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
#include &lt;malloc.h&gt;
#endif
#ifdef OSX
#include &lt;sys/malloc.h&gt;
#endif

#include &lt;lbConfigHook.h&gt;
#include &lt;lbInterfaces.h&gt;

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#ifdef __GNUG__
#pragma implementation "<xsl:value-of select="$ApplicationName"/>.cpp"
#pragma interface "<xsl:value-of select="$ApplicationName"/>.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include &lt;wx/wxprec.h&gt;

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include &lt;wx/wx.h&gt;
#endif

#include &lt;wx/wizard.h&gt;
#include &lt;wx/image.h&gt;

// Include base class definition
#include &lt;<xsl:value-of select="$ApplicationName"/>Base.h&gt;

// Begin implementation code

FixedFormularBase::FixedFormularBase() 
{
	_CL_LOG &lt;&lt; "FixedFormularBase::FixedFormularBase() called." LOG_
	untranslated_formName = NULL;
	base_formName = NULL;
	noDataAvailable = false;
	_created = false;
	REQUEST(getModuleInstance(), lb_I_Container, ComboboxMapperList)
}

FixedFormularBase::~FixedFormularBase() {
	_CL_LOG &lt;&lt; "FixedFormularBase::~FixedFormularBase() called." LOG_

	free (formName);
	free (base_formName);
	free (untranslated_formName);
}

void FixedFormularBase::OnDispatch(wxCommandEvent&amp; event ) {
        switch (event.GetId()) {
        default:
                // Delegate all other events
                {
                	lbErrCodes err = ERR_NONE;
					lb_I_Module* m = getModuleInstance();
			
					UAP_REQUEST(m, lb_I_EventManager, eman)
		
					UAP_REQUEST(m, lb_I_Dispatcher, dispatcher)
					dispatcher-&gt;setEventManager(eman.getPtr());

					UAP_REQUEST(m, lb_I_Integer, param)
			
					param-&gt;setData(event.GetId());
			
					UAP(lb_I_Unknown, uk)
					QI(param, lb_I_Unknown, uk)
		
					UAP_REQUEST(m, lb_I_String, result)
					UAP(lb_I_Unknown, uk_result)
					QI(result, lb_I_Unknown, uk_result)
		
					if (formName != NULL) {
						_LOG &lt;&lt; "FixedFormularBase::OnDispatch(" &lt;&lt; event.GetId() &lt;&lt; ") called ('" &lt;&lt; formName &lt;&lt; "')" LOG_
					} else {
						_LOG &lt;&lt; "FixedFormularBase::OnDispatch(" &lt;&lt; event.GetId() &lt;&lt; ") called ('" &lt;&lt; getClassName() &lt;&lt; "')" LOG_
					}
					dispatcher-&gt;dispatch(event.GetId(), uk.getPtr(), &amp;uk_result);
                }
                break;
        }
}

void LB_STDCALL FixedFormularBase::create(int parentId) {
	wxWindow* w = FindWindowById(parentId);
	
	Create(w, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panel");
	SetFocus();
	_created = true;
}

lbErrCodes LB_STDCALL FixedFormularBase::setName(char const * name, char const * appention) {
	if (formName) free(formName);
	if (untranslated_formName) free(untranslated_formName);

	char* transl = _trans((char*) name);
		
	char* temp = (char*) malloc(strlen(transl)+1);
	temp[0] = 0;
	strcpy(temp, transl);

	if (appention) {
		formName = (char*) malloc(1+strlen(temp)+strlen(appention));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name)+strlen(appention));
	} else {
		formName = (char*) malloc(1+strlen(temp));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name));
	}
	
	formName[0] = 0;
	strcat(formName, temp);
	if (appention) strcat(formName, appention);
	free(temp);
		
	untranslated_formName[0] = 0;
	strcat(untranslated_formName, name);
	if (appention) strcat(untranslated_formName, appention);
		
	base_formName[0] = 0;
	strcat(base_formName, name);
		
	return ERR_NONE;
}

char* LB_STDCALL FixedFormularBase::getQuery() {
	return SQLString-&gt;charrep();
}

lb_I_String* LB_STDCALL FixedFormularBase::getColumnName(int pos) {
	return sampleQuery-&gt;getColumnName(pos);
}

int LB_STDCALL FixedFormularBase::getControls() {
	return sampleQuery-&gt;getColumns();
}

const lb_I_String* LB_STDCALL FixedFormularBase::getControlValue(int pos) {
	UAP(lb_I_String, v)
	v = getColumnName(pos);
	return getControlValue(v->charrep());
}

const lb_I_String* LB_STDCALL FixedFormularBase::getControlValue(char* name) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	wxWindow* w = FindWindowByName(wxString(name), this);
	lb_I_Query::lbDBColumnTypes coltype = sampleQuery-&gt;getColumnType(name);

	switch (coltype) {
		case lb_I_Query::lbDBColumnBit:
			{
				wxCheckBox *check = (wxCheckBox*) w;
				if (check-&gt;GetValue() == TRUE) {
					*value = "true";
				} else {
					*value = "false";
				}
			}
			break;
					
		case lb_I_Query::lbDBColumnChar:
			{
				wxTextCtrl* tx = (wxTextCtrl*) w;
			
				*value = tx-&gt;GetValue().c_str();
			}
			break;
			
		case lb_I_Query::lbDBColumnInteger:
			{
				wxTextCtrl* tx = (wxTextCtrl*) w;
			
				*value = tx-&gt;GetValue().c_str();
			}
			break;
					
		case lb_I_Query::lbDBColumnUnknown:
			break;
	}

	value++;
	return value.getPtr();
}

void LB_STDCALL FixedFormularBase::setFilter(char* filter) {
	if (SQLWhere == NULL) {
		REQUEST(getModuleInstance(), lb_I_String, SQLWhere)
	}

	if (filter != NULL) SQLWhere-&gt;setData(filter);
}

lb_I_String* FixedFormularBase::getTableName(char* columnName) {
	return sampleQuery-&gt;getTableName(columnName);
}

int LB_STDCALL FixedFormularBase::getPrimaryColumns()
{
	int PKColumns = sampleQuery-&gt;getPKColumns();
	
	return PKColumns;
}

int LB_STDCALL FixedFormularBase::getForeignColumns(char* primaryTable)
{
	int PKColumns = sampleQuery-&gt;getFKColumns();
	
	return PKColumns;
}
	
lb_I_String* LB_STDCALL FixedFormularBase::getPrimaryColumn(int pos)
{
	return sampleQuery-&gt;getPKColumn(pos);
}

lb_I_String* LB_STDCALL FixedFormularBase::getForeignColumn(int pos)
{
	return sampleQuery-&gt;getFKColumn(pos);
}

bool LB_STDCALL FixedFormularBase::isCharacterColumn(char* name)
{
	return sampleQuery-&gt;getColumnType(name) == lb_I_Query::lbDBColumnChar;
}

lbErrCodes LB_STDCALL FixedFormularBase::lbDBFirst(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	// Indicate save action
	addingButton->SetLabel(_trans("Add"));

	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;

	lbDBClear();

	err = sampleQuery-&gt;first();

	while (err == ERR_DB_ROWDELETED) err = sampleQuery-&gt;next();

	if (err == ERR_DB_NODATA) {
		sampleQuery-&gt;reopen();
		
		err = sampleQuery->first();
		
		if (err == ERR_DB_NODATA) {
			DISABLE_FOR_NO_DATA()

			return ERR_DB_NODATA;
		} else {
			DISABLE_BOF()
		}
	}

	lbDBRead();
	
	DISABLE_BOF()

	return ERR_NONE;
}

lbErrCodes LB_STDCALL FixedFormularBase::lbDBNext(lb_I_Unknown* uk) {
	// Indicate save action
	addingButton->SetLabel(_trans("Add"));

	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;

	lbErrCodes err = sampleQuery->next();

	// Skip all deleted rows
	while (err == ERR_DB_ROWDELETED) err = sampleQuery->next();
	
	if (err == WARN_DB_NODATA) {
		nextButton->Disable();
		lastButton->Disable();
	}

	if (err == ERR_DB_NODATA) {
		sampleQuery->reopen();
		
		err = sampleQuery->last();
		
		if (err == ERR_DB_NODATA) {
			prevButton->Disable();
			firstButton->Disable();
			return ERR_DB_NODATA;
		} else {
			DISABLE_EOF()
		}
		
	} else {
		prevButton->Enable();
		firstButton->Enable();
		deleteButton->Enable();
	
		lbDBClear();
	}
		
	lbDBRead();

	return ERR_NONE;
}

lbErrCodes LB_STDCALL FixedFormularBase::lbDBPrev(lb_I_Unknown* uk) {
	// Indicate save action
	addingButton->SetLabel(_trans("Add"));

	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;

	lbErrCodes err = sampleQuery->previous();

	// Skip all deleted rows
	while (err == ERR_DB_ROWDELETED) err = sampleQuery->previous();

	if (err == WARN_DB_NODATA) {
		prevButton->Disable();
		firstButton->Disable();
	}

	if (err == ERR_DB_NODATA) {
	
		sampleQuery->reopen();
		err = sampleQuery->first();
		
		if (err == ERR_DB_NODATA) {
			nextButton->Disable();
			lastButton->Disable();
			return ERR_DB_NODATA;
		} else {
			DISABLE_BOF()
		}
	} else {
		nextButton->Enable();
		lastButton->Enable();
		deleteButton->Enable();

		lbDBClear();
	}

	lbDBRead();

	return ERR_NONE;
}

lbErrCodes LB_STDCALL FixedFormularBase::lbDBLast(lb_I_Unknown* uk) {
	// Indicate save action
	addingButton->SetLabel(_trans("Add"));

	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;
	lbDBClear();

	lbErrCodes err = sampleQuery->last();
	
	while (err == ERR_DB_ROWDELETED) err = sampleQuery->previous();

	if (err == ERR_DB_NODATA) {
		sampleQuery->reopen();
		err = sampleQuery->last();
	
		if (err == ERR_DB_NODATA) {
			DISABLE_FOR_NO_DATA()

			return ERR_DB_NODATA;
		}
	}

	lbDBRead();

	DISABLE_EOF()

	return ERR_NONE;
}

lbErrCodes LB_STDCALL FixedFormularBase::lbDBDelete(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	err = sampleQuery->remove();

	if (err == INFO_DB_REOPENED) {
		lbDBRead();
		return ERR_NONE;	
	} else {
		if (err == ERR_DB_NODATA) {
			err = sampleQuery->first();
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				DISABLE_BOF()
				lbDBRead();
				return ERR_NONE;
			} else {
				lbDBClear();
				DISABLE_FOR_NO_DATA()
				return ERR_NONE;
			}
		}
	
	        err = sampleQuery->next();

	        if (err == WARN_DB_NODATA) {
	        	DISABLE_EOF()

			lbDBRead();

			return ERR_NONE;
	        }

	        if (err == ERR_DB_NODATA) {

			err = sampleQuery->first();

			if (err == ERR_DB_NODATA) {

				DISABLE_FOR_NO_DATA()
			
				lbDBClear();

				return ERR_NONE;
			}
	
			DISABLE_BOF()
	        } else {
	        	nextButton->Enable();
	        	lastButton->Enable();
	        	prevButton->Enable();
	        	firstButton->Enable();
	        }
	}
	
	lbDBRead();

	return ERR_NONE;
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
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
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
END_PLUGINS()

lbPluginModule<xsl:value-of select="$ApplicationName"/>::lbPluginModule<xsl:value-of select="$ApplicationName"/>() {
	ref = STARTREF;
	_CL_VERBOSE &lt;&lt; "lbPluginModule<xsl:value-of select="$ApplicationName"/>::lbPluginModule<xsl:value-of select="$ApplicationName"/>() called." LOG_
}

lbPluginModule<xsl:value-of select="$ApplicationName"/>::~lbPluginModule<xsl:value-of select="$ApplicationName"/>() {
	_CL_VERBOSE &lt;&lt; "lbPluginModule<xsl:value-of select="$ApplicationName"/>::~lbPluginModule<xsl:value-of select="$ApplicationName"/>() called." LOG_
}

void LB_STDCALL lbPluginModule<xsl:value-of select="$ApplicationName"/>::initialize() {
	lbErrCodes err = ERR_NONE;
	char ptr[20] = "";
	sprintf(ptr, "%p", this);

	enumPlugins();
	
	UAP_REQUEST(getModuleInstance(), lb_I_Database, database)
	
	database->init();
	if (database->connect("lbDMF", "lbDMF", "dba", "trainres") != ERR_NONE) {
		_LOG &lt;&lt; "Error: Could not connect to given database: '" &lt;&lt; "lbDMF" &lt;&lt; "'" LOG_

		return;
	}


<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
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
		
		*sql = "select id, handlerinterface, namespace, beschreibung from formulartypen where namespace = '";
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
				q->query("insert into formulartypen (namespace, beschreibung, handlerinterface) values ('FixedDBForm_<xsl:value-of select="$FormularName"/>', 'Fest verdrahtetes <xsl:value-of select="$FormularName"/> Formular', 'lb_I_FixedDatabaseForm')");
				
				q = database->getQuery("lbDMF", 0);
				q->skipFKCollecting();
				
				if (q->query(sql->charrep()) == ERR_NONE) {
					UAP(lb_I_String, ID)
					UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
					err = q->first();
					_LOG &lt;&lt; "Try to get new type ID for '<xsl:value-of select="$FormularName"/>'." LOG_
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						ID = q->getAsString(1);
						
						*SQL = "update formulare set typ = ";
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

	
}

lbErrCodes LB_STDCALL lbPluginModule<xsl:value-of select="$ApplicationName"/>::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE &lt;&lt; "lbPluginModule<xsl:value-of select="$ApplicationName"/>::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE &lt;&lt; "Cloning object with " &lt;&lt; uk->getRefCount() &lt;&lt; " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

</exsl:document>

</xsl:template>

</xsl:stylesheet>
