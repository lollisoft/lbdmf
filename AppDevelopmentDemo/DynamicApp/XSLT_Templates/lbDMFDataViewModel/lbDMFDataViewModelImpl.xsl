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

<xsl:template name="createDataViewModelClassImpl">
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

#include "wx/dataview.h"


#include "<xsl:value-of select="$ApplicationName"/><xsl:value-of select="$FormularName"/>Implementation.h"

<xsl:value-of select="$FormularName"/>::<xsl:value-of select="$FormularName"/>() 
{
	//InitModel();
}

<xsl:value-of select="$FormularName"/>::~<xsl:value-of select="$FormularName"/>() {
}

void <xsl:value-of select="$FormularName"/>::SetBackend(bool backend) {
	_backend_plugin = backend;
}


unsigned int <xsl:value-of select="$FormularName"/>::GetNumberOfRows()
{
	return numberOfRows;
}

unsigned int <xsl:value-of select="$FormularName"/>::GetNumberOfCols()
{
	return numberOfColumns;
}

wxString <xsl:value-of select="$FormularName"/>::GetColType( unsigned int col )
{
	return m_columnTypes[col];
}

void <xsl:value-of select="$FormularName"/>::ReadDataRow(lb_I_Query* sampleQuery) {
	int column = 0;
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/> 
	<xsl:variable name="TableName" select="@tablename"/>
	column++;
	<xsl:choose>
	<xsl:when test="@isfk='1'">
		UAP(lb_I_Long, l_<xsl:value-of select="@name"/>)
		l_<xsl:value-of select="@name"/> = sampleQuery-&gt;getAsLong(column);
		m_<xsl:value-of select="@name"/>.Add(l_<xsl:value-of select="@name"/>-&gt;charrep());
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
		s_<xsl:value-of select="@name"/> = sampleQuery-&gt;getAsString(column);
		if (s_<xsl:value-of select="@name"/>-&gt;charrep() == NULL) *s_<xsl:value-of select="@name"/> = "";
		m_<xsl:value-of select="@name"/>.Add(s_<xsl:value-of select="@name"/>-&gt;charrep());
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
		UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
		s_<xsl:value-of select="@name"/> = sampleQuery-&gt;getAsString(column);
		wxString b_<xsl:value-of select="@name"/>;
		if (s_<xsl:value-of select="@name"/>-&gt;charrep() == NULL)
			b_<xsl:value-of select="@name"/> = "False";
		else
			b_<xsl:value-of select="@name"/> = s_<xsl:value-of select="@name"/>-&gt;charrep();
		if (b_<xsl:value-of select="@name"/> == "true") m_<xsl:value-of select="@name"/>.Add(wxString("True"));
		if (b_<xsl:value-of select="@name"/> != "true") m_<xsl:value-of select="@name"/>.Add(wxString("False"));
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
		UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
		s_<xsl:value-of select="@name"/> = sampleQuery-&gt;getAsString(column);
		if (s_<xsl:value-of select="@name"/>-&gt;charrep() == NULL) *s_<xsl:value-of select="@name"/> = "0.0";
		m_<xsl:value-of select="@name"/>.Add(s_<xsl:value-of select="@name"/>-&gt;charrep());
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
		UAP(lb_I_Long, l_<xsl:value-of select="@name"/>)
		l_<xsl:value-of select="@name"/> = sampleQuery-&gt;getAsLong(column);
		m_<xsl:value-of select="@name"/>.Add(l_<xsl:value-of select="@name"/>-&gt;charrep());
			</xsl:when>
			<xsl:when test="@dbtype='String'">
		UAP(lb_I_String, s_<xsl:value-of select="@name"/>)
		s_<xsl:value-of select="@name"/> = sampleQuery-&gt;getAsString(column);
		if (s_<xsl:value-of select="@name"/>-&gt;charrep() == NULL) *s_<xsl:value-of select="@name"/> = "";
		m_<xsl:value-of select="@name"/>.Add(s_<xsl:value-of select="@name"/>-&gt;charrep());
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
	</xsl:choose>
	</xsl:for-each>
	numberOfColumns = column;
}

