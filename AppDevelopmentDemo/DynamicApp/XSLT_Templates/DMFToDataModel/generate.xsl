<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
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
<!-- Helper to create multible files. -->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<!-- EntityModelInterface -->
<xsl:import href="Interfaces-Application.h.xsl"/>

<xsl:import href="EntityModelDecl.inc.xsl"/>

<xsl:import href="Model.h.xsl"/>
<xsl:import href="Model.cpp.xsl"/>
<xsl:import href="plugin.cpp.xsl"/>

<xsl:import href="DBReaderExtension.h.xsl"/>
<xsl:import href="DBReaderExtension.cpp.xsl"/>

<xsl:import href="XMLWriterExtension.h.xsl"/>
<xsl:import href="XMLWriterExtension.cpp.xsl"/>

<xsl:import href="InternalFormatReaderExtension.h.xsl"/>
<xsl:import href="InternalFormatReaderExtension.cpp.xsl"/>

<xsl:import href="InternalFormatWriterExtension.h.xsl"/>
<xsl:import href="InternalFormatWriterExtension.cpp.xsl"/>
<xsl:import href="extensions_plugin.cpp.xsl"/>

<xsl:import href="ApplicationCompositeModel.h.xsl"/>
<xsl:import href="ApplicationCompositeModel.cpp.xsl"/>
<xsl:import href="storage_plugin.cpp.xsl"/>


<xsl:output method="text" indent="no"/>

<xsl:template match="lbDMF">
Export application code to <xsl:value-of select="$basedir"/>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName" select="concat(substring-before($OrginalApplicationName, ' '), substring-after($OrginalApplicationName, ' '))"/>

<xsl:variable name="V" select="//lbDMF/@applicationversion"/>
<xsl:variable name="tempApplicationVersion"><xsl:choose><xsl:when test="$V!=''"><xsl:value-of select="$V"/></xsl:when><xsl:otherwise>2.0</xsl:otherwise></xsl:choose></xsl:variable>
<xsl:variable name="ApplicationVersion">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempApplicationVersion"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'.'"/>
		<xsl:with-param name="substringOut" select="'_'"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="'_'"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="'_'"/>
	</xsl:call-template>
</xsl:variable>
<exsl:document href="{$basedir}/Interfaces/lbInterfaces-{$ApplicationName}.h" method="text">
<!-- === Formular specific template ====================================================================== -->
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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

<xsl:call-template name="EntityModelInterface">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName"/>
</xsl:call-template>
</xsl:for-each>

<xsl:call-template name="EntityModelInterfaceMisc">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>

</exsl:document>

<exsl:document href="{$basedir}/Interfaces/lbInterfaces-{$ApplicationName}-sub-visitor.h" method="text">
<!-- === Formular specific template ====================================================================== -->
// The sub visitor is replaced by a delegation plugin mechanism
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName1">
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

//virtual void LB_STDCALL visit(lb_I_<xsl:value-of select="$FormularName1"/>*) = 0;
</xsl:for-each>

</exsl:document>

<!-- === Formular specific template ====================================================================== -->
// The sub visitor is replaced by a delegation plugin mechanism
<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName2">
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
<exsl:document href="{$basedir}/Plugins/lbDMFDataModel/Generated_EntityModel{$FormularName2}.h" method="text">
<xsl:call-template name="Model.h">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="{$basedir}/Plugins/lbDMFDataModel/Generated_EntityModel{$FormularName2}.cpp" method="text">
<xsl:call-template name="Model.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/XMLWriterExtension_{$FormularName2}.h" method="text">
<xsl:call-template name="XMLWriterExtension.h">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/XMLWriterExtension_{$FormularName2}.cpp" method="text">
<xsl:call-template name="XMLWriterExtension.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>


<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/InternalFormatWriter_{$FormularName2}.h" method="text">
<xsl:call-template name="InternalFormatWriterExtension.h">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/InternalFormatWriter_{$FormularName2}.cpp" method="text">
<xsl:call-template name="InternalFormatWriterExtension.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/InternalFormatReader_{$FormularName2}.h" method="text">
<xsl:call-template name="InternalFormatReaderExtension.h">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/InternalFormatReader_{$FormularName2}.cpp" method="text">
<xsl:call-template name="InternalFormatReaderExtension.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/DBReader_{$FormularName2}.h" method="text">
<xsl:call-template name="DBReaderExtension.h">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/DBReader_{$FormularName2}.cpp" method="text">
<xsl:call-template name="DBReaderExtension.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName2"/>
</xsl:call-template>
</exsl:document>

</xsl:for-each>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/lbDynamicAppStorage_Generated/{$ApplicationName}_v{$ApplicationVersion}/storage_plugin.cpp" method="text">
<xsl:call-template name="storage_plugin.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/lbDynamicAppStorage_Generated/{$ApplicationName}_v{$ApplicationVersion}/ApplicationCompositeModel.h" method="text">
<xsl:call-template name="ApplicationCompositeModel.h">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/lbDynamicAppStorage_Generated/{$ApplicationName}_v{$ApplicationVersion}/ApplicationCompositeModel.cpp" method="text">
<xsl:call-template name="ApplicationCompositeModel.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/Plugins/ExtensionObjects_Generated/{$ApplicationName}/extensions_plugin.cpp" method="text">
<xsl:call-template name="extensions_plugin.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$basedir}/Plugins/lbDMFDataModel/plugin.cpp" method="text">
<xsl:call-template name="plugin.cpp">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
</xsl:call-template>
</exsl:document>


<exsl:document href="{$basedir}/AppDevelopmentDemo/DynamicApp/App/EntityModelDecl.inc" method="text">
<xsl:call-template name="EntityModelDecl.inc">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
</xsl:call-template>
</exsl:document>

</xsl:template>

<!-- here is the template that does the replacement -->
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


</xsl:stylesheet>
