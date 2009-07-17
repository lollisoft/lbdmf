--
-- SQL script created for PostgreSQL
--
	

SET SESSION AUTHORIZATION 'postgres';

CREATE OR REPLACE FUNCTION plpgsql_call_handler()
  RETURNS language_handler AS
'$libdir/plpgsql', 'plpgsql_call_handler'
  LANGUAGE 'c' VOLATILE;


--DROP LANGUAGE plpgsql;

-- Activate this on a fresh database
--CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;

-- dropTable("varchar")
--
-- This function drops a table, if it exists.

CREATE OR REPLACE FUNCTION "dropTable"("varchar")
  RETURNS void AS
'
declare
tres text;
begin
  select tablename into tres from pg_tables where tablename = $1;
  if not tres is null then
    execute ''DROP TABLE "'' || $1 || ''" CASCADE'';
  end if;
  return;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

-- dropConstraint("varchar", "varchar")
--
-- This function drops a constraint for a table, if the table exists.

CREATE OR REPLACE FUNCTION "dropConstraint"("varchar", "varchar")
  RETURNS void AS
'
declare
tres text;
begin
  select tablename into tres from pg_tables where tablename = $1;
  if not tres is null then
    execute ''ALTER TABLE "'' || $1 || ''" DROP CONSTRAINT "'' || $2 || ''"'';
  end if;
  return;
end;
'
  LANGUAGE 'plpgsql' VOLATILE;

-- Class Benutzer of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Anwendungen of type FORM found.
				
-- Class AnwendungenFormulare of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
-- Class Templates of type FORM found.
				
-- Class Templates of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table Templates for lbDMFManager_Entities
-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_parameters for lbDMFManager_Entities
select "dropConstraint"('action_parameters', 'cst_action_parameters_actionid_actions_id');

-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_step_parameter for lbDMFManager_Entities
select "dropConstraint"('action_step_parameter', 'cst_action_step_parameter_action_step_id_action_steps_id');

-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_step_transitions for lbDMFManager_Entities
select "dropConstraint"('action_step_transitions', 'cst_action_step_transitions_src_actionid_action_steps_id');

select "dropConstraint"('action_step_transitions', 'cst_action_step_transitions_dst_actionid_action_steps_id');

-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_steps for lbDMFManager_Entities
select "dropConstraint"('action_steps', 'cst_action_steps_actionid_actions_id');

select "dropConstraint"('action_steps', 'cst_action_steps_type_action_types_id');

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_types for lbDMFManager_Entities
-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table actions for lbDMFManager_Entities
select "dropConstraint"('actions', 'cst_actions_typ_action_types_id');

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungen for lbDMFManager_Entities
-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungen_formulare for lbDMFManager_Entities
select "dropConstraint"('anwendungen_formulare', 'cst_anwendungen_formulare_anwendungid_anwendungen_id');

select "dropConstraint"('anwendungen_formulare', 'cst_anwendungen_formulare_formularid_formulare_id');

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungs_parameter for lbDMFManager_Entities
select "dropConstraint"('anwendungs_parameter', 'cst_anwendungs_parameter_anwendungid_anwendungen_id');

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungsberechtigungen for lbDMFManager_Entities
select "dropConstraint"('anwendungsberechtigungen', 'cst_anwendungsberechtigungen_iduser_users_id');

select "dropConstraint"('anwendungsberechtigungen', 'cst_anwendungsberechtigungen_idformular_formulare_id');

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table applevel_plugin_registry for lbDMFManager_Entities
-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table codegentarget for lbDMFManager_Entities
-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table column_types for lbDMFManager_Entities
-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formular_actions for lbDMFManager_Entities
select "dropConstraint"('formular_actions', 'cst_formular_actions_formular_formulare_id');

select "dropConstraint"('formular_actions', 'cst_formular_actions_action_actions_id');

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formular_parameters for lbDMFManager_Entities
select "dropConstraint"('formular_parameters', 'cst_formular_parameters_formularid_formulare_id');

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formulare for lbDMFManager_Entities
select "dropConstraint"('formulare', 'cst_formulare_anwendungid_anwendungen_id');

select "dropConstraint"('formulare', 'cst_formulare_typ_formulartypen_id');

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formulartypen for lbDMFManager_Entities
-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table regressiontest for lbDMFManager_Entities
-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_element_types for lbDMFManager_Entities
-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_elements for lbDMFManager_Entities
select "dropConstraint"('report_elements', 'cst_report_elements_reportid_reports_id');

