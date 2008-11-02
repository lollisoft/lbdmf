
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

-- Generate application table action_steps for lbDMFManager_Entities
-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities
ALTER TABLE "action_steps" DROP CONSTRAINT "cst_action_types_id_action_steps_type_1";
ALTER TABLE "actions" DROP CONSTRAINT "cst_action_types_id_actions_typ_3";
-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities
ALTER TABLE "action_steps" DROP CONSTRAINT "cst_actions_id_action_steps_actionid_2";
ALTER TABLE "formular_actions" DROP CONSTRAINT "cst_actions_id_formular_actions_action_9";
-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities
ALTER TABLE "anwendungen_formulare" DROP CONSTRAINT "cst_anwendungen_id_anwendungen_formulare_anwendungid_4";
ALTER TABLE "anwendungs_parameter" DROP CONSTRAINT "cst_anwendungen_id_anwendungs_parameter_anwendungid_6";
ALTER TABLE "formulare" DROP CONSTRAINT "cst_anwendungen_id_formulare_anwendungid_12";
ALTER TABLE "user_anwendungen" DROP CONSTRAINT "cst_anwendungen_id_user_anwendungen_anwendungenid_18";
ALTER TABLE "users" DROP CONSTRAINT "cst_anwendungen_id_users_lastapp_20";
-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities
-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities
-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities
-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities
-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities
-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities
-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities
-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities
-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities
ALTER TABLE "anwendungen_formulare" DROP CONSTRAINT "cst_formulare_id_anwendungen_formulare_formularid_5";
ALTER TABLE "anwendungsberechtigungen" DROP CONSTRAINT "cst_formulare_id_anwendungsberechtigungen_idformular_7";
ALTER TABLE "formular_actions" DROP CONSTRAINT "cst_formulare_id_formular_actions_formular_10";
ALTER TABLE "formular_parameters" DROP CONSTRAINT "cst_formulare_id_formular_parameters_formularid_11";
-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities
ALTER TABLE "formulare" DROP CONSTRAINT "cst_formulartypen_id_formulare_typ_13";
-- Class lbDMF_ForeignKeys of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table lbDMF_ForeignKeys for lbDMFManager_Entities
-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities
-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities
ALTER TABLE "report_elements" DROP CONSTRAINT "cst_report_element_types_id_report_elements_typ_14";
-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities
ALTER TABLE "report_texts" DROP CONSTRAINT "cst_report_elements_id_report_texts_elementid_17";
-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities
-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities
-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities
ALTER TABLE "report_elements" DROP CONSTRAINT "cst_reports_id_report_elements_reportid_15";
ALTER TABLE "report_parameters" DROP CONSTRAINT "cst_reports_id_report_parameters_reportid_16";
-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities
-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities
-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities
ALTER TABLE "anwendungsberechtigungen" DROP CONSTRAINT "cst_users_id_anwendungsberechtigungen_iduser_8";
ALTER TABLE "user_anwendungen" DROP CONSTRAINT "cst_users_id_user_anwendungen_userid_19";
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

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE action_steps
exec dropTable 'action_steps';

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE action_types
exec dropTable 'action_types';

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE actions
exec dropTable 'actions';

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungen
exec dropTable 'anwendungen';

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungen_formulare
exec dropTable 'anwendungen_formulare';

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungs_parameter
exec dropTable 'anwendungs_parameter';

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungsberechtigungen
exec dropTable 'anwendungsberechtigungen';

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE applevel_plugin_registry
exec dropTable 'applevel_plugin_registry';

-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE codegentarget
exec dropTable 'codegentarget';

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE column_types
exec dropTable 'column_types';

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE foreignkey_visibledata_mapping
exec dropTable 'foreignkey_visibledata_mapping';

-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formular_actions
exec dropTable 'formular_actions';

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formular_parameters
exec dropTable 'formular_parameters';

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formulare
exec dropTable 'formulare';

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formulartypen
exec dropTable 'formulartypen';

