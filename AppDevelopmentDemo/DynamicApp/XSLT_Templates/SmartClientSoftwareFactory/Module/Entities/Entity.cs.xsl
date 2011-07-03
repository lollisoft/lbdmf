<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../../exsl.xsl"/>

<xsl:template name="Entity.cs">
<xsl:param name="ApplicationID"/><xsl:param name="ApplicationName"/><xsl:param name="FormularName"/><xsl:param name="FormularID"/>using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;

namespace ShellApplication.Entities
{
	/// &lt;summary&gt;
	/// The Model for data.
	/// &lt;/summary&gt;
	public class <xsl:value-of select="$FormularName"/>
	{
		public static string DisplayMember {
			get 
			{
				string dm = "";
<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			</xsl:when>
			<xsl:when test="@dbtype='String'">
				if (dm == "") dm = "<xsl:value-of select="@name"/>";
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
			</xsl:when>
			<xsl:otherwise>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
				dm += "_";
				return dm;
			}
		}
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
            private int _<xsl:value-of select="@name"/>;
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
            private bool _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
            private float _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
            private int _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
            private string _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
            //private binary _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:otherwise>
			// Unknown typ <xsl:value-of select="@dbtype"/>
            //private _unknown_<xsl:value-of select="@dbtype"/> <xsl:value-of select="@name"/>;
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

		static private int ids = 0;
		private int id = 0;

		/// &lt;summary&gt;
		/// Fires when the <xsl:value-of select="$FormularName"/> data changes.
		/// &lt;/summary&gt;
		public event EventHandler <xsl:value-of select="$FormularName"/>InfoChanged;

		/// &lt;summary&gt;
		/// Constructor
		/// &lt;/summary&gt;<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			/// &lt;param name="<xsl:value-of select="@name"/>"&gt;Description of <xsl:value-of select="$FormularName"/>.&lt;/param&gt;
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
			/// &lt;param name="<xsl:value-of select="@name"/>"&gt;Description of <xsl:value-of select="$FormularName"/>.&lt;/param&gt;
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			/// &lt;param name="_<xsl:value-of select="@name"/>"&gt;Description of <xsl:value-of select="$FormularName"/>.&lt;/param&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			/// &lt;param name="_<xsl:value-of select="@name"/>"&gt;Description of <xsl:value-of select="$FormularName"/>.&lt;/param&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			/// &lt;param name="_<xsl:value-of select="@name"/>"&gt;Description of <xsl:value-of select="$FormularName"/>.&lt;/param&gt;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			/// &lt;param name="_<xsl:value-of select="@name"/>"&gt;Description of <xsl:value-of select="$FormularName"/>.&lt;/param&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
			</xsl:when>
			<xsl:otherwise>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
		public <xsl:value-of select="$FormularName"/>(<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			<xsl:if test="position() != 1">,</xsl:if>int _<xsl:value-of select="@name"/>
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
			<xsl:if test="position() != 1">,</xsl:if>int _<xsl:value-of select="@name"/>
    </xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			<xsl:if test="position() != 1">,</xsl:if>bool _<xsl:value-of select="@name"/>
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			<xsl:if test="position() != 1">,</xsl:if>float _<xsl:value-of select="@name"/>
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			<xsl:if test="position() != 1">,</xsl:if>int _<xsl:value-of select="@name"/>
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			<xsl:if test="position() != 1">,</xsl:if>string _<xsl:value-of select="@name"/>
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
			/*<xsl:if test="position() != 1">,</xsl:if>binary _<xsl:value-of select="@name"/>*/
			</xsl:when>
			<xsl:otherwise>
			/*<xsl:if test="position() != 1">,</xsl:if>unknown _<xsl:value-of select="@name"/>*/
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>)
		{
			id = <xsl:value-of select="$FormularName"/>.ids++;
		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
            this._<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
            this._<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
            this._<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
            this._<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
            this._<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
            //this._<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
			</xsl:when>
			<xsl:otherwise>
            //this._<xsl:value-of select="@name"/> = _<xsl:value-of select="@name"/>;
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
		}

		/// &lt;summary&gt;
		/// The unique id of the <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		public int Id
		{
			get { return id; }
		}

		<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
		/// &lt;summary&gt;
		/// <xsl:value-of select="@name"/> of <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		public int <xsl:value-of select="@name"/>_
		{
			get { return _<xsl:value-of select="@name"/>; }
			set
			{
				_<xsl:value-of select="@name"/> = value;
			}
		}
    </xsl:when>
	<xsl:when test="//lbDMF/columntypes/columntype[@name=$FieldName][@tablename=$TableName][@specialcolumn='1']">
		// Special column <xsl:value-of select="@name"/>
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
		/// &lt;summary&gt;
		/// <xsl:value-of select="@name"/> of <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		public bool <xsl:value-of select="@name"/>_
		{
			get { return _<xsl:value-of select="@name"/>; }
			set
			{
				_<xsl:value-of select="@name"/> = value;
			}
		}
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
		/// &lt;summary&gt;
		/// <xsl:value-of select="@name"/> of <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		public float <xsl:value-of select="@name"/>_
		{
			get { return _<xsl:value-of select="@name"/>; }
			set
			{
				_<xsl:value-of select="@name"/> = value;
			}
		}
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
		/// &lt;summary&gt;
		/// <xsl:value-of select="@name"/> of <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		public int <xsl:value-of select="@name"/>_
		{
			get { return _<xsl:value-of select="@name"/>; }
			set
			{
				_<xsl:value-of select="@name"/> = value;
			}
		}
			</xsl:when>
			<xsl:when test="@dbtype='String'">
		/// &lt;summary&gt;
		/// <xsl:value-of select="@name"/> of <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		public string <xsl:value-of select="@name"/>_
		{
			get { return _<xsl:value-of select="@name"/>; }
			set
			{
				_<xsl:value-of select="@name"/> = value;
			}
		}
			</xsl:when>
			<xsl:when test="@dbtype='Binary'">
		/// &lt;summary&gt;
		/// <xsl:value-of select="@name"/> of <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		//public binary <xsl:value-of select="@name"/>_
		//{
		//	get { return _binary_<xsl:value-of select="@name"/>; }
		//	set
		//	{
		//		_binary_<xsl:value-of select="@name"/> = value;
		//	}
		//}
			</xsl:when>
			<xsl:otherwise>
		/// &lt;summary&gt;
		/// <xsl:value-of select="@name"/> of <xsl:value-of select="$FormularName"/>.
		/// &lt;/summary&gt;
		//public unknown_<xsl:value-of select="@dbtype"/>  <xsl:value-of select="@name"/>_
		//{
		//	get { return unknown_<xsl:value-of select="@dbtype"/>_<xsl:value-of select="@name"/>; }
		//	set
		//	{
		//		unknown_<xsl:value-of select="@dbtype"/>_<xsl:value-of select="@name"/> = value;
		//	}
		//}
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

		/// &lt;summary&gt;
		/// Fires the <xsl:value-of select="$FormularName"/> chnaged event.
		/// &lt;/summary&gt;
		public void Fire<xsl:value-of select="$FormularName"/>InfoChanged()
		{
			if (this.<xsl:value-of select="$FormularName"/>InfoChanged != null)
			{
				this.<xsl:value-of select="$FormularName"/>InfoChanged(this, EventArgs.Empty);
			}
		}

	}
}
</xsl:template>
</xsl:stylesheet>
