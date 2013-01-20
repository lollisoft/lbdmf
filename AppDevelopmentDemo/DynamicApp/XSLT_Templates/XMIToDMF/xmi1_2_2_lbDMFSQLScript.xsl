<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:UML="org.omg.xmi.namespace.UML" exclude-result-prefixes="UML">
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
            Ginsterweg 4
            
            65760 Eschborn (germany)
-->
<xsl:import href="XMISettings.xsl"/>
<xsl:import href="createDefaultStoredProcs.xsl"/>

<xsl:output method="text" indent="no"/>

<!-- Stylesheet parameters that will overwrite those given from the XMISettings.xsl file. -->
<xsl:param name="XSLDatabaseBackendSystem"/>
<xsl:param name="XSLDatabaseBackendApplication"/>
<xsl:param name="overwriteDatabase"/>

<xsl:variable name="targetdatabase"><xsl:if test="XSLDatabaseBackendSystem=''"><xsl:value-of select="$settingsfile_targetdatabase"/></xsl:if><xsl:if test="XSLDatabaseBackendSystem!=''"><xsl:value-of select="$XSLDatabaseBackendSystem"/></xsl:if></xsl:variable>

<!-- ********** Select your database target ********** -->

<!--
<xsl:variable name="DefaultDatabaseSystem" select="'MSSQL'"/>
-->
<xsl:variable name="DefaultDatabaseSystem" select="'Sqlite'"/>


<xsl:variable name="TargetDBType">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = 'PostgreSQL'">PostgreSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'MSSQL'">MSSQL</xsl:if>
	<xsl:if test="$targetdatabase = 'Sqlite'">Sqlite</xsl:if>
	<xsl:if test="$targetdatabase = ' '"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
	<xsl:if test="$targetdatabase = ''"><xsl:value-of select="$DefaultDatabaseSystem"/></xsl:if>
</xsl:variable>
<xsl:variable name="TargetDBVersion">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">1.2.3</xsl:if>
	<xsl:if test="$targetdatabase = ' '">7.4</xsl:if>
	<xsl:if test="$targetdatabase = ''">7.4</xsl:if>
</xsl:variable>

<!-- ************************************************* -->


  <xsl:template match="text()|@*">
    <xsl:value-of select="."/>
  </xsl:template>
  <xsl:template match="text()|@*"/>

  <xsl:variable name="derivedTagId" select="//UML:TagDefinition[@name='derived']/@xmi.id"/>

  <xsl:template name="XMI1_2_Root">
    <xsl:for-each select="XMI.content/UML:Model">
      <xsl:call-template name="XMI1_2_Model"/>
    </xsl:for-each>
    <!--xsl:for-each select="UML:Package|UML:Subsystem">
      <xsl:call-template name="XMI1.2_Package_Subsystem"/>
    </xsl:for-each-->
  </xsl:template>

  <xsl:template name="XMI1_2_Model">
    <xsl:variable name="modelID" select="@xmi.id"/>
    <xsl:variable name="packagename" select="concat(@name, UML:ModelElement.name)"/>
	
    <xsl:element name="package">
      <xsl:attribute name="name">
        <xsl:value-of select="concat(@name, UML:ModelElement.name)"/>
      </xsl:attribute>
      <xsl:attribute name="id">
        <xsl:call-template name="XMI1_2_getID"/>
      </xsl:attribute>
      <xsl:apply-templates select="UML:Namespace.ownedElement/UML:Class"/>
    </xsl:element>
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
-- Execute model genAssociations for <xsl:value-of select="@name"/>
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="genAssociations">
          <xsl:with-param name="classID" select="$classID"/>
          <xsl:with-param name="package" select="$packagename"/>
        </xsl:call-template>
      </xsl:for-each>
  </xsl:template>

  <xsl:template match="UML:Package|UML:Subsystem">
    <xsl:variable name="packageID" select="@xmi.id"/>
    <xsl:variable name="name" select="concat(@name, UML:ModelElement.name)"/>
