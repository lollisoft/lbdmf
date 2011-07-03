<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="DetailView.Designer.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>namespace ShellApplication.View<xsl:value-of select="$FormularName"/>WorkItem
{
	partial class <xsl:value-of select="$FormularName"/>DetailView
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
			int tabIndex = 0;
			int yPosStart = 40;
			int yPos = yPosStart;
			this.components = new System.ComponentModel.Container();
            System.Windows.Forms.Label idLabel = new System.Windows.Forms.Label();
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
            System.Windows.Forms.Label <xsl:value-of select="@name"/>Label = new System.Windows.Forms.Label();
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
            System.Windows.Forms.Label <xsl:value-of select="@name"/>Label = new System.Windows.Forms.Label();
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
            System.Windows.Forms.Label <xsl:value-of select="@name"/>Label = new System.Windows.Forms.Label();
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
            System.Windows.Forms.Label <xsl:value-of select="@name"/>Label = new System.Windows.Forms.Label();
			</xsl:when>
			<xsl:when test="@dbtype='String'">
            System.Windows.Forms.Label <xsl:value-of select="@name"/>Label = new System.Windows.Forms.Label();
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
            //System.Windows.Forms.Label <xsl:value-of select="@name"/>Label = new System.Windows.Forms.Label();
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
            //System.Windows.Forms.Label <xsl:value-of select="@name"/>Label = new System.Windows.Forms.Label();
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
			this.<xsl:value-of select="$FormularName"/>BindingSource = new System.Windows.Forms.BindingSource(this.components);
			this.idTextBox = new System.Windows.Forms.TextBox();
			//this.commentsButton = new System.Windows.Forms.Button();
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			this.<xsl:value-of select="@name"/>TextBox = new System.Windows.Forms.TextBox();
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			this.<xsl:value-of select="@name"/>TextBox = new System.Windows.Forms.TextBox();
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			this.<xsl:value-of select="@name"/>TextBox = new System.Windows.Forms.TextBox();
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			this.<xsl:value-of select="@name"/>TextBox = new System.Windows.Forms.TextBox();
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			this.<xsl:value-of select="@name"/>TextBox = new System.Windows.Forms.TextBox();
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
			//this.<xsl:value-of select="@name"/>TextBox = new System.Windows.Forms.TextBox();
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
			//this.<xsl:value-of select="@name"/>TextBox = new System.Windows.Forms.TextBox();
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
			((System.ComponentModel.ISupportInitialize)(this.<xsl:value-of select="$FormularName"/>BindingSource)).BeginInit();
			this.SuspendLayout();
			// 
			// idLabel
			// 
			idLabel.AutoSize = true;
			idLabel.Location = new System.Drawing.Point(27, yPos);
			idLabel.Name = "idLabel";
			idLabel.Size = new System.Drawing.Size(100, 13);
			idLabel.TabIndex = tabIndex++;
			idLabel.Text = "ID:";
			yPos += 30;
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			// 
			// <xsl:value-of select="@name"/>Label
			// 
			<xsl:value-of select="@name"/>Label.AutoSize = true;
			<xsl:value-of select="@name"/>Label.Location = new System.Drawing.Point(27, yPos);
			<xsl:value-of select="@name"/>Label.Name = "<xsl:value-of select="@name"/>Label";
			<xsl:value-of select="@name"/>Label.Size = new System.Drawing.Size(100, 13);
			<xsl:value-of select="@name"/>Label.TabIndex = tabIndex++;
			<xsl:value-of select="@name"/>Label.Text = "Last Name:";
			yPos += 30;
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			// 
			// <xsl:value-of select="@name"/>Label
			// 
			<xsl:value-of select="@name"/>Label.AutoSize = true;
			<xsl:value-of select="@name"/>Label.Location = new System.Drawing.Point(27, yPos);
			<xsl:value-of select="@name"/>Label.Name = "<xsl:value-of select="@name"/>Label";
			<xsl:value-of select="@name"/>Label.Size = new System.Drawing.Size(100, 13);
			<xsl:value-of select="@name"/>Label.TabIndex = tabIndex++;
			<xsl:value-of select="@name"/>Label.Text = "<xsl:value-of select="@name"/>:";
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			// 
			// <xsl:value-of select="@name"/>Label
			// 
			<xsl:value-of select="@name"/>Label.AutoSize = true;
			<xsl:value-of select="@name"/>Label.Location = new System.Drawing.Point(27, yPos);
			<xsl:value-of select="@name"/>Label.Name = "<xsl:value-of select="@name"/>Label";
			<xsl:value-of select="@name"/>Label.Size = new System.Drawing.Size(100, 13);
			<xsl:value-of select="@name"/>Label.TabIndex = tabIndex++;
			<xsl:value-of select="@name"/>Label.Text = "<xsl:value-of select="@name"/>:";
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			// 
			// <xsl:value-of select="@name"/>Label
			// 
			<xsl:value-of select="@name"/>Label.AutoSize = true;
			<xsl:value-of select="@name"/>Label.Location = new System.Drawing.Point(27, yPos);
			<xsl:value-of select="@name"/>Label.Name = "<xsl:value-of select="@name"/>Label";
			<xsl:value-of select="@name"/>Label.Size = new System.Drawing.Size(100, 13);
			<xsl:value-of select="@name"/>Label.TabIndex = tabIndex++;
			<xsl:value-of select="@name"/>Label.Text = "<xsl:value-of select="@name"/>:";
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			// 
			// <xsl:value-of select="@name"/>Label
			// 
			<xsl:value-of select="@name"/>Label.AutoSize = true;
			<xsl:value-of select="@name"/>Label.Location = new System.Drawing.Point(27, yPos);
			<xsl:value-of select="@name"/>Label.Name = "<xsl:value-of select="@name"/>Label";
			<xsl:value-of select="@name"/>Label.Size = new System.Drawing.Size(100, 13);
			<xsl:value-of select="@name"/>Label.TabIndex = tabIndex++;
			<xsl:value-of select="@name"/>Label.Text = "<xsl:value-of select="@name"/>:";
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
            //System.Windows.Forms.Label <xsl:value-of select="@name"/>Label;
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
            //System.Windows.Forms.Label <xsl:value-of select="@name"/>Label;
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
			yPos = yPosStart;
			// 
			// <xsl:value-of select="$FormularName"/>BindingSource
			// 
			this.<xsl:value-of select="$FormularName"/>BindingSource.DataSource = typeof(ShellApplication.Entities.<xsl:value-of select="$FormularName"/>);
			// 
			// <xsl:value-of select="$FormularName"/>TextBox
			// 
			this.idTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.<xsl:value-of select="$FormularName"/>BindingSource, "id", true));
			this.idTextBox.Location = new System.Drawing.Point(27 + 100 + 5, yPos);
			this.idTextBox.Name = "idTextBox";
			this.idTextBox.Size = new System.Drawing.Size(100, 20);
			this.idTextBox.TabIndex = tabIndex++;
			yPos += 30;
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			// 
			// <xsl:value-of select="$FormularName"/>TextBox
			// 
			this.<xsl:value-of select="@name"/>TextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.<xsl:value-of select="$FormularName"/>BindingSource, "<xsl:value-of select="@name"/>_", true));
			this.<xsl:value-of select="@name"/>TextBox.Location = new System.Drawing.Point(27 + 100 + 5, yPos);
			this.<xsl:value-of select="@name"/>TextBox.Name = "<xsl:value-of select="@name"/>TextBox";
			this.<xsl:value-of select="@name"/>TextBox.Size = new System.Drawing.Size(100, 20);
			this.<xsl:value-of select="@name"/>TextBox.TabIndex = tabIndex++;
			yPos += 30;
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			// 
			// <xsl:value-of select="$FormularName"/>TextBox
			// 
			this.<xsl:value-of select="@name"/>TextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.<xsl:value-of select="$FormularName"/>BindingSource, "<xsl:value-of select="@name"/>_", true));
			this.<xsl:value-of select="@name"/>TextBox.Location = new System.Drawing.Point(27 + 100 + 5, yPos);
			this.<xsl:value-of select="@name"/>TextBox.Name = "<xsl:value-of select="@name"/>TextBox";
			this.<xsl:value-of select="@name"/>TextBox.Size = new System.Drawing.Size(100, 20);
			this.<xsl:value-of select="@name"/>TextBox.TabIndex = tabIndex++;
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			// 
			// <xsl:value-of select="$FormularName"/>TextBox
			// 
			this.<xsl:value-of select="@name"/>TextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.<xsl:value-of select="$FormularName"/>BindingSource, "<xsl:value-of select="@name"/>_", true));
			this.<xsl:value-of select="@name"/>TextBox.Location = new System.Drawing.Point(27 + 100 + 5, yPos);
			this.<xsl:value-of select="@name"/>TextBox.Name = "<xsl:value-of select="@name"/>TextBox";
			this.<xsl:value-of select="@name"/>TextBox.Size = new System.Drawing.Size(100, 20);
			this.<xsl:value-of select="@name"/>TextBox.TabIndex = tabIndex++;
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			// 
			// <xsl:value-of select="$FormularName"/>TextBox
			// 
			this.<xsl:value-of select="@name"/>TextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.<xsl:value-of select="$FormularName"/>BindingSource, "<xsl:value-of select="@name"/>_", true));
			this.<xsl:value-of select="@name"/>TextBox.Location = new System.Drawing.Point(27 + 100 + 5, yPos);
			this.<xsl:value-of select="@name"/>TextBox.Name = "<xsl:value-of select="@name"/>TextBox";
			this.<xsl:value-of select="@name"/>TextBox.Size = new System.Drawing.Size(100, 20);
			this.<xsl:value-of select="@name"/>TextBox.TabIndex = tabIndex++;
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			// 
			// <xsl:value-of select="$FormularName"/>TextBox
			// 
			this.<xsl:value-of select="@name"/>TextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.<xsl:value-of select="$FormularName"/>BindingSource, "<xsl:value-of select="@name"/>_", true));
			this.<xsl:value-of select="@name"/>TextBox.Location = new System.Drawing.Point(27 + 100 + 5, yPos);
			this.<xsl:value-of select="@name"/>TextBox.Name = "<xsl:value-of select="@name"/>TextBox";
			this.<xsl:value-of select="@name"/>TextBox.Size = new System.Drawing.Size(100, 20);
			this.<xsl:value-of select="@name"/>TextBox.TabIndex = tabIndex++;
			yPos += 30;
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
            //System.Windows.Forms.Label <xsl:value-of select="@name"/>Label;
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
            //System.Windows.Forms.Label <xsl:value-of select="@name"/>Label;
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
			// 
			// commentsButton
			// 
			//this.commentsButton.Location = new System.Drawing.Point(18, 203);
			//this.commentsButton.Name = "commentsButton";
			//this.commentsButton.Size = new System.Drawing.Size(75, 23);
			//this.commentsButton.TabIndex = 12;
			//this.commentsButton.Text = "Comments";
			//this.commentsButton.Click += new System.EventHandler(this.commentsButton_Click);
			// 
			// <xsl:value-of select="$FormularName"/>DetailView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			//this.Controls.Add(this.commentsButton);
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			this.Controls.Add(this.<xsl:value-of select="@name"/>TextBox);
			this.Controls.Add(<xsl:value-of select="@name"/>Label);
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			this.Controls.Add(this.<xsl:value-of select="@name"/>TextBox);
			this.Controls.Add(<xsl:value-of select="@name"/>Label);
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			this.Controls.Add(this.<xsl:value-of select="@name"/>TextBox);
			this.Controls.Add(<xsl:value-of select="@name"/>Label);
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			this.Controls.Add(this.<xsl:value-of select="@name"/>TextBox);
			this.Controls.Add(<xsl:value-of select="@name"/>Label);
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			this.Controls.Add(this.<xsl:value-of select="@name"/>TextBox);
			this.Controls.Add(<xsl:value-of select="@name"/>Label);
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
			//this.Controls.Add(this.<xsl:value-of select="@name"/>TextBox);
			//this.Controls.Add(<xsl:value-of select="@name"/>Label);
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
			//this.Controls.Add(this.<xsl:value-of select="@name"/>TextBox);
			//this.Controls.Add(<xsl:value-of select="@name"/>Label);
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
			this.Controls.Add(idLabel);
			this.Controls.Add(this.idTextBox);
			this.Name = "<xsl:value-of select="$FormularName"/>DetailView";
			this.Size = new System.Drawing.Size(303, 229);
			this.Title = "<xsl:value-of select="$FormularName"/> Details";
			this.Controls.SetChildIndex(this.idTextBox, 0);
			this.Controls.SetChildIndex(idLabel, 0);
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			this.Controls.SetChildIndex(this.<xsl:value-of select="@name"/>TextBox, 0);
			this.Controls.SetChildIndex(<xsl:value-of select="@name"/>Label, 0);
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			this.Controls.SetChildIndex(this.<xsl:value-of select="@name"/>TextBox, 0);
			this.Controls.SetChildIndex(<xsl:value-of select="@name"/>Label, 0);
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			this.Controls.SetChildIndex(this.<xsl:value-of select="@name"/>TextBox, 0);
			this.Controls.SetChildIndex(<xsl:value-of select="@name"/>Label, 0);
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			this.Controls.SetChildIndex(this.<xsl:value-of select="@name"/>TextBox, 0);
			this.Controls.SetChildIndex(<xsl:value-of select="@name"/>Label, 0);
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			this.Controls.SetChildIndex(this.<xsl:value-of select="@name"/>TextBox, 0);
			this.Controls.SetChildIndex(<xsl:value-of select="@name"/>Label, 0);
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
			//this.Controls.SetChildIndex(this.<xsl:value-of select="@name"/>TextBox, 0);
			//this.Controls.SetChildIndex(<xsl:value-of select="@name"/>Label, 0);
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
			//this.Controls.SetChildIndex(this.<xsl:value-of select="@name"/>TextBox, 0);
			//this.Controls.SetChildIndex(<xsl:value-of select="@name"/>Label, 0);
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
			//this.Controls.SetChildIndex(this.commentsButton, 0);
			((System.ComponentModel.ISupportInitialize)(this.<xsl:value-of select="$FormularName"/>BindingSource)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.BindingSource <xsl:value-of select="$FormularName"/>BindingSource;
		private System.Windows.Forms.TextBox idTextBox;
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
		private System.Windows.Forms.TextBox <xsl:value-of select="@name"/>TextBox;
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
		private System.Windows.Forms.TextBox <xsl:value-of select="@name"/>TextBox;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
		private System.Windows.Forms.TextBox <xsl:value-of select="@name"/>TextBox;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
		private System.Windows.Forms.TextBox <xsl:value-of select="@name"/>TextBox;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
		private System.Windows.Forms.TextBox <xsl:value-of select="@name"/>TextBox;
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
		//private System.Windows.Forms.TextBox <xsl:value-of select="@name"/>TextBox;
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
		//private System.Windows.Forms.TextBox <xsl:value-of select="@name"/>TextBox;
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
		//private System.Windows.Forms.Button commentsButton;

	}
}
</xsl:template>
</xsl:stylesheet>
