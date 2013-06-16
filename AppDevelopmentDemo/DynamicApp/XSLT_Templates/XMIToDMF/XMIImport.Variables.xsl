<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2013  Lothar Behrens (lothar.behrens@lollisoft.de)

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

<!-- Stylesheet parameters that will overwrite those given from the XMISettings.xsl file. -->
<xsl:param name="XSLDatabaseBackendSystem"/>
<xsl:param name="XSLDatabaseBackendApplication"/>
<xsl:param name="overwriteDatabase"/>

<xsl:variable name="targetdatabase">
<xsl:if test="$XSLDatabaseBackendApplication=''"><xsl:value-of select="$settingsfile_targetdatabase"/></xsl:if>
<xsl:if test="$XSLDatabaseBackendApplication!=''"><xsl:value-of select="$XSLDatabaseBackendApplication"/></xsl:if>
</xsl:variable>
<xsl:variable name="execute_droprules">
<xsl:if test="$overwriteDatabase=''"><xsl:value-of select="$settingsfile_execute_droprules"/></xsl:if>
<xsl:if test="$overwriteDatabase!=''"><xsl:value-of select="$overwriteDatabase"/></xsl:if>
</xsl:variable>

<xsl:variable name="DefaultDatabaseSystem" select="'PostgreSQL'"/>

<xsl:variable name="TargetDBType">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = 'PostgreSQL'">PostgreSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'MSSQL'">MSSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'Sqlite'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = ' '"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
	<xsl:if test="$targetdatabase = ''"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
</xsl:variable>
<xsl:variable name="TargetDBVersion">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">1.2.3</xsl:if>
	<xsl:if test="$targetdatabase = ' '">7.4</xsl:if>
	<xsl:if test="$targetdatabase = ''">7.4</xsl:if>
</xsl:variable>


</xsl:stylesheet>
