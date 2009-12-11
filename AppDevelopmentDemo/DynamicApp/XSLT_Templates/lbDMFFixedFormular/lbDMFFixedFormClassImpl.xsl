<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
-->
<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>
<xsl:import href="lbDMFFixedForm_InitHardcoded.xsl"/>


<xsl:template name="createCPPPreample">
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
</xsl:template>

<xsl:template name="createFormClassImpl">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>


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




BEGIN_IMPLEMENT_LB_UNKNOWN(<xsl:value-of select="$FormularName"/>)
        ADD_INTERFACE(lb_I_FixedDatabaseForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOf<xsl:value-of select="$FormularName"/>, <xsl:value-of select="$FormularName"/>)


lbErrCodes LB_STDCALL <xsl:value-of select="$FormularName"/>::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		
        _CL_VERBOSE &lt;&lt; "<xsl:value-of select="$FormularName"/>::setData(...) not implemented yet" LOG_

		UAP(lb_I_DatabaseForm, dbForm)
		QI(uk, lb_I_DatabaseForm, dbForm)
		
        return ERR_NOT_IMPLEMENTED;
}

<xsl:value-of select="$FormularName"/>::<xsl:value-of select="$FormularName"/>() 
{
	_CL_LOG &lt;&lt; "<xsl:value-of select="$FormularName"/>::<xsl:value-of select="$FormularName"/>() called." LOG_
	formName = strdup("<xsl:value-of select="$tempFormularName"/>");
	ref = STARTREF;
}

<xsl:value-of select="$FormularName"/>::~<xsl:value-of select="$FormularName"/>() {
	_CL_LOG &lt;&lt; "<xsl:value-of select="$FormularName"/>::~<xsl:value-of select="$FormularName"/>() called." LOG_
}

lbErrCodes LB_STDCALL <xsl:value-of select="$FormularName"/>::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	char eventName[100] = "";
	
	sprintf(eventName, "%pDatabaseFirst", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::lbDBFirst, eventName);

	sprintf(eventName, "%pDatabaseNext", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::lbDBNext,  eventName);

	sprintf(eventName, "%pDatabasePrev", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::lbDBPrev,  eventName);

	sprintf(eventName, "%pDatabaseLast", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::lbDBLast,  eventName);
	
	sprintf(eventName, "%pDatabaseAdd", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::lbDBAdd,  eventName);
	
	sprintf(eventName, "%pDatabaseDelete", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::lbDBDelete,  eventName);
	
	return ERR_NONE;
}


<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID][@isfk='1']">
void LB_STDCALL <xsl:value-of select="$FormularName"/>::getForeignKeyMappingData_<xsl:value-of select="@name"/>(wxChoice* choice) {
	// The position in the combo box will be mapped to the key in the ukComboboxMapper_<xsl:value-of select="@name"/> mapping instance.
	int cbox_pos = 0;
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Container, ComboboxMapper_<xsl:value-of select="@name"/>)
	<xsl:variable name="pktable" select="@fktable"/>
	<xsl:variable name="pkey" select="//lbDMF/primarykeys/primarykey[@pktable=$pktable]/@pkcolumn"/>
	char* buffer = "select <xsl:value-of select="@fkname"/>, <xsl:value-of select="$pkey"/> from <xsl:value-of select="@fktable"/> order by <xsl:value-of select="$pkey"/>";

	if (database == NULL) {
		REQUEST(manager.getPtr(), lb_I_Database, database)

		database->init();
		if (database->connect("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
							  "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>") != ERR_NONE) {
			_LOG &lt;&lt; "Error: Could not connect to given database: '" &lt;&lt; DBName->charrep() &lt;&lt; "'" LOG_

			return;
		}
	}
	
	UAP(lb_I_Query, q)
	
	q = database-&gt;getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);

	if (q-&gt;query(buffer) == ERR_NONE) {
		int cb_pos = 0;
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, IKey)
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_String, data)
		UAP(lb_I_String, SKey)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Long, possibleKey)


		// key instance for the integer combobox position
		QI(IKey, lb_I_KeyBase, key)

		choice-&gt;Clear();
	
		err = q-&gt;first();
	
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			data = q-&gt;getAsString(1);

			if (data->charrep() == NULL) *data = "&lt;empty&gt;";
			if (*data == "") *data = "&lt;empty&gt;";

			possibleKey = q-&gt;getAsLong(2);
			// uk instance for the foreign key value
			QI(possibleKey, lb_I_Unknown, uk)

			IKey-&gt;setData(cb_pos);
			ComboboxMapper_<xsl:value-of select="@name"/>-&gt;insert(&amp;uk, &amp;key);
			cb_pos++;
			
			choice-&gt;Append(wxString(data->charrep()));

			err = q-&gt;next();

			while (err == ERR_NONE) {
				data = q-&gt;getAsString(1);

				if (data->charrep() == NULL) *data = "&lt;empty&gt;";
				if (*data == "") *data = "&lt;empty&gt;";

				possibleKey = q-&gt;getAsLong(2);
				// uk instance for the foreign key value
				QI(possibleKey, lb_I_Unknown, uk)
				
				IKey->setData(cb_pos);
				ComboboxMapper_<xsl:value-of select="@name"/>-&gt;insert(&amp;uk, &amp;key);
				cb_pos++;
				
				choice-&gt;Append(wxString(data->charrep()));
				err = q-&gt;next();
			}

			if (err == WARN_DB_NODATA) {
				data = q-&gt;getAsString(1);

				if (data->charrep() == NULL) *data = "&lt;empty&gt;";
				if (*data == "") *data = "&lt;empty&gt;";

				possibleKey = q-&gt;getAsLong(2);
				// uk instance for the foreign key value
				QI(possibleKey, lb_I_Unknown, uk)
				
				IKey->setData(cb_pos);
				ComboboxMapper_<xsl:value-of select="@name"/>-&gt;insert(&amp;uk, &amp;key);
				cb_pos++;
				
				choice-&gt;Append(wxString(data->charrep()));
			}
		} 
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, mapperName)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	QI(mapperName, lb_I_KeyBase, key)
	QI(ComboboxMapper_<xsl:value-of select="@name"/>, lb_I_Unknown, uk)
	
	*mapperName = "<xsl:value-of select="@name"/>";
	
	if (ComboboxMapperList->exists(&amp;key) == 1) {
		ComboboxMapperList->remove(&amp;key);
	}
	
	ComboboxMapperList->insert(&amp;uk, &amp;key);
}
</xsl:for-each>



