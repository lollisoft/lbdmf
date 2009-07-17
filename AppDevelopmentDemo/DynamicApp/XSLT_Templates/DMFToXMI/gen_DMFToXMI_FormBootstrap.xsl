<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">

<!-- Helper to create multible files. -->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>
<xsl:import href="XMISettings.xsl"/>
<!-- UML XMI snippets -->
<xsl:import href="UMLXMISnippets.xsl"/>


<xsl:output method="text" indent="no"/>

<xsl:template match="/"><xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName">
<xsl:if test="concat(substring-before($OrginalApplicationName, ' '), substring-after($OrginalApplicationName, ' ')) = ''"><xsl:value-of select="$OrginalApplicationName"/></xsl:if>
<xsl:if test="concat(substring-before($OrginalApplicationName, ' '), substring-after($OrginalApplicationName, ' ')) != ''"><xsl:value-of select="concat(substring-before($OrginalApplicationName, ' '), substring-after($OrginalApplicationName, ' '))"/></xsl:if>
</xsl:variable>

<!-- XSLSettings.xsl should define this variable to either no or yes. -->
<!--<xsl:variable name="stream_output" select="'yes'"/>-->

<xsl:if test="$stream_output='no'">
Export application code to <xsl:value-of select="$basedir"/>
Have Application ID <xsl:value-of select="$ApplicationID"/>
Have Application name <xsl:value-of select="$ApplicationName"/>
Have Application name <xsl:value-of select="$OrginalApplicationName"/>

<!-- === UML XMI file ====================================================================== -->

<exsl:document href="{$basedir}/ModelExchange/{$ApplicationName}.xmi" method="text"><xsl:call-template name="WriteXMIDocument">
<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
<xsl:with-param name="OrginalApplicationName" select="$OrginalApplicationName"/>
</xsl:call-template>
</exsl:document>
</xsl:if>

<xsl:if test="$stream_output='yes'">
<xsl:call-template name="WriteXMIDocument">
<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
<xsl:with-param name="OrginalApplicationName" select="$OrginalApplicationName"/>
</xsl:call-template>
</xsl:if>
</xsl:template>

<xsl:template name="WriteXMIDocument">
	<xsl:param name="ApplicationName"/>
	<xsl:param name="OrginalApplicationName"/>
&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;xmi:XMI xmi:version="2.1" xmlns:uml="http://schema.omg.org/spec/UML/2.1" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1"&gt;
	&lt;xmi:Documentation exporter="gen_DMFToXMI" exporterVersion="1.0"/&gt;
	&lt;uml:Model xmi:type="uml:Model" xmi:id="ID_BOUML_<xsl:value-of select="$ApplicationName"/>" name="DMFToUML"&gt;
		&lt;packagedElement xmi:type="uml:Package" xmi:id="BOUML_<xsl:value-of select="$ApplicationName"/>" name ="<xsl:value-of select="$OrginalApplicationName"/>"&gt;<xsl:for-each select="//lbDMF/formulare/formular[@applicationid=$ApplicationID]">
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


<xsl:call-template name="WriteXMIClass">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName"/>
</xsl:call-template>
</xsl:for-each>
		&lt;/packagedElement&gt;

		&lt;packagedElement xmi:type="uml:Package" xmi:id="BOUML_<xsl:value-of select="$ApplicationName"/>_GeneratedForms" name ="<xsl:value-of select="$OrginalApplicationName"/>_GeneratedForms"&gt;<xsl:for-each select="//lbDMF/dbtables/table">
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


<xsl:call-template name="WriteXMIClass_Bootstrap">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName"/>
</xsl:call-template>
</xsl:for-each>
		&lt;/packagedElement&gt;
		
		
		&lt;packagedElement xmi:type="uml:Package" xmi:id="BOUML_<xsl:value-of select="$ApplicationName"/>_Entities" name ="<xsl:value-of select="$ApplicationName"/>_Entities"&gt;<xsl:for-each select="//lbDMF/dbtables/table">
<xsl:variable name="tempTableName" select="@name"/>
<xsl:variable name="TableName">
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

