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


<xsl:template name="Translate.CreateTable.Sqlite">
    <xsl:param name="ClassID"/><!--  -->
    <xsl:param name="ClassName"/><!--  -->
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
    <xsl:param name="Stereotype"/><!--  -->
CREATE TABLE "<xsl:value-of select="$ClassName"/>" (
	"ID" INTEGER PRIMARY KEY<xsl:call-template name="Translate.CreateColumn.Sqlite"><xsl:with-param name="ClassID" select="$ClassID"/>
	</xsl:call-template><xsl:call-template name="Translate.BuildForeignColumns.Sqlite">
	<xsl:with-param name="ClassID" select="$ClassID"/>
	</xsl:call-template>
);	
</xsl:template>

<xsl:template name="Translate.DropRules.Sqlite">
    <xsl:param name="ID"/><!--  -->
    <xsl:param name="ReferencingClassID"/><!--  -->
    <xsl:param name="ReferencedClassID"/><!--  -->
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
<xsl:if test="$execute_droprules = 'yes'">
-- Create a Translate.DropRules.Sqlite
	<xsl:for-each select="//UML:Namespace.ownedElement/UML:Class">
<xsl:call-template name="Translate.DropAssociations.Sqlite">
	<xsl:with-param name="ClassID" select="@xmi.id"/>
	</xsl:call-template>
	</xsl:for-each>
	<xsl:for-each select="//UML:Namespace.ownedElement/UML:Class">
DROP TABLE "<xsl:value-of select="@name"/>";
	</xsl:for-each>
</xsl:if>
</xsl:template>

<xsl:template name="Translate.StoredProcRules.Sqlite">
    <xsl:param name="ID"/><!--  -->
    <xsl:param name="ReferencingClassID"/><!--  -->
    <xsl:param name="ReferencedClassID"/><!--  -->
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
-- Create a Translate.StoredProcRules.Sqlite
</xsl:template>

<xsl:template match="UML:Classifier.feature/UML:Attribute">
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>,
	"<xsl:value-of select="@name"/>"<xsl:value-of select="' '"/><xsl:variable name="UMLType" select="//UML:DataType[@xmi.id=$type]/@name"/>
<xsl:call-template name="Translate.ConvertType.Sqlite"><xsl:with-param name="typename" select="$UMLType"/></xsl:call-template></xsl:template>
<xsl:template name="Translate.CreateColumn.Sqlite">
<xsl:apply-templates select="UML:Classifier.feature/UML:Attribute"/>	
</xsl:template>

<!-- Handling of found associations -->

<xsl:template name="Translate.Association.Sqlite">
    <xsl:param name="ID"/><!--  -->
    <xsl:param name="ReferencingClassID"/><!--  -->
    <xsl:param name="ReferencedClassID"/><!--  -->
	<xsl:param name="overwriteDatabase"/><!-- When set to yes, DROP rules are created -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database -->
	<xsl:call-template name="Translate.CreateAssociations.Sqlite">
	<xsl:with-param name="ClassID" select="$ReferencingClassID"/>
	</xsl:call-template>	
</xsl:template>

<xsl:template name="Translate.BuildForeignColumns.Sqlite">
    <xsl:param name="ID"/><!--  -->
    <xsl:param name="ClassID"/><!--  -->
    <xsl:param name="AssocuationID"/><!--  -->
    <xsl:param name="TargetDBVersion"/><!-- What is the version of the database --><xsl:call-template name="Translate.CreateForeignColumn.Sqlite">
	<xsl:with-param name="ClassID" select="$ClassID"/>
	</xsl:call-template>
</xsl:template>

<xsl:template name="Translate.ConvertType.Sqlite">
    <xsl:param name="typename"/>
    <xsl:choose>
      <xsl:when test="$typename='bool'">BOOL</xsl:when>
      <xsl:when test="$typename='boolean'">BOOL</xsl:when>
      <xsl:when test="$typename='int'">INTEGER</xsl:when>
      <xsl:when test="$typename='float'">DECIMAL</xsl:when>
      <xsl:when test="$typename='date'">DATE</xsl:when>
      <xsl:when test="$typename='shortstring'">CHAR(20)</xsl:when>
      <xsl:when test="$typename='string'">CHAR(255)</xsl:when>
      <xsl:when test="$typename='text'">TEXT</xsl:when>
      <xsl:when test="$typename='bigstring'">TEXT</xsl:when>
      <xsl:when test="$typename='image'">BYTEA</xsl:when>
    </xsl:choose>
  </xsl:template>

<xsl:template name="Translate.CreateForeignColumn.Sqlite">
  <xsl:param name="ClassID"/><xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $ClassID]">
      <!-- Choose only association ends where navigable is true. -->
      <xsl:variable name="changeForeignKeyName" select="../@name"/>
      <xsl:variable name="thisEnd" select="../.."/>
      <xsl:variable name="thisEndId" select="$thisEnd/@xmi.id"/>
      <xsl:variable name="thisEndType" select="$thisEnd/@type"/>
      <xsl:variable name="thisClassName" select="//UML:Class[@xmi.id=$thisEndType]/@name"/>
      <xsl:variable name="otherEnd" select="../../../UML:AssociationEnd[@type != $thisEndType]"/>
      <xsl:variable name="otherEndType" select="../../../UML:AssociationEnd[@type != $thisEndType]/@type"/>
      <xsl:variable name="otherEndId" select="$otherEnd/@type"/>
      <xsl:variable name="otherClassID" select="../../../UML:AssociationEnd[@type=$otherEndId]/UML:AssociationEnd.participant/@xmi.idref"/>
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/><xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='aggregate'">,
<xsl:variable name="assocname" select="../../../UML:AssociationEnd[@type = $thisEndType]/@name"/><xsl:if test="$assocname=''">	"<xsl:value-of select="$otherClassName"/>" INTEGER</xsl:if>
<xsl:if test="$assocname!=''">
	"<xsl:value-of select="$assocname"/>" INTEGER</xsl:if>
