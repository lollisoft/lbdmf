<xsl:stylesheet 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" 
	xmlns:xmi="http://schema.omg.org/spec/XMI/2.1" 
>
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
<!-- Template to create base class file for fixed database forms -->
<xsl:import href="importUMLClassAsDMFForm.xsl"/>
<xsl:import href="importUMLApplicationTables.xsl"/>
<xsl:import href="createDefaultStoredProcs.xsl"/>
<xsl:import href="importUMLReports.xsl"/>

<xsl:import href="XMISettings.xsl"/>

<xsl:output method="text"/>

<!-- ********** Select your database target ********** -->

<!--
<xsl:variable name="DefaultDatabaseSystem" select="'MSSQL'"/>
-->
<xsl:variable name="DefaultDatabaseSystem" select="'PostgreSQL'"/>


<xsl:variable name="TargetDBType">
	<xsl:if test="$targetdatabase = 'DatabaseLayerGateway'">Sqlite</xsl:if>
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

<xsl:template match="packagedElement"> 
<xsl:value-of select="$activity"/></xsl:template>

	<xsl:template match="/">
--
-- SQL script created for <xsl:value-of select="$TargetDBType"/>
--
	
<xsl:if test="$TargetDBType = 'PostgreSQL'">
SET SESSION AUTHORIZATION 'postgres';

CREATE OR REPLACE FUNCTION plpgsql_call_handler()
  RETURNS language_handler AS
'$libdir/plpgsql', 'plpgsql_call_handler'
  LANGUAGE 'c' VOLATILE;


--DROP LANGUAGE plpgsql;

-- Activate this on a fresh database
--CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;

-- createReportTable()
--
-- This function drops a table, if it exists.

CREATE OR REPLACE FUNCTION "createReportTable"()
  RETURNS void AS
'
declare
tres text;
begin
  select tablename into tres from pg_tables where tablename = ''report'';
  if tres is null then
    execute ''
CREATE TABLE report
(
  report_id SERIAL,
  report_name text,
  report_sys boolean,
  report_source text,
  report_descrip text,
  report_grade integer NOT NULL,
  report_loaddate timestamp without time zone,
  CONSTRAINT report_pkey PRIMARY KEY (report_id)
)
WITH (OIDS=TRUE);

CREATE UNIQUE INDEX report_name_grade_idx
  ON report
  USING btree
  (report_name, report_grade);
	'';
  end if;
  return;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;




-- dropTable("varchar")
--
-- This function drops a table, if it exists.

CREATE OR REPLACE FUNCTION "dropTable"("varchar")
  RETURNS void AS
'
declare
tres text;
begin
  select tablename into tres from pg_tables where tablename = $1;
  if not tres is null then
    execute ''DROP TABLE "'' || $1 || ''" CASCADE'';
  end if;
  return;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

-- dropConstraint("varchar", "varchar")
--
-- This function drops a constraint for a table, if the table exists.

CREATE OR REPLACE FUNCTION "dropConstraint"("varchar", "varchar")
  RETURNS void AS
'
declare
tres text;
begin
  select tablename into tres from pg_tables where tablename = $1;
  if not tres is null then
    execute ''ALTER TABLE "'' || $1 || ''" DROP CONSTRAINT "'' || $2 || ''"'';
  end if;
  return;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;
</xsl:if>
<xsl:if test="$TargetDBType = 'MSSQL'">
CREATE PROCEDURE lbDMF_DropTable @Table VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP TABLE ' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('U') AND upper(pr.name) = upper(@Table)
		
	OPEN hSqlProc
	FETCH hSqlProc INTO @Statement
	WHILE (@@fetch_status = 0)
		BEGIN
			EXECUTE (@Statement)
			FETCH hSqlProc INTO @Statement
		END
	CLOSE hSqlProc
	
	DEALLOCATE hSqlProc
END

GO

CREATE  PROCEDURE lbDMF_DropProc @Proc VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP ' + case pr.xtype when 
			'P' then 'PROCEDURE ' else 'FUNCTION ' end + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('P','FN','TF') AND upper(pr.name) = upper(@Proc)
		
	OPEN hSqlProc
	FETCH hSqlProc INTO @Statement
	WHILE (@@fetch_status = 0)
		BEGIN
			EXECUTE (@Statement)
			FETCH hSqlProc INTO @Statement
		END
	CLOSE hSqlProc
	
	DEALLOCATE hSqlProc
END

GO

CREATE  PROCEDURE lbDMF_DropConstraint @Name VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP CONSTRAINT ' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('F) AND upper(pr.name) = upper(@Name)
		
	OPEN hSqlProc
	FETCH hSqlProc INTO @Statement
	WHILE (@@fetch_status = 0)
		BEGIN
			EXECUTE (@Statement)
			FETCH hSqlProc INTO @Statement
		END
	CLOSE hSqlProc
	
	DEALLOCATE hSqlProc
END

