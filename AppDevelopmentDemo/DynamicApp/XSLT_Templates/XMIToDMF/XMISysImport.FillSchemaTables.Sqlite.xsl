<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" xmlns:UML="org.omg.xmi.namespace.UML" exclude-result-prefixes="UML">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2013  Lothar Behrens (lothar.behrens@lollisoft.de)

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
<xsl:output method="text"/>

<xsl:template name="XMISysImport.FillSchemaAssociations.Sqlite">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="ApplicationName"/>
    <xsl:param name="AssociationId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->

<xsl:variable name="PrimaryKeyClassId" select="//UML:Association[@xmi.id=$AssociationId]/UML:Association.connection/UML:AssociationEnd[@aggregation='aggregate']/UML:AssociationEnd.participant/UML:Class/@xmi.idref"/>
<xsl:variable name="ForeignKeyClassId" select="//UML:Association[@xmi.id=$AssociationId]/UML:Association.connection/UML:AssociationEnd[@aggregation='none']/UML:AssociationEnd.participant/UML:Class/@xmi.idref"/>
<xsl:variable name="PrimaryKeyClassName" select="//UML:Class[@xmi.id=$PrimaryKeyClassId]/@name"/>
<xsl:variable name="ForeignKeyClassName" select="//UML:Class[@xmi.id=$ForeignKeyClassId]/@name"/>

<xsl:variable name="assoc_end_name" select="//UML:Association[@xmi.id=$AssociationId]/UML:Association.connection/UML:AssociationEnd[@aggregation='aggregate']/@name"/>
<xsl:variable name="assoc_name" select="//UML:Association[@xmi.id=$AssociationId]/@name"/>
<xsl:variable name="fieldName">
<xsl:choose>
	<xsl:when test="$assoc_end_name!=''"><xsl:value-of select="$assoc_end_name"/></xsl:when>
<!--
Don't use the association name here. If one has two or more associations between the same tables, the field names must be specified explicitely.
	<xsl:when test="$assoc_name!=''"><xsl:value-of select="$assoc_name"/></xsl:when>
-->
	<xsl:otherwise><xsl:value-of select="$PrimaryKeyClassName"/></xsl:otherwise>
</xsl:choose>
</xsl:variable>


<xsl:call-template name="XMISysImport.FillSchemaTables.Sqlite.foreignkeys">
	<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
	<xsl:with-param name="PrimaryKeyClassId" select="$PrimaryKeyClassId"/>
	<xsl:with-param name="ForeignKeyClassId" select="$ForeignKeyClassId"/>
	<xsl:with-param name="PrimaryKeyClassName" select="$PrimaryKeyClassName"/>
	<xsl:with-param name="ForeignKeyClassName" select="$ForeignKeyClassName"/>
	<xsl:with-param name="ForeignKeyFieldName" select="$fieldName"/>
	
</xsl:call-template>

</xsl:template>

<xsl:template name="XMISysImport.FillSchemaTables.Sqlite">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="ApplicationName"/>
    <xsl:param name="ClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
-- Fill schema tables
<xsl:variable name="ClassName" select="//UML:Class[@xmi.id=$ClassId]/@name"/>

<xsl:call-template name="XMISysImport.FillSchemaTables.Sqlite.dbtables">
	<xsl:with-param name="ClassId" select="$ClassId"/>
	<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
	<xsl:with-param name="ClassName" select="$ClassName"/>
</xsl:call-template>

<xsl:call-template name="XMISysImport.FillSchemaTables.Sqlite.dbcolumns">
	<xsl:with-param name="ClassId" select="$ClassId"/>
	<xsl:with-param name="ClassName" select="$ClassName"/>
</xsl:call-template>

<xsl:call-template name="XMISysImport.FillSchemaTables.Sqlite.primarykeys">
	<xsl:with-param name="ClassID" select="$ClassId"/>
	<xsl:with-param name="ClassName" select="$ClassName"/>
	<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
</xsl:call-template>

<xsl:call-template name="XMISysImport.FillSchemaTableProperties.Sqlite">
	<xsl:with-param name="ClassId" select="$ClassId"/>
	<xsl:with-param name="ApplicationName" select="$ApplicationName"/>
	<xsl:with-param name="ClassName" select="$ClassName"/>
</xsl:call-template>

</xsl:template>

<xsl:template name="XMISysImport.FillSchemaTables.Sqlite.dbtables">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="ClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
-- Fill schema tables dbtables