bool <xsl:value-of select="$FormularName"/>::InitModel() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)

	char* databasename = "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>";
	char* databaseuser = "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>";
	char* databasepass = "<xsl:value-of select="//lbDMF/applicationparameter/parameter[@name='DBPass'][@applicationid=$ApplicationID]/@value"/>";

	char* dbbackend = "DatabaseLayerGateway";


	if (_backend_plugin) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
	} else {
		REQUEST(getModuleInstance(), lb_I_Database, database)
	}



	database-&gt;init();
	if (database-&gt;connect(databasename, databasename, databaseuser, databasepass) != ERR_NONE) {
		wxLogError("Error connecting to database.");
		return false;
	}

	sampleQuery = database->getQuery(databasename, 0);

	char* sql = "select "
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">	"<xsl:value-of select="@name"/>, "
</xsl:for-each>
	"ID FROM <xsl:value-of select="$FormularName"/> ORDER BY ID";

	sampleQuery-&gt;query(sql);
	int row = 0;

	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/> 
	<xsl:variable name="TableName" select="@tablename"/>
	<xsl:choose>
	<xsl:when test="@isfk='1'">
	m_columnTypes.Add("string");
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	m_columnTypes.Add("string");
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	m_columnTypes.Add("string");
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	m_columnTypes.Add("string");
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	m_columnTypes.Add("string");
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
	</xsl:choose>
	</xsl:for-each>

	if (sampleQuery-&gt;first() == ERR_NONE) {
		row++;
		ReadDataRow(sampleQuery.getPtr());
	
		while (sampleQuery-&gt;next() == ERR_NONE) {
			row++;
			ReadDataRow(sampleQuery.getPtr());
		}
	}
	numberOfRows = row;
	sampleQuery-&gt;close();
	database-&gt;close();
}

void <xsl:value-of select="$FormularName"/>::GetValue( wxVariant &amp;variant, unsigned int col, unsigned int row ) {
	int column = 0;
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/> 
	<xsl:variable name="TableName" select="@tablename"/>
	<xsl:choose>
	<xsl:when test="@isfk='1'">
	if (column == col) {
		variant = (wxString) m_<xsl:value-of select="@name"/>[row];
	}
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	if (column == col) {
		variant = (wxString) m_<xsl:value-of select="@name"/>[row];
	}
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	if (column == col) {
		variant = (wxString) m_<xsl:value-of select="@name"/>[row];
	}
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	if (column == col) {
		variant = (wxString) m_<xsl:value-of select="@name"/>[row];
	}
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	if (column == col) {
		variant = (wxString) m_<xsl:value-of select="@name"/>[row];
	}
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
	</xsl:choose>
	column++;
	</xsl:for-each>
}

bool <xsl:value-of select="$FormularName"/>::SetValue( wxVariant &amp;value, unsigned int col, unsigned int row ) {
	int column = 0;
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/> 
	<xsl:variable name="TableName" select="@tablename"/>
	<xsl:choose>
	<xsl:when test="@isfk='1'">
	if (column == col) {
		m_<xsl:value-of select="@name"/>[row] = value.GetString();
		return true;
	}
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	if (column == col) {
		//m_<xsl:value-of select="@name"/>[row] = value.GetString();
		return true;
	}
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	if (column == col) {
		m_<xsl:value-of select="@name"/>[row] = value.GetString();
		return true;
	}
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	if (column == col) {
		m_<xsl:value-of select="@name"/>[row] = value.GetString();
		return true;
	}
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	if (column == col) {
		m_<xsl:value-of select="@name"/>[row] = value.GetString();
		return true;
	}
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	if (column == col) {
		m_<xsl:value-of select="@name"/>[row] = value.GetString();
		return true;
	}
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
	</xsl:choose>
	column++;
	</xsl:for-each>
	return true;
}


</xsl:template>

</xsl:stylesheet>
