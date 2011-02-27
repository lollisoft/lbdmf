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
            Ginsterweg 4
            
            65760 Eschborn (germany)
-->
<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>


<xsl:template name="createFormClassImplHardcodedLayout">
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

// Initialization of the form via source code

void LB_STDCALL <xsl:value-of select="$FormularName"/>::init() {
	lbErrCodes err = ERR_NONE;
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	_LOG &lt;&lt; "<xsl:value-of select="$FormularName"/>::init() called." LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, params)
	
	if (ImageButtonMapperList == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ImageButtonMapperList)
	}
	
	SetName(formName);

	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* sizerHor   = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerNavi  = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerActions = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerLeft  = new wxBoxSizer(wxVERTICAL);	
	wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);

	if (database != NULL) {
		_CL_LOG &lt;&lt; "WARNING: Database instance available!" LOG_
	}
	
	REQUEST(manager.getPtr(), lb_I_Database, database)

	database->init();
	if (database->connect("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
						"<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 
	"<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>", "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>") != ERR_NONE) {
		_LOG &lt;&lt; "Error: Could not connect to given database: '" &lt;&lt; DBName->charrep() &lt;&lt; "'" LOG_

		return;
	}

	if (_DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBName)
		_DBName->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>");
	}
	if (_DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBUser)
		_DBUser->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>");
	}
	if (_DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBPass)
		_DBPass->setData("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>");
	}

	sampleQuery = database->getQuery("<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>", 0);

	int DatabaseFirst;
	int DatabaseNext;
	int DatabasePrev;
	int DatabaseLast;
	int DatabaseAdd;
	int DatabaseDelete;
	
	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
	UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, dispatcher)

	char eventName[100] = "";
		
	sprintf(eventName, "%pDatabaseFirst", this);
	eman->registerEvent(eventName, DatabaseFirst);

	sprintf(eventName, "%pDatabaseNext", this);
	eman->registerEvent(eventName,  DatabaseNext);

	sprintf(eventName, "%pDatabasePrev", this);
	eman->registerEvent(eventName,  DatabasePrev);

	sprintf(eventName, "%pDatabaseLast", this);
	eman->registerEvent(eventName,  DatabaseLast);

	sprintf(eventName, "%pDatabaseAdd", this);
	eman->registerEvent(eventName,  DatabaseAdd);

	sprintf(eventName, "%pDatabaseDelete", this);
	eman->registerEvent(eventName,  DatabaseDelete);

	sprintf(eventName, "%pImageButtonClick", this);
	eman->registerEvent(eventName,  DatabaseDelete);

	dispatcher-&gt;setEventManager(eman.getPtr());

	registerEventHandler(dispatcher.getPtr());

	/// Did I need that here ? 
	sampleQuery-&gt;enableFKCollecting();

	sampleQuery-&gt;setAutoRefresh(meta->getAutorefreshData());

	if (SQLString == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SQLString)
		
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

		
		SQLString->setData("<xsl:value-of select="$Query"/>");
	}

	sampleQuery->query(SQLString->charrep(), false);

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	sampleQuery->setReadonly("<xsl:value-of select="@name"/>"); // <xsl:value-of select="@tablename"/>
</xsl:for-each>
</xsl:for-each>

	sampleQuery-&gt;bind();

	sampleQuery-&gt;first();

	UAP(lb_I_String, s)
	int i = 0;
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
	// FK <xsl:value-of select="@name"/>
	// Create a mapping instance for this combo box
	UAP(lb_I_Unknown, ukComboboxMapper_<xsl:value-of select="@name"/>)
	UAP(lb_I_Container, ComboboxMapper_<xsl:value-of select="@name"/>)

	UAP_REQUEST(manager.getPtr(), lb_I_String, cbName_<xsl:value-of select="@name"/>)
	UAP(lb_I_KeyBase, key_cbName_<xsl:value-of select="@name"/>)
	QI(cbName_<xsl:value-of select="@name"/>, lb_I_KeyBase, key_cbName_<xsl:value-of select="@name"/>)

	// This is the input parameter

	cbName_<xsl:value-of select="@name"/>->setData("<xsl:value-of select="@name"/>");

	wxChoice *cbox_<xsl:value-of select="@name"/> = new wxChoice(this, -1);
	cbox_<xsl:value-of select="@name"/>->SetName("<xsl:value-of select="@name"/>");
	sizerRight->Add(cbox_<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);

	getForeignKeyMappingData_<xsl:value-of select="@name"/>(cbox_<xsl:value-of select="@name"/>);

	char* tLabel<xsl:value-of select="@name"/> = (char*) malloc(strlen("<xsl:value-of select="@name"/>") + 6);
	tLabel<xsl:value-of select="@name"/>[0] = 0;
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "<xsl:value-of select="@name"/>"); 
	wxStaticText *label<xsl:value-of select="@name"/> = new wxStaticText(this, -1, _trans(tLabel<xsl:value-of select="@name"/>), wxPoint());
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "_lbl");
	label<xsl:value-of select="@name"/>-&gt;SetName(_trans(tLabel<xsl:value-of select="@name"/>));
	sizerLeft-&gt;Add(label<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
	free(tLabel<xsl:value-of select="@name"/>);

	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	// Normal Bit column <xsl:value-of select="@name"/>
	wxCheckBox *check<xsl:value-of select="@name"/> = new wxCheckBox(this, -1, "", wxPoint());
	check<xsl:value-of select="@name"/>-&gt;SetName("<xsl:value-of select="@name"/>");
	sizerRight-&gt;Add(check<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
				<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	check<xsl:value-of select="@name"/>-&gt;Disable();
				</xsl:for-each>
	char* tLabel<xsl:value-of select="@name"/> = (char*) malloc(strlen("<xsl:value-of select="@name"/>") + 6);
	tLabel<xsl:value-of select="@name"/>[0] = 0;
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "<xsl:value-of select="@name"/>"); 
	wxStaticText *label<xsl:value-of select="@name"/> = new wxStaticText(this, -1, _trans(tLabel<xsl:value-of select="@name"/>), wxPoint());
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "_lbl");
	label<xsl:value-of select="@name"/>-&gt;SetName(_trans(tLabel<xsl:value-of select="@name"/>));
	sizerLeft-&gt;Add(label<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
	free(tLabel<xsl:value-of select="@name"/>);
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	// Normal Float column <xsl:value-of select="@name"/>
	wxTextValidator val<xsl:value-of select="@name"/> = wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, new wxString(""));
						
	wxArrayString ValArray<xsl:value-of select="@name"/>;
	ValArray<xsl:value-of select="@name"/>.Add(".");
	ValArray<xsl:value-of select="@name"/>.Add("-");
	ValArray<xsl:value-of select="@name"/>.Add("0");
	ValArray<xsl:value-of select="@name"/>.Add("1");
	ValArray<xsl:value-of select="@name"/>.Add("2");
	ValArray<xsl:value-of select="@name"/>.Add("3");
	ValArray<xsl:value-of select="@name"/>.Add("4");
	ValArray<xsl:value-of select="@name"/>.Add("5");
	ValArray<xsl:value-of select="@name"/>.Add("6");
	ValArray<xsl:value-of select="@name"/>.Add("7");
	ValArray<xsl:value-of select="@name"/>.Add("8");
	ValArray<xsl:value-of select="@name"/>.Add("9");
						
	val<xsl:value-of select="@name"/>.SetIncludes(ValArray<xsl:value-of select="@name"/>);
				
						
	s = sampleQuery-&gt;getAsString(++i);
						
	wxTextCtrl *text<xsl:value-of select="@name"/> = new wxTextCtrl(this, -1, s->charrep(), wxPoint(), wxDefaultSize, 0, val<xsl:value-of select="@name"/>);
	text<xsl:value-of select="@name"/>-&gt;SetName("<xsl:value-of select="@name"/>");
	sizerRight-&gt;Add(text<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
				<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	text<xsl:value-of select="@name"/>-&gt;Disable();
				</xsl:for-each>
	char* tLabel<xsl:value-of select="@name"/> = (char*) malloc(strlen("<xsl:value-of select="@name"/>") + 6);
	tLabel<xsl:value-of select="@name"/>[0] = 0;
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "<xsl:value-of select="@name"/>"); 
	wxStaticText *label<xsl:value-of select="@name"/> = new wxStaticText(this, -1, _trans(tLabel<xsl:value-of select="@name"/>), wxPoint());
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "_lbl");
	label<xsl:value-of select="@name"/>-&gt;SetName(_trans(tLabel<xsl:value-of select="@name"/>));
	sizerLeft-&gt;Add(label<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
	free(tLabel<xsl:value-of select="@name"/>);

			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	// Normal Integer column <xsl:value-of select="@name"/>
	wxTextValidator val<xsl:value-of select="@name"/> = wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, new wxString(""));
						
	wxArrayString ValArray<xsl:value-of select="@name"/>;
	ValArray<xsl:value-of select="@name"/>.Add("0");
	ValArray<xsl:value-of select="@name"/>.Add("1");
	ValArray<xsl:value-of select="@name"/>.Add("2");
	ValArray<xsl:value-of select="@name"/>.Add("3");
	ValArray<xsl:value-of select="@name"/>.Add("4");
	ValArray<xsl:value-of select="@name"/>.Add("5");
	ValArray<xsl:value-of select="@name"/>.Add("6");
	ValArray<xsl:value-of select="@name"/>.Add("7");
	ValArray<xsl:value-of select="@name"/>.Add("8");
	ValArray<xsl:value-of select="@name"/>.Add("9");
	ValArray<xsl:value-of select="@name"/>.Add("-");
						
	val<xsl:value-of select="@name"/>.SetIncludes(ValArray<xsl:value-of select="@name"/>);

	s = sampleQuery-&gt;getAsString(++i);
					
	wxTextCtrl *text<xsl:value-of select="@name"/> = new wxTextCtrl(this, -1, s->charrep(), wxPoint(), wxDefaultSize, 0, val<xsl:value-of select="@name"/>);
	text<xsl:value-of select="@name"/>-&gt;SetName("<xsl:value-of select="@name"/>");
    sizerRight-&gt;Add(text<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
	<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	text<xsl:value-of select="@name"/>-&gt;Disable();
	</xsl:for-each>

	char* tLabel<xsl:value-of select="@name"/> = (char*) malloc(strlen("<xsl:value-of select="@name"/>") + 6);
	tLabel<xsl:value-of select="@name"/>[0] = 0;
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "<xsl:value-of select="@name"/>"); 
	wxStaticText *label<xsl:value-of select="@name"/> = new wxStaticText(this, -1, _trans(tLabel<xsl:value-of select="@name"/>), wxPoint());
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "_lbl");
	label<xsl:value-of select="@name"/>-&gt;SetName(_trans(tLabel<xsl:value-of select="@name"/>));
	sizerLeft-&gt;Add(label<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
	free(tLabel<xsl:value-of select="@name"/>);
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	// Normal String column <xsl:value-of select="@name"/>
						
	s = sampleQuery->getAsString(++i);
						
	wxTextCtrl *text<xsl:value-of select="@name"/> = new wxTextCtrl(this, -1, s->charrep(), wxPoint(), wxDefaultSize);
	text<xsl:value-of select="@name"/>->SetName("<xsl:value-of select="@name"/>");
	sizerRight->Add(text<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
	<xsl:for-each select="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@readonly='1']">
	text<xsl:value-of select="@name"/>-&gt;Disable();
	</xsl:for-each>
	char* tLabel<xsl:value-of select="@name"/> = (char*) malloc(strlen("<xsl:value-of select="@name"/>") + 6);
	tLabel<xsl:value-of select="@name"/>[0] = 0;
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "<xsl:value-of select="@name"/>"); 
	wxStaticText *label<xsl:value-of select="@name"/> = new wxStaticText(this, -1, _trans(tLabel<xsl:value-of select="@name"/>), wxPoint());
	tLabel<xsl:value-of select="@name"/> = strcat(tLabel<xsl:value-of select="@name"/>, "_lbl");
	label<xsl:value-of select="@name"/>-&gt;SetName(_trans(tLabel<xsl:value-of select="@name"/>));
	sizerLeft-&gt;Add(label<xsl:value-of select="@name"/>, 1, wxEXPAND | wxALL, 5);
	free(tLabel<xsl:value-of select="@name"/>);
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

	sizerHor-&gt;Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
	sizerHor-&gt;Add(sizerRight, 1, wxEXPAND | wxALL, 5);

	wxButton *button1 = new wxButton(this, DatabaseFirst, _trans("First"));
	wxButton *button2 = new wxButton(this, DatabasePrev, _trans("Prev"));
	wxButton *button3 = new wxButton(this, DatabaseNext, _trans("Next"));
	wxButton *button4 = new wxButton(this, DatabaseLast, _trans("Last"));
	
	firstButton = button1;
	prevButton = button2;
	nextButton = button3;
	lastButton = button4;

	button1-&gt;Disable();
	button2-&gt;Disable();

	sizerNavi-&gt;Add(button1, 1, wxEXPAND | wxALL, 5);
	sizerNavi-&gt;Add(button2, 1, wxEXPAND | wxALL, 5);
	sizerNavi-&gt;Add(button3, 1, wxEXPAND | wxALL, 5);
	sizerNavi-&gt;Add(button4, 1, wxEXPAND | wxALL, 5);

	wxButton *buttonAdd = new wxButton(this, DatabaseAdd, _trans("Add"));
	wxButton *buttonDelete = new wxButton(this, DatabaseDelete, _trans("Delete"));

	deleteButton = buttonDelete;
	addingButton = buttonAdd;


	sizerAddRem-&gt;Add(buttonAdd, 1, wxEXPAND | wxALL, 5);
	sizerAddRem-&gt;Add(buttonDelete, 1, wxEXPAND | wxALL, 5);

	int actionID = 0;

// Don't distinguish between action types
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

	UAP_REQUEST(getModuleInstance(), lb_I_String, actionWhat<xsl:value-of select="$EventIdentifer"/>)
	*actionWhat<xsl:value-of select="$EventIdentifer"/> = "<xsl:value-of select="@event"/>";
	char *eventName<xsl:value-of select="$EventIdentifer"/> = (char*) malloc(strlen(actionWhat<xsl:value-of select="$EventIdentifer"/>-&gt;charrep()) + 20);
	sprintf(eventName<xsl:value-of select="$EventIdentifer"/>, "%p(%s)", this, actionWhat<xsl:value-of select="$EventIdentifer"/>->charrep());
	eman->registerEvent(eventName<xsl:value-of select="$EventIdentifer"/>, actionID);
	
	_LOG &lt;&lt; "Registered action '<xsl:value-of select="@event"/>' to '" &lt;&lt; eventName<xsl:value-of select="$EventIdentifer"/> &lt;&lt; "' actionID " &lt;&lt; actionID LOG_
	
	<xsl:variable name="ActionID" select="@actionid"/>
	wxButton *actionButton<xsl:value-of select="$EventIdentifer"/> = new wxButton(this, actionID, _trans("<xsl:value-of select="//lbDMF/actions/action[@ID=$ActionID]/@name"/>")); //, wxPoint(), wxSize(100,20));
	dispatcher-&gt;addEventHandlerFn(this, (lbEvHandler) &amp;<xsl:value-of select="$FormularName"/>::OnActionButton_<xsl:value-of select="$EventIdentifer"/>, eventName<xsl:value-of select="$EventIdentifer"/>);
	this-&gt;Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	sizerActions-&gt;Add(actionButton<xsl:value-of select="$EventIdentifer"/>, 1, wxEXPAND | wxALL, 5);
	free(eventName<xsl:value-of select="$EventIdentifer"/>);
</xsl:for-each>

	this->Connect( DatabaseFirst,  -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabaseNext,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabasePrev,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabaseLast,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);

	this-&gt;Connect( DatabaseAdd,  -1, wxEVT_COMMAND_BUTTON_CLICKED,   
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);
	this-&gt;Connect( DatabaseDelete, -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &amp;<xsl:value-of select="$FormularName"/>::OnDispatch);

	SetAutoLayout(TRUE);
	
	sizerMain-&gt;Add(sizerHor, 0, wxEXPAND | wxALL, 5);
	sizerMain-&gt;Add(sizerActions, 0, wxEXPAND | wxALL, 5);
	sizerMain-&gt;Add(sizerAddRem, 0, wxEXPAND | wxALL, 5);
	sizerMain-&gt;Add(sizerNavi, 0, wxEXPAND | wxALL, 5);
	
	SetSizer(sizerMain);

	sizerMain-&gt;SetSizeHints(this);
	sizerMain-&gt;Fit(this);

	if (sampleQuery-&gt;dataFetched()) {
		sampleQuery-&gt;first();
		lbDBRead();
	} else {
		nextButton-&gt;Disable();
		lastButton-&gt;Disable();
		deleteButton-&gt;Disable();
	}
}


</xsl:template>

</xsl:stylesheet>