<xsl:for-each select="//lbDMF/formularactions/action[@formularid=$FormularID]">

<xsl:variable name="EventIdentifer">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="@event"/>
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

lbErrCodes LB_STDCALL <xsl:value-of select="$FormularName"/>::OnActionButton_<xsl:value-of select="$EventIdentifer"/>(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	<xsl:variable name="actionid" select="@actionid"/>
	<xsl:variable name="event" select="@event"/>
	wxWindow* w = FindWindowByName(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), this);
		
	wxString uniqueingvalue;
	wxString value;
	wxString errmsg;

	<xsl:variable name="fieldname" select="//lbDMF/actions/action[@ID=$actionid]/@source"/>
	<xsl:variable name="isFK" select="//lbDMF/formularfields/formular[@formularid=$FormularID][@name=$fieldname]/@isfk"/>
	<xsl:variable name="fieldtype" select="//lbDMF/formularfields/formular[@formularid=$FormularID][@name=$fieldname]/@dbtype"/>

	<xsl:choose>
		<xsl:when test="$isFK='1'">
	wxChoice* cbox = (wxChoice*) w;		
			
	int pos = cbox->GetSelection();
				
	if (pos != -1) {
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
		cbName->setData("<xsl:value-of select="$fieldname"/>");
				
		UAP(lb_I_KeyBase, key_cbName)
		UAP(lb_I_Unknown, uk_cbMapper)
		UAP(lb_I_Container, cbMapper)
		UAP(lb_I_KeyBase, key_pos)
		UAP(lb_I_Unknown, uk_mapping)
					
		QI(cbName, lb_I_KeyBase, key_cbName)
		uk_cbMapper = ComboboxMapperList->getElement(&amp;key_cbName);
		QI(uk_cbMapper, lb_I_Container, cbMapper)
		key->setData(pos);
		QI(key, lb_I_KeyBase, key_pos)
		uk_mapping = cbMapper->getElement(&amp;key_pos);
		if (uk_mapping == NULL)  { 
			printf("ERROR: cbMapper didn't found an entry for above search argument\n");
		} else {
			UAP(lb_I_Long, FK_id)
			QI(uk_mapping, lb_I_Long, FK_id)
			int p = FK_id->getData();
			char pp[20] = "";
			sprintf(pp, "%d", p);
			value = pp;
		}
	}
		</xsl:when>
		<xsl:otherwise>
			<!-- Choose code snipped upon database type -->
			<xsl:choose>
				<xsl:when test="$fieldtype='Bit'">
	wxCheckBox *check = (wxCheckBox*) w;
	if (check->GetValue() == TRUE) {
		value = "true";
	} else {
		value = "false";
	}
				</xsl:when>
				<xsl:when test="$fieldtype='Float'">
	wxTextCtrl* tx = (wxTextCtrl*) w;
	value = tx->GetValue();
				</xsl:when>
				<xsl:when test="$fieldtype='String'">
	wxTextCtrl* tx = (wxTextCtrl*) w;
	value = wxString("'") + tx->GetValue() + wxString("'");
				</xsl:when>
				<xsl:when test="$fieldtype='Integer'">
	wxTextCtrl* tx = (wxTextCtrl*) w;
	value = tx->GetValue();
				</xsl:when>
			</xsl:choose>
		</xsl:otherwise>
	</xsl:choose>

	<xsl:for-each select="//lbDMF/actionsteps/action[@actionid=$actionid]">

