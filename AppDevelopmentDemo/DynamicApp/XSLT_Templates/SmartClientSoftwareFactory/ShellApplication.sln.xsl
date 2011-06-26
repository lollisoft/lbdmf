<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ShellApplication.sln">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>
Microsoft Visual Studio Solution File, Format Version 10.00
# Visual Studio 2008
Project("{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}") = "ShellApplication", "ShellApplication.csproj", "{27939947-5B62-4C4C-99FF-898BF0C71D07}"
EndProject
Project("{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}") = "CompositeUI", "..\Blocks\CAB\CS\Source\CompositeUI\CompositeUI.csproj", "{C478E40B-A05E-4C69-9AB3-7A3BB374243F}"
EndProject
Project("{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}") = "CompositeUI.WinForms", "..\Blocks\CAB\CS\Source\CompositeUI.WinForms\CompositeUI.WinForms.csproj", "{073BCD60-F2FB-4DB9-92FB-403C8F9E8DD0}"
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|Any CPU = Debug|Any CPU
		Release|Any CPU = Release|Any CPU
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{27939947-5B62-4C4C-99FF-898BF0C71D07}.Debug|Any CPU.ActiveCfg = Debug|Any CPU
		{27939947-5B62-4C4C-99FF-898BF0C71D07}.Debug|Any CPU.Build.0 = Debug|Any CPU
		{27939947-5B62-4C4C-99FF-898BF0C71D07}.Release|Any CPU.ActiveCfg = Release|Any CPU
		{27939947-5B62-4C4C-99FF-898BF0C71D07}.Release|Any CPU.Build.0 = Release|Any CPU
		{C478E40B-A05E-4C69-9AB3-7A3BB374243F}.Debug|Any CPU.ActiveCfg = Debug|Any CPU
		{C478E40B-A05E-4C69-9AB3-7A3BB374243F}.Debug|Any CPU.Build.0 = Debug|Any CPU
		{C478E40B-A05E-4C69-9AB3-7A3BB374243F}.Release|Any CPU.ActiveCfg = Release|Any CPU
		{C478E40B-A05E-4C69-9AB3-7A3BB374243F}.Release|Any CPU.Build.0 = Release|Any CPU
		{073BCD60-F2FB-4DB9-92FB-403C8F9E8DD0}.Debug|Any CPU.ActiveCfg = Debug|Any CPU
		{073BCD60-F2FB-4DB9-92FB-403C8F9E8DD0}.Debug|Any CPU.Build.0 = Debug|Any CPU
		{073BCD60-F2FB-4DB9-92FB-403C8F9E8DD0}.Release|Any CPU.ActiveCfg = Release|Any CPU
		{073BCD60-F2FB-4DB9-92FB-403C8F9E8DD0}.Release|Any CPU.Build.0 = Release|Any CPU
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
EndGlobal
</xsl:template>
</xsl:stylesheet>