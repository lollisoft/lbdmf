<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1">
<xsl:output method="text"/>


<!-- The main importer for a DMF formular -->
<xsl:template name="importDMFForm">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
	<xsl:param name="TargetDatabaseType"/>
	<xsl:param name="TargetDatabaseVersion"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
					<xsl:call-template name="importDMFFormPostgres">
						<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
						<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
					</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
					<xsl:call-template name="importDMFFormSqlite">
						<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
						<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
					</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
					<xsl:call-template name="importDMFFormMSSQL">
						<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
						<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
					</xsl:call-template>
	</xsl:when>
	<xsl:otherwise>
-- Error: Target database '<xsl:value-of select="$TargetDatabaseType"/>' not support yet.
	</xsl:otherwise>
</xsl:choose>

</xsl:template>

<!-- Lookup the table name in case if the formularname - eg the classname is of type form -->
<xsl:template name="lookupEntityName">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FormularID"/>
	<xsl:choose>
		<xsl:when test="./xmi:Extension/stereotype/@name='form'">
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Dependency'][@client=$FormularID]">
			<xsl:variable name="SupplyerClassID" select="@supplier"/>
			<xsl:variable name="SupplierClassStereoType" select="//packagedElement[@xmi:id=$SupplyerClassID]/xmi:Extension/stereotype/@name"/>
			<xsl:if test="$SupplierClassStereoType='entity'">
				<xsl:variable name="DependencyToEntity" select="//packagedElement[@xmi:id=$SupplyerClassID]/@name"/>
				<xsl:value-of select="$DependencyToEntity"/>
			</xsl:if>
		</xsl:for-each>

		</xsl:when>
		<xsl:otherwise><xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FormularID]/@name"/></xsl:otherwise>
</xsl:choose>

	</xsl:template>

<xsl:template name="lookupEntityID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FormularID"/>
<!--
	<xsl:choose>
		<xsl:when test="./xmi:Extension/stereotype/@name='form'">
-->
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Dependency'][@client=$FormularID]">
			<xsl:variable name="SupplyerClassID" select="@supplier"/>
			<xsl:variable name="SupplierClassStereoType" select="//packagedElement[@xmi:id=$SupplyerClassID]/xmi:Extension/stereotype/@name"/>
			<xsl:if test="$SupplierClassStereoType='entity'">
				<xsl:value-of select="$SupplyerClassID"/>
			</xsl:if>
		</xsl:for-each>
<!--
		</xsl:when>
		<xsl:otherwise><xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FormularID]/@name"/></xsl:otherwise>
</xsl:choose>
-->
	</xsl:template>


<xsl:template name="getTableID">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TableName"/>
    <xsl:param name="FieldName"/>
<xsl:value-of select="//ownedAttribute[@xmi:type='uml:Property'][@name=$FieldName]/@association"/>
</xsl:template>


<xsl:template name="buildSqliteVisibleFieldMapping">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FormularID"/>
    <xsl:param name="FieldName"/><xsl:variable name="tableID"><xsl:call-template name="lookupEntityID">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FieldName" select="$FieldName"/>
	</xsl:call-template></xsl:variable><xsl:variable name="association"><xsl:value-of select="//packagedElement[@xmi:id=$tableID]/ownedAttribute[@name=$FieldName]/type[@xmi:type='uml:Class']/@xmi:idref"/></xsl:variable>
<!--
$association = '<xsl:value-of select="$association"/>'
$tableID = '<xsl:value-of select="$tableID"/>'
$FieldName = '<xsl:value-of select="$FieldName"/>'
-->
INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('<xsl:value-of select="//packagedElement[@xmi:id=$tableID]/@name"/>', '<xsl:value-of select="$FieldName"/>', '<xsl:value-of select="//packagedElement[@xmi:id=$association]/@name"/>', '<xsl:value-of select="//packagedElement[@xmi:id=$association]/ownedAttribute/xmi:Extension/stereotype[@name='visible']/../../@name"/>');
</xsl:template>
<xsl:template name="buildPostgreSQLVisibleFieldMapping">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FormularID"/>
    <xsl:param name="FieldName"/><xsl:variable name="tableID"><xsl:call-template name="lookupEntityID">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FieldName" select="$FieldName"/>
	</xsl:call-template></xsl:variable><xsl:variable name="association"><xsl:value-of select="//packagedElement[@xmi:id=$tableID]/ownedAttribute[@name=$FieldName]/type[@xmi:type='uml:Class']/@xmi:idref"/></xsl:variable>