select "dropConstraint"('report_elements', 'cst_report_elements_typ_report_element_types_id');

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_parameters for lbDMFManager_Entities
select "dropConstraint"('report_parameters', 'cst_report_parameters_reportid_reports_id');

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_texts for lbDMFManager_Entities
select "dropConstraint"('report_texts', 'cst_report_texts_elementid_report_elements_id');

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table reports for lbDMFManager_Entities
-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table translations for lbDMFManager_Entities
-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table user_anwendungen for lbDMFManager_Entities
select "dropConstraint"('user_anwendungen', 'cst_user_anwendungen_userid_users_id');

select "dropConstraint"('user_anwendungen', 'cst_user_anwendungen_anwendungenid_anwendungen_id');

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table users for lbDMFManager_Entities
select "dropConstraint"('users', 'cst_users_lastapp_anwendungen_id');

-- Class Benutzer of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Anwendungen of type FORM found.
				
-- Class AnwendungenFormulare of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
-- Class Templates of type FORM found.
				
-- Class Templates of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Templates for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('Templates');

-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('action_parameters');

-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_parameter for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('action_step_parameter');

-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_transitions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('action_step_transitions');

-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('action_steps');

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('action_types');

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('actions');

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('anwendungen');

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('anwendungen_formulare');

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('anwendungs_parameter');

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('anwendungsberechtigungen');

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('applevel_plugin_registry');

-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('codegentarget');

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('column_types');

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('foreignkey_visibledata_mapping');

-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('formular_actions');

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('formular_parameters');

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('formulare');

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('formulartypen');

-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('regressiontest');

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('report_element_types');

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('report_elements');

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('report_parameters');

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('report_texts');

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('reports');

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('translations');

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('user_anwendungen');

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select "dropTable"('users');

SET SESSION AUTHORIZATION 'dba';

-- Class Benutzer of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Anwendungen of type FORM found.
				
-- Class AnwendungenFormulare of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
-- Class Templates of type FORM found.
				
-- Class Templates of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Templates for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE Templates
CREATE TABLE "Templates" (
	"ID" SERIAL,
	"Name" CHAR(255),
	"Purpose" CHAR(255),
	"Description" TEXT,
	"Aproved" BOOLEAN,
	"Cartridge" INTEGER
) WITH OIDS;

-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_parameters
CREATE TABLE "action_parameters" (
	"id" SERIAL,
	"actionid" INTEGER,
	"name" CHAR(255),
	"value" CHAR(255),
	"interface" CHAR(255),
	"description" CHAR(255)
) WITH OIDS;

-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_parameter for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_step_parameter
CREATE TABLE "action_step_parameter" (
	"id" SERIAL,
	"action_step_id" INTEGER,
	"name" CHAR(255),
	"value" CHAR(255),
	"interface" CHAR(255),
	"description" CHAR(255)
) WITH OIDS;

-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_transitions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_step_transitions
CREATE TABLE "action_step_transitions" (
	"id" SERIAL,
	"expression" CHAR(255),
	"src_actionid" INTEGER,
	"dst_actionid" INTEGER,
	"description" CHAR(255)
) WITH OIDS;

-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_steps
CREATE TABLE "action_steps" (
	"id" SERIAL,
	"actionid" INTEGER,
	"bezeichnung" CHAR(255),
	"a_order_nr" INTEGER,
	"type" INTEGER,
	"what" CHAR(255)
) WITH OIDS;

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_types
CREATE TABLE "action_types" (
	"id" SERIAL,
	"bezeichnung" CHAR(255),
	"action_handler" CHAR(255),
	"module" CHAR(255)
) WITH OIDS;

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE actions
CREATE TABLE "actions" (
	"id" SERIAL,
	"name" CHAR(255),
	"typ" INTEGER,
	"source" CHAR(255),
	"target" CHAR(255)
) WITH OIDS;

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE anwendungen
CREATE TABLE "anwendungen" (
	"id" SERIAL,
	"name" CHAR(255),
	"titel" CHAR(255),
	"modulename" CHAR(255),
	"functor" CHAR(255),
	"interface" CHAR(255)
) WITH OIDS;

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE anwendungen_formulare
CREATE TABLE "anwendungen_formulare" (
	"id" SERIAL,
	"anwendungid" INTEGER,
	"formularid" INTEGER
) WITH OIDS;

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE anwendungs_parameter
CREATE TABLE "anwendungs_parameter" (
	"id" SERIAL,
	"parametername" CHAR(255),
	"parametervalue" CHAR(255),
	"anwendungid" INTEGER
) WITH OIDS;

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE anwendungsberechtigungen
CREATE TABLE "anwendungsberechtigungen" (
	"id" SERIAL,
	"iduser" INTEGER,
	"idformular" INTEGER
) WITH OIDS;

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE applevel_plugin_registry
CREATE TABLE "applevel_plugin_registry" (
	"id" SERIAL,
	"anwendungid" INTEGER
) WITH OIDS;

