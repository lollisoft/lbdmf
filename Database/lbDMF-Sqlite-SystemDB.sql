
-- Params XSLDatabaseBackendSystem: 
-- Params XSLDatabaseBackendApplication: 
-- Params overwriteDatabase: 

-- Params targetdatabase generated: Sqlite

--
-- SQL script created for Sqlite
--

		
		
-- Application is lbDMF Manager. Package is lbDMF Manager
-- Using database settings as of name=lbDMF, user=dbuser
-- Skip rewrite
-- To ignore this statement in the Sqlite rewrite parser. This statement should match to Sqlite syntax.
-- Create default indexes for Sqlite. Version ignored.
-- Using database settings as of name=lbDMF, user=dbuser

CREATE UNIQUE INDEX IF NOT EXISTS "idx_users_userid" on "users" (userid);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formulartypen_hi_ns" on "formulartypen" (handlerinterface, namespace, handlermodule);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_anwendungen_name" on "anwendungen" (name);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formulare_name" on "formulare" (anwendungid, name);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formular_parameter" on "formular_parameters" (formularid, parametername);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_anwendungs_parameter" on "anwendungs_parameter" (anwendungid, parametername);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_column_types" on "column_types" (name, tablename);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_user_anwendungen" on "user_anwendungen" (userid, anwendungenid);

INSERT OR IGNORE INTO "formulartypen" ("handlerinterface", "namespace", "handlermodule", "handlerfunctor", "beschreibung") VALUES ('lb_I_DatabaseForm','','-','','Dynamisch aufgebautes Datenbankformular');

INSERT OR IGNORE INTO "anwendungen" ("name", "titel", "modulename", "functor", "interface") values('lbDMF Manager', 'Application lbDMF Manager', 'lbDynApp', 'instanceOfApplication', 'lb_I_Application');

INSERT OR IGNORE INTO "users" (userid, passwort, lastapp) SELECT 'user', 'TestUser', id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager';

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

INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT users.id,anwendungen.id FROM "users" inner join anwendungen where anwendungen.name = 'lbDMF Manager';

INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'trainres', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', 'lbDMF', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';

drop table tempactions;

		
		-- Class Benutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Benutzer');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', 'kuser.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for users (BOUML_0x1f402_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "passwort", "userid", "vorname", "name" from "users"', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'passwort', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'userid', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'vorname', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Benutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Benutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Benutzer', 1);


-- Association from Benutzer to AnwendungenBenutzer
-- From formular 'BOUML_0x1f402_4'
-- To   formular 'BOUML_0x1f582_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21782_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x21782_0', 1, 'userid');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for AnwendungenBenutzer', 1, 'AnwendungenBenutzer', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21782_0' and source = 'userid'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21782_0' and source = 'userid'), 'action_master_detail_BOUML_0x21782_0');
UPDATE actions set name = 'AnwendungenBenutzer' where name = 'BOUML_0x21782_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class DBType of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'DBType');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'DBType', 'DBType verwalten', 'manageDBType', 'Edit data of DBType', 'field_types.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for dbtype (BOUML_0x24b82_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "description" from "dbtype"', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'dbtype', 0, 'String', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'dbtype', 0, 'String', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'DBType', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'DBType', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'DBType', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'DBType' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FormularFields of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'FormularFields');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularFields', 'FormularFields verwalten', 'manageFormularFields', 'Edit data of FormularFields', 'formular_field.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'formularid', 'formulare', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'dbtypeid', 'dbtype', 'name');


-- Create query for formularfields (BOUML_0x24b02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "dbtype", "tablename", "isfk", "fkname", "fktable", "formularid", "dbtypeid" from "formularfields"', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'dbtype', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'isfk', 'formularfields', 0, 'Bit', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkname', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fktable', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f482_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'formularfields', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f482_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtypeid', 'formularfields', 1, 'name', 'dbtype', 'Integer', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormularFields', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormularFields', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormularFields', 1);


-- Association from FormularFields to DBType
-- From formular 'BOUML_0x24b02_4'
-- To   formular 'BOUML_0x24b82_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x25f02_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x25f02_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for DBType', 1, 'DBType', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x25f02_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x25f02_0' and source = 'name'), 'action_master_detail_BOUML_0x25f02_0');
UPDATE actions set name = 'DBType' where name = 'BOUML_0x25f02_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formulare');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', 'kpersonalizer.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'anwendungid', 'anwendungen', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'typ', 'formulartypen', 'beschreibung');


