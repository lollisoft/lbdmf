<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
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
<xsl:output method="text"/>

<xsl:template name="createDefaultStoredProcs">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
	
	<xsl:param name="database_name"/>
	<xsl:param name="database_user"/>
	<xsl:param name="database_pass"/>

	<xsl:choose>
		<xsl:when test="$TargetDatabaseType='PostgreSQL'">
-- Create default stored procedures for <xsl:value-of select="$TargetDatabaseType"/>. Version ignored.

SET SESSION AUTHORIZATION 'postgres';

--DROP FUNCTION getorCreateapplication(varchar);
--DROP FUNCTION getformularid(int, varchar);

CREATE OR REPLACE FUNCTION plpgsql_call_handler()
  RETURNS language_handler AS
'$libdir/plpgsql', 'plpgsql_call_handler'
  LANGUAGE 'c' VOLATILE;

-- May be a problem
--DROP LANGUAGE plpgsql;
--CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;


CREATE OR REPLACE FUNCTION getorcreateapplication(varchar)
  RETURNS int AS
'
declare
applicationid int;
uid int;
applicationname alias for $1;
begin
  select id into applicationid from anwendungen where name =  applicationname;
  if not applicationid is null then
    return applicationid;
  end if;
  if applicationid is null then
	insert into anwendungen (name, titel, modulename, functor, interface) values(applicationname, ''Application '' || applicationname, ''lbDynApp'', ''instanceOfApplication'', ''lb_I_Application'');

	select id into uid from users where userid = ''user'';
	if uid is null then
		INSERT INTO "users" (userid, passwort, lastapp) values (''user'', ''TestUser'', (select id FROM "anwendungen" WHERE "name" = ''lbDMF Manager''));
		INSERT INTO "formulartypen" ("handlerinterface", "namespace", "handlermodule", "handlerfunctor", "beschreibung") VALUES (''lb_I_DatabaseForm'','''',''-'','''',''Dynamisch aufgebautes Datenbankformular'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Buttonpress'', '''', '''');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''SQL query'', ''instanceOflbSQLQueryAction'', ''lbWorkflowEngine'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open form'', ''instanceOflbFormAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open detail form'', ''instanceOflbDetailFormAction'', ''lbWorkflowEngine'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open master form'', ''instanceOflbMasterFormAction'', ''lbWorkflowEngine'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''CreateReport'', ''instanceOflbExecuteAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open Database Report'', ''instanceOflbDBReportAction'', ''lbDatabaseReport'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Perform XSLT transformation'', ''instanceOflbDMFXslt'', ''lbDMFXslt'');

		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''FormValidator'', '''', '''');

		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''InitialNode'', '''', '''');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''SendSignalAction'', ''instanceOflbSendSignalAction'', ''lbDMFBasicActionSteps'');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''DecisionNode'', ''instanceOflbDecisionAction'', ''lbDMFBasicActionSteps'');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''OpaqueAction'', ''instanceOflbOpAqueOperation'', ''lbWorkflowEngine'');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''FinalNode'', '''', '''');
	end if;


	applicationid = getorcreateapplication(applicationname);
	insert into user_anwendungen (userid, anwendungenid) values (uid, applicationid);
	if applicationname = ''lbDMF Manager'' then
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBName'', ''lbDMF'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBUser'', ''dba'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBPass'', ''trainres'', applicationid);
	else
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBName'', ''<xsl:value-of select="$database_name"/>'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBUser'', ''<xsl:value-of select="$database_user"/>'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBPass'', ''<xsl:value-of select="$database_pass"/>'', applicationid);
	end if;
  end if;
return applicationid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

CREATE OR REPLACE FUNCTION getorcreateactiontype(varchar)
  RETURNS int AS
'
declare
actionid int;
typename alias for $1;
begin
  select id into actionid from action_types where module = typename and action_handler = ''instanceOf'' || typename;
  if not actionid is null then
    return actionid;
  end if;
  if actionid is null then
	insert into action_types (bezeichnung, module, action_handler) values(''Action of type '' || typename, typename, ''instanceOf'' || typename);
	actionid = "getorcreateactiontype"(typename);
  end if;
return actionid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

CREATE OR REPLACE FUNCTION connectactiontoformular(varchar, varchar)
  RETURNS int AS
