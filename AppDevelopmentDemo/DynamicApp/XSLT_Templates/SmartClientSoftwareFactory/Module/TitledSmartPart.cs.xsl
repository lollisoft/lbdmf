<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="TitledSmartPart.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System.Windows.Forms;
using Microsoft.Practices.CompositeUI.SmartParts;

namespace ShellApplication
{
	/// &lt;summary&gt;
	/// Base class for building other smartparts
	/// &lt;/summary&gt;
	[SmartPart]
	public partial class TitledSmartPart : UserControl
	{
		/// &lt;summary&gt;
		/// Constructor
		/// &lt;/summary&gt;
		public TitledSmartPart()
		{
			InitializeComponent();
		}

		/// &lt;summary&gt;
		/// Text that will show in the title label.
		/// &lt;/summary&gt;
		public string Title
		{
			get
			{
				return titleLabel.Text;
			}
			set
			{
				titleLabel.Text = value;
			}
		}

		/// &lt;summary&gt;
		/// Tooltip for the smartpart.
		/// &lt;/summary&gt;
		public string Description
		{
			get
			{
				return toolTip.GetToolTip(titleLabel);
			}
			set
			{
				toolTip.SetToolTip(titleLabel, value);
			}
		}
	}

}
</xsl:template>
</xsl:stylesheet>
