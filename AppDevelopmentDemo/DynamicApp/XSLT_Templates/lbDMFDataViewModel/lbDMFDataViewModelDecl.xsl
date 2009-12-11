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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
-->

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>


<xsl:template name="createDataViewModelClassDecl">
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

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
	// Have field <xsl:value-of select="@tablename"/>.</xsl:for-each>


// Generated class for FormularID = <xsl:value-of select="$FormularID"/>
class <xsl:value-of select="$FormularName"/> : public wxDataViewListModel /*DataViewBase*/ {
public:
	<xsl:value-of select="$FormularName"/>();
	virtual ~<xsl:value-of select="$FormularName"/>();

	virtual void SetBackend(bool backend);

	virtual bool InitModel();
/*
	virtual long GetLongField(unsigned int col, unsigned int row);
	virtual wxString GetStringField(unsigned int col, unsigned int row);
	virtual bool GetBoolField(unsigned int col, unsigned int row);
	virtual wxDateTime GetDateField(unsigned int col, unsigned int row);
*/

	virtual unsigned int GetNumberOfRows();
	virtual unsigned int GetNumberOfCols();
	virtual wxString GetColType( unsigned int col );
	virtual void GetValue( wxVariant &amp;variant, unsigned int col, unsigned int row );
	virtual bool SetValue( wxVariant &amp;value, unsigned int col, unsigned int row );


protected:

	void ReadDataRow(lb_I_Query* sampleQuery);

	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
	<xsl:choose>
	<xsl:when test="@isfk='1'">
	wxArrayString m_<xsl:value-of select="@name"/>;
	</xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
	wxArrayString m_<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
	wxArrayString m_<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
	wxArrayString m_<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
	wxArrayString m_<xsl:value-of select="@name"/>;
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
	</xsl:choose>
	</xsl:for-each>

	wxArrayString m_columnTypes;
	unsigned int numberOfRows;
	unsigned int numberOfColumns;
	bool _backend_plugin;
};
</xsl:template>

</xsl:stylesheet>