<!--
$association = '<xsl:value-of select="$association"/>'
$tableID = '<xsl:value-of select="$tableID"/>'
$FieldName = '<xsl:value-of select="$FieldName"/>'
-->
INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('<xsl:value-of select="//packagedElement[@xmi:id=$tableID]/@name"/>', '<xsl:value-of select="$FieldName"/>', '<xsl:value-of select="//packagedElement[@xmi:id=$association]/@name"/>', '<xsl:value-of select="//packagedElement[@xmi:id=$association]/ownedAttribute/xmi:Extension/stereotype[@name='visible']/../../@name"/>');
</xsl:template>
<xsl:template name="buildMSSQLVisibleFieldMapping">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FormularID"/>
    <xsl:param name="FieldName"/><xsl:variable name="tableID"><xsl:call-template name="lookupEntityID">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$FormularID"/>
		<xsl:with-param name="FieldName" select="$FieldName"/>
	</xsl:call-template></xsl:variable><xsl:variable name="association"><xsl:value-of select="//packagedElement[@xmi:id=$tableID]/ownedAttribute[@name=$FieldName]/type[@xmi:type='uml:Class']/@xmi:idref"/></xsl:variable>
<!--
$association = '<xsl:value-of select="$association"/>'
$tableID = '<xsl:value-of select="$tableID"/>'
$FieldName = '<xsl:value-of select="$FieldName"/>'
-->
INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('<xsl:value-of select="//packagedElement[@xmi:id=$tableID]/@name"/>', '<xsl:value-of select="$FieldName"/>', '<xsl:value-of select="//packagedElement[@xmi:id=$association]/@name"/>', '<xsl:value-of select="//packagedElement[@xmi:id=$association]/ownedAttribute/xmi:Extension/stereotype[@name='visible']/../../@name"/>');
</xsl:template>

<xsl:template name="importDMFFormSqlite">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
-- Generate DMF form definition for <xsl:value-of select="$ApplicationName"/>

<xsl:variable name="tablename"><xsl:call-template name="lookupEntityName">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="@xmi:id"/>
	</xsl:call-template></xsl:variable>

<xsl:if test="$tablename!=''">

<xsl:variable name="classname" select="@name"/>
<xsl:variable name="classID" select="@xmi:id"/>
--select "DropFormular"('<xsl:value-of select="$ApplicationName"/>', '<xsl:value-of select="@name"/>');

<xsl:variable name="ToolbarImageName">
<xsl:if test="./xmi:Extension/taggedValue[@tag='toolbarimage']/@value!=''"><xsl:value-of select="./xmi:Extension/taggedValue[@tag='toolbarimage']/@value"/></xsl:if>
<xsl:if test="./xmi:Extension/taggedValue[@tag='lbDMF:toolbarimagefile']/@value!=''"><xsl:value-of select="./xmi:Extension/taggedValue[@tag='lbDMF:toolbarimagefile']/@value"/></xsl:if>
</xsl:variable>

INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select '<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', '<xsl:value-of select="$ToolbarImageName"/>', id, 1 FROM "anwendungen" where name = '<xsl:value-of select="$ApplicationName"/>';
<!--
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']/type[@xmi:idref='BOUML_datatype_ForeignKey']">
<xsl:call-template name="buildSqliteVisibleFieldMapping">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="../@name"/>
	</xsl:call-template>
</xsl:for-each>
-->
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="tableID"><xsl:call-template name="lookupEntityID">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="$FieldName"/>
	</xsl:call-template></xsl:variable>