<xsl:variable name="tempDetailFormularName" select="@what"/>
<xsl:variable name="DetailFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempDetailFormularName"/>
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
	
	<xsl:choose>
		<xsl:when test="@steptyp='4'">
	// Open detailform <xsl:value-of select="@what"/>
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	UAP(lb_I_GUI, gui)

	meta-&gt;getGUI(&amp;gui);
	
	<xsl:value-of select="$DetailFormularName"/>*  fdf = (<xsl:value-of select="$DetailFormularName"/>*) gui-&gt;findCustomDBForm("<xsl:value-of select="$DetailFormularName"/>");
	
	if (fdf != NULL) {
		// Set's the filter
		_LOG &lt;&lt; "Show previously opened detail form '<xsl:value-of select="$DetailFormularName"/>'" LOG_
		if (!fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), value)) {
			bool result = true;
			<xsl:choose>
				<xsl:when test="$fieldtype='Bit'">
			UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
			UAP_REQUEST(getModuleInstance(), lb_I_String, title)
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			*title = _trans("Fatal Error");
			*msg = _trans("Temporarly setting a Bit column to another value did't ensures uniqueness!");
			meta->msgBox(title->charrep(), msg->charrep());
				</xsl:when>
				<xsl:when test="$fieldtype='Float'">
			wxTextCtrl* tx = (wxTextCtrl*) w;
			uniqueingvalue = tx->GetValue();
			tx->SetValue(wxString("1") + uniqueingvalue);
			lbDBUpdate();
			wxString temp = wxString("1") + uniqueingvalue;
			result = fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), temp);
			tx->SetValue(uniqueingvalue);
			lbDBUpdate();
				</xsl:when>
				<xsl:when test="$fieldtype='String'">
			wxTextCtrl* tx = (wxTextCtrl*) w;
			uniqueingvalue = tx->GetValue();
			tx->SetValue(uniqueingvalue + wxString("0"));
			lbDBUpdate();
			wxString temp = wxString("'") + uniqueingvalue + wxString("0'");
			result = fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), temp);
			tx->SetValue(uniqueingvalue);
			lbDBUpdate();
				</xsl:when>
				<xsl:when test="$fieldtype='Integer'">
			wxTextCtrl* tx = (wxTextCtrl*) w;
			uniqueingvalue = tx->GetValue();
			tx->SetValue(uniqueingvalue + wxString("0"));
			lbDBUpdate();
			wxString temp = uniqueingvalue + wxString("0");
			result = fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), temp);
			tx->SetValue(uniqueingvalue);
			lbDBUpdate();
				</xsl:when>
			</xsl:choose>
				
			if (!result) {
				UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
				UAP_REQUEST(getModuleInstance(), lb_I_String, title)
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*title = _trans("Error");
				*msg = _trans("Failed to make a column temporarly unique!");
				meta->msgBox(title->charrep(), msg->charrep());
			}
		}

		// Finally show up the window
		gui->showForm("<xsl:value-of select="@what"/>");
	} else {
		UAP(lb_I_FixedDatabaseForm, form)
		_LOG &lt;&lt; "Create new detail form '<xsl:value-of select="$DetailFormularName"/>'" LOG_

		fdf = new <xsl:value-of select="$DetailFormularName"/>();
		fdf-&gt;setModuleManager(getModuleInstance(), __FILE__, __LINE__);

		QI(fdf, lb_I_FixedDatabaseForm, form)
		fdf = (<xsl:value-of select="$DetailFormularName"/>*) gui-&gt;addCustomDBForm(form.getPtr(), "<xsl:value-of select="@what"/>");

		if (!fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), value)) {
			bool result = true;
			<xsl:choose>
				<xsl:when test="$fieldtype='Bit'">
			UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
			UAP_REQUEST(getModuleInstance(), lb_I_String, title)
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			*title = _trans("Fatal Error");
			*msg = _trans("Temporarly setting a Bit column to another value did't ensures uniqueness!");
			meta->msgBox(title->charrep(), msg->charrep());
				</xsl:when>
				<xsl:when test="$fieldtype='Float'">
			wxTextCtrl* tx = (wxTextCtrl*) w;
			uniqueingvalue = tx->GetValue();
			tx->SetValue(wxString("1") + uniqueingvalue);
			lbDBUpdate();
			wxString temp = wxString("1") + uniqueingvalue;
			result = fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), temp);
			tx->SetValue(uniqueingvalue);
			lbDBUpdate();
				</xsl:when>
				<xsl:when test="$fieldtype='String'">
			wxTextCtrl* tx = (wxTextCtrl*) w;
			uniqueingvalue = tx->GetValue();
			tx->SetValue(uniqueingvalue + wxString("0"));
			lbDBUpdate();
			wxString temp = wxString("'") + uniqueingvalue + wxString("0'");
			result = fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), temp);
			tx->SetValue(uniqueingvalue);
			lbDBUpdate();
				</xsl:when>
				<xsl:when test="$fieldtype='Integer'">
			wxTextCtrl* tx = (wxTextCtrl*) w;
			uniqueingvalue = tx->GetValue();
			tx->SetValue(uniqueingvalue + wxString("0"));
			lbDBUpdate();
			wxString temp = uniqueingvalue + wxString("0");
			result = fdf->updateFromMaster_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="//lbDMF/actions/action[@ID=$actionid]/@source"/>"), temp);
			tx->SetValue(uniqueingvalue);
			lbDBUpdate();
				</xsl:when>
			</xsl:choose>
				
			if (!result) {
				UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
				UAP_REQUEST(getModuleInstance(), lb_I_String, title)
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*title = _trans("Error");
				*msg = _trans("Failed to make a column temporarly unique!");
				meta->msgBox(title->charrep(), msg->charrep());
			}
		}

		gui-&gt;showForm("<xsl:value-of select="@what"/>");
		form++;

	}
		</xsl:when>
		<xsl:when test="@steptyp='5'">
	// Open masterform <xsl:value-of select="@what"/>
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	UAP(lb_I_GUI, gui)

	meta-&gt;getGUI(&amp;gui);
	
	<xsl:value-of select="$DetailFormularName"/>*  fdf = (<xsl:value-of select="$DetailFormularName"/>*) gui-&gt;findCustomDBForm("<xsl:value-of select="$DetailFormularName"/>");
	
	<xsl:variable name="DetailFormID" select="//lbDMF/formulare/formular[@name=$tempDetailFormularName][@applicationid=$ApplicationID]/@ID"/>
	<xsl:variable name="ptable" select="//lbDMF/formularfields/formular[@formularid=$DetailFormID]/@tablename"/>
	<xsl:variable name="pkey" select="//lbDMF/primarykeys/primarykey[@pktable=$ptable]/@pkcolumn"/>

	if (fdf != NULL) {
		// Set's the filter
		_LOG &lt;&lt; "Show previously opened detail form '<xsl:value-of select="$DetailFormularName"/>'" LOG_
		fdf->updateFromDetail_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="$pkey"/>"), value);

		// Finally show up the window
		gui->showForm("<xsl:value-of select="@what"/>");
	} else {
		UAP(lb_I_FixedDatabaseForm, form)
		_LOG &lt;&lt; "Create new detail form '<xsl:value-of select="$DetailFormularName"/>'" LOG_

		fdf = new <xsl:value-of select="$DetailFormularName"/>();
		fdf-&gt;setModuleManager(getModuleInstance(), __FILE__, __LINE__);

		QI(fdf, lb_I_FixedDatabaseForm, form)
		fdf = (<xsl:value-of select="$DetailFormularName"/>*) gui-&gt;addCustomDBForm(form.getPtr(), "<xsl:value-of select="@what"/>");
		fdf->updateFromDetail_<xsl:value-of select="$FormularName"/>(wxString("<xsl:value-of select="$pkey"/>"), value);
		gui-&gt;showForm("<xsl:value-of select="@what"/>");
		form++;

	}
		</xsl:when>
	</xsl:choose>
	
	</xsl:for-each>
	
	return err;
}
</xsl:for-each>

// ==============

	<xsl:for-each select="//lbDMF/formularactions/action">
		<xsl:variable name="Actionid" select="@actionid"/>
		<xsl:variable name="Formularid" select="@formularid"/>
		<xsl:variable name="Event" select="@event"/>
		<xsl:variable name="AID" select="//lbDMF/formulare/formular[@ID=$Formularid]/@applicationid"/>
		<xsl:if test="$ApplicationID=$AID">
		<xsl:for-each select="//lbDMF/actionsteps/action[@actionid=$Actionid]">
		<xsl:variable name="tempDetailFormularName" select="@what"/>
		<xsl:variable name="DetailFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempDetailFormularName"/>
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
	<xsl:if test="$FormularName=$DetailFormularName">
	<xsl:variable name="tempRealDetailFormularName" select="//lbDMF/formulare/formular[@ID=$Formularid]/@name"/>
	