-- Create query for formulare (BOUML_0x1f482_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "menuname", "menuhilfe", "eventname", "toolbarimage", "anwendungid", "typ" from "formulare"', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'menuname', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'menuhilfe', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'eventname', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'toolbarimage', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f682_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'formulare', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f682_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'typ', 'formulare', 1, 'name', 'formulartypen', 'Integer', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formulare', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formulare', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formulare', 1);


INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('toolbarimage', 'Formulare', 1, 'toolbarimagefile');

-- Association from Formulare to Formular_Parameter
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f502_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21802_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x21802_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formular_Parameter', 1, 'Formular_Parameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21802_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21802_0' and source = 'name'), 'action_master_detail_BOUML_0x21802_0');
UPDATE actions set name = 'Formular_Parameter' where name = 'BOUML_0x21802_0';
	
-- Association from Formulare to Formularaktionenzuordnen
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f802_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21882_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x21882_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formularaktionenzuordnen', 1, 'Formularaktionenzuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21882_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21882_0' and source = 'name'), 'action_master_detail_BOUML_0x21882_0');
UPDATE actions set name = 'Formularaktionenzuordnen' where name = 'BOUML_0x21882_0';
	
-- Association from Formulare to FormularFields
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x24b02_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x25e02_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x25e02_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for FormularFields', 1, 'FormularFields', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x25e02_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x25e02_0' and source = 'name'), 'action_master_detail_BOUML_0x25e02_0');
UPDATE actions set name = 'FormularFields' where name = 'BOUML_0x25e02_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Anwendungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Anwendungen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', 'kthememgr.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for anwendungen (BOUML_0x1f682_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "titel", "name", "interface", "functor", "modulename" from "anwendungen"', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'titel', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'interface', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'functor', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'modulename', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungen', 1);


-- Association from Anwendungen to Anwendungsparameter
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f882_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21682_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x21682_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungsparameter', 1, 'Anwendungsparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21682_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21682_0' and source = 'name'), 'action_master_detail_BOUML_0x21682_0');
UPDATE actions set name = 'Anwendungsparameter' where name = 'BOUML_0x21682_0';
	
-- Association from Anwendungen to Formulare
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21702_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x21702_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21702_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21702_0' and source = 'name'), 'action_master_detail_BOUML_0x21702_0');
UPDATE actions set name = 'Formulare' where name = 'BOUML_0x21702_0';
	

-- Create operation definitions

-- Generate codegeneration operation 'Codegenerieren' for 'Anwendungen'

INSERT OR IGNORE INTO "actions" (name, typ, source) VALUES ('Codegenerieren', (select id from action_types where bezeichnung = 'Buttonpress'), 'name');
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, '', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Codegenerieren'));
INSERT OR IGNORE INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = 'Anwendungen'), (select id from actions where name = 'Codegenerieren'), 'evt_Anwendungen_Codegenerieren');

	
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formular_Parameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formular_Parameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', 'formular_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_parameters', 'formularid', 'formulare', 'name');


-- Create query for formular_parameters (BOUML_0x1f502_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername", "formularid" from "formular_parameters"', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'formular_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'formular_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f482_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'formular_parameters', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formular_Parameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formular_Parameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formular_Parameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formular_Parameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class AnwendungenBenutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'AnwendungenBenutzer');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'AnwendungenBenutzer', 'AnwendungenBenutzer verwalten', 'manageAnwendungenBenutzer', 'Edit data of AnwendungenBenutzer', 'User_application.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'userid', 'users', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'anwendungenid', 'anwendungen', 'name');


-- Create query for user_anwendungen (BOUML_0x1f582_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "userid", "anwendungenid" from "user_anwendungen"', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- otherClassID BOUML_0x1f402_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'userid', 'user_anwendungen', 1, 'userid', 'users', 'Integer', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f402_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungenid', 'user_anwendungen', 1, 'anwendungenid', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'AnwendungenBenutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'AnwendungenBenutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'AnwendungenBenutzer', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'AnwendungenBenutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FormulareAnwendung of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'FormulareAnwendung');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormulareAnwendung', 'FormulareAnwendung verwalten', 'manageFormulareAnwendung', 'Edit data of FormulareAnwendung', 'app_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'anwendungid', 'anwendungen', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'formularid', 'formulare', 'name');


-- Create query for anwendungen_formulare (BOUML_0x1f602_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungid", "formularid", "purpose" from "anwendungen_formulare"', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- otherClassID 	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'anwendungen_formulare', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID 	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'anwendungen_formulare', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'purpose', 'anwendungen_formulare', 0, 'String', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormulareAnwendung', 1);


-- Association from FormulareAnwendung to Formulare
-- From formular 'BOUML_0x1f602_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29402_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x29402_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x29402_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x29402_0' and source = 'name'), 'action_master_detail_BOUML_0x29402_0');
UPDATE actions set name = 'Formulare' where name = 'BOUML_0x29402_0';
	
-- Association from FormulareAnwendung to Anwendungen
-- From formular 'BOUML_0x1f602_4'
-- To   formular 'BOUML_0x1f682_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29482_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x29482_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungen', 1, 'Anwendungen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x29482_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x29482_0' and source = 'name'), 'action_master_detail_BOUML_0x29482_0');
UPDATE actions set name = 'Anwendungen' where name = 'BOUML_0x29482_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Aktionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Aktionen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', 'cache.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'typ', 'action_types', 'bezeichnung');


