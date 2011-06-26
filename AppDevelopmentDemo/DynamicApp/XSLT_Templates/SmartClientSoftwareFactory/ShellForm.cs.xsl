<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ShellForm.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.Practices.CompositeUI.SmartParts;
using Microsoft.Practices.CompositeUI.WinForms;

namespace ShellApplication
{
	[SmartPart]
	public partial class ShellForm : Form
	{
		public ShellForm()
		{
			InitializeComponent();
		}
	}
}
</xsl:template>
</xsl:stylesheet>