-- Creating a database script for targetdatabase='<xsl:value-of select="$targetdatabase"/>' TargetDBType='<xsl:value-of select="$TargetDBType"/>'
<xsl:if test="$TargetDBType = 'PostgreSQL'">
		<!-- Generate System database definition -->
		<xsl:variable name="AppName"><xsl:value-of select="@name"/></xsl:variable>
		
-- Application is <xsl:value-of select="@name"/>.

		<xsl:call-template name="createDefaultStoredProcs">
			<xsl:with-param name="ApplicationID" select="@xmi.id"/>
			<xsl:with-param name="ApplicationName" select="@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>	

</xsl:if>
<xsl:if test="$TargetDBType = 'Sqlite'">
</xsl:if>
	
	
-- Package: <xsl:value-of select="@name"/>
-- Skip rewrite
<xsl:variable name="applicationname" select="@name"/>

<xsl:if test="$TargetDBType = 'Sqlite'">
INSERT OR IGNORE INTO "anwendungen" ("name", "titel", "modulename", "functor", "interface") values('<xsl:value-of select="$applicationname"/>', 'Application <xsl:value-of select="$applicationname"/>', 'lbDynApp', 'instanceOfApplication', 'lb_I_Application');

INSERT OR IGNORE INTO "users" (userid, passwort, lastapp) SELECT 'user', 'TestUser', id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$applicationname"/>';
UPDATE "users" set lastapp = (select id from "anwendungen" where name = '<xsl:value-of select="$applicationname"/>');
INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT id, lastapp FROM "users" WHERE "userid" = 'user';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$applicationname"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'dbpass', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$applicationname"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', '<xsl:value-of select="$applicationname"/>', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$applicationname"/>';
</xsl:if>
<xsl:if test="$TargetDBType = 'PostgreSQL'">
select GetOrCreateApplication('<xsl:value-of select="@name"/>');
</xsl:if>
    <xsl:element name="package">
      <xsl:attribute name="name">
        <xsl:value-of select="@name"/>
      </xsl:attribute>
    <xsl:variable name="packagename" select="@name"/>
-- Apply class templates for package <xsl:value-of select="@name"/>	  
      <xsl:apply-templates select="UML:Namespace.ownedElement/UML:Class"/>

      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
-- Execute in package genAssociations for <xsl:value-of select="$packagename"/>
        <xsl:call-template name="genAssociations">
          <xsl:with-param name="classID" select="$classID"/>
          <xsl:with-param name="package" select="$packagename"/>
        </xsl:call-template>
      </xsl:for-each>

    </xsl:element>
  </xsl:template>

  <xsl:template match="UML:Class">
    <!-- ****************** CLASS ********************* -->
    <xsl:variable name="classID" select="@xmi.id"/>
    <xsl:element name="class">
-- Class is <xsl:value-of select="@name"/>
<xsl:variable name="classname" select="@name"/>
<xsl:variable name="applicationname" select="../../@name"/>

-- Initialize formular definition
<xsl:if test="$TargetDBType = 'Sqlite'">
--select "DropFormular"('<xsl:value-of select="$applicationname"/>', '<xsl:value-of select="@name"/>');

--INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', 'style.png', GetOrCreateApplication('<xsl:value-of select="$applicationname"/>'), 1);
INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select '<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', '<xsl:value-of select="./UML:ModelElement.taggedValue[@tag='toolbarimage']/@value"/>', id, 1 FROM "anwendungen" where name = '<xsl:value-of select="$applicationname"/>';