<xsl:variable name="association"><xsl:value-of select="//packagedElement[@xmi:id=$tableID]/ownedAttribute[@name=$FieldName]/type[@xmi:type='uml:Class']/@xmi:idref"/></xsl:variable>
<xsl:if test="$association!=''">
<xsl:call-template name="buildSqliteVisibleFieldMapping">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="@name"/>
	</xsl:call-template>
</xsl:if>
</xsl:for-each>

-- Create query for <xsl:value-of select="$tablename"/> (<xsl:value-of select="@xmi:id"/>)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select <xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="@name=''">
	</xsl:when>
	<xsl:when test="@association!=''">
	</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
			<xsl:otherwise><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:if test="$Aggregation='none'"><xsl:if test="@association=''">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>"</xsl:if></xsl:if></xsl:for-each> from "<xsl:value-of select="$tablename"/>"', id FROM "formulare" WHERE name = '<xsl:value-of select="@name"/>' and anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', '<xsl:value-of select="@name"/>', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', '<xsl:value-of select="@name"/>', 1);

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
<xsl:variable name="datatype" select="//packagedElement[@xmi:id=$datatypeid]/@name"/>
<!-- Any older representation, propably the initial representation for XMI 1.2 import format -->
<xsl:if test="$datatype='image'">
INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', 1, '<xsl:value-of select="$datatype"/>');
</xsl:if>

<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:toolbarimagefile'">
INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', 1, 'toolbarimagefile');
</xsl:if>
<xsl:if test="./xmi:Extension/taggedValue[@tag='lbDMF:toolbarimagefile']/@value!=''">
INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', 1, 'toolbarimagefile');
</xsl:if>
<xsl:if test="./@association != ''">
-- Association from <xsl:value-of select="$classname"/> to <xsl:value-of select="$datatype"/>
<!-- Create the desired formular action based on the selected stereotype -->

<xsl:call-template name="createSqliteFormularActionByProperty">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="Property" select="@xmi:id"/>
		<xsl:with-param name="FromFormularID" select="$classID"/>
		<xsl:with-param name="ToFormularID" select="$datatypeid"/>		
</xsl:call-template>

</xsl:if>
</xsl:for-each>

-- Create operation definitions
<xsl:for-each select="./ownedOperation[@xmi:type='uml:Operation']">
<xsl:choose>
	<xsl:when test="./xmi:Extension/stereotype/@name='lbDMF:codegeneration'">
-- Generate codegeneration operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'

INSERT OR IGNORE INTO "actions" (name, typ, source) VALUES ('<xsl:value-of select="@name"/>', 1, '<xsl:value-of select="./ownedParameter/@name"/>');
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, '', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = '<xsl:value-of select="@name"/>'));
INSERT OR IGNORE INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = '<xsl:value-of select="$classname"/>'), (select id from actions where name = '<xsl:value-of select="@name"/>'), 'evt_<xsl:value-of select="$classname"/>_<xsl:value-of select="@name"/>');

	</xsl:when>
	<xsl:when test="./xmi:Extension/stereotype/@name='lbDMF:test_application_via_lua'">
-- Generate codegeneration operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'

INSERT OR IGNORE INTO "actions" (name, typ, source, stereotype) VALUES ('Test <xsl:value-of select="@name"/> via wxLua', 1, '<xsl:value-of select="./ownedParameter/@name"/>', 'test_application_via_lua');
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate wxLua code', 1, 'gen_wxLuaFixedFormularClasses.xsl', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Test <xsl:value-of select="@name"/> via wxLua'));
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Test application via wxLua', 2, 'name', (select id from action_types where action_handler = 'instanceOflbExecuteAction'), (select id from actions where name = '<xsl:value-of select="@name"/>'));
INSERT OR IGNORE INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = '<xsl:value-of select="$classname"/>'), (select id from actions where name = '<xsl:value-of select="@name"/>'), 'evt_<xsl:value-of select="$classname"/>_<xsl:value-of select="@name"/>');

	</xsl:when>
	<xsl:when test="./xmi:Extension/stereotype/@name='callxslt'">
-- Generate callxslt operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
	</xsl:when>
	<xsl:when test="./xmi:Extension/stereotype/@name='validator'">
