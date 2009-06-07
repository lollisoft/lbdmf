<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
<!-- Template to create base class file for fixed database forms -->
<xsl:import href="importUMLClassAsDMFForm.xsl"/>
<xsl:import href="importUMLApplicationTables.xsl"/>
<xsl:import href="createDefaultStoredProcs.xsl"/>

<xsl:import href="XMISettings.xsl"/>

<xsl:output method="text"/>

<!-- ********** Select your database target ********** -->

<!--
<xsl:variable name="DefaultDatabaseSystem" select="'MSSQL'"/>
-->
<xsl:variable name="DefaultDatabaseSystem" select="'PostgreSQL'"/>

<xsl:variable name="TargetDBType"><xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">Sqlite</xsl:if><xsl:if test="$targetdatabase = ' '"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if><xsl:if test="$targetdatabase = ''"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if></xsl:variable>
<xsl:variable name="TargetDBVersion"><xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">1.2.3</xsl:if><xsl:if test="$targetdatabase = ' '">7.4</xsl:if><xsl:if test="$targetdatabase = ''">7.4</xsl:if></xsl:variable>

<!-- ************************************************* -->

	<xsl:template match="text()|@*">
		<xsl:value-of select="."/>
	</xsl:template>
	<xsl:template match="text()|@*"/>

<xsl:template match="packagedElement"> 
<xsl:value-of select="$activity"/></xsl:template>


	<xsl:template match="/">

--
-- SQL script created for <xsl:value-of select="$TargetDBType"/>
--

		<!-- Generate System database definition -->
		<xsl:variable name="AppName" select="//packagedElement[@xmi:type='uml:Class']/xmi:Extension/stereotype[@name='form']/../../../@name"/>
		<xsl:call-template name="createDefaultStoredProcs">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="$AppName"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>	
	
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFForm">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
				<!-- Class <xsl:value-of select="@name"/> of type ENTITY found.
					<xsl:call-template name="importApplicationTable">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
					</xsl:call-template>
				-->	
			</xsl:when>
			</xsl:choose>
		</xsl:for-each>


<!-- Generate Application database model -->
<!--
	<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
		<xsl:choose>
			<xsl:when test="./xmi:Extension/stereotype[@name='form']">
			</xsl:when>
			<xsl:when test="./xmi:Extension/stereotype[@name='entity']">

	<xsl:call-template name="importApplicationTableRelation">
		<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
		<xsl:with-param name="ApplicationName" select="../@name"/>
		<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
		<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
	</xsl:call-template>
	
		</xsl:when>
		</xsl:choose>
	</xsl:for-each>
-->





    <xsl:for-each select="//ownedOperation"><xsl:variable name="function" select="@name"/>
	<xsl:if test="./xmi:Extension/stereotype/@name='validator'">
-- Activity operation for class <xsl:value-of select="../@name"/> in package <xsl:value-of select="../../@name"/> is <xsl:value-of select="@name"/>.
-- Operation is a validator using activity <xsl:value-of select="./xmi:Extension/taggedValue[@tag='validator']/@value"/>
		<xsl:variable name="activity" select="./xmi:Extension/taggedValue[@tag='validator']/@value"/>
		<xsl:variable name="activityID" select="//packagedElement[@xmi:type = 'uml:Activity'][@name = $activity]/@xmi:id"/>
<!--<xsl:apply-templates select="../../packagedElement[@xmi:type = 'uml:Activity'][@name = $function]"/>-->

		<xsl:if test="$activityID=''">-- Activity not found.</xsl:if>
		<xsl:if test="$activityID!=''">-- Activity '<xsl:value-of select="$activity"/>' found.
			<xsl:call-template name="convertActivityTolbDMFActivity"><xsl:with-param name="ID" select="$activityID"/><xsl:with-param name="Name" select="$activity"/></xsl:call-template>
		</xsl:if>
	</xsl:if>
</xsl:for-each>
-- Script ready.
</xsl:template>

<xsl:template name="convertActivityTolbDMFActivity">
    <xsl:param name="ID"/>
    <xsl:param name="Name"/>
-- Generate statemachine for <xsl:value-of select="$ID"/>
-- select "CreateActivityOnMissing"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>');

<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:InitialNode'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateInitialNode"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:DecisionNode'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateDecisionNode"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>');
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateOpaqueAction"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="./body"/>'); 
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>
<xsl:for-each select="//packagedElement[@xmi:id=$ID]/edge">
	<xsl:variable name="edgetype" select="@xmi:type"/>
	<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$edgetype='uml:ControlFlow'">
			<xsl:variable name="expression" select="./guard[@xmi:type='uml:OpaqueExpression']/body"/>
--     CreateControlFlow(activityID, ActivityName, controlflowID, source, target, name, body);	

select "CreateControlFlow"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="./@xmi:id"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="./@source"/>', '<xsl:value-of select="./@target"/>', '<xsl:value-of select="$expression"/>');
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$edgetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>

<xsl:for-each select="//packagedElement[@xmi:id=$ID]/node">
	<xsl:variable name="nodetype" select="@xmi:type"/>
		<xsl:variable name="stereotype" select="./xmi:Extension/stereotype/@name"/>
	<xsl:choose>
		<xsl:when test="$nodetype='uml:DecisionNode'">
			<xsl:variable name="decision" select="./@xmi:id"/>
			<xsl:variable name="incoming" select="./incoming/@xmi:idref"/>
			<xsl:for-each select="./outgoing">
-- Node <xsl:value-of select="$nodetype"/>.
select "CreateDecisionPath"('<xsl:value-of select="$ID"/>', '<xsl:value-of select="$Name"/>', '<xsl:value-of select="$decision"/>', '<xsl:value-of select="./@name"/>', '<xsl:value-of select="$stereotype"/>', '<xsl:value-of select="$incoming"/>', '<xsl:value-of select="./@xmi:idref"/>');
			</xsl:for-each>
		</xsl:when>
		<xsl:when test="$nodetype='uml:OpaqueAction'">
		</xsl:when>
		<xsl:when test="$nodetype='uml:FinalNode'">
		</xsl:when>
		<xsl:otherwise>
-- Nodetype <xsl:value-of select="$nodetype"/> not known.
		</xsl:otherwise>
	</xsl:choose>
</xsl:for-each>

</xsl:template>


	<!--<xsl:template match="XMI.content">
	    <xsl:apply-templates/>
	</xsl:template>-->
</xsl:stylesheet>
