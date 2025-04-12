<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Odenwaldstr. 14

            63150 Heusenstamm (germany)
-->
<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>


<xsl:template name="createFormClassDecl">
		<xsl:param name="ApplicationID"/>
		<xsl:param name="FormularID"/>
		<xsl:param name="ParamFormularName"/>
		

<xsl:variable name="tempFormularName" select="$ParamFormularName"/>
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

/////////////////////////////////////////////
// Generated By lbDMF codegenerator templates
/////////////////////////////////////////////

#ifndef __<xsl:value-of select="$FormularName"/>_
#define __<xsl:value-of select="$FormularName"/>_

////@@begin gen include
#include "wxActiveRecord.h"
#include &lt;wx/wx.h&gt;
#include &lt;wx/string.h&gt;
#include &lt;wx/datetime.h&gt;


////@@end gen include

////@@begin custom include
////@@end custom include

////@@begin gen forward
class <xsl:value-of select="$FormularName"/>;
class <xsl:value-of select="$FormularName"/>Row;
class <xsl:value-of select="$FormularName"/>RowSet;

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:variable name="PKFieldName" select="@fkname"/> 
<xsl:variable name="PKTableName" select="@fktable"/>
<xsl:variable name="FormID" select="@formularid"/>
<xsl:if test="@isfk='1'">
	<xsl:variable name="TargetFormID" select="//lbDMF/formularfields/formular[@tablename=$PKTableName][@name=$PKFieldName]/@formularid"/>
	<xsl:variable name="tempTargetForm" select="//lbDMF/formulare/formular[@ID=$TargetFormID]/@name"/>
	<xsl:variable name="TargetForm">
		<xsl:call-template name="SubstringReplace">
			<xsl:with-param name="stringIn">
		<xsl:call-template name="SubstringReplace">
			<xsl:with-param name="stringIn">
		<xsl:call-template name="SubstringReplace">
			<xsl:with-param name="stringIn">
				<xsl:value-of select="$tempTargetForm"/>
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
class <xsl:value-of select="$TargetForm"/>Row; // <xsl:value-of select="$FieldName"/>
</xsl:if>
</xsl:for-each>


////@@end gen forward

////@@begin custom forward
////@@end custom forward

<xsl:variable name="RealTableName"><xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
	<xsl:if test="position()=1"><xsl:value-of select="@tablename"/></xsl:if></xsl:for-each></xsl:variable>

////@@begin gen arClass
// Have Formular <xsl:value-of select="$FormularID"/>.
class <xsl:value-of select="$FormularName"/>: public wxSqliteActiveRecord {
protected:
	<xsl:value-of select="$FormularName"/>Row* RowFromResult(DatabaseResultSet* result);
public:


	<xsl:value-of select="$FormularName"/>();
	<xsl:value-of select="$FormularName"/>(const wxString&amp; name,const wxString&amp; server=wxEmptyString,const wxString&amp; user=wxEmptyString,const wxString&amp; password=wxEmptyString,const wxString&amp; table=wxT("<xsl:value-of select="$RealTableName"/>"));
	<xsl:value-of select="$FormularName"/>(DatabaseLayer* database,const wxString&amp; table=wxT("<xsl:value-of select="$RealTableName"/>"));
	bool Create(const wxString&amp; name,const wxString&amp; server=wxEmptyString,const wxString&amp; user=wxEmptyString,const wxString&amp; password=wxEmptyString,const wxString&amp; table=wxT("<xsl:value-of select="$RealTableName"/>"));
	
	<xsl:value-of select="$FormularName"/>Row* New();
	bool Delete(int key);

	
	<xsl:value-of select="$FormularName"/>Row* Id(int key);

	<xsl:value-of select="$FormularName"/>Row* Where(const wxString&amp; whereClause);
	<xsl:value-of select="$FormularName"/>RowSet* WhereSet(const wxString&amp; whereClause,const wxString&amp; orderBy=wxEmptyString);
	<xsl:value-of select="$FormularName"/>RowSet* All(const wxString&amp; orderBy=wxEmptyString); 

////@@begin custom arClass
public:
////@@end custom arClass
};
////@@end gen arClass

////@@begin gen arRow
class <xsl:value-of select="$FormularName"/>Row: public wxActiveRecordRow{
public:
	<xsl:value-of select="$FormularName"/>Row();
	<xsl:value-of select="$FormularName"/>Row(const <xsl:value-of select="$FormularName"/>Row&amp; src);
	<xsl:value-of select="$FormularName"/>Row(<xsl:value-of select="$FormularName"/>* activeRecord);
	<xsl:value-of select="$FormularName"/>Row(DatabaseLayer* database,const wxString&amp; table=wxT("<xsl:value-of select="$RealTableName"/>"));
	<xsl:value-of select="$FormularName"/>Row&amp; operator=(const <xsl:value-of select="$FormularName"/>Row&amp; src);
	bool GetFromResult(DatabaseResultSet* result);
public:

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@dbtype='String'">
	wxString <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:when>
	<xsl:when test="@dbtype='Integer'">
	int <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:when>
	<xsl:otherwise>
	//Unknown type <xsl:value-of select="@name"/>; // <xsl:value-of select="@tablename"/>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

public:
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:variable name="PKFieldName" select="@fkname"/> 
<xsl:variable name="PKTableName" select="@fktable"/>
<xsl:variable name="FormID" select="@formularid"/>
<xsl:if test="@isfk='1'">
	<xsl:variable name="TargetFormID" select="//lbDMF/formularfields/formular[@tablename=$PKTableName][@name=$PKFieldName]/@formularid"/>
	<xsl:variable name="tempTargetForm" select="//lbDMF/formulare/formular[@ID=$TargetFormID]/@name"/>
	<xsl:variable name="TargetForm">
		<xsl:call-template name="SubstringReplace">
			<xsl:with-param name="stringIn">
		<xsl:call-template name="SubstringReplace">
			<xsl:with-param name="stringIn">
		<xsl:call-template name="SubstringReplace">
			<xsl:with-param name="stringIn">
				<xsl:value-of select="$tempTargetForm"/>
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

	<xsl:value-of select="$TargetForm"/>Row* Get<xsl:value-of select="$TargetForm"/>(); // <xsl:value-of select="$FieldName"/>
</xsl:if>
</xsl:for-each>
	
	bool Save();
	bool Delete();
	
	
////@@begin custom arRow
public:
////@@end custom arRow	

};
////@@end gen arRow

////@@begin gen arSet
class <xsl:value-of select="$FormularName"/>RowSet: public wxActiveRecordRowSet{
public:
	<xsl:value-of select="$FormularName"/>RowSet();
	<xsl:value-of select="$FormularName"/>RowSet(wxActiveRecord* activeRecord);
	<xsl:value-of select="$FormularName"/>RowSet(DatabaseLayer* database,const wxString&amp; table=wxT("<xsl:value-of select="$RealTableName"/>"));
	virtual <xsl:value-of select="$FormularName"/>Row* Item(unsigned long item);
	
	virtual bool SaveAll();
	
	
protected:
	static int CMPFUNC_id(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
	static int CMPFUNC_<xsl:value-of select="@name"/>(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
</xsl:for-each>
	
	static int CMPFUNC_global(wxActiveRecordRow** item1,wxActiveRecordRow** item2);
	virtual CMPFUNC_proto GetCmpFunc(const wxString&amp; var) const;

////@@begin custom arSet
public:
////@@end custom arSet
};
////@@end gen arSet


#endif //__<xsl:value-of select="$FormularName"/>_
</xsl:template>

</xsl:stylesheet>