-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE codegentarget
CREATE TABLE "codegentarget" (
	"id" SERIAL,
	"name" CHAR(255),
	"titel" CHAR(255),
	"modulename" CHAR(255),
	"functor" CHAR(255),
	"interface" CHAR(255)
) WITH OIDS;

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE column_types
CREATE TABLE "column_types" (
	"id" SERIAL,
	"name" CHAR(255),
	"tablename" CHAR(255),
	"ro" BOOLEAN,
	"specialcolumn" BOOLEAN,
	"controltype" CHAR(255)
) WITH OIDS;

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE foreignkey_visibledata_mapping
CREATE TABLE "foreignkey_visibledata_mapping" (
	"id" SERIAL,
	"fkname" CHAR(255),
	"fktable" CHAR(255),
	"pkname" CHAR(255),
	"pktable" CHAR(255)
) WITH OIDS;

-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE formular_actions
CREATE TABLE "formular_actions" (
	"id" SERIAL,
	"formular" INTEGER,
	"action" INTEGER,
	"event" CHAR(255)
) WITH OIDS;

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE formular_parameters
CREATE TABLE "formular_parameters" (
	"id" SERIAL,
	"parametername" CHAR(255),
	"parametervalue" CHAR(255),
	"formularid" INTEGER
) WITH OIDS;

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE formulare
CREATE TABLE "formulare" (
	"id" SERIAL,
	"name" CHAR(255),
	"menuname" CHAR(255),
	"menuorder" INTEGER,
	"eventname" CHAR(255),
	"menuhilfe" CHAR(255),
	"toolbarimage" CHAR(255),
	"anwendungid" INTEGER,
	"typ" INTEGER
) WITH OIDS;

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE formulartypen
CREATE TABLE "formulartypen" (
	"id" SERIAL,
	"handlermodule" CHAR(255),
	"handlerfunctor" CHAR(255),
	"handlerinterface" CHAR(255),
	"namespace" CHAR(255),
	"beschreibung" CHAR(255)
) WITH OIDS;

-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE regressiontest
CREATE TABLE "regressiontest" (
	"id" SERIAL,
	"test" CHAR(255),
	"btest" BOOLEAN,
	"btest1" BOOLEAN
) WITH OIDS;

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE report_element_types
CREATE TABLE "report_element_types" (
	"id" SERIAL,
	"name" CHAR(255),
	"description" CHAR(255)
) WITH OIDS;

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE report_elements
CREATE TABLE "report_elements" (
	"id" SERIAL,
	"reportid" INTEGER,
	"typ" INTEGER,
	"name" CHAR(255),
	"x" INTEGER,
	"y" INTEGER,
	"w" INTEGER,
	"h" INTEGER,
	"description" CHAR(255)
) WITH OIDS;

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE report_parameters
CREATE TABLE "report_parameters" (
	"id" SERIAL,
	"reportid" INTEGER,
	"name" CHAR(255),
	"value" INTEGER
) WITH OIDS;

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE report_texts
CREATE TABLE "report_texts" (
	"id" SERIAL,
	"elementid" INTEGER,
	"line" INTEGER,
	"text" CHAR(255)
) WITH OIDS;

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE reports
CREATE TABLE "reports" (
	"id" SERIAL,
	"name" CHAR(255),
	"description" CHAR(255)
) WITH OIDS;

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE translations
CREATE TABLE "translations" (
	"id" SERIAL,
	"text" CHAR(255),
	"translated" CHAR(255),
	"language" CHAR(255)
) WITH OIDS;

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE user_anwendungen
CREATE TABLE "user_anwendungen" (
	"id" SERIAL,
	"userid" INTEGER,
	"anwendungenid" INTEGER
) WITH OIDS;

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE users
CREATE TABLE "users" (
	"id" SERIAL,
	"name" CHAR(255),
	"vorname" CHAR(255),
	"userid" CHAR(255),
	"passwort" CHAR(255),
	"lastapp" INTEGER
) WITH OIDS;

-- Class Benutzer of type FORM found.
				
-- Class Formulare of type FORM found.
				
-- Class Formular_Parameter of type FORM found.
				
-- Class AnwendungenBenutzer of type FORM found.
				