-- Class lbDMF_ForeignKeys of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table lbDMF_ForeignKeys for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE lbDMF_ForeignKeys
exec dropTable 'lbDMF_ForeignKeys';

-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE regressiontest
exec dropTable 'regressiontest';

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_element_types
exec dropTable 'report_element_types';

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_elements
exec dropTable 'report_elements';

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_parameters
exec dropTable 'report_parameters';

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_texts
exec dropTable 'report_texts';

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE reports
exec dropTable 'reports';

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE translations
exec dropTable 'translations';

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE user_anwendungen
exec dropTable 'user_anwendungen';

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE users
exec dropTable 'users';

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

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE action_steps
CREATE TABLE "action_steps" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"actionid" INTEGER,
	"bezeichnung" char(255),
	"a_order_nr" INTEGER,
--,
	"type" INTEGER,
	"what" char(255)
);

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE action_types
CREATE TABLE "action_types" (
	
--,
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"bezeichnung" char(255),
	"action_handler" char(255),
	"module" char(255)
);

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE actions
CREATE TABLE "actions" (
	
--,
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
--,
	"typ" INTEGER,
	"source" char(255),
	"target" INTEGER
);

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE anwendungen
CREATE TABLE "anwendungen" (
	
--,
--,
--,
--,
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"titel" char(255),
	"modulename" char(255),
	"functor" char(255),
	"interface" char(255)
);

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE anwendungen_formulare
CREATE TABLE "anwendungen_formulare" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"anwendungid" INTEGER,
--,
	"formularid" INTEGER
);

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE anwendungs_parameter
CREATE TABLE "anwendungs_parameter" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"parametername" char(255),
	"parametervalue" char(255),
--,
	"anwendungid" INTEGER
);

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE anwendungsberechtigungen
CREATE TABLE "anwendungsberechtigungen" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"iduser" INTEGER,
--,
	"idformular" INTEGER
);

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE applevel_plugin_registry
CREATE TABLE "applevel_plugin_registry" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"anwendungid" INTEGER
);

-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE codegentarget
CREATE TABLE "codegentarget" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"titel" char(255),
	"modulename" char(255),
	"functor" char(255),
	"interface" char(255)
);

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE column_types
CREATE TABLE "column_types" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"tablename" char(255),
	"ro" BIT,
	"specialcolumn" BIT,
	"controltype" char(255)
);

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE foreignkey_visibledata_mapping
CREATE TABLE "foreignkey_visibledata_mapping" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"fkname" char(255),
	"fktable" char(255),
	"pkname" char(255),
	"pktable" char(255)
);

-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE formular_actions
CREATE TABLE "formular_actions" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"formular" INTEGER,
--,
	"action" INTEGER,
	"event" char(255)
);

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE formular_parameters
CREATE TABLE "formular_parameters" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"parametername" char(255),
	"parametervalue" char(255),
--,
	"formularid" INTEGER
);

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE formulare
CREATE TABLE "formulare" (
	
--,
--,
--,
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"menuname" char(255),
	"menuorder" INTEGER,
	"eventname" char(255),
	"menuhilfe" char(255),
	"toolbarimage" char(255),
--,
	"anwendungid" INTEGER,
--,
	"typ" INTEGER
);

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE formulartypen
CREATE TABLE "formulartypen" (
	
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"handlermodule" char(255),
	"handlerfunctor" char(255),
	"handlerinterface" char(255),
	"namespace" char(255),
	"beschreibung" char(255)
);

-- Class lbDMF_ForeignKeys of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table lbDMF_ForeignKeys for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE lbDMF_ForeignKeys
CREATE TABLE "lbDMF_ForeignKeys" (
	
	"PKTable" char(255),
	"PKColumn" char(255),
	"FKTable" char(255),
	"FKColumn" char(255)
);