<xsl:call-template name="WriteXMIEntity">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="TableID" select="@ID"/>
<xsl:with-param name="TableName" select="$TableName"/>
</xsl:call-template>
</xsl:for-each>


<xsl:for-each select="//foreignkeys/foreignkey">
			&lt;packagedElement xmi:type="uml:Association" xmi:id="ASSOC_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@ID"/>" visibility="protected"&gt;
				&lt;memberEnd xmi:idref="<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>_<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>"/&gt;
				&lt;memberEnd xmi:idref="<xsl:value-of select="@fktable"/>_<xsl:value-of select="@fkcolumn"/>_<xsl:value-of select="@pktable"/>_<xsl:value-of select="@pkcolumn"/>"/&gt;
			&lt;/packagedElement&gt;
</xsl:for-each>
		&lt;/packagedElement&gt;

<!-- Based on the new profile capabilities of BoUML here I should add profile I support with this template. -->

		&lt;packagedElement xmi:type="uml:Profile" xmi:id="lbDMF_Profile" name ="lbDMF" metamodelReference="MMR_lbDMF_Profile">
			&lt;xmi:Extension extender="gen_DMFToXMI"&gt;
				&lt;stereotype name="profile"/&gt;
				&lt;taggedValue tag="metamodelReference" value="http://schema.omg.org/spec/UML/2.1/uml.xml"/&gt;
				&lt;taggedValue tag="metaclassreference" value=""/&gt;
			&lt;/xmi:Extension&gt;
			&lt;packageImport xmi:type="uml:PackageImport" xmi:id="MMR_lbDMF_Profile"&gt;
				&lt;importedPackage xmi:type="uml:Model" href="http://schema.omg.org/spec/UML/2.1/uml.xml#1"/&gt;
			&lt;/packageImport&gt;

			<xsl:call-template name="createStereotype1">
				<xsl:with-param name="StereotypeName" select="'masterdetail_action'"/>
				<xsl:with-param name="ApplyableTo" select="'Relation'"/>
				<xsl:with-param name="Comment" select="'Defines that a relation is a master detail action. The action is as of ´master form opens a detail form´.'"/>
				<xsl:with-param name="Attr1" select="'sourcecolumn'"/>
				<xsl:with-param name="AttrTyp1" select="'String'"/>
			</xsl:call-template>
			
			<xsl:call-template name="createStereotype">
				<xsl:with-param name="StereotypeName" select="'fk'"/>
				<xsl:with-param name="ApplyableTo" select="'Attribute'"/>
				<xsl:with-param name="Comment" select="'Defines that an attribute is a foreign key.'"/>
			</xsl:call-template>
			
			<xsl:call-template name="createStereotype">
				<xsl:with-param name="StereotypeName" select="'pk'"/>
				<xsl:with-param name="ApplyableTo" select="'Attribute'"/>
				<xsl:with-param name="Comment" select="'Defines that an attribute is a primary key.'"/>
			</xsl:call-template>
			
			<xsl:call-template name="createStereotype1">
				<xsl:with-param name="StereotypeName" select="'detailmaster_action'"/>
				<xsl:with-param name="ApplyableTo" select="'Relation'"/>
				<xsl:with-param name="Comment" select="'Defines that a relation is a detail master action. The action is as of ´detail form opens a master form´.'"/>
				<xsl:with-param name="Attr1" select="'sourcecolumn'"/>
				<xsl:with-param name="AttrTyp1" select="'String'"/>
			</xsl:call-template>
			
			<xsl:call-template name="createStereotype3">
				<xsl:with-param name="StereotypeName" select="'relationship'"/>
				<xsl:with-param name="ApplyableTo" select="'Relation'"/>
				<xsl:with-param name="Comment" select="'This stereotype is to specify an association to be a relation.'"/>
				<xsl:with-param name="Attr1" select="'sourcecolumn'"/>
				<xsl:with-param name="AttrTyp1" select="'String'"/>
				<xsl:with-param name="Attr2" select="'table'"/>
				<xsl:with-param name="AttrTyp2" select="'String'"/>
				<xsl:with-param name="Attr3" select="'order'"/>
				<xsl:with-param name="AttrTyp3" select="'Integer'"/>
			</xsl:call-template>

			<xsl:call-template name="createStereotype">
				<xsl:with-param name="StereotypeName" select="'codegeneration'"/>
				<xsl:with-param name="ApplyableTo" select="'Operation'"/>
				<xsl:with-param name="Comment" select="'This stereotype is to specify an association to be a relation.'"/>
			</xsl:call-template>
			
			<xsl:call-template name="createStereotype">
				<xsl:with-param name="StereotypeName" select="'toolbarimagefile'"/>
				<xsl:with-param name="ApplyableTo" select="'Attribute'"/>
				<xsl:with-param name="Comment" select="'This stereotype is to specify an attribute to be a special image selector control'"/>
			</xsl:call-template>
			
			<xsl:call-template name="createStereotype">
				<xsl:with-param name="StereotypeName" select="'test_application_via_lua'"/>
				<xsl:with-param name="ApplyableTo" select="'Operation'"/>
				<xsl:with-param name="Comment" select="'This stereotype is to specify an operation to execute the application generated as wxLua script'"/>
			</xsl:call-template>			
		&lt;/packagedElement&gt;

		
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Bit" name = "boolean"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Float" name = "float"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Integer" name = "int"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_String" name = "string"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Datetime" name = "datetime"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Text" name = "text"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_ForeignKey" name = "int"/&gt;
		
	&lt;/uml:Model&gt;