-- Class FormulareAnwendung of type FORM found.
				
-- Class Anwendungen of type FORM found.
				
-- Class AnwendungenFormulare of type FORM found.
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
-- Class Templates of type FORM found.
				
-- Class Templates of type ENTITY found.

-- Generate application tables Templates for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "Templates" ADD CONSTRAINT "Templates_pkey" PRIMARY KEY ("ID");
		
-- Class action_parameters of type ENTITY found.

-- Generate application tables action_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "action_parameters" ADD CONSTRAINT "action_parameters_pkey" PRIMARY KEY ("id");
		
-- Class action_step_parameter of type ENTITY found.

-- Generate application tables action_step_parameter for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "action_step_parameter" ADD CONSTRAINT "action_step_parameter_pkey" PRIMARY KEY ("id");
		
-- Class action_step_transitions of type ENTITY found.

-- Generate application tables action_step_transitions for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "action_step_transitions" ADD CONSTRAINT "action_step_transitions_pkey" PRIMARY KEY ("id");
		
-- Class action_steps of type ENTITY found.

-- Generate application tables action_steps for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "action_steps" ADD CONSTRAINT "action_steps_pkey" PRIMARY KEY ("id");
		
-- Class action_types of type ENTITY found.

-- Generate application tables action_types for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "action_types" ADD CONSTRAINT "action_types_pkey" PRIMARY KEY ("id");
		
-- Class actions of type ENTITY found.

-- Generate application tables actions for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "actions" ADD CONSTRAINT "actions_pkey" PRIMARY KEY ("id");
		
-- Class anwendungen of type ENTITY found.

-- Generate application tables anwendungen for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "anwendungen" ADD CONSTRAINT "anwendungen_pkey" PRIMARY KEY ("id");
		
-- Class anwendungen_formulare of type ENTITY found.

-- Generate application tables anwendungen_formulare for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "anwendungen_formulare_pkey" PRIMARY KEY ("id");
		
-- Class anwendungs_parameter of type ENTITY found.

-- Generate application tables anwendungs_parameter for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "anwendungs_parameter_pkey" PRIMARY KEY ("id");
		
-- Class anwendungsberechtigungen of type ENTITY found.

-- Generate application tables anwendungsberechtigungen for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "anwendungsberechtigungen_pkey" PRIMARY KEY ("id");
		
-- Class applevel_plugin_registry of type ENTITY found.

-- Generate application tables applevel_plugin_registry for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "applevel_plugin_registry" ADD CONSTRAINT "applevel_plugin_registry_pkey" PRIMARY KEY ("id");
		
-- Class codegentarget of type ENTITY found.

-- Generate application tables codegentarget for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "codegentarget" ADD CONSTRAINT "codegentarget_pkey" PRIMARY KEY ("id");
		
-- Class column_types of type ENTITY found.

-- Generate application tables column_types for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "column_types" ADD CONSTRAINT "column_types_pkey" PRIMARY KEY ("id");
		
-- Class foreignkey_visibledata_mapping of type ENTITY found.

-- Generate application tables foreignkey_visibledata_mapping for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "foreignkey_visibledata_mapping" ADD CONSTRAINT "foreignkey_visibledata_mapping_pkey" PRIMARY KEY ("id");
		
-- Class formular_actions of type ENTITY found.

-- Generate application tables formular_actions for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "formular_actions" ADD CONSTRAINT "formular_actions_pkey" PRIMARY KEY ("id");
		
-- Class formular_parameters of type ENTITY found.

-- Generate application tables formular_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "formular_parameters" ADD CONSTRAINT "formular_parameters_pkey" PRIMARY KEY ("id");
		
-- Class formulare of type ENTITY found.

-- Generate application tables formulare for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "formulare" ADD CONSTRAINT "formulare_pkey" PRIMARY KEY ("id");
		
-- Class formulartypen of type ENTITY found.

-- Generate application tables formulartypen for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "formulartypen" ADD CONSTRAINT "formulartypen_pkey" PRIMARY KEY ("id");
		
-- Class regressiontest of type ENTITY found.

-- Generate application tables regressiontest for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "regressiontest" ADD CONSTRAINT "regressiontest_pkey" PRIMARY KEY ("id");
		
-- Class report_element_types of type ENTITY found.

-- Generate application tables report_element_types for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "report_element_types" ADD CONSTRAINT "report_element_types_pkey" PRIMARY KEY ("id");
		
-- Class report_elements of type ENTITY found.

-- Generate application tables report_elements for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "report_elements" ADD CONSTRAINT "report_elements_pkey" PRIMARY KEY ("id");
		