-- Generate validator operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
<xsl:variable name="parameters">
	<xsl:for-each select="./ownedParameter">
	<xsl:if test="position()!=1">,</xsl:if>
	<xsl:value-of select="@name"/>
	</xsl:for-each>
</xsl:variable>
-- insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', 7, '<xsl:value-of select="$parameters"/>');	
-- insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', 7, (select id from action_types where bezeichnung = 'Activity'));
	</xsl:when>
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = '<xsl:value-of select="@name"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>');

</xsl:if>

</xsl:template>

<xsl:template name="importDMFFormMSSQL">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
-- Generate DMF form definition for <xsl:value-of select="$ApplicationName"/>

<xsl:variable name="tablename"><xsl:call-template name="lookupEntityName">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="@xmi:id"/>
	</xsl:call-template></xsl:variable>

<xsl:variable name="classname" select="@name"/>
<xsl:variable name="classID" select="@xmi:id"/>
exec "DropFormular"('<xsl:value-of select="$ApplicationName"/>', '<xsl:value-of select="@name"/>');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select '<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', '<xsl:value-of select="./xmi:Extension/taggedValue[@tag='toolbarimage']/@value"/>', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';
<!--
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']/type[@xmi:idref='BOUML_datatype_ForeignKey']">
<xsl:call-template name="buildMSSQLVisibleFieldMapping">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="../@name"/>
	</xsl:call-template>
</xsl:for-each>
-->
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="tableID"><xsl:call-template name="lookupEntityID">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="$FieldName"/>
	</xsl:call-template></xsl:variable>
<xsl:variable name="association"><xsl:value-of select="//packagedElement[@xmi:id=$tableID]/ownedAttribute[@name=$FieldName]/type[@xmi:type='uml:Class']/@xmi:idref"/></xsl:variable>
<xsl:if test="$association!=''">
<xsl:call-template name="buildMSSQLVisibleFieldMapping">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="@name"/>
	</xsl:call-template>
</xsl:if>
</xsl:for-each>

-- Create query for <xsl:value-of select="$tablename"/> (<xsl:value-of select="@xmi:id"/>)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select <xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="@name=''">
	</xsl:when>
	<xsl:when test="@association!=''">
	</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
			<xsl:otherwise><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:if test="$Aggregation='none'"><xsl:if test="@association=''">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>"</xsl:if></xsl:if></xsl:for-each> from "<xsl:value-of select="$tablename"/>"', id FROM "formulare" WHERE name = '<xsl:value-of select="@name"/>' and anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', '<xsl:value-of select="@name"/>', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', '<xsl:value-of select="@name"/>', 1);

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
<xsl:variable name="datatype" select="//packagedElement[@xmi:id=$datatypeid]/@name"/>
<!-- Any older representation, propably the initial representation for XMI 1.2 import format -->
<xsl:if test="$datatype='image'">
INSERT INTO "column_types" (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', 1, '<xsl:value-of select="$datatype"/>');
</xsl:if>

<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:toolbarimagefile'">
INSERT INTO "column_types" (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', 1, 'toolbarimagefile');
</xsl:if>
<xsl:if test="./@association != ''">
-- Association from <xsl:value-of select="$classname"/> to <xsl:value-of select="$datatype"/>
<!-- Create the desired formular action based on the selected stereotype -->

<xsl:call-template name="createMSSQLFormularActionByProperty">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="Property" select="@xmi:id"/>
		<xsl:with-param name="FromFormularID" select="$classID"/>
		<xsl:with-param name="ToFormularID" select="$datatypeid"/>		
</xsl:call-template>

</xsl:if>
</xsl:for-each>

-- Create operation definitions
<xsl:for-each select="./ownedOperation[@xmi:type='uml:Operation']">
<xsl:choose>
	<xsl:when test="./xmi:Extension/stereotype/@name='lbDMF:codegeneration'">
-- Generate codegeneration operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'

INSERT INTO "actions" (name, typ, source) VALUES ('<xsl:value-of select="@name"/>', 1, '<xsl:value-of select="./ownedParameter/@name"/>');
INSERT INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, 'lala', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = '<xsl:value-of select="@name"/>'));
INSERT INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = '<xsl:value-of select="$classname"/>'), (select id from actions where name = '<xsl:value-of select="@name"/>'), 'evt_<xsl:value-of select="$classname"/>_<xsl:value-of select="@name"/>');

	</xsl:when>
	<xsl:when test="./xmi:Extension/stereotype/@name='callxslt'">
