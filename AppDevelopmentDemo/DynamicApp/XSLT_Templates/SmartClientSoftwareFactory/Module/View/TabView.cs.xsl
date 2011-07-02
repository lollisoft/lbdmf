<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="TabView.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System.Windows.Forms;
using Microsoft.Practices.CompositeUI.SmartParts;

namespace ShellApplication.View<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// The SmartPart attribute tells the SmartPartMonitor to add this view 
	/// to the WorkItem.
	/// &lt;/summary&gt;
	[SmartPart]
	public partial class <xsl:value-of select="$FormularName"/>TabView : UserControl
	{
		/// &lt;summary&gt;
		/// Constructor
		/// &lt;/summary&gt;
		public <xsl:value-of select="$FormularName"/>TabView()
		{
			InitializeComponent();
		}

	}
}
</xsl:template>
</xsl:stylesheet>
