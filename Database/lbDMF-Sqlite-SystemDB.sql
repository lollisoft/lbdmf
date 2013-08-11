
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

-- Delete database schema information
delete from dbforeignkey where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager')); 
delete from dbprimarykey where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager')); 
delete from dbcolumn where dbtableid in (select id from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager')); 
delete from dbtable where anwendungenid in (select id from anwendungen where name = 'lbDMF Manager'); 

-- delete formularfields
delete from formularfields where formularid in (select id from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager'));

delete from formulare where anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

delete from anwendungs_parameter where anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "user_anwendungen" (userid, anwendungenid) SELECT users.id,anwendungen.id FROM "users" inner join anwendungen where anwendungen.name = 'lbDMF Manager';

INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBUser', 'dba', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBPass', 'trainres', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';
INSERT OR IGNORE INTO "anwendungs_parameter" (parametername, parametervalue, anwendungid) SELECT 'DBName', 'lbDMF', id FROM "anwendungen" WHERE "name" = 'lbDMF Manager';

drop table tempactions;

		
		-- Class DBPrimaryKeys of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'DBPrimaryKeys');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'DBPrimaryKeys', 'DBPrimaryKeys verwalten', 'manageDBPrimaryKeys', 'Edit data of DBPrimaryKeys', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbprimarykey', 'dbtableid', 'dbtable', '');


-- Create query for dbprimarykey (BOUML_0x2ef82_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "tablecatalog", "tableschema", "tablename", "columnname", "columnname2", "keysequence", "dbtableid" from "dbprimarykey"', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablecatalog', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tableschema', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnname', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnname2', 'dbprimarykey', 0, 'String', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'keysequence', 'dbprimarykey', 0, 'Integer', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtableid', 'dbprimarykey', 1, 'tablename', 'dbtable', 'Integer', id FROM "formulare" WHERE name = 'DBPrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'DBPrimaryKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'DBPrimaryKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'DBPrimaryKeys', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'DBPrimaryKeys' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class DBForeignKeys of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'DBForeignKeys');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'DBForeignKeys', 'DBForeignKeys verwalten', 'manageDBForeignKeys', 'Edit data of DBForeignKeys', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbforeignkey', 'dbtableid', 'dbtable', '');


-- Create query for dbforeignkey (BOUML_0x2f102_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "pkcatalog", "pkschema", "pktable", "pkcolumn", "fkcatalog", "fkschema", "fktable", "fkcolumn", "keysequence", "updaterule", "deleterule", "dbtableid" from "dbforeignkey"', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pkcatalog', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pkschema', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pktable', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pkcolumn', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkcatalog', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkschema', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fktable', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkcolumn', 'dbforeignkey', 0, 'String', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'keysequence', 'dbforeignkey', 0, 'Integer', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'updaterule', 'dbforeignkey', 0, 'Integer', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'deleterule', 'dbforeignkey', 0, 'Integer', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtableid', 'dbforeignkey', 1, 'tablename', 'dbtable', 'Integer', id FROM "formulare" WHERE name = 'DBForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'DBForeignKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'DBForeignKeys', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'DBForeignKeys', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'DBForeignKeys' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class DBColumns of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'DBColumns');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'DBColumns', 'DBColumns verwalten', 'manageDBColumns', 'Edit data of DBColumns', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbcolumn', 'dbtableid', 'dbtable', '');


-- Create query for dbcolumn (BOUML_0x2f082_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "columnname", "columnremarks", "typename", "columnsize", "nullable", "tablename", "dbtableid" from "dbcolumn"', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnname', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnremarks', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'typename', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'columnsize', 'dbcolumn', 0, 'Integer', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'nullable', 'dbcolumn', 0, 'Bit', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'dbcolumn', 0, 'String', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtableid', 'dbcolumn', 1, 'tablename', 'dbtable', 'Integer', id FROM "formulare" WHERE name = 'DBColumns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'DBColumns', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'DBColumns', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'DBColumns', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'DBColumns' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class DBTables of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'DBTables');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'DBTables', 'DBTables verwalten', 'manageDBTables', 'Edit data of DBTables', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbtable', 'anwendungenid', 'anwendungen', 'name');


-- Create query for dbtable (BOUML_0x2f002_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "catalogname", "schemaname", "tablename", "tabletype", "tableremarks", "anwendungenid" from "dbtable"', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'catalogname', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'schemaname', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tabletype', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tableremarks', 'dbtable', 0, 'String', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungenid', 'dbtable', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'DBTables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'DBTables', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'DBTables', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'DBTables', 1);


-- Association from DBTables to DBColumns
-- From formular 'BOUML_0x2f002_4'
-- To   formular 'BOUML_0x2f082_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x32282_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x32282_0', 'Columns', 1, 'tablename', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Columns', 
1, 
'DBColumns', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x32282_0' and source = 'tablename'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'DBTables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x32282_0' and source = 'tablename'), 
'action_master_detail_BOUML_0x32282_0'
);
--UPDATE actions set name = 'Columns' where name = 'BOUML_0x32282_0';
	
-- Association from DBTables to DBForeignKeys
-- From formular 'BOUML_0x2f002_4'
-- To   formular 'BOUML_0x2f102_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x32302_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x32302_0', 'ForeignKeys', 1, 'tablename', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for ForeignKeys', 
1, 
'DBForeignKeys', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x32302_0' and source = 'tablename'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'DBTables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x32302_0' and source = 'tablename'), 
'action_master_detail_BOUML_0x32302_0'
);
--UPDATE actions set name = 'ForeignKeys' where name = 'BOUML_0x32302_0';
	
-- Association from DBTables to DBPrimaryKeys
-- From formular 'BOUML_0x2f002_4'
-- To   formular 'BOUML_0x2ef82_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x32382_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x32382_0', 'PrimaryKeys', 1, 'tablename', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for PrimaryKeys', 
1, 
'DBPrimaryKeys', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x32382_0' and source = 'tablename'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'DBTables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x32382_0' and source = 'tablename'), 
'action_master_detail_BOUML_0x32382_0'
);
--UPDATE actions set name = 'PrimaryKeys' where name = 'BOUML_0x32382_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'DBTables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Actions of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Actions');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Actions', 'Actions verwalten', 'manageActions', 'Edit data of Actions', 'cache.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'action', id FROM "formulare" WHERE name = 'Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'typ', 'action_types', 'bezeichnung');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'anwendungenid', 'anwendungen', 'name');


-- Create query for actions (BOUML_0x1f702_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "target", "source", "name", "typ", "anwendungenid" from "actions"', id FROM "formulare" WHERE name = 'Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'target', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'source', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'actions', 0, 'String', id FROM "formulare" WHERE name = 'Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'typ', 'actions', 1, 'bezeichnung', 'action_types', 'Integer', id FROM "formulare" WHERE name = 'Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungenid', 'actions', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Actions', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Actions', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Actions', 1);


-- Association from Actions to Action_Steps
-- From formular 'BOUML_0x1f702_4'
-- To   formular 'BOUML_0x1f902_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21602_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21602_0', 'Aktionsschrittezuordnen', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Aktionsschrittezuordnen', 
1, 
'Action_Steps', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21602_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Actions' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21602_0' and source = 'name'), 
'action_master_detail_BOUML_0x21602_0'
);
--UPDATE actions set name = 'Aktionsschrittezuordnen' where name = 'BOUML_0x21602_0';
	
-- Association from Actions to Action_Parameters
-- From formular 'BOUML_0x1f702_4'
-- To   formular 'BOUML_0x29f02_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b502_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x2b502_0', 'AktionsParameter', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for AktionsParameter', 
1, 
'Action_Parameters', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x2b502_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Actions' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x2b502_0' and source = 'name'), 
'action_master_detail_BOUML_0x2b502_0'
);
--UPDATE actions set name = 'AktionsParameter' where name = 'BOUML_0x2b502_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Actions' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Action_Types of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Action_Types');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Action_Types', 'Action_Types verwalten', 'manageAction_Types', 'Edit data of Action_Types', 'field_types.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'type', id FROM "formulare" WHERE name = 'Action_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for action_types (BOUML_0x28582_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "bezeichnung", "action_handler", "module" from "action_types"', id FROM "formulare" WHERE name = 'Action_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'bezeichnung', 'action_types', 0, 'String', id FROM "formulare" WHERE name = 'Action_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'action_handler', 'action_types', 0, 'String', id FROM "formulare" WHERE name = 'Action_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'module', 'action_types', 0, 'String', id FROM "formulare" WHERE name = 'Action_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Action_Types', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Action_Types', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Action_Types', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Action_Types' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Action_Parameters of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Action_Parameters');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Action_Parameters', 'Action_Parameters verwalten', 'manageAction_Parameters', 'Edit data of Action_Parameters', 'antivirus.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'actionparameter', id FROM "formulare" WHERE name = 'Action_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_parameters', 'actionid', 'actions', 'name');


