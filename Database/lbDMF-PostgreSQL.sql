
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

CREATE OR REPLACE FUNCTION droptable("varchar")
  RETURNS void AS
'
declare
tres text;
declare tt alias for $1;
begin
  select tablename into tres from pg_tables where tablename = $1;
  if not tres is null then
    execute ''DROP TABLE "'' || $1 || ''" CASCADE'';
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
				
-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('action_steps');

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('action_types');

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('actions');

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('anwendungen');

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('anwendungen_formulare');

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('anwendungs_parameter');

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('anwendungsberechtigungen');

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('applevel_plugin_registry');

-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('codegentarget');

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('column_types');

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('foreignkey_visibledata_mapping');

-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('formular_actions');

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('formular_parameters');

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('formulare');

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('formulartypen');

-- Class lbDMF_ForeignKeys of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table lbDMF_ForeignKeys for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('lbDMF_ForeignKeys');

-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('regressiontest');

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('report_element_types');

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('report_elements');

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('report_parameters');

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('report_texts');

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('reports');

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('translations');

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('user_anwendungen');

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'


select dropTable('users');

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
				
-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_steps
CREATE TABLE "action_steps" (
	
	"id" SERIAL,
--,,
	"actionid" INTEGER,
	"bezeichnung" CHAR(255),
	"a_order_nr" INTEGER,
--,,
	"type" INTEGER,
	"what" CHAR(255)
) WITH OIDS;

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE action_types
CREATE TABLE "action_types" (
	
--,,
--,,
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
	
--,,
--,,
	"id" SERIAL,
	"name" CHAR(255),
--,,
	"typ" INTEGER,
	"source" CHAR(255),
	"target" INTEGER
) WITH OIDS;

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE anwendungen
CREATE TABLE "anwendungen" (
	
--,,
--,,
--,,
--,,
--,,
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
--,,
	"anwendungid" INTEGER,
--,,
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
--,,
	"anwendungid" INTEGER
) WITH OIDS;

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE anwendungsberechtigungen
CREATE TABLE "anwendungsberechtigungen" (
	
	"id" SERIAL,
--,,
	"iduser" INTEGER,
--,,
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
--,,
	"formular" INTEGER,
--,,
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
--,,
	"formularid" INTEGER
) WITH OIDS;

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE formulare
CREATE TABLE "formulare" (
	
--,,
--,,
--,,
--,,
	"id" SERIAL,
	"name" CHAR(255),
	"menuname" CHAR(255),
	"menuorder" INTEGER,
	"eventname" CHAR(255),
	"menuhilfe" CHAR(255),
	"toolbarimage" CHAR(255),
--,,
	"anwendungid" INTEGER,
--,,
	"typ" INTEGER
) WITH OIDS;

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE formulartypen
CREATE TABLE "formulartypen" (
	
--,,
	"id" SERIAL,
	"handlermodule" CHAR(255),
	"handlerfunctor" CHAR(255),
	"handlerinterface" CHAR(255),
	"namespace" CHAR(255),
	"beschreibung" CHAR(255)
) WITH OIDS;

-- Class lbDMF_ForeignKeys of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table lbDMF_ForeignKeys for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE lbDMF_ForeignKeys
CREATE TABLE "lbDMF_ForeignKeys" (
	
	"PKTable" CHAR(255),
	"PKColumn" CHAR(255),
	"FKTable" CHAR(255),
	"FKColumn" CHAR(255)
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
	
--,,
	"id" SERIAL,
	"name" CHAR(255),
	"description" CHAR(255)
) WITH OIDS;

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE report_elements
CREATE TABLE "report_elements" (
	
--,,
	"id" SERIAL,
--,,
	"reportid" INTEGER,
--,,
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
--,,
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
--,,
	"elementid" INTEGER,
	"line" INTEGER,
	"text" CHAR(255)
) WITH OIDS;

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE reports
CREATE TABLE "reports" (
	
--,,
--,,
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
--,,
	"userid" INTEGER,
--,,
	"anwendungenid" INTEGER
) WITH OIDS;

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'PostgreSQL'