-- Cleanup
DELETE FROM "formular_parameters" where formularid = (select id from "formulare" where name = '<xsl:value-of select="$classname"/>' and anwendungid in (select id from "anwendungen" where name = '<xsl:value-of select="$applicationname"/>'));

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) values('query', 'select <xsl:for-each select="UML:Classifier.feature/UML:Attribute">
<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:choose>
<xsl:when test="$datatype='bigstring'"></xsl:when>
<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
<xsl:call-template name="genQueryForeignKeyColumns">
<xsl:with-param name="id" select="$classID"/>
<xsl:with-param name="package" select="../../@name"/>
</xsl:call-template><xsl:for-each select="UML:Classifier.feature/UML:Attribute">
<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:choose>
<xsl:when test="$datatype='bigstring'"><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:when>
<xsl:when test="$datatype='image'"><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:when>
<xsl:otherwise></xsl:otherwise>
</xsl:choose>
</xsl:for-each> from "<xsl:value-of select="@name"/>" order by "ID"', (select id from "formulare" where name = '<xsl:value-of select="$classname"/>' and anwendungid in (select id from "anwendungen" where name = '<xsl:value-of select="$applicationname"/>')));
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', 1);

<xsl:for-each select="UML:Classifier.feature/UML:Attribute">

<!--
<UML:StructuralFeature.type>
	<UML:DataType xmi.idref="BOUML_datatype_1"/>
</UML:StructuralFeature.type>
-->

<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:if test="$datatype='image'">
INSERT OR IGNORE INTO column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', 1, 'image');
</xsl:if>
</xsl:for-each>

<xsl:for-each select="UML:Classifier.feature/UML:Operation">

<xsl:choose>
	<xsl:when test="./UML:ModelElement.stereotype/UML:Stereotype/@name='callxslt'">
-- Generate callxslt operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
	
	
	</xsl:when>
	<xsl:when test="./UML:ModelElement.stereotype/UML:Stereotype/@name='validator'">
-- Generate validator operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'

<xsl:variable name="parameters" select="./UML:BehavioralFeature.parameter/@name"/>

INSERT OR IGNORE INTO "action_types" (bezeichnung) values ('Validator');

INSERT OR IGNORE INTO "actions" (name, typ, source) values ('<xsl:value-of select="@name"/>', (select id from action_types where bezeichnung = 'Validator'), '<xsl:value-of select="$parameters"/>');	

INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', 7, (select id from action_types where bezeichnung = 'Activity'));

	</xsl:when>
	<xsl:otherwise>
-- Unknown action type '<xsl:value-of select="./UML:ModelElement.stereotype/UML:Stereotype/@name='validator'"/>'
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>


INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) values(
(select id from "anwendungen" where name = '<xsl:value-of select="$applicationname"/>'), 
(select id from "formulare" where anwendungid in (select id from "anwendungen" where name = '<xsl:value-of select="$applicationname"/>') and name = '<xsl:value-of select="@name"/>'));
</xsl:if>

<xsl:if test="$TargetDBType = 'PostgreSQL'">

select DropFormular('<xsl:value-of select="../../@name"/>', '<xsl:value-of select="@name"/>');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', 'style.png', GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), 1);



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select <xsl:for-each select="UML:Classifier.feature/UML:Attribute">
<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:choose>
<xsl:when test="$datatype='bigstring'"></xsl:when>
<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
<xsl:call-template name="genQueryForeignKeyColumns">
<xsl:with-param name="id" select="$classID"/>
<xsl:with-param name="package" select="../../@name"/>
</xsl:call-template><xsl:for-each select="UML:Classifier.feature/UML:Attribute">
<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:choose>
<xsl:when test="$datatype='bigstring'"><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:when>
<xsl:when test="$datatype='image'"><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:when>
<xsl:otherwise></xsl:otherwise>
</xsl:choose>
</xsl:for-each> from "<xsl:value-of select="@name"/>" order by "ID"', (select id from "formulare" where anwendungid in (select id from "anwendungen" where name = '<xsl:value-of select="../../@name"/>') and name = '<xsl:value-of select="@name"/>'));
insert into column_types (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', true);

<xsl:for-each select="UML:Classifier.feature/UML:Attribute">

<!--
<UML:StructuralFeature.type>
	<UML:DataType xmi.idref="BOUML_datatype_1"/>
</UML:StructuralFeature.type>
-->

<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:if test="$datatype='image'">
insert into column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, 'image');
</xsl:if>
<xsl:if test="$datatype='bigstring'">
insert into column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, 'bigstring');
</xsl:if>
</xsl:for-each>

<xsl:for-each select="UML:Classifier.feature/UML:Operation">

<xsl:choose>
	<xsl:when test="./UML:ModelElement.stereotype/UML:Stereotype/@name='callxslt'">
