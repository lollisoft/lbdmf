<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="MyPresenter.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.Text;

namespace MyModule
{
	public class MyPresenter
	{
		IMyView view;

		public MyPresenter(IMyView view)
		{
			this.view = view;
			view.Load += new EventHandler(view_Load);
		}

		void view_Load(object sender, EventArgs e)
		{
			view.Message = "Hello World from a Module";
		}
	}
}
</xsl:template>
</xsl:stylesheet>