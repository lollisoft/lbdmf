<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="TabView.Designer.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>namespace ShellApplication.View<xsl:value-of select="$FormularName"/>WorkItem
{
	partial class <xsl:value-of select="$FormularName"/>TabView
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
			this.tabWorkspace1 = new Microsoft.Practices.CompositeUI.WinForms.TabWorkspace();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.<xsl:value-of select="$FormularName"/>Details = new ShellApplication.View<xsl:value-of select="$FormularName"/>WorkItem.<xsl:value-of select="$FormularName"/>DetailView();
			this.tabPage2 = new System.Windows.Forms.TabPage();
			this.smartPartPlaceholder1 = new Microsoft.Practices.CompositeUI.WinForms.SmartPartPlaceholder();
			this.tabWorkspace1.SuspendLayout();
			this.tabPage1.SuspendLayout();
			this.tabPage2.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabWorkspace1
			// 
			this.tabWorkspace1.Controls.Add(this.tabPage1);
			this.tabWorkspace1.Controls.Add(this.tabPage2);
			this.tabWorkspace1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabWorkspace1.Location = new System.Drawing.Point(0, 0);
			this.tabWorkspace1.Name = "tabWorkspace1";
			this.tabWorkspace1.SelectedIndex = 0;
			this.tabWorkspace1.Size = new System.Drawing.Size(464, 316);
			this.tabWorkspace1.TabIndex = 0;
			// 
			// tabPage1
			// 
			this.tabPage1.Controls.Add(this.<xsl:value-of select="$FormularName"/>Details);
			this.tabPage1.Location = new System.Drawing.Point(4, 22);
			this.tabPage1.Name = "tabPage1";
			this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage1.Size = new System.Drawing.Size(456, 290);
			this.tabPage1.TabIndex = 1;
			this.tabPage1.Text = "<xsl:value-of select="$FormularName"/> Details";
			// 
			// <xsl:value-of select="$FormularName"/>Details
			// 
			this.<xsl:value-of select="$FormularName"/>Details.Description = "";
			this.<xsl:value-of select="$FormularName"/>Details.Dock = System.Windows.Forms.DockStyle.Fill;
			this.<xsl:value-of select="$FormularName"/>Details.Location = new System.Drawing.Point(3, 3);
			this.<xsl:value-of select="$FormularName"/>Details.Name = "<xsl:value-of select="$FormularName"/>Details";
			this.<xsl:value-of select="$FormularName"/>Details.Size = new System.Drawing.Size(450, 284);
			this.<xsl:value-of select="$FormularName"/>Details.TabIndex = 0;
			this.<xsl:value-of select="$FormularName"/>Details.Title = "<xsl:value-of select="$FormularName"/> Details";
			// 
			// tabPage2
			// 
			this.tabPage2.Controls.Add(this.smartPartPlaceholder1);
			this.tabPage2.Location = new System.Drawing.Point(4, 22);
			this.tabPage2.Name = "tabPage2";
			this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage2.Size = new System.Drawing.Size(456, 290);
			this.tabPage2.TabIndex = 2;
			this.tabPage2.Text = "Summary";
			// 
			// smartPartPlaceholder1
			// 
			this.smartPartPlaceholder1.BackColor = System.Drawing.SystemColors.ControlDark;
			this.smartPartPlaceholder1.SmartPartName = "<xsl:value-of select="$FormularName"/>Summary";
			this.smartPartPlaceholder1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.smartPartPlaceholder1.Location = new System.Drawing.Point(3, 3);
			this.smartPartPlaceholder1.Name = "smartPartPlaceholder1";
			this.smartPartPlaceholder1.Size = new System.Drawing.Size(450, 284);
			this.smartPartPlaceholder1.TabIndex = 0;
			this.smartPartPlaceholder1.Text = "smartPartPlaceholder1";
			// 
			// <xsl:value-of select="$FormularName"/>TabView
			// 
			this.Controls.Add(this.tabWorkspace1);
			this.Name = "<xsl:value-of select="$FormularName"/>TabView";
			this.Size = new System.Drawing.Size(464, 316);
			this.tabWorkspace1.ResumeLayout(false);
			this.tabPage1.ResumeLayout(false);
			this.tabPage2.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private Microsoft.Practices.CompositeUI.WinForms.TabWorkspace tabWorkspace1;
		private System.Windows.Forms.TabPage tabPage1;
		private <xsl:value-of select="$FormularName"/>DetailView <xsl:value-of select="$FormularName"/>Details;
		private System.Windows.Forms.TabPage tabPage2;
		private Microsoft.Practices.CompositeUI.WinForms.SmartPartPlaceholder smartPartPlaceholder1;


	}
}
</xsl:template>
</xsl:stylesheet>