-- Generate callxslt operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
	
	
	</xsl:when>
	<xsl:when test="./UML:ModelElement.stereotype/UML:Stereotype/@name='validator'">
-- Generate validator operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'

<xsl:variable name="parameters" select="./UML:BehavioralFeature.parameter/@name"/>

INSERT OR IGNORE INTO "action_types" (bezeichnung) values ('Validator');

insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', (select id from action_types where bezeichnung = 'Validator'), '<xsl:value-of select="$parameters"/>');	

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', 7, (select id from action_types where bezeichnung = 'Activity'));

	</xsl:when>
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>


insert into anwendungen_formulare (anwendungid, formularid) values(GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), GetFormularId(GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), '<xsl:value-of select="@name"/>'));
  </xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">

select "DropFormular"('<xsl:value-of select="../../@name"/>', '<xsl:value-of select="@name"/>');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="@name"/> verwalten', 'manage<xsl:value-of select="@name"/>', 'Edit data of <xsl:value-of select="@name"/>', 'style.png', GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), 1);



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select <xsl:for-each select="UML:Classifier.feature/UML:Attribute">
<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:choose>
<xsl:when test="$datatype='bigstring'"></xsl:when>
<xsl:when test="$datatype='image'"></xsl:when>
<xsl:otherwise><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:otherwise>
</xsl:choose>
</xsl:for-each>
<xsl:call-template name="genQueryForeignKeyColumns">
<xsl:with-param name="id" select="$classID"/>
<xsl:with-param name="package" select="../../@name"/>
</xsl:call-template><xsl:for-each select="UML:Classifier.feature/UML:Attribute">
<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:choose>
<xsl:when test="$datatype='bigstring'"><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:when>
<xsl:when test="$datatype='image'"><xsl:if test="position()!=1">, </xsl:if>"<xsl:value-of select="@name"/>"</xsl:when>
<xsl:otherwise></xsl:otherwise>
</xsl:choose>
</xsl:for-each> from "<xsl:value-of select="@name"/>" order by "ID"', (select id from "formulare" where anwendungid in (select id from "anwendungen" where name = '<xsl:value-of select="../../@name"/>') and name = '<xsl:value-of select="@name"/>'));
insert into column_types (name, tablename, ro) values ('ID', '<xsl:value-of select="@name"/>', 1);

<xsl:for-each select="UML:Classifier.feature/UML:Attribute">

<!--
<UML:StructuralFeature.type>
	<UML:DataType xmi.idref="BOUML_datatype_1"/>
</UML:StructuralFeature.type>
-->

<xsl:variable name="datatypeid" select="UML:StructuralFeature.type/UML:DataType/@xmi.idref"/> 
<xsl:variable name="datatype" select="//UML:DataType[@xmi.id=$datatypeid]/@name"/>
<xsl:if test="$datatype='image'">
insert into column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, 'image');
</xsl:if>
<xsl:if test="$datatype='bigstring'">
insert into column_types (name, tablename, specialcolumn, controltype) values ('<xsl:value-of select="@name"/>', '<xsl:value-of select="$classname"/>', true, 'bigstring');
</xsl:if>
</xsl:for-each>

<xsl:for-each select="UML:Classifier.feature/UML:Operation">

<xsl:choose>
	<xsl:when test="./UML:ModelElement.stereotype/UML:Stereotype/@name='callxslt'">
-- Generate callxslt operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'
	
	
	</xsl:when>
	<xsl:when test="./UML:ModelElement.stereotype/UML:Stereotype/@name='validator'">
-- Generate validator operation '<xsl:value-of select="@name"/>' for '<xsl:value-of select="$classname"/>'

<xsl:variable name="parameters" select="./UML:BehavioralFeature.parameter/@name"/>

insert into "action_types" (bezeichnung) values ('Validator');

