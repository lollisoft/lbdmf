<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="Controller.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI;
using System.Windows.Forms;

namespace ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// <xsl:value-of select="$FormularName"/>Controller used by the views.
	/// &lt;/summary&gt;
	public class <xsl:value-of select="$FormularName"/>Controller : Controller
	{
		/// &lt;summary&gt;
		/// The <xsl:value-of select="$FormularName"/> State will be injected into the view.
		/// &lt;/summary&gt;
		[State("<xsl:value-of select="$FormularName"/>")]
		public List&lt;<xsl:value-of select="$FormularName"/>&gt; <xsl:value-of select="$FormularName"/>
		{
		    get { return (List&lt;<xsl:value-of select="$FormularName"/>&gt;)State["<xsl:value-of select="$FormularName"/>"]; }
		    set
		    {
		        try
		        {
		            if ((value != null) &amp;&amp;
		                (State != null))
		            {
		                State["<xsl:value-of select="$FormularName"/>"] = value;
		            }
		        }
		        catch (Exception ex)
		        {
		            MessageBox.Show(ex.Message + Environment.NewLine + ex.StackTrace);
		        }
		    }
		}

		/// &lt;summary&gt;
		/// The controller is dependent on the Browse<xsl:value-of select="$FormularName"/> WorkItem
		/// and will not run with out it.
		/// &lt;/summary&gt;
		private Browse<xsl:value-of select="$FormularName"/>WorkItem _<xsl:value-of select="$FormularName"/>WorkItem = null;

		[ServiceDependency(Type = typeof(WorkItem))]
		public Browse<xsl:value-of select="$FormularName"/>WorkItem <xsl:value-of select="$FormularName"/>WorkItem
		{
			set { _<xsl:value-of select="$FormularName"/>WorkItem = value; }
		}

		/// &lt;summary&gt;
		/// Loads Mock data.
		/// &lt;/summary&gt;
		public void Populate<xsl:value-of select="$FormularName"/>Data()
		{
			if (<xsl:value-of select="$FormularName"/> == null)
			{
				throw new ArgumentNullException("<xsl:value-of select="$FormularName"/>");
			}

			//<xsl:value-of select="$FormularName"/>.Add(new <xsl:value-of select="$FormularName"/>("Jesper", "Aaberg", "One Microsoft Way, Redmond WA 98052", "CAB Rocks!"));
		}

		/// &lt;summary&gt;
		/// Shows the <xsl:value-of select="$FormularName"/> details.
		/// &lt;/summary&gt;
		/// &lt;param name="<xsl:value-of select="$FormularName"/>"&gt;&lt;/param&gt;
		public void Show<xsl:value-of select="$FormularName"/>Details(<xsl:value-of select="$FormularName"/><xsl:value-of select="' '"/><xsl:value-of select="$FormularName"/>)
		{
			// To maintain separation of concerns.
			<xsl:value-of select="$FormularName"/>WorkItem.Show<xsl:value-of select="$FormularName"/>Details(<xsl:value-of select="$FormularName"/>);
		}
	}
}
</xsl:template>
</xsl:stylesheet>
