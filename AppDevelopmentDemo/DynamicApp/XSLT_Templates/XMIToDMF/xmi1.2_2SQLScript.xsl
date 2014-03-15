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
<!-- This file must be generated before this template could be applied. -->
<xsl:import href="XMISettings.xsl"/>
<xsl:import href="XMIImport.Variables.xsl"/>

<xsl:output method="text" indent="no"/>

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
-- Creating a database script for '<xsl:value-of select="$targetdatabase"/>'


-- Params XSLDatabaseBackendSystem: <xsl:value-of select="$XSLDatabaseBackendSystem"/>
-- Params XSLDatabaseBackendApplication: <xsl:value-of select="$XSLDatabaseBackendApplication"/>
-- Params overwriteDatabase: <xsl:value-of select="$overwriteDatabase"/>

-- xmi1.2_2SQLScript.xsl: Creating a database script for '<xsl:value-of select="$targetdatabase"/>'


-- Params XSLDatabaseBackendSystem: <xsl:value-of select="$XSLDatabaseBackendSystem"/>
-- Params XSLDatabaseBackendApplication: <xsl:value-of select="$XSLDatabaseBackendApplication"/>
-- Params overwriteDatabase: <xsl:value-of select="$overwriteDatabase"/>

-- xmi1.2_2SQLScript.xsl: Creating a database script for '<xsl:value-of select="$targetdatabase"/>'

<!-- Create some required functions -->

<xsl:if test="$TargetDBType = 'PostgreSQL'">
-- dropconstraint("varchar", "varchar")
--
-- Drops a constraint if it exists.

CREATE OR REPLACE FUNCTION dropconstraint("varchar", "varchar")
  RETURNS void AS
'
declare
tres text;
declare tt alias for $2;
begin
  select conname into tres from pg_constraint where conname = $2;
  if not tres is null then
    execute ''alter table "'' || $1 || ''" drop constraint "'' || $2 || ''"'';
  end if;
  return;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

-- dropTable("varchar")
--
-- This function drops a table, if it exists.

CREATE OR REPLACE FUNCTION dropTable("varchar")
  RETURNS void AS
'
declare
tres text;
declare tt alias for $1;
begin
  select tablename into tres from pg_tables where tablename = $1;
  if not tres is null then
    execute ''DROP TABLE "'' || $1 || ''"'';
  end if;
  return;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
-- dropconstraint("varchar", "varchar")
--
-- Drops a constraint if it exists.
exec sp_sqlexec '
CREATE PROCEDURE lbDMF_DropConstraint(@Table VARCHAR(50), @Name VARCHAR(50))
AS
BEGIN
	DECLARE @Statement1 VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT ''ALTER TABLE '' + @Table + '' DROP CONSTRAINT '' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN (''F'') AND upper(pr.name) = upper(@Name)
		
	OPEN hSqlProc
	FETCH hSqlProc INTO @Statement1
	WHILE (@@fetch_status = 0)
		BEGIN
			EXECUTE (@Statement1)
			FETCH hSqlProc INTO @Statement1
		END
	CLOSE hSqlProc
	
	DEALLOCATE hSqlProc
END;
';

exec sp_sqlexec '
CREATE PROCEDURE lbDMF_DropTable(@Table VARCHAR(50))
AS
BEGIN
	DECLARE @Statement2 VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT ''DROP TABLE '' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN (''U'') AND upper(pr.name) = upper(@Table)
		
	OPEN hSqlProc
	FETCH hSqlProc INTO @Statement2
	WHILE (@@fetch_status = 0)
		BEGIN
			EXECUTE (@Statement2)
			FETCH hSqlProc INTO @Statement2
		END
	CLOSE hSqlProc
	
	DEALLOCATE hSqlProc
END;
';