-- Create query for action_parameters (BOUML_0x29f02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "value", "interface", "description", "actionid" from "action_parameters"', id FROM "formulare" WHERE name = 'Action_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'action_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Action_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'value', 'action_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Action_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'interface', 'action_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Action_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'action_parameters', 0, 'String', id FROM "formulare" WHERE name = 'Action_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'actionid', 'action_parameters', 1, 'name', 'actions', 'Integer', id FROM "formulare" WHERE name = 'Action_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Action_Parameters', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Action_Parameters', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Action_Parameters', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Action_Parameters' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Action_Steps of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Action_Steps');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Action_Steps', 'Action_Steps verwalten', 'manageAction_Steps', 'Edit data of Action_Steps', 'action_steps.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'action', id FROM "formulare" WHERE name = 'Action_Steps' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'type', 'action_types', 'bezeichnung');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'actionid', 'actions', 'name');


-- Create query for action_steps (BOUML_0x1f902_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "bezeichnung", "what", "a_order_nr", "type", "actionid" from "action_steps"', id FROM "formulare" WHERE name = 'Action_Steps' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'bezeichnung', 'action_steps', 0, 'String', id FROM "formulare" WHERE name = 'Action_Steps' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'what', 'action_steps', 0, 'String', id FROM "formulare" WHERE name = 'Action_Steps' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'a_order_nr', 'action_steps', 0, 'Integer', id FROM "formulare" WHERE name = 'Action_Steps' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'type', 'action_steps', 1, 'bezeichnung', 'action_types', 'Integer', id FROM "formulare" WHERE name = 'Action_Steps' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'actionid', 'action_steps', 1, 'name', 'actions', 'Integer', id FROM "formulare" WHERE name = 'Action_Steps' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Action_Steps', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Action_Steps', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Action_Steps', 1);


-- Association from Action_Steps to ActionStep_Parameters
-- From formular 'BOUML_0x1f902_4'
-- To   formular 'BOUML_0x29f82_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b582_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x2b582_0', 'ActionstepParameters', 1, 'bezeichnung', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for ActionstepParameters', 
1, 
'ActionStep_Parameters', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x2b582_0' and source = 'bezeichnung'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Action_Steps' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x2b582_0' and source = 'bezeichnung'), 
'action_master_detail_BOUML_0x2b582_0'
);
--UPDATE actions set name = 'ActionstepParameters' where name = 'BOUML_0x2b582_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Action_Steps' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ActionStep_Parameters of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ActionStep_Parameters');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ActionStep_Parameters', 'ActionStep_Parameters verwalten', 'manageActionStep_Parameters', 'Edit data of ActionStep_Parameters', 'ktip.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'actionstepparameter', id FROM "formulare" WHERE name = 'ActionStep_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_step_parameter', 'action_step_id', 'action_steps', 'bezeichnung');


-- Create query for action_step_parameter (BOUML_0x29f82_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "description", "name", "value", "interface", "action_step_id" from "action_step_parameter"', id FROM "formulare" WHERE name = 'ActionStep_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'action_step_parameter', 0, 'String', id FROM "formulare" WHERE name = 'ActionStep_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'action_step_parameter', 0, 'String', id FROM "formulare" WHERE name = 'ActionStep_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'value', 'action_step_parameter', 0, 'String', id FROM "formulare" WHERE name = 'ActionStep_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'interface', 'action_step_parameter', 0, 'String', id FROM "formulare" WHERE name = 'ActionStep_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'action_step_id', 'action_step_parameter', 1, 'bezeichnung', 'action_steps', 'Integer', id FROM "formulare" WHERE name = 'ActionStep_Parameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ActionStep_Parameters', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ActionStep_Parameters', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ActionStep_Parameters', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ActionStep_Parameters' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Action_Step_Transitions of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Action_Step_Transitions');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Action_Step_Transitions', 'Action_Step_Transitions verwalten', 'manageAction_Step_Transitions', 'Edit data of Action_Step_Transitions', 'kate.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'actionsteptransition', id FROM "formulare" WHERE name = 'Action_Step_Transitions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_step_transitions', 'src_actionid', 'action_steps', 'bezeichnung');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_step_transitions', 'dst_actionid', 'action_steps', 'bezeichnung');


-- Create query for action_step_transitions (BOUML_0x28402_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "expression", "src_actionid", "dst_actionid", "description" from "action_step_transitions"', id FROM "formulare" WHERE name = 'Action_Step_Transitions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'expression', 'action_step_transitions', 0, 'String', id FROM "formulare" WHERE name = 'Action_Step_Transitions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'src_actionid', 'action_step_transitions', 1, 'bezeichnung', 'action_steps', 'Integer', id FROM "formulare" WHERE name = 'Action_Step_Transitions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dst_actionid', 'action_step_transitions', 1, 'bezeichnung', 'action_steps', 'Integer', id FROM "formulare" WHERE name = 'Action_Step_Transitions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'action_step_transitions', 0, 'String', id FROM "formulare" WHERE name = 'Action_Step_Transitions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Action_Step_Transitions', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Action_Step_Transitions', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Action_Step_Transitions', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Action_Step_Transitions' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class UserAccounts of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'UserAccounts');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'UserAccounts', 'UserAccounts verwalten', 'manageUserAccounts', 'Edit data of UserAccounts', 'kuser.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'UserAccounts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for users (BOUML_0x1f402_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "passwort", "userid", "vorname", "name", "secret" from "users"', id FROM "formulare" WHERE name = 'UserAccounts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'passwort', 'users', 0, 'String', id FROM "formulare" WHERE name = 'UserAccounts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'userid', 'users', 0, 'String', id FROM "formulare" WHERE name = 'UserAccounts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'vorname', 'users', 0, 'String', id FROM "formulare" WHERE name = 'UserAccounts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'users', 0, 'String', id FROM "formulare" WHERE name = 'UserAccounts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'secret', 'users', 0, 'String', id FROM "formulare" WHERE name = 'UserAccounts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'UserAccounts', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'UserAccounts', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'UserAccounts', 1);


-- Association from UserAccounts to User_Applications
-- From formular 'BOUML_0x1f402_4'
-- To   formular 'BOUML_0x1f582_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21782_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21782_0', 'AnwendungenBenutzer', 1, 'userid', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for AnwendungenBenutzer', 
1, 
'User_Applications', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21782_0' and source = 'userid'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'UserAccounts' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21782_0' and source = 'userid'), 
'action_master_detail_BOUML_0x21782_0'
);
--UPDATE actions set name = 'AnwendungenBenutzer' where name = 'BOUML_0x21782_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'UserAccounts' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Applications of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Applications');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Applications', 'Applications verwalten', 'manageApplications', 'Edit data of Applications', 'kthememgr.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'application', id FROM "formulare" WHERE name = 'Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for anwendungen (BOUML_0x1f682_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "titel", "name", "interface", "functor", "modulename" from "anwendungen"', id FROM "formulare" WHERE name = 'Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'titel', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'interface', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'functor', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'modulename', 'anwendungen', 0, 'String', id FROM "formulare" WHERE name = 'Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Applications', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Applications', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Applications', 1);


-- Association from Applications to ApplicationParameter
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f882_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21682_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21682_0', 'Anwendungsparameter', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Anwendungsparameter', 
1, 
'ApplicationParameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21682_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Applications' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21682_0' and source = 'name'), 
'action_master_detail_BOUML_0x21682_0'
);
--UPDATE actions set name = 'Anwendungsparameter' where name = 'BOUML_0x21682_0';
	
-- Association from Applications to Formulars
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21702_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21702_0', 'Formulare', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formulare', 
1, 
'Formulars', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21702_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Applications' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21702_0' and source = 'name'), 
'action_master_detail_BOUML_0x21702_0'
);
--UPDATE actions set name = 'Formulare' where name = 'BOUML_0x21702_0';
	
-- Association from Applications to DBTables
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x2f002_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x32502_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x32502_0', 'Tables', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Tables', 
1, 
'DBTables', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x32502_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Applications' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x32502_0' and source = 'name'), 
'action_master_detail_BOUML_0x32502_0'
);
--UPDATE actions set name = 'Tables' where name = 'BOUML_0x32502_0';
	

-- Create operation definitions

-- Generate codegeneration operation 'Codegenerieren' for 'Applications'

INSERT OR IGNORE INTO "actions" (name, typ, source, anwendungenid) VALUES (
'Codegenerieren', 
(select id from action_types where bezeichnung = 'Buttonpress'), 
'name',
(select id from "anwendungen" where name = 'lbDMF Manager'));
INSERT OR IGNORE INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, '', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Codegenerieren'));
INSERT OR IGNORE INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = 'Applications'), (select id from actions where name = 'Codegenerieren'), 'evt_Applications_Codegenerieren');

	
INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Applications' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ApplicationParameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ApplicationParameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ApplicationParameter', 'ApplicationParameter verwalten', 'manageApplicationParameter', 'Edit data of ApplicationParameter', 'app_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'parameter', id FROM "formulare" WHERE name = 'ApplicationParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungs_parameter', 'anwendungid', 'anwendungen', 'name');


