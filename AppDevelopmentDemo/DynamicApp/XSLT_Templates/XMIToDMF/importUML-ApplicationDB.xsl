<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
<!-- Template to create base class file for fixed database forms -->
<xsl:import href="importUMLClassAsDMFForm.xsl"/>
<xsl:import href="importUMLApplicationTables.xsl"/>
<xsl:import href="createDefaultStoredProcs.xsl"/>

<xsl:output method="text"/>

<!-- ********** Select your database target ********** -->

<xsl:variable name="TargetDBType" select="'Sqlite'"/>
<xsl:variable name="TargetDBVersion" select="'1.2.3'"/>

<!--
<xsl:variable name="TargetDBType" select="'PostgreSQL'"/>
<xsl:variable name="TargetDBVersion" select="'7.4'"/>
-->

<!-- ************************************************* -->

	<xsl:template match="text()|@*">
		<xsl:value-of select="."/>
	</xsl:template>
	<xsl:template match="text()|@*"/>

<xsl:template match="packagedElement"> 
<xsl:value-of select="$activity"/></xsl:template>

	<xsl:template match="/">
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']"><xsl:if test="position()!=1"><!--;--></xsl:if>
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
-- Create table model with template 'importApplicationTable'.
<xsl:if test="position()=1">;--1</xsl:if>
		<xsl:call-template name="importApplicationTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
-- Unknown stereotype '<xsl:value-of select="./xmi:Extension/stereotype/@name"/>' for class <xsl:value-of select="@name"/>.
		<xsl:call-template name="importApplicationTableAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']"><xsl:if test="position()!=1"><!--;--></xsl:if>
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
<xsl:if test="position()=1">;--1</xsl:if>
<!-- For templates above, that can generate primary keys in table definition, this here is obsolete. (As for Sqlite)-->
		<xsl:call-template name="importApplicationTablePrimaryKeys">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
<xsl:if test="position()=1">;--2</xsl:if>
		<xsl:call-template name="importApplicationTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
		
			</xsl:when>
			<xsl:otherwise>
-- Unknown stereotype '<xsl:value-of select="./xmi:Extension/stereotype/@name"/>' for class <xsl:value-of select="@name"/>.
<!--<xsl:if test="position()=1">;</xsl:if>-->
		<xsl:call-template name="importApplicationTableRelationAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