exec sp_sqlexec '
CREATE PROCEDURE lbDMF_DropProc(@Name VARCHAR(50))
AS
BEGIN
	DECLARE @Statement3 VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT ''DROP '' + case pr.xtype when 
			''P'' then ''PROCEDURE '' else ''FUNCTION '' end + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN (''P'',''FN'',''TF'') AND upper(pr.name) = upper(@Name)
		
	OPEN hSqlProc
	FETCH hSqlProc INTO @Statement3
	WHILE (@@fetch_status = 0)
		BEGIN
			EXECUTE (@Statement3)
			FETCH hSqlProc INTO @Statement3
		END
	CLOSE hSqlProc
	
	DEALLOCATE hSqlProc
END;
';

</xsl:if>

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
	  
<xsl:if test="$TargetDBType = 'MSSQL'">
exec  lbDMF_DropProc 'lbDMF_DropTable';

exec  lbDMF_DropProc 'lbDMF_DropConstraint';

exec  lbDMF_DropProc 'lbDMF_DropProc';

</xsl:if>
<xsl:if test="$TargetDBType = 'Sqlite'">
-- Drop a constraint
</xsl:if>
	  
  </xsl:template>

  <xsl:template match="UML:Class">
    <!-- ****************** CLASS ********************* -->
    <xsl:variable name="classID" select="@xmi.id"/>
    <xsl:element name="class">
-- Class is <xsl:value-of select="@name"/> <xsl:value-of select="$TargetDBType"/> 

<xsl:if test="$TargetDBType = 'PostgreSQL'">

select dropTable('<xsl:value-of select="@name"/>');

CREATE TABLE "<xsl:value-of select="@name"/>" (
"ID" SERIAL,
PRIMARY KEY ("ID")<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">,
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>
<xsl:variable name="stereotype" select="./UML:ModelElement.stereotype/UML:Stereotype/@name"/>
"<xsl:value-of select="@name"/>"<xsl:value-of select="' '"/><xsl:variable name="UMLType" select="//UML:DataType[@xmi.id=$type]/@name"/>
<xsl:call-template name="convertTypes_DBTypes"><xsl:with-param name="typename" select="$UMLType"/><xsl:with-param name="stereotype" select="$stereotype"/></xsl:call-template>
</xsl:for-each>
) WITH OIDS;

</xsl:if>

<xsl:if test="$TargetDBType = 'MSSQL'">

exec lbDMF_DropTable '<xsl:value-of select="@name"/>';

CREATE TABLE "<xsl:value-of select="@name"/>" (
"ID" INTEGER IDENTITY (1, 1) NOT NULL,
PRIMARY KEY ("ID")<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">,
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>
<xsl:variable name="stereotype" select="./UML:ModelElement.stereotype/UML:Stereotype/@name"/>
"<xsl:value-of select="@name"/>"<xsl:value-of select="' '"/><xsl:variable name="UMLType" select="//UML:DataType[@xmi.id=$type]/@name"/>
<xsl:call-template name="convertTypes_DBTypes"><xsl:with-param name="typename" select="$UMLType"/><xsl:with-param name="stereotype" select="$stereotype"/></xsl:call-template>
</xsl:for-each>
);

</xsl:if>

<xsl:if test="$TargetDBType = 'Sqlite'">
<xsl:if test="$execute_droprules = 'yes'">
DROP TABLE "<xsl:value-of select="@name"/>";
</xsl:if>



CREATE TABLE "<xsl:value-of select="@name"/>" (
"ID" INTEGER PRIMARY KEY<xsl:for-each select="./UML:Classifier.feature/UML:Attribute">,
<xsl:variable name="type" select="./UML:StructuralFeature.type/UML:DataType/@xmi.idref"/>
<xsl:variable name="stereotype" select="./UML:ModelElement.stereotype/UML:Stereotype/@name"/>
"<xsl:value-of select="@name"/>"<xsl:value-of select="' '"/><xsl:variable name="UMLType" select="//UML:DataType[@xmi.id=$type]/@name"/>
<xsl:call-template name="convertTypes_DBTypes"><xsl:with-param name="typename" select="$UMLType"/><xsl:with-param name="stereotype" select="$stereotype"/></xsl:call-template>
</xsl:for-each>
<xsl:call-template name="ForeignColumnForClass_12"><xsl:with-param name="id" select="$classID"/></xsl:call-template>
);

