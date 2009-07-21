
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

SET SESSION AUTHORIZATION 'dba';

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

-- Generate application table action_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_parameters
CREATE TABLE "action_parameters" (
	"id" SERIAL,
	"name" CHAR(255),
	"value" CHAR(255),
	"interface" CHAR(255),
	"description" CHAR(255),
	"actionid" INTEGER
) WITH OIDS;

-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_parameter for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_step_parameter
CREATE TABLE "action_step_parameter" (
	"id" SERIAL,
	"name" CHAR(255),
	"value" CHAR(255),
	"interface" CHAR(255),
	"description" CHAR(255),
	"action_step_id" INTEGER
) WITH OIDS;

-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_transitions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_step_transitions
CREATE TABLE "action_step_transitions" (
	"id" SERIAL,
	"expression" CHAR(255),
	"description" CHAR(255),
	"dst_actionid" INTEGER,
	"src_actionid" INTEGER
) WITH OIDS;

-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_steps
CREATE TABLE "action_steps" (
	"id" SERIAL,
	"bezeichnung" CHAR(255),
	"a_order_nr" INTEGER,
	"what" CHAR(255),
	"type" INTEGER,
	"actionid" INTEGER
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
	"source" CHAR(255),
	"target" CHAR(255),
	"typ" INTEGER
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
	"idformular" INTEGER,
	"iduser" INTEGER
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
	"event" CHAR(255),
	"action" INTEGER,
	"formular" INTEGER
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
	"name" CHAR(255),
	"x" INTEGER,
	"y" INTEGER,
	"w" INTEGER,
	"h" INTEGER,
	"description" CHAR(255),
	"typ" INTEGER,
	"reportid" INTEGER
) WITH OIDS;

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE report_parameters
CREATE TABLE "report_parameters" (
	"id" SERIAL,
	"name" CHAR(255),
	"value" INTEGER,
	"reportid" INTEGER
) WITH OIDS;

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE report_texts
CREATE TABLE "report_texts" (
	"id" SERIAL,
	"line" INTEGER,
	"text" CHAR(255),
	"elementid" INTEGER
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
	"anwendungenid" INTEGER,
	"userid" INTEGER
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
				
-- Class Aktionen of type FORM found.
				
-- Class Uebersetzungen of type FORM found.
				
-- Class Formularaktionenzuordnen of type FORM found.
				
-- Class Anwendungsparameter of type FORM found.
				
-- Class Aktionsschrittezuordnen of type FORM found.
				
-- Class Reportdefinitionen of type FORM found.
				
-- Class Reportparameter of type FORM found.
				
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
		
-- Generate PostgreSQL application relations for table action_parameters for lbDMFManager_Entities	

ALTER TABLE "action_parameters" ADD CONSTRAINT "cst_action_parameters_actionid_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );

-- Generate PostgreSQL application relations for table action_step_parameter for lbDMFManager_Entities	

ALTER TABLE "action_step_parameter" ADD CONSTRAINT "cst_action_step_parameter_action_step_id_action_steps_id" FOREIGN KEY ( "action_step_id" ) REFERENCES "action_steps" ( "id" );

-- Generate PostgreSQL application relations for table action_step_transitions for lbDMFManager_Entities	

ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_dst_actionid_action_steps_id" FOREIGN KEY ( "dst_actionid" ) REFERENCES "action_steps" ( "id" );
	

ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_src_actionid_action_steps_id" FOREIGN KEY ( "src_actionid" ) REFERENCES "action_steps" ( "id" );

-- Generate PostgreSQL application relations for table action_steps for lbDMFManager_Entities	

ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_type_action_types_id" FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "id" );
	

ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_actionid_actions_id" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );

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

ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_idformular_formulare_id" FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "id" );
	

ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_iduser_users_id" FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "id" );

-- Generate PostgreSQL application relations for table applevel_plugin_registry for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table codegentarget for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table column_types for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table formular_actions for lbDMFManager_Entities	

ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_action_actions_id" FOREIGN KEY ( "action" ) REFERENCES "actions" ( "id" );
	

ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_formular_formulare_id" FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "id" );

-- Generate PostgreSQL application relations for table formular_parameters for lbDMFManager_Entities	

ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formular_parameters_formularid_formulare_id" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );

-- Generate PostgreSQL application relations for table formulare for lbDMFManager_Entities	

ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_anwendungid_anwendungen_id" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
	

ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_typ_formulartypen_id" FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "id" );

-- Generate PostgreSQL application relations for table formulartypen for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table regressiontest for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table report_element_types for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table report_elements for lbDMFManager_Entities	

ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_typ_report_element_types_id" FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "id" );
	

ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_reportid_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );

-- Generate PostgreSQL application relations for table report_parameters for lbDMFManager_Entities	

ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_report_parameters_reportid_reports_id" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );

-- Generate PostgreSQL application relations for table report_texts for lbDMFManager_Entities	

ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_texts_elementid_report_elements_id" FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "id" );

-- Generate PostgreSQL application relations for table reports for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table translations for lbDMFManager_Entities
-- Generate PostgreSQL application relations for table user_anwendungen for lbDMFManager_Entities	

ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_anwendungenid_anwendungen_id" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );
	

ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_userid_users_id" FOREIGN KEY ( "userid" ) REFERENCES "users" ( "id" );

-- Generate PostgreSQL application relations for table users for lbDMFManager_Entities	

ALTER TABLE "users" ADD CONSTRAINT "cst_users_lastapp_anwendungen_id" FOREIGN KEY ( "lastapp" ) REFERENCES "anwendungen" ( "id" );


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



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "passwort", "userid", "vorname", "name" from "users" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Benutzer'));
insert into column_types (name, tablename, ro) values ('ID', 'Benutzer', true);


-- Association from Benutzer to AnwendungenBenutzer
-- From formular 'BOUML_0x1f402_4'
-- To   formular 'BOUML_0x1f582_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21782_0.



-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21782_0',  (select id from action_types where bezeichnung = 'Buttonpress'), 'userid');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for AnwendungenBenutzer', 1, 'AnwendungenBenutzer', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21782_0' and source = 'userid'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21782_0' and source = 'userid'), 'action_master_detail_BOUML_0x21782_0');
UPDATE actions set name = 'AnwendungenBenutzer' where name = 'BOUML_0x21782_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Benutzer'));


		-- Class Formulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formulare');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', 'kpersonalizer.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "name", "menuname", "menuhilfe", "eventname", "toolbarimage", "anwendungid", "typ" from "formulare" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formulare'));
insert into column_types (name, tablename, ro) values ('ID', 'Formulare', true);


insert into column_types (name, tablename, specialcolumn, controltype) values ('toolbarimage', 'Formulare', true, 'toolbarimagefile');

-- Association from Formulare to Formular_Parameter
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f502_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21802_0.



-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21802_0',  (select id from action_types where bezeichnung = 'Buttonpress'), 'name');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formular_Parameter', 1, 'Formular_Parameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21802_0' and source = 'name'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21802_0' and source = 'name'), 'action_master_detail_BOUML_0x21802_0');
UPDATE actions set name = 'Formular_Parameter' where name = 'BOUML_0x21802_0';
	
-- Association from Formulare to Formularaktionenzuordnen
-- From formular 'BOUML_0x1f482_4'
-- To   formular 'BOUML_0x1f802_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21882_0.



-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21882_0',  (select id from action_types where bezeichnung = 'Buttonpress'), 'name');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formularaktionenzuordnen', 1, 'Formularaktionenzuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21882_0' and source = 'name'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21882_0' and source = 'name'), 'action_master_detail_BOUML_0x21882_0');
UPDATE actions set name = 'Formularaktionenzuordnen' where name = 'BOUML_0x21882_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formulare'));


		-- Class Formular_Parameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formular_Parameter');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', 'formular_params.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "parametervalue", "parametername", "formularid" from "formular_parameters" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formular_Parameter'));
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



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "titel", "name", "interface", "functor", "modulename" from "anwendungen" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungen'));
insert into column_types (name, tablename, ro) values ('ID', 'Anwendungen', true);


-- Association from Anwendungen to Anwendungsparameter
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f882_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21682_0.