DELETE FROM dbcolumnparameter WHERE dbcolumnid in (SELECT id FROM dbcolumn WHERE dbtableid in (SELECT id FROM dbtable WHERE tablename = '<xsl:value-of select="$ClassName"/>' AND anwendungenid = (SELECT id FROM anwendungen where name = '<xsl:value-of select="$ApplicationName"/>')));

DELETE FROM dbcolumn WHERE dbtableid in (SELECT id FROM dbtable WHERE tablename = '<xsl:value-of select="$ClassName"/>' AND anwendungenid = (SELECT id FROM anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
DELETE FROM dbforeignkey WHERE dbtableid in (SELECT id FROM dbtable WHERE tablename = '<xsl:value-of select="$ClassName"/>' AND anwendungenid = (SELECT id FROM anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
DELETE FROM dbprimarykey WHERE dbtableid in (SELECT id FROM dbtable WHERE tablename = '<xsl:value-of select="$ClassName"/>' AND anwendungenid = (SELECT id FROM anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
DELETE FROM dbtableparameter WHERE dbtableid in (SELECT id FROM dbtable WHERE tablename = '<xsl:value-of select="$ClassName"/>' AND anwendungenid = (SELECT id FROM anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
DELETE FROM dbtable WHERE anwendungenid = (SELECT id FROM anwendungen where name = '<xsl:value-of select="$ApplicationName"/>') AND tablename = '<xsl:value-of select="$ClassName"/>';

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', '<xsl:value-of select="$ClassName"/>', '', '<xsl:value-of select="$ClassId"/>', id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>';

</xsl:template>

<xsl:template name="XMISysImport.FillSchemaTables.Sqlite.dbcolumns">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="ClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
-- Fill schema tables dbcolumns

	<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">
	
	
<xsl:variable name="dbtyperef"><xsl:value-of select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/></xsl:variable>
<xsl:variable name="stereotyperef" select="./UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref"/>
<xsl:variable name="stereotype">
<xsl:if test="$stereotyperef!=''">
<xsl:value-of select="//UML:Stereotype[@xmi.id=$stereotyperef]/@name"/>
</xsl:if>
<xsl:if test="./UML:ModelElement.taggedValue/UML:TaggedValue[@tag='stereotype']/@value!=''">
<xsl:value-of select="./UML:ModelElement.taggedValue/UML:TaggedValue[@tag='stereotype']/@value"/>
</xsl:if>
</xsl:variable>
	
<xsl:variable name="dbtype">
<xsl:choose>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='bool'">BIT</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='date'">DATE</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='datetime'">DATETIME</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='int'">int4</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='string'">bpchar</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='phonenumber'">bpchar</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='bigstring'">TEXT</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='float'">FLOAT</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='double'">DOUBLE</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='decimal'">DECIMAL</xsl:when>
	<xsl:when test="//UML:DataType[@xmi.id=$dbtyperef]/@name='image'">BYTEA</xsl:when>
	  <xsl:otherwise>
	  <xsl:if test="$stereotype='custombinaryfield'"><xsl:value-of select="//UML:DataType[@xmi.id=$dbtyperef]/@name"/></xsl:if>
	  <xsl:if test="$stereotype='customstringfield'"><xsl:value-of select="//UML:DataType[@xmi.id=$dbtyperef]/@name"/></xsl:if>
	  <xsl:if test="$stereotype='custombigstringfield'"><xsl:value-of select="//UML:DataType[@xmi.id=$dbtyperef]/@name"/></xsl:if>
	  </xsl:otherwise>
</xsl:choose>
</xsl:variable>	

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select '<xsl:value-of select="@name"/>', '<xsl:value-of select="@xmi:id"/>', '<xsl:value-of select="$dbtype"/>', -1, 0, '<xsl:value-of select="$ClassName"/>', id from dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND tableremarks = '<xsl:value-of select="$ClassId"/>';

<xsl:choose>

	<xsl:when test="$stereotype='password'">INSERT OR IGNORE INTO "dbcolumnparameter" (parametername, parametervalue, dbcolumnid) VALUES ('stereotype', 'PasswordField', (SELECT id from "dbcolumn" WHERE columnname = '<xsl:value-of select="@name"/>' AND tablename = '<xsl:value-of select="$ClassName"/>' AND dbtableid = (SELECT id FROM dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND tableremarks = '<xsl:value-of select="$ClassId"/>')));</xsl:when>
	<xsl:when test="$stereotype='claim'">INSERT OR IGNORE INTO "dbcolumnparameter" (parametername, parametervalue, dbcolumnid) VALUES ('stereotype', 'ClaimField', (SELECT id from "dbcolumn" WHERE columnname = '<xsl:value-of select="@name"/>' AND tablename = '<xsl:value-of select="$ClassName"/>' AND dbtableid = (SELECT id FROM dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND tableremarks = '<xsl:value-of select="$ClassId"/>')));</xsl:when>
	<xsl:when test="$stereotype='approvedclaim'">INSERT OR IGNORE INTO "dbcolumnparameter" (parametername, parametervalue, dbcolumnid) VALUES ('stereotype', 'ApprovedClaimField', (SELECT id from "dbcolumn" WHERE columnname = '<xsl:value-of select="@name"/>' AND tablename = '<xsl:value-of select="$ClassName"/>' AND dbtableid = (SELECT id FROM dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND tableremarks = '<xsl:value-of select="$ClassId"/>')));</xsl:when>
	<xsl:when test="$stereotype='salt'">INSERT OR IGNORE INTO "dbcolumnparameter" (parametername, parametervalue, dbcolumnid) VALUES ('stereotype', 'HiddenField', (SELECT id from "dbcolumn" WHERE columnname = '<xsl:value-of select="@name"/>' AND tablename = '<xsl:value-of select="$ClassName"/>' AND dbtableid = (SELECT id FROM dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND tableremarks = '<xsl:value-of select="$ClassId"/>')));</xsl:when>
	<xsl:when test="$stereotype='timeout'">INSERT OR IGNORE INTO "dbcolumnparameter" (parametername, parametervalue, dbcolumnid) VALUES ('stereotype', 'HiddenField', (SELECT id from "dbcolumn" WHERE columnname = '<xsl:value-of select="@name"/>' AND tablename = '<xsl:value-of select="$ClassName"/>' AND dbtableid = (SELECT id FROM dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND tableremarks = '<xsl:value-of select="$ClassId"/>')));</xsl:when>
	<xsl:when test="$stereotype='onetimetoken'">INSERT OR IGNORE INTO "dbcolumnparameter" (parametername, parametervalue, dbcolumnid) VALUES ('stereotype', 'HiddenField', (SELECT id from "dbcolumn" WHERE columnname = '<xsl:value-of select="@name"/>' AND tablename = '<xsl:value-of select="$ClassName"/>' AND dbtableid = (SELECT id FROM dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND tableremarks = '<xsl:value-of select="$ClassId"/>')));</xsl:when>

	<xsl:otherwise></xsl:otherwise>

</xsl:choose>

	</xsl:for-each>
	

</xsl:template>

<xsl:template name="XMISysImport.FillSchemaTables.Sqlite.foreignkeys">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="PrimaryKeyClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ForeignKeyClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="PrimaryKeyClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ForeignKeyClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ForeignKeyFieldName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
-- Fill schema tables foreignkeys

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) select '', '', '<xsl:value-of select="$PrimaryKeyClassName"/>', 'ID', '', '', '<xsl:value-of select="$ForeignKeyClassName"/>', '<xsl:value-of select="$ForeignKeyFieldName"/>', 0, 0, 0, id from dbtable where tablename = '<xsl:value-of select="$ForeignKeyClassName"/>' AND tableremarks = '<xsl:value-of select="$ForeignKeyClassId"/>';

</xsl:template>

<xsl:template name="XMISysImport.FillSchemaTables.Sqlite.primarykeys">
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="ClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassName"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
    <xsl:param name="ApplicationName"/>	
-- Fill schema tables primarykeys

INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', '<xsl:value-of select="$ClassName"/>', 'ID',  '', 0, id from dbtable where tablename = '<xsl:value-of select="$ClassName"/>' AND anwendungenid = (SELECT id FROM anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

</xsl:template>

<xsl:template name="XMISysImport.FillSchemaTableProperties.Sqlite">
    <xsl:param name="ClassId"/><!-- The Id for the current class to create schema information -->
    <xsl:param name="ClassName"/><!-- The Id for the current class to create schema information -->
	  <xsl:for-each select="./UML:ModelElement.taggedValue/UML:TaggedValue">
<xsl:if test="$TargetDBType = 'Sqlite'">
insert into dbtableparameter (parametername, parametervalue, dbtableid) values('<xsl:value-of select="@tag"/>', '<xsl:value-of select="@value"/>', 
(select id from dbtable where tablename = '<xsl:value-of select="$ClassName"/>' and tableremarks = '<xsl:value-of select="$ClassId"/>'));
</xsl:if>
      </xsl:for-each>

</xsl:template>
	  
	  

</xsl:stylesheet>

