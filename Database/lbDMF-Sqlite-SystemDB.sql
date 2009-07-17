--
-- SQL script created for PostgreSQL
--

		
		
-- Application is lbDMF Manager. Package is lbDMF Manager
-- Create default stored procedures for PostgreSQL. Version ignored.

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
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''SQL query'', ''instanceOflbSQLQueryAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open form'', ''instanceOflbFormAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open detail form'', ''instanceOflbDetailFormAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open master form'', ''instanceOflbMasterFormAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Open Database Report'', ''instanceOflbDBReportAction'', ''lbDatabaseReport'');
		INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES (''Perform XSLT transformation'', ''instanceOflbDMFXslt'', ''lbDMFXslt'');

		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''FormValidator'', '''', '''');

		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''InitialNode'', '''', '''');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''SendSignalAction'', ''instanceOflbSendSignalAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''DecisionNode'', ''instanceOflbDecisionAction'', ''lbDatabaseForm'');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''OpaqueAction'', ''instanceOflbOpAqueOperation'', ''lbDatabaseForm'');
		INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES (''FinalNode'', '''', '''');
	end if;


	applicationid = getorcreateapplication(applicationname);
	insert into user_anwendungen (userid, anwendungenid) values (uid, applicationid);
	if applicationname = ''lbDMF Manager'' then
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBName'', ''lbDMF'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBUser'', ''dba'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBPass'', ''trainres'', applicationid);
	else
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBName'', ''lbDMF'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBUser'', ''dba'', applicationid);
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBPass'', ''trainres'', applicationid);
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
  
  
  
-- Delete application definitions if they exist. The deletion must be done in reverse order.

-- help table to not loose unused actions.
CREATE TABLE "tempactions" (
	"id"		SERIAL NOT NULL,
	"taction"	INTEGER
);

-- Works
delete from formular_parameters where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager'));
-- From here untested
insert into tempactions (taction) select action from formular_actions where formular in (select id from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager'));

delete from formular_actions where formular in (select id from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager'));

delete from action_step_transitions where src_actionid in (select id from action_steps where actionid in (select taction from tempactions)) or dst_actionid in (select id from action_steps where actionid in (select taction from tempactions));
delete from action_step_parameter where action_step_id in (select id from action_steps where actionid in (select taction from tempactions));
delete from action_parameters where actionid in (select taction from tempactions);

delete from action_steps where actionid in (select taction from tempactions);
delete from actions where id in (select taction from tempactions);
delete from tempactions;
delete from formular_parameters where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager'));
delete from anwendungen_formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager'); 
delete from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

delete from anwendungs_parameter where anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

drop table tempactions;  
		
		-- Class Benutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Benutzer');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', 'kuser.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "name", "vorname", "userid", "passwort" from "users" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Benutzer'));
insert into column_types (name, tablename, ro) values ('ID', 'Benutzer', true);


-- Association from Benutzer to AnwendungenBenutzer
-- From formular 'BOUML_0x1f402_4'
-- To   formular 'BOUML_0x1f582_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21882_0.



-- STELT_BOUML_0x21882_0
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21882_0',  (select id from action_types where bezeichnung = 'Buttonpress'), '');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for AnwendungenBenutzer', 1, 'AnwendungenBenutzer', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21882_0' and source = ''));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21882_0' and source = ''), 'action_master_detail_BOUML_0x21882_0');
UPDATE actions set name = 'AnwendungenBenutzer' where name = 'BOUML_0x21882_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Benutzer'));


		-- Class Formulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formulare');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', 'kpersonalizer.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "toolbarimage", "name", "menuname", "eventname", "menuhilfe", "anwendungid", "typ" from "formulare" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formulare'));
insert into column_types (name, tablename, ro) values ('ID', 'Formulare', true);


insert into column_types (name, tablename, specialcolumn, controltype) values ('toolbarimage', 'Formulare', true, 'toolbarimagefile');

-- Association from Formulare to Formular_Parameter
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f502_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21902_0.



-- STELT_BOUML_0x21902_0
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21902_0',  (select id from action_types where bezeichnung = 'Buttonpress'), '');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formular_Parameter', 1, 'Formular_Parameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21902_0' and source = ''));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21902_0' and source = ''), 'action_master_detail_BOUML_0x21902_0');
UPDATE actions set name = 'Formular_Parameter' where name = 'BOUML_0x21902_0';
	
-- Association from Formulare to Formularaktionenzuordnen
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f882_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21982_0.



-- STELT_BOUML_0x21982_0
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21982_0',  (select id from action_types where bezeichnung = 'Buttonpress'), '');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formularaktionenzuordnen', 1, 'Formularaktionenzuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21982_0' and source = ''));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21982_0' and source = ''), 'action_master_detail_BOUML_0x21982_0');
UPDATE actions set name = 'Formularaktionenzuordnen' where name = 'BOUML_0x21982_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formulare'));


		-- Class Formular_Parameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formular_Parameter');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', 'formular_params.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "parametername", "parametervalue", "formularid" from "formular_parameters" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formular_Parameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Formular_Parameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formular_Parameter'));


		-- Class AnwendungenBenutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'AnwendungenBenutzer');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('AnwendungenBenutzer', 'AnwendungenBenutzer verwalten', 'manageAnwendungenBenutzer', 'Edit data of AnwendungenBenutzer', 'User_application.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "userid", "anwendungenid" from "user_anwendungen" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenBenutzer'));
