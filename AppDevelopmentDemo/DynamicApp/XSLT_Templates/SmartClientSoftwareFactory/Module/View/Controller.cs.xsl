<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="Controller.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI;

namespace SmartPartQuickStart.View<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// Controller for the <xsl:value-of select="$FormularName"/> comments view.
	/// &lt;/summary&gt;
	public class <xsl:value-of select="$FormularName"/>Controller : Controller
	{
		/// &lt;summary&gt;
		/// Has to have a <xsl:value-of select="$FormularName"/> workitem to work.
		/// &lt;/summary&gt;
		private View<xsl:value-of select="$FormularName"/>WorkItem <xsl:value-of select="$FormularName"/>WorkItem = null;

		[ServiceDependency(Type = typeof(WorkItem))]
		public View<xsl:value-of select="$FormularName"/>WorkItem <xsl:value-of select="$FormularName"/>WorkItem
		{
			set { <xsl:value-of select="$FormularName"/>WorkItem = value; }
		}

		/// &lt;summary&gt;
		/// Calls back to the workitem to create and show
		/// the comments view.
		/// &lt;/summary&gt;
		//public void Show<xsl:value-of select="$FormularName"/>Comments()
		//{
		//	<xsl:value-of select="$FormularName"/>WorkItem.Show<xsl:value-of select="$FormularName"/>Comments();
		//}
	}
}
</xsl:template>
</xsl:stylesheet>
