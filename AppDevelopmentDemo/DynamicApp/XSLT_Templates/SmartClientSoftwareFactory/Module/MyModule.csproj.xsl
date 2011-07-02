<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="MyModule.csproj">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>&lt;Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003" ToolsVersion="3.5"&gt;
  &lt;PropertyGroup&gt;
    &lt;Configuration Condition=" '$(Configuration)' == '' "&gt;Debug&lt;/Configuration&gt;
    &lt;Platform Condition=" '$(Platform)' == '' "&gt;AnyCPU&lt;/Platform&gt;
    &lt;ProductVersion&gt;9.0.21022&lt;/ProductVersion&gt;
    &lt;SchemaVersion&gt;2.0&lt;/SchemaVersion&gt;
    &lt;ProjectGuid&gt;{97B7A004-2B34-462C-A055-4A02972A99A9}&lt;/ProjectGuid&gt;
    &lt;OutputType&gt;Library&lt;/OutputType&gt;
    &lt;AppDesignerFolder&gt;Properties&lt;/AppDesignerFolder&gt;
    &lt;RootNamespace&gt;<xsl:value-of select="$ApplicationName"/>Module&lt;/RootNamespace&gt;
    &lt;AssemblyName&gt;<xsl:value-of select="$ApplicationName"/>Module&lt;/AssemblyName&gt;&lt;FileUpgradeFlags&gt;
    &lt;/FileUpgradeFlags&gt;
    &lt;OldToolsVersion&gt;2.0&lt;/OldToolsVersion&gt;
    &lt;UpgradeBackupLocation&gt;
    &lt;/UpgradeBackupLocation&gt;
    &lt;TargetFrameworkVersion&gt;v3.5&lt;/TargetFrameworkVersion&gt;
    &lt;PublishUrl&gt;publish\&lt;/PublishUrl&gt;
    &lt;Install&gt;true&lt;/Install&gt;
    &lt;InstallFrom&gt;Disk&lt;/InstallFrom&gt;
    &lt;UpdateEnabled&gt;false&lt;/UpdateEnabled&gt;
    &lt;UpdateMode&gt;Foreground&lt;/UpdateMode&gt;
    &lt;UpdateInterval&gt;7&lt;/UpdateInterval&gt;
    &lt;UpdateIntervalUnits&gt;Days&lt;/UpdateIntervalUnits&gt;
    &lt;UpdatePeriodically&gt;false&lt;/UpdatePeriodically&gt;
    &lt;UpdateRequired&gt;false&lt;/UpdateRequired&gt;
    &lt;MapFileExtensions&gt;true&lt;/MapFileExtensions&gt;
    &lt;ApplicationRevision&gt;0&lt;/ApplicationRevision&gt;
    &lt;ApplicationVersion&gt;1.0.0.%2a&lt;/ApplicationVersion&gt;
    &lt;IsWebBootstrapper&gt;false&lt;/IsWebBootstrapper&gt;
    &lt;UseApplicationTrust&gt;false&lt;/UseApplicationTrust&gt;
    &lt;BootstrapperEnabled&gt;true&lt;/BootstrapperEnabled&gt;
  &lt;/PropertyGroup&gt;
  &lt;PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' "&gt;
    &lt;DebugSymbols&gt;true&lt;/DebugSymbols&gt;
    &lt;DebugType&gt;full&lt;/DebugType&gt;
    &lt;Optimize&gt;false&lt;/Optimize&gt;
    &lt;OutputPath&gt;..\ShellApplication\bin\Debug\&lt;/OutputPath&gt;
    &lt;DefineConstants&gt;DEBUG;TRACE&lt;/DefineConstants&gt;
    &lt;ErrorReport&gt;prompt&lt;/ErrorReport&gt;
    &lt;WarningLevel&gt;4&lt;/WarningLevel&gt;
  &lt;/PropertyGroup&gt;
  &lt;PropertyGroup Condition=" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' "&gt;
    &lt;DebugType&gt;pdbonly&lt;/DebugType&gt;
    &lt;Optimize&gt;true&lt;/Optimize&gt;
    &lt;OutputPath&gt;..\ShellApplication\bin\Release\&lt;/OutputPath&gt;
    &lt;DefineConstants&gt;TRACE&lt;/DefineConstants&gt;
    &lt;ErrorReport&gt;prompt&lt;/ErrorReport&gt;
    &lt;WarningLevel&gt;4&lt;/WarningLevel&gt;
  &lt;/PropertyGroup&gt;
  &lt;ItemGroup&gt;
    &lt;Reference Include="Microsoft.Practices.ObjectBuilder, Version=1.0.51206.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a, processorArchitecture=MSIL"&gt;
      &lt;SpecificVersion&gt;False&lt;/SpecificVersion&gt;
      &lt;HintPath&gt;..\..\Lib\Microsoft.Practices.ObjectBuilder.dll&lt;/HintPath&gt;
    &lt;/Reference&gt;
    &lt;Reference Include="System" /&gt;
    &lt;Reference Include="System.Core"&gt;
      &lt;RequiredTargetFramework&gt;3.5&lt;/RequiredTargetFramework&gt;
    &lt;/Reference&gt;
    &lt;Reference Include="System.Data" /&gt;
    &lt;Reference Include="System.Windows.Forms" /&gt;
    &lt;Reference Include="System.Xml" /&gt;
	&lt;Reference Include="System.Drawing" /&gt;
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
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
    &lt;Compile Include="Browse<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>ListView.cs"&gt;
      &lt;SubType&gt;UserControl&lt;/SubType&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="Browse<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>ListView.Designer.cs"&gt;
      &lt;DependentUpon&gt;<xsl:value-of select="$FormularName"/>ListView.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="Browse<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Main.cs"&gt;
      &lt;SubType&gt;UserControl&lt;/SubType&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="Browse<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Main.Designer.cs"&gt;
      &lt;DependentUpon&gt;<xsl:value-of select="$FormularName"/>Main.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;<!--
    &lt;Compile Include="Browse<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Main.resx"&gt;
      &lt;DependentUpon&gt;<xsl:value-of select="$FormularName"/>Main.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