-- Generate callxslt operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
	</xsl:when>
	<xsl:when test="./xmi:Extension/stereotype/@name='validator'">
-- Generate validator operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
<xsl:variable name="parameters">
	<xsl:for-each select="./ownedParameter">
	<xsl:if test="position()!=1">,</xsl:if>
	<xsl:value-of select="@name"/>
	</xsl:for-each>
</xsl:variable>
-- insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', 7, '<xsl:value-of select="$parameters"/>');	
-- insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', 7, (select id from action_types where bezeichnung = 'Activity'));
	</xsl:when>
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = '<xsl:value-of select="@name"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>');
</xsl:template>


<xsl:template name="createSqliteFormularActionByProperty">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="Property"/>
    <xsl:param name="FromFormularID"/>
    <xsl:param name="ToFormularID"/>
-- From formular '<xsl:value-of select="$FromFormularID"/>'
-- To   formular '<xsl:value-of select="$ToFormularID"/>'

<xsl:variable name="ActionType" select="./xmi:Extension/stereotype/@name"/>
<xsl:variable name="ActionName" select="//packagedElement[@xmi:type='uml:Association']/memberEnd[@xmi:idref=$Property]/../@name"/>
<xsl:variable name="FromFormName" select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FromFormularID]/@name"/>


-- Create sqlite based action
-- Select action type ActionType: <xsl:value-of select="$ActionType"/>, Property: '<xsl:value-of select="$Property"/>'.


<xsl:choose>
	<xsl:when test="$ActionType='lbDMF:masterdetail_action'">
<!-- Dont use the tagged values for values when profiles are used. BoUML complains about the tagged values thus I should also use the new place -->
<xsl:variable name="visibleField1" select="//lbDMF:masterdetail_action[@base_Element=$Property]/@sourcecolumn"/>
-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('<xsl:value-of select="$Property"/>', 1, '<xsl:value-of select="$visibleField1"/>');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for <xsl:value-of select="$ActionName"/>', 1, '<xsl:value-of select="$ActionName"/>', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField1"/>'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = '<xsl:value-of select="$FromFormName"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>')), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField1"/>'), 'action_master_detail_<xsl:value-of select="$Property"/>');
UPDATE actions set name = '<xsl:value-of select="$ActionName"/>' where name = '<xsl:value-of select="$Property"/>';
	</xsl:when>
	<xsl:when test="$ActionType='lbDMF:detailmaster_action'">
<!-- Dont use the tagged values for values when profiles are used. BoUML complains about the tagged values thus I should also use the new place -->
<xsl:variable name="visibleField" select="lbDMF:detailmaster_action[@base_Element=$Property]/@sourcecolumn"/>
-- Build up a detail master action
INSERT OR IGNORE INTO actions (name, typ, source) values ('<xsl:value-of select="$Property"/>', 1, '<xsl:value-of select="$visibleField"/>');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Detail master action for <xsl:value-of select="$ActionName"/>', 1, '<xsl:value-of select="$ActionName"/>', (select id from action_types where bezeichnung = 'Open master form'), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField"/>'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = '<xsl:value-of select="$FromFormName"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>')), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField"/>'), 'action_master_detail_<xsl:value-of select="$Property"/>');
UPDATE actions set name = '<xsl:value-of select="$ActionName"/>' where name = '<xsl:value-of select="$Property"/>';
	</xsl:when>
</xsl:choose>

</xsl:template>
<xsl:template name="createPostgreSQLFormularActionByProperty">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="Property"/>
    <xsl:param name="FromFormularID"/>
    <xsl:param name="ToFormularID"/>
-- From formular '<xsl:value-of select="$FromFormularID"/>'
-- To   formular '<xsl:value-of select="$ToFormularID"/>'

