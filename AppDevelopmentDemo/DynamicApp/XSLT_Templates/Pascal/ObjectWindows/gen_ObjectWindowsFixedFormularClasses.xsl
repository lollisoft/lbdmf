<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2024-  Lothar Behrens (lothar.behrens@lollisoft.de)

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
<!-- Helper to create multible files. -->
<xsl:import href="../../include/exsl.xsl"/>

<xsl:import href="../../include/lbDMFBaseTemplates.xsl"/>

<!-- Template to create base class file for fixed database forms -->
<xsl:import href="ObjectWindowsApplication.xsl"/>

<!-- Template to create formular implementation code per formular definition 

<xsl:import href="ObjectWindowsFixedFormImplementation.xsl"/>
-->

<!-- Template to create application main module 
<xsl:import href="ObjectWindowsApplicationModul.xsl"/>
-->

<xsl:output method="text" indent="no"/>

<xsl:template match="lbDMF">
Export application code to <xsl:value-of select="$basedir"/>


<xsl:call-template name="createApplicationUnit">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

<xsl:call-template name="createApplication">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

<xsl:call-template name="createApplicationMenu">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

<xsl:call-template name="createApplicationRcDefines">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName" select="concat(substring-before($OrginalApplicationName, ' '), substring-after($OrginalApplicationName, ' '))"/>

</xsl:template>

</xsl:stylesheet>
