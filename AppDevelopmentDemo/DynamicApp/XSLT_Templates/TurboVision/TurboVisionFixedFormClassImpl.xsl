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
<xsl:import href="TurboVisionFixedFormXRC.xsl"/>


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

/* Implementation of form <xsl:value-of select="$FormularName"/>
 * ID = <xsl:value-of select="$FormularID"/>
 */

// Foreign key mapping functions

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID][@isfk='1']">

</xsl:for-each>


// Code for formular actions follows here (OnActionButton_xxx)

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

</xsl:for-each>

// Code for updates from detail formular follows here (updateFromDetail_xxx)

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

	</xsl:if>
	</xsl:if>
	</xsl:for-each>
	</xsl:if>
	</xsl:for-each>


// Code for updates from master formular follows here (updateFromMaster_xxx)

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

</xsl:for-each>


// Formular init routine

<xsl:call-template name="createFormClassImplXRCLayout_InitRountine">
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