-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE regressiontest
CREATE TABLE "regressiontest" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"test" char(255),
	"btest" BIT,
	"btest1" BIT
);

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE report_element_types
CREATE TABLE "report_element_types" (
	
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"description" char(255)
);

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE report_elements
CREATE TABLE "report_elements" (
	
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"reportid" INTEGER,
--,
	"typ" INTEGER,
	"name" char(255),
	"x" INTEGER,
	"y" INTEGER,
	"w" INTEGER,
	"h" INTEGER,
	"description" char(255)
);

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE report_parameters
CREATE TABLE "report_parameters" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"reportid" INTEGER,
	"name" char(255),
	"value" INTEGER
);

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE report_texts
CREATE TABLE "report_texts" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"elementid" INTEGER,
	"line" INTEGER,
	"text" char(255)
);

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE reports
CREATE TABLE "reports" (
	
--,
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"description" char(255)
);

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE translations
CREATE TABLE "translations" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"text" char(255),
	"translated" char(255),
	"language" char(255)
);

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE user_anwendungen
CREATE TABLE "user_anwendungen" (
	
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
--,
	"userid" INTEGER,
--,
	"anwendungenid" INTEGER
);

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- CREATE TABLE users
CREATE TABLE "users" (
	
--,
--,
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"vorname" char(255),
	"userid" char(255),
	"passwort" char(255),
--,
	"lastapp" INTEGER
);

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

-- Generate application tables action_steps for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "action_steps" ADD CONSTRAINT "action_steps_pkey" PRIMARY KEY ("id");
		
-- Class action_types of type ENTITY found.

-- Generate application tables action_types for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "action_types" ADD CONSTRAINT "action_types_pkey" PRIMARY KEY ("id");
		
-- Class actions of type ENTITY found.

-- Generate application tables actions for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "actions" ADD CONSTRAINT "actions_pkey" PRIMARY KEY ("id");
		
-- Class anwendungen of type ENTITY found.

-- Generate application tables anwendungen for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "anwendungen" ADD CONSTRAINT "anwendungen_pkey" PRIMARY KEY ("id");
		
-- Class anwendungen_formulare of type ENTITY found.

-- Generate application tables anwendungen_formulare for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "anwendungen_formulare_pkey" PRIMARY KEY ("id");
		
-- Class anwendungs_parameter of type ENTITY found.

-- Generate application tables anwendungs_parameter for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "anwendungs_parameter_pkey" PRIMARY KEY ("id");
		
-- Class anwendungsberechtigungen of type ENTITY found.

-- Generate application tables anwendungsberechtigungen for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "anwendungsberechtigungen_pkey" PRIMARY KEY ("id");
		
-- Class applevel_plugin_registry of type ENTITY found.

-- Generate application tables applevel_plugin_registry for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "applevel_plugin_registry" ADD CONSTRAINT "applevel_plugin_registry_pkey" PRIMARY KEY ("id");
		
-- Class codegentarget of type ENTITY found.

-- Generate application tables codegentarget for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "codegentarget" ADD CONSTRAINT "codegentarget_pkey" PRIMARY KEY ("id");
		
-- Class column_types of type ENTITY found.

-- Generate application tables column_types for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "column_types" ADD CONSTRAINT "column_types_pkey" PRIMARY KEY ("id");
		
-- Class foreignkey_visibledata_mapping of type ENTITY found.

-- Generate application tables foreignkey_visibledata_mapping for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "foreignkey_visibledata_mapping" ADD CONSTRAINT "foreignkey_visibledata_mapping_pkey" PRIMARY KEY ("id");
		
-- Class formular_actions of type ENTITY found.

-- Generate application tables formular_actions for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "formular_actions" ADD CONSTRAINT "formular_actions_pkey" PRIMARY KEY ("id");
		
-- Class formular_parameters of type ENTITY found.

-- Generate application tables formular_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "formular_parameters" ADD CONSTRAINT "formular_parameters_pkey" PRIMARY KEY ("id");
		
-- Class formulare of type ENTITY found.

-- Generate application tables formulare for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "formulare" ADD CONSTRAINT "formulare_pkey" PRIMARY KEY ("id");
		
-- Class formulartypen of type ENTITY found.

-- Generate application tables formulartypen for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "formulartypen" ADD CONSTRAINT "formulartypen_pkey" PRIMARY KEY ("id");
		
-- Class lbDMF_ForeignKeys of type ENTITY found.

