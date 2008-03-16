<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:UML="org.omg.xmi.namespace.UML" exclude-result-prefixes="UML">
<!--
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2007  Lothar Behrens (lothar.behrens@lollisoft.de)

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
  <xsl:output method="text" indent="no"/>
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
    <xsl:element name="package">
      <xsl:attribute name="name">
        <xsl:value-of select="concat(@name, UML:ModelElement.name)"/>
      </xsl:attribute>
      <xsl:attribute name="id">
        <xsl:call-template name="XMI1_2_getID"/>
      </xsl:attribute>

      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="dropAssociations">
          <xsl:with-param name="classID" select="$classID"/>
        </xsl:call-template>
      </xsl:for-each>

      <xsl:apply-templates select="UML:Namespace.ownedElement/UML:Class"/>
    </xsl:element>
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="genAssociations">
          <xsl:with-param name="classID" select="$classID"/>
        </xsl:call-template>
      </xsl:for-each>
  </xsl:template>

  <xsl:template match="UML:Package|UML:Subsystem">
    <xsl:variable name="packageID" select="@xmi.id"/>
<!--
    <xsl:variable name="stereoTypeID" select="UML:ModelElement.stereotype/@xmi.idref"/>

    <xsl:variable name="stereoTypeName">
      <xsl:value-of select="//UML:Stereotype[@xmi.id = $stereoTypeID]/@name"/>
    </xsl:variable>
-->
    <xsl:variable name="packagename" select="concat(@name, UML:ModelElement.name)"/>
    <xsl:message>
-- New version
-- Package: <xsl:value-of select="@name"/>
    </xsl:message>

      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="dropAssociations">
          <xsl:with-param name="classID" select="$classID"/>
        </xsl:call-template>
      </xsl:for-each>

    <xsl:element name="package">
      <xsl:attribute name="name">
        <xsl:value-of select="@name"/>
      </xsl:attribute>
      <xsl:apply-templates select="UML:Namespace.ownedElement/UML:Class"/>
    </xsl:element>
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="genAssociations">
          <xsl:with-param name="classID" select="$classID"/>
        </xsl:call-template>
      </xsl:for-each>
  </xsl:template>

  <xsl:template match="UML:Class">
    <!-- ****************** CLASS ********************* -->
    <xsl:variable name="classID" select="@xmi.id"/>
    <xsl:element name="class">
-- Class is <xsl:value-of select="@name"/>
select dropTable('<xsl:value-of select="@name"/>');

CREATE TABLE "<xsl:value-of select="@name"/>" (
"ID" SERIAL,
PRIMARY KEY ("ID")<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">,
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>
"<xsl:value-of select="@name"/>"<xsl:value-of select="' '"/><xsl:variable name="UMLType" select="//UML:DataType[@xmi.id=$type]/@name"/>
<xsl:call-template name="convertTypes_DBTypes"><xsl:with-param name="typename" select="$UMLType"/></xsl:call-template>
</xsl:for-each>
);
    </xsl:element>
  </xsl:template>

  <xsl:template name="convertTypes_DBTypes">
    <xsl:param name="typename"/>
    <xsl:choose>
      <xsl:when test="$typename='int'">INTEGER</xsl:when>
      <xsl:when test="$typename='float'">DECIMAL</xsl:when>
      <xsl:when test="$typename='date'">DATE</xsl:when>
      <xsl:when test="$typename='string'">CHAR(100)</xsl:when>
      <xsl:when test="$typename='bigstring'">bytea</xsl:when>
      <xsl:when test="$typename='image'">bytea</xsl:when>
    </xsl:choose>

  </xsl:template>

  <xsl:template name="genAssociations">
    <!-- ****************** CLASS ********************* -->
    <xsl:param name="classID"/>
    <xsl:call-template name="associationsForClass_12">
      <xsl:with-param name="id" select="$classID"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template name="dropAssociations">
    <!-- ****************** CLASS ********************* -->
    <xsl:param name="classID"/>
    <xsl:call-template name="drop_associationsForClass_12">
      <xsl:with-param name="id" select="$classID"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template name="associationsForClass_12">
    <xsl:param name="id"/>
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
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/>
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='none'">
-- Association <xsl:value-of select="$otherClassName"/> -&gt; <xsl:value-of select="$thisClassName"/>

ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD COLUMN "<xsl:value-of select="$thisClassName"/>" INT;
ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD CONSTRAINT "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ID" FOREIGN KEY ( "<xsl:value-of select="$thisClassName"/>" )
   REFERENCES "<xsl:value-of select="$thisClassName"/>" ( "ID" );
</xsl:if>
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="drop_associationsForClass_12">
    <xsl:param name="id"/>
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
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/>
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='none'">
-- Association <xsl:value-of select="$thisClassName"/> -&gt; <xsl:value-of select="$otherClassName"/>
select dropConstraint('<xsl:value-of select="$otherClassName"/>', 'fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ID');
</xsl:if>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
