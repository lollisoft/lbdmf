
-- Speedup many times
BEGIN TRANSACTION;

-- Params XSLDatabaseBackendSystem: 
-- Params XSLDatabaseBackendApplication: 
-- Params overwriteDatabase: 

--
-- SQL script created for Sqlite
--
	

-- Class Anwendungen of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class FormularFields of type FORM found.
				
-- Class Benutzer of type FORM found.
				
-- Class DBType of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
-- Class FormularTypen of type FORM found.
				
-- Class Tables of type FORM found.
				
-- Class Columns of type FORM found.
				
-- Class PrimaryKeys of type FORM found.
				
-- Class ForeignKeys of type FORM found.
				
-- Class TableParameter of type FORM found.
				
-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_parameters
CREATE TABLE "action_parameters" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"value" BPCHAR,
	"interface" BPCHAR,
	"description" BPCHAR,
	"actionid" INTEGER
);

-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_parameter for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_step_parameter
CREATE TABLE "action_step_parameter" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"value" BPCHAR,
	"interface" BPCHAR,
	"description" BPCHAR,
	"action_step_id" INTEGER
);

-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_transitions for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_step_transitions
CREATE TABLE "action_step_transitions" (
	"id" INTEGER PRIMARY KEY,
	"expression" BPCHAR,
	"description" BPCHAR,
	"dst_actionid" INTEGER,
	"src_actionid" INTEGER
);

-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_steps
CREATE TABLE "action_steps" (
	"id" INTEGER PRIMARY KEY,
	"bezeichnung" BPCHAR,
	"a_order_nr" INTEGER,
	"what" BPCHAR,
	"type" INTEGER,
	"actionid" INTEGER
);

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_types
CREATE TABLE "action_types" (
	"id" INTEGER PRIMARY KEY,
	"bezeichnung" BPCHAR,
	"action_handler" BPCHAR,
	"module" BPCHAR
);

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE actions
CREATE TABLE "actions" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"source" BPCHAR,
	"target" BPCHAR,
	"typ" INTEGER,
	"anwendungenid" INTEGER
);

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE anwendungen
CREATE TABLE "anwendungen" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"titel" BPCHAR,
	"modulename" BPCHAR,
	"functor" BPCHAR,
	"interface" BPCHAR,
	"requirements" BYTEA,
	"background" BYTEA,
	"model_complete" BOOLEAN,
	"model_errors" TEXT
);

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE anwendungen_formulare
CREATE TABLE "anwendungen_formulare" (
	"id" INTEGER PRIMARY KEY,
	"anwendungid" INTEGER,
	"formularid" INTEGER,
	"purpose" BPCHAR
);

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE anwendungs_parameter
CREATE TABLE "anwendungs_parameter" (
	"id" INTEGER PRIMARY KEY,
	"parametername" BPCHAR,
	"parametervalue" BPCHAR,
	"anwendungid" INTEGER
);

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE anwendungsberechtigungen
CREATE TABLE "anwendungsberechtigungen" (
	"id" INTEGER PRIMARY KEY,
	"idformular" INTEGER,
	"iduser" INTEGER
);

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE applevel_plugin_registry
CREATE TABLE "applevel_plugin_registry" (
	"id" INTEGER PRIMARY KEY,
	"anwendungid" INTEGER
);

-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE codegentarget
CREATE TABLE "codegentarget" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"titel" BPCHAR,
	"modulename" BPCHAR,
	"functor" BPCHAR,
	"interface" BPCHAR
);

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE column_types
CREATE TABLE "column_types" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"tablename" BPCHAR,
	"ro" BOOLEAN,
	"specialcolumn" BOOLEAN,
	"controltype" BPCHAR
);

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE foreignkey_visibledata_mapping
CREATE TABLE "foreignkey_visibledata_mapping" (
	"id" INTEGER PRIMARY KEY,
	"fkname" BPCHAR,
	"fktable" BPCHAR,
	"pkname" BPCHAR,
	"pktable" BPCHAR
);

-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE formular_actions
CREATE TABLE "formular_actions" (
	"id" INTEGER PRIMARY KEY,
	"event" BPCHAR,
	"action" INTEGER,
	"formular" INTEGER
);

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE formular_parameters
CREATE TABLE "formular_parameters" (
	"id" INTEGER PRIMARY KEY,
	"parametername" BPCHAR,
	"parametervalue" BPCHAR,
	"formularid" INTEGER
);

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE formulare
CREATE TABLE "formulare" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"menuname" BPCHAR,
	"menuorder" INTEGER,
	"eventname" BPCHAR,
	"menuhilfe" BPCHAR,
	"toolbarimage" BPCHAR,
	"anwendungid" INTEGER,
	"typ" INTEGER
);

