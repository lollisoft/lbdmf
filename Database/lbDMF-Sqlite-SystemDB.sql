
-- Speedup many times
BEGIN TRANSACTION;

-- Params XSLDatabaseBackendSystem: 
-- Params XSLDatabaseBackendApplication: 
-- Params overwriteDatabase: 

-- Params targetdatabase generated: Sqlite

--
-- SQL script created for Sqlite
--

		
		
-- Application is lbDMF Manager. Package is lbDMF Manager
-- Using database settings as of name=lbdmf, user=dbuser
-- Skip rewrite
-- To ignore this statement in the Sqlite rewrite parser. This statement should match to Sqlite syntax.
-- Create default indexes for Sqlite. Version ignored.
-- Using database settings as of name=lbdmf, user=dbuser

CREATE UNIQUE INDEX IF NOT EXISTS "idx_users_userid" on "users" (userid);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formulartypen_hi_ns" on "formulartypen" (handlerinterface, namespace, handlermodule);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_anwendungen_name" on "anwendungen" (name);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formulare_name" on "formulare" (anwendungid, name);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_formular_parameter" on "formular_parameters" (formularid, parametername);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_anwendungs_parameter" on "anwendungs_parameter" (anwendungid, parametername);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_column_types" on "column_types" (name, tablename);

CREATE UNIQUE INDEX IF NOT EXISTS "idx_user_anwendungen" on "user_anwendungen" (userid, anwendungenid);

INSERT OR IGNORE INTO "formulartypen" ("handlerinterface", "namespace", "handlermodule", "handlerfunctor", "beschreibung") VALUES ('lb_I_DatabaseForm','','-','','Dynamisch aufgebautes Datenbankformular');

--  || cast(X'00' as TEXT)
INSERT OR IGNORE INTO "anwendungen" ("name", "titel", "modulename", "functor", "interface", "model_complete", "model_errors") values('lbDMF Manager', 'Application lbDMF Manager', 'lbDynApp', 'instanceOfApplication', 'lb_I_Application', 1, 'Import started');

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

-- Delete database schema information
delete from dbforeignkey where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager')); 
delete from dbprimarykey where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager')); 
delete from dbcolumn where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager')); 
delete from dbtableparameter where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager')); 
delete from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager'); 

delete from formularfieldparameter where formularfieldid IN (select id from formularfields where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager')));
-- delete formularfields
delete from formularfields where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager'));

delete from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

delete from anwendungs_parameter where anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT users.id,anwendungen.id FROM "users" inner join anwendungen where anwendungen.name = 'lbDMF Manager';

INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'trainres', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', 'lbDMF', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';

drop table tempactions;

		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi gen extensions', 'yes', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi comment exporter', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi uml2.0', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi primitive type', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi gen eclipse', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi use profile', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi path', '/Users/lothar/develop/Projects/CPP/AppDevelopmentDemo/DynamicApp/UMLSamples/SecondStageModels/lbDMF Manager.xmi', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi vis prefix', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi no model', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi linefeed', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi gen views', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi pk prefix', 'no', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('gxmi encoding', 'UTF-8', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('ProductVersion', '1.0.6.0', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DataStoreBaseAddress', 'net.tcp://cloud.lollisoft.de:49381', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('UpgradeCode', '48dc066c-97cc-4512-8fa3-52bbe195e075', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('StsBaseAddress', 'net.tcp://cloud.lollisoft.de:8000', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('ProductCode', 'ECDCC18A-BE39-40DA-8369-B360B1F0BD86', (select id from anwendungen where name = 'lbDMF Manager'));
		
		-- Class Anwendungen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Anwendungen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', 'kthememgr.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Application', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen', 'requirements', 'richtext', '');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen', 'background', 'richtext', '');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen', 'model_errors', 'bigstring', '');


-- Create query for anwendungen (BOUML_0x1f682_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "titel", "name", "interface", "functor", "modulename", "requirements", "background", "model_complete", "model_errors" from "anwendungen"', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name titel
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'titel', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name interface
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'interface', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name functor
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'functor', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name modulename
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'modulename', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name requirements
-- Field datatypeid BOUML_datatype_0
-- Field datatype richtext
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'requirements', 'anwendungen', 0, 'richtext', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');
		
INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('requirements', 'Anwendungen', 1, 'richtext');


-- Field name background
-- Field datatypeid BOUML_datatype_0
-- Field datatype richtext
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'background', 'anwendungen', 0, 'richtext', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');
		
INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('background', 'Anwendungen', 1, 'richtext');


-- Field name Anwendungsparameter

-- Field name Formulare

-- Field name Tables

-- Field name model_complete
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'model_complete', 'anwendungen', 0, 'Bit', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name model_errors
-- Field datatypeid BOUML_datatype_1
-- Field datatype bigstring


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungen', 1);


-- Association from Anwendungen to Anwendungsparameter
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f882_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21682_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21682_0', 'Anwendungsparameter', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Anwendungsparameter', 
1, 
'Anwendungsparameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21682_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21682_0' and source = 'name'), 
'action_master_detail_BOUML_0x21682_0'
);
--UPDATE actions set name = 'Anwendungsparameter' where name = 'BOUML_0x21682_0';
	
-- Association from Anwendungen to Formulare
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21702_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21702_0', 'Formulare', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formulare', 
1, 
'Formulare', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21702_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21702_0' and source = 'name'), 
'action_master_detail_BOUML_0x21702_0'
);
--UPDATE actions set name = 'Formulare' where name = 'BOUML_0x21702_0';
	
-- Association from Anwendungen to Tables
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x28082_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2d202_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x2d202_0', 'Tables', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Tables', 
1, 
'Tables', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x2d202_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x2d202_0' and source = 'name'), 
'action_master_detail_BOUML_0x2d202_0'
);
--UPDATE actions set name = 'Tables' where name = 'BOUML_0x2d202_0';
	

-- Create operation definitions

-- Generate codegeneration operation 'Codegenerieren' for 'Anwendungen'

INSERT OR IGNORE INTO "actions" (name, typ, source, anwendungenid) VALUES (
'Codegenerieren', 
(select id from action_types where bezeichnung = 'Buttonpress'), 
'name',
(select id from "anwendungen" where name = 'lbDMF Manager'));
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, '', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Codegenerieren'));
INSERT OR IGNORE INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = 'Anwendungen'), (select id from actions where name = 'Codegenerieren'), 'evt_Anwendungen_Codegenerieren');

	
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formulare of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formulare');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', 'kpersonalizer.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Application', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'anwendungid', 'anwendungen', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'typ', 'formulartypen', 'beschreibung');


-- Create query for formulare (BOUML_0x1f482_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "menuname", "menuhilfe", "eventname", "toolbarimage", "anwendungid", "typ" from "formulare"', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name menuname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'menuname', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name menuhilfe
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'menuhilfe', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name eventname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'eventname', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name toolbarimage
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'toolbarimage', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Formular_Parameter

-- Field name Formularaktionenzuordnen

-- Field name anwendungid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'formulare', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name typ
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'typ', 'formulare', 1, 'beschreibung', 'formulartypen', 'Integer', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Fields


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
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21802_0', 'Formular_Parameter', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formular_Parameter', 
1, 
'Formular_Parameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21802_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21802_0' and source = 'name'), 
'action_master_detail_BOUML_0x21802_0'
);
--UPDATE actions set name = 'Formular_Parameter' where name = 'BOUML_0x21802_0';
	
-- Association from Formulare to Formularaktionenzuordnen
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f802_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21882_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21882_0', 'Formularaktionenzuordnen', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formularaktionenzuordnen', 
1, 
'Formularaktionenzuordnen', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21882_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21882_0' and source = 'name'), 
'action_master_detail_BOUML_0x21882_0'
);
--UPDATE actions set name = 'Formularaktionenzuordnen' where name = 'BOUML_0x21882_0';
	
-- Association from Formulare to FormularFields
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x24b02_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x25e02_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x25e02_0', 'FormularFields', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for FormularFields', 
1, 
'FormularFields', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x25e02_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x25e02_0' and source = 'name'), 
'action_master_detail_BOUML_0x25e02_0'
);
--UPDATE actions set name = 'FormularFields' where name = 'BOUML_0x25e02_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FormularFields of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'FormularFields');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularFields', 'FormularFields verwalten', 'manageFormularFields', 'Edit data of FormularFields', 'formular_field.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Application', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'formularid', 'formulare', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'dbtypeid', 'dbtype', 'name');