insert into actions (name, typ, source) values ('<xsl:value-of select="@name"/>', (select id from action_types where bezeichnung = 'Validator'), '<xsl:value-of select="$parameters"/>');	

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for <xsl:value-of select="@name"/>', 1, '<xsl:value-of select="@name"/>', 7, (select id from action_types where bezeichnung = 'Activity'));

	</xsl:when>
	<xsl:otherwise>
	</xsl:otherwise>
</xsl:choose>

</xsl:for-each>


insert into anwendungen_formulare (anwendungid, formularid) values(GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), GetFormularId(GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), '<xsl:value-of select="@name"/>'));
  </xsl:if>
    </xsl:element>
  </xsl:template>

  <xsl:template name="convertTypes_DBTypes">
    <xsl:param name="typename"/>
    <xsl:choose>
      <xsl:when test="$typename='int'">INTEGER</xsl:when>
      <xsl:when test="$typename='float'">DECIMAL</xsl:when>
      <xsl:when test="$typename='string'">CHAR(100)</xsl:when>
      <xsl:when test="$typename='bigstring'">bytea</xsl:when>
      <xsl:when test="$typename='image'">bytea</xsl:when>
    </xsl:choose>

  </xsl:template>

  <xsl:template name="genAssociations">
    <xsl:param name="classID"/>
    <xsl:param name="package"/>

-- 	genAssociations called.

    <xsl:call-template name="associationsForClass_12">
      <xsl:with-param name="id" select="$classID"/>
      <xsl:with-param name="package" select="$package"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template name="genQueryForeignKeyColumns">
    <xsl:param name="id"/>
    <xsl:param name="package"/>
<xsl:if test="$TargetDBType = 'Sqlite'">
    <!-- UML1.4: -->
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $id]">
      <!-- Choose only association ends where navigable is true. -->
      <xsl:variable name="aggregation" select="../../@aggregation"/>
      <xsl:variable name="thisEnd" select="../.."/>
      <xsl:variable name="thisEndId" select="$thisEnd/@xmi.id"/>
      <xsl:variable name="thisEndType" select="$thisEnd/@type"/>
      <xsl:variable name="thisClassName" select="//UML:Class[@xmi.id=$thisEndType]/@name"/>
      <xsl:variable name="otherEnd" select="../../../UML:AssociationEnd[@type != $thisEndType]"/>
      <xsl:variable name="otherEndType" select="../../../UML:AssociationEnd[@type != $thisEndType]/@type"/>
      <xsl:variable name="otherEndId" select="$otherEnd/@type"/>
      <xsl:variable name="otherClassID" select="../../../UML:AssociationEnd[@type=$otherEndId]/UML:AssociationEnd.participant/@xmi.idref"/>
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/><xsl:if test="$aggregation='none'">
<xsl:variable name="assocname" select="../../@name"/>
<!--<xsl:if test="../../../UML:AssociationEnd/UML:ModelElement.stereotype/UML:Stereotype/@name='masterdetail_action'">-->, "<xsl:value-of select="$otherClassName"/><xsl:value-of select="$assocname"/>" <!--</xsl:if>-->
</xsl:if>
</xsl:for-each>
</xsl:if>
<xsl:if test="$TargetDBType = 'PostgreSQL'">
    <!-- UML1.4: -->
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $id]">
      <!-- Choose only association ends where navigable is true. -->
      <xsl:variable name="thisEnd" select="../.."/>
      <xsl:variable name="thisEndId" select="$thisEnd/@xmi.id"/>
      <xsl:variable name="thisEndType" select="$thisEnd/@type"/>
      <xsl:variable name="thisClassName" select="//UML:Class[@xmi.id=$thisEndType]/@name"/>
      <xsl:variable name="otherEnd" select="../../../UML:AssociationEnd[@type != $thisEndType]"/>
      <xsl:variable name="otherEndType" select="../../../UML:AssociationEnd[@type != $thisEndType]/@type"/>
      <xsl:variable name="otherEndId" select="$otherEnd/@type"/>
      <xsl:variable name="otherClassID" select="../../../UML:AssociationEnd[@type=$otherEndId]/UML:AssociationEnd.participant/@xmi.idref"/>
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/><xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='aggregate'">
<xsl:variable name="assocname" select="../../@name"/>
<!--<xsl:if test="../../../UML:AssociationEnd/UML:ModelElement.stereotype/UML:Stereotype/@name='masterdetail_action'">-->, "<xsl:value-of select="$otherClassName"/><xsl:value-of select="$assocname"/>" <!--</xsl:if>-->
</xsl:if>
</xsl:for-each>
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
    <!-- UML1.4: -->
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $id]">
      <!-- Choose only association ends where navigable is true. -->
      <xsl:variable name="thisEnd" select="../.."/>
      <xsl:variable name="thisEndId" select="$thisEnd/@xmi.id"/>
      <xsl:variable name="thisEndType" select="$thisEnd/@type"/>
      <xsl:variable name="thisClassName" select="//UML:Class[@xmi.id=$thisEndType]/@name"/>
      <xsl:variable name="otherEnd" select="../../../UML:AssociationEnd[@type != $thisEndType]"/>
      <xsl:variable name="otherEndType" select="../../../UML:AssociationEnd[@type != $thisEndType]/@type"/>
      <xsl:variable name="otherEndId" select="$otherEnd/@type"/>
      <xsl:variable name="otherClassID" select="../../../UML:AssociationEnd[@type=$otherEndId]/UML:AssociationEnd.participant/@xmi.idref"/>
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/><xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='aggregate'">
<xsl:variable name="assocname" select="../../@name"/>
<!--<xsl:if test="../../../UML:AssociationEnd/UML:ModelElement.stereotype/UML:Stereotype/@name='masterdetail_action'">-->, "<xsl:value-of select="$otherClassName"/><xsl:value-of select="$assocname"/>" <!--</xsl:if>-->
</xsl:if>
</xsl:for-each>
</xsl:if>
  </xsl:template>

  <xsl:template name="associationsForClass_12">
    <xsl:param name="id"/>
    <xsl:param name="package"/>    
    <!-- UML1.4: -->
