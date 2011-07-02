<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="TitledSmartPart.Designer.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>namespace ShellApplication
{
	partial class TitledSmartPart
	{
		/// &lt;summary&gt; 
		/// Required designer variable.
		/// &lt;/summary&gt;
		private System.ComponentModel.IContainer components = null;

		/// &lt;summary&gt; 
		/// Clean up any resources being used.
		/// &lt;/summary&gt;
		/// &lt;param name="disposing"&gt;true if managed resources should be disposed; otherwise, false.&lt;/param&gt;
		protected override void Dispose(bool disposing)
		{
			if (disposing &amp;&amp; (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Component Designer generated code

		/// &lt;summary&gt; 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// &lt;/summary&gt;
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.titleLabel = new System.Windows.Forms.Label();
			this.toolTip = new System.Windows.Forms.ToolTip(this.components);
			this.SuspendLayout();
			// 
			// titleLabel
			// 
			this.titleLabel.BackColor = System.Drawing.SystemColors.ControlDark;
			this.titleLabel.Dock = System.Windows.Forms.DockStyle.Top;
			this.titleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.titleLabel.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.titleLabel.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.titleLabel.Location = new System.Drawing.Point(0, 0);
			this.titleLabel.Name = "titleLabel";
			this.titleLabel.Padding = new System.Windows.Forms.Padding(3);
			this.titleLabel.Size = new System.Drawing.Size(588, 23);
			this.titleLabel.TabIndex = 0;
			// 
			// TitledSmartPart
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.titleLabel);
			this.Name = "TitledSmartPart";
			this.Size = new System.Drawing.Size(588, 339);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Label titleLabel;
		private System.Windows.Forms.ToolTip toolTip;
	}
}
</xsl:template>
</xsl:stylesheet>