<!-- Based on the new profile capabilities of BoUML here I should add the stereotype hints for the masterdetail and detailmaster actions. -->

<xsl:for-each select="//formulare/formular[@applicationid=$ApplicationID]">
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

<xsl:call-template name="WriteXMIClassRelationalActionStereotype">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="FormularID" select="@ID"/>
<xsl:with-param name="FormName" select="$FormularName"/>
</xsl:call-template>
</xsl:for-each>

<xsl:for-each select="//dbtables/table">
<xsl:variable name="tempTableName" select="@name"/>
<xsl:variable name="TableName">
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

<xsl:call-template name="WriteXMIEntityRelationStereotype">
<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
<xsl:with-param name="EntityID" select="@ID"/>
<xsl:with-param name="EntityName" select="$TableName"/>
</xsl:call-template>
</xsl:for-each>
&lt;/xmi:XMI&gt;</xsl:template>



<xsl:template name="createStereotype">
	<xsl:param name="StereotypeName"/>
	<xsl:param name="ApplyableTo"/>
	<xsl:param name="Comment"/>
			&lt;packagedElement xmi:type="uml:Stereotype" name="<xsl:value-of select="$StereotypeName"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_ID" visibility="package" isAbstract="false" &gt;
				&lt;ownedComment xmi:type="uml:Comment" xmi:id="COMMENT_<xsl:value-of select="$StereotypeName"/>" body="<xsl:value-of select="$Comment"/>"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="stereotype"/&gt;
					&lt;taggedValue tag="stereotypeSetParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeCheckParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeApplyOn" value="<xsl:value-of select="$ApplyableTo"/>"/&gt;
					&lt;taggedValue tag="stereotypeSet" value=""/&gt;
					&lt;taggedValue tag="stereotypeExtension" value="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
					&lt;taggedValue tag="stereotypeCheck" value=""/&gt;
				&lt;/xmi:Extension&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="base_Element" xmi:id="BASE_<xsl:value-of select="$StereotypeName"/>_ID" association="EXT_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
					&lt;type xmi:type="uml:Class" href="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
				&lt;/ownedAttribute&gt;
			&lt;/packagedElement&gt;
			&lt;packagedElement xmi:type="uml:Extension" name="A_Element_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXT_<xsl:value-of select="$StereotypeName"/>_ID" memberEnd="BASE_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
				&lt;ownedEnd xmi:type="uml:ExtensionEnd" name="extension_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXTEND_<xsl:value-of select="$StereotypeName"/>_ID" type="<xsl:value-of select="$StereotypeName"/>_ID" aggregation="composite"/&gt;
			&lt;/packagedElement&gt;
</xsl:template>