<xsl:variable name="ActionType" select="./xmi:Extension/stereotype/@name"/>
<xsl:variable name="ActionName" select="//packagedElement[@xmi:type='uml:Association']/memberEnd[@xmi:idref=$Property]/../@name"/>
<xsl:variable name="FromFormName" select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FromFormularID]/@name"/>


-- Create Postgresql based action
-- Select action type ActionType: <xsl:value-of select="$ActionType"/>, Property: <xsl:value-of select="$Property"/>.


<xsl:choose>
	<xsl:when test="$ActionType='lbDMF:masterdetail_action'">
<!-- Dont use the tagged values for values when profiles are used. BoUML complains about the tagged values thus I should also use the new place -->
<xsl:variable name="visibleField" select="//lbDMF:masterdetail_action[@base_Element=$Property]/@sourcecolumn"/>
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('<xsl:value-of select="$Property"/>',  (select id from action_types where bezeichnung = 'Buttonpress'), '<xsl:value-of select="$visibleField"/>');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for <xsl:value-of select="$ActionName"/>', 1, '<xsl:value-of select="$ActionName"/>', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField"/>'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = '<xsl:value-of select="$FromFormName"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>')), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField"/>'), 'action_master_detail_<xsl:value-of select="$Property"/>');
UPDATE actions set name = '<xsl:value-of select="$ActionName"/>' where name = '<xsl:value-of select="$Property"/>';
	</xsl:when>
	<xsl:when test="$ActionType='lbDMF:detailmaster_action'">
<!-- Dont use the tagged values for values when profiles are used. BoUML complains about the tagged values thus I should also use the new place -->
<xsl:variable name="STELTProperty">STELT_<xsl:value-of select="$Property"/></xsl:variable>
-- <xsl:value-of select="$STELTProperty"/>
<xsl:variable name="visibleField" select="//lbDMF:detailmaster_action[@xmi:id=$STELTProperty]/@sourcecolumn"/>
-- Build up a detail master action
INSERT INTO actions (name, typ, source) values ('<xsl:value-of select="$Property"/>', (select id from action_types where bezeichnung = 'Buttonpress'), '<xsl:value-of select="$visibleField"/>');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Detail master action for <xsl:value-of select="$ActionName"/>', 1, '<xsl:value-of select="$ActionName"/>', (select id from action_types where bezeichnung = 'Open master form'), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField"/>'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = '<xsl:value-of select="$FromFormName"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>')), (select id from actions where name = '<xsl:value-of select="$Property"/>' and source = '<xsl:value-of select="$visibleField"/>'), 'action_master_detail_<xsl:value-of select="$Property"/>');
UPDATE actions set name = '<xsl:value-of select="$ActionName"/>' where name = '<xsl:value-of select="$Property"/>';
	</xsl:when>
</xsl:choose>

</xsl:template>
<xsl:template name="createMSSQLFormularActionByProperty">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="Property"/>
    <xsl:param name="FromFormularID"/>
    <xsl:param name="ToFormularID"/>
<xsl:variable name="IsMasterDetail"><xsl:value-of select="//lbDMF:masterdetail_action[@base_Element=$Property]/@base_Element"/></xsl:variable>
<xsl:variable name="IsDetailMaster"><xsl:value-of select="//lbDMF:detailmaster_action[@base_Element=$Property]/@base_Element"/></xsl:variable>
-- Select action type IsMasterDetail: <xsl:value-of select="$IsMasterDetail"/>, IsDetailMaster: <xsl:value-of select="$IsDetailMaster"/>

<xsl:choose>
	<xsl:when test="$ActionType='lbDMF:masterdetail_action'">