'
declare
actionid int;
action alias for $1;
formular alias for $2;
begin
  select id into actionid from action_types where module = typename and action_handler = ''instanceOf'' || typename;
  if not actionid is null then
    return actionid;
  end if;
  if actionid is null then
	insert into action_types (bezeichnung, module, action_handler) values(''Action of type '' || typename, typename, ''instanceOf'' || typename);
	actionid = "getorcreateactiontype"(typename);
  end if;
return actionid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

CREATE OR REPLACE FUNCTION "dropformular"("varchar", "varchar")
  RETURNS bool AS
'
declare appid int;
declare formid int;
declare appname alias for $1;
declare formname alias for $2;
begin
	select id into appid from anwendungen where name = appname;
	select id into formid from formulare where name = formname and anwendungid = appid;

	delete from formular_parameters where formularid = formid;
	delete from anwendungen_formulare where anwendungid = appid and formularid = formid;
	delete from formular_actions where formular = formid;
	delete from formulare where anwendungid = appid and id = formid;
	delete from foreignkey_visibledata_mapping where fktable = formname;

	return true;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;


CREATE OR REPLACE FUNCTION getformularid(int, varchar)
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
  
CREATE OR REPLACE FUNCTION "createReportTable"()
  RETURNS void AS
$BODY$
declare
tres text;
begin
  select tablename into tres from pg_tables where tablename = 'report';
  if tres is null then
    execute '
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
	';
  end if;
  return;
end;
$BODY$
  LANGUAGE 'plpgsql' VOLATILE
  COST 100;
ALTER FUNCTION "createReportTable"() OWNER TO postgres;
  
  
-- Delete application definitions if they exist. The deletion must be done in reverse order.

-- help table to not loose unused actions.
CREATE TABLE "tempactions" (
	"id"		SERIAL NOT NULL,
	"taction"	INTEGER
);

-- Works
delete from formular_parameters where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
-- From here untested
insert into tempactions (taction) select action from formular_actions where formular in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));

delete from formular_actions where formular in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));

delete from action_step_transitions where src_actionid in (select id from action_steps where actionid in (select taction from tempactions)) or dst_actionid in (select id from action_steps where actionid in (select taction from tempactions));
delete from action_step_parameter where action_step_id in (select id from action_steps where actionid in (select taction from tempactions));
delete from action_parameters where actionid in (select taction from tempactions);

delete from action_steps where actionid in (select taction from tempactions);
delete from actions where id in (select taction from tempactions);
delete from tempactions;
delete from formular_parameters where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
delete from anwendungen_formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'); 
delete from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

delete from anwendungs_parameter where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');
delete from user_anwendungen where anwendungenid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');
update users set lastapp = NULL where lastapp in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');
delete from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>';

drop table tempactions;  
		</xsl:when>
		<xsl:when test="$TargetDatabaseType='Sqlite'">
-- Skip rewrite
-- To ignore this statement in the Sqlite rewrite parser. This statement should match to Sqlite syntax.
-- Create default indexes for <xsl:value-of select="$TargetDatabaseType"/>. Version ignored.
-- Using database settings as of name=<xsl:value-of select="$database_name"/>, user=<xsl:value-of select="$database_user"/>

CREATE UNIQUE INDEX IF NOT EXISTS "idx_users_userid" on "users" (userid);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formulartypen_hi_ns" on "formulartypen" (handlerinterface, namespace, handlermodule);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_anwendungen_name" on "anwendungen" (name);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formulare_name" on "formulare" (anwendungid, name);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formular_parameter" on "formular_parameters" (formularid, parametername);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_anwendungs_parameter" on "anwendungs_parameter" (anwendungid, parametername);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_column_types" on "column_types" (name, tablename);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_user_anwendungen" on "user_anwendungen" (userid, anwendungenid);

INSERT OR IGNORE INTO "formulartypen" ("handlerinterface", "namespace", "handlermodule", "handlerfunctor", "beschreibung") VALUES ('lb_I_DatabaseForm','','-','','Dynamisch aufgebautes Datenbankformular');

INSERT OR IGNORE INTO "anwendungen" ("name", "titel", "modulename", "functor", "interface") values('<xsl:value-of select="$ApplicationName"/>', 'Application <xsl:value-of select="$ApplicationName"/>', 'lbDynApp', 'instanceOfApplication', 'lb_I_Application');