</xsl:if>

    </xsl:element>
  </xsl:template>


  <xsl:template name="convertTypes_DBTypes">
    <xsl:param name="typename"/>
	<xsl:param name="stereotype"/>
<xsl:if test="$TargetDBType = 'PostgreSQL'">
    <xsl:choose>
      <xsl:when test="$typename='int'">INTEGER</xsl:when>
      <xsl:when test="$typename='float'">DECIMAL</xsl:when>
      <xsl:when test="$typename='date'">DATE</xsl:when>
      <xsl:when test="$typename='shortstring'">CHAR(20)</xsl:when>
      <xsl:when test="$typename='string'">CHAR(255)</xsl:when>
      <xsl:when test="$typename='bigstring'">bytea</xsl:when>
      <xsl:when test="$typename='bool'">bool</xsl:when>
      <xsl:when test="$typename='boolean'">bool</xsl:when>
      <xsl:when test="$typename='image'">bytea</xsl:when>
	  <xsl:otherwise>
	  <xsl:if test="$stereotype='custombinaryfield'">bytea</xsl:if>
	  <xsl:if test="$stereotype='customstringfield'">CHAR(255)</xsl:if>
	  <xsl:if test="$stereotype='custombigstringfield'">bytea</xsl:if>
	  </xsl:otherwise>
    </xsl:choose>
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
    <xsl:choose>
      <xsl:when test="$typename='int'">INTEGER</xsl:when>
      <xsl:when test="$typename='float'">DECIMAL</xsl:when>
      <xsl:when test="$typename='date'">DATE</xsl:when>
      <xsl:when test="$typename='shortstring'">CHAR(20)</xsl:when>
      <xsl:when test="$typename='string'">CHAR(255)</xsl:when>
      <xsl:when test="$typename='bigstring'">bytea</xsl:when>
      <xsl:when test="$typename='bool'">bool</xsl:when>
      <xsl:when test="$typename='boolean'">bool</xsl:when>
      <xsl:when test="$typename='image'">bytea</xsl:when>
	  <xsl:otherwise>
	  <xsl:if test="$stereotype='custombinaryfield'">bytea</xsl:if>
	  <xsl:if test="$stereotype='customstringfield'">CHAR(255)</xsl:if>
	  <xsl:if test="$stereotype='custombigstringfield'">bytea</xsl:if>
	  </xsl:otherwise>
    </xsl:choose>
</xsl:if>
<xsl:if test="$TargetDBType = 'Sqlite'">
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
	  <xsl:otherwise>
	  <xsl:if test="$stereotype='custombinaryfield'">BYTEA</xsl:if>
	  <xsl:if test="$stereotype='customstringfield'">CHAR(255)</xsl:if>
	  <xsl:if test="$stereotype='custombigstringfield'">BYTEA</xsl:if>
	  </xsl:otherwise>
    </xsl:choose>
</xsl:if>
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

<xsl:variable name="assocname" select="../../../UML:AssociationEnd[@type != $thisEndType]/@name"/>


-- Association <xsl:value-of select="$otherClassName"/> -&gt; <xsl:value-of select="$thisClassName"/> with name '<xsl:value-of select="$assocname"/>'


<xsl:if test="$assocname=''">
<xsl:if test="$TargetDBType = 'PostgreSQL'">
ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD COLUMN "<xsl:value-of select="$thisClassName"/>" INT;
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD "<xsl:value-of select="$thisClassName"/>" INT;
</xsl:if>
<xsl:if test="$TargetDBType = 'Sqlite'">
<xsl:if test="$execute_droprules = 'yes'">
--DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ins";
--DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_upd";
--DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_del";
DELETE FROM "lbDMF_ForeignKeys" WHERE 
"PKTable" = '<xsl:value-of select="$thisClassName"/>' AND
"PKColumn" = 'ID' AND
"FKTable" = '<xsl:value-of select="$otherClassName"/>' AND
"FKColumn" = '<xsl:value-of select="$thisClassName"/>';