-->    &lt;Compile Include="Browse<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Controller.cs" /&gt;
    &lt;Compile Include="Browse<xsl:value-of select="$FormularName"/>WorkItem\Browse<xsl:value-of select="$FormularName"/>WorkItem.cs" /&gt;
</xsl:for-each>
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
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
    &lt;Compile Include="View<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>TabView.cs"&gt;
      &lt;SubType&gt;UserControl&lt;/SubType&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="View<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>TabView.Designer.cs"&gt;
      &lt;DependentUpon&gt;<xsl:value-of select="$FormularName"/>TabView.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="View<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Details.cs"&gt;
      &lt;SubType&gt;UserControl&lt;/SubType&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="View<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Details.Designer.cs"&gt;
      &lt;DependentUpon&gt;<xsl:value-of select="$FormularName"/>Details.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;<!--
    &lt;Compile Include="View<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Details.resx"&gt;
      &lt;DependentUpon&gt;<xsl:value-of select="$FormularName"/>Details.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
-->    &lt;Compile Include="View<xsl:value-of select="$FormularName"/>WorkItem\<xsl:value-of select="$FormularName"/>Controller.cs" /&gt;
    &lt;Compile Include="View<xsl:value-of select="$FormularName"/>WorkItem\View<xsl:value-of select="$FormularName"/>WorkItem.cs" /&gt;
</xsl:for-each>
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
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
    &lt;Compile Include="Entities\<xsl:value-of select="$FormularName"/>.cs" /&gt;
</xsl:for-each>
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
    &lt;Compile Include="I<xsl:value-of select="$ApplicationName"/>View.cs" /&gt;
    &lt;Compile Include="<xsl:value-of select="$ApplicationName"/>ModuleInit.cs" /&gt;
    &lt;Compile Include="<xsl:value-of select="$ApplicationName"/>Presenter.cs" /&gt;
    &lt;Compile Include="<xsl:value-of select="$ApplicationName"/>View.cs"&gt;
      &lt;SubType&gt;UserControl&lt;/SubType&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="<xsl:value-of select="$ApplicationName"/>View.Designer.cs"&gt;
      &lt;DependentUpon&gt;<xsl:value-of select="$ApplicationName"/>View.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="<xsl:value-of select="$ApplicationName"/>WorkItem.cs" /&gt;
    &lt;Compile Include="TitledSmartPart.cs"&gt;
      &lt;SubType&gt;UserControl&lt;/SubType&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="TitledSmartPart.Designer.cs"&gt;
      &lt;DependentUpon&gt;TitledSmartPart.cs&lt;/DependentUpon&gt;
    &lt;/Compile&gt;
    &lt;Compile Include="Properties\AssemblyInfo.cs" /&gt;
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
    &lt;ProjectReference Include="..\..\Blocks\CAB\CS\Source\CompositeUI.WinForms\CompositeUI.WinForms.csproj"&gt;
      &lt;Project&gt;{073BCD60-F2FB-4DB9-92FB-403C8F9E8DD0}&lt;/Project&gt;
      &lt;Name&gt;CompositeUI.WinForms&lt;/Name&gt;
    &lt;/ProjectReference&gt;
    &lt;ProjectReference Include="..\..\Blocks\CAB\CS\Source\CompositeUI\CompositeUI.csproj"&gt;
      &lt;Project&gt;{C478E40B-A05E-4C69-9AB3-7A3BB374243F}&lt;/Project&gt;
      &lt;Name&gt;CompositeUI&lt;/Name&gt;
    &lt;/ProjectReference&gt;
  &lt;/ItemGroup&gt;
  &lt;ItemGroup&gt;
    &lt;BootstrapperPackage Include="Microsoft.Net.Framework.2.0"&gt;
      &lt;Visible&gt;False&lt;/Visible&gt;
      &lt;ProductName&gt;.NET Framework 2.0 %28x86%29&lt;/ProductName&gt;
      &lt;Install&gt;true&lt;/Install&gt;
    &lt;/BootstrapperPackage&gt;
    &lt;BootstrapperPackage Include="Microsoft.Net.Framework.3.0"&gt;
      &lt;Visible&gt;False&lt;/Visible&gt;
      &lt;ProductName&gt;.NET Framework 3.0 %28x86%29&lt;/ProductName&gt;
      &lt;Install&gt;false&lt;/Install&gt;
    &lt;/BootstrapperPackage&gt;
    &lt;BootstrapperPackage Include="Microsoft.Net.Framework.3.5"&gt;
      &lt;Visible&gt;False&lt;/Visible&gt;
      &lt;ProductName&gt;.NET Framework 3.5&lt;/ProductName&gt;
      &lt;Install&gt;false&lt;/Install&gt;
    &lt;/BootstrapperPackage&gt;
  &lt;/ItemGroup&gt;
  &lt;Import Project="$(MSBuildBinPath)\Microsoft.CSharp.targets" /&gt;
  &lt;!-- To modify your build process, add your task inside one of the targets below and uncomment it. 
       Other similar extension points exist, see Microsoft.Common.targets.
  &lt;Target Name="BeforeBuild"&gt;
  &lt;/Target&gt;
  &lt;Target Name="AfterBuild"&gt;
  &lt;/Target&gt;
  --&gt;
&lt;/Project&gt;
</xsl:template>
</xsl:stylesheet>