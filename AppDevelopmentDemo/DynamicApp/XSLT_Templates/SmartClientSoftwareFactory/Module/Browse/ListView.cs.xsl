<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="ListView.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.ObjectBuilder;

namespace ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// Provides a list fo <xsl:value-of select="$FormularName"/>.
	/// &lt;/summary&gt;
	public partial class CustomerListView : TitledSmartPart
	{
		/// &lt;summary&gt;
		/// The controller will get injected into the smartpart
		/// when it is added to the workitem.
		/// &lt;/summary&gt;
		private <xsl:value-of select="$FormularName"/>Controller controller = null;

		[CreateNew]
		public <xsl:value-of select="$FormularName"/>Controller Controller
		{
			set { controller = value; }
		}

		/// &lt;summary&gt;
		/// The <xsl:value-of select="$FormularName"/> list State will be injected into the view.
		/// &lt;/summary&gt;
		private List&lt;<xsl:value-of select="$FormularName"/>&gt; <xsl:value-of select="$FormularName"/> = null;

		[State]
		public List&lt;<xsl:value-of select="$FormularName"/>&gt; <xsl:value-of select="$FormularName"/>
		{
			set { <xsl:value-of select="$FormularName"/> = value; }
		}

		/// &lt;summary&gt;
		/// Constructor
		/// &lt;/summary&gt;
		public CustomerListView()
		{
			InitializeComponent();
		}

		/// &lt;summary&gt;
		/// Sets the datasource for the listbox.
		/// Wires up the SelectedIndexChanged event.
		/// &lt;/summary&gt;
		/// &lt;param name="e"&gt;&lt;/param&gt;
		protected override void OnLoad(EventArgs e)
		{
			if (DesignMode == false)
			{
				controller.Populate<xsl:value-of select="$FormularName"/>Data();

				<xsl:value-of select="$FormularName"/>ListBox.DataSource = <xsl:value-of select="$FormularName"/>;
				<xsl:value-of select="$FormularName"/>ListBox.DisplayMember = <xsl:value-of select="$FormularName"/>.DisplayMember;

				this.<xsl:value-of select="$FormularName"/>ListBox.SelectedIndexChanged += 
					new EventHandler(<xsl:value-of select="$FormularName"/>ListBox_SelectedIndexChanged);
			}
		}

		private void <xsl:value-of select="$FormularName"/>ListBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			//Call the controller to show <xsl:value-of select="$FormularName"/> details.
			controller.Show<xsl:value-of select="$FormularName"/>Details((<xsl:value-of select="$FormularName"/>)this.<xsl:value-of select="$FormularName"/>ListBox.SelectedValue);
		}

	}
}
</xsl:template>
</xsl:stylesheet>
