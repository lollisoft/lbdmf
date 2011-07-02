<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="Main.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System;
using System.Windows.Forms;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.CompositeUI.SmartParts;
using System.Collections.ObjectModel;

namespace ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// The SmartPart attribute tells the SmartPartMonitor to add this view 
	/// to the WorkItem.
	/// &lt;/summary&gt;
	[SmartPart]
	public partial class <xsl:value-of select="$FormularName"/>Main : UserControl, IWorkspace
	{
		/// &lt;summary&gt;
		/// Constructor
		/// &lt;/summary&gt;
		public <xsl:value-of select="$FormularName"/>Main()
		{
			InitializeComponent();
		}

		// You can make anything a workspace by implementing the
		// IWorkspace interface.
		#region IWorkspace Members

		/// &lt;summary&gt;
		/// Fired when a smartpart is closing.
		/// &lt;/summary&gt;
		public event EventHandler&lt;WorkspaceCancelEventArgs&gt; SmartPartClosing;

		/// &lt;summary&gt;
		/// Fires when the smartpart is activated.
		/// &lt;/summary&gt;
		public event EventHandler&lt;WorkspaceEventArgs&gt; SmartPartActivated
		{
			add { throw new Exception("The method or operation is not implemented."); }
			remove { throw new Exception("The method or operation is not implemented."); }
		}

		/// &lt;summary&gt;
		/// Shows the given smartpart in a workspace with the 
		/// given smartpartinfo which provides additional information.
		/// &lt;/summary&gt;
		/// &lt;param name="smartPart"&gt;&lt;/param&gt;
		/// &lt;param name="smartPartInfo"&gt;&lt;/param&gt;
		public void Show(object smartPart, ISmartPartInfo smartPartInfo)
		{
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Show(smartPart, smartPartInfo);
		}

		/// &lt;summary&gt;
		/// Shows the given smartpart in a workspace.
		/// &lt;/summary&gt;
		/// &lt;param name="smartPart"&gt;&lt;/param&gt;
		public void Show(object smartPart)
		{
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Show(smartPart);
		}

		/// &lt;summary&gt;
		/// Hides the given smartpart.
		/// &lt;/summary&gt;
		/// &lt;param name="smartPart"&gt;&lt;/param&gt;
		public void Hide(object smartPart)
		{
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Hide(smartPart);
		}

		/// &lt;summary&gt;
		/// Closes the given smartpart.
		/// &lt;/summary&gt;
		/// &lt;param name="smartPart"&gt;&lt;/param&gt;
		public void Close(object smartPart)
		{
			SmartPartClosing(this, new WorkspaceCancelEventArgs(smartPart));

			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Close(smartPart);
		}

		#endregion


		#region IWorkspace Members


		public ReadOnlyCollection&lt;object&gt; SmartParts
		{
			get { throw new Exception("The method or operation is not implemented."); }
		}

		public object ActiveSmartPart
		{
			get { throw new Exception("The method or operation is not implemented."); }
		}

		public void Activate(object smartPart)
		{
			throw new Exception("The method or operation is not implemented.");
		}

		public void ApplySmartPartInfo(object smartPart, ISmartPartInfo smartPartInfo)
		{
			throw new Exception("The method or operation is not implemented.");
		}

		public bool Contains(object smartPart)
		{
			throw new Exception("The method or operation is not implemented.");
		}

		public bool IsActive(object smartPart)
		{
			throw new Exception("The method or operation is not implemented.");
		}

		#endregion

	}
}
</xsl:template>
</xsl:stylesheet>