-- Create query for anwendungs_parameter (BOUML_0x1f882_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "anwendungid" from "anwendungs_parameter"', id FROM "formulare" WHERE name = 'ApplicationParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'anwendungs_parameter', 0, 'String', id FROM "formulare" WHERE name = 'ApplicationParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'anwendungs_parameter', 0, 'String', id FROM "formulare" WHERE name = 'ApplicationParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'anwendungs_parameter', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'ApplicationParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ApplicationParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ApplicationParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ApplicationParameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ApplicationParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Applications_Formulars of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Applications_Formulars');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Applications_Formulars', 'Applications_Formulars verwalten', 'manageApplications_Formulars', 'Edit data of Applications_Formulars', 'app_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'applicationformular', id FROM "formulare" WHERE name = 'Applications_Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'anwendungid', 'anwendungen', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'formularid', 'formulare', 'name');


-- Create query for anwendungen_formulare (BOUML_0x1f602_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungid", "formularid" from "anwendungen_formulare"', id FROM "formulare" WHERE name = 'Applications_Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'anwendungen_formulare', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Applications_Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'anwendungen_formulare', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'Applications_Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Applications_Formulars', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Applications_Formulars', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Applications_Formulars', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Applications_Formulars' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formulars of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formulars');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formulars', 'Formulars verwalten', 'manageFormulars', 'Edit data of Formulars', 'kpersonalizer.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'formular', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'anwendungid', 'anwendungen', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'typ', 'formulartypen', 'beschreibung');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', '', 'formularfields', '');


-- Create query for formulare (BOUML_0x1f482_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "menuname", "menuhilfe", "eventname", "toolbarimage", "anwendungid", "typ" from "formulare"', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'menuname', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'menuhilfe', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'eventname', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'toolbarimage', 'formulare', 0, 'String', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungid', 'formulare', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'typ', 'formulare', 1, 'beschreibung', 'formulartypen', 'Integer', id FROM "formulare" WHERE name = 'Formulars' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formulars', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formulars', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formulars', 1);


INSERT OR IGNORE INTO "column_types" (name, tablename, specialcolumn, controltype) values ('toolbarimage', 'Formulars', 1, 'toolbarimagefile');

-- Association from Formulars to FormularParameter
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f502_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21802_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21802_0', 'FormularParameter', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for FormularParameter', 
1, 
'FormularParameter', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21802_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Formulars' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21802_0' and source = 'name'), 
'action_master_detail_BOUML_0x21802_0'
);
--UPDATE actions set name = 'FormularParameter' where name = 'BOUML_0x21802_0';
	
-- Association from Formulars to Formular_Actions
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f802_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21882_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21882_0', 'Formularaktionenzuordnen', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formularaktionenzuordnen', 
1, 
'Formular_Actions', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21882_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Formulars' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21882_0' and source = 'name'), 
'action_master_detail_BOUML_0x21882_0'
);
--UPDATE actions set name = 'Formularaktionenzuordnen' where name = 'BOUML_0x21882_0';
	
-- Association from Formulars to Formulare
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x21202_4'




-- Create sqlite based action
-- Select action type ActionType: , Property: 'BOUML_0x22402_0'.



-- Association from Formulars to Formular_Fields
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x26a02_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x34182_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x34182_0', 'Formular_Fields', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Formular_Fields', 
1, 
'Formular_Fields', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x34182_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Formulars' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x34182_0' and source = 'name'), 
'action_master_detail_BOUML_0x34182_0'
);
--UPDATE actions set name = 'Formular_Fields' where name = 'BOUML_0x34182_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formulars' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formular_Actions of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formular_Actions');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Actions', 'Formular_Actions verwalten', 'manageFormular_Actions', 'Edit data of Formular_Actions', 'actions_formulare.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'action', id FROM "formulare" WHERE name = 'Formular_Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'action', 'actions', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'formular', 'formulare', 'name');


-- Create query for formular_actions (BOUML_0x1f802_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "event", "action", "formular" from "formular_actions"', id FROM "formulare" WHERE name = 'Formular_Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'event', 'formular_actions', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'action', 'formular_actions', 1, 'name', 'actions', 'Integer', id FROM "formulare" WHERE name = 'Formular_Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formular', 'formular_actions', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'Formular_Actions' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formular_Actions', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formular_Actions', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formular_Actions', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formular_Actions' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FormularParameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'FormularParameter');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularParameter', 'FormularParameter verwalten', 'manageFormularParameter', 'Edit data of FormularParameter', 'formular_params.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'parameter', id FROM "formulare" WHERE name = 'FormularParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_parameters', 'formularid', 'formulare', 'name');


-- Create query for formular_parameters (BOUML_0x1f502_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername", "formularid" from "formular_parameters"', id FROM "formulare" WHERE name = 'FormularParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametervalue', 'formular_parameters', 0, 'String', id FROM "formulare" WHERE name = 'FormularParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'parametername', 'formular_parameters', 0, 'String', id FROM "formulare" WHERE name = 'FormularParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'formular_parameters', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'FormularParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FormularParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FormularParameter', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FormularParameter', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class User_Applications of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'User_Applications');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'User_Applications', 'User_Applications verwalten', 'manageUser_Applications', 'Edit data of User_Applications', 'User_application.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'User_Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'userid', 'users', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'anwendungenid', 'anwendungen', 'name');


-- Create query for user_anwendungen (BOUML_0x1f582_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "userid", "anwendungenid" from "user_anwendungen"', id FROM "formulare" WHERE name = 'User_Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'userid', 'user_anwendungen', 1, 'userid', 'users', 'Integer', id FROM "formulare" WHERE name = 'User_Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'anwendungenid', 'user_anwendungen', 1, 'name', 'anwendungen', 'Integer', id FROM "formulare" WHERE name = 'User_Applications' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'User_Applications', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'User_Applications', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'User_Applications', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'User_Applications' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Translations of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Translations');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Translations', 'Translations verwalten', 'manageTranslations', 'Edit data of Translations', 'babelfish.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Translations' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for translations (BOUML_0x1f782_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "translated", "text", "language" from "translations"', id FROM "formulare" WHERE name = 'Translations' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'translated', 'translations', 0, 'String', id FROM "formulare" WHERE name = 'Translations' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'text', 'translations', 0, 'String', id FROM "formulare" WHERE name = 'Translations' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'language', 'translations', 0, 'String', id FROM "formulare" WHERE name = 'Translations' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Translations', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Translations', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Translations', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Translations' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Reports of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Reports');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reports', 'Reports verwalten', 'manageReports', 'Edit data of Reports', 'print_class.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'Reports' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for reports (BOUML_0x1f982_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "description", "name" from "reports"', id FROM "formulare" WHERE name = 'Reports' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'reports', 0, 'String', id FROM "formulare" WHERE name = 'Reports' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'reports', 0, 'String', id FROM "formulare" WHERE name = 'Reports' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Reports', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Reports', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Reports', 1);


-- Association from Reports to ReportParameters
-- From formular 'BOUML_0x1f982_4'
-- To   formular 'BOUML_0x1fa02_4'




-- Create sqlite based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21902_0'.



-- Build up a master detail action
INSERT OR IGNORE INTO actions (target, name, typ, source, anwendungenid) select 'BOUML_0x21902_0', 'Reportparameter', 1, 'name', id from "anwendungen" where name = 'lbDMF Manager';	
INSERT OR IGNORE INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values (
'Master detail action for Reportparameter', 
1, 
'ReportParameters', 
(select id from action_types where bezeichnung = 'Open detail form'), 
(select id from actions where target = 'BOUML_0x21902_0' and source = 'name'));
INSERT OR IGNORE INTO formular_actions (formular, action, event) VALUES(
(SELECT id FROM "formulare" WHERE "name" = 'Reports' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')),
(SELECT id from actions where target = 'BOUML_0x21902_0' and source = 'name'), 
'action_master_detail_BOUML_0x21902_0'
);
--UPDATE actions set name = 'Reportparameter' where name = 'BOUML_0x21902_0';
	

-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reports' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ReportParameters of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ReportParameters');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ReportParameters', 'ReportParameters verwalten', 'manageReportParameters', 'Edit data of ReportParameters', 'kword.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'ReportParameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_parameters', 'reportid', 'reports', 'name');


-- Create query for report_parameters (BOUML_0x1fa02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "value", "name", "reportid" from "report_parameters"', id FROM "formulare" WHERE name = 'ReportParameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'value', 'report_parameters', 0, 'Integer', id FROM "formulare" WHERE name = 'ReportParameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'report_parameters', 0, 'String', id FROM "formulare" WHERE name = 'ReportParameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'reportid', 'report_parameters', 1, 'name', 'reports', 'Integer', id FROM "formulare" WHERE name = 'ReportParameters' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ReportParameters', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ReportParameters', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ReportParameters', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ReportParameters' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ReportElements of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ReportElements');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ReportElements', 'ReportElements verwalten', 'manageReportElements', 'Edit data of ReportElements', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_elements', 'reportid', 'reports', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_elements', 'typ', 'report_element_types', '');