insert into column_types (name, tablename, ro) values ('ID', 'AnwendungenBenutzer', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenBenutzer'));


		-- Class FormulareAnwendung of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'FormulareAnwendung');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('FormulareAnwendung', 'FormulareAnwendung verwalten', 'manageFormulareAnwendung', 'Edit data of FormulareAnwendung', 'app_formulare.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "anwendungid", "formularid" from "anwendungen_formulare" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'FormulareAnwendung'));
insert into column_types (name, tablename, ro) values ('ID', 'FormulareAnwendung', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'FormulareAnwendung'));


		-- Class Anwendungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Anwendungen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', 'kthememgr.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "name", "titel", "modulename", "functor", "interface" from "anwendungen" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungen'));
insert into column_types (name, tablename, ro) values ('ID', 'Anwendungen', true);


-- Association from Anwendungen to Anwendungsparameter
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f902_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21782_0.



-- STELT_BOUML_0x21782_0
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21782_0',  (select id from action_types where bezeichnung = 'Buttonpress'), '');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungsparameter', 1, 'Anwendungsparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21782_0' and source = ''));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21782_0' and source = ''), 'action_master_detail_BOUML_0x21782_0');
UPDATE actions set name = 'Anwendungsparameter' where name = 'BOUML_0x21782_0';
	
-- Association from Anwendungen to Formulare
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21802_0.



-- STELT_BOUML_0x21802_0
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21802_0',  (select id from action_types where bezeichnung = 'Buttonpress'), '');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21802_0' and source = ''));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21802_0' and source = ''), 'action_master_detail_BOUML_0x21802_0');
UPDATE actions set name = 'Formulare' where name = 'BOUML_0x21802_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungen'));


		-- Class AnwendungenFormulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'AnwendungenFormulare');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('AnwendungenFormulare', 'AnwendungenFormulare verwalten', 'manageAnwendungenFormulare', 'Edit data of AnwendungenFormulare', 'app_formulare.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select  from "" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenFormulare'));
insert into column_types (name, tablename, ro) values ('ID', 'AnwendungenFormulare', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenFormulare'));


		-- Class Aktionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Aktionen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', 'cache.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "id", "name", "typ", "source", "target" from "actions" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionen'));
insert into column_types (name, tablename, ro) values ('ID', 'Aktionen', true);


-- Association from Aktionen to Aktionsschrittezuordnen
-- From formular 'BOUML_0x1f782_4'
-- To   formular 'BOUML_0x1f982_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21702_0.



-- STELT_BOUML_0x21702_0
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21702_0',  (select id from action_types where bezeichnung = 'Buttonpress'), '');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Aktionsschrittezuordnen', 1, 'Aktionsschrittezuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21702_0' and source = ''));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21702_0' and source = ''), 'action_master_detail_BOUML_0x21702_0');
UPDATE actions set name = 'Aktionsschrittezuordnen' where name = 'BOUML_0x21702_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionen'));


		-- Class Uebersetzungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Uebersetzungen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', 'babelfish.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "text", "translated" from "translations" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Uebersetzungen'));
insert into column_types (name, tablename, ro) values ('ID', 'Uebersetzungen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Uebersetzungen'));


		-- Class Formularaktionenzuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formularaktionenzuordnen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formularaktionenzuordnen', 'Formularaktionenzuordnen verwalten', 'manageFormularaktionenzuordnen', 'Edit data of Formularaktionenzuordnen', 'actions_formulare.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "formular", "action", "event" from "formular_actions" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formularaktionenzuordnen'));
insert into column_types (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formularaktionenzuordnen'));


		-- Class Anwendungsparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Anwendungsparameter');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', 'app_params.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "parametername", "parametervalue", "anwendungid" from "anwendungs_parameter" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungsparameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Anwendungsparameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungsparameter'));


		-- Class Aktionsschrittezuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Aktionsschrittezuordnen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', 'action_steps.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "id", "actionid", "bezeichnung", "a_order_nr", "type", "what" from "action_steps" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionsschrittezuordnen'));