-- Class report_parameters of type ENTITY found.

-- Generate application tables report_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "report_parameters" ADD CONSTRAINT "report_parameters_pkey" PRIMARY KEY ("id");
		
-- Class report_texts of type ENTITY found.

-- Generate application tables report_texts for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "report_texts" ADD CONSTRAINT "report_texts_pkey" PRIMARY KEY ("id");
		
-- Class reports of type ENTITY found.

-- Generate application tables reports for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "reports" ADD CONSTRAINT "reports_pkey" PRIMARY KEY ("id");
		
-- Class translations of type ENTITY found.

-- Generate application tables translations for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "translations" ADD CONSTRAINT "translations_pkey" PRIMARY KEY ("id");
		
-- Class user_anwendungen of type ENTITY found.

-- Generate application tables user_anwendungen for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "user_anwendungen" ADD CONSTRAINT "user_anwendungen_pkey" PRIMARY KEY ("id");
		
-- Class users of type ENTITY found.

-- Generate application tables users for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


ALTER TABLE "users" ADD CONSTRAINT "users_pkey" PRIMARY KEY ("id");
		
-- Generate PostgreSQL application relations for table Templates for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table action_parameters for lbDMFManager_Entities
ALTER TABLE "action_parameters" ADD CONSTRAINT "cst_action_parameters_actionid_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );

-- Generate PostgreSQL application relations for table action_step_parameter for lbDMFManager_Entities
ALTER TABLE "action_step_parameter" ADD CONSTRAINT "cst_action_step_parameter_action_step_id_action_steps_id" FOREIGN KEY ( "action_step_id" ) REFERENCES "action_steps" ( "id" );

-- Generate PostgreSQL application relations for table action_step_transitions for lbDMFManager_Entities
ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_src_actionid_action_steps_id" FOREIGN KEY ( "src_actionid" ) REFERENCES "action_steps" ( "id" );

ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_dst_actionid_action_steps_id" FOREIGN KEY ( "dst_actionid" ) REFERENCES "action_steps" ( "id" );

-- Generate PostgreSQL application relations for table action_steps for lbDMFManager_Entities
ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_actionid_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );

ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_type_action_types_id" FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "id" );

-- Generate PostgreSQL application relations for table action_types for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table actions for lbDMFManager_Entities
ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_typ_action_types_id" FOREIGN KEY ( "typ" ) REFERENCES "action_types" ( "id" );

-- Generate PostgreSQL application relations for table anwendungen for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table anwendungen_formulare for lbDMFManager_Entities
ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_anwendungid_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_formularid_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );

-- Generate PostgreSQL application relations for table anwendungs_parameter for lbDMFManager_Entities
ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "cst_anwendungs_parameter_anwendungid_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

-- Generate PostgreSQL application relations for table anwendungsberechtigungen for lbDMFManager_Entities
ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_iduser_users_id" FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "id" );

ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_idformular_formulare_id" FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "id" );

-- Generate PostgreSQL application relations for table applevel_plugin_registry for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table codegentarget for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table column_types for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table formular_actions for lbDMFManager_Entities
ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_formular_formulare_id" FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "id" );

ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_action_actions_id" FOREIGN KEY ( "action" ) REFERENCES "actions" ( "id" );

-- Generate PostgreSQL application relations for table formular_parameters for lbDMFManager_Entities
ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formular_parameters_formularid_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );

-- Generate PostgreSQL application relations for table formulare for lbDMFManager_Entities
ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_anwendungid_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_typ_formulartypen_id" FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "id" );

-- Generate PostgreSQL application relations for table formulartypen for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table regressiontest for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table report_element_types for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table report_elements for lbDMFManager_Entities
ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_reportid_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );

ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_typ_report_element_types_id" FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "id" );

-- Generate PostgreSQL application relations for table report_parameters for lbDMFManager_Entities
ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_report_parameters_reportid_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );

-- Generate PostgreSQL application relations for table report_texts for lbDMFManager_Entities
ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_texts_elementid_report_elements_id" FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "id" );

-- Generate PostgreSQL application relations for table reports for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table translations for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table user_anwendungen for lbDMFManager_Entities
ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_userid_users_id" FOREIGN KEY ( "userid" ) REFERENCES "users" ( "id" );

ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_anwendungenid_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );

-- Generate PostgreSQL application relations for table users for lbDMFManager_Entities
ALTER TABLE "users" ADD CONSTRAINT "cst_users_lastapp_anwendungen_id" FOREIGN KEY ( "lastapp" ) REFERENCES "anwendungen" ( "id" );