-- Build up a master detail action
<!-- Dont use the tagged values for values when profiles are used. BoUML complains about the tagged values thus I should also use the new place -->
<xsl:variable name="STELTProperty">STELT_<xsl:value-of select="$Property"/></xsl:variable>
-- <xsl:value-of select="$STELTProperty"/>
<xsl:variable name="visibleField" select="//lbDMF:masterdetail_action[@xmi:id=$STELTProperty]/@sourcecolumn"/>
insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', 1, '<xsl:value-of select="./@xmi:id"/>');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = '<xsl:value-of select="@name"/>' and source = '<xsl:value-of select="./@xmi:id"/>'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = '<xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FromFormularID]/@name"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>')), (select id from actions where name = '<xsl:value-of select="@name"/>' and source = '<xsl:value-of select="./@xmi:id"/>'), 'action_master_detail_<xsl:value-of select="$Property"/>');

update actions set source = '<xsl:value-of select="$visibleField"/>' where source = '<xsl:value-of select="./@xmi:id"/>';

	</xsl:when>
	<xsl:when test="$ActionType='lbDMF:detailmaster_action'">
-- Build up a detail master action
<!-- Dont use the tagged values for values when profiles are used. BoUML complains about the tagged values thus I should also use the new place -->
<xsl:variable name="STELTProperty">STELT_<xsl:value-of select="$Property"/></xsl:variable>
-- <xsl:value-of select="$STELTProperty"/>
<xsl:variable name="visibleField" select="//lbDMF:detailmaster_action[@xmi:id=$STELTProperty]/@sourcecolumn"/>
insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', 1, '<xsl:value-of select="./@xmi:id"/>');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = '<xsl:value-of select="@name"/>' and source = '<xsl:value-of select="./@xmi:id"/>'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = '<xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FromFormularID]/@name"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>')), (select id from actions where name = '<xsl:value-of select="@name"/>' and source = '<xsl:value-of select="./@xmi:id"/>'), 'action_master_detail_<xsl:value-of select="$Property"/>');

update actions set source = '<xsl:value-of select="$visibleField"/>' where source = '<xsl:value-of select="./@xmi:id"/>';

	</xsl:when>
</xsl:choose>

</xsl:template>

<xsl:template name="lookupVisibleField">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="FromFormularID"/>
<!-- Get the entity name by calling existing template -->
<xsl:variable name="EntityName"><xsl:call-template name="lookupEntityName">
    <xsl:with-param name="ApplicationID" select="$ApplicationID"/>
    <xsl:with-param name="ApplicationName" select="$ApplicationName"/>
    <xsl:with-param name="FormularID" select="$FromFormularID"/>
</xsl:call-template></xsl:variable>
<xsl:variable name="FormID" select="//packagedElement[@xmi:type='uml:Class'][@name=$EntityName]/@xmi:id"/>
<xsl:variable name="EntityID" select="//packagedElement[@xmi:type='uml:Dependency'][@client=$FormID]/@supplier"/>
<xsl:value-of select="//packagedElement[@xmi:id=$EntityID]/ownedAttribute[@xmi:type='uml:Property']/xmi:Extension/stereotype[@name='visible']/../../@name"/>
</xsl:template>

<xsl:template name="importDMFFormPostgres">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
-- Generate DMF form definition for <xsl:value-of select="$ApplicationName"/>

<xsl:variable name="tablename"><xsl:call-template name="lookupEntityName">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="@xmi:id"/>
	</xsl:call-template></xsl:variable>

<xsl:variable name="classname" select="@name"/>
<xsl:variable name="classID" select="@xmi:id"/>
select dropformular('<xsl:value-of select="$ApplicationName"/>', '<xsl:value-of select="@name"/>');

<xsl:variable name="ToolbarImageName">
<xsl:if test="./xmi:Extension/taggedValue[@tag='toolbarimage']/@value!=''"><xsl:value-of select="./xmi:Extension/taggedValue[@tag='toolbarimage']/@value"/></xsl:if>
<xsl:if test="./xmi:Extension/taggedValue[@tag='lbDMF:toolbarimagefile']/@value!=''"><xsl:value-of select="./xmi:Extension/taggedValue[@tag='lbDMF:toolbarimagefile']/@value"/></xsl:if>
</xsl:variable>

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', '<xsl:value-of select="$ToolbarImageName"/>', getorcreateapplication('<xsl:value-of select="$ApplicationName"/>'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));
<!--
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']/type[@xmi:idref='BOUML_datatype_ForeignKey']">
<xsl:call-template name="buildPostgreSQLVisibleFieldMapping">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="../@name"/>
	</xsl:call-template>