-- Generate application tables lbDMF_ForeignKeys for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


-- Class regressiontest of type ENTITY found.

-- Generate application tables regressiontest for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "regressiontest" ADD CONSTRAINT "regressiontest_pkey" PRIMARY KEY ("id");
		
-- Class report_element_types of type ENTITY found.

-- Generate application tables report_element_types for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "report_element_types" ADD CONSTRAINT "report_element_types_pkey" PRIMARY KEY ("id");
		
-- Class report_elements of type ENTITY found.

-- Generate application tables report_elements for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "report_elements" ADD CONSTRAINT "report_elements_pkey" PRIMARY KEY ("id");
		
-- Class report_parameters of type ENTITY found.

-- Generate application tables report_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "report_parameters" ADD CONSTRAINT "report_parameters_pkey" PRIMARY KEY ("id");
		
-- Class report_texts of type ENTITY found.

-- Generate application tables report_texts for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "report_texts" ADD CONSTRAINT "report_texts_pkey" PRIMARY KEY ("id");
		
-- Class reports of type ENTITY found.

-- Generate application tables reports for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "reports" ADD CONSTRAINT "reports_pkey" PRIMARY KEY ("id");
		
-- Class translations of type ENTITY found.

-- Generate application tables translations for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "translations" ADD CONSTRAINT "translations_pkey" PRIMARY KEY ("id");
		
-- Class user_anwendungen of type ENTITY found.

-- Generate application tables user_anwendungen for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "user_anwendungen" ADD CONSTRAINT "user_anwendungen_pkey" PRIMARY KEY ("id");
		
-- Class users of type ENTITY found.

-- Generate application tables users for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "users" ADD CONSTRAINT "users_pkey" PRIMARY KEY ("id");
		
-- Generate application table action_steps for lbDMFManager_Entities
-- Generate application table action_types for lbDMFManager_Entities
ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_types_id_action_steps_type_1" FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "id" );
ALTER TABLE "actions" ADD CONSTRAINT "cst_action_types_id_actions_typ_3" FOREIGN KEY ( "typ" ) REFERENCES "action_types" ( "id" );
-- Generate application table actions for lbDMFManager_Entities
ALTER TABLE "action_steps" ADD CONSTRAINT "cst_actions_id_action_steps_actionid_2" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );
ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_actions_id_formular_actions_action_9" FOREIGN KEY ( "action" ) REFERENCES "actions" ( "id" );
-- Generate application table anwendungen for lbDMFManager_Entities
ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_id_anwendungen_formulare_anwendungid_4" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "cst_anwendungen_id_anwendungs_parameter_anwendungid_6" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
ALTER TABLE "formulare" ADD CONSTRAINT "cst_anwendungen_id_formulare_anwendungid_12" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_anwendungen_id_user_anwendungen_anwendungenid_18" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );
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
ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_formulare_id_anwendungen_formulare_formularid_5" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_formulare_id_anwendungsberechtigungen_idformular_7" FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "id" );
ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formulare_id_formular_actions_formular_10" FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "id" );
ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formulare_id_formular_parameters_formularid_11" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
-- Generate application table formulartypen for lbDMFManager_Entities
ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulartypen_id_formulare_typ_13" FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "id" );
-- Generate application table lbDMF_ForeignKeys for lbDMFManager_Entities
-- Generate application table regressiontest for lbDMFManager_Entities
-- Generate application table report_element_types for lbDMFManager_Entities
ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_element_types_id_report_elements_typ_14" FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "id" );
-- Generate application table report_elements for lbDMFManager_Entities
ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_elements_id_report_texts_elementid_17" FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "id" );
-- Generate application table report_parameters for lbDMFManager_Entities
-- Generate application table report_texts for lbDMFManager_Entities
-- Generate application table reports for lbDMFManager_Entities
ALTER TABLE "report_elements" ADD CONSTRAINT "cst_reports_id_report_elements_reportid_15" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );
ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_reports_id_report_parameters_reportid_16" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );
-- Generate application table translations for lbDMFManager_Entities
-- Generate application table user_anwendungen for lbDMFManager_Entities
-- Generate application table users for lbDMFManager_Entities
ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_users_id_anwendungsberechtigungen_iduser_8" FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "id" );
ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_users_id_user_anwendungen_userid_19" FOREIGN KEY ( "userid" ) REFERENCES "users" ( "id" );
-- Create default stored procedures for MSSQL. Version ignored.


