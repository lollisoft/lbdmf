<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="BrowseWorkItem.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System.Collections.Generic;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.CompositeUI.SmartParts;
using Microsoft.Practices.ObjectBuilder;
using ShellApplication.Entities;

namespace ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// Browse Cusotmer WorkItem.
	/// &lt;/summary&gt;
	public class Browse<xsl:value-of select="$FormularName"/>WorkItem : WorkItem
	{
		private <xsl:value-of select="$FormularName"/>Main <xsl:value-of select="$FormularName"/>Main;

		/// &lt;summary&gt;
		/// Starts the workitem.  You can put any logic 
		/// here that makes the workitem work as desired.
		/// &lt;/summary&gt;
		protected override void OnRunStarted()
		{
			base.OnRunStarted();

			//Create the main view that will be shown on the main workspace
			//of the MainForm.
			IWorkspace workspace = this.Workspaces["MainFormWorkspace"];
			<xsl:value-of select="$FormularName"/>Main = this.Items.AddNew&lt;<xsl:value-of select="$FormularName"/>Main&gt;("<xsl:value-of select="$FormularName"/>Main");
			workspace.Show(<xsl:value-of select="$FormularName"/>Main);
		}

		/// &lt;summary&gt;
		/// Shows the details for a <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		/// &lt;param name="<xsl:value-of select="$FormularName"/>"&gt;&lt;/param&gt;
		public void Show<xsl:value-of select="$FormularName"/>Details(<xsl:value-of select="$FormularName"/><xsl:value-of select="' '"/><xsl:value-of select="$FormularName"/>)
		{
			//Set the state so the child workitem gets injected with it.
			State["<xsl:value-of select="$FormularName"/>"] = <xsl:value-of select="$FormularName"/>;

			//Create a key for the workitem so we can check
			//later if the workitem has already been created.
			string key = <xsl:value-of select="$FormularName"/>.Id + "Details";

			View<xsl:value-of select="$FormularName"/>WorkItem.View<xsl:value-of select="$FormularName"/>WorkItem <xsl:value-of select="$FormularName"/>WorkItem = Items.Get&lt;View<xsl:value-of select="$FormularName"/>WorkItem.View<xsl:value-of select="$FormularName"/>WorkItem&gt;(key);

			if (<xsl:value-of select="$FormularName"/>WorkItem == null)
			{
				<xsl:value-of select="$FormularName"/>WorkItem =
					this.Items.AddNew&lt;View<xsl:value-of select="$FormularName"/>WorkItem.View<xsl:value-of select="$FormularName"/>WorkItem&gt;(key);
				<xsl:value-of select="$FormularName"/>WorkItem.<xsl:value-of select="$FormularName"/> = (<xsl:value-of select="$FormularName"/>)State["<xsl:value-of select="$FormularName"/>"];
			}
			
			//Run the child workitem.
			<xsl:value-of select="$FormularName"/>WorkItem.Run(<xsl:value-of select="$FormularName"/>Main.<xsl:value-of select="$FormularName"/>DeckedWorkspace);
		}
	}
}
</xsl:template>
</xsl:stylesheet>