<xsl:variable name="RealDetailFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempRealDetailFormularName"/>
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

	<xsl:if test="@steptyp='5'">
void LB_STDCALL <xsl:value-of select="$FormularName"/>::updateFromDetail_<xsl:value-of select="$RealDetailFormularName"/>(wxString column, wxString&amp; value) {
	lbErrCodes err = ERR_NONE;
	_LOG &lt;&lt; "<xsl:value-of select="$FormularName"/>::updateFromDetail_<xsl:value-of select="$RealDetailFormularName"/>('" &lt;&lt; column.c_str() &lt;&lt; "', '" &lt;&lt; value.c_str() &lt;&lt; "') called." LOG_

	if (MasterDetailRelationData == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, MasterDetailRelationData)
	} else {
		MasterDetailRelationData-&gt;deleteAll();
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, colName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, fkValue)
	UAP(lb_I_Unknown, uk_colValue)
	UAP(lb_I_KeyBase, key_fk)
	QI(fkValue, lb_I_Unknown, uk_colValue)
	QI(colName, lb_I_KeyBase, key_fk)
	
	wxWindow* w = FindWindowByName(column, this);
	if (w) w->Hide();
	w = FindWindowByName(column+wxString("_lbl"), this);
	if (w) w->Hide();

	Layout();		

	UAP_REQUEST(manager.getPtr(), lb_I_String, newWhereClause)
	UAP_REQUEST(manager.getPtr(), lb_I_String, newQuery)

	*newWhereClause += " where ";
	*newWhereClause += column.c_str();
	*newWhereClause += " = ";
	*newWhereClause += value.c_str();

	sampleQuery = database-&gt;getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);

<xsl:variable name="tempQuery" select="//lbDMF/formularparameter/parameter[@formularid=$FormularID][@name='query']/@value"/>
<xsl:variable name="Query">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempQuery"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'&quot;'"/>
		<xsl:with-param name="substringOut" select="'\&quot;'"/>
	</xsl:call-template>
</xsl:variable>

	*newQuery = sampleQuery-&gt;setWhereClause("<xsl:value-of select="$Query"/>", newWhereClause-&gt;charrep());

	_LOG &lt;&lt; "Have created new query: " &lt;&lt; newQuery-&gt;charrep() LOG_

	err = sampleQuery-&gt;query(newQuery-&gt;charrep());
	
	if (err != ERR_NONE) {
			_LOG &lt;&lt; "Error: Failed to get data for detail form." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton-&gt;Disable();
			prevButton-&gt;Disable();
			lastButton-&gt;Disable();
			nextButton-&gt;Disable();
			deleteButton-&gt;Disable();
			noDataAvailable = false;	
	} else {
		err = sampleQuery-&gt;first();

		if ((err != ERR_NONE) &amp;&amp; (err != WARN_DB_NODATA)) {
			_LOG &lt;&lt; "Error: Failed to get data for detail form (after moving to first)." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton-&gt;Disable();
			prevButton-&gt;Disable();
			lastButton-&gt;Disable();
			nextButton-&gt;Disable();
			deleteButton-&gt;Disable();
			noDataAvailable = false;	
		} else {
			lbDBRead();
			lastButton-&gt;Enable();
			nextButton-&gt;Enable();
			deleteButton-&gt;Enable();
		}
	}
}
	</xsl:if>
	</xsl:if>
	</xsl:for-each>
	</xsl:if>
	</xsl:for-each>


// ==============

<xsl:for-each select="//lbDMF/actionsteps/action[@what=$tempFormularName]">

<xsl:variable name="actionid" select="@actionid"/>
<xsl:variable name="formularid" select="//lbDMF/formularactions/action[@actionid=$actionid]/@formularid"/>

<xsl:variable name="tempForeignFormularName" select="//lbDMF/formulare/formular[@ID=$formularid]/@name"/>

// Action ID = <xsl:value-of select="$actionid"/>
// Master Formular ID = <xsl:value-of select="$formularid"/>
// Master Formular Name = <xsl:value-of select="$tempForeignFormularName"/>

<xsl:variable name="ForeignFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempForeignFormularName"/>
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

	<xsl:if test="@steptyp='4'">
bool LB_STDCALL <xsl:value-of select="$FormularName"/>::updateFromMaster_<xsl:value-of select="$ForeignFormularName"/>(wxString column, wxString&amp; value) {
	lbErrCodes err = ERR_NONE;
	_LOG &lt;&lt; "<xsl:value-of select="$FormularName"/>::updateFromMaster_<xsl:value-of select="$ForeignFormularName"/>('" &lt;&lt; column.c_str() &lt;&lt; "', '" &lt;&lt; value.c_str() &lt;&lt; "') called." LOG_
	
	// Get the primary columns of the master form
	<xsl:variable name="primarytable">
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$formularid][@tablename[not(preceding::formular/@tablename = .)]]">
		<xsl:value-of select="@tablename"/><xsl:if test="position() != last()">,</xsl:if>
	</xsl:for-each>
	</xsl:variable>

	<xsl:variable name="thistable">
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID][@tablename[not(preceding::formular/@tablename = .)]]">
		<xsl:value-of select="@tablename"/><xsl:if test="position() != last()">,</xsl:if>
	</xsl:for-each>
	</xsl:variable>

	<xsl:variable name="primarykeys">
	<xsl:for-each select="//lbDMF/primarykeys/primarykey[@pktable=$primarytable]">
		<xsl:value-of select="@pkcolumn"/><xsl:if test="position() != last()">,</xsl:if>
	</xsl:for-each>
	</xsl:variable>
	
	<xsl:variable name="relatedforeignkey" select="//lbDMF/foreignkeys/foreignkey[@pktable=$primarytable][@fktable=$thistable]/@fkcolumn"/>

	// Thistable is <xsl:value-of select="$thistable"/>

	if (MasterDetailRelationData == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, MasterDetailRelationData)
	} else {
		MasterDetailRelationData-&gt;deleteAll();
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, colName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, fkValue)
	UAP(lb_I_Unknown, uk_colValue)
	UAP(lb_I_KeyBase, key_fk)
	QI(fkValue, lb_I_Unknown, uk_colValue)
	QI(colName, lb_I_KeyBase, key_fk)
	
	wxWindow* w = FindWindowByName(wxString("<xsl:value-of select="$relatedforeignkey"/>"), this);
	if (w) w->Hide();
	w = FindWindowByName(wxString("<xsl:value-of select="$relatedforeignkey"/>")+wxString("_lbl"), this);
	if (w) w->Hide();

	Layout();		
	