-- associationsForClass_12 called.
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $id]">
      <!-- Choose only association ends where navigable is true. -->
      <xsl:variable name="thisEnd" select="../.."/>
      <xsl:variable name="thisEndId" select="$thisEnd/@xmi.id"/>
      <xsl:variable name="thisEndType" select="$thisEnd/@type"/>
      <xsl:variable name="thisClassName" select="//UML:Class[@xmi.id=$thisEndType]/@name"/>
      <xsl:variable name="otherEnd" select="../../../UML:AssociationEnd[@type != $thisEndType]"/>
      <xsl:variable name="otherEndType" select="../../../UML:AssociationEnd[@type != $thisEndType]/@type"/>
      <xsl:variable name="otherEndId" select="$otherEnd/@type"/>
      <xsl:variable name="otherClassID" select="../../../UML:AssociationEnd[@type=$otherEndId]/UML:AssociationEnd.participant/@xmi.idref"/>
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/>

-- Have an association <xsl:value-of select="$thisClassName"/> -&gt; <xsl:value-of select="$otherClassName"/>

<xsl:variable name="assocname" select="../../@name"/>
	  
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='aggregate'">
<xsl:variable name="assocVisibleName" select="substring-after(substring-before(../../../../@name, ')'), '(')"/>
-- Visible name is <xsl:value-of select="$assocVisibleName"/>
<xsl:if test="$assocVisibleName!=''">
<xsl:if test="$TargetDBType = 'PostgreSQL'">
insert into foreignkey_visibledata_mapping (fkname, fktable, pkname, pktable) values ('<xsl:value-of select="$otherClassName"/><xsl:value-of select="$assocname"/>', '<xsl:value-of select="$thisClassName"/>', '<xsl:value-of select="$assocVisibleName"/>', '<xsl:value-of select="$otherClassName"/>');
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
insert into foreignkey_visibledata_mapping (fkname, fktable, pkname, pktable) values ('<xsl:value-of select="$otherClassName"/><xsl:value-of select="$assocname"/>', '<xsl:value-of select="$thisClassName"/>', '<xsl:value-of select="$assocVisibleName"/>', '<xsl:value-of select="$otherClassName"/>');
</xsl:if>
<xsl:if test="$TargetDBType = 'Sqlite'">
INSERT OR IGNORE INTO foreignkey_visibledata_mapping (fkname, fktable, pkname, pktable) values ('<xsl:value-of select="$otherClassName"/><xsl:value-of select="$assocname"/>', '<xsl:value-of select="$thisClassName"/>', '<xsl:value-of select="$assocVisibleName"/>', '<xsl:value-of select="$otherClassName"/>');
</xsl:if>
</xsl:if>
</xsl:if>

