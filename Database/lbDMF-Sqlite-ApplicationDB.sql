
--
-- SQL script created for Sqlite
--
	

-- Class Benutzer of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Anwendungen of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_parameters
CREATE TABLE "action_parameters" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"value" BPCHAR,
	"interface" BPCHAR,
	"description" BPCHAR
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
	"description" BPCHAR
);

-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_transitions for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_step_transitions
CREATE TABLE "action_step_transitions" (
	"id" INTEGER PRIMARY KEY,
	"expression" BPCHAR,
	"description" BPCHAR
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
	"action_step_id" INTEGER,
	"dst_actionid" INTEGER,
	"src_actionid" INTEGER
);

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE action_types
CREATE TABLE "action_types" (
	"id" INTEGER PRIMARY KEY,
	"bezeichnung" BPCHAR,
	"action_handler" BPCHAR,
	"module" BPCHAR,
	"type" INTEGER,
	"typ" INTEGER
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
	"actionid" INTEGER,
	"actionid" INTEGER,
	"action" INTEGER
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
	"anwendungid" INTEGER,
	"anwendungid" INTEGER,
	"anwendungid" INTEGER,
	"anwendungenid" INTEGER,
	"lastapp" INTEGER
);

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE anwendungen_formulare
CREATE TABLE "anwendungen_formulare" (
	"id" INTEGER PRIMARY KEY
);

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE anwendungs_parameter
CREATE TABLE "anwendungs_parameter" (
	"id" INTEGER PRIMARY KEY,
	"parametername" BPCHAR,
	"parametervalue" BPCHAR
);

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE anwendungsberechtigungen
CREATE TABLE "anwendungsberechtigungen" (
	"id" INTEGER PRIMARY KEY
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
	"event" BPCHAR
);

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE formular_parameters
CREATE TABLE "formular_parameters" (
	"id" INTEGER PRIMARY KEY,
	"parametername" BPCHAR,
	"parametervalue" BPCHAR
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
	"formularid" INTEGER,
	"idformular" INTEGER,
	"formular" INTEGER,
	"formularid" INTEGER
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
	"beschreibung" BPCHAR,
	"typ" INTEGER
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
	"description" BPCHAR,
	"typ" INTEGER
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
	"elementid" INTEGER
);

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE report_parameters
CREATE TABLE "report_parameters" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"value" INTEGER
);

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE report_texts
CREATE TABLE "report_texts" (
	"id" INTEGER PRIMARY KEY,
	"line" INTEGER,
	"text" BPCHAR
);

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE Sqlite TABLE reports
CREATE TABLE "reports" (
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"description" BPCHAR,
	"reportid" INTEGER,
	"reportid" INTEGER
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
	"id" INTEGER PRIMARY KEY
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
	"iduser" INTEGER,
	"userid" INTEGER
);

-- Class Benutzer of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Anwendungen of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
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

-- Generate Sqlite application relations for table action_parameters for lbDMFManager_Entities
-- Generate Sqlite application relations for table action_step_parameter for lbDMFManager_Entities
-- Generate Sqlite application relations for table action_step_transitions for lbDMFManager_Entities
-- Generate Sqlite application relations for table action_steps for lbDMFManager_Entities	