<xsl:template name="createStereotype1">
	<xsl:param name="StereotypeName"/>
	<xsl:param name="ApplyableTo"/>
	<xsl:param name="Comment"/>
	<xsl:param name="Attr1"/>
	<xsl:param name="AttrTyp1"/>
			&lt;packagedElement xmi:type="uml:Stereotype" name="<xsl:value-of select="$StereotypeName"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_ID" visibility="package" isAbstract="false" &gt;
				&lt;ownedComment xmi:type="uml:Comment" xmi:id="COMMENT_<xsl:value-of select="$StereotypeName"/>" body="<xsl:value-of select="$Comment"/>"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="stereotype"/&gt;
					&lt;taggedValue tag="stereotypeSetParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeCheckParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeApplyOn" value="<xsl:value-of select="$ApplyableTo"/>"/&gt;
					&lt;taggedValue tag="stereotypeSet" value=""/&gt;
					&lt;taggedValue tag="stereotypeExtension" value="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
					&lt;taggedValue tag="stereotypeCheck" value=""/&gt;
				&lt;/xmi:Extension&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$Attr1"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_Attr1_ID" visibility="private"&gt;
					&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#<xsl:value-of select="$AttrTyp1"/>"/&gt;
				&lt;/ownedAttribute&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="base_Element" xmi:id="BASE_<xsl:value-of select="$StereotypeName"/>_ID" association="EXT_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
					&lt;type xmi:type="uml:Class" href="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
				&lt;/ownedAttribute&gt;
			&lt;/packagedElement&gt;
			&lt;packagedElement xmi:type="uml:Extension" name="A_Element_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXT_<xsl:value-of select="$StereotypeName"/>_ID" memberEnd="BASE_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
				&lt;ownedEnd xmi:type="uml:ExtensionEnd" name="extension_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXTEND_<xsl:value-of select="$StereotypeName"/>_ID" type="<xsl:value-of select="$StereotypeName"/>_ID" aggregation="composite"/&gt;
			&lt;/packagedElement&gt;
</xsl:template>


<xsl:template name="createStereotype2">
	<xsl:param name="StereotypeName"/>
	<xsl:param name="ApplyableTo"/>
	<xsl:param name="Comment"/>
	<xsl:param name="Attr1"/>
	<xsl:param name="AttrTyp1"/>
	<xsl:param name="Attr2"/>
	<xsl:param name="AttrTyp2"/>
			&lt;packagedElement xmi:type="uml:Stereotype" name="<xsl:value-of select="$StereotypeName"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_ID" visibility="package" isAbstract="false" &gt;
				&lt;ownedComment xmi:type="uml:Comment" xmi:id="COMMENT_<xsl:value-of select="$StereotypeName"/>" body="<xsl:value-of select="$Comment"/>"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="stereotype"/&gt;
					&lt;taggedValue tag="stereotypeSetParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeCheckParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeApplyOn" value="<xsl:value-of select="$ApplyableTo"/>"/&gt;
					&lt;taggedValue tag="stereotypeSet" value=""/&gt;
					&lt;taggedValue tag="stereotypeExtension" value="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
					&lt;taggedValue tag="stereotypeCheck" value=""/&gt;
				&lt;/xmi:Extension&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$Attr1"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_Attr1_ID" visibility="private"&gt;
					&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#<xsl:value-of select="$AttrTyp1"/>"/&gt;
				&lt;/ownedAttribute&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$Attr2"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_Attr2_ID" visibility="private"&gt;
					&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#<xsl:value-of select="$AttrTyp2"/>"/&gt;
				&lt;/ownedAttribute&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="base_Element" xmi:id="BASE_<xsl:value-of select="$StereotypeName"/>_ID" association="EXT_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
					&lt;type xmi:type="uml:Class" href="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
				&lt;/ownedAttribute&gt;
			&lt;/packagedElement&gt;
			&lt;packagedElement xmi:type="uml:Extension" name="A_Element_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXT_<xsl:value-of select="$StereotypeName"/>_ID" memberEnd="BASE_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
				&lt;ownedEnd xmi:type="uml:ExtensionEnd" name="extension_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXTEND_<xsl:value-of select="$StereotypeName"/>_ID" type="<xsl:value-of select="$StereotypeName"/>_ID" aggregation="composite"/&gt;
			&lt;/packagedElement&gt;
