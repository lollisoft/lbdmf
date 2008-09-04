<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:xmi="http://schema.omg.org/spec/XMI/2.1">
<xsl:output method="text"/>

<xsl:template name="createDefaultStoredProcs">
    <xsl:param name="ApplicationID"/>
    <xsl:param name="ApplicationName"/>
    <xsl:param name="TargetDatabaseType"/>
    <xsl:param name="TargetDatabaseVersion"/>
	<xsl:choose>
		<xsl:when test="$TargetDatabaseType='PostgreSQL'">
-- Create default stored procedures for <xsl:value-of select="$TargetDatabaseType"/>. Version ignored.

SET SESSION AUTHORIZATION 'postgres';

DROP FUNCTION GetOrCreateApplication(varchar);
DROP FUNCTION GetFormularId(int, varchar);

CREATE OR REPLACE FUNCTION plpgsql_call_handler()
  RETURNS language_handler AS
'$libdir/plpgsql', 'plpgsql_call_handler'
  LANGUAGE 'c' VOLATILE;

-- May be a problem
--DROP LANGUAGE plpgsql;
--CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;


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

CREATE OR REPLACE FUNCTION GetOrCreateActiontype(varchar)
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
	actionid = GetOrCreateActiontype(typename);
  end if;
return actionid;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

CREATE OR REPLACE FUNCTION ConnectActionToFormular(varchar, varchar)
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
	actionid = GetOrCreateActiontype(typename);
  end if;
return actionid;
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
		</xsl:when>
		<xsl:when test="$TargetDatabaseType='Sqlite'">
-- Skip rewrite
-- To ignore this statement in the Sqlite rewrite parser. This statement should match to Sqlite syntax.
-- Create default indexes for <xsl:value-of select="$TargetDatabaseType"/>. Version ignored.

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

INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT id, lastapp FROM "users" WHERE "userid" = 'user';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'dbpass', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', 'lbDMF', id FROM "anwendungen" WHERE "name" = '<xsl:value-of select="$ApplicationName"/>';

-- Create the standard action types

INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Buttonpress', '', '');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('SQL query', 'instanceOflbSQLQueryAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open form', 'instanceOflbFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open detail form', 'instanceOflbDetailFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open master form', 'instanceOflbMasterFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open Database Report', 'instanceOflbDBReportAction', 'lbDatabaseReport');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Perform XSLT transformation', 'instanceOflbDMFXslt', 'lbDMFXslt');

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