--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_action_step_id_action_step_parameter_id" FOREIGN KEY ( "action_step_id" ) REFERENCES "action_step_parameter" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_steps_action_step_id_ins" BEFORE INSERT ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action_step_id IS NOT NULL) AND ((SELECT id FROM action_step_parameter WHERE id = new.action_step_id) IS NULL))
                 THEN RAISE(ABORT, 'action_step_id violates foreign key action_step_parameter(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_action_step_id_upd" BEFORE UPDATE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action_step_id IS NOT NULL) AND ((SELECT id FROM action_step_parameter WHERE id = new.action_step_id) IS NULL))
                 THEN RAISE(ABORT, 'action_step_id violates foreign key action_step_parameter(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_action_step_id_del" BEFORE DELETE ON action_step_parameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT action_step_id FROM action_steps WHERE action_step_id = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key action_steps(action_step_id)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_step_parameter', 'id', 'action_steps', 'action_step_id');

	

--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_dst_actionid_action_step_transitions_id" FOREIGN KEY ( "dst_actionid" ) REFERENCES "action_step_transitions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_steps_dst_actionid_ins" BEFORE INSERT ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dst_actionid IS NOT NULL) AND ((SELECT id FROM action_step_transitions WHERE id = new.dst_actionid) IS NULL))
                 THEN RAISE(ABORT, 'dst_actionid violates foreign key action_step_transitions(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_dst_actionid_upd" BEFORE UPDATE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.dst_actionid IS NOT NULL) AND ((SELECT id FROM action_step_transitions WHERE id = new.dst_actionid) IS NULL))
                 THEN RAISE(ABORT, 'dst_actionid violates foreign key action_step_transitions(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_dst_actionid_del" BEFORE DELETE ON action_step_transitions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT dst_actionid FROM action_steps WHERE dst_actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key action_steps(dst_actionid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_step_transitions', 'id', 'action_steps', 'dst_actionid');

	

--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_src_actionid_action_step_transitions_id" FOREIGN KEY ( "src_actionid" ) REFERENCES "action_step_transitions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_steps_src_actionid_ins" BEFORE INSERT ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.src_actionid IS NOT NULL) AND ((SELECT id FROM action_step_transitions WHERE id = new.src_actionid) IS NULL))
                 THEN RAISE(ABORT, 'src_actionid violates foreign key action_step_transitions(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_src_actionid_upd" BEFORE UPDATE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.src_actionid IS NOT NULL) AND ((SELECT id FROM action_step_transitions WHERE id = new.src_actionid) IS NULL))
                 THEN RAISE(ABORT, 'src_actionid violates foreign key action_step_transitions(id)')
    END;
END;
CREATE TRIGGER "fk_action_steps_src_actionid_del" BEFORE DELETE ON action_step_transitions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT src_actionid FROM action_steps WHERE src_actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key action_steps(src_actionid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_step_transitions', 'id', 'action_steps', 'src_actionid');


-- Generate Sqlite application relations for table action_types for lbDMFManager_Entities	

--ALTER TABLE "action_types" ADD CONSTRAINT "cst_action_types_type_action_steps_id" FOREIGN KEY ( "type" ) REFERENCES "action_steps" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_types_type_ins" BEFORE INSERT ON action_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.type IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.type) IS NULL))
                 THEN RAISE(ABORT, 'type violates foreign key action_steps(id)')
    END;
END;
CREATE TRIGGER "fk_action_types_type_upd" BEFORE UPDATE ON action_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.type IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.type) IS NULL))
                 THEN RAISE(ABORT, 'type violates foreign key action_steps(id)')
    END;
END;
CREATE TRIGGER "fk_action_types_type_del" BEFORE DELETE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT type FROM action_types WHERE type = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key action_types(type)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_steps', 'id', 'action_types', 'type');

	

--ALTER TABLE "action_types" ADD CONSTRAINT "cst_action_types_typ_actions_id" FOREIGN KEY ( "typ" ) REFERENCES "actions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_action_types_typ_ins" BEFORE INSERT ON action_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'typ violates foreign key actions(id)')
    END;
END;
CREATE TRIGGER "fk_action_types_typ_upd" BEFORE UPDATE ON action_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM actions WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'typ violates foreign key actions(id)')
    END;
END;
CREATE TRIGGER "fk_action_types_typ_del" BEFORE DELETE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT typ FROM action_types WHERE typ = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key action_types(typ)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('actions', 'id', 'action_types', 'typ');


-- Generate Sqlite application relations for table actions for lbDMFManager_Entities	

--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_actionid_action_parameters_id" FOREIGN KEY ( "actionid" ) REFERENCES "action_parameters" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_actions_actionid_ins" BEFORE INSERT ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM action_parameters WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'actionid violates foreign key action_parameters(id)')
    END;
END;
CREATE TRIGGER "fk_actions_actionid_upd" BEFORE UPDATE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM action_parameters WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'actionid violates foreign key action_parameters(id)')
    END;
