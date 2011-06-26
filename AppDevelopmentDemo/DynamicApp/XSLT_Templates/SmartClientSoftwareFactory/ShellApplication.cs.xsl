<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ShellApplication.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI.WinForms;

namespace ShellApplication
{
	public class ShellApplication : FormShellApplication&lt;ShellWorkItem, ShellForm&gt;
	{
		[STAThread]
		static void Main()
		{
			new ShellApplication().Run();
		}
	}
}
</xsl:template>
</xsl:stylesheet>