</xsl:for-each>
-->
<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']"><xsl:variable name="FieldName" select="@name"/><xsl:variable name="tableID"><xsl:call-template name="lookupEntityID">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="$FieldName"/>
	</xsl:call-template></xsl:variable>
<xsl:variable name="association"><xsl:value-of select="//packagedElement[@xmi:id=$tableID]/ownedAttribute[@name=$FieldName]/type[@xmi:type='uml:Class']/@xmi:idref"/></xsl:variable>
<xsl:if test="$association!=''">
<xsl:call-template name="buildPostgreSQLVisibleFieldMapping">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="$classID"/>
		<xsl:with-param name="FieldName" select="@name"/>
	</xsl:call-template>
</xsl:if>
</xsl:for-each>

insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select <xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="@name=''">
	</xsl:when>
	<xsl:when test="@association!=''">
	</xsl:when>
	<xsl:otherwise>
		<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
		<xsl:variable name="datatype" select="//packagedElement[@xmi.id=$datatypeid]/@name"/>
		<xsl:choose>
			<xsl:when test="$datatype='bigstring'"></xsl:when>
			<xsl:when test="$datatype='image'"></xsl:when>
			<xsl:otherwise><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:if test="$Aggregation='none'"><xsl:if test="@association=''">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>"</xsl:if></xsl:if></xsl:for-each> from "<xsl:value-of select="$tablename"/>"', getformularid(getorcreateapplication('<xsl:value-of select="$ApplicationName"/>'), '<xsl:value-of select="@name"/>'));
insert into column_types (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', true);

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
<xsl:variable name="datatype" select="//packagedElement[@xmi:id=$datatypeid]/@name"/>
<xsl:if test="$datatype='image'">
insert into column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, '<xsl:value-of select="$datatype"/>');
</xsl:if>
<xsl:if test="./xmi:Extension/stereotype/@name='lbDMF:toolbarimagefile'">
insert into column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, 'toolbarimagefile');
</xsl:if>
<xsl:if test="./@association != ''">
-- Association from <xsl:value-of select="$classname"/> to <xsl:value-of select="$datatype"/>
<!-- Create the desired formular action based on the selected stereotype -->

<xsl:call-template name="createPostgreSQLFormularActionByProperty">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="Property" select="@xmi:id"/>
		<xsl:with-param name="FromFormularID" select="$classID"/>
		<xsl:with-param name="ToFormularID" select="$datatypeid"/>		
</xsl:call-template>

</xsl:if>
</xsl:for-each>
-- Create operation definitions
<xsl:for-each select="./ownedOperation[@xmi:type='uml:Operation']">
<xsl:choose>
	<xsl:when test="./xmi:Extension/stereotype/@name='callxslt'">
-- Generate callxslt operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
	</xsl:when>
	<xsl:when test="./xmi:Extension/stereotype/@name='validator'">
-- Generate validator operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
<xsl:variable name="parameters">
	<xsl:for-each select="./ownedParameter">
	<xsl:if test="position()!=1">,</xsl:if>
	<xsl:value-of select="@name"/>
	</xsl:for-each>
</xsl:variable>
insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', (select id from action_types where bezeichnung = 'FormValidator'), '<xsl:value-of select="$parameters"/>');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', (select id from action_types where bezeichnung = 'FormValidator'), (select id from action_types where bezeichnung = 'Activity'));
	</xsl:when>
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('<xsl:value-of select="$ApplicationName"/>'), getformularid(getorcreateapplication('<xsl:value-of select="$ApplicationName"/>'), '<xsl:value-of select="@name"/>'));

</xsl:template>




  <xsl:template name="genQueryForeignKeyColumns">
    <xsl:param name="id"/>
    <xsl:param name="package"/>
	<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property'][@association='none']">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id='otherClassID']/@name"/>"</xsl:for-each>
  </xsl:template>


	<!--<xsl:template match="XMI.content">
	    <xsl:apply-templates/>
	</xsl:template>-->
</xsl:stylesheet>
