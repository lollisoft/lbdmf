
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

INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT id, lastapp FROM "users" WHERE "userid" = 'user';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'dbpass', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', 'lbDMF', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';

-- Create the standard action types

INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Buttonpress', '', '');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('SQL query', 'instanceOflbSQLQueryAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open form', 'instanceOflbFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open detail form', 'instanceOflbDetailFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open master form', 'instanceOflbMasterFormAction', 'lbDatabaseForm');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open Database Report', 'instanceOflbDBReportAction', 'lbDatabaseReport');
INSERT OR IGNORE INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Perform XSLT transformation', 'instanceOflbDMFXslt', 'lbDMFXslt');

		
		-- Class Benutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Benutzer');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', 'kuser.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for users (Benutzer_1)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "passwort", "userid", "vorname", "name" from "users"', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Benutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Benutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Benutzer', 1);


-- Association from Benutzer to AnwendungenBenutzer
-- Select action type IsMasterDetail: Prop_Benutzer_1_AnwendungenBenutzer_8, IsDetailMaster: 
-- Build up a master detail action

INSERT OR IGNORE INTO actions (name, typ, source) values ('AnwendungenBenutzer', 1, 'userid');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for AnwendungenBenutzer', 1, 'AnwendungenBenutzer', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'AnwendungenBenutzer' and source = 'userid'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'AnwendungenBenutzer' and source = 'userid'), 'action_master_detail_Prop_Benutzer_1_AnwendungenBenutzer_8');

	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Formulare');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', 'kpersonalizer.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'typ', 'formulartypen', 'beschreibung');
	
INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'anwendungid', 'anwendungen', 'name');
	

-- Create query for formulare (Formulare_2)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "typ", "anwendungid", "menuhilfe", "eventname", "menuname", "name", "toolbarimage" from "formulare"', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formulare', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formulare', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formulare', 1);


INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('toolbarimage', 'Formulare', 1, 'toolbarimagefile');

-- Association from Formulare to Formular_Parameter
-- Select action type IsMasterDetail: Prop_Formulare_2_Formular_Parameter_7, IsDetailMaster: 
-- Build up a master detail action

INSERT OR IGNORE INTO actions (name, typ, source) values ('Formular_Parameter', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formular_Parameter', 1, 'Formular_Parameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formular_Parameter' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formular_Parameter' and source = 'name'), 'action_master_detail_Prop_Formulare_2_Formular_Parameter_7');

	
-- Association from Formulare to Formularaktionenzuordnen
-- Select action type IsMasterDetail: Prop_Formulare_2_Formularaktionenzuordnen_27, IsDetailMaster: 
-- Build up a master detail action

INSERT OR IGNORE INTO actions (name, typ, source) values ('Formularaktionenzuordnen', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formularaktionenzuordnen', 1, 'Formularaktionenzuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formularaktionenzuordnen' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formularaktionenzuordnen' and source = 'name'), 'action_master_detail_Prop_Formulare_2_Formularaktionenzuordnen_27');

	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formular_Parameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Formular_Parameter');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', 'formular_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_parameters', 'formularid', 'formulare', 'name');
	

-- Create query for formular_parameters (Formular_Parameter_7)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "formularid", "parametervalue", "parametername" from "formular_parameters"', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formular_Parameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formular_Parameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formular_Parameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formular_Parameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class AnwendungenBenutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'AnwendungenBenutzer');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'AnwendungenBenutzer', 'AnwendungenBenutzer verwalten', 'manageAnwendungenBenutzer', 'Edit data of AnwendungenBenutzer', 'User_application.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'anwendungenid', 'anwendungen', 'name');
	
INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'userid', 'users', 'userid');
	

-- Create query for user_anwendungen (AnwendungenBenutzer_8)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungenid", "userid" from "user_anwendungen"', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'AnwendungenBenutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'AnwendungenBenutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'AnwendungenBenutzer', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'AnwendungenBenutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class FormulareAnwendung of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'FormulareAnwendung');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormulareAnwendung', 'FormulareAnwendung verwalten', 'manageFormulareAnwendung', 'Edit data of FormulareAnwendung', 'app_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'formularid', 'formulare', 'name');
	
INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'anwendungid', 'anwendungen', 'name');
	

-- Create query for anwendungen_formulare (FormulareAnwendung_17)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "formularid", "anwendungid" from "anwendungen_formulare"', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormulareAnwendung', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Anwendungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Anwendungen');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', 'kthememgr.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for anwendungen (Anwendungen_19)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "interface", "functor", "modulename", "titel", "name" from "anwendungen"', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungen', 1);


-- Association from Anwendungen to Formulare
-- Select action type IsMasterDetail: Prop_Anwendungen_19_Formulare_2, IsDetailMaster: 
-- Build up a master detail action

INSERT OR IGNORE INTO actions (name, typ, source) values ('Formulare', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formulare' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formulare' and source = 'name'), 'action_master_detail_Prop_Anwendungen_19_Formulare_2');

	
-- Association from Anwendungen to Anwendungsparameter
-- Select action type IsMasterDetail: Prop_Anwendungen_19_Anwendungsparameter_28, IsDetailMaster: 
-- Build up a master detail action

INSERT OR IGNORE INTO actions (name, typ, source) values ('Anwendungsparameter', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungsparameter', 1, 'Anwendungsparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Anwendungsparameter' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Anwendungsparameter' and source = 'name'), 'action_master_detail_Prop_Anwendungen_19_Anwendungsparameter_28');

	