GO
</xsl:if>

<!-- Generate SQL statements to drop tables before creating them -->
<xsl:if test="$execute_droprules = 'yes'">
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']"><xsl:if test="position()!=1"><!--;--></xsl:if>
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
-- Create table model with template 'importApplicationTable'.
<xsl:if test="position()=1">;--1</xsl:if>
		<xsl:call-template name="importApplicationDropTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
-- Create table model with template 'importApplicationTable'.
<xsl:if test="position()=1">;--1</xsl:if>
		<xsl:call-template name="importApplicationDropTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
-- Unknown stereotype '<xsl:value-of select="./xmi:Extension/stereotype/@name"/>' for class <xsl:value-of select="@name"/>.
		<xsl:call-template name="importApplicationDropTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']"><xsl:if test="position()!=1"><!--;--></xsl:if>
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
-- Create table model with template 'importApplicationTable'.
<xsl:if test="position()=1">;--1</xsl:if>
		<xsl:call-template name="dropApplicationTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
-- Create table model with template 'importApplicationTable'.
<xsl:if test="position()=1">;--1</xsl:if>
		<xsl:call-template name="dropApplicationTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
-- Unknown stereotype '<xsl:value-of select="./xmi:Extension/stereotype/@name"/>' for class <xsl:value-of select="@name"/>.
		<xsl:call-template name="dropApplicationTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>
</xsl:if>


<xsl:if test="$TargetDBType = 'PostgreSQL'">
SET SESSION AUTHORIZATION 'dba';
</xsl:if>	
	
		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']"><xsl:if test="position()!=1"><!--;--></xsl:if>
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
-- Create table model with template 'importApplicationTable'.
<xsl:if test="position()=1">;--1</xsl:if>
		<xsl:call-template name="importApplicationTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='report']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFReport">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
						<xsl:with-param name="TargetReportSystem" select="'OpenRPT'"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:report']">
		-- Class <xsl:value-of select="@name"/> of type FORM found.
					<xsl:call-template name="importDMFReport">
						<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
						<xsl:with-param name="ApplicationName" select="../@name"/>
						<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
						<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
						<xsl:with-param name="TargetReportSystem" select="'OpenRPT'"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
-- Create table model with template 'importApplicationTable'.
<xsl:if test="position()=1">;--1</xsl:if>
		<xsl:call-template name="importApplicationTable">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
-- Unknown stereotype '<xsl:value-of select="./xmi:Extension/stereotype/@name"/>' for class <xsl:value-of select="@name"/>.
-- Create table via importApplicationTableAutoID
<!--
		<xsl:call-template name="importApplicationTableAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
-->
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']"><xsl:if test="position()!=1"><!--;--></xsl:if>
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
<xsl:if test="position()=1">;--1</xsl:if>
<!-- For templates above, that can generate primary keys in table definition, this here is obsolete. (As for Sqlite)-->
		<xsl:call-template name="importApplicationTablePrimaryKeys">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:form']">
-- Class <xsl:value-of select="@name"/> of type FORM found.
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:entity']">
-- Class <xsl:value-of select="@name"/> of type ENTITY found.
<xsl:if test="position()=1">;--1</xsl:if>
<!-- For templates above, that can generate primary keys in table definition, this here is obsolete. (As for Sqlite)-->
		<xsl:call-template name="importApplicationTablePrimaryKeys">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>

		<xsl:for-each select="//packagedElement[@xmi:type='uml:Class']">
			<xsl:choose>
				<xsl:when test="./xmi:Extension/stereotype[@name='form']">
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='entity']">
<xsl:if test="position()=1">;--2</xsl:if>
		<xsl:call-template name="importApplicationTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
		
			</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:form']">
				</xsl:when>
				<xsl:when test="./xmi:Extension/stereotype[@name='lbDMF:entity']">
<xsl:if test="position()=1">;--2</xsl:if>
		<xsl:call-template name="importApplicationTableRelation">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
		
			</xsl:when>
			<xsl:otherwise>
-- Unknown stereotype '<xsl:value-of select="./xmi:Extension/stereotype/@name"/>' for class <xsl:value-of select="@name"/>.
<!--<xsl:if test="position()=1">;</xsl:if>-->
		<xsl:call-template name="importApplicationTableRelationAutoID">
			<xsl:with-param name="ApplicationID" select="../@xmi:id"/>
			<xsl:with-param name="ApplicationName" select="../@name"/>
			<xsl:with-param name="TargetDatabaseType" select="$TargetDBType"/>
			<xsl:with-param name="TargetDatabaseVersion" select="$TargetDBVersion"/>
		</xsl:call-template>
</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>
<xsl:if test="$TargetDBType = 'MSSQL'">
exec lbDMF_DropProc 'lbDMF_DropTable'
GO

exec lbDMF_DropProc 'lbDMF_DropProc'
GO

</xsl:if>
	</xsl:template>
</xsl:stylesheet>