-- Create query for formularfields (BOUML_0x24b02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "dbtype", "tablename", "isfk", "fkname", "fktable", "formularid", "dbtypeid" from "formularfields"', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name dbtype
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'dbtype', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tablename
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name isfk
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'isfk', 'formularfields', 0, 'Bit', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name fkname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkname', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name fktable
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fktable', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name DBType

-- Field name formularid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'formularfields', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name dbtypeid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtypeid', 'formularfields', 1, 'name', 'dbtype', 'Integer', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Parameter


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormularFields', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormularFields', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormularFields', 1);


-- Association from FormularFields to DBType
-- From formular 'BOUML_0x24b02_4'
-- To   formular 'BOUML_0x24b82_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x25f02_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x25f02_0', 'DBType', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for DBType', 
1, 
'DBType', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x25f02_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x25f02_0' and source = 'name'), 
'action_master_detail_BOUML_0x25f02_0'
);
--UPDATE actions set name = 'DBType' where name = 'BOUML_0x25f02_0';
	
-- Association from FormularFields to FormularFieldParameter
-- From formular 'BOUML_0x24b02_4'
-- To   formular 'BOUML_0x33702_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x3d782_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x3d782_0', 'Parameter', 1, 'parametername', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Parameter', 
1, 
'FormularFieldParameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x3d782_0' and source = 'parametername'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x3d782_0' and source = 'parametername'), 
'action_master_detail_BOUML_0x3d782_0'
);
--UPDATE actions set name = 'Parameter' where name = 'BOUML_0x3d782_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Benutzer of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Benutzer');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', 'kuser.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Authentification', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'User Management', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for users (BOUML_0x1f402_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "passwort", "userid", "vorname", "name" from "users"', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name passwort
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'passwort', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name userid
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'userid', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name vorname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'vorname', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'users', 0, 'String', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name AnwendungenBenutzer


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Benutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Benutzer', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Benutzer', 1);


-- Association from Benutzer to AnwendungenBenutzer
-- From formular 'BOUML_0x1f402_4'
-- To   formular 'BOUML_0x1f582_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21782_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21782_0', 'AnwendungenBenutzer', 1, 'userid', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for AnwendungenBenutzer', 
1, 
'AnwendungenBenutzer', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21782_0' and source = 'userid'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21782_0' and source = 'userid'), 
'action_master_detail_BOUML_0x21782_0'
);
--UPDATE actions set name = 'AnwendungenBenutzer' where name = 'BOUML_0x21782_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class DBType of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'DBType');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'DBType', 'DBType verwalten', 'manageDBType', 'Edit data of DBType', 'field_types.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'System Configuration', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Database', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for dbtype (BOUML_0x24b82_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "description" from "dbtype"', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'dbtype', 0, 'String', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name description
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'dbtype', 0, 'String', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'DBType', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'DBType', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'DBType', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'DBType' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formular_Parameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formular_Parameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', 'formular_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Applications', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Forms', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_parameters', 'formularid', 'formulare', 'name');


-- Create query for formular_parameters (BOUML_0x1f502_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername", "formularid" from "formular_parameters"', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name parametervalue
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'formular_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name parametername
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'formular_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name formularid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

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

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Authentification', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'User Management', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'userid', 'users', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'anwendungenid', 'anwendungen', 'name');


-- Create query for user_anwendungen (BOUML_0x1f582_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "userid", "anwendungenid" from "user_anwendungen"', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name userid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'userid', 'user_anwendungen', 1, 'userid', 'users', 'Integer', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name anwendungenid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungenid', 'user_anwendungen', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



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

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Authentification', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'User Management', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'anwendungid', 'anwendungen', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'formularid', 'formulare', 'name');


-- Create query for anwendungen_formulare (BOUML_0x1f602_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungid", "formularid", "purpose" from "anwendungen_formulare"', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name anwendungid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'anwendungen_formulare', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name formularid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'anwendungen_formulare', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name purpose
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'purpose', 'anwendungen_formulare', 0, 'String', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Formulare

-- Field name Anwendungen


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormulareAnwendung', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormulareAnwendung', 1);


-- Association from FormulareAnwendung to Formulare
-- From formular 'BOUML_0x1f602_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29402_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x29402_0', 'Formulare', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formulare', 
1, 
'Formulare', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x29402_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x29402_0' and source = 'name'), 
'action_master_detail_BOUML_0x29402_0'
);
--UPDATE actions set name = 'Formulare' where name = 'BOUML_0x29402_0';
	
-- Association from FormulareAnwendung to Anwendungen
-- From formular 'BOUML_0x1f602_4'
-- To   formular 'BOUML_0x1f682_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29482_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x29482_0', 'Anwendungen', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Anwendungen', 
1, 
'Anwendungen', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x29482_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x29482_0' and source = 'name'), 
'action_master_detail_BOUML_0x29482_0'
);
--UPDATE actions set name = 'Anwendungen' where name = 'BOUML_0x29482_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Aktionen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Aktionen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', 'cache.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Applications', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Actions', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'typ', 'action_types', 'bezeichnung');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'anwendungenid', 'anwendungen', 'name');


-- Create query for actions (BOUML_0x1f702_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "target", "source", "name", "typ", "anwendungenid" from "actions"', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name target
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'target', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name source
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'source', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name typ
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'typ', 'actions', 1, 'bezeichnung', 'action_types', 'Integer', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Aktionsschrittezuordnen

-- Field name anwendungenid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungenid', 'actions', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Aktionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionen', 1);


-- Association from Aktionen to Aktionsschrittezuordnen
-- From formular 'BOUML_0x1f702_4'
-- To   formular 'BOUML_0x1f902_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21602_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21602_0', 'Aktionsschrittezuordnen', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Aktionsschrittezuordnen', 
1, 
'Aktionsschrittezuordnen', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21602_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21602_0' and source = 'name'), 
'action_master_detail_BOUML_0x21602_0'
);
--UPDATE actions set name = 'Aktionsschrittezuordnen' where name = 'BOUML_0x21602_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Uebersetzungen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Uebersetzungen');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', 'babelfish.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Applications', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Configurations', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for translations (BOUML_0x1f782_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "translated", "text" from "translations"', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name translated
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'translated', 'translations', 0, 'String', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name text
-- Field datatypeid 
-- Field datatype 
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

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Applications', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Forms', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'action', 'actions', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'formular', 'formulare', 'name');


-- Create query for formular_actions (BOUML_0x1f802_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "event", "action", "formular" from "formular_actions"', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name event
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'event', 'formular_actions', 0, 'String', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name action
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'action', 'formular_actions', 1, 'name', 'actions', 'Integer', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name formular
-- Field datatypeid 
-- Field datatype 
-- dropdown field

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

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Applications', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Application Definition', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungs_parameter', 'anwendungid', 'anwendungen', 'name');


-- Create query for anwendungs_parameter (BOUML_0x1f882_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername", "anwendungid" from "anwendungs_parameter"', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name parametervalue
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'anwendungs_parameter', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name parametername
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'anwendungs_parameter', 0, 'String', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name anwendungid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

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

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Applications', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Actions', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'type', 'action_types', 'bezeichnung');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'actionid', 'actions', 'name');


-- Create query for action_steps (BOUML_0x1f902_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "bezeichnung", "what", "a_order_nr", "type", "actionid" from "action_steps"', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name bezeichnung
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'bezeichnung', 'action_steps', 0, 'String', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name what
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'what', 'action_steps', 0, 'String', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name a_order_nr
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'a_order_nr', 'action_steps', 0, 'Integer', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name type
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'type', 'action_steps', 1, 'bezeichnung', 'action_types', 'Integer', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name actionid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

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

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Reports', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Definitions', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for reports (BOUML_0x1f982_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "description", "name" from "reports"', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name description
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'reports', 0, 'String', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'reports', 0, 'String', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Reportparameter


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Reportdefinitionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Reportdefinitionen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Reportdefinitionen', 1);


-- Association from Reportdefinitionen to Reportparameter
-- From formular 'BOUML_0x1f982_4'
-- To   formular 'BOUML_0x1fa02_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21902_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21902_0', 'Reportparameter', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Reportparameter', 
1, 
'Reportparameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21902_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21902_0' and source = 'name'), 
'action_master_detail_BOUML_0x21902_0'
);
--UPDATE actions set name = 'Reportparameter' where name = 'BOUML_0x21902_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Reportparameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Reportparameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', 'kword.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Reports', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Definitions', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_parameters', 'reportid', 'reports', 'name');


