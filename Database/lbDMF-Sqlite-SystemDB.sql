

--
-- SQL script created for Sqlite
--

		
		
-- Application is lbDMF Manager. Package is lbDMF Manager
-- Skip rewrite
-- To ignore this statement in the Sqlite rewrite parser. This statement should match to Sqlite syntax.
-- Create default indexes for Sqlite. Version ignored.

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
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('SQL query', 'instanceOflbSQLQueryAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open form', 'instanceOflbFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open detail form', 'instanceOflbDetailFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open master form', 'instanceOflbMasterFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open Database Report', 'instanceOflbDBReportAction', 'lbDatabaseReport');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Perform XSLT transformation', 'instanceOflbDMFXslt', 'lbDMFXslt');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open application', 'instanceOflbExecuteAction', 'lbDatabaseForm');



-- Delete application definitions if they exist. The deletion must be done in reverse order.

-- help table to not loose unused actions.
CREATE TABLE "tempactions" (
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

INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT id, lastapp FROM "users" WHERE "userid" = 'user';

INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'trainres', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', 'lbDMF', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';

drop table tempactions;

		
		-- Class Benutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Benutzer');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', 'kuser.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for users (BOUML_0x1f402_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "passwort", "userid", "vorname", "name" from "users"', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

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


		-- Class Formulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Formulare');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', 'kpersonalizer.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for formulare (BOUML_0x1f482_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "menuhilfe", "eventname", "menuname", "name", "toolbarimage" from "formulare"', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

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
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formular_Parameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Formular_Parameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', 'formular_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for formular_parameters (BOUML_0x1f502_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername" from "formular_parameters"', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formular_Parameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formular_Parameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formular_Parameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formular_Parameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class AnwendungenBenutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'AnwendungenBenutzer');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'AnwendungenBenutzer', 'AnwendungenBenutzer verwalten', 'manageAnwendungenBenutzer', 'Edit data of AnwendungenBenutzer', 'User_application.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for user_anwendungen (BOUML_0x1f582_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "userid", "anwendungenid" from "user_anwendungen"', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'AnwendungenBenutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'AnwendungenBenutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'AnwendungenBenutzer', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'AnwendungenBenutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FormulareAnwendung of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'FormulareAnwendung');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormulareAnwendung', 'FormulareAnwendung verwalten', 'manageFormulareAnwendung', 'Edit data of FormulareAnwendung', 'app_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for anwendungen_formulare (BOUML_0x1f602_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungid", "formularid" from "anwendungen_formulare"', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormulareAnwendung', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Anwendungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Anwendungen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', 'kthememgr.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for anwendungen (BOUML_0x1f682_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "interface", "functor", "modulename", "titel", "name" from "anwendungen"', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

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

INSERT OR IGNORE INTO "actions" (name, typ, source) VALUES ('Codegenerieren', 1, 'name');
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, '', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Codegenerieren'));
INSERT OR IGNORE INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = 'Anwendungen'), (select id from actions where name = 'Codegenerieren'), 'evt_Anwendungen_Codegenerieren');

	
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Aktionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Aktionen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', 'cache.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for actions (BOUML_0x1f702_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "target", "source", "name", "id" from "actions"', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

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
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Uebersetzungen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', 'babelfish.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for translations (BOUML_0x1f782_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "translated", "text" from "translations"', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Uebersetzungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Uebersetzungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Uebersetzungen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Uebersetzungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formularaktionenzuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Formularaktionenzuordnen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formularaktionenzuordnen', 'Formularaktionenzuordnen verwalten', 'manageFormularaktionenzuordnen', 'Edit data of Formularaktionenzuordnen', 'actions_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for formular_actions (BOUML_0x1f802_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "event" from "formular_actions"', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formularaktionenzuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formularaktionenzuordnen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formularaktionenzuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Anwendungsparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Anwendungsparameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', 'app_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for anwendungs_parameter (BOUML_0x1f882_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername" from "anwendungs_parameter"', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungsparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungsparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungsparameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungsparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Aktionsschrittezuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Aktionsschrittezuordnen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', 'action_steps.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for action_steps (BOUML_0x1f902_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "what", "a_order_nr", "bezeichnung", "id" from "action_steps"', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Aktionsschrittezuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionsschrittezuordnen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionsschrittezuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Reportdefinitionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Reportdefinitionen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', 'print_class.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for reports (BOUML_0x1f982_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "description", "name" from "reports"', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

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
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Reportparameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', 'kword.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for report_parameters (BOUML_0x1fa02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "value", "name" from "report_parameters"', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Reportparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Reportparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Reportparameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


-- Script ready.