-- Create query for actions (BOUML_0x1f702_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "target", "source", "name", "typ" from "actions"', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'target', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'source', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID 	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'typ', 'actions', 1, 'name', 'action_types', 'Integer', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Aktionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionen', 1);


-- Association from Aktionen to Aktionsschrittezuordnen
-- From formular 'BOUML_0x1f702_4'
-- To   formular 'BOUML_0x1f902_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21602_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x21602_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Aktionsschrittezuordnen', 1, 'Aktionsschrittezuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21602_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21602_0' and source = 'name'), 'action_master_detail_BOUML_0x21602_0');
UPDATE actions set name = 'Aktionsschrittezuordnen' where name = 'BOUML_0x21602_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Uebersetzungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Uebersetzungen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', 'babelfish.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for translations (BOUML_0x1f782_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "translated", "text" from "translations"', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'translated', 'translations', 0, 'String', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'text', 'translations', 0, 'String', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Uebersetzungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Uebersetzungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Uebersetzungen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Uebersetzungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formularaktionenzuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formularaktionenzuordnen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formularaktionenzuordnen', 'Formularaktionenzuordnen verwalten', 'manageFormularaktionenzuordnen', 'Edit data of Formularaktionenzuordnen', 'actions_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'action', 'actions', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'formular', 'formulare', 'name');


-- Create query for formular_actions (BOUML_0x1f802_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "event", "action", "formular" from "formular_actions"', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'event', 'formular_actions', 0, 'String', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f482_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'action', 'formular_actions', 1, 'name', 'actions', 'Integer', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f482_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formular', 'formular_actions', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formularaktionenzuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formularaktionenzuordnen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formularaktionenzuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Anwendungsparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Anwendungsparameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', 'app_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungs_parameter', 'anwendungid', 'anwendungen', 'name');


-- Create query for anwendungs_parameter (BOUML_0x1f882_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername", "anwendungid" from "anwendungs_parameter"', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'anwendungs_parameter', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'anwendungs_parameter', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f682_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'anwendungs_parameter', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungsparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungsparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungsparameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungsparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Aktionsschrittezuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Aktionsschrittezuordnen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', 'action_steps.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'type', 'action_types', 'bezeichnung');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'actionid', 'actions', 'name');


-- Create query for action_steps (BOUML_0x1f902_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "bezeichnung", "what", "a_order_nr", "type", "actionid" from "action_steps"', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'bezeichnung', 'action_steps', 0, 'String', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'what', 'action_steps', 0, 'String', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'a_order_nr', 'action_steps', 0, 'Integer', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f702_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'type', 'action_steps', 1, 'name', 'action_types', 'Integer', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f702_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'actionid', 'action_steps', 1, 'name', 'actions', 'Integer', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Aktionsschrittezuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionsschrittezuordnen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionsschrittezuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Reportdefinitionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Reportdefinitionen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', 'print_class.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for reports (BOUML_0x1f982_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "description", "name" from "reports"', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'reports', 0, 'String', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'reports', 0, 'String', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Reportdefinitionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Reportdefinitionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Reportdefinitionen', 1);


-- Association from Reportdefinitionen to Reportparameter
-- From formular 'BOUML_0x1f982_4'
-- To   formular 'BOUML_0x1fa02_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21902_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x21902_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Reportparameter', 1, 'Reportparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21902_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21902_0' and source = 'name'), 'action_master_detail_BOUML_0x21902_0');
UPDATE actions set name = 'Reportparameter' where name = 'BOUML_0x21902_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Reportparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Reportparameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', 'kword.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_parameters', 'reportid', 'reports', 'name');