create  PROCEDURE DropProc @Proc VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP ' + case pr.xtype when 
			'P' then 'PROCEDURE ' else 'FUNCTION ' end + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('P','FN','TF') AND upper(pr.name) = upper(@Proc)
		
	OPEN hSqlProc
	FETCH hSqlProc INTO @Statement
	WHILE (@@fetch_status = 0)
		BEGIN
			EXECUTE (@Statement)
			FETCH hSqlProc INTO @Statement
		END
	CLOSE hSqlProc
	
	DEALLOCATE hSqlProc
END


exec DropProc 'getorcreateapplication';


create  FUNCTION getorcreateapplication(@FNName varchar)
  RETURNS int AS
'
declare @applicationid int;
declare @uid int;
declare @applicationname char(100);

BEGIN
  @applicationname = @FNName;
  select id into @applicationid from anwendungen where name = @applicationname;
  if not @applicationid is null then
    return @applicationid;
  end if;
  if @applicationid is null then
	insert into anwendungen (name, titel, modulename, functor, interface) values(applicationname, ''Application '' || applicationname, ''lbDynApp'', ''instanceOfApplication'', ''lb_I_Application'');

	select id into @uid from users where userid = ''user'';
	if @uid is null then
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


	applicationid = getorcreateapplication(@applicationname);
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
exec "DropFormular"('lbDMF Manager', 'Benutzer');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for users (Benutzer_1)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "vorname", "userid", "passwort" from "users"', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Benutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Benutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Benutzer', 1);


-- Association from Benutzer to AnwendungenBenutzer
-- Select action type IsMasterDetail: Prop_Benutzer_1_AnwendungenBenutzer_4, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('AnwendungenBenutzer', 1, 'userid');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for AnwendungenBenutzer', 1, 'AnwendungenBenutzer', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'AnwendungenBenutzer' and source = 'userid'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'AnwendungenBenutzer' and source = 'userid'), 'action_master_detail_Prop_Benutzer_1_AnwendungenBenutzer_4');

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Formulare');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'anwendungid', 'anwendungen', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'typ', 'formulartypen', 'beschreibung');


-- Create query for formulare (Formulare_2)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "toolbarimage", "name", "menuname", "eventname", "menuhilfe", "anwendungid", "typ" from "formulare"', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Formulare', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Formulare', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Formulare', 1);


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

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formular_Parameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Formular_Parameter');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_parameters', 'formularid', 'formulare', 'name');


-- Create query for formular_parameters (Formular_Parameter_3)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "formularid" from "formular_parameters"', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Formular_Parameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Formular_Parameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Formular_Parameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formular_Parameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class AnwendungenBenutzer of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'AnwendungenBenutzer');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'AnwendungenBenutzer', 'AnwendungenBenutzer verwalten', 'manageAnwendungenBenutzer', 'Edit data of AnwendungenBenutzer', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'userid', 'users', 'userid');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'anwendungenid', 'anwendungen', 'name');


-- Create query for user_anwendungen (AnwendungenBenutzer_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "userid", "anwendungenid" from "user_anwendungen"', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'AnwendungenBenutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'AnwendungenBenutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'AnwendungenBenutzer', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'AnwendungenBenutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class FormulareAnwendung of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'FormulareAnwendung');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormulareAnwendung', 'FormulareAnwendung verwalten', 'manageFormulareAnwendung', 'Edit data of FormulareAnwendung', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'anwendungid', 'anwendungen', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'formularid', 'formulare', 'name');


-- Create query for anwendungen_formulare (FormulareAnwendung_5)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungid", "formularid" from "anwendungen_formulare"', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'FormulareAnwendung', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'FormulareAnwendung', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'FormulareAnwendung', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Anwendungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Anwendungen');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for anwendungen (Anwendungen_6)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "titel", "modulename", "functor", "interface" from "anwendungen"', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungen', 1);


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