</xsl:template>



<xsl:template name="createStereotype3">
	<xsl:param name="StereotypeName"/>
	<xsl:param name="ApplyableTo"/>
	<xsl:param name="Comment"/>
	<xsl:param name="Attr1"/>
	<xsl:param name="AttrTyp1"/>
	<xsl:param name="Attr2"/>
	<xsl:param name="AttrTyp2"/>
	<xsl:param name="Attr3"/>
	<xsl:param name="AttrTyp3"/>
			&lt;packagedElement xmi:type="uml:Stereotype" name="<xsl:value-of select="$StereotypeName"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_ID" visibility="package" isAbstract="false" &gt;
				&lt;ownedComment xmi:type="uml:Comment" xmi:id="COMMENT_<xsl:value-of select="$StereotypeName"/>" body="<xsl:value-of select="$Comment"/>"/&gt;
				&lt;xmi:Extension extender="Bouml"&gt;
					&lt;stereotype name="stereotype"/&gt;
					&lt;taggedValue tag="stereotypeSetParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeCheckParameters" value=""/&gt;
					&lt;taggedValue tag="stereotypeApplyOn" value="<xsl:value-of select="$ApplyableTo"/>"/&gt;
					&lt;taggedValue tag="stereotypeSet" value=""/&gt;
					&lt;taggedValue tag="stereotypeExtension" value="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
					&lt;taggedValue tag="stereotypeCheck" value=""/&gt;
				&lt;/xmi:Extension&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$Attr1"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_Attr1_ID" visibility="private"&gt;
					&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#<xsl:value-of select="$AttrTyp1"/>"/&gt;
				&lt;/ownedAttribute&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$Attr2"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_Attr2_ID" visibility="private"&gt;
					&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#<xsl:value-of select="$AttrTyp2"/>"/&gt;
				&lt;/ownedAttribute&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="<xsl:value-of select="$Attr3"/>" xmi:id="<xsl:value-of select="$StereotypeName"/>_Attr3_ID" visibility="private"&gt;
					&lt;type xmi:type="uml:PrimitiveType" href="http://schema.omg.org/spec/UML/2.1/uml.xml#<xsl:value-of select="$AttrTyp3"/>"/&gt;
				&lt;/ownedAttribute&gt;
				&lt;ownedAttribute xmi:type="uml:Property" name="base_Element" xmi:id="BASE_<xsl:value-of select="$StereotypeName"/>_ID" association="EXT_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
					&lt;type xmi:type="uml:Class" href="http://schema.omg.org/spec/UML/2.1/uml.xml#Element"/&gt;
				&lt;/ownedAttribute&gt;
			&lt;/packagedElement&gt;
			&lt;packagedElement xmi:type="uml:Extension" name="A_Element_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXT_<xsl:value-of select="$StereotypeName"/>_ID" memberEnd="BASE_<xsl:value-of select="$StereotypeName"/>_ID"&gt;
				&lt;ownedEnd xmi:type="uml:ExtensionEnd" name="extension_<xsl:value-of select="$StereotypeName"/>" xmi:id="EXTEND_<xsl:value-of select="$StereotypeName"/>_ID" type="<xsl:value-of select="$StereotypeName"/>_ID" aggregation="composite"/&gt;
			&lt;/packagedElement&gt;
</xsl:template>


<!-- here is the template that does the replacement -->
<xsl:template name="SubstringReplace">
	<xsl:param name="stringIn"/>
	<xsl:param name="substringIn"/>
	<xsl:param name="substringOut"/>
	<xsl:choose>
		<xsl:when test="contains($stringIn,$substringIn)">
			<xsl:value-of select="concat(substring-before($stringIn,$substringIn),$substringOut)"/>
			<xsl:call-template name="SubstringReplace">
				<xsl:with-param name="stringIn" select="substring-after($stringIn,$substringIn)"/>
				<xsl:with-param name="substringIn" select="$substringIn"/>
				<xsl:with-param name="substringOut" select="$substringOut"/>
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$stringIn"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>


</xsl:stylesheet>