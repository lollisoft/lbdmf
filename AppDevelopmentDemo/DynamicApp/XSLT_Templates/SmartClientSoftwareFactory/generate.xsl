<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:import href="ShellForm.cs.xsl"/>
<xsl:import href="ShellForm.Designer.cs.xsl"/>
<xsl:import href="ShellForm.resx.xsl"/>
<xsl:import href="ShellApplication.csproj.xsl"/>
<xsl:import href="ShellApplication.cs.xsl"/>
<xsl:import href="ShellWorkItem.cs.xsl"/>

<xsl:import href="Properties/AssemblyInfo.cs.xsl"/>
<xsl:import href="Properties/Resources.Designer.cs.xsl"/>
<xsl:import href="Properties/Resources.resx.xsl"/>
<xsl:import href="Properties/Settings.Designer.cs.xsl"/>
<xsl:import href="Properties/Settings.settings.xsl"/>

<xsl:output method="text" indent="no"/>

<xsl:template match="lbDMF">
<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="DBName" select="//lbDMF/applicationparameter/parameter[@name='DBName'][@applicationid=$ApplicationID]/@value"/>
<xsl:variable name="DBUser" select="//lbDMF/applicationparameter/parameter[@name='DBUser'][@applicationid=$ApplicationID]/@value"/>
<xsl:variable name="InternalDBName" select="//lbDMF/applicationparameter/parameter[@name='InternalDBName'][@applicationid=$ApplicationID]/@value"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$OrginalApplicationName"/>
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

Have application ID = <xsl:value-of select="$ApplicationID"/>
Create <xsl:value-of select="$OrginalApplicationName"/>
DBName <xsl:value-of select="$DBName"/>
InternalDBName <xsl:value-of select="$InternalDBName"/>
.


<exsl:document href="{$ApplicationName}/Properties/AssemblyInfo.cs" method="text">
<xsl:call-template name="AssemblyInfo.cs">
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="DBName" select="$DBName"/>
		<xsl:with-param name="InternalDBName" select="$InternalDBName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="{$ApplicationName}/Properties/Resources.Designer.cs" method="text">
<xsl:call-template name="Resources.Designer.cs">
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="DBName" select="$DBName"/>
		<xsl:with-param name="InternalDBName" select="$InternalDBName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="{$ApplicationName}/Properties/Resources.resx" method="text">
<xsl:call-template name="Resources.resx">
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="DBName" select="$DBName"/>
		<xsl:with-param name="InternalDBName" select="$InternalDBName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="{$ApplicationName}/Properties/Settings.Designer.cs" method="text">
<xsl:call-template name="Settings.Designer.cs">
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="DBName" select="$DBName"/>
		<xsl:with-param name="InternalDBName" select="$InternalDBName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="{$ApplicationName}/Properties/Settings.settings" method="text">
<xsl:call-template name="Settings.settings">
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="DBName" select="$DBName"/>
		<xsl:with-param name="DBUser" select="$DBUser"/>
		<xsl:with-param name="InternalDBName" select="$InternalDBName"/>
</xsl:call-template>
</exsl:document>


<exsl:document href="{$ApplicationName}/ShellWorkItem.cs" method="text">
<xsl:call-template name="ShellWorkItem.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$ApplicationName}/ShellForm.cs" method="text">
<xsl:call-template name="ShellForm.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$ApplicationName}/ShellForm.Designer.cs" method="text">
<xsl:call-template name="ShellForm.Designer.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$ApplicationName}/ShellForm.resx" method="text">
<xsl:call-template name="ShellForm.resx">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$ApplicationName}/ShellApplication.cs" method="text">
<xsl:call-template name="ShellApplication.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="{$ApplicationName}/ShellApplication.csproj" method="text">
<xsl:call-template name="ShellApplication.csproj">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
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