<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='none'">
<xsl:if test="../../../UML:AssociationEnd/UML:ModelElement.stereotype/UML:Stereotype/@name='masterdetail_action'">
-- Association <xsl:value-of select="$thisClassName"/> -&gt; <xsl:value-of select="$otherClassName"/>
<xsl:variable name="assocname2" select="../../../../@name"/>
<xsl:variable name="assocname1" select="substring-after(substring-before($assocname2, ')'), '(')"/>

-- ActionID from assocname2 = <xsl:value-of select="$assocname2"/> converted is <xsl:value-of select="$assocname1"/>

<xsl:if test="$TargetDBType = 'Sqlite'">
delete from formular_actions where formular IN 
	(select id from "formulare" where anwendungid IN
		(select id from "anwendungen" where name = '<xsl:value-of select="$package"/>') and 
		name = '<xsl:value-of select="$thisClassName"/>');
delete from action_steps where actionid IN 
	(select ID from actions where name = '<xsl:value-of select="$assocname1"/>_<xsl:value-of select="$otherClassName"/>');
delete from action_parameters where actionid IN 
	(select ID from actions where name = '<xsl:value-of select="$assocname1"/>_<xsl:value-of select="$otherClassName"/>');
delete from actions where name = '<xsl:value-of select="$assocname1"/>_<xsl:value-of select="$otherClassName"/>';
</xsl:if>

<xsl:if test="$assocname1=''">
insert into actions (name, typ, source, target)
values ('<xsl:value-of select="$otherClassName"/>', 1, 'ID', 0);
</xsl:if>
<xsl:if test="$assocname1!=''">
insert into actions (name, typ, source, target)
values ('<xsl:value-of select="$assocname1"/>_<xsl:value-of select="$otherClassName"/>', 1, '<xsl:value-of select="$assocname1"/>', 0);
</xsl:if>
<xsl:if test="$TargetDBType = 'PostgreSQL'">
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'open <xsl:value-of select="$otherClassName"/>', 1, '<xsl:value-of select="$otherClassName"/>', 4, 
currval('actions_id_seq')); 

insert into formular_actions (formular, action, event) values (GetFormularId(GetOrCreateApplication('<xsl:value-of select="$package"/>'), '<xsl:value-of select="$thisClassName"/>'), currval('actions_id_seq'), 'evt_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>');
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'open <xsl:value-of select="$otherClassName"/>', 1, '<xsl:value-of select="$otherClassName"/>', 4, currval('actions_id_seq')); 

insert into formular_actions (formular, action, event) values (GetFormularId(GetOrCreateApplication('<xsl:value-of select="$package"/>'), '<xsl:value-of select="$thisClassName"/>'), currval('actions_id_seq'), 'evt_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>');
</xsl:if>
<xsl:if test="$TargetDBType = 'Sqlite'">
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) 
values ('open <xsl:value-of select="$otherClassName"/>', 1, '<xsl:value-of select="$otherClassName"/>', 4, 
(select id from actions where name = '<xsl:value-of select="$assocname1"/>_<xsl:value-of select="$otherClassName"/>')); 

insert into formular_actions (formular, action, event) values (
(select id from "formulare" where anwendungid in 
 (select id from "anwendungen" where name = '<xsl:value-of select="$package"/>') 
	and name = '<xsl:value-of select="$thisClassName"/>'), 
(select id from actions where name = '<xsl:value-of select="$assocname1"/>_<xsl:value-of select="$otherClassName"/>'), 'evt_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>');
</xsl:if>
</xsl:if>
</xsl:if>
</xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