-- Generate codegeneration operation 'Codegenerieren' for 'Anwendungen'

INSERT INTO "actions" (name, typ, source) VALUES ('Codegenerieren', 1, 'name');
INSERT INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, 'lala', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Codegenerieren'));
INSERT INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = 'Anwendungen'), (select id from actions where name = 'Codegenerieren'), 'evt_Anwendungen_Codegenerieren');

	
INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class AnwendungenFormulare of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'AnwendungenFormulare');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'AnwendungenFormulare', 'AnwendungenFormulare verwalten', 'manageAnwendungenFormulare', 'Edit data of AnwendungenFormulare', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for  (AnwendungenFormulare_7)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select  from ""', id FROM "formulare" WHERE name = 'AnwendungenFormulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'AnwendungenFormulare', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'AnwendungenFormulare', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'AnwendungenFormulare', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'AnwendungenFormulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Aktionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Aktionen');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'typ', 'action_types', 'bezeichnung');


-- Create query for actions (Aktionen_8)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "id", "name", "typ", "source", "target" from "actions"', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Aktionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionen', 1);


-- Association from Aktionen to Aktionsschrittezuordnen
-- Select action type IsMasterDetail: Prop_Aktionen_8_Aktionsschrittezuordnen_12, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Aktionsschrittezuordnen', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Aktionsschrittezuordnen', 1, 'Aktionsschrittezuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'name'), 'action_master_detail_Prop_Aktionen_8_Aktionsschrittezuordnen_12');

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Uebersetzungen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Uebersetzungen');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for translations (Uebersetzungen_9)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "text", "translated" from "translations"', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Uebersetzungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Uebersetzungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Uebersetzungen', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Uebersetzungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formularaktionenzuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Formularaktionenzuordnen');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formularaktionenzuordnen', 'Formularaktionenzuordnen verwalten', 'manageFormularaktionenzuordnen', 'Edit data of Formularaktionenzuordnen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'formular', 'formulare', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'action', 'actions', 'name');


-- Create query for formular_actions (Formularaktionenzuordnen_10)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "formular", "action", "event" from "formular_actions"', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Formularaktionenzuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Formularaktionenzuordnen', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formularaktionenzuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Anwendungsparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Anwendungsparameter');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungs_parameter', 'anwendungid', 'anwendungen', 'name');


-- Create query for anwendungs_parameter (Anwendungsparameter_11)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "anwendungid" from "anwendungs_parameter"', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungsparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungsparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungsparameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungsparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Aktionsschrittezuordnen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Aktionsschrittezuordnen');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'actionid', 'actions', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'type', 'action_types', 'bezeichnung');


-- Create query for action_steps (Aktionsschrittezuordnen_12)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "id", "actionid", "bezeichnung", "a_order_nr", "type", "what" from "action_steps"', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Aktionsschrittezuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionsschrittezuordnen', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionsschrittezuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Reportdefinitionen of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Reportdefinitionen');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';



-- Create query for reports (Reportdefinitionen_13)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "description" from "reports"', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Reportdefinitionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Reportdefinitionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Reportdefinitionen', 1);


-- Association from Reportdefinitionen to Reportparameter
-- Select action type IsMasterDetail: Prop_Reportdefinitionen_13_Reportparameter_14, IsDetailMaster: 
-- Build up a master detail action

insert into actions (name, typ, source) values ('Reportparameter', 1, 'name');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Reportparameter', 1, 'Reportparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Reportparameter' and source = 'name'));
insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Reportparameter' and source = 'name'), 'action_master_detail_Prop_Reportdefinitionen_13_Reportparameter_14');

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Reportparameter of type FORM found.
					
-- Generate DMF form definition for lbDMF Manager
exec "DropFormular"('lbDMF Manager', 'Reportparameter');


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_parameters', 'reportid', 'reports', 'name');


-- Create query for report_parameters (Reportparameter_14)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "reportid", "name", "value" from "report_parameters"', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Reportparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Reportparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Reportparameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

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
