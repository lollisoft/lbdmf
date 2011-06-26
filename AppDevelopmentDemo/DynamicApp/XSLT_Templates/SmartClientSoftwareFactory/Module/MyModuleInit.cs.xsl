<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="MyModuleInit.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.CompositeUI.Services;

namespace MyModule
{
	public class MyModuleInit: ModuleInit
	{
		private IWorkItemTypeCatalogService myCatalogService;
		private WorkItem parentWorkItem;

		[ServiceDependency]
		public IWorkItemTypeCatalogService myWorkItemCatalog
		{
			set { myCatalogService = value; }
		}

		[ServiceDependency]
		public WorkItem ParentWorkItem
		{
			set { parentWorkItem = value; }
		}

		public override void Load()
		{
			base.Load();
			MyWorkItem myWorkItem = parentWorkItem.WorkItems.AddNew&lt;MyWorkItem&gt;();
			myWorkItem.Run(parentWorkItem.Workspaces["tabWorkspace1"]);
		}
	}
}
</xsl:template>
</xsl:stylesheet>