-- CREATE TABLE users
CREATE TABLE "users" (
	
--,,
--,,
	"id" SERIAL,
	"name" CHAR(255),
	"vorname" CHAR(255),
	"userid" CHAR(255),
	"passwort" CHAR(255),
--,,
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
		
-- Class lbDMF_ForeignKeys of type ENTITY found.

-- Generate application tables lbDMF_ForeignKeys for lbDMFManager_Entities primary keys. Tagtet database: 'PostgreSQL'


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
		
-- Generate application table action_steps for lbDMFManager_Entities
-- Generate application table action_types for lbDMFManager_Entities

--ALTER TABLE "action_types" ADD CONSTRAINT "action_types_pkey" PRIMARY KEY ("id");
ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_types_id_action_steps_type_1" FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "id" );

--ALTER TABLE "action_types" ADD CONSTRAINT "action_types_pkey" PRIMARY KEY ("id");
ALTER TABLE "actions" ADD CONSTRAINT "cst_action_types_id_actions_typ_3" FOREIGN KEY ( "typ" ) REFERENCES "action_types" ( "id" );
-- Generate application table actions for lbDMFManager_Entities

--ALTER TABLE "actions" ADD CONSTRAINT "actions_pkey" PRIMARY KEY ("id");
ALTER TABLE "action_steps" ADD CONSTRAINT "cst_actions_id_action_steps_actionid_2" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );

--ALTER TABLE "actions" ADD CONSTRAINT "actions_pkey" PRIMARY KEY ("id");
ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_actions_id_formular_actions_action_9" FOREIGN KEY ( "action" ) REFERENCES "actions" ( "id" );
-- Generate application table anwendungen for lbDMFManager_Entities

--ALTER TABLE "anwendungen" ADD CONSTRAINT "anwendungen_pkey" PRIMARY KEY ("id");
ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_id_anwendungen_formulare_anwendungid_4" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

--ALTER TABLE "anwendungen" ADD CONSTRAINT "anwendungen_pkey" PRIMARY KEY ("id");
ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "cst_anwendungen_id_anwendungs_parameter_anwendungid_6" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

--ALTER TABLE "anwendungen" ADD CONSTRAINT "anwendungen_pkey" PRIMARY KEY ("id");
ALTER TABLE "formulare" ADD CONSTRAINT "cst_anwendungen_id_formulare_anwendungid_12" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );

--ALTER TABLE "anwendungen" ADD CONSTRAINT "anwendungen_pkey" PRIMARY KEY ("id");
ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_anwendungen_id_user_anwendungen_anwendungenid_18" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );

--ALTER TABLE "anwendungen" ADD CONSTRAINT "anwendungen_pkey" PRIMARY KEY ("id");
ALTER TABLE "users" ADD CONSTRAINT "cst_anwendungen_id_users_lastapp_20" FOREIGN KEY ( "lastapp" ) REFERENCES "anwendungen" ( "id" );
-- Generate application table anwendungen_formulare for lbDMFManager_Entities
-- Generate application table anwendungs_parameter for lbDMFManager_Entities
-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities
-- Generate application table applevel_plugin_registry for lbDMFManager_Entities
-- Generate application table codegentarget for lbDMFManager_Entities
-- Generate application table column_types for lbDMFManager_Entities
-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Generate application table formular_actions for lbDMFManager_Entities
-- Generate application table formular_parameters for lbDMFManager_Entities
-- Generate application table formulare for lbDMFManager_Entities

--ALTER TABLE "formulare" ADD CONSTRAINT "formulare_pkey" PRIMARY KEY ("id");
ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_formulare_id_anwendungen_formulare_formularid_5" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );

--ALTER TABLE "formulare" ADD CONSTRAINT "formulare_pkey" PRIMARY KEY ("id");
ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_formulare_id_anwendungsberechtigungen_idformular_7" FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "id" );

--ALTER TABLE "formulare" ADD CONSTRAINT "formulare_pkey" PRIMARY KEY ("id");
ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formulare_id_formular_actions_formular_10" FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "id" );

--ALTER TABLE "formulare" ADD CONSTRAINT "formulare_pkey" PRIMARY KEY ("id");
ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formulare_id_formular_parameters_formularid_11" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
-- Generate application table formulartypen for lbDMFManager_Entities

--ALTER TABLE "formulartypen" ADD CONSTRAINT "formulartypen_pkey" PRIMARY KEY ("id");
ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulartypen_id_formulare_typ_13" FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "id" );
-- Generate application table lbDMF_ForeignKeys for lbDMFManager_Entities
-- Generate application table regressiontest for lbDMFManager_Entities
-- Generate application table report_element_types for lbDMFManager_Entities

--ALTER TABLE "report_element_types" ADD CONSTRAINT "report_element_types_pkey" PRIMARY KEY ("id");
ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_element_types_id_report_elements_typ_14" FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "id" );
-- Generate application table report_elements for lbDMFManager_Entities

--ALTER TABLE "report_elements" ADD CONSTRAINT "report_elements_pkey" PRIMARY KEY ("id");
ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_elements_id_report_texts_elementid_17" FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "id" );
-- Generate application table report_parameters for lbDMFManager_Entities
-- Generate application table report_texts for lbDMFManager_Entities
-- Generate application table reports for lbDMFManager_Entities

--ALTER TABLE "reports" ADD CONSTRAINT "reports_pkey" PRIMARY KEY ("id");
ALTER TABLE "report_elements" ADD CONSTRAINT "cst_reports_id_report_elements_reportid_15" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );

--ALTER TABLE "reports" ADD CONSTRAINT "reports_pkey" PRIMARY KEY ("id");
ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_reports_id_report_parameters_reportid_16" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );
-- Generate application table translations for lbDMFManager_Entities
-- Generate application table user_anwendungen for lbDMFManager_Entities
-- Generate application table users for lbDMFManager_Entities

--ALTER TABLE "users" ADD CONSTRAINT "users_pkey" PRIMARY KEY ("id");
ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_users_id_anwendungsberechtigungen_iduser_8" FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "id" );

--ALTER TABLE "users" ADD CONSTRAINT "users_pkey" PRIMARY KEY ("id");
ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_users_id_user_anwendungen_userid_19" FOREIGN KEY ( "userid" ) REFERENCES "users" ( "id" );
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

	end if;


	applicationid = getorcreateapplication(applicationname);
	insert into user_anwendungen (userid, anwendungenid) values (1, applicationid);
	insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBUser'', ''dba'', applicationid);
	insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBPass'', ''trainres'', applicationid);
	if applicationname = ''lbDMF Manager'' then
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBName'', ''lbDMF'', applicationid);
	else
		insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values(''DBName'', ''lbDMF Manager'', applicationid);
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
	actionid = getorcreateactiontype"(typename);
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
		
		-- Class Benutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Benutzer');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', 'kuser.png', getorcreateapplication('lbDMF Manager'), 1);



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "name", "vorname", "userid", "passwort" from "users" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Benutzer'));
insert into column_types (name, tablename, ro) values ('ID', 'Benutzer', true);


-- Association from Benutzer to AnwendungenBenutzer
-- Select action type IsMasterDetail: Prop_Benutzer_1_AnwendungenBenutzer_4, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('AnwendungenBenutzer', 1, 'userid');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for AnwendungenBenutzer', 1, 'AnwendungenBenutzer', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'AnwendungenBenutzer' and source = 'userid'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'AnwendungenBenutzer' and source = 'userid'), 'action_master_detail_Prop_Benutzer_1_AnwendungenBenutzer_4');

	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Benutzer'));


		-- Class Formulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formulare');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', 'kpersonalizer.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'anwendungid', 'anwendungen', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'typ', 'formulartypen', 'beschreibung');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "toolbarimage", "name", "menuname", "eventname", "menuhilfe", "anwendungid", "typ" from "formulare" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formulare'));