<!--
	<xsl:variable name="primarykeys">
	<xsl:for-each select="//lbDMF/primarykeys/primarykey[@pktable=$primarytable][@pkcolumn[not(preceding::primarykey/@pkcolumn = .)]]">
		<xsl:value-of select="@pkcolumn"/><xsl:if test="position() != last()">,</xsl:if>
	</xsl:for-each>
	</xsl:variable>
-->
	wxString primaryQuery = wxString("SELECT <xsl:value-of select="$primarykeys"/> FROM <xsl:value-of select="$primarytable"/>") + wxString(" where ") + column + " = " + value;
	
	REQUEST(getModuleInstance(), lb_I_Database, database)
	UAP(lb_I_Query, PKQuery)

	database->init();
	database->connect("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
						"<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>");

	PKQuery = database->getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);

	UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)

	*SQL = primaryQuery.c_str();

	err = PKQuery->query(SQL->charrep());
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, newWhereClause)
	UAP_REQUEST(manager.getPtr(), lb_I_String, newQuery)

	if (err != ERR_NONE) {
		_LOG &lt;&lt; "Error: Failed to get primary key value over column '" &lt;&lt; column.c_str() &lt;&lt; "'. (" &lt;&lt; primaryQuery.c_str() &lt;&lt; ")" LOG_
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_String, title)
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		
		*msg = _trans("Failed to issue database query to find related detail data. Please have a look into the logfile.");
		*title = _trans("Warning");
		
		meta->msgBox(title->charrep(), msg->charrep());
		return true;
	}

	err = PKQuery->first();

	if ((err != ERR_NONE) &amp;&amp; (err != WARN_DB_NODATA)) {
		_LOG &lt;&lt; "Error: Failed to get primary key value over column '" &lt;&lt; column.c_str() &lt;&lt; "'. No data available. (" &lt;&lt; primaryQuery.c_str() &lt;&lt; ")" LOG_
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_String, title)
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		
		*msg = _trans("Failed to issue database query to find related detail data. Please have a look into the logfile.");
		*title = _trans("Warning");
		
		meta->msgBox(title->charrep(), msg->charrep());
		return true;
	}
	
	if (err == ERR_NONE) {
		return false;
	}
	
	*newWhereClause += " where ";
	<xsl:for-each select="//lbDMF/primarykeys/primarykey[@pktable=$primarytable]">
	*newWhereClause += "<xsl:value-of select="$relatedforeignkey"/>";
	*newWhereClause += " = ";
	*newWhereClause += PKQuery-&gt;getAsString(<xsl:value-of select="position()"/>);
	
	*fkValue = PKQuery-&gt;getAsString(<xsl:value-of select="position()"/>);

		<xsl:if test="position() != last()">
	*newWhereClause += " AND ";
		</xsl:if>
	</xsl:for-each>

	*colName = "<xsl:value-of select="$relatedforeignkey"/>";
	
	MasterDetailRelationData-&gt;insert(&amp;uk_colValue, &amp;key_fk);
<xsl:variable name="tempQuery" select="//lbDMF/formularparameter/parameter[@formularid=$FormularID][@name='query']/@value"/>
<xsl:variable name="Query">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempQuery"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'&quot;'"/>
		<xsl:with-param name="substringOut" select="'\&quot;'"/>
	</xsl:call-template>
</xsl:variable>

	sampleQuery = database-&gt;getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);

	*newQuery = sampleQuery-&gt;setWhereClause("<xsl:value-of select="$Query"/>", newWhereClause-&gt;charrep());

	_LOG &lt;&lt; "Have created new query: " &lt;&lt; newQuery-&gt;charrep() LOG_

	err = sampleQuery-&gt;query(newQuery-&gt;charrep());
	
	if (err != ERR_NONE) {
			_LOG &lt;&lt; "Error: Failed to get data for detail form." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton-&gt;Disable();
			prevButton-&gt;Disable();
			lastButton-&gt;Disable();
			nextButton-&gt;Disable();
			deleteButton-&gt;Disable();
			noDataAvailable = false;	
	} else {
		err = sampleQuery-&gt;first();

		if ((err != ERR_NONE) &amp;&amp; (err != WARN_DB_NODATA)) {
			_LOG &lt;&lt; "Error: Failed to get data for detail form (after moving to first)." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton-&gt;Disable();
			prevButton-&gt;Disable();
			lastButton-&gt;Disable();
			nextButton-&gt;Disable();
			deleteButton-&gt;Disable();
			noDataAvailable = false;	
		} else {
			lbDBRead();
			lastButton-&gt;Enable();
			nextButton-&gt;Enable();
			deleteButton-&gt;Enable();
		}
	}
	return true;
}
</xsl:if>
</xsl:for-each>


// Formular init routine

<xsl:call-template name="createFormClassImplHardcodedLayout">
	<xsl:with-param name="ApplicationID">
		<xsl:value-of select="$ApplicationID"/>
	</xsl:with-param>
	<xsl:with-param name="FormularID">
		<xsl:value-of select="$FormularID"/>
	</xsl:with-param>
</xsl:call-template>



