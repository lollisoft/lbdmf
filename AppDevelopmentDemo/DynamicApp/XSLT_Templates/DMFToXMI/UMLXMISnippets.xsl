<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<xsl:template name="WriteXMIClass">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
	
<xsl:variable name="tempFormularName" select="$FormName"/>
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
		&lt;packagedElement xmi:type="uml:Class" name="<xsl:value-of select="$FormularName"/>" xmi:id="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" visibility="package" isAbstract="false"&gt;
						&lt;xmi:Extension extender="Bouml"&gt;
							&lt;stereotype name="form"/&gt;
						&lt;/xmi:Extension&gt;

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
<!--
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_ForeignKey"/&gt;
			&lt;/ownedAttribute&gt;
-->
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
		&lt;/packagedElement&gt;
		
<xsl:for-each select="//formularactions/action[@formularid=$FormularID]">
	<xsl:variable name="ActionID" select="@actionid"/>
	<xsl:choose>
		<xsl:when test="//actions/action[@ID=$ActionID]/@typ='1'">
		<!-- A Button press action -->
			<xsl:for-each select="//actionsteps/action[@actionid=$ActionID]">
				<xsl:choose>
					<xsl:when test="@steptyp='1'">
					<!-- A Button press action -->
					</xsl:when>
					<xsl:when test="@steptyp='2'">
					<!-- A SQL query action -->
					</xsl:when>
					<xsl:when test="@steptyp='3'">
					<!-- A open form action -->
					</xsl:when>
					<xsl:when test="@steptyp='4'">
					<!-- A open detail form action -->
<xsl:variable name="tempFormularName" select="//formulare/formular[@ID = $FormularID]/@name"/>
<xsl:variable name="TFormularName">
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

<xsl:variable name="targetForm" select="@what"/>

<xsl:variable name="tempTargetFormularName" select="@what"/>
<xsl:variable name="TTargetFormularName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTargetFormularName"/>
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

<xsl:variable name="targetFormID" select="//lbDMF/formulare/formular[@applicationid=$ApplicationID][@name=$targetForm]/@ID"/>

			&lt;packagedElement xmi:type="uml:Dependency" xmi:id="Action_<xsl:value-of select="@ID"/>" client="<xsl:value-of select="$TFormularName"/>_<xsl:value-of select="$FormularID"/>" supplier="<xsl:value-of select="$TTargetFormularName"/>_<xsl:value-of select="$targetFormID"/>"&gt;
			&lt;/packagedElement&gt;
					
					</xsl:when>
					<xsl:when test="@steptyp='5'">
					<!-- A open master form action -->
					</xsl:when>
				</xsl:choose>
			</xsl:for-each>
		</xsl:when>
	</xsl:choose>
</xsl:for-each>

</xsl:template>

<xsl:template name="WriteXMIClassRelationalActions">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="FormularID"/>
	<xsl:param name="FormName"/>
	
<xsl:variable name="tempFormularName" select="$FormName"/>
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
		&lt;packagedElement xmi:type="uml:Class" name="<xsl:value-of select="$FormularName"/>" xmi:id="<xsl:value-of select="$FormularName"/>_<xsl:value-of select="$FormularID"/>" visibility="package" isAbstract="false"&gt;
						&lt;xmi:Extension extender="Bouml"&gt;
							&lt;stereotype name="form"/&gt;
						&lt;/xmi:Extension&gt;

<xsl:for-each select="//lbDMF/formularfields/formular[@formularid=$FormularID]">
<xsl:variable name="FieldName" select="@name"/> 
<xsl:variable name="TableName" select="@tablename"/>
<xsl:choose>
	<xsl:when test="@isfk='1'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_ForeignKey"/&gt;
			&lt;/ownedAttribute&gt;
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@dbtype='Bit'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Float'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='Integer'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@dbtype='String'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$FormularID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
		&lt;/packagedElement&gt;
</xsl:template>

<xsl:template name="WriteXMIEntity">
	<xsl:param name="ApplicationID"/>
	<xsl:param name="TableID"/>
	<xsl:param name="TableName"/>
	