insert into column_types (name, tablename, ro) values ('ID', 'Formulare', true);


-- Association from Formulare to Formular_Parameter
-- Select action type IsMasterDetail: Prop_Formulare_2_Formular_Parameter_3, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Formular_Parameter', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formular_Parameter', 1, 'Formular_Parameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formular_Parameter' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formular_Parameter' and source = 'name'), 'action_master_detail_Prop_Formulare_2_Formular_Parameter_3');

	
-- Association from Formulare to Formularaktionenzuordnen
-- Select action type IsMasterDetail: Prop_Formulare_2_Formularaktionenzuordnen_10, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Formularaktionenzuordnen', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formularaktionenzuordnen', 1, 'Formularaktionenzuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formularaktionenzuordnen' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formularaktionenzuordnen' and source = 'name'), 'action_master_detail_Prop_Formulare_2_Formularaktionenzuordnen_10');

	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formulare'));


		-- Class Formular_Parameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formular_Parameter');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', 'formular_params.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_parameters', 'formularid', 'formulare', 'name');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "parametername", "parametervalue", "formularid" from "formular_parameters" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formular_Parameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Formular_Parameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formular_Parameter'));


		-- Class AnwendungenBenutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'AnwendungenBenutzer');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('AnwendungenBenutzer', 'AnwendungenBenutzer verwalten', 'manageAnwendungenBenutzer', 'Edit data of AnwendungenBenutzer', 'User_application.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'userid', 'users', 'userid');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'anwendungenid', 'anwendungen', 'name');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "userid", "anwendungenid" from "user_anwendungen" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenBenutzer'));
insert into column_types (name, tablename, ro) values ('ID', 'AnwendungenBenutzer', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenBenutzer'));


		-- Class FormulareAnwendung of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'FormulareAnwendung');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('FormulareAnwendung', 'FormulareAnwendung verwalten', 'manageFormulareAnwendung', 'Edit data of FormulareAnwendung', 'app_formulare.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'anwendungid', 'anwendungen', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'formularid', 'formulare', 'name');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "anwendungid", "formularid" from "anwendungen_formulare" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'FormulareAnwendung'));
insert into column_types (name, tablename, ro) values ('ID', 'FormulareAnwendung', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'FormulareAnwendung'));


		-- Class Anwendungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Anwendungen');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', 'kthememgr.png', getorcreateapplication('lbDMF Manager'), 1);



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "name", "titel", "modulename", "functor", "interface" from "anwendungen" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungen'));
insert into column_types (name, tablename, ro) values ('ID', 'Anwendungen', true);


-- Association from Anwendungen to Formulare
-- Select action type IsMasterDetail: Prop_Anwendungen_6_Formulare_2, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Formulare', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formulare' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formulare' and source = 'name'), 'action_master_detail_Prop_Anwendungen_6_Formulare_2');

	
-- Association from Anwendungen to Anwendungsparameter
-- Select action type IsMasterDetail: Prop_Anwendungen_6_Anwendungsparameter_11, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Anwendungsparameter', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungsparameter', 1, 'Anwendungsparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Anwendungsparameter' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Anwendungsparameter' and source = 'name'), 'action_master_detail_Prop_Anwendungen_6_Anwendungsparameter_11');

	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungen'));


		-- Class AnwendungenFormulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'AnwendungenFormulare');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('AnwendungenFormulare', 'AnwendungenFormulare verwalten', 'manageAnwendungenFormulare', 'Edit data of AnwendungenFormulare', 'app_formulare.png', getorcreateapplication('lbDMF Manager'), 1);



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select  from "" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenFormulare'));
insert into column_types (name, tablename, ro) values ('ID', 'AnwendungenFormulare', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'AnwendungenFormulare'));


		-- Class Aktionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Aktionen');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', 'cache.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'typ', 'action_types', 'bezeichnung');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "id", "name", "typ", "source", "target" from "actions" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionen'));
