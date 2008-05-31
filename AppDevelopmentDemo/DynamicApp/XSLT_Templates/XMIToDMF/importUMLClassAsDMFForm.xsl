<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
<xsl:output method="text"/>



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
		<xsl:otherwise>-<xsl:value-of select="//packagedElement[@xmi:type='uml:Class'][@xmi:id=$FormularID]/@name"/>-</xsl:otherwise>
</xsl:choose>
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

<xsl:variable name="classname" select="@name"/>
<xsl:variable name="classID" select="@xmi:id"/>
--select "DropFormular"('<xsl:value-of select="$ApplicationName"/>', '<xsl:value-of select="@name"/>');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select '<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', 'style.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';
-- Create query for <xsl:value-of select="$tablename"/> (<xsl:value-of select="@xmi:id"/>)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select <xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="@name=''">
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
<xsl:if test="$Aggregation='none'">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>"</xsl:if></xsl:for-each> from "<xsl:value-of select="$tablename"/>"', id FROM "formulare" WHERE name = '<xsl:value-of select="@name"/>' and anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', '<xsl:value-of select="@name"/>', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', '<xsl:value-of select="@name"/>', 1);

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
<xsl:variable name="datatype" select="//packagedElement[@xmi:id=$datatypeid]/@name"/>
<xsl:if test="$datatype='image'">
INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, '<xsl:value-of select="$datatype"/>');
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
-- insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', 7, '<xsl:value-of select="$parameters"/>');	
-- insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', 7, (select id from action_types where bezeichnung = 'Activity'));
	</xsl:when>
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = '<xsl:value-of select="@name"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>');
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
select "DropFormular"('<xsl:value-of select="$ApplicationName"/>', '<xsl:value-of select="@name"/>');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', 'style.png', GetOrCreateApplication('<xsl:value-of select="$ApplicationName"/>'), 1);

insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select <xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:choose>
	<xsl:when test="@name=''">
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
<xsl:if test="$Aggregation='none'">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>"</xsl:if></xsl:for-each> from "<xsl:value-of select="$tablename"/>" order by "ID"', GetFormularId(GetOrCreateApplication('<xsl:value-of select="$ApplicationName"/>'), '<xsl:value-of select="@name"/>'));
insert into column_types (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', true);

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="datatypeid" select="./type/@xmi:idref"/> 
<xsl:variable name="datatype" select="//packagedElement[@xmi:id=$datatypeid]/@name"/>
<xsl:if test="$datatype='image'">
insert into column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, '<xsl:value-of select="$datatype"/>');
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
insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', 7, '<xsl:value-of select="$parameters"/>');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', 7, (select id from action_types where bezeichnung = 'Activity'));
	</xsl:when>
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
insert into anwendungen_formulare (anwendungid, formularid) values(GetOrCreateApplication('<xsl:value-of select="$ApplicationName"/>'), GetFormularId(GetOrCreateApplication('<xsl:value-of select="$ApplicationName"/>'), '<xsl:value-of select="@name"/>'));

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