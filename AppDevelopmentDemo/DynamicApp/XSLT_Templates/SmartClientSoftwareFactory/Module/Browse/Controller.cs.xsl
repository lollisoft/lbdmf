<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="Controller.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Practices.CompositeUI;
using System.Windows.Forms;
using ShellApplication.Entities;

namespace ShellApplication.Browse<xsl:value-of select="$FormularName"/>WorkItem
{
	/// &lt;summary&gt;
	/// <xsl:value-of select="$FormularName"/>Controller used by the views.
	/// &lt;/summary&gt;
	public class <xsl:value-of select="$FormularName"/>Controller : Controller
	{
		/// &lt;summary&gt;
		/// The <xsl:value-of select="$FormularName"/> State will be injected into the view.
		/// &lt;/summary&gt;
		[State("<xsl:value-of select="$FormularName"/>")]
		public List&lt;<xsl:value-of select="$FormularName"/>&gt; <xsl:value-of select="$FormularName"/>
		{
		    get { return (List&lt;<xsl:value-of select="$FormularName"/>&gt;)State["<xsl:value-of select="$FormularName"/>"]; }
		    set
		    {
		        try
		        {
		            if ((value != null) &amp;&amp;
		                (State != null))
		            {
		                State["<xsl:value-of select="$FormularName"/>"] = value;
		            }
		        }
		        catch (Exception ex)
		        {
		            MessageBox.Show(ex.Message + Environment.NewLine + ex.StackTrace);
		        }
		    }
		}

		/// &lt;summary&gt;
		/// The controller is dependent on the Browse<xsl:value-of select="$FormularName"/> WorkItem
		/// and will not run with out it.
		/// &lt;/summary&gt;
		private Browse<xsl:value-of select="$FormularName"/>WorkItem _<xsl:value-of select="$FormularName"/>WorkItem = null;

		[ServiceDependency(Type = typeof(WorkItem))]
		public Browse<xsl:value-of select="$FormularName"/>WorkItem <xsl:value-of select="$FormularName"/>WorkItem
		{
			set { _<xsl:value-of select="$FormularName"/>WorkItem = value; }
		}

		/// &lt;summary&gt;
		/// Loads Mock data.
		/// &lt;/summary&gt;
		public void Populate<xsl:value-of select="$FormularName"/>Data()
		{
			if (<xsl:value-of select="$FormularName"/> == null)
			{
				throw new ArgumentNullException("<xsl:value-of select="$FormularName"/>");
			}
			<xsl:call-template name="Mock">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="EntityID" select="'1'"/>
			</xsl:call-template>
			<xsl:call-template name="Mock">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="EntityID" select="'2'"/>
			</xsl:call-template>
			<xsl:call-template name="Mock">
		<xsl:with-param name="ApplicationID" select="//lbDMF/@applicationid"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularName" select="$FormularName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="EntityID" select="'3'"/>
			</xsl:call-template>

		}

		/// &lt;summary&gt;
		/// Shows the <xsl:value-of select="$FormularName"/> details.
		/// &lt;/summary&gt;
		/// &lt;param name="<xsl:value-of select="$FormularName"/>"&gt;&lt;/param&gt;
		public void Show<xsl:value-of select="$FormularName"/>Details(<xsl:value-of select="$FormularName"/><xsl:value-of select="' '"/><xsl:value-of select="$FormularName"/>)
		{
			// To maintain separation of concerns.
			_<xsl:value-of select="$FormularName"/>WorkItem.Show<xsl:value-of select="$FormularName"/>Details(<xsl:value-of select="$FormularName"/>);
		}
	}
}
</xsl:template>
<xsl:template name="Mock">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/><xsl:param name="EntityID"/>
			<xsl:value-of select="$FormularName"/>.Add(new <xsl:value-of select="$FormularName"/>(<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'"><xsl:if test="position() != 1">,</xsl:if><xsl:value-of select="$EntityID"/></xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']"><xsl:if test="position() != 1">,</xsl:if><xsl:value-of select="$EntityID"/>
    </xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'"><xsl:if test="position() != 1">,</xsl:if>true</xsl:when>
			<xsl:when test="@dbtype='Float'"><xsl:if test="position() != 1">,</xsl:if><xsl:value-of select="$EntityID"/>.0F</xsl:when>
			<xsl:when test="@dbtype='Integer'"><xsl:if test="position() != 1">,</xsl:if><xsl:value-of select="$EntityID"/></xsl:when>
			<xsl:when test="@dbtype='String'"><xsl:if test="position() != 1">,</xsl:if>"Lala <xsl:value-of select="$EntityID"/> <xsl:value-of select="@name"/>"</xsl:when>
			<xsl:when test="@dbtype='Binary'">/*<xsl:if test="position() != 1">,</xsl:if>"Lala <xsl:value-of select="$EntityID"/> <xsl:value-of select="@name"/>"*/</xsl:when>
			<xsl:otherwise>/*<xsl:if test="position() != 1">,</xsl:if>"Lala unknown <xsl:value-of select="$EntityID"/> <xsl:value-of select="@name"/>"*/</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>));
</xsl:template>

</xsl:stylesheet>