<xsl:variable name="tempTableName" select="$TableName"/>
<xsl:variable name="TName">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
	<xsl:call-template name="SubstringReplace">
		<xsl:with-param name="stringIn">
			<xsl:value-of select="$tempTableName"/>
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
		&lt;packagedElement xmi:type="uml:Class" name="<xsl:value-of select="$TName"/>" xmi:id="ID_<xsl:value-of select="$TName"/>" visibility="package" isAbstract="false"&gt;
			&lt;xmi:Extension extender="Bouml"&gt;
				&lt;stereotype name="entity"/&gt;
			&lt;/xmi:Extension&gt;

<xsl:for-each select="//dbcolumns/column[@tablename=$TName]">
<xsl:variable name="FieldName" select="@name"/>
<xsl:variable name="TableName" select="@tablename"/>
<xsl:for-each select="//foreignkeys/foreignkey[@pktable=$TName][@pkcolumn=$FieldName]">
			&lt;ownedAttribute xmi:type="uml:Property" 
<!--			name="<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@ID"/>"-->
			name="<xsl:value-of select="@fkcolumn"/>"
			xmi:id="<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" 
			visibility="protected" 
			association="ASSOC_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" aggregation="none"&gt;
				&lt;type xmi:idref="ID_<xsl:value-of select="@fktable"/>"/&gt;
				&lt;lowerValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_LOWER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="*"/&gt;
				&lt;upperValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_UPPER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="*"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="relationship"/&gt;
				&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
</xsl:for-each>
<xsl:for-each select="//foreignkeys/foreignkey[@fktable=$TName][@fkcolumn=$FieldName]">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="@fktable"/>_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@ID"/>" 
			xmi:id="<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@ID"/>" 
			visibility="protected" association="ASSOC_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" 
			aggregation="none"&gt;
				&lt;type xmi:idref="ID_<xsl:value-of select="@pktable"/>"/&gt;
				&lt;lowerValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_LOWER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="1"/&gt;
				&lt;upperValue xmi:type="uml:LiteralString" xmi:id="MULTIPLICITY_UPPER_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@fktable"/>" value="1"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="relationship"/&gt;
				&lt;/xmi:Extension&gt;
			&lt;/ownedAttribute&gt;
</xsl:for-each>
<xsl:choose>
	<xsl:when test="@isfk='1'">
<!--
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_ForeignKey"/&gt;
			&lt;/ownedAttribute&gt;
-->
	</xsl:when>
	<xsl:otherwise>
		<xsl:choose>
			<xsl:when test="@typ='Bit'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bool'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Bit"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='Float'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Float"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='int4'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_Integer"/&gt;
				<xsl:if test="//primarykeys/primarykey[@pktable=$TName][@pkcolumn=$FieldName]">
					&lt;xmi:Extension extender="Bouml"&gt;
						&lt;stereotype name="key"/&gt;
					&lt;/xmi:Extension&gt;
				</xsl:if>
			&lt;/ownedAttribute&gt;
			</xsl:when>
			<xsl:when test="@typ='bpchar'">
			&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$FieldName"/>" xmi:id="<xsl:value-of select="$FieldName"/>_<xsl:value-of select="$TName"/>_<xsl:value-of select="$TableID"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;type xmi:idref="BOUML_datatype_String"/&gt;
			&lt;/ownedAttribute&gt;
			</xsl:when>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

		&lt;/packagedElement&gt;


<xsl:for-each select="//formularfields/formular[@tablename=$TableName]">
		<xsl:if test="position()=1">
			<xsl:variable name="FormID" select="@formularid"/>

<xsl:variable name="tempFormularName" select="//formulare/formular[@ID = $FormID]/@name"/>
<xsl:variable name="TFormularName">
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

			&lt;packagedElement xmi:type="uml:Dependency" xmi:id="FormID_<xsl:value-of select="@ID"/>" client="<xsl:value-of select="$TFormularName"/>_<xsl:value-of select="@formularid"/>" supplier="ID_<xsl:value-of select="//dbtables/table[@name=$TableName]/@name"/>"&gt;
			&lt;/packagedElement&gt;
		</xsl:if>
</xsl:for-each>		
		
</xsl:template>

</xsl:stylesheet>