</xsl:if>
    </xsl:for-each>
  </xsl:template>

<xsl:template name="Translate.DropAssociations.Sqlite">
    <xsl:param name="ClassID"/>
    <!-- UML1.4: -->
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $ClassID]">
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
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='none'">
<xsl:variable name="assocname" select="../../../UML:AssociationEnd[@type != $thisEndType]/@name"/>
<xsl:if test="$assocname=''">
<xsl:if test="$TargetDBType = 'Sqlite'">
DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ins";
DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_upd";
DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_del";
DELETE FROM "lbDMF_ForeignKeys" WHERE "PKTable"='<xsl:value-of select="$thisClassName"/>' AND "PKColumn"='ID' AND "FKTable"='<xsl:value-of select="$otherClassName"/>' AND "FKColumn"='<xsl:value-of select="$thisClassName"/>';
</xsl:if>
</xsl:if>
<xsl:if test="$assocname!=''">
<xsl:if test="$TargetDBType = 'Sqlite'">
DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_<xsl:value-of select="$assocname"/>_ins";
DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_upd";
DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_del";
DELETE FROM "lbDMF_ForeignKeys" WHERE "PKTable"='<xsl:value-of select="$thisClassName"/>' AND "PKColumn"='ID' AND "FKTable"='<xsl:value-of select="$otherClassName"/>' AND "FKColumn"='<xsl:value-of select="$assocname"/>';
</xsl:if>
</xsl:if>
</xsl:if>
    </xsl:for-each>
</xsl:template>

<xsl:template name="Translate.CreateAssociations.Sqlite">
    <xsl:param name="ClassID"/>
    <!-- UML1.4: -->
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $ClassID]">
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
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='none'">
<xsl:variable name="assocname" select="../../../UML:AssociationEnd[@type != $thisEndType]/@name"/>
<xsl:if test="$assocname=''">
<xsl:if test="$TargetDBType = 'Sqlite'">
CREATE TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ins" BEFORE INSERT ON <xsl:value-of select="$otherClassName"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="$thisClassName"/> IS NOT NULL) AND ((SELECT ID FROM <xsl:value-of select="$thisClassName"/> WHERE ID = new.<xsl:value-of select="$thisClassName"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="$thisClassName"/> violates foreign key <xsl:value-of select="$thisClassName"/>(ID)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_upd" BEFORE UPDATE ON <xsl:value-of select="$otherClassName"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="$thisClassName"/> IS NOT NULL) AND ((SELECT ID FROM <xsl:value-of select="$thisClassName"/> WHERE ID = new.<xsl:value-of select="$thisClassName"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="$thisClassName"/> violates foreign key <xsl:value-of select="$thisClassName"/>(ID)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_del" BEFORE DELETE ON <xsl:value-of select="$thisClassName"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT <xsl:value-of select="$thisClassName"/> FROM <xsl:value-of select="$otherClassName"/> WHERE <xsl:value-of select="$thisClassName"/> = old.<xsl:value-of select="$thisClassName"/>) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key <xsl:value-of select="$otherClassName"/>(<xsl:value-of select="$thisClassName"/>)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('<xsl:value-of select="$thisClassName"/>', 'ID', '<xsl:value-of select="$otherClassName"/>', '<xsl:value-of select="$thisClassName"/>');
</xsl:if>
</xsl:if>
<xsl:if test="$assocname!=''">
<xsl:if test="$TargetDBType = 'Sqlite'">
CREATE TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_<xsl:value-of select="$assocname"/>_ins" BEFORE INSERT ON <xsl:value-of select="$otherClassName"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="$assocname"/> IS NOT NULL) AND ((SELECT ID FROM <xsl:value-of select="$thisClassName"/> WHERE ID = new.<xsl:value-of select="$assocname"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="$thisClassName"/> violates foreign key <xsl:value-of select="$assocname"/>(ID)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_upd" BEFORE UPDATE ON <xsl:value-of select="$otherClassName"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.<xsl:value-of select="$assocname"/> IS NOT NULL) AND ((SELECT ID FROM <xsl:value-of select="$thisClassName"/> WHERE ID = new.<xsl:value-of select="$assocname"/>) IS NULL))
                 THEN RAISE(ABORT, '<xsl:value-of select="$thisClassName"/> violates foreign key <xsl:value-of select="$assocname"/>(ID)')
    END;
END;
CREATE TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_del" BEFORE DELETE ON <xsl:value-of select="$thisClassName"/> FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT <xsl:value-of select="$assocname"/> FROM <xsl:value-of select="$otherClassName"/> WHERE <xsl:value-of select="$assocname"/> = old.ID) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key <xsl:value-of select="$otherClassName"/>(<xsl:value-of select="$assocname"/>)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('<xsl:value-of select="$thisClassName"/>', 'ID', '<xsl:value-of select="$otherClassName"/>', '<xsl:value-of select="$assocname"/>');
</xsl:if>
</xsl:if>
</xsl:if>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
