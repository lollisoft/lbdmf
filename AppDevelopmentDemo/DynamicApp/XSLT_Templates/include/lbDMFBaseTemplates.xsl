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
<xsl:template name="SubstringReplace">
	<xsl:param name="stringIn"/>
	<xsl:param name="substringIn"/>
	<xsl:param name="substringOut"/>
	<xsl:choose>
		<xsl:when test="contains($stringIn,$substringIn)">
			<xsl:value-of select="concat(substring-before($stringIn,$substringIn),$substringOut)"/>
			<xsl:call-template name="SubstringReplace">
				<xsl:with-param name="stringIn" select="substring-after($stringIn,$substringIn)"/>
				<xsl:with-param name="substringIn" select="$substringIn"/>
				<xsl:with-param name="substringOut" select="$substringOut"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$stringIn"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<!-- I always have trouble using the valur from the database (platform specific). The application must chdir to the desired directory for these templates to work.
<xsl:variable name="codegenbasedir" select="//lbDMF/applicationparameter/parameter[@applicationid=$ApplicationID][@name='codegenbasedir']/@value"/>
-->
<xsl:variable name="codegenbasedir" select="''"/>
<xsl:variable name="codegentarget" select="//lbDMF/applicationparameter/parameter[@applicationid=$ApplicationID][@name='codegentarget']/@value"/>
<xsl:variable name="basedir">
<xsl:if test="$codegenbasedir=''"><xsl:value-of select="'.'"/></xsl:if>
<xsl:if test="$codegenbasedir!=''"><xsl:value-of select="$codegenbasedir"/></xsl:if>
</xsl:variable>

<xsl:variable name="pluginsdir">
<xsl:choose>
<xsl:when test="$codegentarget!=''">Code/Targets/<xsl:value-of select="$codegentarget"/>/Plugins</xsl:when>
<xsl:otherwise>Code/Targets/lbDMF/Plugins</xsl:otherwise>
</xsl:choose>
</xsl:variable>
<xsl:variable name="appmoduledir">
<xsl:choose>
<xsl:when test="$codegentarget!=''">Code/Targets/<xsl:value-of select="$codegentarget"/>/Modules</xsl:when>
<xsl:otherwise>Code/Targets/lbDMF/Modules</xsl:otherwise>
</xsl:choose>
</xsl:variable>
<xsl:variable name="appexecutedir">
<xsl:choose>
<xsl:when test="$codegentarget!=''">Code/Targets/<xsl:value-of select="$codegentarget"/>/WxGUI_Applications</xsl:when>
<xsl:otherwise>Code/Targets/lbDMF/WxGUI_Applications</xsl:otherwise>
</xsl:choose>
</xsl:variable>
<xsl:variable name="consoleappexecutedir">
<xsl:choose>
<xsl:when test="$codegentarget!=''">Code/Targets/<xsl:value-of select="$codegentarget"/>/Console_Applications</xsl:when>
<xsl:otherwise>Code/Targets/lbDMF/Console_Applications</xsl:otherwise>
</xsl:choose>
</xsl:variable>

</xsl:stylesheet>