INSERT OR IGNORE INTO "users" (userid, passwort, lastapp) SELECT 'user', 'TestUser', id  FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';

-- Create the standard action types

INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Buttonpress', '', '');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('SQL query', 'instanceOflbSQLQueryAction', 'lbWorkflowEngine');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open form', 'instanceOflbFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open detail form', 'instanceOflbDetailFormAction', 'lbWorkflowEngine');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open master form', 'instanceOflbMasterFormAction', 'lbWorkflowEngine');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open Database Report', 'instanceOflbDBReportAction', 'lbDatabaseReport');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Perform XSLT transformation', 'instanceOflbDMFXslt', 'lbDMFXslt');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open application', 'instanceOflbExecuteAction', 'lbDatabaseForm');

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('FormValidator', '', '');

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('InitialNode', '', '');
INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('SendSignalAction', 'instanceOflbSendSignalAction', 'lbDMFBasicActionSteps');
INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('DecisionNode', 'instanceOflbDecisionAction', 'lbDMFBasicActionSteps');
INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('OpaqueAction', 'instanceOflbOpAqueOperation', 'lbWorkflowEngine');
INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('FinalNode', '', '');


-- Delete application definitions if they exist. The deletion must be done in reverse order.

-- help table to not loose unused actions.
CREATE TABLE IF NOT EXISTS "tempactions" (
	"id"		INTEGER PRIMARY KEY,
	"taction"	INTEGER
);

-- Works
delete from formular_parameters where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
-- From here untested
insert into tempactions (taction) select action from formular_actions where formular in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));

delete from formular_actions where formular in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));

delete from action_step_transitions where src_actionid in (select id from action_steps where actionid in (select taction from tempactions)) or dst_actionid in (select id from action_steps where actionid in (select taction from tempactions));
delete from action_step_parameter where action_step_id in (select id from action_steps where actionid in (select taction from tempactions));
delete from action_parameters where actionid in (select taction from tempactions);

delete from action_steps where actionid in (select taction from tempactions);
delete from actions where id in (select taction from tempactions);
delete from tempactions;
delete from formular_parameters where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));
delete from anwendungen_formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'); 

-- Delete database schema information
delete from dbforeignkey where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>')); 
delete from dbprimarykey where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>')); 
delete from dbcolumn where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>')); 
delete from dbtable where anwendungenid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'); 

-- delete formularfields
delete from formularfields where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>'));

delete from formulare where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

delete from anwendungs_parameter where anwendungid in (select id from anwendungen where name = '<xsl:value-of select="$ApplicationName"/>');

INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT users.id,anwendungen.id FROM "users" inner join anwendungen where anwendungen.name = '<xsl:value-of select="$ApplicationName"/>';
<xsl:if test="$ApplicationName = 'lbDMF Manager'">
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'trainres', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', 'lbDMF', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
</xsl:if>
<xsl:if test="$ApplicationName != 'lbDMF Manager'">
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', '<xsl:value-of select="$database_user"/>', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', '<xsl:value-of select="$database_pass"/>', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', '<xsl:value-of select="$database_name"/>', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
</xsl:if>
drop table tempactions;

		</xsl:when>
		<xsl:when test="$TargetDatabaseType='MSSQL'">
-- Create default stored procedures for <xsl:value-of select="$TargetDatabaseType"/>. Version ignored.

CREATE PROCEDURE DropTable @Table VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP TABLE ' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('U') AND upper(pr.name) = upper(@Proc)
		
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

CREATE  PROCEDURE DropProc @Proc VARCHAR(50)
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