insert into column_types (name, tablename, ro) values ('ID', 'Aktionen', true);


-- Association from Aktionen to Aktionsschrittezuordnen
-- Select action type IsMasterDetail: Prop_Aktionen_8_Aktionsschrittezuordnen_12, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Aktionsschrittezuordnen', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Aktionsschrittezuordnen', 1, 'Aktionsschrittezuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'name'), 'action_master_detail_Prop_Aktionen_8_Aktionsschrittezuordnen_12');

	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionen'));


		-- Class Uebersetzungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Uebersetzungen');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', 'babelfish.png', getorcreateapplication('lbDMF Manager'), 1);



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "text", "translated" from "translations" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Uebersetzungen'));
insert into column_types (name, tablename, ro) values ('ID', 'Uebersetzungen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Uebersetzungen'));


		-- Class Formularaktionenzuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Formularaktionenzuordnen');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Formularaktionenzuordnen', 'Formularaktionenzuordnen verwalten', 'manageFormularaktionenzuordnen', 'Edit data of Formularaktionenzuordnen', 'actions_formulare.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'formular', 'formulare', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'action', 'actions', 'name');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "formular", "action", "event" from "formular_actions" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Formularaktionenzuordnen'));
insert into column_types (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Formularaktionenzuordnen'));


		-- Class Anwendungsparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Anwendungsparameter');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', 'app_params.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungs_parameter', 'anwendungid', 'anwendungen', 'name');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "parametername", "parametervalue", "anwendungid" from "anwendungs_parameter" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungsparameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Anwendungsparameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Anwendungsparameter'));


		-- Class Aktionsschrittezuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Aktionsschrittezuordnen');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', 'action_steps.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'actionid', 'actions', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'type', 'action_types', 'bezeichnung');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "id", "actionid", "bezeichnung", "a_order_nr", "type", "what" from "action_steps" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionsschrittezuordnen'));
insert into column_types (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Aktionsschrittezuordnen'));


		-- Class Reportdefinitionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Reportdefinitionen');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', 'print_class.png', getorcreateapplication('lbDMF Manager'), 1);



insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "name", "description" from "reports" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Reportdefinitionen'));
insert into column_types (name, tablename, ro) values ('ID', 'Reportdefinitionen', true);


-- Association from Reportdefinitionen to Reportparameter
-- Select action type IsMasterDetail: Prop_Reportdefinitionen_13_Reportparameter_14, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Reportparameter', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Reportparameter', 1, 'Reportparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Reportparameter' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Reportparameter' and source = 'name'), 'action_master_detail_Prop_Reportdefinitionen_13_Reportparameter_14');

	
-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Reportdefinitionen'));


		-- Class Reportparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
select dropformular('lbDMF Manager', 'Reportparameter');

insert into formulare (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ)
	values ('Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', 'kword.png', getorcreateapplication('lbDMF Manager'), 1);


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_parameters', 'reportid', 'reports', 'name');


insert into formular_parameters (parametername, parametervalue, formularid) values('query', 'select "reportid", "name", "value" from "report_parameters" order by id', getformularid(getorcreateapplication('lbDMF Manager'), 'Reportparameter'));
insert into column_types (name, tablename, ro) values ('ID', 'Reportparameter', true);


-- Create operation definitions

insert into anwendungen_formulare (anwendungid, formularid) values(getorcreateapplication('lbDMF Manager'), getformularid(getorcreateapplication('lbDMF Manager'), 'Reportparameter'));


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
				
		-- Class lbDMF_ForeignKeys of type ENTITY found.
				
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