-- Create query for report_parameters (BOUML_0x1fa02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "value", "name", "reportid" from "report_parameters"', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name value
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'value', 'report_parameters', 0, 'Integer', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name name
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'report_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name reportid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

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

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'System Configuration', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Application', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for formulartypen (BOUML_0x26502_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "handlername", "handlerfunctor", "handlerintarface", "namespace", "beschreibung" from "formulartypen"', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name handlername
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'handlername', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name handlerfunctor
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'handlerfunctor', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name handlerintarface
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'handlerintarface', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name namespace
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'namespace', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name beschreibung
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'beschreibung', 'formulartypen', 0, 'String', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Formulare


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormularTypen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormularTypen', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormularTypen', 1);


-- Association from FormularTypen to Formulare
-- From formular 'BOUML_0x26502_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29582_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x29582_0', 'Formulare', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formulare', 
1, 
'Formulare', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x29582_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'FormularTypen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x29582_0' and source = 'name'), 
'action_master_detail_BOUML_0x29582_0'
);
--UPDATE actions set name = 'Formulare' where name = 'BOUML_0x29582_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularTypen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Tables of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Tables');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Tables', 'Tables verwalten', 'manageTables', 'Edit data of Tables', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Database', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbtable', 'anwendungenid', 'anwendungen', 'name');


-- Create query for dbtable (BOUML_0x28082_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "catalogname", "schemaname", "tablename", "tabletype", "tableremarks", "anwendungenid" from "dbtable"', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name catalogname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'catalogname', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name schemaname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'schemaname', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tablename
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tabletype
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tabletype', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tableremarks
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tableremarks', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Columns

-- Field name PrimaryKeys

-- Field name ForeignKeys

-- Field name anwendungenid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungenid', 'dbtable', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name TableParameter


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Tables', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Tables', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Tables', 1);


-- Association from Tables to Columns
-- From formular 'BOUML_0x28082_4'
-- To   formular 'BOUML_0x28102_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b402_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x2b402_0', 'Columns', 1, 'tablename', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Columns', 
1, 
'Columns', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x2b402_0' and source = 'tablename'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x2b402_0' and source = 'tablename'), 
'action_master_detail_BOUML_0x2b402_0'
);
--UPDATE actions set name = 'Columns' where name = 'BOUML_0x2b402_0';
	
-- Association from Tables to PrimaryKeys
-- From formular 'BOUML_0x28082_4'
-- To   formular 'BOUML_0x28202_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b582_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x2b582_0', 'PrimaryKeys', 1, 'tablename', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for PrimaryKeys', 
1, 
'PrimaryKeys', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x2b582_0' and source = 'tablename'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x2b582_0' and source = 'tablename'), 
'action_master_detail_BOUML_0x2b582_0'
);
--UPDATE actions set name = 'PrimaryKeys' where name = 'BOUML_0x2b582_0';
	
-- Association from Tables to ForeignKeys
-- From formular 'BOUML_0x28082_4'
-- To   formular 'BOUML_0x28182_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b602_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x2b602_0', 'ForeignKeys', 1, 'tablename', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for ForeignKeys', 
1, 
'ForeignKeys', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x2b602_0' and source = 'tablename'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x2b602_0' and source = 'tablename'), 
'action_master_detail_BOUML_0x2b602_0'
);
--UPDATE actions set name = 'ForeignKeys' where name = 'BOUML_0x2b602_0';
	
-- Association from Tables to TableParameter
-- From formular 'BOUML_0x28082_4'
-- To   formular 'BOUML_0x30382_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x37002_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x37002_0', 'TableParameter', 1, 'tablename', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for TableParameter', 
1, 
'TableParameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x37002_0' and source = 'tablename'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x37002_0' and source = 'tablename'), 
'action_master_detail_BOUML_0x37002_0'
);
--UPDATE actions set name = 'TableParameter' where name = 'BOUML_0x37002_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Columns of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Columns');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Columns', 'Columns verwalten', 'manageColumns', 'Edit data of Columns', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Database', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbcolumn', 'dbtableid', 'dbtable', '');


-- Create query for dbcolumn (BOUML_0x28102_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "columnname", "columnremarks", "typename", "columnsize", "nullable", "tablename", "dbtableid" from "dbcolumn"', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name columnname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnname', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name columnremarks
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnremarks', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name typename
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'typename', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name columnsize
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnsize', 'dbcolumn', 0, 'Integer', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name nullable
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'nullable', 'dbcolumn', 0, 'Bit', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tablename
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name dbtableid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtableid', 'dbcolumn', 1, 'tablename', 'dbtable', 'Integer', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name Parameter


INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Columns', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Columns', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Columns', 1);


-- Association from Columns to ColumnParameter
-- From formular 'BOUML_0x28102_4'
-- To   formular 'BOUML_0x31d82_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x3d802_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x3d802_0', 'Parameter', 1, 'parametername', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Parameter', 
1, 
'ColumnParameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x3d802_0' and source = 'parametername'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Columns' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x3d802_0' and source = 'parametername'), 
'action_master_detail_BOUML_0x3d802_0'
);
--UPDATE actions set name = 'Parameter' where name = 'BOUML_0x3d802_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Columns' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class PrimaryKeys of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'PrimaryKeys');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'PrimaryKeys', 'PrimaryKeys verwalten', 'managePrimaryKeys', 'Edit data of PrimaryKeys', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Database', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbprimarykey', 'dbtableid', 'dbtable', '');


-- Create query for dbprimarykey (BOUML_0x28202_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "tablecatalog", "tableschema", "tablename", "columnname", "columnname2", "keysequence", "dbtableid" from "dbprimarykey"', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name tablecatalog
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablecatalog', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tableschema
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tableschema', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tablename
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name columnname
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnname', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name columnname2
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnname2', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name keysequence
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'keysequence', 'dbprimarykey', 0, 'Integer', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name dbtableid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtableid', 'dbprimarykey', 1, 'tablename', 'dbtable', 'Integer', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'PrimaryKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'PrimaryKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'PrimaryKeys', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'PrimaryKeys' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ForeignKeys of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ForeignKeys');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ForeignKeys', 'ForeignKeys verwalten', 'manageForeignKeys', 'Edit data of ForeignKeys', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Database', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbforeignkey', 'dbtableid', 'dbtable', '');