-- Create operation definitions

-- Generate codegeneration operation 'Codegenerieren' for 'Anwendungen'

INSERT OR IGNORE INTO "actions" (name, typ, source) VALUES ('Codegenerieren', 1, 'name');
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, 'lala', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Codegenerieren'));
INSERT OR IGNORE INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = 'Anwendungen'), (select id from actions where name = 'Codegenerieren'), 'evt_Anwendungen_Codegenerieren');

	
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class AnwendungenFormulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'AnwendungenFormulare');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'AnwendungenFormulare', 'AnwendungenFormulare verwalten', 'manageAnwendungenFormulare', 'Edit data of AnwendungenFormulare', 'app_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for  (AnwendungenFormulare_20)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select  from ""', id FROM "formulare" WHERE name = 'AnwendungenFormulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'AnwendungenFormulare', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'AnwendungenFormulare', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'AnwendungenFormulare', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'AnwendungenFormulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Aktionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Aktionen');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', 'cache.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'typ', 'action_types', 'bezeichnung');
	

-- Create query for actions (Aktionen_24)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "target", "source", "typ", "name", "id" from "actions"', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Aktionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionen', 1);


-- Association from Aktionen to Aktionsschrittezuordnen
-- Select action type IsMasterDetail: Prop_Aktionen_24_Aktionsschrittezuordnen_29, IsDetailMaster: 
-- Build up a master detail action

INSERT OR IGNORE INTO actions (name, typ, source) values ('Aktionsschrittezuordnen', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Aktionsschrittezuordnen', 1, 'Aktionsschrittezuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'name'), 'action_master_detail_Prop_Aktionen_24_Aktionsschrittezuordnen_29');

	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Uebersetzungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Uebersetzungen');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', 'babelfish.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for translations (Uebersetzungen_25)
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


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'action', 'actions', 'name');
	
INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'formular', 'formulare', 'name');
	

-- Create query for formular_actions (Formularaktionenzuordnen_27)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "event", "action", "formular" from "formular_actions"', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formularaktionenzuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formularaktionenzuordnen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formularaktionenzuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Anwendungsparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Anwendungsparameter');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', 'app_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungs_parameter', 'anwendungid', 'anwendungen', 'name');
	

-- Create query for anwendungs_parameter (Anwendungsparameter_28)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungid", "parametervalue", "parametername" from "anwendungs_parameter"', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungsparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungsparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungsparameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungsparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Aktionsschrittezuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Aktionsschrittezuordnen');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', 'action_steps.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'type', 'action_types', 'bezeichnung');
	
INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'actionid', 'actions', 'name');
	

-- Create query for action_steps (Aktionsschrittezuordnen_29)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "what", "type", "a_order_nr", "bezeichnung", "actionid", "id" from "action_steps"', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Aktionsschrittezuordnen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionsschrittezuordnen', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionsschrittezuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Reportdefinitionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Reportdefinitionen');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', 'print_class.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for reports (Reportdefinitionen_438)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "description", "name" from "reports"', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Reportdefinitionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Reportdefinitionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Reportdefinitionen', 1);


-- Association from Reportdefinitionen to Reportparameter
-- Select action type IsMasterDetail: Prop_Reportdefinitionen_438_Reportparameter_439, IsDetailMaster: 
-- Build up a master detail action

INSERT OR IGNORE INTO actions (name, typ, source) values ('Reportparameter', 1, 'name');	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Reportparameter', 1, 'Reportparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Reportparameter' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Reportparameter' and source = 'name'), 'action_master_detail_Prop_Reportdefinitionen_438_Reportparameter_439');

	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Reportparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
--select "DropFormular"('lbDMF Manager', 'Reportparameter');


INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', 'kword.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_parameters', 'reportid', 'reports', 'name');
	

-- Create query for report_parameters (Reportparameter_439)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "value", "name", "reportid" from "report_parameters"', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Reportparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Reportparameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Reportparameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class action_steps of type ENTITY found.
				
		-- Class action_types of type ENTITY found.
				
		-- Class actions of type ENTITY found.
				
		-- Class anwendungen of type ENTITY found.
				
		-- Class anwendungen_formulare of type ENTITY found.
				
		-- Class anwendungs_parameter of type ENTITY found.
				
		-- Class anwendungsberechtigungen of type ENTITY found.
				
		-- Class applevel_plugin_registry of type ENTITY found.
				
		-- Class codegentarget of type ENTITY found.
				
		-- Class column_types of type ENTITY found.
				
		-- Class foreignkey_visibledata_mapping of type ENTITY found.
				
		-- Class formular_actions of type ENTITY found.
				
		-- Class formular_parameters of type ENTITY found.
				
		-- Class formulare of type ENTITY found.
				
		-- Class formulartypen of type ENTITY found.
				
		-- Class regressiontest of type ENTITY found.
				
		-- Class report_element_types of type ENTITY found.
				
		-- Class report_elements of type ENTITY found.
				
		-- Class report_parameters of type ENTITY found.
				
		-- Class report_texts of type ENTITY found.
				
		-- Class reports of type ENTITY found.
				
		-- Class translations of type ENTITY found.
				
		-- Class user_anwendungen of type ENTITY found.
				
		-- Class users of type ENTITY found.
				
-- Script ready.
