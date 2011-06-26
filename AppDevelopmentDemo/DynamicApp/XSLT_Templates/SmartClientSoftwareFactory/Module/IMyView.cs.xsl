<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="IMyView.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.Text;

namespace MyModule
{
	public interface IMyView
	{
		event EventHandler Load;
		string Message { get; set; }
	}
}
</xsl:template>
</xsl:stylesheet>