END;
CREATE TRIGGER "fk_actions_actionid_del" BEFORE DELETE ON action_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT actionid FROM actions WHERE actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key actions(actionid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_parameters', 'id', 'actions', 'actionid');

	

--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_actionid_action_steps_id" FOREIGN KEY ( "actionid" ) REFERENCES "action_steps" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_actions_actionid_ins" BEFORE INSERT ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'actionid violates foreign key action_steps(id)')
    END;
END;
CREATE TRIGGER "fk_actions_actionid_upd" BEFORE UPDATE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.actionid IS NOT NULL) AND ((SELECT id FROM action_steps WHERE id = new.actionid) IS NULL))
                 THEN RAISE(ABORT, 'actionid violates foreign key action_steps(id)')
    END;
END;
CREATE TRIGGER "fk_actions_actionid_del" BEFORE DELETE ON action_steps FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT actionid FROM actions WHERE actionid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key actions(actionid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('action_steps', 'id', 'actions', 'actionid');

	

--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_action_formular_actions_id" FOREIGN KEY ( "action" ) REFERENCES "formular_actions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_actions_action_ins" BEFORE INSERT ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action IS NOT NULL) AND ((SELECT id FROM formular_actions WHERE id = new.action) IS NULL))
                 THEN RAISE(ABORT, 'action violates foreign key formular_actions(id)')
    END;
END;
CREATE TRIGGER "fk_actions_action_upd" BEFORE UPDATE ON actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.action IS NOT NULL) AND ((SELECT id FROM formular_actions WHERE id = new.action) IS NULL))
                 THEN RAISE(ABORT, 'action violates foreign key formular_actions(id)')
    END;
END;
CREATE TRIGGER "fk_actions_action_del" BEFORE DELETE ON formular_actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT action FROM actions WHERE action = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key actions(action)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formular_actions', 'id', 'actions', 'action');


-- Generate Sqlite application relations for table anwendungen for lbDMFManager_Entities	

