<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="MyWorkItem.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.CompositeUI.SmartParts;

namespace MyModule
{
	public class MyWorkItem: WorkItem
	{
 		public void Run(IWorkspace tabWorkspace)
 		{
 			IMyView view = this.Items.AddNew&lt;MyView&gt;();
 			MyPresenter presenter = new MyPresenter(view);
 			this.Items.Add(presenter);
 			tabWorkspace.Show(view);
 		}
	}
}
</xsl:template>
</xsl:stylesheet>