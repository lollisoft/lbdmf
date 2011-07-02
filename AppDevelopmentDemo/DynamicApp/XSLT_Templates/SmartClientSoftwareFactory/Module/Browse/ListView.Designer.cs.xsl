<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="ListView.Designer.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>namespace ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem
{
	partial class <xsl:value-of select="$FormularName"/>ListView
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
			this.<xsl:value-of select="$FormularName"/>ListBox = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// <xsl:value-of select="$FormularName"/>ListBox
			// 
			this.<xsl:value-of select="$FormularName"/>ListBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.<xsl:value-of select="$FormularName"/>ListBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.<xsl:value-of select="$FormularName"/>ListBox.FormattingEnabled = true;
			this.<xsl:value-of select="$FormularName"/>ListBox.Location = new System.Drawing.Point(0, 23);
			this.<xsl:value-of select="$FormularName"/>ListBox.Name = "<xsl:value-of select="$FormularName"/>ListBox";
			this.<xsl:value-of select="$FormularName"/>ListBox.Size = new System.Drawing.Size(240, 403);
			this.<xsl:value-of select="$FormularName"/>ListBox.TabIndex = 1;
			// 
			// <xsl:value-of select="$FormularName"/>ListView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.Controls.Add(this.<xsl:value-of select="$FormularName"/>ListBox);
			this.Name = "<xsl:value-of select="$FormularName"/>ListView";
			this.Size = new System.Drawing.Size(240, 433);
			this.Title = "<xsl:value-of select="$FormularName"/>";
			this.Controls.SetChildIndex(this.<xsl:value-of select="$FormularName"/>ListBox, 0);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ListBox <xsl:value-of select="$FormularName"/>ListBox;
	}
}
</xsl:template>
</xsl:stylesheet>