--ALTER TABLE "anwendungen" ADD CONSTRAINT "cst_anwendungen_anwendungid_anwendungen_formulare_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen_formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungen_anwendungid_ins" BEFORE INSERT ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen_formulare WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungid violates foreign key anwendungen_formulare(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungid_upd" BEFORE UPDATE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungen_formulare WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungid violates foreign key anwendungen_formulare(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungid_del" BEFORE DELETE ON anwendungen_formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungid FROM anwendungen WHERE anwendungid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key anwendungen(anwendungid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen_formulare', 'id', 'anwendungen', 'anwendungid');

	

--ALTER TABLE "anwendungen" ADD CONSTRAINT "cst_anwendungen_anwendungid_anwendungs_parameter_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungs_parameter" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungen_anwendungid_ins" BEFORE INSERT ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungs_parameter WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungid violates foreign key anwendungs_parameter(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungid_upd" BEFORE UPDATE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM anwendungs_parameter WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungid violates foreign key anwendungs_parameter(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungid_del" BEFORE DELETE ON anwendungs_parameter FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungid FROM anwendungen WHERE anwendungid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key anwendungen(anwendungid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungs_parameter', 'id', 'anwendungen', 'anwendungid');

	

--ALTER TABLE "anwendungen" ADD CONSTRAINT "cst_anwendungen_anwendungid_formulare_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungen_anwendungid_ins" BEFORE INSERT ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungid violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungid_upd" BEFORE UPDATE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungid IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.anwendungid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungid violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungid_del" BEFORE DELETE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungid FROM anwendungen WHERE anwendungid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key anwendungen(anwendungid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulare', 'id', 'anwendungen', 'anwendungid');

	

--ALTER TABLE "anwendungen" ADD CONSTRAINT "cst_anwendungen_anwendungenid_user_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "user_anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungen_anwendungenid_ins" BEFORE INSERT ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM user_anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungenid violates foreign key user_anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungenid_upd" BEFORE UPDATE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.anwendungenid IS NOT NULL) AND ((SELECT id FROM user_anwendungen WHERE id = new.anwendungenid) IS NULL))
                 THEN RAISE(ABORT, 'anwendungenid violates foreign key user_anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_anwendungenid_del" BEFORE DELETE ON user_anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT anwendungenid FROM anwendungen WHERE anwendungenid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key anwendungen(anwendungenid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('user_anwendungen', 'id', 'anwendungen', 'anwendungenid');

	

--ALTER TABLE "anwendungen" ADD CONSTRAINT "cst_anwendungen_lastapp_users_id" FOREIGN KEY ( "lastapp" ) REFERENCES "users" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_anwendungen_lastapp_ins" BEFORE INSERT ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.lastapp IS NOT NULL) AND ((SELECT id FROM users WHERE id = new.lastapp) IS NULL))
                 THEN RAISE(ABORT, 'lastapp violates foreign key users(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_lastapp_upd" BEFORE UPDATE ON anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.lastapp IS NOT NULL) AND ((SELECT id FROM users WHERE id = new.lastapp) IS NULL))
                 THEN RAISE(ABORT, 'lastapp violates foreign key users(id)')
    END;
END;
CREATE TRIGGER "fk_anwendungen_lastapp_del" BEFORE DELETE ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT lastapp FROM anwendungen WHERE lastapp = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key anwendungen(lastapp)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('users', 'id', 'anwendungen', 'lastapp');


-- Generate Sqlite application relations for table anwendungen_formulare for lbDMFManager_Entities
-- Generate Sqlite application relations for table anwendungs_parameter for lbDMFManager_Entities
-- Generate Sqlite application relations for table anwendungsberechtigungen for lbDMFManager_Entities
-- Generate Sqlite application relations for table applevel_plugin_registry for lbDMFManager_Entities
-- Generate Sqlite application relations for table codegentarget for lbDMFManager_Entities
-- Generate Sqlite application relations for table column_types for lbDMFManager_Entities
-- Generate Sqlite application relations for table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Generate Sqlite application relations for table formular_actions for lbDMFManager_Entities
-- Generate Sqlite application relations for table formular_parameters for lbDMFManager_Entities
-- Generate Sqlite application relations for table formulare for lbDMFManager_Entities	

--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_formularid_anwendungen_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "anwendungen_formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formulare_formularid_ins" BEFORE INSERT ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM anwendungen_formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'formularid violates foreign key anwendungen_formulare(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_formularid_upd" BEFORE UPDATE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM anwendungen_formulare WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'formularid violates foreign key anwendungen_formulare(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_formularid_del" BEFORE DELETE ON anwendungen_formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT formularid FROM formulare WHERE formularid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key formulare(formularid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungen_formulare', 'id', 'formulare', 'formularid');

	

--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_idformular_anwendungsberechtigungen_id" FOREIGN KEY ( "idformular" ) REFERENCES "anwendungsberechtigungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formulare_idformular_ins" BEFORE INSERT ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.idformular IS NOT NULL) AND ((SELECT id FROM anwendungsberechtigungen WHERE id = new.idformular) IS NULL))
                 THEN RAISE(ABORT, 'idformular violates foreign key anwendungsberechtigungen(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_idformular_upd" BEFORE UPDATE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.idformular IS NOT NULL) AND ((SELECT id FROM anwendungsberechtigungen WHERE id = new.idformular) IS NULL))
                 THEN RAISE(ABORT, 'idformular violates foreign key anwendungsberechtigungen(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_idformular_del" BEFORE DELETE ON anwendungsberechtigungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT idformular FROM formulare WHERE idformular = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key formulare(idformular)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungsberechtigungen', 'id', 'formulare', 'idformular');

	

--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_formular_formular_actions_id" FOREIGN KEY ( "formular" ) REFERENCES "formular_actions" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formulare_formular_ins" BEFORE INSERT ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formular IS NOT NULL) AND ((SELECT id FROM formular_actions WHERE id = new.formular) IS NULL))
                 THEN RAISE(ABORT, 'formular violates foreign key formular_actions(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_formular_upd" BEFORE UPDATE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formular IS NOT NULL) AND ((SELECT id FROM formular_actions WHERE id = new.formular) IS NULL))
                 THEN RAISE(ABORT, 'formular violates foreign key formular_actions(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_formular_del" BEFORE DELETE ON formular_actions FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT formular FROM formulare WHERE formular = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key formulare(formular)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formular_actions', 'id', 'formulare', 'formular');

	

--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_formularid_formular_parameters_id" FOREIGN KEY ( "formularid" ) REFERENCES "formular_parameters" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formulare_formularid_ins" BEFORE INSERT ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formular_parameters WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'formularid violates foreign key formular_parameters(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_formularid_upd" BEFORE UPDATE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.formularid IS NOT NULL) AND ((SELECT id FROM formular_parameters WHERE id = new.formularid) IS NULL))
                 THEN RAISE(ABORT, 'formularid violates foreign key formular_parameters(id)')
    END;
END;
CREATE TRIGGER "fk_formulare_formularid_del" BEFORE DELETE ON formular_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT formularid FROM formulare WHERE formularid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key formulare(formularid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formular_parameters', 'id', 'formulare', 'formularid');


-- Generate Sqlite application relations for table formulartypen for lbDMFManager_Entities	

--ALTER TABLE "formulartypen" ADD CONSTRAINT "cst_formulartypen_typ_formulare_id" FOREIGN KEY ( "typ" ) REFERENCES "formulare" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_formulartypen_typ_ins" BEFORE INSERT ON formulartypen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'typ violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_formulartypen_typ_upd" BEFORE UPDATE ON formulartypen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM formulare WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'typ violates foreign key formulare(id)')
    END;
END;
CREATE TRIGGER "fk_formulartypen_typ_del" BEFORE DELETE ON formulare FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT typ FROM formulartypen WHERE typ = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key formulartypen(typ)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('formulare', 'id', 'formulartypen', 'typ');


-- Generate Sqlite application relations for table regressiontest for lbDMFManager_Entities
-- Generate Sqlite application relations for table report_element_types for lbDMFManager_Entities	

--ALTER TABLE "report_element_types" ADD CONSTRAINT "cst_report_element_types_typ_report_elements_id" FOREIGN KEY ( "typ" ) REFERENCES "report_elements" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_report_element_types_typ_ins" BEFORE INSERT ON report_element_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM report_elements WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'typ violates foreign key report_elements(id)')
    END;
END;
CREATE TRIGGER "fk_report_element_types_typ_upd" BEFORE UPDATE ON report_element_types FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.typ IS NOT NULL) AND ((SELECT id FROM report_elements WHERE id = new.typ) IS NULL))
                 THEN RAISE(ABORT, 'typ violates foreign key report_elements(id)')
    END;
END;
CREATE TRIGGER "fk_report_element_types_typ_del" BEFORE DELETE ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT typ FROM report_element_types WHERE typ = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key report_element_types(typ)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('report_elements', 'id', 'report_element_types', 'typ');


-- Generate Sqlite application relations for table report_elements for lbDMFManager_Entities	

--ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_elementid_report_texts_id" FOREIGN KEY ( "elementid" ) REFERENCES "report_texts" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_report_elements_elementid_ins" BEFORE INSERT ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.elementid IS NOT NULL) AND ((SELECT id FROM report_texts WHERE id = new.elementid) IS NULL))
                 THEN RAISE(ABORT, 'elementid violates foreign key report_texts(id)')
    END;
END;
CREATE TRIGGER "fk_report_elements_elementid_upd" BEFORE UPDATE ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.elementid IS NOT NULL) AND ((SELECT id FROM report_texts WHERE id = new.elementid) IS NULL))
                 THEN RAISE(ABORT, 'elementid violates foreign key report_texts(id)')
    END;
