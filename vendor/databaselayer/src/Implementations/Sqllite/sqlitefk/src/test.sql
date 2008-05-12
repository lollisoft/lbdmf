
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
				
-- Class Activities of type FORM found.
				
-- Class ActivityNodes of type FORM found.
				
-- Class ControlFlow of type FORM found.
				
-- Class DecisionPath of type FORM found.
				
-- Class Project of type FORM found.
				
-- Class Todo of type FORM found.
				
-- Class Activities of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Activities for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE Activities
CREATE TABLE "Activities" (
	
--,
--,
--,
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
	"UmlId" BPCHAR
);

-- Class ActivityNodes of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ActivityNodes for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE ActivityNodes
CREATE TABLE "ActivityNodes" (
	
--,
--,
--,
--,
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
	"Stereotype" BPCHAR,
	"UmlId" BPCHAR,
	"NodeType" BPCHAR,
	"Body" BPCHAR,
--,
	"Activities" INTEGER
);

-- Class ControlFlow of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table ControlFlow for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE ControlFlow
CREATE TABLE "ControlFlow" (
	
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
	"Expression" BPCHAR,
	"UmlId" BPCHAR,
	"Stereotype" BPCHAR,
--,
	"Activities" INTEGER,
--,
	"ActivityNodesSource1" INTEGER,
--,
	"ActivityNodesTarget1" INTEGER
);

-- Class DecisionPath of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table DecisionPath for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE DecisionPath
CREATE TABLE "DecisionPath" (
	
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
	"UmlId" BPCHAR,
	"Stereotype" BPCHAR,
--,
	"Activities" INTEGER,
--,
	"ActivityNodesSource2" INTEGER,
--,
	"ActivityNodesTarget2" INTEGER
);

-- Class PluginModules of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table PluginModules for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE PluginModules
CREATE TABLE "PluginModules" (
	
--,
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
	"Modulname" BPCHAR,
--,
	"Vendor" INTEGER
);

-- Class Plugins of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Plugins for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE Plugins
CREATE TABLE "Plugins" (
	
	"ID" INTEGER PRIMARY KEY,
	"Functor" BPCHAR,
	"Namespace" BPCHAR,
	"PrimaryInterface" BPCHAR,
--,
	"PluginModules" INTEGER
);

-- Class Project of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Project for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE Project
CREATE TABLE "Project" (
	
--,
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR
);

-- Class Template of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Template for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE Template
CREATE TABLE "Template" (
	
--,
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
--,
	"Templates" INTEGER
);

-- Class TemplateParameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table TemplateParameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE TemplateParameters
CREATE TABLE "TemplateParameters" (
	
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
--,
	"Template" INTEGER
);

-- Class Templates of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Templates for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE Templates
CREATE TABLE "Templates" (
	
--,
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
	"Purpose" BPCHAR
);

-- Class Todo of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Todo for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE Todo
CREATE TABLE "Todo" (
	
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR,
--,
	"Project" INTEGER
);

-- Class Vendor of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table Vendor for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE Vendor
CREATE TABLE "Vendor" (
	
--,
	"ID" INTEGER PRIMARY KEY,
	"Name" BPCHAR
);

