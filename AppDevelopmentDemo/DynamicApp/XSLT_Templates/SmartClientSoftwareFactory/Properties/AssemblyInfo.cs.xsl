<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="AssemblyInfo.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

// General Information about an assembly is controlled through the following 
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
[assembly: AssemblyTitle("ShellApplication")]
[assembly: AssemblyDescription("Smart Client Software Factory Walkthrough Shell")]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyProduct("ShellApplication")]
[assembly: AssemblyCulture("")]

// Setting ComVisible to false makes the types in this assembly not visible 
// to COM components.  If you need to access a type in this assembly from 
// COM, set the ComVisible attribute to true on that type.
[assembly: ComVisible(false)]

// The following GUID is for the ID of the typelib if this project is exposed to COM
[assembly: Guid("ea534c19-97ae-4c7c-81b9-ff0e7ec69cb0")]

</xsl:template>
</xsl:stylesheet>