END;
CREATE TRIGGER "fk_report_elements_elementid_del" BEFORE DELETE ON report_texts FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT elementid FROM report_elements WHERE elementid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key report_elements(elementid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('report_texts', 'id', 'report_elements', 'elementid');


-- Generate Sqlite application relations for table report_parameters for lbDMFManager_Entities
-- Generate Sqlite application relations for table report_texts for lbDMFManager_Entities
-- Generate Sqlite application relations for table reports for lbDMFManager_Entities	

--ALTER TABLE "reports" ADD CONSTRAINT "cst_reports_reportid_report_elements_id" FOREIGN KEY ( "reportid" ) REFERENCES "report_elements" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_reports_reportid_ins" BEFORE INSERT ON reports FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM report_elements WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'reportid violates foreign key report_elements(id)')
    END;
END;
CREATE TRIGGER "fk_reports_reportid_upd" BEFORE UPDATE ON reports FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM report_elements WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'reportid violates foreign key report_elements(id)')
    END;
END;
CREATE TRIGGER "fk_reports_reportid_del" BEFORE DELETE ON report_elements FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT reportid FROM reports WHERE reportid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key reports(reportid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('report_elements', 'id', 'reports', 'reportid');

	

--ALTER TABLE "reports" ADD CONSTRAINT "cst_reports_reportid_report_parameters_id" FOREIGN KEY ( "reportid" ) REFERENCES "report_parameters" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_reports_reportid_ins" BEFORE INSERT ON reports FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM report_parameters WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'reportid violates foreign key report_parameters(id)')
    END;
END;
CREATE TRIGGER "fk_reports_reportid_upd" BEFORE UPDATE ON reports FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.reportid IS NOT NULL) AND ((SELECT id FROM report_parameters WHERE id = new.reportid) IS NULL))
                 THEN RAISE(ABORT, 'reportid violates foreign key report_parameters(id)')
    END;