-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21682_0',  (select id from action_types where bezeichnung = 'Buttonpress'), 'name');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungsparameter', 1, 'Anwendungsparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21682_0' and source = 'name'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21682_0' and source = 'name'), 'action_master_detail_BOUML_0x21682_0');
UPDATE actions set name = 'Anwendungsparameter' where name = 'BOUML_0x21682_0';
	
-- Association from Anwendungen to Formulare
-- From formular 'BOUML_0x1f682_4'
-- To   formular 'BOUML_0x1f482_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21702_0.



-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21702_0',  (select id from action_types where bezeichnung = 'Buttonpress'), 'name');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21702_0' and source = 'name'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21702_0' and source = 'name'), 'action_master_detail_BOUML_0x21702_0');
UPDATE actions set name = 'Formulare' where name = 'BOUML_0x21702_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungen'));


		-- Class Aktionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Aktionen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', 'cache.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "target", "source", "name", "typ" from "actions" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionen'));
insert into column_types (name, tablename, ro) values ('ID', 'Aktionen', true);


-- Association from Aktionen to Aktionsschrittezuordnen
-- From formular 'BOUML_0x1f702_4'
-- To   formular 'BOUML_0x1f902_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21602_0.



-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21602_0',  (select id from action_types where bezeichnung = 'Buttonpress'), 'name');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Aktionsschrittezuordnen', 1, 'Aktionsschrittezuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21602_0' and source = 'name'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21602_0' and source = 'name'), 'action_master_detail_BOUML_0x21602_0');
UPDATE actions set name = 'Aktionsschrittezuordnen' where name = 'BOUML_0x21602_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionen'));


		-- Class Uebersetzungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Uebersetzungen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', 'babelfish.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "translated", "text" from "translations" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Uebersetzungen'));
insert into column_types (name, tablename, ro) values ('ID', 'Uebersetzungen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Uebersetzungen'));


		-- Class Formularaktionenzuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formularaktionenzuordnen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formularaktionenzuordnen', 'Formularaktionenzuordnen verwalten', 'manageFormularaktionenzuordnen', 'Edit data of Formularaktionenzuordnen', 'actions_formulare.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "event", "action", "formular" from "formular_actions" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formularaktionenzuordnen'));
insert into column_types (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formularaktionenzuordnen'));


		-- Class Anwendungsparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Anwendungsparameter');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', 'app_params.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "parametervalue", "parametername", "anwendungid" from "anwendungs_parameter" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungsparameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Anwendungsparameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungsparameter'));


		-- Class Aktionsschrittezuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Aktionsschrittezuordnen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', 'action_steps.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "bezeichnung", "what", "a_order_nr", "type", "actionid" from "action_steps" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionsschrittezuordnen'));
insert into column_types (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionsschrittezuordnen'));


		-- Class Reportdefinitionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Reportdefinitionen');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', 'print_class.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "description", "name" from "reports" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Reportdefinitionen'));
insert into column_types (name, tablename, ro) values ('ID', 'Reportdefinitionen', true);


-- Association from Reportdefinitionen to Reportparameter
-- From formular 'BOUML_0x1f982_4'
-- To   formular 'BOUML_0x1fa02_4'




-- Create Postgresql based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: BOUML_0x21902_0.



-- Build up a master detail action
INSERT INTO actions (name, typ, source) values ('BOUML_0x21902_0',  (select id from action_types where bezeichnung = 'Buttonpress'), 'name');	
INSERT INTO action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Reportparameter', 1, 'Reportparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'BOUML_0x21902_0' and source = 'name'));
INSERT INTO formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'BOUML_0x21902_0' and source = 'name'), 'action_master_detail_BOUML_0x21902_0');
UPDATE actions set name = 'Reportparameter' where name = 'BOUML_0x21902_0';
	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Reportdefinitionen'));


		-- Class Reportparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Reportparameter');



insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', 'kword.png', getorcreateapplication('lbDMF Manager'), (select id from formulartypen where handlerinterface = 'lb_I_DatabaseForm' and beschreibung = 'Dynamisch aufgebautes Datenbankformular'));



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "value", "name", "reportid" from "report_parameters" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Reportparameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Reportparameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Reportparameter'));


-- Script ready.