-- Class formularfields of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formularfields for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE formularfields
CREATE TABLE "formularfields" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"tablename" BPCHAR,
	"formularid" INTEGER,
	"dbtypeid" INTEGER,
	"isfk" BOOLEAN,
	"fkname" BPCHAR,
	"fktable" BPCHAR,
	"dbtype" BPCHAR
);

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE formulartypen
CREATE TABLE "formulartypen" (
	"id" INTEGER PRIMARY KEY,
	"handlermodule" BPCHAR,
	"handlerfunctor" BPCHAR,
	"handlerinterface" BPCHAR,
	"namespace" BPCHAR,
	"beschreibung" BPCHAR
);

-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE regressiontest
CREATE TABLE "regressiontest" (
	"id" INTEGER PRIMARY KEY,
	"test" BPCHAR,
	"btest" BOOLEAN,
	"btest1" BOOLEAN
);

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE report_element_types
CREATE TABLE "report_element_types" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"description" BPCHAR
);

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE report_elements
CREATE TABLE "report_elements" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"x" INTEGER,
	"y" INTEGER,
	"w" INTEGER,
	"h" INTEGER,
	"description" BPCHAR,
	"typ" INTEGER,
	"reportid" INTEGER
);

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE report_parameters
CREATE TABLE "report_parameters" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"value" INTEGER,
	"reportid" INTEGER
);

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE report_texts
CREATE TABLE "report_texts" (
	"id" INTEGER PRIMARY KEY,
	"line" INTEGER,
	"text" BPCHAR,
	"elementid" INTEGER
);

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE reports
CREATE TABLE "reports" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"description" BPCHAR
);

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE translations
CREATE TABLE "translations" (
	"id" INTEGER PRIMARY KEY,
	"text" BPCHAR,
	"translated" BPCHAR,
	"language" BPCHAR
);

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE user_anwendungen
CREATE TABLE "user_anwendungen" (
	"id" INTEGER PRIMARY KEY,
	"anwendungenid" INTEGER,
	"userid" INTEGER
);

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE users
CREATE TABLE "users" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"vorname" BPCHAR,
	"userid" BPCHAR,
	"passwort" BPCHAR,
	"lastapp" INTEGER
);

-- Class dbtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtype for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE dbtype
CREATE TABLE "dbtype" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"description" BPCHAR
);

-- Class dbtable of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtable for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE dbtable
CREATE TABLE "dbtable" (
	"id" INTEGER PRIMARY KEY,
	"catalogname" BPCHAR,
	"schemaname" BPCHAR,
	"tablename" BPCHAR,
	"tabletype" BPCHAR,
	"tableremarks" BPCHAR,
	"anwendungenid" INTEGER
);

-- Class dbcolumn of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbcolumn for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE dbcolumn
CREATE TABLE "dbcolumn" (
	"id" INTEGER PRIMARY KEY,
	"columnname" BPCHAR,
	"columnremarks" BPCHAR,
	"typename" BPCHAR,
	"columnsize" INTEGER,
	"nullable" BOOLEAN,
	"tablename" BPCHAR,
	"dbtableid" INTEGER
);

-- Class dbforeignkey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbforeignkey for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE dbforeignkey
CREATE TABLE "dbforeignkey" (
	"id" INTEGER PRIMARY KEY,
	"pkcatalog" BPCHAR,
	"pkschema" BPCHAR,
	"pktable" BPCHAR,
	"pkcolumn" BPCHAR,
	"fkcatalog" BPCHAR,
	"fkschema" BPCHAR,
	"fktable" BPCHAR,
	"fkcolumn" BPCHAR,
	"keysequence" INTEGER,
	"updaterule" INTEGER,
	"deleterule" INTEGER,
	"dbtableid" INTEGER
);

-- Class dbprimarykey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbprimarykey for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE dbprimarykey
CREATE TABLE "dbprimarykey" (
	"id" INTEGER PRIMARY KEY,
	"tablecatalog" BPCHAR,
	"tableschema" BPCHAR,
	"tablename" BPCHAR,
	"columnname" BPCHAR,
	"columnname2" BPCHAR,
	"keysequence" INTEGER,
	"dbtableid" INTEGER
);

-- Unknown stereotype 'filterdefinition' for class UserFilter.
-- Create table via importApplicationTableAutoID

-- Class dbtableparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtableparameter for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE dbtableparameter
CREATE TABLE "dbtableparameter" (
	"id" INTEGER PRIMARY KEY,
	"parametername" BPCHAR,
	"parametervalue" BPCHAR,
	"dbtableid" INTEGER
);

-- Class Anwendungen of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class FormularFields of type FORM found.
				
-- Class Benutzer of type FORM found.
				
-- Class DBType of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
-- Class FormularTypen of type FORM found.
				
-- Class Tables of type FORM found.
				
-- Class Columns of type FORM found.
				
-- Class PrimaryKeys of type FORM found.
				
-- Class ForeignKeys of type FORM found.
				
-- Class TableParameter of type FORM found.
				
-- Class action_parameters of type ENTITY found.

-- Generate application tables action_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class action_step_parameter of type ENTITY found.

-- Generate application tables action_step_parameter for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class action_step_transitions of type ENTITY found.

-- Generate application tables action_step_transitions for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class action_steps of type ENTITY found.

-- Generate application tables action_steps for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class action_types of type ENTITY found.