END;
CREATE TRIGGER "fk_reports_reportid_del" BEFORE DELETE ON report_parameters FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT reportid FROM reports WHERE reportid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key reports(reportid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('report_parameters', 'id', 'reports', 'reportid');


-- Generate Sqlite application relations for table translations for lbDMFManager_Entities
-- Generate Sqlite application relations for table user_anwendungen for lbDMFManager_Entities
-- Generate Sqlite application relations for table users for lbDMFManager_Entities	

--ALTER TABLE "users" ADD CONSTRAINT "cst_users_iduser_anwendungsberechtigungen_id" FOREIGN KEY ( "iduser" ) REFERENCES "anwendungsberechtigungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_users_iduser_ins" BEFORE INSERT ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.iduser IS NOT NULL) AND ((SELECT id FROM anwendungsberechtigungen WHERE id = new.iduser) IS NULL))
                 THEN RAISE(ABORT, 'iduser violates foreign key anwendungsberechtigungen(id)')
    END;
END;
CREATE TRIGGER "fk_users_iduser_upd" BEFORE UPDATE ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.iduser IS NOT NULL) AND ((SELECT id FROM anwendungsberechtigungen WHERE id = new.iduser) IS NULL))
                 THEN RAISE(ABORT, 'iduser violates foreign key anwendungsberechtigungen(id)')
    END;
END;
CREATE TRIGGER "fk_users_iduser_del" BEFORE DELETE ON anwendungsberechtigungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT iduser FROM users WHERE iduser = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key users(iduser)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('anwendungsberechtigungen', 'id', 'users', 'iduser');

	

--ALTER TABLE "users" ADD CONSTRAINT "cst_users_userid_user_anwendungen_id" FOREIGN KEY ( "userid" ) REFERENCES "user_anwendungen" ( "id" );

-- Build trigger manually. (Todo: add support for nullable and not nullable)

CREATE TRIGGER "fk_users_userid_ins" BEFORE INSERT ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.userid IS NOT NULL) AND ((SELECT id FROM user_anwendungen WHERE id = new.userid) IS NULL))
                 THEN RAISE(ABORT, 'userid violates foreign key user_anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_users_userid_upd" BEFORE UPDATE ON users FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((new.userid IS NOT NULL) AND ((SELECT id FROM user_anwendungen WHERE id = new.userid) IS NULL))
                 THEN RAISE(ABORT, 'userid violates foreign key user_anwendungen(id)')
    END;
END;
CREATE TRIGGER "fk_users_userid_del" BEFORE DELETE ON user_anwendungen FOR EACH ROW
BEGIN
    SELECT CASE WHEN ((SELECT userid FROM users WHERE userid = old.id) IS NOT NULL)
                 THEN RAISE(ABORT, 'id violates foreign key users(userid)')
    END;
END;
INSERT INTO "lbDMF_ForeignKeys" ("PKTable", "PKColumn", "FKTable", "FKColumn") VALUES ('user_anwendungen', 'id', 'users', 'userid');