-- Create query for dbforeignkey (BOUML_0x28182_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "pkcatalog", "pkschema", "pktable", "pkcolumn", "fkcatalog", "fkschema", "fktable", "fkcolumn", "dbtableid" from "dbforeignkey"', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name pkcatalog
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pkcatalog', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name pkschema
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pkschema', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name pktable
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pktable', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name pkcolumn
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pkcolumn', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name fkcatalog
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkcatalog', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name fkschema
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkschema', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name fktable
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fktable', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name fkcolumn
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkcolumn', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name dbtableid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtableid', 'dbforeignkey', 1, 'tablename', 'dbtable', 'Integer', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ForeignKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ForeignKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ForeignKeys', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ForeignKeys' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class TableParameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'TableParameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'TableParameter', 'TableParameter verwalten', 'manageTableParameter', 'Edit data of TableParameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonPageName', 'Home', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'RibbonGroupName', 'Database', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for dbtableparameter (BOUML_0x30382_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "tableid" from "dbtableparameter"', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name parametername
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'dbtableparameter', 0, 'String', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name parametervalue
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'dbtableparameter', 0, 'String', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name tableid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'tableid', 'dbtableparameter', 1, 'tablename', 'dbtable', 'Integer', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'TableParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'TableParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'TableParameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'TableParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ColumnParameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ColumnParameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ColumnParameter', 'ColumnParameter verwalten', 'manageColumnParameter', 'Edit data of ColumnParameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'ColumnParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for dbcolumnparameter (BOUML_0x31d82_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "columnid" from "dbcolumnparameter"', id FROM "formulare" WHERE name = 'ColumnParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name parametername
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'dbcolumnparameter', 0, 'String', id FROM "formulare" WHERE name = 'ColumnParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name parametervalue
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'dbcolumnparameter', 0, 'String', id FROM "formulare" WHERE name = 'ColumnParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name columnid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'columnid', 'dbcolumnparameter', 1, 'columnname', 'dbcolumn', 'Integer', id FROM "formulare" WHERE name = 'ColumnParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ColumnParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ColumnParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ColumnParameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ColumnParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FormularFieldParameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'FormularFieldParameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularFieldParameter', 'FormularFieldParameter verwalten', 'manageFormularFieldParameter', 'Edit data of FormularFieldParameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'FormularFieldParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfieldparameter', 'formularfieldid', 'formularfields', '');


-- Create query for formularfieldparameter (BOUML_0x33702_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "formularfieldid" from "formularfieldparameter"', id FROM "formulare" WHERE name = 'FormularFieldParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



-- Field name parametername
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'formularfieldparameter', 0, 'String', id FROM "formulare" WHERE name = 'FormularFieldParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name parametervalue
-- Field datatypeid 
-- Field datatype 
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'formularfieldparameter', 0, 'String', id FROM "formulare" WHERE name = 'FormularFieldParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Field name formularfieldid
-- Field datatypeid 
-- Field datatype 
-- dropdown field

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularfieldid', 'formularfieldparameter', 1, 'name', 'formularfields', 'Integer', id FROM "formulare" WHERE name = 'FormularFieldParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormularFieldParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormularFieldParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormularFieldParameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularFieldParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class action_parameters of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_parameters', '', 'BOUML_0x1fb82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x20982_1', 'int4', -1, 0, 'action_parameters', id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x20a02_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'value', 'BOUML_0x20a82_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x20b02_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x20b82_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'actionid', 'BOUML_0x20382_0', 'int4', -1, 0, 'action_parameters', id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_parameters', 'id',  '', 0, id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'actions', 'id', '', '', 'action_parameters', 'actionid', 0, 0, 0, id from dbtable where tablename = 'action_parameters' AND tableremarks = 'BOUML_0x1fb82_4';

		-- Class action_step_parameter of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_step_parameter', '', 'BOUML_0x1fc02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x20c02_1', 'int4', -1, 0, 'action_step_parameter', id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x20c82_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'value', 'BOUML_0x20d02_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x20d82_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x20e02_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'action_step_id', 'BOUML_0x1fe82_0', 'int4', -1, 0, 'action_step_parameter', id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_step_parameter', 'id',  '', 0, id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_steps', 'id', '', '', 'action_step_parameter', 'action_step_id', 0, 0, 0, id from dbtable where tablename = 'action_step_parameter' AND tableremarks = 'BOUML_0x1fc02_4';

		-- Class action_step_transitions of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_step_transitions', '', 'BOUML_0x1fc82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x20e82_1', 'int4', -1, 0, 'action_step_transitions', id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'expression', 'BOUML_0x20f02_1', 'bpchar', -1, 0, 'action_step_transitions', id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x20f82_1', 'bpchar', -1, 0, 'action_step_transitions', id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dst_actionid', 'BOUML_0x1ff82_0', 'int4', -1, 0, 'action_step_transitions', id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'src_actionid', 'BOUML_0x20082_0', 'int4', -1, 0, 'action_step_transitions', id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_step_transitions', 'id',  '', 0, id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_steps', 'id', '', '', 'action_step_transitions', 'dst_actionid', 0, 0, 0, id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_steps', 'id', '', '', 'action_step_transitions', 'src_actionid', 0, 0, 0, id from dbtable where tablename = 'action_step_transitions' AND tableremarks = 'BOUML_0x1fc82_4';

		-- Class action_steps of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_steps', '', 'BOUML_0x1fd02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21002_1', 'int4', -1, 0, 'action_steps', id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'bezeichnung', 'BOUML_0x21082_1', 'bpchar', -1, 0, 'action_steps', id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'a_order_nr', 'BOUML_0x21102_1', 'int4', -1, 0, 'action_steps', id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'what', 'BOUML_0x21182_1', 'bpchar', -1, 0, 'action_steps', id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'type', 'BOUML_0x20182_0', 'int4', -1, 0, 'action_steps', id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'actionid', 'BOUML_0x20482_0', 'int4', -1, 0, 'action_steps', id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_steps', 'id',  '', 0, id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_types', 'id', '', '', 'action_steps', 'type', 0, 0, 0, id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'actions', 'id', '', '', 'action_steps', 'actionid', 0, 0, 0, id from dbtable where tablename = 'action_steps' AND tableremarks = 'BOUML_0x1fd02_4';

		-- Class action_types of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_types', '', 'BOUML_0x1fd82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21202_1', 'int4', -1, 0, 'action_types', id from dbtable where tablename = 'action_types' AND tableremarks = 'BOUML_0x1fd82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'bezeichnung', 'BOUML_0x21282_1', 'bpchar', -1, 0, 'action_types', id from dbtable where tablename = 'action_types' AND tableremarks = 'BOUML_0x1fd82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'action_handler', 'BOUML_0x21302_1', 'bpchar', -1, 0, 'action_types', id from dbtable where tablename = 'action_types' AND tableremarks = 'BOUML_0x1fd82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'module', 'BOUML_0x21382_1', 'bpchar', -1, 0, 'action_types', id from dbtable where tablename = 'action_types' AND tableremarks = 'BOUML_0x1fd82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_types', 'id',  '', 0, id from dbtable where tablename = 'action_types' AND tableremarks = 'BOUML_0x1fd82_4';


		-- Class actions of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'actions', '', 'BOUML_0x1fe02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21402_1', 'int4', -1, 0, 'actions', id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x21482_1', 'bpchar', -1, 0, 'actions', id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'source', 'BOUML_0x21502_1', 'bpchar', -1, 0, 'actions', id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'target', 'BOUML_0x21582_1', 'bpchar', -1, 0, 'actions', id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typ', 'BOUML_0x20202_0', 'int4', -1, 0, 'actions', id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungenid', 'BOUML_0x30502_0', 'int4', -1, 0, 'actions', id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'actions', 'id',  '', 0, id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_types', 'id', '', '', 'actions', 'typ', 0, 0, 0, id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'actions', 'anwendungenid', 0, 0, 0, id from dbtable where tablename = 'actions' AND tableremarks = 'BOUML_0x1fe02_4';

		-- Class anwendungen of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungen', '', 'BOUML_0x1fe82_4', id from anwendungen where name = 'lbDMF Manager';


insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_method', 'subquery_join', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('action_link_to_owner', 'user_anwendungen', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('action_link_to_owner_link_field', 'anwendungenid', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('action_link_to_owner_parentvalue', '1', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_outer', 'ID', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('action_link_to_owner_link_parentfield', 'userid', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_subquery', 'user_anwendungen', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_inner', 'anwendungenid', 
(select id from dbtable where tablename = 'anwendungen' and tableremarks = 'BOUML_0x1fe82_4'));

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21602_1', 'int4', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x21682_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'titel', 'BOUML_0x21702_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'modulename', 'BOUML_0x21782_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'functor', 'BOUML_0x21802_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x21882_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'requirements', 'BOUML_0x35502_1', 'richtext', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'background', 'BOUML_0x36f02_1', 'richtext', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'model_complete', 'BOUML_0x38982_1', 'BOOLEAN', -1, 0, 'anwendungen', id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungen', 'id',  '', 0, id from dbtable where tablename = 'anwendungen' AND tableremarks = 'BOUML_0x1fe82_4';


		-- Class anwendungen_formulare of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungen_formulare', '', 'BOUML_0x1ff02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21902_1', 'int4', -1, 0, 'anwendungen_formulare', id from dbtable where tablename = 'anwendungen_formulare' AND tableremarks = 'BOUML_0x1ff02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x20602_0', 'int4', -1, 0, 'anwendungen_formulare', id from dbtable where tablename = 'anwendungen_formulare' AND tableremarks = 'BOUML_0x1ff02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x20b82_0', 'int4', -1, 0, 'anwendungen_formulare', id from dbtable where tablename = 'anwendungen_formulare' AND tableremarks = 'BOUML_0x1ff02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'purpose', 'BOUML_0x29882_1', 'bpchar', -1, 0, 'anwendungen_formulare', id from dbtable where tablename = 'anwendungen_formulare' AND tableremarks = 'BOUML_0x1ff02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungen_formulare', 'id',  '', 0, id from dbtable where tablename = 'anwendungen_formulare' AND tableremarks = 'BOUML_0x1ff02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'anwendungen_formulare', 'anwendungid', 0, 0, 0, id from dbtable where tablename = 'anwendungen_formulare' AND tableremarks = 'BOUML_0x1ff02_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'anwendungen_formulare', 'formularid', 0, 0, 0, id from dbtable where tablename = 'anwendungen_formulare' AND tableremarks = 'BOUML_0x1ff02_4';

		-- Class anwendungs_parameter of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungs_parameter', '', 'BOUML_0x1ff82_4', id from anwendungen where name = 'lbDMF Manager';


insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_method', 'subquery_join', 
(select id from dbtable where tablename = 'anwendungs_parameter' and tableremarks = 'BOUML_0x1ff82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_outer', 'anwendungid', 
(select id from dbtable where tablename = 'anwendungs_parameter' and tableremarks = 'BOUML_0x1ff82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_subquery', 'anwendungen', 
(select id from dbtable where tablename = 'anwendungs_parameter' and tableremarks = 'BOUML_0x1ff82_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_inner', 'ID', 
(select id from dbtable where tablename = 'anwendungs_parameter' and tableremarks = 'BOUML_0x1ff82_4'));

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21982_1', 'int4', -1, 0, 'anwendungs_parameter', id from dbtable where tablename = 'anwendungs_parameter' AND tableremarks = 'BOUML_0x1ff82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x21a02_1', 'bpchar', -1, 0, 'anwendungs_parameter', id from dbtable where tablename = 'anwendungs_parameter' AND tableremarks = 'BOUML_0x1ff82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x21a82_1', 'bpchar', -1, 0, 'anwendungs_parameter', id from dbtable where tablename = 'anwendungs_parameter' AND tableremarks = 'BOUML_0x1ff82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x20702_0', 'int4', -1, 0, 'anwendungs_parameter', id from dbtable where tablename = 'anwendungs_parameter' AND tableremarks = 'BOUML_0x1ff82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungs_parameter', 'id',  '', 0, id from dbtable where tablename = 'anwendungs_parameter' AND tableremarks = 'BOUML_0x1ff82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'anwendungs_parameter', 'anwendungid', 0, 0, 0, id from dbtable where tablename = 'anwendungs_parameter' AND tableremarks = 'BOUML_0x1ff82_4';

		-- Class anwendungsberechtigungen of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungsberechtigungen', '', 'BOUML_0x20002_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21b02_1', 'int4', -1, 0, 'anwendungsberechtigungen', id from dbtable where tablename = 'anwendungsberechtigungen' AND tableremarks = 'BOUML_0x20002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'idformular', 'BOUML_0x20c82_0', 'int4', -1, 0, 'anwendungsberechtigungen', id from dbtable where tablename = 'anwendungsberechtigungen' AND tableremarks = 'BOUML_0x20002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'iduser', 'BOUML_0x21482_0', 'int4', -1, 0, 'anwendungsberechtigungen', id from dbtable where tablename = 'anwendungsberechtigungen' AND tableremarks = 'BOUML_0x20002_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungsberechtigungen', 'id',  '', 0, id from dbtable where tablename = 'anwendungsberechtigungen' AND tableremarks = 'BOUML_0x20002_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'anwendungsberechtigungen', 'idformular', 0, 0, 0, id from dbtable where tablename = 'anwendungsberechtigungen' AND tableremarks = 'BOUML_0x20002_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'users', 'id', '', '', 'anwendungsberechtigungen', 'iduser', 0, 0, 0, id from dbtable where tablename = 'anwendungsberechtigungen' AND tableremarks = 'BOUML_0x20002_4';

		-- Class applevel_plugin_registry of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'applevel_plugin_registry', '', 'BOUML_0x20082_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21b82_1', 'int4', -1, 0, 'applevel_plugin_registry', id from dbtable where tablename = 'applevel_plugin_registry' AND tableremarks = 'BOUML_0x20082_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x21c02_1', 'int4', -1, 0, 'applevel_plugin_registry', id from dbtable where tablename = 'applevel_plugin_registry' AND tableremarks = 'BOUML_0x20082_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'applevel_plugin_registry', 'id',  '', 0, id from dbtable where tablename = 'applevel_plugin_registry' AND tableremarks = 'BOUML_0x20082_4';


		-- Class codegentarget of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'codegentarget', '', 'BOUML_0x20102_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21c82_1', 'int4', -1, 0, 'codegentarget', id from dbtable where tablename = 'codegentarget' AND tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x21d02_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tablename = 'codegentarget' AND tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'titel', 'BOUML_0x21d82_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tablename = 'codegentarget' AND tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'modulename', 'BOUML_0x21e02_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tablename = 'codegentarget' AND tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'functor', 'BOUML_0x21e82_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tablename = 'codegentarget' AND tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x21f02_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tablename = 'codegentarget' AND tableremarks = 'BOUML_0x20102_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'codegentarget', 'id',  '', 0, id from dbtable where tablename = 'codegentarget' AND tableremarks = 'BOUML_0x20102_4';


		-- Class column_types of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'column_types', '', 'BOUML_0x20182_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21f82_1', 'int4', -1, 0, 'column_types', id from dbtable where tablename = 'column_types' AND tableremarks = 'BOUML_0x20182_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x22002_1', 'bpchar', -1, 0, 'column_types', id from dbtable where tablename = 'column_types' AND tableremarks = 'BOUML_0x20182_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x22082_1', 'bpchar', -1, 0, 'column_types', id from dbtable where tablename = 'column_types' AND tableremarks = 'BOUML_0x20182_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'controltype', 'BOUML_0x22202_1', 'bpchar', -1, 0, 'column_types', id from dbtable where tablename = 'column_types' AND tableremarks = 'BOUML_0x20182_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'column_types', 'id',  '', 0, id from dbtable where tablename = 'column_types' AND tableremarks = 'BOUML_0x20182_4';


		-- Class foreignkey_visibledata_mapping of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'foreignkey_visibledata_mapping', '', 'BOUML_0x20202_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22282_1', 'int4', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tablename = 'foreignkey_visibledata_mapping' AND tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkname', 'BOUML_0x22302_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tablename = 'foreignkey_visibledata_mapping' AND tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fktable', 'BOUML_0x22382_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tablename = 'foreignkey_visibledata_mapping' AND tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkname', 'BOUML_0x22402_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tablename = 'foreignkey_visibledata_mapping' AND tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pktable', 'BOUML_0x22482_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tablename = 'foreignkey_visibledata_mapping' AND tableremarks = 'BOUML_0x20202_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'foreignkey_visibledata_mapping', 'id',  '', 0, id from dbtable where tablename = 'foreignkey_visibledata_mapping' AND tableremarks = 'BOUML_0x20202_4';


		-- Class formular_actions of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formular_actions', '', 'BOUML_0x20282_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22502_1', 'int4', -1, 0, 'formular_actions', id from dbtable where tablename = 'formular_actions' AND tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'event', 'BOUML_0x22582_1', 'bpchar', -1, 0, 'formular_actions', id from dbtable where tablename = 'formular_actions' AND tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'action', 'BOUML_0x20502_0', 'int4', -1, 0, 'formular_actions', id from dbtable where tablename = 'formular_actions' AND tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formular', 'BOUML_0x20d82_0', 'int4', -1, 0, 'formular_actions', id from dbtable where tablename = 'formular_actions' AND tableremarks = 'BOUML_0x20282_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formular_actions', 'id',  '', 0, id from dbtable where tablename = 'formular_actions' AND tableremarks = 'BOUML_0x20282_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'actions', 'id', '', '', 'formular_actions', 'action', 0, 0, 0, id from dbtable where tablename = 'formular_actions' AND tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formular_actions', 'formular', 0, 0, 0, id from dbtable where tablename = 'formular_actions' AND tableremarks = 'BOUML_0x20282_4';

		-- Class formular_parameters of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formular_parameters', '', 'BOUML_0x20302_4', id from anwendungen where name = 'lbDMF Manager';


insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_method', 'subquery_join', 
(select id from dbtable where tablename = 'formular_parameters' and tableremarks = 'BOUML_0x20302_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_outer', 'formularid', 
(select id from dbtable where tablename = 'formular_parameters' and tableremarks = 'BOUML_0x20302_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_subquery', 'formulare', 
(select id from dbtable where tablename = 'formular_parameters' and tableremarks = 'BOUML_0x20302_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_inner', 'ID', 
(select id from dbtable where tablename = 'formular_parameters' and tableremarks = 'BOUML_0x20302_4'));

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22602_1', 'int4', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x22682_1', 'bpchar', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x22702_1', 'bpchar', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x20e82_0', 'int4', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formular_parameters', 'id',  '', 0, id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formular_parameters', 'formularid', 0, 0, 0, id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

		-- Class formulare of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formulare', '', 'BOUML_0x20382_4', id from anwendungen where name = 'lbDMF Manager';


insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_method', 'subquery_join', 
(select id from dbtable where tablename = 'formulare' and tableremarks = 'BOUML_0x20382_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_field', 'null', 
(select id from dbtable where tablename = 'formulare' and tableremarks = 'BOUML_0x20382_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_outer', 'anwendungid', 
(select id from dbtable where tablename = 'formulare' and tableremarks = 'BOUML_0x20382_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_subquery', 'anwendungen', 
(select id from dbtable where tablename = 'formulare' and tableremarks = 'BOUML_0x20382_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_inner', 'ID', 
(select id from dbtable where tablename = 'formulare' and tableremarks = 'BOUML_0x20382_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_value', 'null', 
(select id from dbtable where tablename = 'formulare' and tableremarks = 'BOUML_0x20382_4'));

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22782_1', 'int4', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x22802_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'menuname', 'BOUML_0x22882_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'menuorder', 'BOUML_0x22902_1', 'int4', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'eventname', 'BOUML_0x22982_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'menuhilfe', 'BOUML_0x22a02_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'toolbarimage', 'BOUML_0x22a82_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x20802_0', 'int4', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typ', 'BOUML_0x20f82_0', 'int4', -1, 0, 'formulare', id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formulare', 'id',  '', 0, id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'formulare', 'anwendungid', 0, 0, 0, id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulartypen', 'id', '', '', 'formulare', 'typ', 0, 0, 0, id from dbtable where tablename = 'formulare' AND tableremarks = 'BOUML_0x20382_4';

		-- Class formularfields of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formularfields', '', 'BOUML_0x24a02_4', id from anwendungen where name = 'lbDMF Manager';


insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_method', 'subquery_join', 
(select id from dbtable where tablename = 'formularfields' and tableremarks = 'BOUML_0x24a02_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_outer', 'formularid', 
(select id from dbtable where tablename = 'formularfields' and tableremarks = 'BOUML_0x24a02_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_subquery', 'formulare', 
(select id from dbtable where tablename = 'formularfields' and tableremarks = 'BOUML_0x24a02_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_inner', 'ID', 
(select id from dbtable where tablename = 'formularfields' and tableremarks = 'BOUML_0x24a02_4'));

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x27b82_1', 'int4', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x27482_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x27502_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x25b82_0', 'int4', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtypeid', 'BOUML_0x25d02_0', 'int4', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'isfk', 'BOUML_0x27702_1', 'BOOLEAN', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkname', 'BOUML_0x27782_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fktable', 'BOUML_0x27802_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtype', 'BOUML_0x27e02_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formularfields', 'id',  '', 0, id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formularfields', 'formularid', 0, 0, 0, id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtype', 'id', '', '', 'formularfields', 'dbtypeid', 0, 0, 0, id from dbtable where tablename = 'formularfields' AND tableremarks = 'BOUML_0x24a02_4';

		-- Class formulartypen of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formulartypen', '', 'BOUML_0x20402_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22b02_1', 'int4', -1, 0, 'formulartypen', id from dbtable where tablename = 'formulartypen' AND tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'handlermodule', 'BOUML_0x22b82_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tablename = 'formulartypen' AND tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'handlerfunctor', 'BOUML_0x22c02_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tablename = 'formulartypen' AND tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'handlerinterface', 'BOUML_0x22c82_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tablename = 'formulartypen' AND tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'namespace', 'BOUML_0x22d02_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tablename = 'formulartypen' AND tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'beschreibung', 'BOUML_0x22d82_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tablename = 'formulartypen' AND tableremarks = 'BOUML_0x20402_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formulartypen', 'id',  '', 0, id from dbtable where tablename = 'formulartypen' AND tableremarks = 'BOUML_0x20402_4';


		-- Class regressiontest of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'regressiontest', '', 'BOUML_0x20482_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22e02_1', 'int4', -1, 0, 'regressiontest', id from dbtable where tablename = 'regressiontest' AND tableremarks = 'BOUML_0x20482_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'test', 'BOUML_0x22e82_1', 'bpchar', -1, 0, 'regressiontest', id from dbtable where tablename = 'regressiontest' AND tableremarks = 'BOUML_0x20482_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'regressiontest', 'id',  '', 0, id from dbtable where tablename = 'regressiontest' AND tableremarks = 'BOUML_0x20482_4';


		-- Class report_element_types of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_element_types', '', 'BOUML_0x20502_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23002_1', 'int4', -1, 0, 'report_element_types', id from dbtable where tablename = 'report_element_types' AND tableremarks = 'BOUML_0x20502_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23082_1', 'bpchar', -1, 0, 'report_element_types', id from dbtable where tablename = 'report_element_types' AND tableremarks = 'BOUML_0x20502_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x23102_1', 'bpchar', -1, 0, 'report_element_types', id from dbtable where tablename = 'report_element_types' AND tableremarks = 'BOUML_0x20502_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_element_types', 'id',  '', 0, id from dbtable where tablename = 'report_element_types' AND tableremarks = 'BOUML_0x20502_4';


		-- Class report_elements of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_elements', '', 'BOUML_0x20582_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23182_1', 'int4', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23202_1', 'bpchar', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'x', 'BOUML_0x23282_1', 'int4', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'y', 'BOUML_0x23302_1', 'int4', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'w', 'BOUML_0x23382_1', 'int4', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'h', 'BOUML_0x23402_1', 'int4', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x23482_1', 'bpchar', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typ', 'BOUML_0x21002_0', 'int4', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'reportid', 'BOUML_0x21282_0', 'int4', -1, 0, 'report_elements', id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_elements', 'id',  '', 0, id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'report_element_types', 'id', '', '', 'report_elements', 'typ', 0, 0, 0, id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'reports', 'id', '', '', 'report_elements', 'reportid', 0, 0, 0, id from dbtable where tablename = 'report_elements' AND tableremarks = 'BOUML_0x20582_4';

		-- Class report_parameters of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_parameters', '', 'BOUML_0x20602_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23502_1', 'int4', -1, 0, 'report_parameters', id from dbtable where tablename = 'report_parameters' AND tableremarks = 'BOUML_0x20602_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23582_1', 'bpchar', -1, 0, 'report_parameters', id from dbtable where tablename = 'report_parameters' AND tableremarks = 'BOUML_0x20602_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'value', 'BOUML_0x23602_1', 'int4', -1, 0, 'report_parameters', id from dbtable where tablename = 'report_parameters' AND tableremarks = 'BOUML_0x20602_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'reportid', 'BOUML_0x21382_0', 'int4', -1, 0, 'report_parameters', id from dbtable where tablename = 'report_parameters' AND tableremarks = 'BOUML_0x20602_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_parameters', 'id',  '', 0, id from dbtable where tablename = 'report_parameters' AND tableremarks = 'BOUML_0x20602_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'reports', 'id', '', '', 'report_parameters', 'reportid', 0, 0, 0, id from dbtable where tablename = 'report_parameters' AND tableremarks = 'BOUML_0x20602_4';

		-- Class report_texts of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_texts', '', 'BOUML_0x20682_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23682_1', 'int4', -1, 0, 'report_texts', id from dbtable where tablename = 'report_texts' AND tableremarks = 'BOUML_0x20682_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'line', 'BOUML_0x23702_1', 'int4', -1, 0, 'report_texts', id from dbtable where tablename = 'report_texts' AND tableremarks = 'BOUML_0x20682_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'text', 'BOUML_0x23782_1', 'bpchar', -1, 0, 'report_texts', id from dbtable where tablename = 'report_texts' AND tableremarks = 'BOUML_0x20682_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'elementid', 'BOUML_0x21102_0', 'int4', -1, 0, 'report_texts', id from dbtable where tablename = 'report_texts' AND tableremarks = 'BOUML_0x20682_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_texts', 'id',  '', 0, id from dbtable where tablename = 'report_texts' AND tableremarks = 'BOUML_0x20682_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'report_elements', 'id', '', '', 'report_texts', 'elementid', 0, 0, 0, id from dbtable where tablename = 'report_texts' AND tableremarks = 'BOUML_0x20682_4';

		-- Class reports of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'reports', '', 'BOUML_0x20702_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23802_1', 'int4', -1, 0, 'reports', id from dbtable where tablename = 'reports' AND tableremarks = 'BOUML_0x20702_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23882_1', 'bpchar', -1, 0, 'reports', id from dbtable where tablename = 'reports' AND tableremarks = 'BOUML_0x20702_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x23902_1', 'bpchar', -1, 0, 'reports', id from dbtable where tablename = 'reports' AND tableremarks = 'BOUML_0x20702_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'reports', 'id',  '', 0, id from dbtable where tablename = 'reports' AND tableremarks = 'BOUML_0x20702_4';


		-- Class translations of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'translations', '', 'BOUML_0x20782_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23982_1', 'int4', -1, 0, 'translations', id from dbtable where tablename = 'translations' AND tableremarks = 'BOUML_0x20782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'text', 'BOUML_0x23a02_1', 'bpchar', -1, 0, 'translations', id from dbtable where tablename = 'translations' AND tableremarks = 'BOUML_0x20782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'translated', 'BOUML_0x23a82_1', 'bpchar', -1, 0, 'translations', id from dbtable where tablename = 'translations' AND tableremarks = 'BOUML_0x20782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'language', 'BOUML_0x23b02_1', 'bpchar', -1, 0, 'translations', id from dbtable where tablename = 'translations' AND tableremarks = 'BOUML_0x20782_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'translations', 'id',  '', 0, id from dbtable where tablename = 'translations' AND tableremarks = 'BOUML_0x20782_4';


		-- Class user_anwendungen of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'user_anwendungen', '', 'BOUML_0x20802_4', id from anwendungen where name = 'lbDMF Manager';


insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_method', 'subquery_join', 
(select id from dbtable where tablename = 'user_anwendungen' and tableremarks = 'BOUML_0x20802_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_outer', 'anwendungenid', 
(select id from dbtable where tablename = 'user_anwendungen' and tableremarks = 'BOUML_0x20802_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_subquery', 'users', 
(select id from dbtable where tablename = 'user_anwendungen' and tableremarks = 'BOUML_0x20802_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_inner', 'ID', 
(select id from dbtable where tablename = 'user_anwendungen' and tableremarks = 'BOUML_0x20802_4'));

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23b82_1', 'int4', -1, 0, 'user_anwendungen', id from dbtable where tablename = 'user_anwendungen' AND tableremarks = 'BOUML_0x20802_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungenid', 'BOUML_0x20902_0', 'int4', -1, 0, 'user_anwendungen', id from dbtable where tablename = 'user_anwendungen' AND tableremarks = 'BOUML_0x20802_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'userid', 'BOUML_0x21582_0', 'int4', -1, 0, 'user_anwendungen', id from dbtable where tablename = 'user_anwendungen' AND tableremarks = 'BOUML_0x20802_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'user_anwendungen', 'id',  '', 0, id from dbtable where tablename = 'user_anwendungen' AND tableremarks = 'BOUML_0x20802_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'user_anwendungen', 'anwendungenid', 0, 0, 0, id from dbtable where tablename = 'user_anwendungen' AND tableremarks = 'BOUML_0x20802_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'users', 'id', '', '', 'user_anwendungen', 'userid', 0, 0, 0, id from dbtable where tablename = 'user_anwendungen' AND tableremarks = 'BOUML_0x20802_4';

		-- Class users of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'users', '', 'BOUML_0x20882_4', id from anwendungen where name = 'lbDMF Manager';


insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_method', 'subquery_filter', 
(select id from dbtable where tablename = 'users' and tableremarks = 'BOUML_0x20882_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_field', 'userid', 
(select id from dbtable where tablename = 'users' and tableremarks = 'BOUML_0x20882_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_outer', 'ID', 
(select id from dbtable where tablename = 'users' and tableremarks = 'BOUML_0x20882_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_subquery', 'user_anwendungen', 
(select id from dbtable where tablename = 'users' and tableremarks = 'BOUML_0x20882_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_inner', 'userid', 
(select id from dbtable where tablename = 'users' and tableremarks = 'BOUML_0x20882_4'));

insert into dbtableparameter (parametername, parametervalue, dbtableid) values('owner_match_value', '1', 
(select id from dbtable where tablename = 'users' and tableremarks = 'BOUML_0x20882_4'));

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23c02_1', 'int4', -1, 0, 'users', id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23c82_1', 'bpchar', -1, 0, 'users', id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'vorname', 'BOUML_0x23d02_1', 'bpchar', -1, 0, 'users', id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'userid', 'BOUML_0x23d82_1', 'bpchar', -1, 0, 'users', id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'passwort', 'BOUML_0x23e02_1', 'bpchar', -1, 0, 'users', id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'lastapp', 'BOUML_0x20a02_0', 'int4', -1, 0, 'users', id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'users', 'id',  '', 0, id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'users', 'lastapp', 0, 0, 0, id from dbtable where tablename = 'users' AND tableremarks = 'BOUML_0x20882_4';

		-- Class dbtype of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbtype', '', 'BOUML_0x24a82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x27b02_1', 'int4', -1, 0, 'dbtype', id from dbtable where tablename = 'dbtype' AND tableremarks = 'BOUML_0x24a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x27602_1', 'bpchar', -1, 0, 'dbtype', id from dbtable where tablename = 'dbtype' AND tableremarks = 'BOUML_0x24a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x27682_1', 'bpchar', -1, 0, 'dbtype', id from dbtable where tablename = 'dbtype' AND tableremarks = 'BOUML_0x24a82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbtype', 'id',  '', 0, id from dbtable where tablename = 'dbtype' AND tableremarks = 'BOUML_0x24a82_4';


		-- Class dbtable of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbtable', '', 'BOUML_0x27e82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x2ba82_1', 'int4', -1, 0, 'dbtable', id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'catalogname', 'BOUML_0x2b482_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'schemaname', 'BOUML_0x2b502_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x2b582_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tabletype', 'BOUML_0x2b602_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tableremarks', 'BOUML_0x2b682_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungenid', 'BOUML_0x2d102_0', 'int4', -1, 0, 'dbtable', id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbtable', 'id',  '', 0, id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'dbtable', 'anwendungenid', 0, 0, 0, id from dbtable where tablename = 'dbtable' AND tableremarks = 'BOUML_0x27e82_4';

		-- Class dbcolumn of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbcolumn', '', 'BOUML_0x27f02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x2ba02_1', 'int4', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnname', 'BOUML_0x2b702_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnremarks', 'BOUML_0x2b782_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typename', 'BOUML_0x2b802_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnsize', 'BOUML_0x2b882_1', 'int4', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'nullable', 'BOUML_0x2b902_1', 'BOOLEAN', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x2b982_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtableid', 'BOUML_0x2b082_0', 'int4', -1, 0, 'dbcolumn', id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbcolumn', 'id',  '', 0, id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtable', 'id', '', '', 'dbcolumn', 'dbtableid', 0, 0, 0, id from dbtable where tablename = 'dbcolumn' AND tableremarks = 'BOUML_0x27f02_4';

		-- Class dbforeignkey of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbforeignkey', '', 'BOUML_0x27f82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x2be82_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkcatalog', 'BOUML_0x2bf02_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkschema', 'BOUML_0x2bf82_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pktable', 'BOUML_0x2c002_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkcolumn', 'BOUML_0x2c082_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkcatalog', 'BOUML_0x30402_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkschema', 'BOUML_0x30482_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fktable', 'BOUML_0x30502_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkcolumn', 'BOUML_0x30582_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'keysequence', 'BOUML_0x2c102_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'updaterule', 'BOUML_0x2c182_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'deleterule', 'BOUML_0x2c202_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtableid', 'BOUML_0x2b182_0', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbforeignkey', 'id',  '', 0, id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtable', 'id', '', '', 'dbforeignkey', 'dbtableid', 0, 0, 0, id from dbtable where tablename = 'dbforeignkey' AND tableremarks = 'BOUML_0x27f82_4';

		-- Class dbprimarykey of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbprimarykey', '', 'BOUML_0x28002_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x2be02_1', 'int4', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablecatalog', 'BOUML_0x2bb02_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tableschema', 'BOUML_0x2bb82_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x2bc02_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnname', 'BOUML_0x2bc82_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnname2', 'BOUML_0x2bd02_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'keysequence', 'BOUML_0x2bd82_1', 'int4', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtableid', 'BOUML_0x2af82_0', 'int4', -1, 0, 'dbprimarykey', id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbprimarykey', 'id',  '', 0, id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtable', 'id', '', '', 'dbprimarykey', 'dbtableid', 0, 0, 0, id from dbtable where tablename = 'dbprimarykey' AND tableremarks = 'BOUML_0x28002_4';

		-- Class dbtableparameter of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbtableparameter', '', 'BOUML_0x30302_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x3bf02_1', 'int4', -1, 0, 'dbtableparameter', id from dbtable where tablename = 'dbtableparameter' AND tableremarks = 'BOUML_0x30302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x3a382_1', 'bpchar', -1, 0, 'dbtableparameter', id from dbtable where tablename = 'dbtableparameter' AND tableremarks = 'BOUML_0x30302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x3a402_1', 'bpchar', -1, 0, 'dbtableparameter', id from dbtable where tablename = 'dbtableparameter' AND tableremarks = 'BOUML_0x30302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtableid', 'BOUML_0x36f02_0', 'int4', -1, 0, 'dbtableparameter', id from dbtable where tablename = 'dbtableparameter' AND tableremarks = 'BOUML_0x30302_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbtableparameter', 'id',  '', 0, id from dbtable where tablename = 'dbtableparameter' AND tableremarks = 'BOUML_0x30302_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtable', 'id', '', '', 'dbtableparameter', 'dbtableid', 0, 0, 0, id from dbtable where tablename = 'dbtableparameter' AND tableremarks = 'BOUML_0x30302_4';

		-- Class dbcolumnparameter of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbcolumnparameter', '', 'BOUML_0x31d02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x3d882_1', 'int4', -1, 0, 'dbcolumnparameter', id from dbtable where tablename = 'dbcolumnparameter' AND tableremarks = 'BOUML_0x31d02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x3d902_1', 'bpchar', -1, 0, 'dbcolumnparameter', id from dbtable where tablename = 'dbcolumnparameter' AND tableremarks = 'BOUML_0x31d02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x3d982_1', 'bpchar', -1, 0, 'dbcolumnparameter', id from dbtable where tablename = 'dbcolumnparameter' AND tableremarks = 'BOUML_0x31d02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbcolumnid', 'BOUML_0x38982_0', 'int4', -1, 0, 'dbcolumnparameter', id from dbtable where tablename = 'dbcolumnparameter' AND tableremarks = 'BOUML_0x31d02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbcolumnparameter', 'id',  '', 0, id from dbtable where tablename = 'dbcolumnparameter' AND tableremarks = 'BOUML_0x31d02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbcolumn', 'id', '', '', 'dbcolumnparameter', 'dbcolumnid', 0, 0, 0, id from dbtable where tablename = 'dbcolumnparameter' AND tableremarks = 'BOUML_0x31d02_4';

		-- Class formularfieldparameter of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formularfieldparameter', '', 'BOUML_0x33782_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x3f602_1', 'int4', -1, 0, 'formularfieldparameter', id from dbtable where tablename = 'formularfieldparameter' AND tableremarks = 'BOUML_0x33782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x3f682_1', 'bpchar', -1, 0, 'formularfieldparameter', id from dbtable where tablename = 'formularfieldparameter' AND tableremarks = 'BOUML_0x33782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x3f702_1', 'bpchar', -1, 0, 'formularfieldparameter', id from dbtable where tablename = 'formularfieldparameter' AND tableremarks = 'BOUML_0x33782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularfieldid', 'BOUML_0x3a402_0', 'int4', -1, 0, 'formularfieldparameter', id from dbtable where tablename = 'formularfieldparameter' AND tableremarks = 'BOUML_0x33782_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formularfieldparameter', 'id',  '', 0, id from dbtable where tablename = 'formularfieldparameter' AND tableremarks = 'BOUML_0x33782_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formularfields', 'id', '', '', 'formularfieldparameter', 'formularfieldid', 0, 0, 0, id from dbtable where tablename = 'formularfieldparameter' AND tableremarks = 'BOUML_0x33782_4';

-- Activity operation for class Anwendungen in package lbDMF Manager is GenerateTurboVision.
-- Operation is a validator using activity 
-- Activity ID is 'BOUML_0x20e02_39'
		-- Activity 'GenerateTurboVision' found.
			
-- Generate statemachine for BOUML_0x20e02_39
-- select "CreateActivityOnMissing"('BOUML_0x20e02_39', 'GenerateTurboVision');

-- Delete old statemachine
delete from "action_step_parameter" where "action_step_id" in (select id from "action_steps" where "actionid" in (select "id" from "actions" where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager')));
delete from "action_step_transitions" where "description" = '_BOUML_0x20e02_39';
delete from "action_steps" where "actionid" in (select "id" from "actions" where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager'));
delete from "formular_actions" where action in (select id from actions where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager'));
delete from "actions" where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager');


-- A form validator should be used before saving the changes to the database

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('GenerateTurboVision_BOUML_0x20e02_39', 'instanceOflbAction', 'lbDatabaseForm');

INSERT OR IGNORE INTO "actions" ("name", "typ", "source", "target", "anwendungenid") VALUES (
'GenerateTurboVision', 
(select "id" from "action_types" where "bezeichnung" = 'Buttonpress'),
'name',
'BOUML_0x20e02_39', 
(select id from "anwendungen" where name = 'lbDMF Manager'));

INSERT OR IGNORE INTO "formular_actions" ("formular", "action", "event") VALUES (
(select "id" from "formulare" where "name" = 'Anwendungen'), 
(select "id" from "actions" where "target" = 'BOUML_0x20e02_39'),
'eventGenerateTurboVision_BOUML_0x20e02_39_Buttonpress');
	
-- Create activity nodes for Sqlite

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x22982_70', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x22a02_72', '2', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24202_56', '3', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', './wxWrapper.app/Contents/Resources/XSLT/TurboVision/gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24302_56', '4', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('SaveApplicationID', '{SaveApplicationID}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'exportApplicationToXMLBuffer', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x25c82_56', '5', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'writeStringToFile', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{memorybuffer}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x28f82_56', '6', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Info', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Only Mac, Windows and Unix flavoured machines are supported.', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29002_56', '7', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '\develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\XSLT_Templates\TurboVision\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29082_56', '8', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '/usr/share/lbdmf/TurboVision/gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29102_46', '9', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2aa82_56', '10', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Operating system and selected application...', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Os Type is {OSType}. ApplicationId is {SaveApplicationID}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24382_73', '11', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24402_73', '12', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24482_73', '13', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2c402_56', '14', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'fileExists', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '\\develop\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\TurboVision\\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x25e02_73', '15', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2c482_56', '16', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

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
delete from "action_step_parameter" where "action_step_id" in (select id from "action_steps" where "actionid" in (select "id" from "actions" where "target" = 'BOUML_0x1f482_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager')));
delete from "action_step_transitions" where "description" = '_BOUML_0x1f482_39';
delete from "action_steps" where "actionid" in (select "id" from "actions" where "target" = 'BOUML_0x1f482_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager'));
delete from "formular_actions" where action in (select id from actions where "target" = 'BOUML_0x1f482_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager'));
delete from "actions" where "target" = 'BOUML_0x1f482_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager');


-- A form validator should be used before saving the changes to the database

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('actValidateAnwendungen_BOUML_0x1f482_39', 'instanceOflbAction', 'lbDatabaseForm');

INSERT OR IGNORE INTO "actions" ("name", "typ", "source", "target", "anwendungenid") VALUES (
'actValidateAnwendungen', 
(select "id" from "action_types" where "bezeichnung" = 'FormValidator'),
'name',
'BOUML_0x1f482_39', 
(select id from "anwendungen" where name = 'lbDMF Manager'));

INSERT OR IGNORE INTO "formular_actions" ("formular", "action", "event") VALUES (
(select "id" from "formulare" where "name" = 'Anwendungen'), 
(select "id" from "actions" where "target" = 'BOUML_0x1f482_39'),
'eventactValidateAnwendungen_BOUML_0x1f482_39_FormValidator');
	
-- Create activity nodes for Sqlite

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20d82_70', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e02_73', '2', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e82_72', '3', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20f02_73', '4', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20f82_73', '5', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x21002_73', '6', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20d82_56', '7', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The name of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e02_46', '8', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e82_56', '9', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The interface of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x22802_56', '10', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The functor must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x22882_56', '11', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The modulename of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('name', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('interface', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('functor', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
INSERT OR IGNORE INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('modulename', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
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



UPDATE "anwendungen" SET "model_errors" = (SELECT "model_errors" || cast(X'0A' as TEXT) || 'Import completed' || cast(X'00' as TEXT)) where name = 'lbDMF Manager';
	


-- Script ready.
COMMIT;
