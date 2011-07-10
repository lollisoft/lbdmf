<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
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
<!-- Template to create base class file for fixed database forms -->
<xsl:import href="Interface.h.xsl"/>

<xsl:import href="XMISettings.xsl"/>

<xsl:output method="text"/>

<!-- ********** Select your database target ********** -->

<!--
<xsl:variable name="DefaultDatabaseSystem" select="'MSSQL'"/>
-->
<xsl:variable name="DefaultDatabaseSystem" select="'PostgreSQL'"/>

<xsl:variable name="TargetDBType"><xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">Sqlite</xsl:if><xsl:if test="$targetdatabase = ' '"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if><xsl:if test="$targetdatabase = ''"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if></xsl:variable>
<xsl:variable name="TargetDBVersion"><xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">1.2.3</xsl:if><xsl:if test="$targetdatabase = ' '">7.4</xsl:if><xsl:if test="$targetdatabase = ''">7.4</xsl:if></xsl:variable>

<!-- ************************************************* -->

	<xsl:template match="text()|@*">
		<xsl:value-of select="."/>
	</xsl:template>
	<xsl:template match="text()|@*"/>

<xsl:template match="packagedElement"> 
<xsl:value-of select="$activity"/></xsl:template>


	<xsl:template match="/">

--
-- Template created for <xsl:value-of select="$TargetDBType"/>
--

		<!-- Generate System database definition -->
		<xsl:variable name="_AppName"><xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/xmi:Extension/stereotype[@name='form']/../../../@name"/></xsl:variable>

		<xsl:variable name="AppName">
		<xsl:if test="$_AppName=''"><xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/../@name"/></xsl:if>
		<xsl:if test="$_AppName!=''"><xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/xmi:Extension/stereotype[@name='form']/../../../@name"/></xsl:if>		
		</xsl:variable>
		
-- Application is <xsl:value-of select="$AppName"/>. Package is <xsl:value-of select="//packagedElement[@xmi:type='uml:Class']/../@name"/>
	
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">

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

		<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
<exsl:document href="./Interfaces/I{$FormularName}.h" method="text">
<xsl:call-template name="Interface.h">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$AppName"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="./@xmi:id"/></xsl:with-param>
		<xsl:with-param name="FormName"><xsl:value-of select="$FormularName"/></xsl:with-param>
</xsl:call-template>
</exsl:document>


<!--
					<xsl:call-template name="importDMFForm">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
					</xsl:call-template>
-->
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:report']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
<!--
					<xsl:call-template name="importDMFReport">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
						<xsl:with-param name="TargetReportSystem" select="'OpenRPT'"/>
					</xsl:call-template>
-->
				</xsl:when>
			</xsl:choose>
		</xsl:for-each>
-- Script ready.
</xsl:template>
</xsl:stylesheet>