-- Create query for report_parameters (BOUML_0x1fa02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "value", "name", "reportid" from "report_parameters"', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'value', 'report_parameters', 0, 'Integer', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'report_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- otherClassID BOUML_0x1f982_4	
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'reportid', 'report_parameters', 1, 'name', 'reports', 'Integer', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Reportparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Reportparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Reportparameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FormularTypen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'FormularTypen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularTypen', 'FormularTypen verwalten', 'manageFormularTypen', 'Edit data of FormularTypen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for formulartypen (BOUML_0x26502_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "handlername", "handlerfunctor", "handlerintarface", "namespace", "beschreibung" from "formulartypen"', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'handlername', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'handlerfunctor', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'handlerintarface', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'namespace', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'beschreibung', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormularTypen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormularTypen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormularTypen', 1);


-- Association from FormularTypen to Formulare
-- From formular 'BOUML_0x26502_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29582_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (name, typ, source) values ('BOUML_0x29582_0', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x29582_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormularTypen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x29582_0' and source = 'name'), 'action_master_detail_BOUML_0x29582_0');
UPDATE actions set name = 'Formulare' where name = 'BOUML_0x29582_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularTypen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


-- Activity operation for class Anwendungen in package lbDMF Manager is GenerateTurboVision.
-- Operation is a validator using activity 
-- Activity ID is 'BOUML_0x20e02_39'
		-- Activity 'GenerateTurboVision' found.
			
-- Generate statemachine for BOUML_0x20e02_39
-- select "CreateActivityOnMissing"('BOUML_0x20e02_39', 'GenerateTurboVision');