lbErrCodes LB_STDCALL <xsl:value-of select="$FormularName"/>::lbDBClear() {
	wxWindow* w;
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	w = FindWindowByName(wxString("<xsl:value-of select="@name"/>"), this);
	if (w != NULL) {
<xsl:choose>
	<xsl:when test="@isfk='1'">
		wxChoice* cbox_<xsl:value-of select="@name"/> = (wxChoice*) w;
		if (sampleQuery->isAdding() == 1) {
			_LOG &lt;&lt; "Be in adding mode ('<xsl:value-of select="@name"/>') to NULL." LOG_
			if (cbox_<xsl:value-of select="@name"/>->IsEnabled()) {
				_LOG &lt;&lt; "Set a combobox column ('<xsl:value-of select="@name"/>') to NULL." LOG_
				sampleQuery->setNull("<xsl:value-of select="@name"/>");
			}
		}
		cbox_<xsl:value-of select="@name"/>->SetSelection(-1);
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
		wxCheckBox *check_<xsl:value-of select="@name"/> = (wxCheckBox*) w;
		check_<xsl:value-of select="@name"/>->SetValue(false);
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
		wxTextCtrl* tx_<xsl:value-of select="@name"/> = (wxTextCtrl*) w;
		tx_<xsl:value-of select="@name"/>->SetValue(wxString(""));
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
		wxTextCtrl* tx_<xsl:value-of select="@name"/> = (wxTextCtrl*) w;
		tx_<xsl:value-of select="@name"/>->SetValue(wxString(""));
			</xsl:when>
			<xsl:when test="@dbtype='String'">
		wxTextCtrl* tx_<xsl:value-of select="@name"/> = (wxTextCtrl*) w;
		tx_<xsl:value-of select="@name"/>->SetValue(wxString(""));
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
	}
</xsl:for-each>
	return ERR_NONE;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$FormularName"/>::lbDBUpdate() {
	wxWindow* w;
	UAP_REQUEST(getModuleInstance(), lb_I_String, col)
	UAP_REQUEST(getModuleInstance(), lb_I_String, val)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	w = FindWindowByName(wxString("<xsl:value-of select="@name"/>"), this);
<xsl:choose>
	<xsl:when test="@isfk='1'">
	wxChoice* cbox_<xsl:value-of select="@name"/> = (wxChoice*) w;
				
	int pos_<xsl:value-of select="@name"/> = cbox_<xsl:value-of select="@name"/>->GetSelection();
				
	if (pos_<xsl:value-of select="@name"/> != -1) {
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
		cbName-&gt;setData("<xsl:value-of select="@name"/>");
					
		UAP(lb_I_KeyBase, key_cbName)
		UAP(lb_I_Unknown, uk_cbMapper)
		UAP(lb_I_Container, cbMapper)
					
		QI(cbName, lb_I_KeyBase, key_cbName)
			
		uk_cbMapper = ComboboxMapperList-&gt;getElement(&amp;key_cbName);
					
		QI(uk_cbMapper, lb_I_Container, cbMapper)
					
		key-&gt;setData(pos_<xsl:value-of select="@name"/>);

		UAP(lb_I_KeyBase, key_pos)
		QI(key, lb_I_KeyBase, key_pos)
		UAP(lb_I_Unknown, uk_mapping)
		uk_mapping = cbMapper-&gt;getElement(&amp;key_pos);

		if (uk_mapping == NULL)  { 
			if (!sampleQuery-&gt;isNullable("<xsl:value-of select="@name"/>")) {
				if (!meta-&gt;askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
			}
		} else {
			UAP(lb_I_Long, FK_id)
					
			QI(uk_mapping, lb_I_Long, FK_id)
			
			long p = FK_id-&gt;getData();
					
			char pp[20] = "";
						
			sprintf(pp, "%dl", p);
					
			col-&gt;setData("<xsl:value-of select="@name"/>");
			val-&gt;setData(pp);
				
			sampleQuery-&gt;setNull("<xsl:value-of select="@name"/>", false);
			sampleQuery-&gt;setString(*&amp;col, *&amp;val);
		}
	} else {
		if (!sampleQuery-&gt;isNullable("<xsl:value-of select="@name"/>")) {
			if (!meta-&gt;askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
		}
	}
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		wxCheckBox *check = (wxCheckBox*) w;
		if (check->GetValue() == TRUE) {
			wxString v = "true";
			col->setData("<xsl:value-of select="@name"/>");
			val->setData(v.c_str());
	
			sampleQuery->setString(*&amp;col, *&amp;val);
		} else {
			wxString v = "false";
			col->setData("<xsl:value-of select="@name"/>");
			val->setData(v.c_str());
		
			sampleQuery->setString(*&amp;col, *&amp;val);
		}
	}
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		wxTextCtrl* tx = (wxTextCtrl*) w;

		wxString v = tx->GetValue();

		col->setData("<xsl:value-of select="@name"/>");
		val->setData(v.c_str());

		sampleQuery->setString(*&amp;col, *&amp;val);
	}
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		wxTextCtrl* tx = (wxTextCtrl*) w;

		wxString v = tx->GetValue();

		col->setData("<xsl:value-of select="@name"/>");
		val->setData(v.c_str());

		sampleQuery->setString(*&amp;col, *&amp;val);
	}
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	if (!sampleQuery->getReadonly("<xsl:value-of select="@name"/>")) {
		wxTextCtrl* tx = (wxTextCtrl*) w;

		wxString v = tx->GetValue();

		col->setData("<xsl:value-of select="@name"/>");
		val->setData(v.c_str());

		sampleQuery->setString(*&amp;col, *&amp;val);
	}
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

	if (sampleQuery->update() != ERR_NONE) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)

		newTitle->setData(formName);
		
		*newTitle += ": Update failed !";

		SetName(newTitle->charrep());

		if (meta->askYesNo("Error while updating data. Would you re - read the current data and retry ?")) {
			lbDBRead();
		}
		
		_LOG &lt;&lt; "Update a database record in form '<xsl:value-of select="$FormularName"/>' failed." LOG_

		return ERR_UPDATE_FAILED;
	}


	return ERR_NONE;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$FormularName"/>::lbDBRead() {
	lbErrCodes err = ERR_NONE;
	wxWindow* w;
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	w = FindWindowByName(wxString("<xsl:value-of select="@name"/>"), this);
<xsl:choose>
	<xsl:when test="@isfk='1'">
	wxChoice* cbox_<xsl:value-of select="@name"/> = (wxChoice*) w;

	UAP_REQUEST(manager.getPtr(), lb_I_Integer, key_<xsl:value-of select="@name"/>)
	UAP_REQUEST(manager.getPtr(), lb_I_String, cbName_<xsl:value-of select="@name"/>)

	cbName_<xsl:value-of select="@name"/>->setData("<xsl:value-of select="@name"/>");

	UAP(lb_I_KeyBase, key_cbName_<xsl:value-of select="@name"/>)
	UAP(lb_I_Unknown, uk_cbMapper_<xsl:value-of select="@name"/>)
	UAP(lb_I_Container, cbMapper_<xsl:value-of select="@name"/>)
	QI(cbName_<xsl:value-of select="@name"/>, lb_I_KeyBase, key_cbName_<xsl:value-of select="@name"/>)

	uk_cbMapper_<xsl:value-of select="@name"/> = ComboboxMapperList->getElement(&amp;key_cbName_<xsl:value-of select="@name"/>);

	QI(uk_cbMapper_<xsl:value-of select="@name"/>, lb_I_Container, cbMapper_<xsl:value-of select="@name"/>)
				
	int count_<xsl:value-of select="@name"/> = cbMapper_<xsl:value-of select="@name"/>->Count();
				
	if (count_<xsl:value-of select="@name"/> != 0) {
		char *newFK = NULL;
		UAP(lb_I_String, s)

		s = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
		newFK = (char*) malloc(strlen(s->charrep()) + 1);
		newFK[0] = 0;
								
		strcpy(newFK, s->charrep());
		key_<xsl:value-of select="@name"/>->setData(atoi(newFK));
				
		UAP(lb_I_KeyBase, key_FK_id)
		QI(key_<xsl:value-of select="@name"/>, lb_I_KeyBase, key_FK_id)
				
		UAP(lb_I_Unknown, uk_cbBoxPosition)
		UAP(lb_I_Integer, cbBoxPosition)
				
		int cbPos = 0;
				
		while (cbMapper_<xsl:value-of select="@name"/>->hasMoreElements() == 1) {
			UAP(lb_I_Long, sel)
	        UAP(lb_I_Unknown, e)
			e = cbMapper_<xsl:value-of select="@name"/>->nextElement();
	        QI(e, lb_I_Long, sel)
				        
	        if (sel->getData() == atoi(newFK)) {
	        	cbox_<xsl:value-of select="@name"/>->SetSelection(cbPos);
	        }
	        cbPos++;
		}
				
		if (newFK) {
			free(newFK);
			newFK = NULL;
		}
	}
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	wxCheckBox *check_<xsl:value-of select="@name"/> = (wxCheckBox*) w;
#ifndef OSX	
	if (sampleQuery->isNull("<xsl:value-of select="@name"/>")) {
		check_<xsl:value-of select="@name"/>->SetValue(false);
	} else {
#endif
		UAP(lb_I_String, s)
		s = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
								
		if ((strcmp(s->charrep(), "true") == 0) || (strcmp(s->charrep(), "1") == 0)) {
			check_<xsl:value-of select="@name"/>->SetValue(true);
		} else {
			check_<xsl:value-of select="@name"/>->SetValue(false);
		}
#ifndef OSX
	}
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
	s_<xsl:value-of select="@name"/> = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
	wxTextCtrl* tx_<xsl:value-of select="@name"/> = (wxTextCtrl*) w;
	tx_<xsl:value-of select="@name"/>->SetValue(wxString(s_<xsl:value-of select="@name"/>->charrep()));
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
	s_<xsl:value-of select="@name"/> = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
	wxTextCtrl* tx_<xsl:value-of select="@name"/> = (wxTextCtrl*) w;
	tx_<xsl:value-of select="@name"/>->SetValue(wxString(s_<xsl:value-of select="@name"/>->charrep()));
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
	s_<xsl:value-of select="@name"/> = sampleQuery->getAsString("<xsl:value-of select="@name"/>");
	wxTextCtrl* tx_<xsl:value-of select="@name"/> = (wxTextCtrl*) w;
	tx_<xsl:value-of select="@name"/>->SetValue(wxString(s_<xsl:value-of select="@name"/>->charrep()));
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
	return ERR_NONE;
}