-- Create query for report_elements (BOUML_0x2b902_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "description", "x", "y", "w", "h", "reportid", "typ" from "report_elements"', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'report_elements', 0, 'String', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'report_elements', 0, 'String', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'x', 'report_elements', 0, 'Integer', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'y', 'report_elements', 0, 'Integer', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'w', 'report_elements', 0, 'Integer', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'h', 'report_elements', 0, 'Integer', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'reportid', 'report_elements', 1, 'name', 'reports', 'Integer', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'typ', 'report_elements', 1, 'name', 'report_element_types', 'Integer', id FROM "formulare" WHERE name = 'ReportElements' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ReportElements', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ReportElements', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ReportElements', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ReportElements' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ReportElementTypes of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ReportElementTypes');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ReportElementTypes', 'ReportElementTypes verwalten', 'manageReportElementTypes', 'Edit data of ReportElementTypes', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'ReportElementTypes' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for report_element_types (BOUML_0x2ba02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "description" from "report_element_types"', id FROM "formulare" WHERE name = 'ReportElementTypes' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'report_element_types', 0, 'String', id FROM "formulare" WHERE name = 'ReportElementTypes' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'description', 'report_element_types', 0, 'String', id FROM "formulare" WHERE name = 'ReportElementTypes' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ReportElementTypes', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ReportElementTypes', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ReportElementTypes', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ReportElementTypes' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class ReportTexts of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'ReportTexts');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ReportTexts', 'ReportTexts verwalten', 'manageReportTexts', 'Edit data of ReportTexts', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'ReportTexts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_texts', 'elementid', 'report_elements', 'name');


-- Create query for report_texts (BOUML_0x2b982_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "line", "text", "elementid" from "report_texts"', id FROM "formulare" WHERE name = 'ReportTexts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'line', 'report_texts', 0, 'Integer', id FROM "formulare" WHERE name = 'ReportTexts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'text', 'report_texts', 0, 'String', id FROM "formulare" WHERE name = 'ReportTexts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'elementid', 'report_texts', 1, 'name', 'report_elements', 'Integer', id FROM "formulare" WHERE name = 'ReportTexts' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'ReportTexts', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'ReportTexts', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'ReportTexts', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ReportTexts' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Formular_Fields of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Formular_Fields');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Fields', 'Formular_Fields verwalten', 'manageFormular_Fields', 'Edit data of Formular_Fields', 'view_detailed.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'formular', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'formularid', 'formulare', 'name');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'dbtypeid', 'dbtype', 'name');


-- Create query for formularfields (BOUML_0x26a02_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "fkname", "fktable", "dbtype", "isforeignkey", "name", "tablename", "formularid", "dbtypeid" from "formularfields"', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkname', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fktable', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'dbtype', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'isforeignkey', 'formularfields', 0, 'Bit', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'formularfields', 0, 'String', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'formularid', 'formularfields', 1, 'name', 'formulare', 'Integer', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

-- dropdown field
INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, fkname, fktable, dbtype, formularid) SELECT 'dbtypeid', 'formularfields', 1, 'name', 'dbtype', 'Integer', id FROM "formulare" WHERE name = 'Formular_Fields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Formular_Fields', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Formular_Fields', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Formular_Fields', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formular_Fields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class Column_Types of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'Column_Types');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Column_Types', 'Column_Types verwalten', 'manageColumn_Types', 'Edit data of Column_Types', 'kedit.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'columntype', id FROM "formulare" WHERE name = 'Column_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('column_types', 'ro', 'boolean', '');

INSERT OR IGNORE INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('column_types', 'specialcolumn', 'boolean', '');


-- Create query for column_types (BOUML_0x28482_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "tablename", "ro", "specialcolumn", "controltype" from "column_types"', id FROM "formulare" WHERE name = 'Column_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'name', 'column_types', 0, 'String', id FROM "formulare" WHERE name = 'Column_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'tablename', 'column_types', 0, 'String', id FROM "formulare" WHERE name = 'Column_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'ro', 'column_types', 0, 'Bit', id FROM "formulare" WHERE name = 'Column_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'specialcolumn', 'column_types', 0, 'Bit', id FROM "formulare" WHERE name = 'Column_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'controltype', 'column_types', 0, 'String', id FROM "formulare" WHERE name = 'Column_Types' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'Column_Types', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'Column_Types', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'Column_Types', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Column_Types' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class FKPK_Mapping of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager in Sqlite database


--select "DropFormular"('lbDMF Manager', 'FKPK_Mapping');



INSERT OR IGNORE INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FKPK_Mapping', 'FKPK_Mapping verwalten', 'manageFKPK_Mapping', 'Edit data of FKPK_Mapping', 'kcmdf.png', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid) select 'XMLEntityName', 'entry', id FROM "formulare" WHERE name = 'FKPK_Mapping' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


-- Create query for foreignkey_visibledata_mapping (BOUML_0x28502_4)
INSERT OR IGNORE INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "pktable", "pkname", "fktable", "fkname" from "foreignkey_visibledata_mapping"', id FROM "formulare" WHERE name = 'FKPK_Mapping' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');


INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pktable', 'foreignkey_visibledata_mapping', 0, 'String', id FROM "formulare" WHERE name = 'FKPK_Mapping' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'pkname', 'foreignkey_visibledata_mapping', 0, 'String', id FROM "formulare" WHERE name = 'FKPK_Mapping' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fktable', 'foreignkey_visibledata_mapping', 0, 'String', id FROM "formulare" WHERE name = 'FKPK_Mapping' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT OR IGNORE INTO "formularfields" (name, tablename, isfk, dbtype, formularid) SELECT 'fkname', 'foreignkey_visibledata_mapping', 0, 'String', id FROM "formulare" WHERE name = 'FKPK_Mapping' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');



INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('ID', 'FKPK_Mapping', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('id', 'FKPK_Mapping', 1);
INSERT OR IGNORE INTO "column_types" (name, tablename, ro) values ('Id', 'FKPK_Mapping', 1);



-- Create operation definitions

INSERT OR IGNORE INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FKPK_Mapping' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');


		-- Class action_parameters of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_parameters', '', 'BOUML_0x1fb82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x20982_1', 'int4', -1, 0, 'action_parameters', id from dbtable where tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x20a02_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'value', 'BOUML_0x20a82_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x20b02_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x20b82_1', 'bpchar', -1, 0, 'action_parameters', id from dbtable where tableremarks = 'BOUML_0x1fb82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'actionid', 'BOUML_0x20382_0', 'int4', -1, 0, 'action_parameters', id from dbtable where tableremarks = 'BOUML_0x1fb82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_parameters', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1fb82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'actions', 'id', '', '', 'action_parameters', 'actionid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fb82_4';

		-- Class action_step_parameter of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_step_parameter', '', 'BOUML_0x1fc02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x20c02_1', 'int4', -1, 0, 'action_step_parameter', id from dbtable where tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x20c82_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'value', 'BOUML_0x20d02_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x20d82_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x20e02_1', 'bpchar', -1, 0, 'action_step_parameter', id from dbtable where tableremarks = 'BOUML_0x1fc02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'action_step_id', 'BOUML_0x1fe82_0', 'int4', -1, 0, 'action_step_parameter', id from dbtable where tableremarks = 'BOUML_0x1fc02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_step_parameter', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1fc02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_steps', 'id', '', '', 'action_step_parameter', 'action_step_id', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fc02_4';

		-- Class action_step_transitions of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_step_transitions', '', 'BOUML_0x1fc82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x20e82_1', 'int4', -1, 0, 'action_step_transitions', id from dbtable where tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'expression', 'BOUML_0x20f02_1', 'bpchar', -1, 0, 'action_step_transitions', id from dbtable where tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x20f82_1', 'bpchar', -1, 0, 'action_step_transitions', id from dbtable where tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dst_actionid', 'BOUML_0x1ff82_0', 'int4', -1, 0, 'action_step_transitions', id from dbtable where tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'src_actionid', 'BOUML_0x20082_0', 'int4', -1, 0, 'action_step_transitions', id from dbtable where tableremarks = 'BOUML_0x1fc82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_step_transitions', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1fc82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_steps', 'id', '', '', 'action_step_transitions', 'dst_actionid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fc82_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_steps', 'id', '', '', 'action_step_transitions', 'src_actionid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fc82_4';

		-- Class action_steps of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_steps', '', 'BOUML_0x1fd02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21002_1', 'int4', -1, 0, 'action_steps', id from dbtable where tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'bezeichnung', 'BOUML_0x21082_1', 'bpchar', -1, 0, 'action_steps', id from dbtable where tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'a_order_nr', 'BOUML_0x21102_1', 'int4', -1, 0, 'action_steps', id from dbtable where tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'what', 'BOUML_0x21182_1', 'bpchar', -1, 0, 'action_steps', id from dbtable where tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'type', 'BOUML_0x20182_0', 'int4', -1, 0, 'action_steps', id from dbtable where tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'actionid', 'BOUML_0x20482_0', 'int4', -1, 0, 'action_steps', id from dbtable where tableremarks = 'BOUML_0x1fd02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_steps', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1fd02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_types', 'id', '', '', 'action_steps', 'type', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fd02_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'actions', 'id', '', '', 'action_steps', 'actionid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fd02_4';

		-- Class action_types of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'action_types', '', 'BOUML_0x1fd82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21202_1', 'int4', -1, 0, 'action_types', id from dbtable where tableremarks = 'BOUML_0x1fd82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'bezeichnung', 'BOUML_0x21282_1', 'bpchar', -1, 0, 'action_types', id from dbtable where tableremarks = 'BOUML_0x1fd82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'action_handler', 'BOUML_0x21302_1', 'bpchar', -1, 0, 'action_types', id from dbtable where tableremarks = 'BOUML_0x1fd82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'module', 'BOUML_0x21382_1', 'bpchar', -1, 0, 'action_types', id from dbtable where tableremarks = 'BOUML_0x1fd82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'action_types', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1fd82_4';


		-- Class actions of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'actions', '', 'BOUML_0x1fe02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21402_1', 'int4', -1, 0, 'actions', id from dbtable where tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x21482_1', 'bpchar', -1, 0, 'actions', id from dbtable where tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'source', 'BOUML_0x21502_1', 'bpchar', -1, 0, 'actions', id from dbtable where tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'target', 'BOUML_0x21582_1', 'bpchar', -1, 0, 'actions', id from dbtable where tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typ', 'BOUML_0x20202_0', 'int4', -1, 0, 'actions', id from dbtable where tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungenid', 'BOUML_0x32702_0', 'int4', -1, 0, 'actions', id from dbtable where tableremarks = 'BOUML_0x1fe02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'actions', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1fe02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'action_types', 'id', '', '', 'actions', 'typ', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fe02_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'actions', 'anwendungenid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1fe02_4';

		-- Class anwendungen of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungen', '', 'BOUML_0x1fe82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21602_1', 'int4', -1, 0, 'anwendungen', id from dbtable where tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x21682_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'titel', 'BOUML_0x21702_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'modulename', 'BOUML_0x21782_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'functor', 'BOUML_0x21802_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tableremarks = 'BOUML_0x1fe82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x21882_1', 'bpchar', -1, 0, 'anwendungen', id from dbtable where tableremarks = 'BOUML_0x1fe82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungen', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1fe82_4';


		-- Class anwendungen_formulare of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungen_formulare', '', 'BOUML_0x1ff02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21902_1', 'int4', -1, 0, 'anwendungen_formulare', id from dbtable where tableremarks = 'BOUML_0x1ff02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x20602_0', 'int4', -1, 0, 'anwendungen_formulare', id from dbtable where tableremarks = 'BOUML_0x1ff02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x20b82_0', 'int4', -1, 0, 'anwendungen_formulare', id from dbtable where tableremarks = 'BOUML_0x1ff02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungen_formulare', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1ff02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'anwendungen_formulare', 'anwendungid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1ff02_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'anwendungen_formulare', 'formularid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1ff02_4';

		-- Class anwendungs_parameter of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungs_parameter', '', 'BOUML_0x1ff82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21982_1', 'int4', -1, 0, 'anwendungs_parameter', id from dbtable where tableremarks = 'BOUML_0x1ff82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x21a02_1', 'bpchar', -1, 0, 'anwendungs_parameter', id from dbtable where tableremarks = 'BOUML_0x1ff82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x21a82_1', 'bpchar', -1, 0, 'anwendungs_parameter', id from dbtable where tableremarks = 'BOUML_0x1ff82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x20702_0', 'int4', -1, 0, 'anwendungs_parameter', id from dbtable where tableremarks = 'BOUML_0x1ff82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungs_parameter', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x1ff82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'anwendungs_parameter', 'anwendungid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x1ff82_4';

		-- Class anwendungsberechtigungen of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'anwendungsberechtigungen', '', 'BOUML_0x20002_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21b02_1', 'int4', -1, 0, 'anwendungsberechtigungen', id from dbtable where tableremarks = 'BOUML_0x20002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'idformular', 'BOUML_0x20c82_0', 'int4', -1, 0, 'anwendungsberechtigungen', id from dbtable where tableremarks = 'BOUML_0x20002_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'iduser', 'BOUML_0x21482_0', 'int4', -1, 0, 'anwendungsberechtigungen', id from dbtable where tableremarks = 'BOUML_0x20002_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'anwendungsberechtigungen', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20002_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'anwendungsberechtigungen', 'idformular', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20002_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'users', 'id', '', '', 'anwendungsberechtigungen', 'iduser', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20002_4';

		-- Class applevel_plugin_registry of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'applevel_plugin_registry', '', 'BOUML_0x20082_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21b82_1', 'int4', -1, 0, 'applevel_plugin_registry', id from dbtable where tableremarks = 'BOUML_0x20082_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x21c02_1', 'int4', -1, 0, 'applevel_plugin_registry', id from dbtable where tableremarks = 'BOUML_0x20082_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'applevel_plugin_registry', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20082_4';


		-- Class codegentarget of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'codegentarget', '', 'BOUML_0x20102_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21c82_1', 'int4', -1, 0, 'codegentarget', id from dbtable where tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x21d02_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'titel', 'BOUML_0x21d82_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'modulename', 'BOUML_0x21e02_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'functor', 'BOUML_0x21e82_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tableremarks = 'BOUML_0x20102_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'interface', 'BOUML_0x21f02_1', 'bpchar', -1, 0, 'codegentarget', id from dbtable where tableremarks = 'BOUML_0x20102_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'codegentarget', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20102_4';


		-- Class column_types of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'column_types', '', 'BOUML_0x20182_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x21f82_1', 'int4', -1, 0, 'column_types', id from dbtable where tableremarks = 'BOUML_0x20182_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x22002_1', 'bpchar', -1, 0, 'column_types', id from dbtable where tableremarks = 'BOUML_0x20182_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x22082_1', 'bpchar', -1, 0, 'column_types', id from dbtable where tableremarks = 'BOUML_0x20182_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'controltype', 'BOUML_0x22202_1', 'bpchar', -1, 0, 'column_types', id from dbtable where tableremarks = 'BOUML_0x20182_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'column_types', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20182_4';


		-- Class foreignkey_visibledata_mapping of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'foreignkey_visibledata_mapping', '', 'BOUML_0x20202_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22282_1', 'int4', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkname', 'BOUML_0x22302_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fktable', 'BOUML_0x22382_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkname', 'BOUML_0x22402_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tableremarks = 'BOUML_0x20202_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pktable', 'BOUML_0x22482_1', 'bpchar', -1, 0, 'foreignkey_visibledata_mapping', id from dbtable where tableremarks = 'BOUML_0x20202_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'foreignkey_visibledata_mapping', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20202_4';


		-- Class formular_actions of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formular_actions', '', 'BOUML_0x20282_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22502_1', 'int4', -1, 0, 'formular_actions', id from dbtable where tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'event', 'BOUML_0x22582_1', 'bpchar', -1, 0, 'formular_actions', id from dbtable where tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'action', 'BOUML_0x20502_0', 'int4', -1, 0, 'formular_actions', id from dbtable where tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formular', 'BOUML_0x20d82_0', 'int4', -1, 0, 'formular_actions', id from dbtable where tableremarks = 'BOUML_0x20282_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formular_actions', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20282_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'actions', 'id', '', '', 'formular_actions', 'action', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20282_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formular_actions', 'formular', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20282_4';

		-- Class formular_parameters of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formular_parameters', '', 'BOUML_0x20302_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22602_1', 'int4', -1, 0, 'formular_parameters', id from dbtable where tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x22682_1', 'bpchar', -1, 0, 'formular_parameters', id from dbtable where tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x22702_1', 'bpchar', -1, 0, 'formular_parameters', id from dbtable where tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x20e82_0', 'int4', -1, 0, 'formular_parameters', id from dbtable where tableremarks = 'BOUML_0x20302_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formular_parameters', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20302_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formular_parameters', 'formularid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20302_4';

		-- Class formulare of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formulare', '', 'BOUML_0x20382_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22782_1', 'int4', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x22802_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'menuname', 'BOUML_0x22882_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'menuorder', 'BOUML_0x22902_1', 'int4', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'eventname', 'BOUML_0x22982_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'menuhilfe', 'BOUML_0x22a02_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'toolbarimage', 'BOUML_0x22a82_1', 'bpchar', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungid', 'BOUML_0x20802_0', 'int4', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typ', 'BOUML_0x20f82_0', 'int4', -1, 0, 'formulare', id from dbtable where tableremarks = 'BOUML_0x20382_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formulare', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20382_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'formulare', 'anwendungid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20382_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulartypen', 'id', '', '', 'formulare', 'typ', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20382_4';

		-- Class formulartypen of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formulartypen', '', 'BOUML_0x20402_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22b02_1', 'int4', -1, 0, 'formulartypen', id from dbtable where tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'handlermodule', 'BOUML_0x22b82_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'handlerfunctor', 'BOUML_0x22c02_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'handlerinterface', 'BOUML_0x22c82_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'namespace', 'BOUML_0x22d02_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tableremarks = 'BOUML_0x20402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'beschreibung', 'BOUML_0x22d82_1', 'bpchar', -1, 0, 'formulartypen', id from dbtable where tableremarks = 'BOUML_0x20402_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formulartypen', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20402_4';


		-- Class regressiontest of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'regressiontest', '', 'BOUML_0x20482_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22e02_1', 'int4', -1, 0, 'regressiontest', id from dbtable where tableremarks = 'BOUML_0x20482_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'test', 'BOUML_0x22e82_1', 'bpchar', -1, 0, 'regressiontest', id from dbtable where tableremarks = 'BOUML_0x20482_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'regressiontest', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20482_4';


		-- Class report_element_types of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_element_types', '', 'BOUML_0x20502_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23002_1', 'int4', -1, 0, 'report_element_types', id from dbtable where tableremarks = 'BOUML_0x20502_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23082_1', 'bpchar', -1, 0, 'report_element_types', id from dbtable where tableremarks = 'BOUML_0x20502_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x23102_1', 'bpchar', -1, 0, 'report_element_types', id from dbtable where tableremarks = 'BOUML_0x20502_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_element_types', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20502_4';


		-- Class report_elements of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_elements', '', 'BOUML_0x20582_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23182_1', 'int4', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23202_1', 'bpchar', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'x', 'BOUML_0x23282_1', 'int4', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'y', 'BOUML_0x23302_1', 'int4', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'w', 'BOUML_0x23382_1', 'int4', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'h', 'BOUML_0x23402_1', 'int4', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x23482_1', 'bpchar', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typ', 'BOUML_0x21002_0', 'int4', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'reportid', 'BOUML_0x21282_0', 'int4', -1, 0, 'report_elements', id from dbtable where tableremarks = 'BOUML_0x20582_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_elements', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20582_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'report_element_types', 'id', '', '', 'report_elements', 'typ', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20582_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'reports', 'id', '', '', 'report_elements', 'reportid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20582_4';

		-- Class report_parameters of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_parameters', '', 'BOUML_0x20602_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23502_1', 'int4', -1, 0, 'report_parameters', id from dbtable where tableremarks = 'BOUML_0x20602_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23582_1', 'bpchar', -1, 0, 'report_parameters', id from dbtable where tableremarks = 'BOUML_0x20602_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'value', 'BOUML_0x23602_1', 'int4', -1, 0, 'report_parameters', id from dbtable where tableremarks = 'BOUML_0x20602_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'reportid', 'BOUML_0x21382_0', 'int4', -1, 0, 'report_parameters', id from dbtable where tableremarks = 'BOUML_0x20602_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_parameters', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20602_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'reports', 'id', '', '', 'report_parameters', 'reportid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20602_4';

		-- Class report_texts of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report_texts', '', 'BOUML_0x20682_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23682_1', 'int4', -1, 0, 'report_texts', id from dbtable where tableremarks = 'BOUML_0x20682_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'line', 'BOUML_0x23702_1', 'int4', -1, 0, 'report_texts', id from dbtable where tableremarks = 'BOUML_0x20682_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'text', 'BOUML_0x23782_1', 'bpchar', -1, 0, 'report_texts', id from dbtable where tableremarks = 'BOUML_0x20682_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'elementid', 'BOUML_0x21102_0', 'int4', -1, 0, 'report_texts', id from dbtable where tableremarks = 'BOUML_0x20682_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report_texts', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20682_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'report_elements', 'id', '', '', 'report_texts', 'elementid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20682_4';

		-- Class reports of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'reports', '', 'BOUML_0x20702_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23802_1', 'int4', -1, 0, 'reports', id from dbtable where tableremarks = 'BOUML_0x20702_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23882_1', 'bpchar', -1, 0, 'reports', id from dbtable where tableremarks = 'BOUML_0x20702_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x23902_1', 'bpchar', -1, 0, 'reports', id from dbtable where tableremarks = 'BOUML_0x20702_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'reports', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20702_4';


		-- Class translations of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'translations', '', 'BOUML_0x20782_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23982_1', 'int4', -1, 0, 'translations', id from dbtable where tableremarks = 'BOUML_0x20782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'text', 'BOUML_0x23a02_1', 'bpchar', -1, 0, 'translations', id from dbtable where tableremarks = 'BOUML_0x20782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'translated', 'BOUML_0x23a82_1', 'bpchar', -1, 0, 'translations', id from dbtable where tableremarks = 'BOUML_0x20782_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'language', 'BOUML_0x23b02_1', 'bpchar', -1, 0, 'translations', id from dbtable where tableremarks = 'BOUML_0x20782_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'translations', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20782_4';


		-- Class user_anwendungen of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'user_anwendungen', '', 'BOUML_0x20802_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23b82_1', 'int4', -1, 0, 'user_anwendungen', id from dbtable where tableremarks = 'BOUML_0x20802_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungenid', 'BOUML_0x20902_0', 'int4', -1, 0, 'user_anwendungen', id from dbtable where tableremarks = 'BOUML_0x20802_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'userid', 'BOUML_0x21582_0', 'int4', -1, 0, 'user_anwendungen', id from dbtable where tableremarks = 'BOUML_0x20802_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'user_anwendungen', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20802_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'user_anwendungen', 'anwendungenid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20802_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'users', 'id', '', '', 'user_anwendungen', 'userid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20802_4';

		-- Class users of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'users', '', 'BOUML_0x20882_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x23c02_1', 'int4', -1, 0, 'users', id from dbtable where tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x23c82_1', 'bpchar', -1, 0, 'users', id from dbtable where tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'vorname', 'BOUML_0x23d02_1', 'bpchar', -1, 0, 'users', id from dbtable where tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'userid', 'BOUML_0x23d82_1', 'bpchar', -1, 0, 'users', id from dbtable where tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'passwort', 'BOUML_0x23e02_1', 'bpchar', -1, 0, 'users', id from dbtable where tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'lastapp', 'BOUML_0x20a02_0', 'int4', -1, 0, 'users', id from dbtable where tableremarks = 'BOUML_0x20882_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'secret', 'BOUML_0x35982_1', 'bpchar', -1, 0, 'users', id from dbtable where tableremarks = 'BOUML_0x20882_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'users', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x20882_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'users', 'lastapp', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x20882_4';

		-- Class formularfields of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formularfields', '', 'BOUML_0x26a82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x29102_1', 'int4', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x29182_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x29202_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x27f02_0', 'int4', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkname', 'BOUML_0x29302_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fktable', 'BOUML_0x29382_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtype', 'BOUML_0x29282_1', 'bpchar', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'isfk', 'BOUML_0x2eb82_1', 'BOOLEAN', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtypeid', 'BOUML_0x32602_0', 'int4', -1, 0, 'formularfields', id from dbtable where tableremarks = 'BOUML_0x26a82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formularfields', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x26a82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formularfields', 'formularid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x26a82_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtype', 'id', '', '', 'formularfields', 'dbtypeid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x26a82_4';

		-- Class tipmessage of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'tipmessage', '', 'BOUML_0x2d382_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x33f02_1', 'int4', -1, 0, 'tipmessage', id from dbtable where tableremarks = 'BOUML_0x2d382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'caption', 'BOUML_0x33f82_1', 'bpchar', -1, 0, 'tipmessage', id from dbtable where tableremarks = 'BOUML_0x2d382_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'message', 'BOUML_0x34002_1', 'bpchar', -1, 0, 'tipmessage', id from dbtable where tableremarks = 'BOUML_0x2d382_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'tipmessage', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x2d382_4';


		-- Class formulare_tipmessage of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formulare_tipmessage', '', 'BOUML_0x2d402_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x2e982_0', 'int4', -1, 0, 'formulare_tipmessage', id from dbtable where tableremarks = 'BOUML_0x2d402_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tipmessageid', 'BOUML_0x2eb02_0', 'int4', -1, 0, 'formulare_tipmessage', id from dbtable where tableremarks = 'BOUML_0x2d402_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formulare_tipmessage', 'formularid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x2d402_4';

INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'tipmessage', 'id', '', '', 'formulare_tipmessage', 'tipmessageid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x2d402_4';

		-- Class dbtable of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbtable', '', 'BOUML_0x2ed82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x38c82_1', 'int4', -1, 0, 'dbtable', id from dbtable where tableremarks = 'BOUML_0x2ed82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'catalogname', 'BOUML_0x38d02_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tableremarks = 'BOUML_0x2ed82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'schemaname', 'BOUML_0x38d82_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tableremarks = 'BOUML_0x2ed82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x38e02_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tableremarks = 'BOUML_0x2ed82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tabletype', 'BOUML_0x38e82_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tableremarks = 'BOUML_0x2ed82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tableremarks', 'BOUML_0x38f02_1', 'bpchar', -1, 0, 'dbtable', id from dbtable where tableremarks = 'BOUML_0x2ed82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'anwendungenid', 'BOUML_0x32482_0', 'int4', -1, 0, 'dbtable', id from dbtable where tableremarks = 'BOUML_0x2ed82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbtable', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x2ed82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'anwendungen', 'id', '', '', 'dbtable', 'anwendungenid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x2ed82_4';

		-- Class dbcolumn of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbcolumn', '', 'BOUML_0x2ee02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x38f82_1', 'int4', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnname', 'BOUML_0x39002_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnremarks', 'BOUML_0x39082_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'typename', 'BOUML_0x39102_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnsize', 'BOUML_0x39182_1', 'int4', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'nullable', 'BOUML_0x39202_1', 'BOOLEAN', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x39282_1', 'bpchar', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtableid', 'BOUML_0x30502_0', 'int4', -1, 0, 'dbcolumn', id from dbtable where tableremarks = 'BOUML_0x2ee02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbcolumn', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x2ee02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtable', 'id', '', '', 'dbcolumn', 'dbtableid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x2ee02_4';

		-- Class dbforeignkey of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbforeignkey', '', 'BOUML_0x2ee82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x39302_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkcatalog', 'BOUML_0x39382_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkschema', 'BOUML_0x39402_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pktable', 'BOUML_0x39482_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'pkcolumn', 'BOUML_0x39502_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkcatalog', 'BOUML_0x39582_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkschema', 'BOUML_0x39602_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fktable', 'BOUML_0x39682_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'fkcolumn', 'BOUML_0x39702_1', 'bpchar', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'keysequence', 'BOUML_0x39782_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'updaterule', 'BOUML_0x39802_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'deleterule', 'BOUML_0x39882_1', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtableid', 'BOUML_0x30582_0', 'int4', -1, 0, 'dbforeignkey', id from dbtable where tableremarks = 'BOUML_0x2ee82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbforeignkey', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x2ee82_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtable', 'id', '', '', 'dbforeignkey', 'dbtableid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x2ee82_4';

		-- Class dbprimarykey of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbprimarykey', '', 'BOUML_0x2ef02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x39902_1', 'int4', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablecatalog', 'BOUML_0x39982_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tableschema', 'BOUML_0x39a02_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'tablename', 'BOUML_0x39a82_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnname', 'BOUML_0x39b02_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'columnname2', 'BOUML_0x39b82_1', 'bpchar', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'keysequence', 'BOUML_0x39c02_1', 'int4', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'dbtableid', 'BOUML_0x30682_0', 'int4', -1, 0, 'dbprimarykey', id from dbtable where tableremarks = 'BOUML_0x2ef02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbprimarykey', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x2ef02_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'dbtable', 'id', '', '', 'dbprimarykey', 'dbtableid', 0, 0, 0, id from dbtable where tableremarks = 'BOUML_0x2ef02_4';

		-- Class dbtype of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'dbtype', '', 'BOUML_0x30a82_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x3c582_1', 'int4', -1, 0, 'dbtype', id from dbtable where tableremarks = 'BOUML_0x30a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'name', 'BOUML_0x3c602_1', 'bpchar', -1, 0, 'dbtype', id from dbtable where tableremarks = 'BOUML_0x30a82_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'description', 'BOUML_0x3c682_1', 'bpchar', -1, 0, 'dbtype', id from dbtable where tableremarks = 'BOUML_0x30a82_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'dbtype', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x30a82_4';


		-- Class report of type FORM found.
					
INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'report', '', 'BOUML_0x30b02_4', id from anwendungen where name = 'lbDMF Manager';


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x3c882_1', 'int4', -1, 0, 'report', id from dbtable where tableremarks = 'BOUML_0x30b02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'report_name', 'BOUML_0x3c702_1', 'bpchar', -1, 0, 'report', id from dbtable where tableremarks = 'BOUML_0x30b02_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'report_grade', 'BOUML_0x3c782_1', 'int4', -1, 0, 'report', id from dbtable where tableremarks = 'BOUML_0x30b02_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'report', 'id',  '', 0, id from dbtable where tableremarks = 'BOUML_0x30b02_4';


		-- Class Formulare of type FORM found.
					
-- Generate DMF report definition for Reports in PostgreSQL database 


-- select dropreport('Reports', 'Formulare');



-- insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) values ('Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', '', getorcreateapplication('Reports'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));


delete from report where report_name = 'ReportFormulare';
insert into report (report_name, report_grade, report_source) values('ReportFormulare', 0, '<!DOCTYPE openRPTDef>
<report>
 <title></title>
 <name></name>
 <description></description>
 <size>A4</size>
 <portrait/>
 <topmargin>100</topmargin>
 <bottommargin>100</bottommargin>
 <rightmargin>100</rightmargin>
 <leftmargin>100</leftmargin>
 <querysource>
  <name>FormularQuery</name>
  <sql>select "name", "menuname", "menuorder", "eventname", "menuhilfe", "toolbarimage" from Formulare
order by id</sql>
 </querysource>
 <pghead>
  <height>75</height>



  <label>
   <rect>
    <x>5</x>
    <y>25</y>
    <width>100</width>
    <height>25</height>
   </rect>
   <font>
    <face>Helvetica</face>
    <size>12</size>
    <weight>normal</weight>
   </font>
   <left/>
   <top/>
   <string>name</string>
  </label>
			
  <label>
   <rect>
    <x>93.8333333333333</x>
    <y>25</y>
    <width>100</width>
    <height>25</height>
   </rect>
   <font>
    <face>Helvetica</face>
    <size>12</size>
    <weight>normal</weight>
   </font>
   <left/>
   <top/>
   <string>menuname</string>
  </label>
			
  <label>
   <rect>
    <x>182.666666666667</x>
    <y>25</y>
    <width>100</width>
    <height>25</height>
   </rect>
   <font>
    <face>Helvetica</face>
    <size>12</size>
    <weight>normal</weight>
   </font>
   <left/>
   <top/>
   <string>menuorder</string>
  </label>
			
  <label>
   <rect>
    <x>271.5</x>
    <y>25</y>
    <width>100</width>
    <height>25</height>
   </rect>
   <font>
    <face>Helvetica</face>
    <size>12</size>
    <weight>normal</weight>
   </font>
   <left/>
   <top/>
   <string>eventname</string>
  </label>
			
  <label>
   <rect>
    <x>360.333333333333</x>
    <y>25</y>
    <width>100</width>
    <height>25</height>
   </rect>
   <font>
    <face>Helvetica</face>
    <size>12</size>
    <weight>normal</weight>
   </font>
   <left/>
   <top/>
   <string>menuhilfe</string>
  </label>
			
  <label>
   <rect>
    <x>449.166666666667</x>
    <y>25</y>
    <width>100</width>
    <height>25</height>
   </rect>
   <font>
    <face>Helvetica</face>
    <size>12</size>
    <weight>normal</weight>
   </font>
   <left/>
   <top/>
   <string>toolbarimage</string>
  </label>
			

  <line>
   <xstart>0</xstart>
   <ystart>20</ystart>
   <xend>625</xend>
   <yend>20</yend>
   <weight>2</weight>
  </line>
  <line>
   <xstart>0</xstart>
   <ystart>75</ystart>
   <xend>625</xend>
   <yend>75</yend>
   <weight>2</weight>
  </line>
 </pghead>
 
 <section>
  <name>Formulare</name>
  <detail>
   <key>
    <query>FormularQuery</query>
   </key>
   <height>70</height>




   <field>
    <rect>
     <x>5</x>
     <y>25</y>
     <width>100</width>
     <height>20</height>
    </rect>
    <font>
     <face>Helvetica</face>
     <size>10</size>
     <weight>normal</weight>
    </font>
    <left/>
    <top/>
    <data>
     <query>FormularQuery</query>
     <column>name</column>
    </data>
   </field>
			
   <field>
    <rect>
     <x>93.8333333333333</x>
     <y>25</y>
     <width>100</width>
     <height>20</height>
    </rect>
    <font>
     <face>Helvetica</face>
     <size>10</size>
     <weight>normal</weight>
    </font>
    <left/>
    <top/>
    <data>
     <query>FormularQuery</query>
     <column>menuname</column>
    </data>
   </field>
			
   <field>
    <rect>
     <x>182.666666666667</x>
     <y>25</y>
     <width>100</width>
     <height>20</height>
    </rect>
    <font>
     <face>Helvetica</face>
     <size>10</size>
     <weight>normal</weight>
    </font>
    <left/>
    <top/>
    <data>
     <query>FormularQuery</query>
     <column>menuorder</column>
    </data>
   </field>
			
   <field>
    <rect>
     <x>271.5</x>
     <y>25</y>
     <width>100</width>
     <height>20</height>
    </rect>
    <font>
     <face>Helvetica</face>
     <size>10</size>
     <weight>normal</weight>
    </font>
    <left/>
    <top/>
    <data>
     <query>FormularQuery</query>
     <column>eventname</column>
    </data>
   </field>
			
   <field>
    <rect>
     <x>360.333333333333</x>
     <y>25</y>
     <width>100</width>
     <height>20</height>
    </rect>
    <font>
     <face>Helvetica</face>
     <size>10</size>
     <weight>normal</weight>
    </font>
    <left/>
    <top/>
    <data>
     <query>FormularQuery</query>
     <column>menuhilfe</column>
    </data>
   </field>
			
   <field>
    <rect>
     <x>449.166666666667</x>
     <y>25</y>
     <width>100</width>
     <height>20</height>
    </rect>
    <font>
     <face>Helvetica</face>
     <size>10</size>
     <weight>normal</weight>
    </font>
    <left/>
    <top/>
    <data>
     <query>FormularQuery</query>
     <column>toolbarimage</column>
    </data>
   </field>
			
   
   <line>
    <xstart>0</xstart>
    <ystart>60</ystart>
    <xend>625</xend>
    <yend>60</yend>
    <weight>0</weight>
   </line>
  </detail>
 </section>
</report>');




-- Activity operation for class Applications in package lbDMF Manager is CreateSystemApplication.
-- Operation is a validator using activity 
-- Activity ID is 'BOUML_0x20e02_39'
		-- Activity 'CreateSystemApplication' found.
			
-- Generate statemachine for BOUML_0x20e02_39
-- select "CreateActivityOnMissing"('BOUML_0x20e02_39', 'CreateSystemApplication');

-- Delete old statemachine
delete from "action_step_parameter" where "action_step_id" in (select id from "action_steps" where "actionid" in (select "id" from "actions" where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager')));
delete from "action_step_transitions" where "description" = '_BOUML_0x20e02_39';
delete from "action_steps" where "actionid" in (select "id" from "actions" where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager'));
delete from "formular_actions" where action in (select id from actions where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager'));
delete from "actions" where "target" = 'BOUML_0x20e02_39' AND "anwendungenid" = (select id from "anwendungen" where name = 'lbDMF Manager');

-- A form validator should be used before saving the changes to the database

INSERT OR IGNORE INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('CreateSystemApplication_BOUML_0x20e02_39', 'instanceOflbAction', 'lbDatabaseForm');

INSERT OR IGNORE INTO "actions" ("name", "typ", "source", "target", "anwendungenid") VALUES (
'CreateSystemApplication', 
(select "id" from "action_types" where "bezeichnung" = 'Buttonpress'),
'name',
'BOUML_0x20e02_39', 
(select id from "anwendungen" where name = 'lbDMF Manager'));

INSERT OR IGNORE INTO "formular_actions" ("formular", "action", "event") VALUES (
(select "id" from "formulare" where "name" = 'Applications'), 
(select "id" from "actions" where "target" = 'BOUML_0x20e02_39'),
'eventCreateSystemApplication_BOUML_0x20e02_39_Buttonpress');
	
-- Create activity nodes for Sqlite

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x22982_70', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x22a02_72', '2', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24202_56', '3', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '{BasePath}/AppDevelopmentDemo/DynamicApp/XSLT_Templates/DMFToDataModel/generate.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

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

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '{BasePath}\AppDevelopmentDemo\DynamicApp\XSLT_Templates\DMFToDataModel\generate.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29082_56', '8', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '{BasePath}/AppDevelopmentDemo/DynamicApp/XSLT_Templates/DMFToDataModel/generate.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29102_46', '9', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2aa82_56', '10', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'System Code Generator', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Generate code for {OSType}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

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

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '{BasePath}\XSLT\DMFToDataModel\generate.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2de02_56', '17', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2de02_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', 'Q:\\develop\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\SecondStageModels\\lbDMF ', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2de02_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', 'Q:\\develop\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\importUML-ApplicationDB.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2de02_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2de82_56', '18', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2df02_56', '19', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2df82_56', '20', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2e002_56', '21', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2e082_56', '22', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2e102_56', '23', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2e102_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{BasePath}\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\SecondStageModels\\lbDMF Manager.xmi', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2e102_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '{BasePath}\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\importUML-SystemDB.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2e102_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2e182_56', '24', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2e182_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{BasePath}\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\SecondStageModels\\lbDMF Manager.xmi', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2e182_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '{BasePath}\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\importUML-ApplicationDB.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2e182_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x27782_73', '25', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2fb82_56', '26', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'writeStringToFile', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fb82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{systemDDL}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fb82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '{BasePath}\\Database\\lbDMF-Sqlite-SystemDB.sql', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fb82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2fc02_56', '27', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'writeStringToFile', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fc02_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{applicationDDL}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fc02_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '{BasePath}\\Database\\lbDMF-Sqlite-SystemDB.sql', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fc02_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2fc82_56', '28', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'writeStringToFile', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fc82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{CombinedDDL}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fc82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '{BasePath}\\Database\\lbDMF-PostgreSQL.sql', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fc82_56'));

INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2fd02_46', '29', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
INSERT OR IGNORE INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2fd82_56', '30', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Plattform', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fd82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fd82_56'));

INSERT OR IGNORE INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Es wurde Code in einer Endbenutzer Installation generiert', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2fd82_56'));

-- Create activity transitions

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22982_70'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2df02_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

UPDATE "action_step_transitions" set "expression" = 'file = lala.xml' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2de02_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e002_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22a02_72'));

UPDATE "action_step_transitions" set "expression" = 'result = 1' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22a02_72');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Unix"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

UPDATE "action_step_transitions" set "expression" = 'BasePath = /home/lothar/develop/Projects/CPP' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Mac"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

UPDATE "action_step_transitions" set "expression" = 'BasePath = /Users/lothar/develop/Projects/CPP' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Windows"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('result == 1', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

UPDATE "action_step_transitions" set "expression" = 'BasePath = \\develop\\Projects\\CPP' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('result == 0', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

UPDATE "action_step_transitions" set "expression" = 'BasePath = \\lbDMF' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fd82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2de02_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2de82_56'));

UPDATE "action_step_transitions" set "expression" = 'systemDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2de02_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2de82_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2de82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73'));

UPDATE "action_step_transitions" set "expression" = 'applicationDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2de82_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2df02_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2df82_56'));

