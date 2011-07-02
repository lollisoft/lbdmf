<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="exsl.xsl"/>

<xsl:template name="ShellForm.Designer.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>namespace ShellApplication
{
	partial class ShellForm
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

		#region Windows Form Designer generated code

		/// &lt;summary&gt;
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// &lt;/summary&gt;
		private void InitializeComponent()
		{
			// The main menu
			this.mainMenuStrip = new System.Windows.Forms.MenuStrip();
			this.File = new System.Windows.Forms.ToolStripMenuItem();
			this.Exit = new System.Windows.Forms.ToolStripMenuItem();
			this.mainMenuStrip.SuspendLayout();
			//
			// splitContainer1
			//
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.tabWorkspace1 = new Microsoft.Practices.CompositeUI.WinForms.TabWorkspace();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.SuspendLayout();
			// 
			// mainMenuStrip
			// 
			this.mainMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.File});
			this.mainMenuStrip.Location = new System.Drawing.Point(0, 0);
			this.mainMenuStrip.Name = "mainMenuStrip";
			this.mainMenuStrip.Size = new System.Drawing.Size(292, 24);
			this.mainMenuStrip.TabIndex = 0;
			this.mainMenuStrip.Text = "menuStrip1";
			// 
			// File
			// 
			this.File.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Exit});
			this.File.Name = "File";
			this.File.Size = new System.Drawing.Size(35, 20);
			this.File.Text = "&amp;File";
			// 
			// Exit
			// 
			this.Exit.Name = "Exit";
			this.Exit.Size = new System.Drawing.Size(152, 22);
			this.Exit.Text = "E&amp;xit";
			this.Exit.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.tabWorkspace1);
			this.splitContainer1.Size = new System.Drawing.Size(492, 271);
			this.splitContainer1.SplitterDistance = 246;
			this.splitContainer1.TabIndex = 0;
			// 
			// tabWorkspace1
			// 
			this.tabWorkspace1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabWorkspace1.Location = new System.Drawing.Point(0, 0);
			this.tabWorkspace1.Name = "tabWorkspace1";
			this.tabWorkspace1.SelectedIndex = 0;
			this.tabWorkspace1.Size = new System.Drawing.Size(246, 271);
			this.tabWorkspace1.TabIndex = 0;
			// 
			// ShellForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(492, 271);
			this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.mainMenuStrip);
            this.MainMenuStrip = this.mainMenuStrip;
            this.Controls.Add(this.mainMenuStrip);
            this.MainMenuStrip = this.mainMenuStrip;
			this.Name = "ShellForm";
			this.Text = "Hello World Shell";
            this.mainMenuStrip.ResumeLayout(false);
            this.mainMenuStrip.PerformLayout();
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.SplitContainer splitContainer1;
		private Microsoft.Practices.CompositeUI.WinForms.TabWorkspace tabWorkspace1;
        private System.Windows.Forms.MenuStrip mainMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem File;
        private System.Windows.Forms.ToolStripMenuItem Exit;
	}
}
</xsl:template>
</xsl:stylesheet>
