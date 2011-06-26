<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="MyView.Designer.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>namespace MyModule
{
	partial class MyView
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
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(22, 22);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(46, 17);
			this.label1.TabIndex = 0;
			this.label1.Text = "label1";
			// 
			// MyView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.label1);
			this.Name = "MyView";
			this.Size = new System.Drawing.Size(250, 250);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
	}
}
</xsl:template>
</xsl:stylesheet>