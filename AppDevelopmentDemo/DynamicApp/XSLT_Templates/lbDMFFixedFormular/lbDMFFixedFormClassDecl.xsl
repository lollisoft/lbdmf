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

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
	<xsl:variable name="FieldName" select="@name"/>
	<xsl:variable name="TableName" select="@tablename"/>
	// Have field <xsl:value-of select="@tablename"/>.</xsl:for-each>


// Generated class for FormularID = <xsl:value-of select="$FormularID"/>
class <xsl:value-of select="$FormularName"/> : public FixedFormularBase {
public:
	<xsl:value-of select="$FormularName"/>();
	virtual ~<xsl:value-of select="$FormularName"/>();

	DECLARE_LB_UNKNOWN()

	<xsl:for-each select="//lbDMF/actionsteps/action[@what=$tempFormularName]">
	<xsl:variable name="actionid" select="@actionid"/>
	<xsl:variable name="formularid" select="//lbDMF/formularactions/action[@actionid=$actionid]/@formularid"/>
	<xsl:variable name="tempForeignFormularName" select="//lbDMF/formulare/formular[@ID=$formularid]/@name"/>
	
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

	<xsl:variable name="ForeignAppID" select="//lbDMF/formulare/formular[@name=$tempForeignFormularName]/@applicationid"/>
	<xsl:if test="'$ForeignAppID'='$ApplicationID'">
private:
	// My AppID = <xsl:value-of select="$ApplicationID"/>
	// AppID for foreign formular = <xsl:value-of select="//lbDMF/formulare/formular[@name=$tempForeignFormularName]/@applicationid"/>
	// tempForeignFormularName = <xsl:value-of select="//lbDMF/formulare/formular[@name=$tempForeignFormularName]/@name"/>
	//
	
	<xsl:value-of select="$ForeignFormularName"/>* detailForm_<xsl:value-of select="$ForeignFormularName"/>;

	</xsl:if>


public:	
	<xsl:if test="@steptyp='4'">
	//bool LB_STDCALL updateFromMaster_<xsl:value-of select="$ForeignFormularName"/>(wxString column, wxString&amp; value);
	</xsl:if>
	<xsl:if test="@steptyp='5'">
	bool LB_STDCALL updateFromMaster_<xsl:value-of select="$ForeignFormularName"/>(wxString column, wxString&amp; value);
	</xsl:if>
	
	</xsl:for-each>
		
	<xsl:for-each select="//lbDMF/formularactions/action[@formularid=$FormularID]">
		<xsl:variable name="actionid" select="@actionid"/>
		<xsl:variable name="event" select="@event"/>
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
			//<xsl:value-of select="$DetailFormularName"/>* detailForm_<xsl:value-of select="$DetailFormularName"/>;
		</xsl:when>
		<xsl:when test="@steptyp='5'">
			//<xsl:value-of select="$DetailFormularName"/>* masterForm_<xsl:value-of select="$DetailFormularName"/>;
		</xsl:when>
	</xsl:choose>
	</xsl:for-each>
	
	<xsl:variable name="EventIdentifer">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$event"/>
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

	lbErrCodes LB_STDCALL OnActionButton_<xsl:value-of select="$EventIdentifer"/>(lb_I_Unknown* uk);
	</xsl:for-each>

	<xsl:for-each select="//lbDMF/formularactions/action">
		<xsl:variable name="actionid" select="@actionid"/>
		<xsl:variable name="formularid" select="@formularid"/>
		<xsl:variable name="event" select="@event"/>
		<xsl:variable name="aID" select="//lbDMF/formulare/formular[@ID=$formularid]/@applicationid"/>
		<xsl:if test="$ApplicationID=$aID">
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
	<xsl:if test="$FormularName=$DetailFormularName">
	<xsl:variable name="tempRealDetailFormularName" select="//lbDMF/formulare/formular[@ID=$formularid]/@name"/>
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
	<xsl:if test="@steptyp='4'">
	bool LB_STDCALL updateFromMaster_<xsl:value-of select="$RealDetailFormularName"/>(wxString column, wxString&amp; value);
	</xsl:if>
	<xsl:if test="@steptyp='5'">
	void LB_STDCALL updateFromDetail_<xsl:value-of select="$RealDetailFormularName"/>(wxString column, wxString&amp; value);
	</xsl:if>
	</xsl:if>
	</xsl:for-each>
	</xsl:if>
	</xsl:for-each>
	<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID][@isfk='1']">
	void LB_STDCALL getForeignKeyMappingData_<xsl:value-of select="@name"/>(wxChoice* choice);
	</xsl:for-each>

	void LB_STDCALL init();

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);

	lbErrCodes LB_STDCALL lbDBAdd(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbDBUpdate();
	lbErrCodes LB_STDCALL lbDBClear();
	lbErrCodes LB_STDCALL lbDBRead();

};
</xsl:template>

</xsl:stylesheet>
