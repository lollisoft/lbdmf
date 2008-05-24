<xsl:stylesheet version="1.1" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" extension-element-prefixes="exsl">

<!-- Helper to create multible files. -->
<xsl:import href="../include/exsl.xsl"/>

<xsl:import href="../include/lbDMFBaseTemplates.xsl"/>

<!-- UML XMI snippets -->
<xsl:import href="UMLXMISnippets.xsl"/>


<xsl:output method="text" indent="no"/>

<xsl:template match="lbDMF">
Export application code to <xsl:value-of select="$basedir"/>

<xsl:variable name="ApplicationID" select="//lbDMF/@applicationid"/>
<xsl:variable name="OrginalApplicationName" select="//lbDMF/applications/application[@ID=$ApplicationID]/@name"/>
<xsl:variable name="ApplicationName" select="concat(substring-before($OrginalApplicationName, ' '), substring-after($OrginalApplicationName, ' '))"/>


<!-- === UML XMI file ====================================================================== -->

<exsl:document href="{$basedir}/ModelExchange/{$ApplicationName}.xmi" method="text">&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;xmi:XMI xmi:version="2.1" xmlns:uml="http://schema.omg.org/spec/UML/2.1" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1"&gt;
	&lt;xmi:Documentation exporter="gen_DMFToXMI" exporterVersion="1.0"/&gt;
	&lt;uml:Model xmi:type="uml:Model" name="DMFToUML"&gt;
		&lt;packagedElement xmi:type="uml:Package" xmi:id="BOUML_<xsl:value-of select="$ApplicationName"/>" name ="<xsl:value-of select="$OrginalApplicationName"/>"&gt;<xsl:for-each select="formulare/formular[@applicationid=$ApplicationID]">
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
		
		
		&lt;packagedElement xmi:type="uml:Package" xmi:id="BOUML_<xsl:value-of select="$ApplicationName"/>_Entities" name ="<xsl:value-of select="$ApplicationName"/>_Entities"&gt;<xsl:for-each select="dbtables/table">
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
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Bit" name = "boolean"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Float" name = "float"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_Integer" name = "int"/&gt;
		&lt;packagedElement xmi:type="uml:DataType" xmi:id="BOUML_datatype_String" name = "string"/&gt;
	&lt;/uml:Model&gt;
&lt;/xmi:XMI&gt;</exsl:document>
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