UPDATE "action_step_transitions" set "expression" = 'systemDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2df02_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2df82_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2df82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73'));

UPDATE "action_step_transitions" set "expression" = 'applicationDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2df82_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e002_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e082_56'));

UPDATE "action_step_transitions" set "expression" = 'systemDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e002_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e082_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e082_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73'));

UPDATE "action_step_transitions" set "expression" = 'applicationDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e082_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e102_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e182_56'));

UPDATE "action_step_transitions" set "expression" = 'systemDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e102_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e182_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e182_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73'));

UPDATE "action_step_transitions" set "expression" = 'applicationDDL = {stepout}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e182_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('backend == DatabaseLayerGateway', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fb82_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fd02_46'));

UPDATE "action_step_transitions" set "expression" = 'CombinedDDL = {applicationDDL}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x27782_73') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fd02_46');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fb82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fc02_56'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fc02_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fc82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fd02_46'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fc82_56'));

UPDATE "action_step_transitions" set "expression" = 'CombinedDDL += {systemDDL}' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fd02_46') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fc82_56');

INSERT OR IGNORE INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2fd82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2e102_56'));

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
		
UPDATE "action_steps" set "bezeichnung" = 'transformXSLT' where "bezeichnung" = 'BOUML_0x2de02_56';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x2de82_56';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x2df02_56';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x2df82_56';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x2e002_56';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x2e082_56';
		
UPDATE "action_steps" set "bezeichnung" = 'transformXSLT' where "bezeichnung" = 'BOUML_0x2e102_56';
		
UPDATE "action_steps" set "bezeichnung" = 'transformXSLT' where "bezeichnung" = 'BOUML_0x2e182_56';
		
UPDATE "action_steps" set "bezeichnung" = '' where "bezeichnung" = 'BOUML_0x27782_73';
		
UPDATE "action_steps" set "bezeichnung" = 'writeStringToFile' where "bezeichnung" = 'BOUML_0x2fb82_56';
		
UPDATE "action_steps" set "bezeichnung" = 'writeStringToFile' where "bezeichnung" = 'BOUML_0x2fc02_56';
		
UPDATE "action_steps" set "bezeichnung" = 'writeStringToFile' where "bezeichnung" = 'BOUML_0x2fc82_56';
		
UPDATE "action_steps" set "bezeichnung" = 'Combine DDL files in transition' where "bezeichnung" = 'BOUML_0x2fd02_46';
		
UPDATE "action_steps" set "bezeichnung" = 'showMsgBox' where "bezeichnung" = 'BOUML_0x2fd82_56';
		

-- Cleanup unused double types
DELETE FROM "action_types" where "id" NOT IN (SELECT "typ" from "actions") AND "id" NOT IN (SELECT "type" from "action_steps");


-- Activity operation for class Applications in package lbDMF Manager is actValidateAnwendungen.
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
(select "id" from "formulare" where "name" = 'Applications'), 
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


-- Script ready.
COMMIT;
