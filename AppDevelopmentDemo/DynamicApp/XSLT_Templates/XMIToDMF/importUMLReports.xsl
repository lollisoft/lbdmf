<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:lbDMF="http:///schemas/lbDMF/1">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2009  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
-->
<xsl:output method="text"/>

<xsl:template name="importDMFReport">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
	<xsl:param name="TargetDatabaseType"/>
	<xsl:param name="TargetDatabaseVersion"/>
	<xsl:param name="TargetReportSystem"/>

<xsl:choose>
	<xsl:when test="$TargetDatabaseType='PostgreSQL'">
					<xsl:call-template name="importDMFReportPostgres">
						<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
						<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
						<xsl:with-param name="TargetReportSystem" select="$TargetReportSystem"/>
					</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='Sqlite'">
					<xsl:call-template name="importDMFReportSqlite">
						<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
						<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
						<xsl:with-param name="TargetReportSystem" select="$TargetReportSystem"/>
					</xsl:call-template>
	</xsl:when>
	<xsl:when test="$TargetDatabaseType='MSSQL'">
					<xsl:call-template name="importDMFReportMSSQL">
						<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
						<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
						<xsl:with-param name="TargetReportSystem" select="$TargetReportSystem"/>
					</xsl:call-template>
	</xsl:when>
	<xsl:otherwise>
-- Error: Target database '<xsl:value-of select="$TargetDatabaseType"/>' not support yet.
	</xsl:otherwise>
</xsl:choose>

</xsl:template>

<xsl:template name="importDMFReportSqlite">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetReportSystem"/>
-- Generate DMF form definition for <xsl:value-of select="$ApplicationName"/> in Sqlite database

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

-- INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select '<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', '<xsl:value-of select="$ToolbarImageName"/>', id, 1 FROM "anwendungen" where name = '<xsl:value-of select="$ApplicationName"/>';
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
INSERT OR IGNORE INTO "report" (parametername, parametervalue, formularid)
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
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>"</xsl:if></xsl:if></xsl:for-each> from <xsl:value-of select="$tablename"/>', id FROM "formulare" WHERE name = '<xsl:value-of select="@name"/>' and anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

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
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = '<xsl:value-of select="@name"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>');

</xsl:if>

</xsl:template>
<xsl:template name="importDMFReportPostgres">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetReportSystem"/>
-- Generate DMF report definition for <xsl:value-of select="$ApplicationName"/> in PostgreSQL database 

<xsl:variable name="tablename"><xsl:call-template name="lookupEntityName">
		<xsl:with-param name="ApplicationID" select="$ApplicationID"/>
		<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
		<xsl:with-param name="FormularID" select="@xmi:id"/>
	</xsl:call-template></xsl:variable>

<xsl:variable name="classname" select="@name"/>
<xsl:variable name="classID" select="@xmi:id"/>
-- select dropreport('<xsl:value-of select="$ApplicationName"/>', '<xsl:value-of select="@name"/>');

<xsl:variable name="ToolbarImageName">
<xsl:if test="./xmi:Extension/taggedValue[@tag='toolbarimage']/@value!=''"><xsl:value-of select="./xmi:Extension/taggedValue[@tag='toolbarimage']/@value"/></xsl:if>
<xsl:if test="./xmi:Extension/taggedValue[@tag='lbDMF:toolbarimagefile']/@value!=''"><xsl:value-of select="./xmi:Extension/taggedValue[@tag='lbDMF:toolbarimagefile']/@value"/></xsl:if>
</xsl:variable>

-- insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', '<xsl:value-of select="$ToolbarImageName"/>', getorcreateapplication('<xsl:value-of select="$ApplicationName"/>'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));
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
delete from report where report_name = 'Report<xsl:value-of select="$tablename"/>';
insert into report (report_name, report_grade, report_source) values('Report<xsl:value-of select="$tablename"/>', 0, '&lt;!DOCTYPE openRPTDef&gt;
&lt;report&gt;
 &lt;title&gt;&lt;/title&gt;
 &lt;name&gt;&lt;/name&gt;
 &lt;description&gt;&lt;/description&gt;
 &lt;size&gt;A4&lt;/size&gt;
 &lt;portrait/&gt;
 &lt;topmargin&gt;100&lt;/topmargin&gt;
 &lt;bottommargin&gt;100&lt;/bottommargin&gt;
 &lt;rightmargin&gt;100&lt;/rightmargin&gt;
 &lt;leftmargin&gt;100&lt;/leftmargin&gt;
 &lt;querysource&gt;
  &lt;name&gt;FormularQuery&lt;/name&gt;
  &lt;sql&gt;select <xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
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
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>, "<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>"</xsl:if></xsl:if></xsl:for-each> from <xsl:value-of select="$tablename"/>
<!--
&lt;? if exists("filter") ?&gt;
   WHERE anwendungid = &lt;? value("filter") ?&gt;
&lt;? endif ?&gt;
-->
order by id&lt;/sql&gt;
 &lt;/querysource&gt;
 &lt;pghead&gt;
  &lt;height&gt;75&lt;/height&gt;


<xsl:variable name="Columns"><xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
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
			<xsl:otherwise>
<xsl:if test="position()=last()"><xsl:value-of select="position()"/></xsl:if>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each></xsl:variable>

<xsl:variable name="ForeignKeys"><xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:if test="$Aggregation='none'"><xsl:if test="@association=''">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>
<xsl:if test="position()=last()"><xsl:value-of select="position()"/></xsl:if>
</xsl:if></xsl:if></xsl:for-each></xsl:variable>

<xsl:variable name="PageWidth" select="533"/> <!-- Inches -->


<xsl:variable name="AllColumns">
<xsl:if test="$ForeignKeys = ''"><xsl:value-of select="$Columns"/></xsl:if>
<xsl:if test="$ForeignKeys != ''"><xsl:value-of select="$Columns + $ForeignKeys"/></xsl:if>
</xsl:variable>

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
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
			<xsl:otherwise>
  &lt;label&gt;
   &lt;rect&gt;
    &lt;x&gt;<xsl:value-of select="5+(position()-1)*($PageWidth div $AllColumns)"/>&lt;/x&gt;
    &lt;y&gt;25&lt;/y&gt;
    &lt;width&gt;100&lt;/width&gt;
    &lt;height&gt;25&lt;/height&gt;
   &lt;/rect&gt;
   &lt;font&gt;
    &lt;face&gt;Helvetica&lt;/face&gt;
    &lt;size&gt;12&lt;/size&gt;
    &lt;weight&gt;normal&lt;/weight&gt;
   &lt;/font&gt;
   &lt;left/&gt;
   &lt;top/&gt;
   &lt;string&gt;<xsl:value-of select="@name"/>&lt;/string&gt;
  &lt;/label&gt;
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:if test="$Aggregation='none'"><xsl:if test="@association=''">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>
  &lt;label&gt;
   &lt;rect&gt;
    &lt;x&gt;<xsl:value-of select="5+(position()-1)*($PageWidth div $AllColumns)"/>&lt;/x&gt;
    &lt;y&gt;45&lt;/y&gt;
    &lt;width&gt;100&lt;/width&gt;
    &lt;height&gt;25&lt;/height&gt;
   &lt;/rect&gt;
   &lt;font&gt;
    &lt;face&gt;Helvetica&lt;/face&gt;
    &lt;size&gt;12&lt;/size&gt;
    &lt;weight&gt;normal&lt;/weight&gt;
   &lt;/font&gt;
   &lt;left/&gt;
   &lt;top/&gt;
   &lt;string&gt;<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>&lt;/string&gt;
  &lt;/label&gt;
</xsl:if></xsl:if></xsl:for-each>

  &lt;line&gt;
   &lt;xstart&gt;0&lt;/xstart&gt;
   &lt;ystart&gt;20&lt;/ystart&gt;
   &lt;xend&gt;625&lt;/xend&gt;
   &lt;yend&gt;20&lt;/yend&gt;
   &lt;weight&gt;2&lt;/weight&gt;
  &lt;/line&gt;
  &lt;line&gt;
   &lt;xstart&gt;0&lt;/xstart&gt;
   &lt;ystart&gt;75&lt;/ystart&gt;
   &lt;xend&gt;625&lt;/xend&gt;
   &lt;yend&gt;75&lt;/yend&gt;
   &lt;weight&gt;2&lt;/weight&gt;
  &lt;/line&gt;
 &lt;/pghead&gt;
 
 &lt;section&gt;
  &lt;name&gt;Formulare&lt;/name&gt;
  &lt;detail&gt;
   &lt;key&gt;
    &lt;query&gt;FormularQuery&lt;/query&gt;
   &lt;/key&gt;
   &lt;height&gt;70&lt;/height&gt;



<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
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
			<xsl:otherwise>
   &lt;field&gt;
    &lt;rect&gt;
     &lt;x&gt;<xsl:value-of select="5+(position()-1)*($PageWidth div $AllColumns)"/>&lt;/x&gt;
     &lt;y&gt;25&lt;/y&gt;
     &lt;width&gt;100&lt;/width&gt;
     &lt;height&gt;20&lt;/height&gt;
    &lt;/rect&gt;
    &lt;font&gt;
     &lt;face&gt;Helvetica&lt;/face&gt;
     &lt;size&gt;10&lt;/size&gt;
     &lt;weight&gt;normal&lt;/weight&gt;
    &lt;/font&gt;
    &lt;left/&gt;
    &lt;top/&gt;
    &lt;data&gt;
     &lt;query&gt;FormularQuery&lt;/query&gt;
     &lt;column&gt;<xsl:value-of select="@name"/>&lt;/column&gt;
    &lt;/data&gt;
   &lt;/field&gt;
			</xsl:otherwise>
		</xsl:choose>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>

<xsl:for-each select="./ownedAttribute[@xmi:type='uml:Property']">
<xsl:variable name="Aggregation" select="@aggregation"/>
<xsl:if test="$Aggregation='none'"><xsl:if test="@association=''">
<xsl:variable name="otherClassID" select="./type/@xmi:idref"/>
   &lt;field&gt;
    &lt;rect&gt;
     &lt;x&gt;<xsl:value-of select="5+(position()-1)*($PageWidth div $AllColumns)"/>&lt;/x&gt;
     &lt;y&gt;45&lt;/y&gt;
     &lt;width&gt;100&lt;/width&gt;
     &lt;height&gt;20&lt;/height&gt;
    &lt;/rect&gt;
    &lt;font&gt;
     &lt;face&gt;Helvetica&lt;/face&gt;
     &lt;size&gt;10&lt;/size&gt;
     &lt;weight&gt;normal&lt;/weight&gt;
    &lt;/font&gt;
    &lt;left/&gt;
    &lt;top/&gt;
    &lt;data&gt;
     &lt;query&gt;FormularQuery&lt;/query&gt;
     &lt;column&gt;<xsl:value-of select="//packagedElement[@xmi:id=$otherClassID]/@name"/>&lt;/column&gt;
    &lt;/data&gt;
   &lt;/field&gt;
</xsl:if></xsl:if></xsl:for-each>
   
   &lt;line&gt;
    &lt;xstart&gt;0&lt;/xstart&gt;
    &lt;ystart&gt;60&lt;/ystart&gt;
    &lt;xend&gt;625&lt;/xend&gt;
    &lt;yend&gt;60&lt;/yend&gt;
    &lt;weight&gt;0&lt;/weight&gt;
   &lt;/line&gt;
  &lt;/detail&gt;
 &lt;/section&gt;
&lt;/report&gt;');



</xsl:template>
<xsl:template name="importDMFReportMSSQL">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetReportSystem"/>
-- Generate DMF form definition for <xsl:value-of select="$ApplicationName"/> in MSSQL database

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
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = '<xsl:value-of select="@name"/>' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>');
</xsl:template>

</xsl:stylesheet>