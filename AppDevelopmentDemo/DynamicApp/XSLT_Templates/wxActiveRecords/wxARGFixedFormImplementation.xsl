<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../include/exsl.xsl"/>

<!-- Template to create a plugin definition for a given class-->
<xsl:import href="wxARGFixedFormPlugin.xsl"/>

<!-- Template to create a class definition for a given class -->
<xsl:import href="wxARGFixedFormClassDecl.xsl"/>

<!-- Template to create a class implementation for a given class -->
<xsl:import href="wxARGFixedFormClassImpl.xsl"/>

<xsl:output method="text" indent="no"/>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
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


<!-- This template creates a pair of files per formular name -->
<xsl:template name="CreateFixedFormImplementation">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>

<!-- Create the header for the formular -->
<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/{$ApplicationName}{$FormName}Implementation.h" method="text">
/* Implementation class for fixed database formular header file
 * Application: <xsl:value-of select="$ApplicationName"/>
 * Formular: <xsl:value-of select="$FormName"/>
 */
 
<xsl:call-template name="createFormClassDecl">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
		<xsl:with-param name="ParamFormularName"><xsl:value-of select="$FormName"/></xsl:with-param>
</xsl:call-template>
 
</exsl:document>

<!-- Create the implementation for the formular -->
<exsl:document href="{$basedir}/{$pluginsdir}/{$ApplicationName}/{$ApplicationName}{$FormName}Implementation.cpp" method="text">
/* Implementation class for fixed database formular
 *  <xsl:value-of select="$ApplicationName"/>
 */
 
<!--<xsl:call-template name="createCPPPreample"/>-->

<xsl:call-template name="createFormClassImpl">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
</xsl:call-template>
<!--  
<xsl:call-template name="createFormPlugin">
		<xsl:with-param name="ApplicationID"><xsl:value-of select="$ApplicationID"/></xsl:with-param>
		<xsl:with-param name="FormularID"><xsl:value-of select="$FormularID"/></xsl:with-param>
</xsl:call-template>
-->
</exsl:document>

</xsl:template>

</xsl:stylesheet>