insert into column_types (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionsschrittezuordnen'));


		-- Class Reportdefinitionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Reportdefinitionen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', 'print_class.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "name", "description" from "reports" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Reportdefinitionen'));
insert into column_types (name, tablename, ro) values ('ID', 'Reportdefinitionen', true);


-- Association from Reportdefinitionen to Reportparameter
-- From formular 'BOUML_0x1fa02_4'
-- To   formular 'BOUML_0x1fa82_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21a02_0.



-- STELT_BOUML_0x21a02_0
-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21a02_0',  (select id from action_types where bezeichnung = 'Buttonpress'), '');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Reportparameter', 1, 'Reportparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21a02_0' and source = ''));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21a02_0' and source = ''), 'action_master_detail_BOUML_0x21a02_0');
UPDATE actions set name = 'Reportparameter' where name = 'BOUML_0x21a02_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Reportdefinitionen'));


		-- Class Reportparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Reportparameter');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', 'kword.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "reportid", "name", "value" from "report_parameters" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Reportparameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Reportparameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Reportparameter'));


		-- Class Templates of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Templates');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Templates', 'Templates verwalten', 'manageTemplates', 'Edit data of Templates', 'antivirus.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "Cartridge", "Aproved", "Purpose", "Name" from "Templates" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Templates'));
insert into column_types (name, tablename, ro) values ('ID', 'Templates', true);


-- Create operation definitions

-- Generate validator operation 'NotEmpty' for 'Templates'

insert into actions (name, typ, source) values ('NotEmpty', (select id from action_types where bezeichnung = 'FormValidator'), 'Name,Purpose');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Validation activity for NotEmpty', 1, 'NotEmpty', (select id from action_types where bezeichnung = 'FormValidator'), (select id from action_types where bezeichnung = 'Activity'));
	
insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Templates'));


-- Activity operation for class Templates in package lbDMF Manager is NotEmpty.
-- Operation is a validator using activity 
-- Activity ID is 'BOUML_0x1f402_39'
		-- Activity 'NotEmpty' found.
			
INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('NotEmpty_BOUML_0x1f402_39', 'instanceOflbAction', 'lbDatabaseForm');

INSERT INTO "actions" ("name", "typ", "source", "target") VALUES ('NotEmpty_BOUML_0x1f402_39', (select "id" from "action_types" where "bezeichnung" = 'FormValidator'), '', '');

INSERT INTO "formular_actions" ("formular", "action", "event") VALUES ((select "id" from "formulare" where "name" = 'Templates'), (select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'eventNotEmpty_BOUML_0x1f402_39_Validator');
	
-- Create activity nodes for Sqlite

INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1f402_63', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1f482_66', '2', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1f402_56', '3', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Fehler', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f402_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f402_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Name could not be empty.', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f402_56'));

INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1f502_65', '4', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1f482_46', '5', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), 'Value {Value} in Name is ok.');
		
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('Purpose', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'));
		
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('return', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'));
		
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('Name', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'));
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1f582_66', '9', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
-- Nodetype uml:ObjectNode not known.
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1f902_56', '11', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f902_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f902_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Purpose could not be empty.', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f902_56'));

INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1fa02_66', '12', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'NotEmpty_BOUML_0x1f402_39'), 'BOUML_0x1fd82_56', '13', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1fd82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1fd82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Name is not Willi', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1fd82_56'));

-- Create activity transitions

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', 'Validate_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f402_63'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_66'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('Name == ""', 'Name is empty_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_66'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f402_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_66'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f582_66'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f402_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65'));

UPDATE "action_step_transitions" set "expression" = 'result = 0' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f402_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65');

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', 'Validation done_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_46'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65'));

UPDATE "action_step_transitions" set "expression" = 'result = 1' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_46') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65');

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('Purpose == ""', 'Purpose is empty_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f582_66'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f902_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f582_66'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1fa02_66'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', 'Return failure_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f902_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65'));

UPDATE "action_step_transitions" set "expression" = 'result = 0' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f902_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65');

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1fa02_66'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1fd82_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('Name == "Willi"', 'Is Willi_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1fa02_66'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f402_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1fd82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65'));

UPDATE "action_step_transitions" set "expression" = 'result = 0' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1fd82_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x1f502_65');

-- Rename activity nodes for Sqlite

UPDATE "action_steps" set "bezeichnung" = 'Start' where "bezeichnung" = 'BOUML_0x1f402_63';
		
UPDATE "action_steps" set "bezeichnung" = 'NameNotEmpty' where "bezeichnung" = 'BOUML_0x1f482_66';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x1f402_56';
		
UPDATE "action_steps" set "bezeichnung" = 'FinalNode' where "bezeichnung" = 'BOUML_0x1f502_65';
		
UPDATE "action_steps" set "bezeichnung" = 'StoreLogInformation' where "bezeichnung" = 'BOUML_0x1f482_46';
		
-- Nodetype uml:ActivityParameterNode not known.
		
-- Nodetype uml:ActivityParameterNode not known.
		
-- Nodetype uml:ActivityParameterNode not known.
		
UPDATE "action_steps" set "bezeichnung" = 'PurposeNotEmpty' where "bezeichnung" = 'BOUML_0x1f582_66';
		
-- Nodetype uml:ObjectNode not known.
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x1f902_56';
		
UPDATE "action_steps" set "bezeichnung" = 'MussWilliSein' where "bezeichnung" = 'BOUML_0x1fa02_66';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x1fd82_56';
		

-- Cleanup unused double types
DELETE FROM "action_types" where "id" NOT IN (SELECT "typ" from "actions") AND "id" NOT IN (SELECT "type" from "action_steps");


-- Script ready.