<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="Main.Designer.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>namespace ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem
{
	partial class <xsl:value-of select="$FormularName"/>Main
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
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.<xsl:value-of select="$FormularName"/>ListView1 = new ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem.<xsl:value-of select="$FormularName"/>ListView();
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace = new Microsoft.Practices.CompositeUI.WinForms.DeckWorkspace();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.SuspendLayout();
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.<xsl:value-of select="$FormularName"/>ListView1);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.<xsl:value-of select="$FormularName"/>DeckedWorkspace);
			this.splitContainer1.Size = new System.Drawing.Size(655, 529);
			this.splitContainer1.SplitterDistance = 219;
			this.splitContainer1.TabIndex = 1;
			this.splitContainer1.Text = "splitContainer1";
			// 
			// <xsl:value-of select="$FormularName"/>ListView1
			// 
			this.<xsl:value-of select="$FormularName"/>ListView1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.<xsl:value-of select="$FormularName"/>ListView1.Description = "";
			this.<xsl:value-of select="$FormularName"/>ListView1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.<xsl:value-of select="$FormularName"/>ListView1.Location = new System.Drawing.Point(0, 0);
			this.<xsl:value-of select="$FormularName"/>ListView1.Name = "<xsl:value-of select="$FormularName"/>ListView1";
			this.<xsl:value-of select="$FormularName"/>ListView1.Size = new System.Drawing.Size(219, 529);
			this.<xsl:value-of select="$FormularName"/>ListView1.TabIndex = 0;
			this.<xsl:value-of select="$FormularName"/>ListView1.Title = "<xsl:value-of select="$FormularName"/>";
			// 
			// <xsl:value-of select="$FormularName"/>DeckedWorkspace
			// 
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Dock = System.Windows.Forms.DockStyle.Fill;
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Location = new System.Drawing.Point(0, 0);
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Name = "<xsl:value-of select="$FormularName"/>DeckedWorkspace";
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.Size = new System.Drawing.Size(432, 529);
			this.<xsl:value-of select="$FormularName"/>DeckedWorkspace.TabIndex = 0;
			// 
			// <xsl:value-of select="$FormularName"/>Main
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.splitContainer1);
			this.Name = "<xsl:value-of select="$FormularName"/>Main";
			this.Size = new System.Drawing.Size(655, 529);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			this.splitContainer1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.SplitContainer splitContainer1;
		private <xsl:value-of select="$FormularName"/>ListView <xsl:value-of select="$FormularName"/>ListView1;
		internal Microsoft.Practices.CompositeUI.WinForms.DeckWorkspace <xsl:value-of select="$FormularName"/>DeckedWorkspace;
	}
}
</xsl:template>
</xsl:stylesheet>