-- Generate application tables action_types for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class actions of type ENTITY found.

-- Generate application tables actions for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class anwendungen of type ENTITY found.

-- Generate application tables anwendungen for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class anwendungen_formulare of type ENTITY found.

-- Generate application tables anwendungen_formulare for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class anwendungs_parameter of type ENTITY found.

-- Generate application tables anwendungs_parameter for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class anwendungsberechtigungen of type ENTITY found.

-- Generate application tables anwendungsberechtigungen for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class applevel_plugin_registry of type ENTITY found.

-- Generate application tables applevel_plugin_registry for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class codegentarget of type ENTITY found.

-- Generate application tables codegentarget for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class column_types of type ENTITY found.

-- Generate application tables column_types for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class foreignkey_visibledata_mapping of type ENTITY found.

-- Generate application tables foreignkey_visibledata_mapping for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class formular_actions of type ENTITY found.

-- Generate application tables formular_actions for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class formular_parameters of type ENTITY found.

-- Generate application tables formular_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class formulare of type ENTITY found.

-- Generate application tables formulare for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class formularfields of type ENTITY found.

-- Generate application tables formularfields for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class formulartypen of type ENTITY found.

-- Generate application tables formulartypen for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class regressiontest of type ENTITY found.

-- Generate application tables regressiontest for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class report_element_types of type ENTITY found.

-- Generate application tables report_element_types for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class report_elements of type ENTITY found.

-- Generate application tables report_elements for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class report_parameters of type ENTITY found.

-- Generate application tables report_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class report_texts of type ENTITY found.

-- Generate application tables report_texts for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class reports of type ENTITY found.

-- Generate application tables reports for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class translations of type ENTITY found.

-- Generate application tables translations for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class user_anwendungen of type ENTITY found.

-- Generate application tables user_anwendungen for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class users of type ENTITY found.

-- Generate application tables users for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class dbtype of type ENTITY found.

-- Generate application tables dbtype for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class dbtable of type ENTITY found.

-- Generate application tables dbtable for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class dbcolumn of type ENTITY found.

-- Generate application tables dbcolumn for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class dbforeignkey of type ENTITY found.

-- Generate application tables dbforeignkey for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class dbprimarykey of type ENTITY found.

-- Generate application tables dbprimarykey for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class dbtableparameter of type ENTITY found.

-- Generate application tables dbtableparameter for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Generate Sqlite application relations for table action_parameters for lbDMFManager_Entities
-- Create table relations for action_parameters
--ALTER TABLE "action_parameters" ADD CONSTRAINT "cst_action_parameters_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "action_parameters" ADD CONSTRAINT "cst_action_parameters_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_parameters_actionid_ins" BEFORE INSERT ON action_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: actionid violates foreign key actions(id = SELECT new.actionid)')
    END;
END;
CREATE TRIGGER "fk_action_parameters_actionid_upd" BEFORE UPDATE ON action_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: actionid violates foreign key actions(id)')
    END;
END;
CREATE TRIGGER "fk_action_parameters_actionid_del" BEFORE DELETE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT actionid FROM action_parameters WHERE actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key action_parameters(actionid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('actions', 'id', 'action_parameters', 'actionid');
 

-- Generate Sqlite application relations for table action_step_parameter for lbDMFManager_Entities
-- Create table relations for action_step_parameter
--ALTER TABLE "action_step_parameter" ADD CONSTRAINT "cst_action_step_parameter_action_steps_id" FOREIGN KEY ( "action_step_id" ) REFERENCES "action_steps" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "action_step_parameter" ADD CONSTRAINT "cst_action_step_parameter_action_steps_id" FOREIGN KEY ( "action_step_id" ) REFERENCES "action_steps" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_step_parameter_action_step_id_ins" BEFORE INSERT ON action_step_parameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action_step_id IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.action_step_id) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: action_step_id violates foreign key action_steps(id = SELECT new.action_step_id)')
    END;
END;
CREATE TRIGGER "fk_action_step_parameter_action_step_id_upd" BEFORE UPDATE ON action_step_parameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action_step_id IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.action_step_id) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: action_step_id violates foreign key action_steps(id)')
    END;