-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE action_steps
CREATE TABLE "action_steps" (
	
	"id" INTEGER PRIMARY KEY,
--,
	"actionid" INTEGER,
	"bezeichnung" BPCHAR,
	"a_order_nr" INTEGER,
--,
	"type" INTEGER
);

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE action_types
CREATE TABLE "action_types" (
	
--,
--,
	"id" INTEGER PRIMARY KEY,
	"bezeichnung" BPCHAR,
	"action_handler" BPCHAR,
	"module" BPCHAR
);

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE actions
CREATE TABLE "actions" (
	
--,
--,
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
--,
	"typ" INTEGER,
	"source" BPCHAR,
	"target" INTEGER
);

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE anwendungen
CREATE TABLE "anwendungen" (
	
--,
--,
--,
--,
--,
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"titel" BPCHAR,
	"modulename" BPCHAR,
	"functor" BPCHAR,
	"interface" BPCHAR
);

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE anwendungen_formulare
CREATE TABLE "anwendungen_formulare" (
	
	"id" INTEGER PRIMARY KEY,
--,
	"anwendungid" INTEGER,
--,
	"formularid" INTEGER
);

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE anwendungs_parameter
CREATE TABLE "anwendungs_parameter" (
	
	"id" INTEGER PRIMARY KEY,
	"parametername" BPCHAR,
	"parametervalue" BPCHAR,
--,
	"anwendungid" INTEGER
);

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE anwendungsberechtigungen
CREATE TABLE "anwendungsberechtigungen" (
	
	"id" INTEGER PRIMARY KEY,
--,
	"iduser" INTEGER,
--,
	"idformular" INTEGER
);

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE applevel_plugin_registry
CREATE TABLE "applevel_plugin_registry" (
	
	"id" INTEGER PRIMARY KEY,
	"anwendungid" INTEGER
);

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE column_types
CREATE TABLE "column_types" (
	
	"id" INTEGER,
	"name" BPCHAR,
	"tablename" BPCHAR,
	"ro" BOOLEAN,
	"specialcolumn" BOOLEAN,
	"controltype" BPCHAR
);

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE foreignkey_visibledata_mapping
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


