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
    <xsl:variable name="stereoTypeID" select="UML:ModelElement.stereotype//@xmi.idref"/>
    <xsl:variable name="stereoTypeName">
      <xsl:value-of select="//UML:Stereotype[@xmi.id = $stereoTypeID]/@name"/>
    </xsl:variable>
    <xsl:variable name="name" select="concat(@name, UML:ModelElement.name)"/>
    <xsl:message>

SET SESSION AUTHORIZATION 'postgres';

DROP FUNCTION GetOrCreateApplication(varchar);
DROP FUNCTION GetFormularId(int, varchar);

CREATE OR REPLACE FUNCTION plpgsql_call_handler()
  RETURNS language_handler AS
'$libdir/plpgsql', 'plpgsql_call_handler'
  LANGUAGE 'c' VOLATILE;

DROP LANGUAGE plpgsql;
CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;


CREATE OR REPLACE FUNCTION GetOrCreateApplication(varchar)
  RETURNS int AS
'
declare
applicationid int;
applicationname alias for $1;
begin
  select id into applicationid from anwendungen where name =  applicationname;
  if not applicationid is null then
    return applicationid;
  end if;
  if applicationid is null then
	insert into anwendungen (name, titel, modulename, functor, interface) values(applicationname, ''Application '' || applicationname, ''lbDynApp'', ''instanceOfApplication'', ''lb_I_Application'');
	applicationid = GetOrCreateApplication(applicationname);
	insert into user_anwendungen (userid, anwendungenid) values (1, applicationid);
	insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBUser'', ''dba'', applicationid);
	insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBPass'', ''trainres'', applicationid);
	insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBName'', ''CRM'', applicationid);
  end if;
return applicationid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

CREATE OR REPLACE FUNCTION GetFormularId(int, varchar)
  RETURNS int AS
'
declare
formularid int;
applicationid alias for $1;
applicationname alias for $2;
begin
	select id into formularid from formulare where anwendungid = applicationid and name = applicationname;
	return formularid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

	
	
-- Package: <xsl:value-of select="$name"/>


select GetOrCreateApplication('<xsl:value-of select="$name"/>');

    </xsl:message>
    <xsl:element name="package">
      <xsl:attribute name="name">
        <xsl:value-of select="$name"/>
      </xsl:attribute>
      <xsl:apply-templates select="UML:Namespace.ownedElement/UML:Class"/>
    </xsl:element>
      <xsl:for-each select="UML:Namespace.ownedElement/UML:Class">
        <xsl:variable name="classID" select="@xmi.id"/>
        <xsl:call-template name="genAssociations">
          <xsl:with-param name="classID" select="$classID"/>
          <xsl:with-param name="package" select="$name"/>
        </xsl:call-template>
      </xsl:for-each>
  </xsl:template>

  <xsl:template match="UML:Class">
    <!-- ****************** CLASS ********************* -->
    <xsl:variable name="classID" select="@xmi.id"/>
    <xsl:element name="class">
-- Class is <xsl:value-of select="@name"/>
<xsl:variable name="classname" select="@name"/>
-- Initialize formular definition

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
</xsl:for-each> from "<xsl:value-of select="@name"/>" order by "ID"', GetFormularId(GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), '<xsl:value-of select="@name"/>'));
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
</xsl:for-each>

insert into anwendungen_formulare (anwendungid, formularid) values(GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), GetFormularId(GetOrCreateApplication('<xsl:value-of select="../../@name"/>'), '<xsl:value-of select="@name"/>'));
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
    <!-- ****************** CLASS ********************* -->
    <xsl:param name="classID"/>
    <xsl:param name="package"/>
    <xsl:call-template name="associationsForClass_12">
      <xsl:with-param name="id" select="$classID"/>
      <xsl:with-param name="package" select="$package"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template name="genQueryForeignKeyColumns">
    <xsl:param name="id"/>
    <xsl:param name="package"/>
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
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/><xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='none'">
<xsl:if test="../../../UML:AssociationEnd/UML:ModelElement.stereotype/UML:Stereotype/@name='masterdetail_action'">, "<xsl:value-of select="$otherClassName"/>" </xsl:if>
</xsl:if>
</xsl:for-each>
  </xsl:template>

  <xsl:template name="associationsForClass_12">
    <xsl:param name="id"/>
    <xsl:param name="package"/>    
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
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='aggregate'">
<xsl:if test="../../../UML:AssociationEnd/UML:ModelElement.stereotype/UML:Stereotype/@name='masterdetail_action'">
-- Association <xsl:value-of select="$thisClassName"/> -&gt; <xsl:value-of select="$otherClassName"/>
<xsl:variable name="assocname" select="../../../../@name"/>
<xsl:variable name="assocname1" select="substring-after(substring-before($assocname, ')'), '(')"/>
<xsl:if test="$assocname1=''">
insert into actions (name, typ, source, target) values ('<xsl:value-of select="$otherClassName"/>', 1, 'ID', 0);
</xsl:if>
<xsl:if test="$assocname1!=''">
insert into actions (name, typ, source, target) values ('<xsl:value-of select="$otherClassName"/>', 1, '<xsl:value-of select="$assocname1"/>', 0);
</xsl:if>
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'open <xsl:value-of select="$otherClassName"/>', 1, '<xsl:value-of select="$otherClassName"/>', 4, currval('actions_id_seq')); 

insert into formular_actions (formular, action, event) values (GetFormularId(GetOrCreateApplication('<xsl:value-of select="$package"/>'), '<xsl:value-of select="$thisClassName"/>'), currval('actions_id_seq'), 'evt_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>');
</xsl:if>
</xsl:if>
</xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