lbErrCodes LB_STDCALL <xsl:value-of select="$FormularName"/>::lbDBAdd(lb_I_Unknown* uk) {
	lbErrCodes errUpdate = ERR_NONE;
	_CL_LOG &lt;&lt; "lbDatabasePanel::lbDBAdd() called. Have query: " &lt;&lt; getQuery() LOG_
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	if (addingButton->GetLabel() == wxString(_trans("Save"))) {
		// Save mode for first data entry.
		lbDBUpdate();
		firstButton->Enable();
		prevButton->Enable();
		addingButton->SetLabel(_trans("Add"));
		return ERR_NONE;
	}

	if (sampleQuery-&gt;isAdding() == 0) {
		if (sampleQuery-&gt;dataFetched()) errUpdate = lbDBUpdate();

		if (sampleQuery-&gt;add() != ERR_NONE) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)

			newTitle-&gt;setData(formName);
		
			*newTitle += ": Add failed !";
			
			_LOG &lt;&lt; newTitle-&gt;charrep() LOG_

			SetName(_trans(newTitle-&gt;charrep()));
		} else {
			// Delete fields and set foreign key columns to NULL
			
			lbDBClear();
			
			errUpdate = ERR_NONE;
		}
	} else {
		_CL_LOG &lt;&lt; "Query is in add mode." LOG_
		return ERR_NONE;
	}
	
	char* foreignkey = NULL;
	char* foreignkey_value = NULL;
	
	if (MasterDetailRelationData != NULL) {
			for (int i = 1; i &lt;= MasterDetailRelationData-&gt;Count(); i++) {
				lbErrCodes err = ERR_NONE;
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_KeyBase, key)
				UAP(lb_I_String, value)
				
				key = MasterDetailRelationData-&gt;getKeyAt(i);
				uk = MasterDetailRelationData-&gt;getElementAt(i);
				QI(uk, lb_I_String, value)
				
				foreignkey = strdup(key-&gt;charrep());
				foreignkey_value = strdup(value-&gt;charrep());
			
				_LOG &lt;&lt; "Set a foreign key column '" &lt;&lt; foreignkey &lt;&lt; "' to a proper value." LOG_

				wxWindow* w = FindWindowByName(wxString(key-&gt;charrep()), this);
		
				if (w != NULL) {
					wxChoice* cbox = (wxChoice*) w;
					lbErrCodes err = ERR_NONE;

					_LOG &lt;&lt; "Found the required control." LOG_

					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key1)
					UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)

					cbName->setData(key->charrep());

					UAP(lb_I_KeyBase, key_cbName)
					UAP(lb_I_Unknown, uk_cbMapper)
					UAP(lb_I_Container, cbMapper)

					QI(cbName, lb_I_KeyBase, key_cbName)
					uk_cbMapper = ComboboxMapperList->getElement(&amp;key_cbName);

					QI(uk_cbMapper, lb_I_Container, cbMapper)
			
					int count = cbMapper->Count();
				
					if (count != 0) {
						char *newFK = NULL;

						_LOG &lt;&lt; "Have mapped key values." LOG_
	
						newFK = (char*) malloc(strlen(value->charrep()) + 1);
						newFK[0] = 0;
						strcpy(newFK, value->charrep());
						key1->setData(atoi(newFK));
						UAP(lb_I_KeyBase, key_FK_id)
						QI(key1, lb_I_KeyBase, key_FK_id)
						UAP(lb_I_Unknown, uk_cbBoxPosition)
						UAP(lb_I_Integer, cbBoxPosition)
						int cbPos = 0;
						bool selected = false;
				
						while (cbMapper->hasMoreElements() == 1) {
							UAP(lb_I_Long, sel)
					        UAP(lb_I_Unknown, e)
					        e = cbMapper->nextElement();
					        QI(e, lb_I_Long, sel)
				        
							_LOG &lt;&lt; "Compare given key (" &lt;&lt; sel->charrep() &lt;&lt; ") with required key (" &lt;&lt; newFK &lt;&lt; ")." LOG_
							
					        if (sel->getData() == (long) atoi(newFK)) {
					        	selected = true;
					        	cbox->SetSelection(cbPos);
								_LOG &lt;&lt; "Set combobox to " &lt;&lt; cbPos &lt;&lt; ". It has '" &lt;&lt; cbox->GetStringSelection().c_str() &lt;&lt; "'." LOG_
					        }
					        cbPos++;
						}
						
						if (newFK) {
							free(newFK);
							newFK = NULL;
						}
					}
				}
			}
	}
	
	_CL_LOG &lt;&lt; "Determine update failed..." LOG_
	
	if (errUpdate == ERR_UPDATE_FAILED) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)
		_CL_LOG &lt;&lt; "Updating after add failed." LOG_
		
		newTitle-&gt;setData(formName);
		
		*newTitle += ": Missing fields !";
		
		_LOG &lt;&lt; newTitle-&gt;charrep() LOG_
		
		SetName(_trans(newTitle-&gt;charrep()));
	} else {
		_CL_LOG &lt;&lt; "Updating after add succeeded. Move to last." LOG_
		
		if (allNaviDisabled == true) {
			lbDBFirst(NULL);
			lbDBClear();
		} else {
			if (sampleQuery-&gt;dataFetched()) {
				_LOG &lt;&lt; "Add on empty data result..." LOG_
				if (foreignkey != NULL) {
					if (sampleQuery-&gt;isNull(foreignkey)) {
						_LOG &lt;&lt; "Column for foreignkey binding is set to NULL. -- Wrong" LOG_
						UAP_REQUEST(manager.getPtr(), lb_I_String, col)
						UAP_REQUEST(manager.getPtr(), lb_I_String, val)
						
						*col = foreignkey;
						*val = foreignkey_value;
						
						sampleQuery-&gt;setString(*&amp;col, *&amp;val);
					} else {
						_LOG &lt;&lt; "Column for foreignkey binding is not set to NULL." LOG_				
					}
				}

				if (sampleQuery-&gt;update() == ERR_NONE) {
					if (sampleQuery-&gt;last() == ERR_NONE) {
						lbDBRead();
					} else {
						_LOG &lt;&lt; "Error: Moving to new record failed." LOG_
					}
				} else {
					if (meta-&gt;askYesNo("Error: Adding new record failed!\n\nDo you want to retry ?")) {
						lbDBClear();
						if (sampleQuery-&gt;update() != ERR_NONE) {
							UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)
							newTitle-&gt;setData(formName);
							*newTitle += ": Add failed !";
							_LOG &lt;&lt; newTitle-&gt;charrep() LOG_
							SetName(_trans(newTitle-&gt;charrep()));
							_LOG &lt;&lt; "Fatal: Adding a new record failed." LOG_
						}
					}
				}

				if (lbDBLast(NULL) != ERR_NONE) {
					_LOG &lt;&lt; "Move to last after updating failed." LOG_
					lbDBFirst(NULL);
				} else {
					lbDBClear();
				}
			} else {
				if (foreignkey != NULL) {
					if (sampleQuery-&gt;isNull(foreignkey)) {
						_LOG &lt;&lt; "Column for foreignkey binding is set to NULL. -- Wrong" LOG_
						UAP_REQUEST(manager.getPtr(), lb_I_String, col)
						UAP_REQUEST(manager.getPtr(), lb_I_String, val)
						
						*col = foreignkey;
						*val = foreignkey_value;
						
						sampleQuery-&gt;setString(*&amp;col, *&amp;val);
					} else {
						_LOG &lt;&lt; "Column for foreignkey binding is not set to NULL." LOG_				
					}
				} else {
					_LOG &lt;&lt; "Foreign key name is null. There may be no keys to be preset." LOG_
				}
				
				if (sampleQuery-&gt;update() == ERR_NONE) {
					if (sampleQuery-&gt;last() == ERR_NONE)
						lbDBRead();
					else
						_LOG &lt;&lt; "Error: Moving to new record failed." LOG_
				} else {
					if (meta-&gt;askYesNo("Error: Adding new record failed!\n\nDo you want to retry ?")) {
						lbDBClear();
						if (sampleQuery-&gt;update() != ERR_NONE) {
							UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)
							newTitle-&gt;setData(formName);
							*newTitle += ": Add failed !";
							_LOG &lt;&lt; newTitle-&gt;charrep() LOG_
							SetName(_trans(newTitle-&gt;charrep()));
							_LOG &lt;&lt; "Fatal: Adding a new record failed." LOG_
						}
					}
				}
			}
		}
	}

	// Indicate save action
	addingButton->SetLabel(_trans("Save"));

	_CL_LOG &lt;&lt; "Return from lbDatabasePanel::lbDBAdd(lb_I_Unknown* uk)" LOG_

	return ERR_NONE;
}
</xsl:template>

</xsl:stylesheet>