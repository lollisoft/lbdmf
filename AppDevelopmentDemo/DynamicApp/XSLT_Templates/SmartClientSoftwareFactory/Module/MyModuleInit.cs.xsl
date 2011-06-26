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

		[ServiceDependency]
		public IWorkItemTypeCatalogService myWorkItemCatalog
		{
			set { myCatalogService = value; }
		}

		public override void Load()
		{
			base.Load();
			myCatalogService.RegisterWorkItem&lt;MyWorkItem&gt;();
		}
	}
}
</xsl:template>
</xsl:stylesheet>