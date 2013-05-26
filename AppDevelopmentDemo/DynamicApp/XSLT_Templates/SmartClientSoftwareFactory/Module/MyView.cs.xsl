<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../exsl.xsl"/>

<xsl:template name="MyView.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/>using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using Microsoft.Practices.CompositeUI;
using Microsoft.Practices.CompositeUI.SmartParts;

namespace MyModule
{
	[SmartPart]
	public partial class MyView : UserControl, IMyView 
	{
        private WorkItem parentWorkItem;

        [ServiceDependency]
        public WorkItem ParentWorkItem
        {
            set { parentWorkItem = value; }
        }

		public MyView()
		{
			InitializeComponent();
		}

		#region IMyView Members

		public string Message
		{
			get
			{
				return this.label1.Text;
			}
			set
			{
				this.label1.Text = value;
			}
		}

		#endregion

<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID][@typid='1']">
<xsl:variable name="FormularID" select="@ID"/>
<xsl:variable name="tempFormularName" select="@name"/>
<xsl:variable name="FormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempFormularName"/>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'-'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="'>'"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="substringIn" select="' '"/>
		<xsl:with-param name="substringOut" select="''"/>
	</xsl:call-template>
</xsl:variable>
        private void <xsl:value-of select="$FormularName"/>_Click(object sender, EventArgs e)
        {
			//MessageBox.Show("<xsl:value-of select="$FormularName"/> Clicked.");
			try
			{
				ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem.Browse<xsl:value-of select="$FormularName"/>WorkItem myWorkItem = parentWorkItem.WorkItems.AddNew&lt;ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem.Browse<xsl:value-of select="$FormularName"/>WorkItem&gt;();
				if (myWorkItem.Workspaces == null)
				{
					MessageBox.Show("<xsl:value-of select="$FormularName"/> Workspaces is null!");
					return;
				}
                if (parentWorkItem.State.Count > 0)
                {
					myWorkItem.State["<xsl:value-of select="$FormularName"/>"] = parentWorkItem.State["<xsl:value-of select="$FormularName"/>"];
                    myWorkItem.Run();
                }
			}
			catch (Exception ex)
			{
				MessageBox.Show("Fehler beim erzeugen von <xsl:value-of select="$FormularName"/>: " + ex.Message);
			}
        }
</xsl:for-each>
	}
}
</xsl:template>
</xsl:stylesheet>