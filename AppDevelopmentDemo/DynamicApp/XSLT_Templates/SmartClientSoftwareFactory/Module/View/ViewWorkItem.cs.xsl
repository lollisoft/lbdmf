<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="ViewWorkItem.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>namespace ShellApplication.View<xsl:value-of select="$FormularName"/>using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.CompositeUI.SmartParts;
using Microsoft.Practices.CompositeUI.WinForms;

namespace SmartPartQuickStart.View<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// A WorkItem to handle the viewing of one <xsl:value-of select="$FormularName"/>.
	/// &lt;/summary&gt;
	public class View<xsl:value-of select="$FormularName"/>WorkItem : WorkItem
	{
		private <xsl:value-of select="$FormularName"/>TabView tabView;
		private <xsl:value-of select="$FormularName"/>CommentsView commentsView;
		private <xsl:value-of select="$FormularName"/>SummaryView <xsl:value-of select="$FormularName"/>Summary;

		/// &lt;summary&gt;
		/// Starts the workitem.
		/// &lt;/summary&gt;
		/// &lt;param name="workspace"&gt;&lt;/param&gt;
		public void Run(IWorkspace workspace)
		{
			//Create views to be used by workitem
			CreateSummaryView();
			CreateTabView();

			//Make the tabview visible in the workspace.
			workspace.Show(tabView);
		}

		/// &lt;summary&gt;
		/// Shows the custoemr comments in a new tab.
		/// &lt;/summary&gt;
		//public void Show<xsl:value-of select="$FormularName"/>Comments()
		//{
		//	//retrieve the tab workspace from the workitem.
		//	//"tabWorkspace1" is the name of the control.
		//	IWorkspace tabbedSpace = Workspaces["tabWorkspace1"];
		//
		//	if (tabbedSpace != null)
		//	{
		//		if (commentsView == null)
		//		{
		//			commentsView = this.Items.AddNew&lt;<xsl:value-of select="$FormularName"/>CommentsView&gt;("<xsl:value-of select="$FormularName"/>CommentsView");
		//			ISmartPartInfo info = new SmartPartInfo();
		//			info.Title = "Comments";
		//			this.RegisterSmartPartInfo(commentsView, info);
		//		}
		//		//The "Show" of the tabworkspace creates 
		//		//a new tab and show the comments view.
		//		tabbedSpace.Show(commentsView);
		//	}
		//}

		/// &lt;summary&gt;
		/// State that is inject in the workitem.
		/// The State is set this way so child items
		/// can get inject with the state.
		/// &lt;/summary&gt;
		public <xsl:value-of select="$FormularName"/> <xsl:value-of select="$FormularName"/>
		{
			get { return (<xsl:value-of select="$FormularName"/>)State["<xsl:value-of select="$FormularName"/>"]; }
			set { State["<xsl:value-of select="$FormularName"/>"] = value; }
		}

		//private void CreateSummaryView()
		//{
		//	if (<xsl:value-of select="$FormularName"/>Summary == null)
		//	{
		//		<xsl:value-of select="$FormularName"/>Summary = this.Items.AddNew&lt;<xsl:value-of select="$FormularName"/>SummaryView&gt;("<xsl:value-of select="$FormularName"/>Summary");
		//	}
		//}

		private void CreateTabView()
		{
			if (tabView == null)
			{
				tabView = this.Items.AddNew&lt;<xsl:value-of select="$FormularName"/>TabView&gt;("<xsl:value-of select="$FormularName"/>View");
			}
		}


	}
}
</xsl:template>
</xsl:stylesheet>
