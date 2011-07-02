<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="DetailView.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.ObjectBuilder;
using ShellApplication.Entities;

namespace ShellApplication.View<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// Displays the details of the <xsl:value-of select="$FormularName"/>.
	/// &lt;/summary&gt;
	public partial class <xsl:value-of select="$FormularName"/>DetailView : TitledSmartPart
	{
		/// &lt;summary&gt;
		/// The <xsl:value-of select="$FormularName"/> State will be injected into the view.
		/// &lt;/summary&gt;
		private <xsl:value-of select="$FormularName"/> <xsl:value-of select="$FormularName"/> = null;

		[State("<xsl:value-of select="$FormularName"/>")]
		public <xsl:value-of select="$FormularName"/> <xsl:value-of select="$FormularName"/>
		{
			set { <xsl:value-of select="$FormularName"/> = value; }
		}

		/// &lt;summary&gt;
		/// The controller will be injected into the view.
		/// &lt;/summary&gt;
		private <xsl:value-of select="$FormularName"/>Controller controller = null;

		[CreateNew]
		public <xsl:value-of select="$FormularName"/>Controller Controller
		{
			set { controller = value; }
		}

		/// &lt;summary&gt;
		/// Constructor
		/// &lt;/summary&gt;
		public <xsl:value-of select="$FormularName"/>DetailView()
		{
			InitializeComponent();
		}

		/// &lt;summary&gt;
		/// Adds the <xsl:value-of select="$FormularName"/> to the binding source.
		/// &lt;/summary&gt;
		/// &lt;param name="e"&gt;&lt;/param&gt;
		protected override void OnLoad(EventArgs e)
		{
			base.OnLoad(e);

			if (this.<xsl:value-of select="$FormularName"/> != null)
			{
				this.<xsl:value-of select="$FormularName"/>BindingSource.Add(this.<xsl:value-of select="$FormularName"/>);
			}
		}

		private void commentsButton_Click(object sender, EventArgs e)
		{
			//Calls to the controller to show the comments associated with
			//the <xsl:value-of select="$FormularName"/>.
			controller.Show<xsl:value-of select="$FormularName"/>Comments();
		}
	}
}
</xsl:template>
</xsl:stylesheet>