-- Delete old statemachine
delete from "action_step_parameter" where "action_step_id" in (select id from "action_steps" where "actionid" in (select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'));
delete from "action_step_transitions" where "description" = '_BOUML_0x20e02_39';
delete from "action_steps" where "actionid" in (select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39');
delete from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39';



-- A form validator should be used before saving the changes to the database

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('GenerateTurboVision_BOUML_0x20e02_39', 'instanceOflbAction', 'lbDatabaseForm');

INSERT OR IGNORE INTO "actions" ("name", "typ", "source", "target") VALUES ('GenerateTurboVision_BOUML_0x20e02_39', (select "id" from "action_types" where "bezeichnung" = 'Buttonpress'), 'name', '');

INSERT OR IGNORE INTO "formular_actions" ("formular", "action", "event") VALUES ((select "id" from "formulare" where "name" = 'Anwendungen'), (select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'eventGenerateTurboVision_BOUML_0x20e02_39_Buttonpress');
	
-- Create activity nodes for Sqlite

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x22982_70', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x22a02_72', '2', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x24202_56', '3', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', './wxWrapper.app/Contents/Resources/XSLT/TurboVision/gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x24302_56', '4', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('SaveApplicationID', '{SaveApplicationID}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'exportApplicationToXMLBuffer', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x25c82_56', '5', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'writeStringToFile', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{memorybuffer}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x28f82_56', '6', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Info', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Only Mac, Windows and Unix flavoured machines are supported.', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x29002_56', '7', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '\develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\XSLT_Templates\TurboVision\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x29082_56', '8', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '/usr/share/lbdmf/TurboVision/gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x29102_46', '9', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x2aa82_56', '10', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Operating system and selected application...', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Os Type is {OSType}. ApplicationId is {SaveApplicationID}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x24382_73', '11', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x24402_73', '12', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x24482_73', '13', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x2c402_56', '14', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'fileExists', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '\\develop\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\TurboVision\\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x25e02_73', '15', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'GenerateTurboVision_BOUML_0x20e02_39'), 'BOUML_0x2c482_56', '16', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '\lbDMF\XSLT\TurboVision\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

-- Create activity transitions

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22982_70'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

UPDATE "action_step_transitions" set "expression" = 'file = lala.xml' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22a02_72'));

UPDATE "action_step_transitions" set "expression" = 'result = 1' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22a02_72');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Unix"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Mac"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Windows"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('result == 1', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('result == 0', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

-- Rename activity nodes for Sqlite

UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x22982_70';
		
UPDATE "action_steps" set "bezeichnung" = 'FinalNode' where "bezeichnung" = 'BOUML_0x22a02_72';
		
UPDATE "action_steps" set "bezeichnung" = 'transformXSLT' where "bezeichnung" = 'BOUML_0x24202_56';
		
UPDATE "action_steps" set "bezeichnung" = 'exportApplicationToXMLBuffer' where "bezeichnung" = 'BOUML_0x24302_56';
		
UPDATE "action_steps" set "bezeichnung" = 'writeStringToFile' where "bezeichnung" = 'BOUML_0x25c82_56';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x28f82_56';
		
UPDATE "action_steps" set "bezeichnung" = 'transformXSLT' where "bezeichnung" = 'BOUML_0x29002_56';
		
UPDATE "action_steps" set "bezeichnung" = 'transformXSLT' where "bezeichnung" = 'BOUML_0x29082_56';
		
UPDATE "action_steps" set "bezeichnung" = 'NOP' where "bezeichnung" = 'BOUML_0x29102_46';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x2aa82_56';
		
UPDATE "action_steps" set "bezeichnung" = 'Unix' where "bezeichnung" = 'BOUML_0x24382_73';
		
UPDATE "action_steps" set "bezeichnung" = 'Mac' where "bezeichnung" = 'BOUML_0x24402_73';
		
UPDATE "action_steps" set "bezeichnung" = 'Windows' where "bezeichnung" = 'BOUML_0x24482_73';
		
UPDATE "action_steps" set "bezeichnung" = 'fileExists' where "bezeichnung" = 'BOUML_0x2c402_56';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x25e02_73';
		
UPDATE "action_steps" set "bezeichnung" = 'transformXSLT' where "bezeichnung" = 'BOUML_0x2c482_56';
		

-- Cleanup unused double types
DELETE FROM "action_types" where "id" NOT IN (SELECT "typ" from "actions") AND "id" NOT IN (SELECT "type" from "action_steps");


-- Activity operation for class Anwendungen in package lbDMF Manager is actValidateAnwendungen.
-- Operation is a validator using activity 
-- Activity ID is 'BOUML_0x1f482_39'
		-- Activity 'actValidateAnwendungen' found.
			
-- Generate statemachine for BOUML_0x1f482_39
-- select "CreateActivityOnMissing"('BOUML_0x1f482_39', 'actValidateAnwendungen');

-- Delete old statemachine
delete from "action_step_parameter" where "action_step_id" in (select id from "action_steps" where "actionid" in (select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'));
delete from "action_step_transitions" where "description" = '_BOUML_0x1f482_39';
delete from "action_steps" where "actionid" in (select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39');
delete from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39';



-- A form validator should be used before saving the changes to the database

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('actValidateAnwendungen_BOUML_0x1f482_39', 'instanceOflbAction', 'lbDatabaseForm');

INSERT OR IGNORE INTO "actions" ("name", "typ", "source", "target") VALUES ('actValidateAnwendungen_BOUML_0x1f482_39', (select "id" from "action_types" where "bezeichnung" = 'FormValidator'), 'name', '');

INSERT OR IGNORE INTO "formular_actions" ("formular", "action", "event") VALUES ((select "id" from "formulare" where "name" = 'Anwendungen'), (select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'eventactValidateAnwendungen_BOUML_0x1f482_39_FormValidator');
	
-- Create activity nodes for Sqlite

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20d82_70', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20e02_73', '2', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20e82_72', '3', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20f02_73', '4', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20f82_73', '5', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x21002_73', '6', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20d82_56', '7', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The name of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20e02_46', '8', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x20e82_56', '9', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The interface of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x22802_56', '10', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The functor must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'), 'BOUML_0x22882_56', '11', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The modulename of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('name', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'));
		
INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('interface', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'));
		
INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('functor', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'));
		
INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('modulename', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "name" = 'actValidateAnwendungen_BOUML_0x1f482_39'));
		
-- Create activity transitions

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_70'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f02_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('name == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f82_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('interface == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f82_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('functor == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f82_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72'));

UPDATE "action_step_transitions" set "expression" = 'result = 1' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('modulename == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72'));

UPDATE "action_step_transitions" set "expression" = 'result = 0' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

-- Rename activity nodes for Sqlite

UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x20d82_70';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x20e02_73';
		
UPDATE "action_steps" set "bezeichnung" = 'FinalNode' where "bezeichnung" = 'BOUML_0x20e82_72';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x20f02_73';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x20f82_73';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x21002_73';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x20d82_56';
		
UPDATE "action_steps" set "bezeichnung" = 'seterror' where "bezeichnung" = 'BOUML_0x20e02_46';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x20e82_56';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x22802_56';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x22882_56';
		
-- Nodetype uml:ActivityParameterNode not known.
		
-- Nodetype uml:ActivityParameterNode not known.
		
-- Nodetype uml:ActivityParameterNode not known.
		
-- Nodetype uml:ActivityParameterNode not known.
		

-- Cleanup unused double types
DELETE FROM "action_types" where "id" NOT IN (SELECT "typ" from "actions") AND "id" NOT IN (SELECT "type" from "action_steps");


-- Script ready.