</xsl:if>


--ALTER TABLE "<xsl:value-of select="$otherClassName"/>" 
--ADD CONSTRAINT "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ID" 
--FOREIGN KEY ( "<xsl:value-of select="$thisClassName"/>" ) 
--REFERENCES "<xsl:value-of select="$thisClassName"/>" ( "ID" );

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
-- ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD CONSTRAINT "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_ID" FOREIGN KEY ( "<xsl:value-of select="$assocname"/>" ) REFERENCES "<xsl:value-of select="$thisClassName"/>" ( "ID" );
<xsl:if test="$execute_droprules = 'yes'">
--DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ins";
--DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_upd";
--DROP TRIGGER "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_del";
DELETE FROM "lbDMF_ForeignKeys" WHERE 
"PKTable" = '<xsl:value-of select="$thisClassName"/>' AND
"PKColumn" = 'ID' AND
"FKTable" = '<xsl:value-of select="$otherClassName"/>' AND
"FKColumn" = '<xsl:value-of select="$thisClassName"/>';

</xsl:if>


--ALTER TABLE "<xsl:value-of select="$otherClassName"/>" 
--ADD CONSTRAINT "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/>_ID" 
--FOREIGN KEY ( "<xsl:value-of select="$thisClassName"/>" ) 
--REFERENCES "<xsl:value-of select="$thisClassName"/>" ( "ID" );

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
<xsl:if test="$TargetDBType = 'PostgreSQL'">
ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD COLUMN "<xsl:value-of select="$assocname"/>" INT;
ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD CONSTRAINT "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_ID" FOREIGN KEY ( "<xsl:value-of select="$assocname"/>" ) REFERENCES "<xsl:value-of select="$thisClassName"/>" ( "ID" );
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD COLUMN "<xsl:value-of select="$assocname"/>" INT;
ALTER TABLE "<xsl:value-of select="$otherClassName"/>" ADD CONSTRAINT "fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_ID" FOREIGN KEY ( "<xsl:value-of select="$assocname"/>" ) REFERENCES "<xsl:value-of select="$thisClassName"/>" ( "ID" );
</xsl:if>
</xsl:if>
</xsl:if>
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="ForeignColumnForClass_12">
    <xsl:param name="id"/>
    <!-- UML1.4: -->
    <xsl:for-each select="//UML:AssociationEnd/UML:AssociationEnd.participant/*[@xmi.idref = $id]">
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
      <xsl:variable name="otherClassName" select="//UML:Class[@xmi.id=$otherEndId]/@name"/>
	  
<xsl:if test="../../../UML:AssociationEnd[@type=$otherEndId]/@aggregation='aggregate'">,
<xsl:variable name="assocname" select="../../../UML:AssociationEnd[@type = $thisEndType]/@name"/>
<xsl:if test="$assocname=''">
"<xsl:value-of select="$otherClassName"/>" INTEGER</xsl:if>
<xsl:if test="$assocname!=''">
"<xsl:value-of select="$assocname"/>" INTEGER</xsl:if>
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

<xsl:variable name="assocname" select="../../../UML:AssociationEnd[@type != $thisEndType]/@name"/>

<xsl:if test="$TargetDBType = 'PostgreSQL'">
select dropConstraint('<xsl:value-of select="$otherClassName"/>', 'fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_ID');
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
exec  lbDMF_DropConstraint '<xsl:value-of select="$otherClassName"/>', 'fk_<xsl:value-of select="$otherClassName"/>_<xsl:value-of select="$thisClassName"/><xsl:value-of select="$assocname"/>_ID';
</xsl:if>
<xsl:if test="$TargetDBType = 'Sqlite'">
-- Drop a constraint
</xsl:if>
</xsl:if>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