CREATE  PROC createapplication(@FNName varchar) AS
BEGIN
  declare @applicationid int;
  declare @uid int;
  declare @applicationname char(100);

  set @applicationname = @FNName;
  set @applicationid = (select id from anwendungen where name = @applicationname);
  if @applicationid is null
  begin
	insert into anwendungen 
	(name, titel, modulename, functor, interface) values(@applicationname, 'Application ' + @applicationname, 'lbDynApp', 'instanceOfApplication', 'lb_I_Application');
	set @uid = (select id from users where userid = 'user')
	if @uid is null 
    begin
		declare @appid as int
		set @appid = (select id FROM "anwendungen" WHERE "name" = 'lbDMF Manager');
		INSERT INTO "users" (userid, passwort, lastapp) values ('user', 'TestUser', @appid);
		INSERT INTO "formulartypen" ("handlerinterface", "namespace", "handlermodule", "handlerfunctor", "beschreibung") VALUES ('lb_I_DatabaseForm','','-','','Dynamisch aufgebautes Datenbankformular');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Buttonpress', '', '');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('SQL query', 'instanceOflbSQLQueryAction', 'lbDatabaseForm');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open form', 'instanceOflbFormAction', 'lbDatabaseForm');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open detail form', 'instanceOflbDetailFormAction', 'lbDatabaseForm');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open master form', 'instanceOflbMasterFormAction', 'lbDatabaseForm');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open Database Report', 'instanceOflbDBReportAction', 'lbDatabaseReport');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Perform XSLT transformation', 'instanceOflbDMFXslt', 'lbDMFXslt');
    end


	--set @applicationid = getorcreateapplication(@applicationname);
	insert into user_anwendungen (userid, anwendungenid) values (1, @applicationid);
	if @applicationname = 'lbDMF Manager' 
    begin
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DBName', 'lbDMF', @applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DBUser', 'dba', @applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DBPass', 'trainres', @applicationid);
	end
	if @applicationname != 'lbDMF Manager' 
    begin
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DBName', '<xsl:value-of select="$database_name"/>', @applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DBUser', '<xsl:value-of select="$database_user"/>', @applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DBPass', '<xsl:value-of select="$database_pass"/>', @applicationid);
	end
  end
end

GO


CREATE PROC getapplication(@FNName varchar) AS
BEGIN
  declare @applicationid int;
  declare @uid int;
  declare @applicationname char(100);

  set @applicationname = @FNName;
  set @applicationid = (select id from anwendungen where name = @applicationname);
  if not @applicationid is null 
  begin
    return @applicationid
  end
  if @applicationid is null
  begin
	exec ('exec createapplication ' + @FNName)
  end
  set @applicationid = ('exec getapplication ' + @FNName)
  Select @applicationid
end

GO


/*
CREATE FUNCTION getorcreateactiontype(varchar)
  RETURNS int AS
'
declare
actionid int;
typename alias for $1;
begin
  select id into actionid from action_types where module = typename and action_handler = ''instanceOf'' || typename;
  if not actionid is null then
    return actionid;
  end if;
  if actionid is null then
	insert into action_types (bezeichnung, module, action_handler) values(''Action of type '' || typename, typename, ''instanceOf'' || typename);
	actionid = getorcreateactiontype"(typename);
  end if;
return actionid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

CREATE OR REPLACE FUNCTION connectactiontoformular(varchar, varchar)
  RETURNS int AS
'
declare
actionid int;
action alias for $1;
formular alias for $2;
begin
  select id into actionid from action_types where module = typename and action_handler = ''instanceOf'' || typename;
  if not actionid is null then
    return actionid;
  end if;
  if actionid is null then
	insert into action_types (bezeichnung, module, action_handler) values(''Action of type '' || typename, typename, ''instanceOf'' || typename);
	actionid = "getorcreateactiontype"(typename);
  end if;
return actionid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

CREATE OR REPLACE FUNCTION "dropformular"("varchar", "varchar")
  RETURNS bool AS
'
declare appid int;
declare formid int;
declare appname alias for $1;
declare formname alias for $2;
begin
	select id into appid from anwendungen where name = appname;
	select id into formid from formulare where name = formname and anwendungid = appid;

	delete from formular_parameters where formularid = formid;
	delete from anwendungen_formulare where anwendungid = appid and formularid = formid;
	delete from formular_actions where formular = formid;
	delete from formulare where anwendungid = appid and id = formid;

	return true;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;


CREATE OR REPLACE FUNCTION getformularid(int, varchar)
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
*/
		</xsl:when>
		<xsl:otherwise>
-- Error: Target database '<xsl:value-of select="$TargetDatabaseType"/>' does not support stored procedures.
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>


	<!--<xsl:template match="XMI.content">
	    <xsl:apply-templates/>
	</xsl:template>-->
</xsl:stylesheet>