-- CREATE TABLE formular_actions
CREATE TABLE "formular_actions" (
	
	"id" INTEGER PRIMARY KEY,
--,
	"formular" INTEGER,
--,
	"action" INTEGER,
	"event" BPCHAR
);

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE formular_parameters
CREATE TABLE "formular_parameters" (
	
	"id" INTEGER PRIMARY KEY,
	"parametername" BPCHAR,
	"parametervalue" BPCHAR,
--,
	"formularid" INTEGER
);

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE formulare
CREATE TABLE "formulare" (
	
--,
--,
--,
--,
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"menuname" BPCHAR,
	"menuorder" INTEGER,
	"eventname" BPCHAR,
	"menuhilfe" BPCHAR,
	"toolbarimage" BPCHAR,
--,
	"anwendungid" INTEGER,
--,
	"typ" INTEGER
);

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE formulartypen
CREATE TABLE "formulartypen" (
	
--,
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


-- CREATE TABLE regressiontest
CREATE TABLE "regressiontest" (
	
	"id" INTEGER PRIMARY KEY,
	"test" BPCHAR,
	"btest" BOOLEAN,
	"btest1" BOOLEAN
);

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE report_element_types
CREATE TABLE "report_element_types" (
	
--,
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"description" BPCHAR
);

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE report_elements
CREATE TABLE "report_elements" (
	
--,
	"id" INTEGER PRIMARY KEY,
--,
	"reportid" INTEGER,
--,
	"typ" INTEGER,
	"name" BPCHAR,
	"x" INTEGER,
	"y" INTEGER,
	"w" INTEGER,
	"h" INTEGER,
	"description" BPCHAR
);

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE report_parameters
CREATE TABLE "report_parameters" (
	
	"id" INTEGER PRIMARY KEY,
--,
	"reportid" INTEGER,
	"name" BPCHAR,
	"value" INTEGER
);

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE report_texts
CREATE TABLE "report_texts" (
	
	"id" INTEGER PRIMARY KEY,
--,
	"elementid" INTEGER,
	"line" INTEGER,
	"text" BPCHAR
);

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE reports
CREATE TABLE "reports" (
	
--,
--,
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"description" BPCHAR
);

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE translations
CREATE TABLE "translations" (
	
	"id" INTEGER PRIMARY KEY,
	"text" BPCHAR,
	"translated" BPCHAR,
	"language" BPCHAR
);

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE user_anwendungen
CREATE TABLE "user_anwendungen" (
	
	"id" INTEGER PRIMARY KEY,
--,
	"userid" INTEGER,
--,
	"anwendungenid" INTEGER
);

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'Sqlite'


-- CREATE TABLE users
CREATE TABLE "users" (
	
--,
--,
	"id" INTEGER PRIMARY KEY,
	"name" BPCHAR,
	"vorname" BPCHAR,
	"userid" BPCHAR,
	"passwort" BPCHAR,
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
				
-- Class Activities of type FORM found.
				
-- Class ActivityNodes of type FORM found.
				
-- Class ControlFlow of type FORM found.
				
-- Class DecisionPath of type FORM found.
				
-- Class Project of type FORM found.
				
-- Class Todo of type FORM found.
				
-- Class Activities of type ENTITY found.

-- Generate application tables Activities for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ActivityNodes of type ENTITY found.

-- Generate application tables ActivityNodes for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class ControlFlow of type ENTITY found.

-- Generate application tables ControlFlow for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class DecisionPath of type ENTITY found.

-- Generate application tables DecisionPath for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class PluginModules of type ENTITY found.

-- Generate application tables PluginModules for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class Plugins of type ENTITY found.

-- Generate application tables Plugins for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class Project of type ENTITY found.

-- Generate application tables Project for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class Template of type ENTITY found.

-- Generate application tables Template for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class TemplateParameters of type ENTITY found.

-- Generate application tables TemplateParameters for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class Templates of type ENTITY found.

-- Generate application tables Templates for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class Todo of type ENTITY found.

-- Generate application tables Todo for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


-- Skipped, due to creation in template 'importApplicationTable'

-- Class Vendor of type ENTITY found.

-- Generate application tables Vendor for lbDMFManager_Entities primary keys. Tagtet database: 'Sqlite'


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

-- Generate application table Activities for lbDMFManager_Entities
ALTER TABLE "DecisionPath" ADD CONSTRAINT "cst_Activities_ID_DecisionPath_Activities_19" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );
ALTER TABLE "ControlFlow" ADD CONSTRAINT "cst_Activities_ID_ControlFlow_Activities_20" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );
ALTER TABLE "ActivityNodes" ADD CONSTRAINT "cst_Activities_ID_ActivityNodes_Activities_21" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );
-- Generate application table ActivityNodes for lbDMFManager_Entities
ALTER TABLE "DecisionPath" ADD CONSTRAINT "cst_ActivityNodes_ID_DecisionPath_ActivityNodesSource2_29" FOREIGN KEY ( "ActivityNodesSource2" ) REFERENCES "ActivityNodes" ( "ID" );
ALTER TABLE "ControlFlow" ADD CONSTRAINT "cst_ActivityNodes_ID_ControlFlow_ActivityNodesSource1_30" FOREIGN KEY ( "ActivityNodesSource1" ) REFERENCES "ActivityNodes" ( "ID" );
ALTER TABLE "DecisionPath" ADD CONSTRAINT "cst_ActivityNodes_ID_DecisionPath_ActivityNodesTarget2_31" FOREIGN KEY ( "ActivityNodesTarget2" ) REFERENCES "ActivityNodes" ( "ID" );
ALTER TABLE "ControlFlow" ADD CONSTRAINT "cst_ActivityNodes_ID_ControlFlow_ActivityNodesTarget1_32" FOREIGN KEY ( "ActivityNodesTarget1" ) REFERENCES "ActivityNodes" ( "ID" );
-- Generate application table ControlFlow for lbDMFManager_Entities
-- Generate application table DecisionPath for lbDMFManager_Entities
-- Generate application table PluginModules for lbDMFManager_Entities
ALTER TABLE "Plugins" ADD CONSTRAINT "cst_PluginModules_ID_Plugins_PluginModules_17" FOREIGN KEY ( "PluginModules" ) REFERENCES "PluginModules" ( "ID" );
-- Generate application table Plugins for lbDMFManager_Entities
-- Generate application table Project for lbDMFManager_Entities
ALTER TABLE "Todo" ADD CONSTRAINT "cst_Project_ID_Todo_Project_14" FOREIGN KEY ( "Project" ) REFERENCES "Project" ( "ID" );
-- Generate application table Template for lbDMFManager_Entities
ALTER TABLE "TemplateParameters" ADD CONSTRAINT "cst_Template_ID_TemplateParameters_Template_15" FOREIGN KEY ( "Template" ) REFERENCES "Template" ( "ID" );
-- Generate application table TemplateParameters for lbDMFManager_Entities
-- Generate application table Templates for lbDMFManager_Entities
ALTER TABLE "Template" ADD CONSTRAINT "cst_Templates_ID_Template_Templates_16" FOREIGN KEY ( "Templates" ) REFERENCES "Templates" ( "ID" );
-- Generate application table Todo for lbDMFManager_Entities
-- Generate application table Vendor for lbDMFManager_Entities
ALTER TABLE "PluginModules" ADD CONSTRAINT "cst_Vendor_ID_PluginModules_Vendor_18" FOREIGN KEY ( "Vendor" ) REFERENCES "Vendor" ( "ID" );
-- Generate application table action_steps for lbDMFManager_Entities
-- Generate application table action_types for lbDMFManager_Entities
ALTER TABLE "actions" ADD CONSTRAINT "cst_action_types_id_actions_typ_12" FOREIGN KEY ( "typ" ) REFERENCES "action_types" ( "id" );
ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_types_id_action_steps_type_28" FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "id" );
-- Generate application table actions for lbDMFManager_Entities
ALTER TABLE "action_steps" ADD CONSTRAINT "cst_actions_id_action_steps_actionid_13" FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "id" );
ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_actions_id_formular_actions_action_25" FOREIGN KEY ( "action" ) REFERENCES "actions" ( "id" );
-- Generate application table anwendungen for lbDMFManager_Entities
ALTER TABLE "users" ADD CONSTRAINT "cst_anwendungen_id_users_lastapp_1" FOREIGN KEY ( "lastapp" ) REFERENCES "anwendungen" ( "id" );
ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "cst_anwendungen_id_anwendungs_parameter_anwendungid_10" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_id_anwendungen_formulare_anwendungid_11" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_anwendungen_id_user_anwendungen_anwendungenid_22" FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "id" );
ALTER TABLE "formulare" ADD CONSTRAINT "cst_anwendungen_id_formulare_anwendungid_24" FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "id" );
-- Generate application table anwendungen_formulare for lbDMFManager_Entities
-- Generate application table anwendungs_parameter for lbDMFManager_Entities
-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities
-- Generate application table applevel_plugin_registry for lbDMFManager_Entities
-- Generate application table column_types for lbDMFManager_Entities
-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Generate application table formular_actions for lbDMFManager_Entities
-- Generate application table formular_parameters for lbDMFManager_Entities
-- Generate application table formulare for lbDMFManager_Entities
ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formulare_id_formular_parameters_formularid_7" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formulare_id_formular_actions_formular_8" FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "id" );
ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_formulare_id_anwendungsberechtigungen_idformular_9" FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "id" );
ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_formulare_id_anwendungen_formulare_formularid_27" FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "id" );
-- Generate application table formulartypen for lbDMFManager_Entities
ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulartypen_id_formulare_typ_6" FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "id" );
-- Generate application table regressiontest for lbDMFManager_Entities
-- Generate application table report_element_types for lbDMFManager_Entities
ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_element_types_id_report_elements_typ_23" FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "id" );
-- Generate application table report_elements for lbDMFManager_Entities
ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_elements_id_report_texts_elementid_3" FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "id" );
-- Generate application table report_parameters for lbDMFManager_Entities
-- Generate application table report_texts for lbDMFManager_Entities
-- Generate application table reports for lbDMFManager_Entities
ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_reports_id_report_parameters_reportid_4" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );
ALTER TABLE "report_elements" ADD CONSTRAINT "cst_reports_id_report_elements_reportid_5" FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "id" );
-- Generate application table translations for lbDMFManager_Entities
-- Generate application table user_anwendungen for lbDMFManager_Entities
-- Generate application table users for lbDMFManager_Entities
ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_users_id_user_anwendungen_userid_2" FOREIGN KEY ( "userid" ) REFERENCES "users" ( "id" );
ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_users_id_anwendungsberechtigungen_iduser_26" FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "id" );