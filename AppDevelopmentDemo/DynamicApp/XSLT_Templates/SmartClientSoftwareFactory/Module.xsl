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

<xsl:import href="Module/Browse/Controller.cs.xsl"/>
<xsl:import href="Module/Browse/BrowseWorkItem.cs.xsl"/>
<xsl:import href="Module/Browse/Main.cs.xsl"/>
<xsl:import href="Module/Browse/Main.resx.xsl"/>
<xsl:import href="Module/Browse/Main.Designer.cs.xsl"/>
<xsl:import href="Module/Entities/Entity.cs.xsl"/>


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

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
<xsl:variable name="FormularID" select="@ID"/>
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
<!--
<exsl:document href="SmartClient/{$ApplicationName}Module/Browse{$FormularName}WorkItem/{$FormularName}Main.resx" method="text">
<xsl:call-template name="Main.resx">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
</xsl:call-template>
</exsl:document>
-->
<exsl:document href="SmartClient/{$ApplicationName}Module/Browse{$FormularName}WorkItem/{$FormularName}Main.cs" method="text">
<xsl:call-template name="Main.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="SmartClient/{$ApplicationName}Module/Browse{$FormularName}WorkItem/{$FormularName}Main.Designer.cs" method="text">
<xsl:call-template name="Main.Designer.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="SmartClient/{$ApplicationName}Module/Browse{$FormularName}WorkItem/Browse{$FormularName}WorkItem.cs" method="text">
<xsl:call-template name="BrowseWorkItem.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="SmartClient/{$ApplicationName}Module/Browse{$FormularName}WorkItem/{$FormularName}Controller.cs" method="text">
<xsl:call-template name="Controller.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
</xsl:call-template>
</exsl:document>

<exsl:document href="SmartClient/{$ApplicationName}Module/Entities/{$FormularName}.cs" method="text">
<xsl:call-template name="Entity.cs">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
</xsl:call-template>
</exsl:document>

</xsl:for-each>



</xsl:template>


<xsl:template name="View">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/>


</xsl:template>

<xsl:template name="Browse">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/>


</xsl:template>

</xsl:stylesheet>
