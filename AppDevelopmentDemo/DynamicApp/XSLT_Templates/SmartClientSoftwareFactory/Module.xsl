<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>
<xsl:import href="Module/MyModule.sln.xsl"/>
<xsl:import href="Module/MyModule.csproj.xsl"/>
<xsl:import href="Module/MyModuleInit.cs.xsl"/>
<xsl:import href="Module/MyWorkItem.cs.xsl"/>
<xsl:import href="Module/Properties/ModuleAssemblyInfo.cs.xsl"/>

<xsl:import href="Module/MyPresenter.cs.xsl"/>
<xsl:import href="Module/MyView.cs.xsl"/>
<xsl:import href="Module/MyView.Designer.cs.xsl"/>
<xsl:import href="Module/MyView.resx.xsl"/>
<xsl:import href="Module/IMyView.cs.xsl"/>

<xsl:template name="Module">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}Module.sln" method="text">
<xsl:call-template name="MyModule.sln">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}Module.csproj" method="text">
<xsl:call-template name="MyModule.csproj">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}ModuleInit.cs" method="text">
<xsl:call-template name="MyModuleInit.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}WorkItem.cs" method="text">
<xsl:call-template name="MyWorkItem.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/I{$ApplicationName}View.cs" method="text">
<xsl:call-template name="IMyView.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}View.cs" method="text">
<xsl:call-template name="MyView.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}View.Designer.cs" method="text">
<xsl:call-template name="MyView.Designer.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}Presenter.cs" method="text">
<xsl:call-template name="MyPresenter.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/{$ApplicationName}View.resx" method="text">
<xsl:call-template name="MyView.resx">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
<exsl:document href="SmartClient/{$ApplicationName}Module/Properties/AssemblyInfo.cs" method="text">
<xsl:call-template name="ModuleAssemblyInfo.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>
</exsl:document>
</xsl:template>
</xsl:stylesheet>