END;
CREATE TRIGGER "fk_action_step_parameter_action_step_id_del" BEFORE DELETE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT action_step_id FROM action_step_parameter WHERE action_step_id = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key action_step_parameter(action_step_id = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_steps', 'id', 'action_step_parameter', 'action_step_id');
 

-- Generate Sqlite application relations for table action_step_transitions for lbDMFManager_Entities
-- Create table relations for action_step_transitions
--ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_action_steps_id" FOREIGN KEY ( "dst_actionid" ) REFERENCES "action_steps" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_action_steps_id" FOREIGN KEY ( "dst_actionid" ) REFERENCES "action_steps" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_step_transitions_dst_actionid_ins" BEFORE INSERT ON action_step_transitions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dst_actionid IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.dst_actionid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: dst_actionid violates foreign key action_steps(id = SELECT new.dst_actionid)')
    END;
END;
CREATE TRIGGER "fk_action_step_transitions_dst_actionid_upd" BEFORE UPDATE ON action_step_transitions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dst_actionid IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.dst_actionid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: dst_actionid violates foreign key action_steps(id)')
    END;
END;
CREATE TRIGGER "fk_action_step_transitions_dst_actionid_del" BEFORE DELETE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT dst_actionid FROM action_step_transitions WHERE dst_actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key action_step_transitions(dst_actionid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_steps', 'id', 'action_step_transitions', 'dst_actionid');
 

--ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_action_steps_id" FOREIGN KEY ( "src_actionid" ) REFERENCES "action_steps" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_action_steps_id" FOREIGN KEY ( "src_actionid" ) REFERENCES "action_steps" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_step_transitions_src_actionid_ins" BEFORE INSERT ON action_step_transitions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.src_actionid IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.src_actionid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: src_actionid violates foreign key action_steps(id = SELECT new.src_actionid)')
    END;
END;
CREATE TRIGGER "fk_action_step_transitions_src_actionid_upd" BEFORE UPDATE ON action_step_transitions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.src_actionid IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.src_actionid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: src_actionid violates foreign key action_steps(id)')
    END;
END;
CREATE TRIGGER "fk_action_step_transitions_src_actionid_del" BEFORE DELETE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT src_actionid FROM action_step_transitions WHERE src_actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key action_step_transitions(src_actionid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_steps', 'id', 'action_step_transitions', 'src_actionid');
 

-- Generate Sqlite application relations for table action_steps for lbDMFManager_Entities
-- Create table relations for action_steps
--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_action_types_id" FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_action_types_id" FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_steps_type_ins" BEFORE INSERT ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.type IS NOT NULL) AND ((SELECT id FROM action_types WHERE id = new.type) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: type violates foreign key action_types(id = SELECT new.type)')
    END;
END;
CREATE TRIGGER "fk_action_steps_type_upd" BEFORE UPDATE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.type IS NOT NULL) AND ((SELECT id FROM action_types WHERE id = new.type) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: type violates foreign key action_types(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_type_del" BEFORE DELETE ON action_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT type FROM action_steps WHERE type = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key action_steps(type = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_types', 'id', 'action_steps', 'type');
 

--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_steps_actionid_ins" BEFORE INSERT ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: actionid violates foreign key actions(id = SELECT new.actionid)')
    END;
END;
CREATE TRIGGER "fk_action_steps_actionid_upd" BEFORE UPDATE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: actionid violates foreign key actions(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_actionid_del" BEFORE DELETE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT actionid FROM action_steps WHERE actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key action_steps(actionid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('actions', 'id', 'action_steps', 'actionid');
 

-- Generate Sqlite application relations for table action_types for lbDMFManager_Entities
-- Create table relations for action_types
-- Generate Sqlite application relations for table actions for lbDMFManager_Entities
-- Create table relations for actions
--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_action_types_id" FOREIGN KEY ( "typ" ) REFERENCES "action_types" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_action_types_id" FOREIGN KEY ( "typ" ) REFERENCES "action_types" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_actions_typ_ins" BEFORE INSERT ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM action_types WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: typ violates foreign key action_types(id = SELECT new.typ)')
    END;
END;
CREATE TRIGGER "fk_actions_typ_upd" BEFORE UPDATE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM action_types WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: typ violates foreign key action_types(id)')
    END;
END;
CREATE TRIGGER "fk_actions_typ_del" BEFORE DELETE ON action_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT typ FROM actions WHERE typ = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key actions(typ = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_types', 'id', 'actions', 'typ');
 

--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_actions_anwendungenid_ins" BEFORE INSERT ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: anwendungenid violates foreign key anwendungen(id = SELECT new.anwendungenid)')
    END;
END;
CREATE TRIGGER "fk_actions_anwendungenid_upd" BEFORE UPDATE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: anwendungenid violates foreign key anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_actions_anwendungenid_del" BEFORE DELETE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungenid FROM actions WHERE anwendungenid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key actions(anwendungenid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen', 'id', 'actions', 'anwendungenid');
 

-- Generate Sqlite application relations for table anwendungen for lbDMFManager_Entities
-- Create table relations for anwendungen
-- Generate Sqlite application relations for table anwendungen_formulare for lbDMFManager_Entities
-- Create table relations for anwendungen_formulare
--ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungen_formulare_anwendungid_ins" BEFORE INSERT ON anwendungen_formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: anwendungid violates foreign key anwendungen(id = SELECT new.anwendungid)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_formulare_anwendungid_upd" BEFORE UPDATE ON anwendungen_formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: anwendungid violates foreign key anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_formulare_anwendungid_del" BEFORE DELETE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungid FROM anwendungen_formulare WHERE anwendungid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key anwendungen_formulare(anwendungid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen', 'id', 'anwendungen_formulare', 'anwendungid');
 

--ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungen_formulare_formularid_ins" BEFORE INSERT ON anwendungen_formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: formularid violates foreign key formulare(id = SELECT new.formularid)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_formulare_formularid_upd" BEFORE UPDATE ON anwendungen_formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: formularid violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_formulare_formularid_del" BEFORE DELETE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT formularid FROM anwendungen_formulare WHERE formularid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key anwendungen_formulare(formularid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulare', 'id', 'anwendungen_formulare', 'formularid');
 

-- Generate Sqlite application relations for table anwendungs_parameter for lbDMFManager_Entities
-- Create table relations for anwendungs_parameter
--ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "cst_anwendungs_parameter_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "cst_anwendungs_parameter_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungs_parameter_anwendungid_ins" BEFORE INSERT ON anwendungs_parameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: anwendungid violates foreign key anwendungen(id = SELECT new.anwendungid)')
    END;
END;
CREATE TRIGGER "fk_anwendungs_parameter_anwendungid_upd" BEFORE UPDATE ON anwendungs_parameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: anwendungid violates foreign key anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungs_parameter_anwendungid_del" BEFORE DELETE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungid FROM anwendungs_parameter WHERE anwendungid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key anwendungs_parameter(anwendungid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen', 'id', 'anwendungs_parameter', 'anwendungid');
 

-- Generate Sqlite application relations for table anwendungsberechtigungen for lbDMFManager_Entities
-- Create table relations for anwendungsberechtigungen
--ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_formulare_id" FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_formulare_id" FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungsberechtigungen_idformular_ins" BEFORE INSERT ON anwendungsberechtigungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.idformular IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.idformular) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: idformular violates foreign key formulare(id = SELECT new.idformular)')
    END;
END;
CREATE TRIGGER "fk_anwendungsberechtigungen_idformular_upd" BEFORE UPDATE ON anwendungsberechtigungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.idformular IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.idformular) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: idformular violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungsberechtigungen_idformular_del" BEFORE DELETE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT idformular FROM anwendungsberechtigungen WHERE idformular = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key anwendungsberechtigungen(idformular = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulare', 'id', 'anwendungsberechtigungen', 'idformular');
 

--ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_users_id" FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_users_id" FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungsberechtigungen_iduser_ins" BEFORE INSERT ON anwendungsberechtigungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.iduser IS NOT NULL) AND ((SELECT id FROM users WHERE id = new.iduser) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: iduser violates foreign key users(id = SELECT new.iduser)')
    END;
END;
CREATE TRIGGER "fk_anwendungsberechtigungen_iduser_upd" BEFORE UPDATE ON anwendungsberechtigungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.iduser IS NOT NULL) AND ((SELECT id FROM users WHERE id = new.iduser) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: iduser violates foreign key users(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungsberechtigungen_iduser_del" BEFORE DELETE ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT iduser FROM anwendungsberechtigungen WHERE iduser = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key anwendungsberechtigungen(iduser = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('users', 'id', 'anwendungsberechtigungen', 'iduser');
 

-- Generate Sqlite application relations for table applevel_plugin_registry for lbDMFManager_Entities
-- Create table relations for applevel_plugin_registry
-- Generate Sqlite application relations for table codegentarget for lbDMFManager_Entities
-- Create table relations for codegentarget
-- Generate Sqlite application relations for table column_types for lbDMFManager_Entities
-- Create table relations for column_types
-- Generate Sqlite application relations for table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Create table relations for foreignkey_visibledata_mapping
-- Generate Sqlite application relations for table formular_actions for lbDMFManager_Entities
-- Create table relations for formular_actions
--ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_actions_id" FOREIGN KEY ( "action" ) REFERENCES "actions" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_actions_id" FOREIGN KEY ( "action" ) REFERENCES "actions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formular_actions_action_ins" BEFORE INSERT ON formular_actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.action) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: action violates foreign key actions(id = SELECT new.action)')
    END;
END;
CREATE TRIGGER "fk_formular_actions_action_upd" BEFORE UPDATE ON formular_actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.action) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: action violates foreign key actions(id)')
    END;
END;
CREATE TRIGGER "fk_formular_actions_action_del" BEFORE DELETE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT action FROM formular_actions WHERE action = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key formular_actions(action = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('actions', 'id', 'formular_actions', 'action');
 

--ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_formulare_id" FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_formulare_id" FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formular_actions_formular_ins" BEFORE INSERT ON formular_actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formular IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formular) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: formular violates foreign key formulare(id = SELECT new.formular)')
    END;
END;
CREATE TRIGGER "fk_formular_actions_formular_upd" BEFORE UPDATE ON formular_actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formular IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formular) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: formular violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_formular_actions_formular_del" BEFORE DELETE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT formular FROM formular_actions WHERE formular = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key formular_actions(formular = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulare', 'id', 'formular_actions', 'formular');
 

-- Generate Sqlite application relations for table formular_parameters for lbDMFManager_Entities
-- Create table relations for formular_parameters
--ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formular_parameters_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formular_parameters_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formular_parameters_formularid_ins" BEFORE INSERT ON formular_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: formularid violates foreign key formulare(id = SELECT new.formularid)')
    END;
END;
CREATE TRIGGER "fk_formular_parameters_formularid_upd" BEFORE UPDATE ON formular_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: formularid violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_formular_parameters_formularid_del" BEFORE DELETE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT formularid FROM formular_parameters WHERE formularid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key formular_parameters(formularid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulare', 'id', 'formular_parameters', 'formularid');
 

-- Generate Sqlite application relations for table formulare for lbDMFManager_Entities
-- Create table relations for formulare
--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formulare_anwendungid_ins" BEFORE INSERT ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: anwendungid violates foreign key anwendungen(id = SELECT new.anwendungid)')
    END;
END;
CREATE TRIGGER "fk_formulare_anwendungid_upd" BEFORE UPDATE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: anwendungid violates foreign key anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_anwendungid_del" BEFORE DELETE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungid FROM formulare WHERE anwendungid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key formulare(anwendungid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen', 'id', 'formulare', 'anwendungid');
 

--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_formulartypen_id" FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_formulartypen_id" FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formulare_typ_ins" BEFORE INSERT ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM formulartypen WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: typ violates foreign key formulartypen(id = SELECT new.typ)')
    END;
END;
CREATE TRIGGER "fk_formulare_typ_upd" BEFORE UPDATE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM formulartypen WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: typ violates foreign key formulartypen(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_typ_del" BEFORE DELETE ON formulartypen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT typ FROM formulare WHERE typ = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key formulare(typ = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulartypen', 'id', 'formulare', 'typ');
 

-- Generate Sqlite application relations for table formularfields for lbDMFManager_Entities
-- Create table relations for formularfields
--ALTER TABLE "formularfields" ADD CONSTRAINT "cst_formularfields_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "formularfields" ADD CONSTRAINT "cst_formularfields_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formularfields_formularid_ins" BEFORE INSERT ON formularfields FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: formularid violates foreign key formulare(id = SELECT new.formularid)')
    END;
END;
CREATE TRIGGER "fk_formularfields_formularid_upd" BEFORE UPDATE ON formularfields FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: formularid violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_formularfields_formularid_del" BEFORE DELETE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT formularid FROM formularfields WHERE formularid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key formularfields(formularid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulare', 'id', 'formularfields', 'formularid');
 

--ALTER TABLE "formularfields" ADD CONSTRAINT "cst_formularfields_dbtype_id" FOREIGN KEY ( "dbtypeid" ) REFERENCES "dbtype" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "formularfields" ADD CONSTRAINT "cst_formularfields_dbtype_id" FOREIGN KEY ( "dbtypeid" ) REFERENCES "dbtype" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formularfields_dbtypeid_ins" BEFORE INSERT ON formularfields FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtypeid IS NOT NULL) AND ((SELECT id FROM dbtype WHERE id = new.dbtypeid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: dbtypeid violates foreign key dbtype(id = SELECT new.dbtypeid)')
    END;
END;
CREATE TRIGGER "fk_formularfields_dbtypeid_upd" BEFORE UPDATE ON formularfields FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtypeid IS NOT NULL) AND ((SELECT id FROM dbtype WHERE id = new.dbtypeid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: dbtypeid violates foreign key dbtype(id)')
    END;
END;
CREATE TRIGGER "fk_formularfields_dbtypeid_del" BEFORE DELETE ON dbtype FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT dbtypeid FROM formularfields WHERE dbtypeid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key formularfields(dbtypeid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('dbtype', 'id', 'formularfields', 'dbtypeid');
 

-- Generate Sqlite application relations for table formulartypen for lbDMFManager_Entities
-- Create table relations for formulartypen
-- Generate Sqlite application relations for table regressiontest for lbDMFManager_Entities
-- Create table relations for regressiontest
-- Generate Sqlite application relations for table report_element_types for lbDMFManager_Entities
-- Create table relations for report_element_types
-- Generate Sqlite application relations for table report_elements for lbDMFManager_Entities
-- Create table relations for report_elements
--ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_report_element_types_id" FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_report_element_types_id" FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_report_elements_typ_ins" BEFORE INSERT ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM report_element_types WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: typ violates foreign key report_element_types(id = SELECT new.typ)')
    END;
END;
CREATE TRIGGER "fk_report_elements_typ_upd" BEFORE UPDATE ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM report_element_types WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: typ violates foreign key report_element_types(id)')
    END;
END;
CREATE TRIGGER "fk_report_elements_typ_del" BEFORE DELETE ON report_element_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT typ FROM report_elements WHERE typ = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key report_elements(typ = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('report_element_types', 'id', 'report_elements', 'typ');
 

--ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_report_elements_reportid_ins" BEFORE INSERT ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM reports WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: reportid violates foreign key reports(id = SELECT new.reportid)')
    END;
END;
CREATE TRIGGER "fk_report_elements_reportid_upd" BEFORE UPDATE ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM reports WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: reportid violates foreign key reports(id)')
    END;
END;
CREATE TRIGGER "fk_report_elements_reportid_del" BEFORE DELETE ON reports FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT reportid FROM report_elements WHERE reportid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key report_elements(reportid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('reports', 'id', 'report_elements', 'reportid');
 

-- Generate Sqlite application relations for table report_parameters for lbDMFManager_Entities
-- Create table relations for report_parameters
--ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_report_parameters_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_report_parameters_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_report_parameters_reportid_ins" BEFORE INSERT ON report_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM reports WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: reportid violates foreign key reports(id = SELECT new.reportid)')
    END;
END;
CREATE TRIGGER "fk_report_parameters_reportid_upd" BEFORE UPDATE ON report_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM reports WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: reportid violates foreign key reports(id)')
    END;
END;
CREATE TRIGGER "fk_report_parameters_reportid_del" BEFORE DELETE ON reports FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT reportid FROM report_parameters WHERE reportid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key report_parameters(reportid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('reports', 'id', 'report_parameters', 'reportid');
 

-- Generate Sqlite application relations for table report_texts for lbDMFManager_Entities
-- Create table relations for report_texts
--ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_texts_report_elements_id" FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_texts_report_elements_id" FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_report_texts_elementid_ins" BEFORE INSERT ON report_texts FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.elementid IS NOT NULL) AND ((SELECT id FROM report_elements WHERE id = new.elementid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: elementid violates foreign key report_elements(id = SELECT new.elementid)')
    END;
END;
CREATE TRIGGER "fk_report_texts_elementid_upd" BEFORE UPDATE ON report_texts FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.elementid IS NOT NULL) AND ((SELECT id FROM report_elements WHERE id = new.elementid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: elementid violates foreign key report_elements(id)')
    END;
END;
CREATE TRIGGER "fk_report_texts_elementid_del" BEFORE DELETE ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT elementid FROM report_texts WHERE elementid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key report_texts(elementid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('report_elements', 'id', 'report_texts', 'elementid');
 

-- Generate Sqlite application relations for table reports for lbDMFManager_Entities
-- Create table relations for reports
-- Generate Sqlite application relations for table translations for lbDMFManager_Entities
-- Create table relations for translations
-- Generate Sqlite application relations for table user_anwendungen for lbDMFManager_Entities
-- Create table relations for user_anwendungen
--ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_user_anwendungen_anwendungenid_ins" BEFORE INSERT ON user_anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: anwendungenid violates foreign key anwendungen(id = SELECT new.anwendungenid)')
    END;
END;
CREATE TRIGGER "fk_user_anwendungen_anwendungenid_upd" BEFORE UPDATE ON user_anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: anwendungenid violates foreign key anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_user_anwendungen_anwendungenid_del" BEFORE DELETE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungenid FROM user_anwendungen WHERE anwendungenid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key user_anwendungen(anwendungenid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen', 'id', 'user_anwendungen', 'anwendungenid');
 

--ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_users_id" FOREIGN KEY ( "userid" ) REFERENCES "users" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_users_id" FOREIGN KEY ( "userid" ) REFERENCES "users" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_user_anwendungen_userid_ins" BEFORE INSERT ON user_anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.userid IS NOT NULL) AND ((SELECT id FROM users WHERE id = new.userid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: userid violates foreign key users(id = SELECT new.userid)')
    END;
END;
CREATE TRIGGER "fk_user_anwendungen_userid_upd" BEFORE UPDATE ON user_anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.userid IS NOT NULL) AND ((SELECT id FROM users WHERE id = new.userid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: userid violates foreign key users(id)')
    END;
END;
CREATE TRIGGER "fk_user_anwendungen_userid_del" BEFORE DELETE ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT userid FROM user_anwendungen WHERE userid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key user_anwendungen(userid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('users', 'id', 'user_anwendungen', 'userid');
 

-- Generate Sqlite application relations for table users for lbDMFManager_Entities
-- Create table relations for users
--ALTER TABLE "users" ADD CONSTRAINT "cst_users_anwendungen_id" FOREIGN KEY ( "lastapp" ) REFERENCES "anwendungen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "users" ADD CONSTRAINT "cst_users_anwendungen_id" FOREIGN KEY ( "lastapp" ) REFERENCES "anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_users_lastapp_ins" BEFORE INSERT ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.lastapp IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.lastapp) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: lastapp violates foreign key anwendungen(id = SELECT new.lastapp)')
    END;
END;
CREATE TRIGGER "fk_users_lastapp_upd" BEFORE UPDATE ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.lastapp IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.lastapp) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: lastapp violates foreign key anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_users_lastapp_del" BEFORE DELETE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT lastapp FROM users WHERE lastapp = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key users(lastapp = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen', 'id', 'users', 'lastapp');
 

-- Generate Sqlite application relations for table dbtype for lbDMFManager_Entities
-- Create table relations for dbtype
-- Generate Sqlite application relations for table dbtable for lbDMFManager_Entities
-- Create table relations for dbtable
--ALTER TABLE "dbtable" ADD CONSTRAINT "cst_dbtable_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "dbtable" ADD CONSTRAINT "cst_dbtable_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_dbtable_anwendungenid_ins" BEFORE INSERT ON dbtable FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: anwendungenid violates foreign key anwendungen(id = SELECT new.anwendungenid)')
    END;
END;
CREATE TRIGGER "fk_dbtable_anwendungenid_upd" BEFORE UPDATE ON dbtable FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: anwendungenid violates foreign key anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_dbtable_anwendungenid_del" BEFORE DELETE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungenid FROM dbtable WHERE anwendungenid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key dbtable(anwendungenid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen', 'id', 'dbtable', 'anwendungenid');
 

-- Generate Sqlite application relations for table dbcolumn for lbDMFManager_Entities
-- Create table relations for dbcolumn
--ALTER TABLE "dbcolumn" ADD CONSTRAINT "cst_dbcolumn_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "dbcolumn" ADD CONSTRAINT "cst_dbcolumn_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_dbcolumn_dbtableid_ins" BEFORE INSERT ON dbcolumn FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: dbtableid violates foreign key dbtable(id = SELECT new.dbtableid)')
    END;
END;
CREATE TRIGGER "fk_dbcolumn_dbtableid_upd" BEFORE UPDATE ON dbcolumn FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: dbtableid violates foreign key dbtable(id)')
    END;
END;
CREATE TRIGGER "fk_dbcolumn_dbtableid_del" BEFORE DELETE ON dbtable FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT dbtableid FROM dbcolumn WHERE dbtableid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key dbcolumn(dbtableid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('dbtable', 'id', 'dbcolumn', 'dbtableid');
 

-- Generate Sqlite application relations for table dbforeignkey for lbDMFManager_Entities
-- Create table relations for dbforeignkey
--ALTER TABLE "dbforeignkey" ADD CONSTRAINT "cst_dbforeignkey_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "dbforeignkey" ADD CONSTRAINT "cst_dbforeignkey_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_dbforeignkey_dbtableid_ins" BEFORE INSERT ON dbforeignkey FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: dbtableid violates foreign key dbtable(id = SELECT new.dbtableid)')
    END;
END;
CREATE TRIGGER "fk_dbforeignkey_dbtableid_upd" BEFORE UPDATE ON dbforeignkey FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: dbtableid violates foreign key dbtable(id)')
    END;
END;
CREATE TRIGGER "fk_dbforeignkey_dbtableid_del" BEFORE DELETE ON dbtable FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT dbtableid FROM dbforeignkey WHERE dbtableid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key dbforeignkey(dbtableid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('dbtable', 'id', 'dbforeignkey', 'dbtableid');
 

-- Generate Sqlite application relations for table dbprimarykey for lbDMFManager_Entities
-- Create table relations for dbprimarykey
--ALTER TABLE "dbprimarykey" ADD CONSTRAINT "cst_dbprimarykey_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "dbprimarykey" ADD CONSTRAINT "cst_dbprimarykey_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_dbprimarykey_dbtableid_ins" BEFORE INSERT ON dbprimarykey FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: dbtableid violates foreign key dbtable(id = SELECT new.dbtableid)')
    END;
END;
CREATE TRIGGER "fk_dbprimarykey_dbtableid_upd" BEFORE UPDATE ON dbprimarykey FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: dbtableid violates foreign key dbtable(id)')
    END;
END;
CREATE TRIGGER "fk_dbprimarykey_dbtableid_del" BEFORE DELETE ON dbtable FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT dbtableid FROM dbprimarykey WHERE dbtableid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key dbprimarykey(dbtableid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('dbtable', 'id', 'dbprimarykey', 'dbtableid');
 

-- Unknown stereotype 'filterdefinition' for class UserFilter.

-- Generate application table UserFilter for lbDMFManager_Entities
-- Create table relations for UserFilter with auto id
	

-- Generate Sqlite application relations for table dbtableparameter for lbDMFManager_Entities
-- Create table relations for dbtableparameter
--ALTER TABLE "dbtableparameter" ADD CONSTRAINT "cst_dbtableparameter_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );
-- Using just in time rewriting doesn't work when execute_droprules is set to yes. The fk tool has no parser for DROP rules and also no DELETE statement is supported.
--ALTER TABLE "dbtableparameter" ADD CONSTRAINT "cst_dbtableparameter_dbtable_id" FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_dbtableparameter_dbtableid_ins" BEFORE INSERT ON dbtableparameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'INSERT: dbtableid violates foreign key dbtable(id = SELECT new.dbtableid)')
    END;
END;
CREATE TRIGGER "fk_dbtableparameter_dbtableid_upd" BEFORE UPDATE ON dbtableparameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dbtableid IS NOT NULL) AND ((SELECT id FROM dbtable WHERE id = new.dbtableid) IS NULL))
                 THEN RAISE(ABORT, 'UPDATE: dbtableid violates foreign key dbtable(id)')
    END;
END;
CREATE TRIGGER "fk_dbtableparameter_dbtableid_del" BEFORE DELETE ON dbtable FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT dbtableid FROM dbtableparameter WHERE dbtableid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'DELETE: id violates foreign key dbtableparameter(dbtableid = old.id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('dbtable', 'id', 'dbtableparameter', 'dbtableid');
 

-- Script ready.
COMMIT;
	