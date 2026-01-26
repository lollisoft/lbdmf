
-- Params XSLDatabaseBackendSystem: MSSQL
-- Params XSLDatabaseBackendApplication: MSSQL
-- Params overwriteDatabase: yes

--
-- SQL script created for MSSQL
--
	

IF OBJECT_ID('lbDMF_DropTable', 'P') IS NOT NULL
    DROP PROCEDURE lbDMF_DropTable;
GO
CREATE PROCEDURE lbDMF_DropTable @Table VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP TABLE ' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('U') AND upper(pr.name) = upper(@Table)
		
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
GO

IF OBJECT_ID('lbDMF_DropProc', 'P') IS NOT NULL
    DROP PROCEDURE lbDMF_DropProc;
GO
CREATE  PROCEDURE lbDMF_DropProc @Proc VARCHAR(50)
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
GO

IF OBJECT_ID('lbDMF_DropConstraint', 'P') IS NOT NULL
    DROP PROCEDURE lbDMF_DropConstraint;
GO
CREATE  PROCEDURE lbDMF_DropConstraint @Name VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP CONSTRAINT ' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('F') AND upper(pr.name) = upper(@Name)
		
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
GO

-- Speedup many times
BEGIN TRANSACTION;


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
				
-- Class ColumnParameter of type FORM found.
				
-- Class FormularFieldParameter of type FORM found.
				
-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_parameters for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "actionid"
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "action_parameters"
-- Constraint name would be cst_action_parameters_actionid_actions

--             cst_action_parameters_actionid_actions
IF OBJECT_ID('[cst_action_parameters_actionid_actions]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_parameters] 
    DROP CONSTRAINT [cst_action_parameters_actionid_actions];
END
IF OBJECT_ID('[cst_BOUML_0x20382_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [actions] 
    DROP CONSTRAINT [cst_BOUML_0x20382_0];
END



--ALTER TABLE "actions" DROP CONSTRAINT "cst_BOUML_0x20382_0";
-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_step_parameter for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "action_step_id"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "action_step_parameter"
-- Constraint name would be cst_action_step_parameter_action_step_id_action_steps

--             cst_action_step_parameter_action_step_id_action_steps
IF OBJECT_ID('[cst_action_step_parameter_action_step_id_action_steps]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_step_parameter] 
    DROP CONSTRAINT [cst_action_step_parameter_action_step_id_action_steps];
END
IF OBJECT_ID('[cst_BOUML_0x1fe82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_steps] 
    DROP CONSTRAINT [cst_BOUML_0x1fe82_0];
END



--ALTER TABLE "action_steps" DROP CONSTRAINT "cst_BOUML_0x1fe82_0";
-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_step_transitions for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dst_actionid"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "action_step_transitions"
-- Constraint name would be cst_action_step_transitions_dst_actionid_action_steps

--             cst_action_step_transitions_dst_actionid_action_steps
IF OBJECT_ID('[cst_action_step_transitions_dst_actionid_action_steps]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_step_transitions] 
    DROP CONSTRAINT [cst_action_step_transitions_dst_actionid_action_steps];
END
IF OBJECT_ID('[cst_BOUML_0x1ff82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_steps] 
    DROP CONSTRAINT [cst_BOUML_0x1ff82_0];
END



--ALTER TABLE "action_steps" DROP CONSTRAINT "cst_BOUML_0x1ff82_0";
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "src_actionid"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "action_step_transitions"
-- Constraint name would be cst_action_step_transitions_src_actionid_action_steps

--             cst_action_step_transitions_src_actionid_action_steps
IF OBJECT_ID('[cst_action_step_transitions_src_actionid_action_steps]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_step_transitions] 
    DROP CONSTRAINT [cst_action_step_transitions_src_actionid_action_steps];
END
IF OBJECT_ID('[cst_BOUML_0x20082_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_steps] 
    DROP CONSTRAINT [cst_BOUML_0x20082_0];
END



--ALTER TABLE "action_steps" DROP CONSTRAINT "cst_BOUML_0x20082_0";
-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_steps for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "type"
-- Aggregation type "none"
-- Primary table "action_types"
-- Primary column ""
-- Foreign table "action_steps"
-- Constraint name would be cst_action_steps_type_action_types

--             cst_action_steps_type_action_types
IF OBJECT_ID('[cst_action_steps_type_action_types]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_steps] 
    DROP CONSTRAINT [cst_action_steps_type_action_types];
END
IF OBJECT_ID('[cst_BOUML_0x20182_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_types] 
    DROP CONSTRAINT [cst_BOUML_0x20182_0];
END



--ALTER TABLE "action_types" DROP CONSTRAINT "cst_BOUML_0x20182_0";
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "actionid"
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "action_steps"
-- Constraint name would be cst_action_steps_actionid_actions

--             cst_action_steps_actionid_actions
IF OBJECT_ID('[cst_action_steps_actionid_actions]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_steps] 
    DROP CONSTRAINT [cst_action_steps_actionid_actions];
END
IF OBJECT_ID('[cst_BOUML_0x20482_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [actions] 
    DROP CONSTRAINT [cst_BOUML_0x20482_0];
END



--ALTER TABLE "actions" DROP CONSTRAINT "cst_BOUML_0x20482_0";
-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table action_types for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table actions for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "typ"
-- Aggregation type "none"
-- Primary table "action_types"
-- Primary column ""
-- Foreign table "actions"
-- Constraint name would be cst_actions_typ_action_types

--             cst_actions_typ_action_types
IF OBJECT_ID('[cst_actions_typ_action_types]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [actions] 
    DROP CONSTRAINT [cst_actions_typ_action_types];
END
IF OBJECT_ID('[cst_BOUML_0x20202_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [action_types] 
    DROP CONSTRAINT [cst_BOUML_0x20202_0];
END



--ALTER TABLE "action_types" DROP CONSTRAINT "cst_BOUML_0x20202_0";
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungenid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "actions"
-- Constraint name would be cst_actions_anwendungenid_anwendungen

--             cst_actions_anwendungenid_anwendungen
IF OBJECT_ID('[cst_actions_anwendungenid_anwendungen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [actions] 
    DROP CONSTRAINT [cst_actions_anwendungenid_anwendungen];
END
IF OBJECT_ID('[cst_BOUML_0x30502_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen] 
    DROP CONSTRAINT [cst_BOUML_0x30502_0];
END



--ALTER TABLE "anwendungen" DROP CONSTRAINT "cst_BOUML_0x30502_0";
-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungen for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungen_formulare for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "anwendungen_formulare"
-- Constraint name would be cst_anwendungen_formulare_anwendungid_anwendungen

--             cst_anwendungen_formulare_anwendungid_anwendungen
IF OBJECT_ID('[cst_anwendungen_formulare_anwendungid_anwendungen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen_formulare] 
    DROP CONSTRAINT [cst_anwendungen_formulare_anwendungid_anwendungen];
END
IF OBJECT_ID('[cst_BOUML_0x20602_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen] 
    DROP CONSTRAINT [cst_BOUML_0x20602_0];
END



--ALTER TABLE "anwendungen" DROP CONSTRAINT "cst_BOUML_0x20602_0";
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularid"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "anwendungen_formulare"
-- Constraint name would be cst_anwendungen_formulare_formularid_formulare

--             cst_anwendungen_formulare_formularid_formulare
IF OBJECT_ID('[cst_anwendungen_formulare_formularid_formulare]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen_formulare] 
    DROP CONSTRAINT [cst_anwendungen_formulare_formularid_formulare];
END
IF OBJECT_ID('[cst_BOUML_0x20b82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulare] 
    DROP CONSTRAINT [cst_BOUML_0x20b82_0];
END



--ALTER TABLE "formulare" DROP CONSTRAINT "cst_BOUML_0x20b82_0";
-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungs_parameter for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "anwendungs_parameter"
-- Constraint name would be cst_anwendungs_parameter_anwendungid_anwendungen

--             cst_anwendungs_parameter_anwendungid_anwendungen
IF OBJECT_ID('[cst_anwendungs_parameter_anwendungid_anwendungen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungs_parameter] 
    DROP CONSTRAINT [cst_anwendungs_parameter_anwendungid_anwendungen];
END
IF OBJECT_ID('[cst_BOUML_0x20702_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen] 
    DROP CONSTRAINT [cst_BOUML_0x20702_0];
END



--ALTER TABLE "anwendungen" DROP CONSTRAINT "cst_BOUML_0x20702_0";
-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table anwendungsberechtigungen for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "idformular"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "anwendungsberechtigungen"
-- Constraint name would be cst_anwendungsberechtigungen_idformular_formulare

--             cst_anwendungsberechtigungen_idformular_formulare
IF OBJECT_ID('[cst_anwendungsberechtigungen_idformular_formulare]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungsberechtigungen] 
    DROP CONSTRAINT [cst_anwendungsberechtigungen_idformular_formulare];
END
IF OBJECT_ID('[cst_BOUML_0x20c82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulare] 
    DROP CONSTRAINT [cst_BOUML_0x20c82_0];
END



--ALTER TABLE "formulare" DROP CONSTRAINT "cst_BOUML_0x20c82_0";
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "iduser"
-- Aggregation type "none"
-- Primary table "users"
-- Primary column ""
-- Foreign table "anwendungsberechtigungen"
-- Constraint name would be cst_anwendungsberechtigungen_iduser_users

--             cst_anwendungsberechtigungen_iduser_users
IF OBJECT_ID('[cst_anwendungsberechtigungen_iduser_users]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungsberechtigungen] 
    DROP CONSTRAINT [cst_anwendungsberechtigungen_iduser_users];
END
IF OBJECT_ID('[cst_BOUML_0x21482_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [users] 
    DROP CONSTRAINT [cst_BOUML_0x21482_0];
END



--ALTER TABLE "users" DROP CONSTRAINT "cst_BOUML_0x21482_0";
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
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "action"
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "formular_actions"
-- Constraint name would be cst_formular_actions_action_actions

--             cst_formular_actions_action_actions
IF OBJECT_ID('[cst_formular_actions_action_actions]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formular_actions] 
    DROP CONSTRAINT [cst_formular_actions_action_actions];
END
IF OBJECT_ID('[cst_BOUML_0x20502_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [actions] 
    DROP CONSTRAINT [cst_BOUML_0x20502_0];
END



--ALTER TABLE "actions" DROP CONSTRAINT "cst_BOUML_0x20502_0";
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formular"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "formular_actions"
-- Constraint name would be cst_formular_actions_formular_formulare

--             cst_formular_actions_formular_formulare
IF OBJECT_ID('[cst_formular_actions_formular_formulare]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formular_actions] 
    DROP CONSTRAINT [cst_formular_actions_formular_formulare];
END
IF OBJECT_ID('[cst_BOUML_0x20d82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulare] 
    DROP CONSTRAINT [cst_BOUML_0x20d82_0];
END



--ALTER TABLE "formulare" DROP CONSTRAINT "cst_BOUML_0x20d82_0";
-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formular_parameters for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularid"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "formular_parameters"
-- Constraint name would be cst_formular_parameters_formularid_formulare

--             cst_formular_parameters_formularid_formulare
IF OBJECT_ID('[cst_formular_parameters_formularid_formulare]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formular_parameters] 
    DROP CONSTRAINT [cst_formular_parameters_formularid_formulare];
END
IF OBJECT_ID('[cst_BOUML_0x20e82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulare] 
    DROP CONSTRAINT [cst_BOUML_0x20e82_0];
END



--ALTER TABLE "formulare" DROP CONSTRAINT "cst_BOUML_0x20e82_0";
-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formulare for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_anwendungid_anwendungen

--             cst_formulare_anwendungid_anwendungen
IF OBJECT_ID('[cst_formulare_anwendungid_anwendungen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulare] 
    DROP CONSTRAINT [cst_formulare_anwendungid_anwendungen];
END
IF OBJECT_ID('[cst_BOUML_0x20802_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen] 
    DROP CONSTRAINT [cst_BOUML_0x20802_0];
END



--ALTER TABLE "anwendungen" DROP CONSTRAINT "cst_BOUML_0x20802_0";
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "typ"
-- Aggregation type "none"
-- Primary table "formulartypen"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_typ_formulartypen

--             cst_formulare_typ_formulartypen
IF OBJECT_ID('[cst_formulare_typ_formulartypen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulare] 
    DROP CONSTRAINT [cst_formulare_typ_formulartypen];
END
IF OBJECT_ID('[cst_BOUML_0x20f82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulartypen] 
    DROP CONSTRAINT [cst_BOUML_0x20f82_0];
END



--ALTER TABLE "formulartypen" DROP CONSTRAINT "cst_BOUML_0x20f82_0";
-- dropMSSQLTableRelation
	
-- Class formularfields of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formularfields for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularid"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "formularfields"
-- Constraint name would be cst_formularfields_formularid_formulare

--             cst_formularfields_formularid_formulare
IF OBJECT_ID('[cst_formularfields_formularid_formulare]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formularfields] 
    DROP CONSTRAINT [cst_formularfields_formularid_formulare];
END
IF OBJECT_ID('[cst_BOUML_0x25b82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formulare] 
    DROP CONSTRAINT [cst_BOUML_0x25b82_0];
END



--ALTER TABLE "formulare" DROP CONSTRAINT "cst_BOUML_0x25b82_0";
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtypeid"
-- Aggregation type "none"
-- Primary table "dbtype"
-- Primary column ""
-- Foreign table "formularfields"
-- Constraint name would be cst_formularfields_dbtypeid_dbtype

--             cst_formularfields_dbtypeid_dbtype
IF OBJECT_ID('[cst_formularfields_dbtypeid_dbtype]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formularfields] 
    DROP CONSTRAINT [cst_formularfields_dbtypeid_dbtype];
END
IF OBJECT_ID('[cst_BOUML_0x25d02_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbtype] 
    DROP CONSTRAINT [cst_BOUML_0x25d02_0];
END



--ALTER TABLE "dbtype" DROP CONSTRAINT "cst_BOUML_0x25d02_0";
-- dropMSSQLTableRelation
	
-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formulartypen for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table regressiontest for lbDMFManager_Entities
-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_element_types for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_elements for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "typ"
-- Aggregation type "none"
-- Primary table "report_element_types"
-- Primary column ""
-- Foreign table "report_elements"
-- Constraint name would be cst_report_elements_typ_report_element_types

--             cst_report_elements_typ_report_element_types
IF OBJECT_ID('[cst_report_elements_typ_report_element_types]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [report_elements] 
    DROP CONSTRAINT [cst_report_elements_typ_report_element_types];
END
IF OBJECT_ID('[cst_BOUML_0x21002_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [report_element_types] 
    DROP CONSTRAINT [cst_BOUML_0x21002_0];
END



--ALTER TABLE "report_element_types" DROP CONSTRAINT "cst_BOUML_0x21002_0";
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "reportid"
-- Aggregation type "none"
-- Primary table "reports"
-- Primary column ""
-- Foreign table "report_elements"
-- Constraint name would be cst_report_elements_reportid_reports

--             cst_report_elements_reportid_reports
IF OBJECT_ID('[cst_report_elements_reportid_reports]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [report_elements] 
    DROP CONSTRAINT [cst_report_elements_reportid_reports];
END
IF OBJECT_ID('[cst_BOUML_0x21282_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [reports] 
    DROP CONSTRAINT [cst_BOUML_0x21282_0];
END



--ALTER TABLE "reports" DROP CONSTRAINT "cst_BOUML_0x21282_0";
-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_parameters for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "reportid"
-- Aggregation type "none"
-- Primary table "reports"
-- Primary column ""
-- Foreign table "report_parameters"
-- Constraint name would be cst_report_parameters_reportid_reports

--             cst_report_parameters_reportid_reports
IF OBJECT_ID('[cst_report_parameters_reportid_reports]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [report_parameters] 
    DROP CONSTRAINT [cst_report_parameters_reportid_reports];
END
IF OBJECT_ID('[cst_BOUML_0x21382_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [reports] 
    DROP CONSTRAINT [cst_BOUML_0x21382_0];
END



--ALTER TABLE "reports" DROP CONSTRAINT "cst_BOUML_0x21382_0";
-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table report_texts for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "elementid"
-- Aggregation type "none"
-- Primary table "report_elements"
-- Primary column ""
-- Foreign table "report_texts"
-- Constraint name would be cst_report_texts_elementid_report_elements

--             cst_report_texts_elementid_report_elements
IF OBJECT_ID('[cst_report_texts_elementid_report_elements]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [report_texts] 
    DROP CONSTRAINT [cst_report_texts_elementid_report_elements];
END
IF OBJECT_ID('[cst_BOUML_0x21102_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [report_elements] 
    DROP CONSTRAINT [cst_BOUML_0x21102_0];
END



--ALTER TABLE "report_elements" DROP CONSTRAINT "cst_BOUML_0x21102_0";
-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table reports for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table translations for lbDMFManager_Entities
-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table user_anwendungen for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungenid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "user_anwendungen"
-- Constraint name would be cst_user_anwendungen_anwendungenid_anwendungen

--             cst_user_anwendungen_anwendungenid_anwendungen
IF OBJECT_ID('[cst_user_anwendungen_anwendungenid_anwendungen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [user_anwendungen] 
    DROP CONSTRAINT [cst_user_anwendungen_anwendungenid_anwendungen];
END
IF OBJECT_ID('[cst_BOUML_0x20902_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen] 
    DROP CONSTRAINT [cst_BOUML_0x20902_0];
END



--ALTER TABLE "anwendungen" DROP CONSTRAINT "cst_BOUML_0x20902_0";
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "userid"
-- Aggregation type "none"
-- Primary table "users"
-- Primary column ""
-- Foreign table "user_anwendungen"
-- Constraint name would be cst_user_anwendungen_userid_users

--             cst_user_anwendungen_userid_users
IF OBJECT_ID('[cst_user_anwendungen_userid_users]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [user_anwendungen] 
    DROP CONSTRAINT [cst_user_anwendungen_userid_users];
END
IF OBJECT_ID('[cst_BOUML_0x21582_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [users] 
    DROP CONSTRAINT [cst_BOUML_0x21582_0];
END



--ALTER TABLE "users" DROP CONSTRAINT "cst_BOUML_0x21582_0";
-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table users for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "lastapp"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "users"
-- Constraint name would be cst_users_lastapp_anwendungen

--             cst_users_lastapp_anwendungen
IF OBJECT_ID('[cst_users_lastapp_anwendungen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [users] 
    DROP CONSTRAINT [cst_users_lastapp_anwendungen];
END
IF OBJECT_ID('[cst_BOUML_0x20a02_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen] 
    DROP CONSTRAINT [cst_BOUML_0x20a02_0];
END



--ALTER TABLE "anwendungen" DROP CONSTRAINT "cst_BOUML_0x20a02_0";
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- Class dbtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table dbtype for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- Class dbtable of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table dbtable for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungenid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "dbtable"
-- Constraint name would be cst_dbtable_anwendungenid_anwendungen

--             cst_dbtable_anwendungenid_anwendungen
IF OBJECT_ID('[cst_dbtable_anwendungenid_anwendungen]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbtable] 
    DROP CONSTRAINT [cst_dbtable_anwendungenid_anwendungen];
END
IF OBJECT_ID('[cst_BOUML_0x2d102_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [anwendungen] 
    DROP CONSTRAINT [cst_BOUML_0x2d102_0];
END



--ALTER TABLE "anwendungen" DROP CONSTRAINT "cst_BOUML_0x2d102_0";
-- dropMSSQLTableRelation
	
-- Class dbcolumn of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table dbcolumn for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbcolumn"
-- Constraint name would be cst_dbcolumn_dbtableid_dbtable

--             cst_dbcolumn_dbtableid_dbtable
IF OBJECT_ID('[cst_dbcolumn_dbtableid_dbtable]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbcolumn] 
    DROP CONSTRAINT [cst_dbcolumn_dbtableid_dbtable];
END
IF OBJECT_ID('[cst_BOUML_0x2b082_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbtable] 
    DROP CONSTRAINT [cst_BOUML_0x2b082_0];
END



--ALTER TABLE "dbtable" DROP CONSTRAINT "cst_BOUML_0x2b082_0";
-- dropMSSQLTableRelation
	
-- Class dbforeignkey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table dbforeignkey for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbforeignkey"
-- Constraint name would be cst_dbforeignkey_dbtableid_dbtable

--             cst_dbforeignkey_dbtableid_dbtable
IF OBJECT_ID('[cst_dbforeignkey_dbtableid_dbtable]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbforeignkey] 
    DROP CONSTRAINT [cst_dbforeignkey_dbtableid_dbtable];
END
IF OBJECT_ID('[cst_BOUML_0x2b182_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbtable] 
    DROP CONSTRAINT [cst_BOUML_0x2b182_0];
END



--ALTER TABLE "dbtable" DROP CONSTRAINT "cst_BOUML_0x2b182_0";
-- Class dbprimarykey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table dbprimarykey for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbprimarykey"
-- Constraint name would be cst_dbprimarykey_dbtableid_dbtable

--             cst_dbprimarykey_dbtableid_dbtable
IF OBJECT_ID('[cst_dbprimarykey_dbtableid_dbtable]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbprimarykey] 
    DROP CONSTRAINT [cst_dbprimarykey_dbtableid_dbtable];
END
IF OBJECT_ID('[cst_BOUML_0x2af82_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbtable] 
    DROP CONSTRAINT [cst_BOUML_0x2af82_0];
END



--ALTER TABLE "dbtable" DROP CONSTRAINT "cst_BOUML_0x2af82_0";
-- Unknown stereotype 'filterdefinition' for class UserFilter.
		
-- Drop application table UserFilter for lbDMFManager_Entities
-- Class dbtableparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table dbtableparameter for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbtableparameter"
-- Constraint name would be cst_dbtableparameter_dbtableid_dbtable

--             cst_dbtableparameter_dbtableid_dbtable
IF OBJECT_ID('[cst_dbtableparameter_dbtableid_dbtable]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbtableparameter] 
    DROP CONSTRAINT [cst_dbtableparameter_dbtableid_dbtable];
END
IF OBJECT_ID('[cst_BOUML_0x36f02_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbtable] 
    DROP CONSTRAINT [cst_BOUML_0x36f02_0];
END



--ALTER TABLE "dbtable" DROP CONSTRAINT "cst_BOUML_0x36f02_0";
-- Class dbcolumnparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table dbcolumnparameter for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbcolumnid"
-- Aggregation type "none"
-- Primary table "dbcolumn"
-- Primary column ""
-- Foreign table "dbcolumnparameter"
-- Constraint name would be cst_dbcolumnparameter_dbcolumnid_dbcolumn

--             cst_dbcolumnparameter_dbcolumnid_dbcolumn
IF OBJECT_ID('[cst_dbcolumnparameter_dbcolumnid_dbcolumn]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbcolumnparameter] 
    DROP CONSTRAINT [cst_dbcolumnparameter_dbcolumnid_dbcolumn];
END
IF OBJECT_ID('[cst_BOUML_0x38982_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [dbcolumn] 
    DROP CONSTRAINT [cst_BOUML_0x38982_0];
END



--ALTER TABLE "dbcolumn" DROP CONSTRAINT "cst_BOUML_0x38982_0";
-- Class formularfieldparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Drop application table formularfieldparameter for lbDMFManager_Entities
-- dropMSSQLTableRelation
	
-- dropDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularfieldid"
-- Aggregation type "none"
-- Primary table "formularfields"
-- Primary column ""
-- Foreign table "formularfieldparameter"
-- Constraint name would be cst_formularfieldparameter_formularfieldid_formularfields

--             cst_formularfieldparameter_formularfieldid_formularfields
IF OBJECT_ID('[cst_formularfieldparameter_formularfieldid_formularfields]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formularfieldparameter] 
    DROP CONSTRAINT [cst_formularfieldparameter_formularfieldid_formularfields];
END
IF OBJECT_ID('[cst_BOUML_0x3a402_0]', 'F') IS NOT NULL
BEGIN
    ALTER TABLE [formularfields] 
    DROP CONSTRAINT [cst_BOUML_0x3a402_0];
END



--ALTER TABLE "formularfields" DROP CONSTRAINT "cst_BOUML_0x3a402_0";
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
				
-- Class ColumnParameter of type FORM found.
				
-- Class FormularFieldParameter of type FORM found.
				
-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE action_parameters
exec lbDMF_dropTable 'action_parameters';

-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_parameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE action_step_parameter
exec lbDMF_dropTable 'action_step_parameter';

-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_transitions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE action_step_transitions
exec lbDMF_dropTable 'action_step_transitions';

-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE action_steps
exec lbDMF_dropTable 'action_steps';

-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE action_types
exec lbDMF_dropTable 'action_types';

-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE actions
exec lbDMF_dropTable 'actions';

-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungen
exec lbDMF_dropTable 'anwendungen';

-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungen_formulare
exec lbDMF_dropTable 'anwendungen_formulare';

-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungs_parameter
exec lbDMF_dropTable 'anwendungs_parameter';

-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE anwendungsberechtigungen
exec lbDMF_dropTable 'anwendungsberechtigungen';

-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE applevel_plugin_registry
exec lbDMF_dropTable 'applevel_plugin_registry';

-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE codegentarget
exec lbDMF_dropTable 'codegentarget';

-- Class column_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table column_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE column_types
exec lbDMF_dropTable 'column_types';

-- Class foreignkey_visibledata_mapping of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table foreignkey_visibledata_mapping for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE foreignkey_visibledata_mapping
exec lbDMF_dropTable 'foreignkey_visibledata_mapping';

-- Class formular_actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_actions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formular_actions
exec lbDMF_dropTable 'formular_actions';

-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formular_parameters
exec lbDMF_dropTable 'formular_parameters';

-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formulare
exec lbDMF_dropTable 'formulare';

-- Class formularfields of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formularfields for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formularfields
exec lbDMF_dropTable 'formularfields';

-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formulartypen
exec lbDMF_dropTable 'formulartypen';

-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE regressiontest
exec lbDMF_dropTable 'regressiontest';

-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_element_types
exec lbDMF_dropTable 'report_element_types';

-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_elements
exec lbDMF_dropTable 'report_elements';

-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_parameters
exec lbDMF_dropTable 'report_parameters';

-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE report_texts
exec lbDMF_dropTable 'report_texts';

-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE reports
exec lbDMF_dropTable 'reports';

-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE translations
exec lbDMF_dropTable 'translations';

-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE user_anwendungen
exec lbDMF_dropTable 'user_anwendungen';

-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE users
exec lbDMF_dropTable 'users';

-- Class dbtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtype for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE dbtype
exec lbDMF_dropTable 'dbtype';

-- Class dbtable of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtable for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE dbtable
exec lbDMF_dropTable 'dbtable';

-- Class dbcolumn of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbcolumn for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE dbcolumn
exec lbDMF_dropTable 'dbcolumn';

-- Class dbforeignkey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbforeignkey for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE dbforeignkey
exec lbDMF_dropTable 'dbforeignkey';

-- Class dbprimarykey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbprimarykey for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE dbprimarykey
exec lbDMF_dropTable 'dbprimarykey';

-- Unknown stereotype 'filterdefinition' for class UserFilter.
		
-- Generate application table UserFilter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE UserFilter
exec lbDMF_dropTable 'UserFilter';

-- Class dbtableparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtableparameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE dbtableparameter
exec lbDMF_dropTable 'dbtableparameter';

-- Class dbcolumnparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbcolumnparameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE dbcolumnparameter
exec lbDMF_dropTable 'dbcolumnparameter';

-- Class formularfieldparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formularfieldparameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- DROP TABLE formularfieldparameter
exec lbDMF_dropTable 'formularfieldparameter';

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
				
-- Class ColumnParameter of type FORM found.
				
-- Class FormularFieldParameter of type FORM found.
				
-- Class action_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE action_parameters FOR MSSQL
CREATE TABLE "action_parameters" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"value" char(255),
	"interface" char(255),
	"description" char(255),
	"actionid" INTEGER
);


-- Class action_step_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_parameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE action_step_parameter FOR MSSQL
CREATE TABLE "action_step_parameter" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"value" char(255),
	"interface" char(255),
	"description" char(255),
	"action_step_id" INTEGER
);


-- Class action_step_transitions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_step_transitions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE action_step_transitions FOR MSSQL
CREATE TABLE "action_step_transitions" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"expression" char(255),
	"description" char(255),
	"dst_actionid" INTEGER,
	"src_actionid" INTEGER
);


-- Class action_steps of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_steps for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE action_steps FOR MSSQL
CREATE TABLE "action_steps" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"bezeichnung" char(255),
	"a_order_nr" INTEGER,
	"what" char(255),
	"type" INTEGER,
	"actionid" INTEGER
);


-- Class action_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table action_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE action_types FOR MSSQL
CREATE TABLE "action_types" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"bezeichnung" char(255),
	"action_handler" char(255),
	"module" char(255)
);


-- Class actions of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table actions for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE actions FOR MSSQL
CREATE TABLE "actions" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"source" char(255),
	"target" char(255),
	"typ" INTEGER,
	"anwendungenid" INTEGER
);


-- Class anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE anwendungen FOR MSSQL
CREATE TABLE "anwendungen" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"titel" char(255),
	"modulename" char(255),
	"functor" char(255),
	"interface" char(255),
	"requirements" TEXT,
	"background" TEXT,
	"model_complete" BIT,
	"model_errors" TEXT
);


-- Class anwendungen_formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungen_formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE anwendungen_formulare FOR MSSQL
CREATE TABLE "anwendungen_formulare" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"anwendungid" INTEGER,
	"formularid" INTEGER,
	"purpose" char(255)
);


-- Class anwendungs_parameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungs_parameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE anwendungs_parameter FOR MSSQL
CREATE TABLE "anwendungs_parameter" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"parametername" char(255),
	"parametervalue" char(255),
	"anwendungid" INTEGER
);


-- Class anwendungsberechtigungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table anwendungsberechtigungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE anwendungsberechtigungen FOR MSSQL
CREATE TABLE "anwendungsberechtigungen" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"idformular" INTEGER,
	"iduser" INTEGER
);


-- Class applevel_plugin_registry of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table applevel_plugin_registry for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE applevel_plugin_registry FOR MSSQL
CREATE TABLE "applevel_plugin_registry" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"anwendungid" INTEGER
);


-- Class codegentarget of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table codegentarget for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE codegentarget FOR MSSQL
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


-- createMSSQLTable CREATE TABLE column_types FOR MSSQL
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


-- createMSSQLTable CREATE TABLE foreignkey_visibledata_mapping FOR MSSQL
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


-- createMSSQLTable CREATE TABLE formular_actions FOR MSSQL
CREATE TABLE "formular_actions" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"event" char(255),
	"action" INTEGER,
	"formular" INTEGER
);


-- Class formular_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formular_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE formular_parameters FOR MSSQL
CREATE TABLE "formular_parameters" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"parametername" char(255),
	"parametervalue" char(255),
	"formularid" INTEGER
);


-- Class formulare of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulare for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE formulare FOR MSSQL
CREATE TABLE "formulare" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"menuname" char(255),
	"menuorder" INTEGER,
	"eventname" char(255),
	"menuhilfe" char(255),
	"toolbarimage" char(255),
	"anwendungid" INTEGER,
	"typ" INTEGER
);


-- Class formularfields of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formularfields for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE formularfields FOR MSSQL
CREATE TABLE "formularfields" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"tablename" char(255),
	"formularid" INTEGER,
	"dbtypeid" INTEGER,
	"isfk" BIT,
	"fkname" char(255),
	"fktable" char(255),
	"dbtype" char(255)
);


-- Class formulartypen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formulartypen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE formulartypen FOR MSSQL
CREATE TABLE "formulartypen" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"handlermodule" char(255),
	"handlerfunctor" char(255),
	"handlerinterface" char(255),
	"namespace" char(255),
	"beschreibung" char(255)
);


-- Class regressiontest of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table regressiontest for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE regressiontest FOR MSSQL
CREATE TABLE "regressiontest" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"test" char(255),
	"btest" BIT,
	"btest1" BIT
);


-- Class report_element_types of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_element_types for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE report_element_types FOR MSSQL
CREATE TABLE "report_element_types" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"description" char(255)
);


-- Class report_elements of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_elements for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE report_elements FOR MSSQL
CREATE TABLE "report_elements" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"x" INTEGER,
	"y" INTEGER,
	"w" INTEGER,
	"h" INTEGER,
	"description" char(255),
	"typ" INTEGER,
	"reportid" INTEGER
);


-- Class report_parameters of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_parameters for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE report_parameters FOR MSSQL
CREATE TABLE "report_parameters" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"value" INTEGER,
	"reportid" INTEGER
);


-- Class report_texts of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table report_texts for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE report_texts FOR MSSQL
CREATE TABLE "report_texts" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"line" INTEGER,
	"text" char(255),
	"elementid" INTEGER
);


-- Class reports of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table reports for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE reports FOR MSSQL
CREATE TABLE "reports" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"description" char(255)
);


-- Class translations of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table translations for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE translations FOR MSSQL
CREATE TABLE "translations" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"text" char(255),
	"translated" char(255),
	"language" char(255)
);


-- Class user_anwendungen of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table user_anwendungen for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE user_anwendungen FOR MSSQL
CREATE TABLE "user_anwendungen" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"anwendungenid" INTEGER,
	"userid" INTEGER
);


-- Class users of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table users for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE users FOR MSSQL
CREATE TABLE "users" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"vorname" char(255),
	"userid" char(255),
	"passwort" char(255),
	"lastapp" INTEGER
);


-- Class dbtype of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtype for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE dbtype FOR MSSQL
CREATE TABLE "dbtype" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"name" char(255),
	"description" char(255)
);


-- Class dbtable of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtable for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE dbtable FOR MSSQL
CREATE TABLE "dbtable" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"catalogname" char(255),
	"schemaname" char(255),
	"tablename" char(255),
	"tabletype" char(255),
	"tableremarks" char(255),
	"anwendungenid" INTEGER
);


-- Class dbcolumn of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbcolumn for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE dbcolumn FOR MSSQL
CREATE TABLE "dbcolumn" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"columnname" char(255),
	"columnremarks" char(255),
	"typename" char(255),
	"columnsize" INTEGER,
	"nullable" BIT,
	"tablename" char(255),
	"dbtableid" INTEGER
);


-- Class dbforeignkey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbforeignkey for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE dbforeignkey FOR MSSQL
CREATE TABLE "dbforeignkey" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"pkcatalog" char(255),
	"pkschema" char(255),
	"pktable" char(255),
	"pkcolumn" char(255),
	"fkcatalog" char(255),
	"fkschema" char(255),
	"fktable" char(255),
	"fkcolumn" char(255),
	"keysequence" INTEGER,
	"updaterule" INTEGER,
	"deleterule" INTEGER,
	"dbtableid" INTEGER
);


-- Class dbprimarykey of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbprimarykey for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE dbprimarykey FOR MSSQL
CREATE TABLE "dbprimarykey" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"tablecatalog" char(255),
	"tableschema" char(255),
	"tablename" char(255),
	"columnname" char(255),
	"columnname2" char(255),
	"keysequence" INTEGER,
	"dbtableid" INTEGER
);


-- Unknown stereotype 'filterdefinition' for class UserFilter.
-- Create table via importApplicationTableAutoID

-- Class dbtableparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbtableparameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE dbtableparameter FOR MSSQL
CREATE TABLE "dbtableparameter" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"parametername" char(255),
	"parametervalue" char(255),
	"dbtableid" INTEGER
);


-- Class dbcolumnparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table dbcolumnparameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE dbcolumnparameter FOR MSSQL
CREATE TABLE "dbcolumnparameter" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"parametername" char(255),
	"parametervalue" char(255),
	"dbcolumnid" INTEGER
);


-- Class formularfieldparameter of type ENTITY found.
-- Create table model with template 'importApplicationTable'.

-- Generate application table formularfieldparameter for lbDMFManager_Entities. Tagtet database: 'MSSQL'


-- createMSSQLTable CREATE TABLE formularfieldparameter FOR MSSQL
CREATE TABLE "formularfieldparameter" (
	"id" INTEGER IDENTITY (1, 1) NOT NULL,
	"parametername" char(255),
	"parametervalue" char(255),
	"formularfieldid" INTEGER
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
				
-- Class ColumnParameter of type FORM found.
				
-- Class FormularFieldParameter of type FORM found.
				
-- Class action_parameters of type ENTITY found.

-- Generate application tables action_parameters for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "action_parameters" ADD CONSTRAINT "action_parameters_pkey" PRIMARY KEY ("id");
		
-- Class action_step_parameter of type ENTITY found.

-- Generate application tables action_step_parameter for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "action_step_parameter" ADD CONSTRAINT "action_step_parameter_pkey" PRIMARY KEY ("id");
		
-- Class action_step_transitions of type ENTITY found.

-- Generate application tables action_step_transitions for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "action_step_transitions" ADD CONSTRAINT "action_step_transitions_pkey" PRIMARY KEY ("id");
		
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
		
-- Class formularfields of type ENTITY found.

-- Generate application tables formularfields for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "formularfields" ADD CONSTRAINT "formularfields_pkey" PRIMARY KEY ("id");
		
-- Class formulartypen of type ENTITY found.

-- Generate application tables formulartypen for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "formulartypen" ADD CONSTRAINT "formulartypen_pkey" PRIMARY KEY ("id");
		
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
		
-- Class dbtype of type ENTITY found.

-- Generate application tables dbtype for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "dbtype" ADD CONSTRAINT "dbtype_pkey" PRIMARY KEY ("id");
		
-- Class dbtable of type ENTITY found.

-- Generate application tables dbtable for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "dbtable" ADD CONSTRAINT "dbtable_pkey" PRIMARY KEY ("id");
		
-- Class dbcolumn of type ENTITY found.

-- Generate application tables dbcolumn for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "dbcolumn" ADD CONSTRAINT "dbcolumn_pkey" PRIMARY KEY ("id");
		
-- Class dbforeignkey of type ENTITY found.

-- Generate application tables dbforeignkey for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "dbforeignkey" ADD CONSTRAINT "dbforeignkey_pkey" PRIMARY KEY ("id");
		
-- Class dbprimarykey of type ENTITY found.

-- Generate application tables dbprimarykey for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "dbprimarykey" ADD CONSTRAINT "dbprimarykey_pkey" PRIMARY KEY ("id");
		
-- Class dbtableparameter of type ENTITY found.

-- Generate application tables dbtableparameter for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "dbtableparameter" ADD CONSTRAINT "dbtableparameter_pkey" PRIMARY KEY ("id");
		
-- Class dbcolumnparameter of type ENTITY found.

-- Generate application tables dbcolumnparameter for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "dbcolumnparameter" ADD CONSTRAINT "dbcolumnparameter_pkey" PRIMARY KEY ("id");
		
-- Class formularfieldparameter of type ENTITY found.

-- Generate application tables formularfieldparameter for lbDMFManager_Entities primary keys. Tagtet database: 'MSSQL'


ALTER TABLE "formularfieldparameter" ADD CONSTRAINT "formularfieldparameter_pkey" PRIMARY KEY ("id");
		
-- Generate MSSQL application relations for table action_parameters for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "actionid"
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "action_parameters"
-- Constraint name would be cst_action_parameters_actionid_actions
-- Not Empty case 1
ALTER TABLE "action_parameters" 
ADD CONSTRAINT "cst_action_parameters_actionid_actions" 
FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "ID" );

-- Generate MSSQL application relations for table action_step_parameter for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "action_step_id"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "action_step_parameter"
-- Constraint name would be cst_action_step_parameter_action_step_id_action_steps
-- Not Empty case 1
ALTER TABLE "action_step_parameter" 
ADD CONSTRAINT "cst_action_step_parameter_action_step_id_action_steps" 
FOREIGN KEY ( "action_step_id" ) REFERENCES "action_steps" ( "ID" );

-- Generate MSSQL application relations for table action_step_transitions for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dst_actionid"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "action_step_transitions"
-- Constraint name would be cst_action_step_transitions_dst_actionid_action_steps
-- Not Empty case 1
ALTER TABLE "action_step_transitions" 
ADD CONSTRAINT "cst_action_step_transitions_dst_actionid_action_steps" 
FOREIGN KEY ( "dst_actionid" ) REFERENCES "action_steps" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "src_actionid"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "action_step_transitions"
-- Constraint name would be cst_action_step_transitions_src_actionid_action_steps
-- Not Empty case 1
ALTER TABLE "action_step_transitions" 
ADD CONSTRAINT "cst_action_step_transitions_src_actionid_action_steps" 
FOREIGN KEY ( "src_actionid" ) REFERENCES "action_steps" ( "ID" );

-- Generate MSSQL application relations for table action_steps for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_1"
-- Aggregation type "none"
-- Primary table "action_step_parameter"
-- Primary column ""
-- Foreign table "action_steps"
-- Constraint name would be cst_action_steps_anonymous_role_1_action_step_parameter
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "action_step_parameter" ADD CONSTRAINT "cst_action_step_parameter_action_steps_action_steps" FOREIGN KEY ( "action_steps" ) REFERENCES "action_steps" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_2"
-- Aggregation type "none"
-- Primary table "action_step_transitions"
-- Primary column ""
-- Foreign table "action_steps"
-- Constraint name would be cst_action_steps_anonymous_role_2_action_step_transitions
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_action_steps_action_steps" FOREIGN KEY ( "action_steps" ) REFERENCES "action_steps" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_3"
-- Aggregation type "none"
-- Primary table "action_step_transitions"
-- Primary column ""
-- Foreign table "action_steps"
-- Constraint name would be cst_action_steps_anonymous_role_3_action_step_transitions
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "action_step_transitions" ADD CONSTRAINT "cst_action_step_transitions_action_steps_action_steps" FOREIGN KEY ( "action_steps" ) REFERENCES "action_steps" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "type"
-- Aggregation type "none"
-- Primary table "action_types"
-- Primary column ""
-- Foreign table "action_steps"
-- Constraint name would be cst_action_steps_type_action_types
-- Not Empty case 1
ALTER TABLE "action_steps" 
ADD CONSTRAINT "cst_action_steps_type_action_types" 
FOREIGN KEY ( "type" ) REFERENCES "action_types" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "actionid"
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "action_steps"
-- Constraint name would be cst_action_steps_actionid_actions
-- Not Empty case 1
ALTER TABLE "action_steps" 
ADD CONSTRAINT "cst_action_steps_actionid_actions" 
FOREIGN KEY ( "actionid" ) REFERENCES "actions" ( "ID" );

-- Generate MSSQL application relations for table action_types for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_4"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "action_types"
-- Constraint name would be cst_action_types_anonymous_role_4_action_steps
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_action_types_action_types" FOREIGN KEY ( "action_types" ) REFERENCES "action_types" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_5"
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "action_types"
-- Constraint name would be cst_action_types_anonymous_role_5_actions
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_action_types_action_types" FOREIGN KEY ( "action_types" ) REFERENCES "action_types" ( "ID" );

-- Generate MSSQL application relations for table actions for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "typ"
-- Aggregation type "none"
-- Primary table "action_types"
-- Primary column ""
-- Foreign table "actions"
-- Constraint name would be cst_actions_typ_action_types
-- Not Empty case 1
ALTER TABLE "actions" 
ADD CONSTRAINT "cst_actions_typ_action_types" 
FOREIGN KEY ( "typ" ) REFERENCES "action_types" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_6"
-- Aggregation type "none"
-- Primary table "action_parameters"
-- Primary column ""
-- Foreign table "actions"
-- Constraint name would be cst_actions_anonymous_role_6_action_parameters
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "action_parameters" ADD CONSTRAINT "cst_action_parameters_actions_actions" FOREIGN KEY ( "actions" ) REFERENCES "actions" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_7"
-- Aggregation type "none"
-- Primary table "action_steps"
-- Primary column ""
-- Foreign table "actions"
-- Constraint name would be cst_actions_anonymous_role_7_action_steps
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "action_steps" ADD CONSTRAINT "cst_action_steps_actions_actions" FOREIGN KEY ( "actions" ) REFERENCES "actions" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_8"
-- Aggregation type "none"
-- Primary table "formular_actions"
-- Primary column ""
-- Foreign table "actions"
-- Constraint name would be cst_actions_anonymous_role_8_formular_actions
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_actions_actions" FOREIGN KEY ( "actions" ) REFERENCES "actions" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungenid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "actions"
-- Constraint name would be cst_actions_anwendungenid_anwendungen
-- Not Empty case 1
ALTER TABLE "actions" 
ADD CONSTRAINT "cst_actions_anwendungenid_anwendungen" 
FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "ID" );

-- Generate MSSQL application relations for table anwendungen for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_9"
-- Aggregation type "none"
-- Primary table "anwendungen_formulare"
-- Primary column ""
-- Foreign table "anwendungen"
-- Constraint name would be cst_anwendungen_anonymous_role_9_anwendungen_formulare
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_anwendungen_anwendungen" FOREIGN KEY ( "anwendungen" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_10"
-- Aggregation type "none"
-- Primary table "anwendungs_parameter"
-- Primary column ""
-- Foreign table "anwendungen"
-- Constraint name would be cst_anwendungen_anonymous_role_10_anwendungs_parameter
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "anwendungs_parameter" ADD CONSTRAINT "cst_anwendungs_parameter_anwendungen_anwendungen" FOREIGN KEY ( "anwendungen" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_11"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "anwendungen"
-- Constraint name would be cst_anwendungen_anonymous_role_11_formulare
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_anwendungen_anwendungen" FOREIGN KEY ( "anwendungen" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_12"
-- Aggregation type "none"
-- Primary table "user_anwendungen"
-- Primary column ""
-- Foreign table "anwendungen"
-- Constraint name would be cst_anwendungen_anonymous_role_12_user_anwendungen
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_anwendungen_anwendungen" FOREIGN KEY ( "anwendungen" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_13"
-- Aggregation type "none"
-- Primary table "users"
-- Primary column ""
-- Foreign table "anwendungen"
-- Constraint name would be cst_anwendungen_anonymous_role_13_users
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "users" ADD CONSTRAINT "cst_users_anwendungen_anwendungen" FOREIGN KEY ( "anwendungen" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "anwendungen"
-- Constraint name would be cst_anwendungen__dbtable
-- Empty
-- Unclear case
--ALTER TABLE "dbtable" ADD CONSTRAINT "cst_dbtable_anwendungen_anwendungen" FOREIGN KEY ( "anwendungen" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "anwendungen"
-- Constraint name would be cst_anwendungen__actions
-- Empty
-- Unclear case
--ALTER TABLE "actions" ADD CONSTRAINT "cst_actions_anwendungen_anwendungen" FOREIGN KEY ( "anwendungen" ) REFERENCES "anwendungen" ( "ID" );

-- Generate MSSQL application relations for table anwendungen_formulare for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "anwendungen_formulare"
-- Constraint name would be cst_anwendungen_formulare_anwendungid_anwendungen
-- Not Empty case 1
ALTER TABLE "anwendungen_formulare" 
ADD CONSTRAINT "cst_anwendungen_formulare_anwendungid_anwendungen" 
FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularid"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "anwendungen_formulare"
-- Constraint name would be cst_anwendungen_formulare_formularid_formulare
-- Not Empty case 1
ALTER TABLE "anwendungen_formulare" 
ADD CONSTRAINT "cst_anwendungen_formulare_formularid_formulare" 
FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "ID" );

-- Generate MSSQL application relations for table anwendungs_parameter for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "anwendungs_parameter"
-- Constraint name would be cst_anwendungs_parameter_anwendungid_anwendungen
-- Not Empty case 1
ALTER TABLE "anwendungs_parameter" 
ADD CONSTRAINT "cst_anwendungs_parameter_anwendungid_anwendungen" 
FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "ID" );

-- Generate MSSQL application relations for table anwendungsberechtigungen for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "idformular"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "anwendungsberechtigungen"
-- Constraint name would be cst_anwendungsberechtigungen_idformular_formulare
-- Not Empty case 1
ALTER TABLE "anwendungsberechtigungen" 
ADD CONSTRAINT "cst_anwendungsberechtigungen_idformular_formulare" 
FOREIGN KEY ( "idformular" ) REFERENCES "formulare" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "iduser"
-- Aggregation type "none"
-- Primary table "users"
-- Primary column ""
-- Foreign table "anwendungsberechtigungen"
-- Constraint name would be cst_anwendungsberechtigungen_iduser_users
-- Not Empty case 1
ALTER TABLE "anwendungsberechtigungen" 
ADD CONSTRAINT "cst_anwendungsberechtigungen_iduser_users" 
FOREIGN KEY ( "iduser" ) REFERENCES "users" ( "ID" );

-- Generate MSSQL application relations for table applevel_plugin_registry for lbDMFManager_Entities
-- Generate MSSQL application relations for table codegentarget for lbDMFManager_Entities
-- Generate MSSQL application relations for table column_types for lbDMFManager_Entities
-- Generate MSSQL application relations for table foreignkey_visibledata_mapping for lbDMFManager_Entities
-- Generate MSSQL application relations for table formular_actions for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "action"
-- Aggregation type "none"
-- Primary table "actions"
-- Primary column ""
-- Foreign table "formular_actions"
-- Constraint name would be cst_formular_actions_action_actions
-- Not Empty case 1
ALTER TABLE "formular_actions" 
ADD CONSTRAINT "cst_formular_actions_action_actions" 
FOREIGN KEY ( "action" ) REFERENCES "actions" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formular"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "formular_actions"
-- Constraint name would be cst_formular_actions_formular_formulare
-- Not Empty case 1
ALTER TABLE "formular_actions" 
ADD CONSTRAINT "cst_formular_actions_formular_formulare" 
FOREIGN KEY ( "formular" ) REFERENCES "formulare" ( "ID" );

-- Generate MSSQL application relations for table formular_parameters for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularid"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "formular_parameters"
-- Constraint name would be cst_formular_parameters_formularid_formulare
-- Not Empty case 1
ALTER TABLE "formular_parameters" 
ADD CONSTRAINT "cst_formular_parameters_formularid_formulare" 
FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "ID" );

-- Generate MSSQL application relations for table formulare for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_anwendungid_anwendungen
-- Not Empty case 1
ALTER TABLE "formulare" 
ADD CONSTRAINT "cst_formulare_anwendungid_anwendungen" 
FOREIGN KEY ( "anwendungid" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_14"
-- Aggregation type "none"
-- Primary table "anwendungen_formulare"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_anonymous_role_14_anwendungen_formulare
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "anwendungen_formulare" ADD CONSTRAINT "cst_anwendungen_formulare_formulare_formulare" FOREIGN KEY ( "formulare" ) REFERENCES "formulare" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_15"
-- Aggregation type "none"
-- Primary table "anwendungsberechtigungen"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_anonymous_role_15_anwendungsberechtigungen
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_formulare_formulare" FOREIGN KEY ( "formulare" ) REFERENCES "formulare" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_16"
-- Aggregation type "none"
-- Primary table "formular_actions"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_anonymous_role_16_formular_actions
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "formular_actions" ADD CONSTRAINT "cst_formular_actions_formulare_formulare" FOREIGN KEY ( "formulare" ) REFERENCES "formulare" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_17"
-- Aggregation type "none"
-- Primary table "formular_parameters"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_anonymous_role_17_formular_parameters
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "formular_parameters" ADD CONSTRAINT "cst_formular_parameters_formulare_formulare" FOREIGN KEY ( "formulare" ) REFERENCES "formulare" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "typ"
-- Aggregation type "none"
-- Primary table "formulartypen"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare_typ_formulartypen
-- Not Empty case 1
ALTER TABLE "formulare" 
ADD CONSTRAINT "cst_formulare_typ_formulartypen" 
FOREIGN KEY ( "typ" ) REFERENCES "formulartypen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "formularfields"
-- Primary column ""
-- Foreign table "formulare"
-- Constraint name would be cst_formulare__formularfields
-- Empty
-- Unclear case
--ALTER TABLE "formularfields" ADD CONSTRAINT "cst_formularfields_formulare_formulare" FOREIGN KEY ( "formulare" ) REFERENCES "formulare" ( "ID" );

-- Generate MSSQL application relations for table formularfields for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularid"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "formularfields"
-- Constraint name would be cst_formularfields_formularid_formulare
-- Not Empty case 1
ALTER TABLE "formularfields" 
ADD CONSTRAINT "cst_formularfields_formularid_formulare" 
FOREIGN KEY ( "formularid" ) REFERENCES "formulare" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtypeid"
-- Aggregation type "none"
-- Primary table "dbtype"
-- Primary column ""
-- Foreign table "formularfields"
-- Constraint name would be cst_formularfields_dbtypeid_dbtype
-- Not Empty case 1
ALTER TABLE "formularfields" 
ADD CONSTRAINT "cst_formularfields_dbtypeid_dbtype" 
FOREIGN KEY ( "dbtypeid" ) REFERENCES "dbtype" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "formularfieldparameter"
-- Primary column ""
-- Foreign table "formularfields"
-- Constraint name would be cst_formularfields__formularfieldparameter
-- Empty
-- Unclear case
--ALTER TABLE "formularfieldparameter" ADD CONSTRAINT "cst_formularfieldparameter_formularfields_formularfields" FOREIGN KEY ( "formularfields" ) REFERENCES "formularfields" ( "ID" );

-- Generate MSSQL application relations for table formulartypen for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_18"
-- Aggregation type "none"
-- Primary table "formulare"
-- Primary column ""
-- Foreign table "formulartypen"
-- Constraint name would be cst_formulartypen_anonymous_role_18_formulare
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "formulare" ADD CONSTRAINT "cst_formulare_formulartypen_formulartypen" FOREIGN KEY ( "formulartypen" ) REFERENCES "formulartypen" ( "ID" );

-- Generate MSSQL application relations for table regressiontest for lbDMFManager_Entities
-- Generate MSSQL application relations for table report_element_types for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_19"
-- Aggregation type "none"
-- Primary table "report_elements"
-- Primary column ""
-- Foreign table "report_element_types"
-- Constraint name would be cst_report_element_types_anonymous_role_19_report_elements
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_report_element_types_report_element_types" FOREIGN KEY ( "report_element_types" ) REFERENCES "report_element_types" ( "ID" );

-- Generate MSSQL application relations for table report_elements for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "typ"
-- Aggregation type "none"
-- Primary table "report_element_types"
-- Primary column ""
-- Foreign table "report_elements"
-- Constraint name would be cst_report_elements_typ_report_element_types
-- Not Empty case 1
ALTER TABLE "report_elements" 
ADD CONSTRAINT "cst_report_elements_typ_report_element_types" 
FOREIGN KEY ( "typ" ) REFERENCES "report_element_types" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_20"
-- Aggregation type "none"
-- Primary table "report_texts"
-- Primary column ""
-- Foreign table "report_elements"
-- Constraint name would be cst_report_elements_anonymous_role_20_report_texts
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "report_texts" ADD CONSTRAINT "cst_report_texts_report_elements_report_elements" FOREIGN KEY ( "report_elements" ) REFERENCES "report_elements" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "reportid"
-- Aggregation type "none"
-- Primary table "reports"
-- Primary column ""
-- Foreign table "report_elements"
-- Constraint name would be cst_report_elements_reportid_reports
-- Not Empty case 1
ALTER TABLE "report_elements" 
ADD CONSTRAINT "cst_report_elements_reportid_reports" 
FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "ID" );

-- Generate MSSQL application relations for table report_parameters for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "reportid"
-- Aggregation type "none"
-- Primary table "reports"
-- Primary column ""
-- Foreign table "report_parameters"
-- Constraint name would be cst_report_parameters_reportid_reports
-- Not Empty case 1
ALTER TABLE "report_parameters" 
ADD CONSTRAINT "cst_report_parameters_reportid_reports" 
FOREIGN KEY ( "reportid" ) REFERENCES "reports" ( "ID" );

-- Generate MSSQL application relations for table report_texts for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "elementid"
-- Aggregation type "none"
-- Primary table "report_elements"
-- Primary column ""
-- Foreign table "report_texts"
-- Constraint name would be cst_report_texts_elementid_report_elements
-- Not Empty case 1
ALTER TABLE "report_texts" 
ADD CONSTRAINT "cst_report_texts_elementid_report_elements" 
FOREIGN KEY ( "elementid" ) REFERENCES "report_elements" ( "ID" );

-- Generate MSSQL application relations for table reports for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_21"
-- Aggregation type "none"
-- Primary table "report_elements"
-- Primary column ""
-- Foreign table "reports"
-- Constraint name would be cst_reports_anonymous_role_21_report_elements
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "report_elements" ADD CONSTRAINT "cst_report_elements_reports_reports" FOREIGN KEY ( "reports" ) REFERENCES "reports" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_22"
-- Aggregation type "none"
-- Primary table "report_parameters"
-- Primary column ""
-- Foreign table "reports"
-- Constraint name would be cst_reports_anonymous_role_22_report_parameters
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "report_parameters" ADD CONSTRAINT "cst_report_parameters_reports_reports" FOREIGN KEY ( "reports" ) REFERENCES "reports" ( "ID" );

-- Generate MSSQL application relations for table translations for lbDMFManager_Entities
-- Generate MSSQL application relations for table user_anwendungen for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungenid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "user_anwendungen"
-- Constraint name would be cst_user_anwendungen_anwendungenid_anwendungen
-- Not Empty case 1
ALTER TABLE "user_anwendungen" 
ADD CONSTRAINT "cst_user_anwendungen_anwendungenid_anwendungen" 
FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "userid"
-- Aggregation type "none"
-- Primary table "users"
-- Primary column ""
-- Foreign table "user_anwendungen"
-- Constraint name would be cst_user_anwendungen_userid_users
-- Not Empty case 1
ALTER TABLE "user_anwendungen" 
ADD CONSTRAINT "cst_user_anwendungen_userid_users" 
FOREIGN KEY ( "userid" ) REFERENCES "users" ( "ID" );

-- Generate MSSQL application relations for table users for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "lastapp"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "users"
-- Constraint name would be cst_users_lastapp_anwendungen
-- Not Empty case 1
ALTER TABLE "users" 
ADD CONSTRAINT "cst_users_lastapp_anwendungen" 
FOREIGN KEY ( "lastapp" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_23"
-- Aggregation type "none"
-- Primary table "anwendungsberechtigungen"
-- Primary column ""
-- Foreign table "users"
-- Constraint name would be cst_users_anonymous_role_23_anwendungsberechtigungen
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "anwendungsberechtigungen" ADD CONSTRAINT "cst_anwendungsberechtigungen_users_users" FOREIGN KEY ( "users" ) REFERENCES "users" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anonymous_role_24"
-- Aggregation type "none"
-- Primary table "user_anwendungen"
-- Primary column ""
-- Foreign table "users"
-- Constraint name would be cst_users_anonymous_role_24_user_anwendungen
-- Not Empty case 2
-- Unclear case
--ALTER TABLE "user_anwendungen" ADD CONSTRAINT "cst_user_anwendungen_users_users" FOREIGN KEY ( "users" ) REFERENCES "users" ( "ID" );

-- Generate MSSQL application relations for table dbtype for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "formularfields"
-- Primary column ""
-- Foreign table "dbtype"
-- Constraint name would be cst_dbtype__formularfields
-- Empty
-- Unclear case
--ALTER TABLE "formularfields" ADD CONSTRAINT "cst_formularfields_dbtype_dbtype" FOREIGN KEY ( "dbtype" ) REFERENCES "dbtype" ( "ID" );

-- Generate MSSQL application relations for table dbtable for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "dbprimarykey"
-- Primary column ""
-- Foreign table "dbtable"
-- Constraint name would be cst_dbtable__dbprimarykey
-- Empty
-- Unclear case
--ALTER TABLE "dbprimarykey" ADD CONSTRAINT "cst_dbprimarykey_dbtable_dbtable" FOREIGN KEY ( "dbtable" ) REFERENCES "dbtable" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "dbcolumn"
-- Primary column ""
-- Foreign table "dbtable"
-- Constraint name would be cst_dbtable__dbcolumn
-- Empty
-- Unclear case
--ALTER TABLE "dbcolumn" ADD CONSTRAINT "cst_dbcolumn_dbtable_dbtable" FOREIGN KEY ( "dbtable" ) REFERENCES "dbtable" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "dbforeignkey"
-- Primary column ""
-- Foreign table "dbtable"
-- Constraint name would be cst_dbtable__dbforeignkey
-- Empty
-- Unclear case
--ALTER TABLE "dbforeignkey" ADD CONSTRAINT "cst_dbforeignkey_dbtable_dbtable" FOREIGN KEY ( "dbtable" ) REFERENCES "dbtable" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "anwendungenid"
-- Aggregation type "none"
-- Primary table "anwendungen"
-- Primary column ""
-- Foreign table "dbtable"
-- Constraint name would be cst_dbtable_anwendungenid_anwendungen
-- Not Empty case 1
ALTER TABLE "dbtable" 
ADD CONSTRAINT "cst_dbtable_anwendungenid_anwendungen" 
FOREIGN KEY ( "anwendungenid" ) REFERENCES "anwendungen" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "dbtableparameter"
-- Primary column ""
-- Foreign table "dbtable"
-- Constraint name would be cst_dbtable__dbtableparameter
-- Empty
-- Unclear case
--ALTER TABLE "dbtableparameter" ADD CONSTRAINT "cst_dbtableparameter_dbtable_dbtable" FOREIGN KEY ( "dbtable" ) REFERENCES "dbtable" ( "ID" );

-- Generate MSSQL application relations for table dbcolumn for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbcolumn"
-- Constraint name would be cst_dbcolumn_dbtableid_dbtable
-- Not Empty case 1
ALTER TABLE "dbcolumn" 
ADD CONSTRAINT "cst_dbcolumn_dbtableid_dbtable" 
FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "ID" );
-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name ""
-- Aggregation type "none"
-- Primary table "dbcolumnparameter"
-- Primary column ""
-- Foreign table "dbcolumn"
-- Constraint name would be cst_dbcolumn__dbcolumnparameter
-- Empty
-- Unclear case
--ALTER TABLE "dbcolumnparameter" ADD CONSTRAINT "cst_dbcolumnparameter_dbcolumn_dbcolumn" FOREIGN KEY ( "dbcolumn" ) REFERENCES "dbcolumn" ( "ID" );

-- Generate MSSQL application relations for table dbforeignkey for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbforeignkey"
-- Constraint name would be cst_dbforeignkey_dbtableid_dbtable
-- Not Empty case 1
ALTER TABLE "dbforeignkey" 
ADD CONSTRAINT "cst_dbforeignkey_dbtableid_dbtable" 
FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "ID" );

-- Generate MSSQL application relations for table dbprimarykey for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbprimarykey"
-- Constraint name would be cst_dbprimarykey_dbtableid_dbtable
-- Not Empty case 1
ALTER TABLE "dbprimarykey" 
ADD CONSTRAINT "cst_dbprimarykey_dbtableid_dbtable" 
FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "ID" );

-- Unknown stereotype 'filterdefinition' for class UserFilter.

-- Generate application table UserFilter for lbDMFManager_Entities
-- Generate MSSQL application relations for table dbtableparameter for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbtableid"
-- Aggregation type "none"
-- Primary table "dbtable"
-- Primary column ""
-- Foreign table "dbtableparameter"
-- Constraint name would be cst_dbtableparameter_dbtableid_dbtable
-- Not Empty case 1
ALTER TABLE "dbtableparameter" 
ADD CONSTRAINT "cst_dbtableparameter_dbtableid_dbtable" 
FOREIGN KEY ( "dbtableid" ) REFERENCES "dbtable" ( "ID" );

-- Generate MSSQL application relations for table dbcolumnparameter for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "dbcolumnid"
-- Aggregation type "none"
-- Primary table "dbcolumn"
-- Primary column ""
-- Foreign table "dbcolumnparameter"
-- Constraint name would be cst_dbcolumnparameter_dbcolumnid_dbcolumn
-- Not Empty case 1
ALTER TABLE "dbcolumnparameter" 
ADD CONSTRAINT "cst_dbcolumnparameter_dbcolumnid_dbcolumn" 
FOREIGN KEY ( "dbcolumnid" ) REFERENCES "dbcolumn" ( "ID" );

-- Generate MSSQL application relations for table formularfieldparameter for lbDMFManager_Entities-- Unknown: Stereotype is '', backendType is ''
		
-- createDBType 
-- Check if name is empty to create automatic key field name
-- Element name "formularfieldid"
-- Aggregation type "none"
-- Primary table "formularfields"
-- Primary column ""
-- Foreign table "formularfieldparameter"
-- Constraint name would be cst_formularfieldparameter_formularfieldid_formularfields
-- Not Empty case 1
ALTER TABLE "formularfieldparameter" 
ADD CONSTRAINT "cst_formularfieldparameter_formularfieldid_formularfields" 
FOREIGN KEY ( "formularfieldid" ) REFERENCES "formularfields" ( "ID" );

exec lbDMF_DropProc 'lbDMF_DropTable'
GO

exec lbDMF_DropProc 'lbDMF_DropProc'
GO


-- Script ready.
COMMIT;



-- Speedup many times
BEGIN TRANSACTION;


-- Params XSLDatabaseBackendSystem: MSSQL
-- Params XSLDatabaseBackendApplication: MSSQL
-- Params overwriteDatabase: yes

-- Params targetdatabase generated: MSSQL

--
-- SQL script created for MSSQL
--

		
		
-- Application is lbDMF Manager. Package is lbDMF Manager
-- Using database settings as of name=lbDMF, user=db_ac3473_site1_admin

-- Create default stored procedures for MSSQL. Version ignored.

	
IF OBJECT_ID('DropTable', 'P') IS NOT NULL
    DROP PROCEDURE DropTable;
GO

CREATE PROCEDURE DropTable @Table VARCHAR(50)
AS
BEGIN
	DECLARE @Statement VARCHAR(200)
	DECLARE hSqlProc CURSOR LOCAL FOR
		SELECT 'DROP TABLE ' + pr.name
		FROM sysobjects pr
		WHERE pr.xtype IN ('U') AND upper(pr.name) = upper(@Table)
		
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
GO

IF OBJECT_ID('DropProc', 'P') IS NOT NULL
    DROP PROCEDURE DropProc;
GO

CREATE  PROCEDURE DropProc @Proc VARCHAR(50)
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
GO

IF OBJECT_ID('getorcreateapplication', 'P') IS NOT NULL
    DROP PROCEDURE getorcreateapplication;
GO

CREATE PROCEDURE getorcreateapplication
    @applicationname VARCHAR(255)
AS
BEGIN
    SET NOCOUNT ON;
    DECLARE @applicationid INT;
    DECLARE @uid INT;

    -- 1. Check if application already exists
    SELECT @applicationid = id 
    FROM anwendungen 
    WHERE name = @applicationname;

    IF @applicationid IS NOT NULL
    BEGIN
        SELECT @applicationid AS Result;
        RETURN @applicationid;
    END

    -- 2. Insert new application
    -- SQL Server uses '+' for concatenation instead of '||'
    INSERT INTO anwendungen (name, titel, modulename, functor, interface) 
    VALUES (@applicationname, 'Application ' + @applicationname, 'lbDynApp', 'instanceOfApplication', 'lb_I_Application');

    -- Get the ID of the record just inserted
    SET @applicationid = SCOPE_IDENTITY();

    -- 3. Check for 'user' and initialize default system data if missing
    SELECT @uid = id FROM users WHERE userid = 'user';

    IF @uid IS NULL
    BEGIN
        INSERT INTO "users" (userid, passwort, lastapp) 
        VALUES ('user', 'TestUser', (SELECT id FROM "anwendungen" WHERE "name" = 'lbDMF Manager'));

        SET @uid = SCOPE_IDENTITY();

        INSERT INTO "formulartypen" ("handlerinterface", "namespace", "handlermodule", "handlerfunctor", "beschreibung") 
        VALUES ('lb_I_DatabaseForm','','-','','Dynamisch aufgebautes Datenbankformular');

        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Buttonpress', '', '');
        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('SQL query', 'instanceOflbSQLQueryAction', 'lbWorkflowEngine');
        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open form', 'instanceOflbFormAction', 'lbDatabaseForm');
        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open detail form', 'instanceOflbDetailFormAction', 'lbWorkflowEngine');
        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open master form', 'instanceOflbMasterFormAction', 'lbWorkflowEngine');
        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('CreateReport', 'instanceOflbExecuteAction', 'lbDatabaseForm');
        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Open Database Report', 'instanceOflbDBReportAction', 'lbDatabaseReport');
        INSERT INTO "action_types" (bezeichnung, action_handler, module) VALUES ('Perform XSLT transformation', 'instanceOflbDMFXslt', 'lbDMFXslt');
        INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('FormValidator', '', '');
        INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('InitialNode', '', '');
        INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('SendSignalAction', 'instanceOflbSendSignalAction', 'lbDMFBasicActionSteps');
        INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('DecisionNode', 'instanceOflbDecisionAction', 'lbDMFBasicActionSteps');
        INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('OpaqueAction', 'instanceOflbOpAqueOperation', 'lbWorkflowEngine');
        INSERT INTO "action_types" ("bezeichnung", "action_handler", "module") VALUES ('FinalNode', '', '');
    END

    -- 4. Associate User with Application
    INSERT INTO user_anwendungen (userid, anwendungenid) 
    VALUES (@uid, @applicationid);

    -- 5. Insert Parameters
    IF @applicationname = 'lbDMF Manager'
    BEGIN
        INSERT INTO anwendungs_parameter (parametername, parametervalue, anwendungid) VALUES('DBName', 'lbDMF', @applicationid);
        INSERT INTO anwendungs_parameter (parametername, parametervalue, anwendungid) VALUES('DBUser', 'dba', @applicationid);
        INSERT INTO anwendungs_parameter (parametername, parametervalue, anwendungid) VALUES('DBPass', 'trainres', @applicationid);
    END
    ELSE
    BEGIN
        INSERT INTO anwendungs_parameter (parametername, parametervalue, anwendungid) VALUES('DBName', 'lbDMF', @applicationid);
        INSERT INTO anwendungs_parameter (parametername, parametervalue, anwendungid) VALUES('DBUser', 'db_ac3473_site1_admin', @applicationid);
        INSERT INTO anwendungs_parameter (parametername, parametervalue, anwendungid) VALUES('DBPass', 'GTuF$Ni$Nek75', @applicationid);
    END

    SELECT @applicationid AS Result;
    RETURN @applicationid;
END;
GO

IF OBJECT_ID('getapplication', 'P') IS NOT NULL
    DROP PROCEDURE getapplication;
GO

CREATE PROC getapplication(@FNName varchar) AS
BEGIN
  declare @applicationid int;
  declare @uid int;
  declare @applicationname char(100);

  set @applicationname = @FNName;
  set @applicationid = (select id from anwendungen where name = @applicationname);
  if not @applicationid is null 
  begin
    return @applicationid
  end
  if @applicationid is null
  begin
	exec ('exec createapplication ' + @FNName)
  end
  set @applicationid = ('exec getapplication ' + @FNName)
  Select @applicationid
end
GO

IF OBJECT_ID('DropFormular', 'P') IS NOT NULL
    DROP PROCEDURE DropFormular;
GO

CREATE PROCEDURE DropFormular
    @appname NVARCHAR(255),
    @formname NVARCHAR(255),
    @success BIT OUTPUT -- Returns 1 for true, 0 for false
AS
BEGIN
    SET NOCOUNT ON;
    DECLARE @appid INT;
    DECLARE @formid INT;

    -- 1. Look up the IDs
    SELECT @appid = id FROM anwendungen WHERE name = @appname;
    SELECT @formid = id FROM formulare WHERE name = @formname AND anwendungid = @appid;

    -- 2. Exit early if either ID is missing
    IF @appid IS NULL OR @formid IS NULL
    BEGIN
        SET @success = 0;
        RETURN;
    END

    BEGIN TRY
        BEGIN TRANSACTION;

        -- 3. Perform deletions in order of dependency
        DELETE FROM formular_parameters WHERE formularid = @formid;
        DELETE FROM anwendungen_formulare WHERE anwendungid = @appid AND formularid = @formid;
        DELETE FROM formular_actions WHERE formular = @formid;
        DELETE FROM formulare WHERE anwendungid = @appid AND id = @formid;

        COMMIT TRANSACTION;
        SET @success = 1;
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0 ROLLBACK TRANSACTION;
        SET @success = 0;
        -- Optional: THROW; 
    END CATCH
END;
GO

/*
CREATE FUNCTION getorcreateactiontype(varchar)
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
*/
			
		
declare @Success bit	

exec getorcreateapplication 'lbDMF Manager'

	
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
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('ProductVersion', '1.0.7.0', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('LoggingNamespaceName', 'Lollisoft', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('DataStoreBaseAddress', 'net.tcp://cloud.lollisoft.de:49381', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('LoggingStrategy', 'client', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('UpgradeCode', '48dc066c-97cc-4512-8fa3-52bbe195e075', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('StsBaseAddress', 'net.tcp://cloud.lollisoft.de:8000', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('ProductCode', '5494B76A-60ED-4DB1-94D4-3C44FF658F9F', (select id from anwendungen where name = 'lbDMF Manager'));
		
insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values('LoggingImplementation', 'client', (select id from anwendungen where name = 'lbDMF Manager'));
		
		-- Class Anwendungen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Anwendungen', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungen', 'Anwendungen verwalten', 'manageAnwendungen', 'Edit data of Anwendungen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen', 'requirements', 'richtext', '');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen', 'background', 'richtext', '');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen', 'model_errors', 'bigstring', '');


-- Create query for anwendungen (BOUML_0x1f682_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "titel", "name", "interface", "functor", "modulename", "requirements", "background", "model_complete", "model_errors" from "anwendungen"', id FROM "formulare" WHERE name = 'Anwendungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungen', 1);


-- Association from Anwendungen to Anwendungsparameter

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21682_0'.
	

-- Select action type IsMasterDetail: BOUML_0x21682_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x21682_0
insert into actions (name, typ, source) values ('Anwendungsparameter', 1, 'BOUML_0x21682_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungsparameter', 1, 'Anwendungsparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Anwendungsparameter' and source = 'BOUML_0x21682_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Anwendungsparameter' and source = 'BOUML_0x21682_0'), 'action_master_detail_BOUML_0x21682_0');

update actions set source = '' where source = 'BOUML_0x21682_0';

	
-- Association from Anwendungen to Formulare

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21702_0'.
	

-- Select action type IsMasterDetail: BOUML_0x21702_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x21702_0
insert into actions (name, typ, source) values ('Formulare', 1, 'BOUML_0x21702_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formulare' and source = 'BOUML_0x21702_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formulare' and source = 'BOUML_0x21702_0'), 'action_master_detail_BOUML_0x21702_0');

update actions set source = '' where source = 'BOUML_0x21702_0';

	
-- Association from Anwendungen to Tables

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2d202_0'.
	

-- Select action type IsMasterDetail: BOUML_0x2d202_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x2d202_0
insert into actions (name, typ, source) values ('Tables', 1, 'BOUML_0x2d202_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Tables', 1, 'Tables', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Tables' and source = 'BOUML_0x2d202_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Tables' and source = 'BOUML_0x2d202_0'), 'action_master_detail_BOUML_0x2d202_0');

update actions set source = '' where source = 'BOUML_0x2d202_0';

	

-- Create operation definitions

-- Generate codegeneration operation 'Codegenerieren' for 'Anwendungen'

INSERT INTO "actions" (name, typ, source) VALUES ('Codegenerieren', (select id from action_types where bezeichnung = 'Buttonpress'), 'name');
INSERT INTO "action_steps" (bezeichnung, a_order_nr, what, type, actionid) VALUES ('Generate code', 1, 'lala', (select id from action_types where action_handler = 'instanceOflbDMFXslt'), (select id from actions where name = 'Codegenerieren'));
INSERT INTO "formular_actions" (formular, action, event) VALUES ((select id from formulare where name = 'Anwendungen'), (select id from actions where name = 'Codegenerieren'), 'evt_Anwendungen_Codegenerieren');

	
INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formulare of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Formulare', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formulare', 'Formulare verwalten', 'manageFormulare', 'Edit data of Formulare', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'anwendungid', 'anwendungen', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formulare', 'typ', 'formulartypen', 'beschreibung');


-- Create query for formulare (BOUML_0x1f482_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "menuname", "menuhilfe", "eventname", "toolbarimage", "anwendungid", "typ" from "formulare"', id FROM "formulare" WHERE name = 'Formulare' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Formulare', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Formulare', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Formulare', 1);


INSERT INTO "column_types" (name, tablename, specialcolumn, controltype) values ('toolbarimage', 'Formulare', 1, 'toolbarimagefile');

-- Association from Formulare to Formular_Parameter

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21802_0'.
	

-- Select action type IsMasterDetail: BOUML_0x21802_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x21802_0
insert into actions (name, typ, source) values ('Formular_Parameter', 1, 'BOUML_0x21802_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formular_Parameter', 1, 'Formular_Parameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formular_Parameter' and source = 'BOUML_0x21802_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formular_Parameter' and source = 'BOUML_0x21802_0'), 'action_master_detail_BOUML_0x21802_0');

update actions set source = '' where source = 'BOUML_0x21802_0';

	
-- Association from Formulare to Formularaktionenzuordnen

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21882_0'.
	

-- Select action type IsMasterDetail: BOUML_0x21882_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x21882_0
insert into actions (name, typ, source) values ('Formularaktionenzuordnen', 1, 'BOUML_0x21882_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formularaktionenzuordnen', 1, 'Formularaktionenzuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formularaktionenzuordnen' and source = 'BOUML_0x21882_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formularaktionenzuordnen' and source = 'BOUML_0x21882_0'), 'action_master_detail_BOUML_0x21882_0');

update actions set source = '' where source = 'BOUML_0x21882_0';

	
-- Association from Formulare to FormularFields

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x25e02_0'.
	

-- Select action type IsMasterDetail: BOUML_0x25e02_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x25e02_0
insert into actions (name, typ, source) values ('Fields', 1, 'BOUML_0x25e02_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Fields', 1, 'FormularFields', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Fields' and source = 'BOUML_0x25e02_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Fields' and source = 'BOUML_0x25e02_0'), 'action_master_detail_BOUML_0x25e02_0');

update actions set source = '' where source = 'BOUML_0x25e02_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formulare' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class FormularFields of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'FormularFields', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularFields', 'FormularFields verwalten', 'manageFormularFields', 'Edit data of FormularFields', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'formularid', 'formulare', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfields', 'dbtypeid', 'dbtype', 'name');


-- Create query for formularfields (BOUML_0x24b02_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "dbtype", "tablename", "isfk", "fkname", "fktable", "formularid", "dbtypeid" from "formularfields"', id FROM "formulare" WHERE name = 'FormularFields' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'FormularFields', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'FormularFields', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'FormularFields', 1);


-- Association from FormularFields to DBType

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x25f02_0'.
	

-- Select action type IsMasterDetail: BOUML_0x25f02_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x25f02_0
insert into actions (name, typ, source) values ('DBType', 1, 'BOUML_0x25f02_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for DBType', 1, 'DBType', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'DBType' and source = 'BOUML_0x25f02_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'DBType' and source = 'BOUML_0x25f02_0'), 'action_master_detail_BOUML_0x25f02_0');

update actions set source = '' where source = 'BOUML_0x25f02_0';

	
-- Association from FormularFields to FormularFieldParameter

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x3d782_0'.
	

-- Select action type IsMasterDetail: BOUML_0x3d782_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x3d782_0
insert into actions (name, typ, source) values ('Parameter', 1, 'BOUML_0x3d782_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Parameter', 1, 'FormularFieldParameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Parameter' and source = 'BOUML_0x3d782_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Parameter' and source = 'BOUML_0x3d782_0'), 'action_master_detail_BOUML_0x3d782_0');

update actions set source = '' where source = 'BOUML_0x3d782_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularFields' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Benutzer of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Benutzer', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Benutzer', 'Benutzer verwalten', 'manageBenutzer', 'Edit data of Benutzer', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


-- Create query for users (BOUML_0x1f402_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "passwort", "userid", "vorname", "name" from "users"', id FROM "formulare" WHERE name = 'Benutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Benutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Benutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Benutzer', 1);


-- Association from Benutzer to AnwendungenBenutzer

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21782_0'.
	

-- Select action type IsMasterDetail: BOUML_0x21782_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x21782_0
insert into actions (name, typ, source) values ('AnwendungenBenutzer', 1, 'BOUML_0x21782_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for AnwendungenBenutzer', 1, 'AnwendungenBenutzer', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'AnwendungenBenutzer' and source = 'BOUML_0x21782_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'AnwendungenBenutzer' and source = 'BOUML_0x21782_0'), 'action_master_detail_BOUML_0x21782_0');

update actions set source = '' where source = 'BOUML_0x21782_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Benutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class DBType of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'DBType', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'DBType', 'DBType verwalten', 'manageDBType', 'Edit data of DBType', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


-- Create query for dbtype (BOUML_0x24b82_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "name", "description" from "dbtype"', id FROM "formulare" WHERE name = 'DBType' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'DBType', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'DBType', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'DBType', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'DBType' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formular_Parameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Formular_Parameter', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formular_Parameter', 'Formular_Parameter verwalten', 'manageFormular_Parameter', 'Edit data of Formular_Parameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_parameters', 'formularid', 'formulare', 'name');


-- Create query for formular_parameters (BOUML_0x1f502_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername", "formularid" from "formular_parameters"', id FROM "formulare" WHERE name = 'Formular_Parameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Formular_Parameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Formular_Parameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Formular_Parameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formular_Parameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class AnwendungenBenutzer of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'AnwendungenBenutzer', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'AnwendungenBenutzer', 'AnwendungenBenutzer verwalten', 'manageAnwendungenBenutzer', 'Edit data of AnwendungenBenutzer', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'userid', 'users', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('user_anwendungen', 'anwendungenid', 'anwendungen', 'name');


-- Create query for user_anwendungen (BOUML_0x1f582_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "userid", "anwendungenid" from "user_anwendungen"', id FROM "formulare" WHERE name = 'AnwendungenBenutzer' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'AnwendungenBenutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'AnwendungenBenutzer', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'AnwendungenBenutzer', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'AnwendungenBenutzer' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class FormulareAnwendung of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'FormulareAnwendung', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormulareAnwendung', 'FormulareAnwendung verwalten', 'manageFormulareAnwendung', 'Edit data of FormulareAnwendung', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'anwendungid', 'anwendungen', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungen_formulare', 'formularid', 'formulare', 'name');


-- Create query for anwendungen_formulare (BOUML_0x1f602_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "anwendungid", "formularid", "purpose" from "anwendungen_formulare"', id FROM "formulare" WHERE name = 'FormulareAnwendung' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'FormulareAnwendung', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'FormulareAnwendung', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'FormulareAnwendung', 1);


-- Association from FormulareAnwendung to Formulare

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29402_0'.
	

-- Select action type IsMasterDetail: BOUML_0x29402_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x29402_0
insert into actions (name, typ, source) values ('Formulare', 1, 'BOUML_0x29402_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formulare' and source = 'BOUML_0x29402_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formulare' and source = 'BOUML_0x29402_0'), 'action_master_detail_BOUML_0x29402_0');

update actions set source = '' where source = 'BOUML_0x29402_0';

	
-- Association from FormulareAnwendung to Anwendungen

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29482_0'.
	

-- Select action type IsMasterDetail: BOUML_0x29482_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x29482_0
insert into actions (name, typ, source) values ('Anwendungen', 1, 'BOUML_0x29482_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Anwendungen', 1, 'Anwendungen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Anwendungen' and source = 'BOUML_0x29482_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Anwendungen' and source = 'BOUML_0x29482_0'), 'action_master_detail_BOUML_0x29482_0');

update actions set source = '' where source = 'BOUML_0x29482_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormulareAnwendung' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Aktionen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Aktionen', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionen', 'Aktionen verwalten', 'manageAktionen', 'Edit data of Aktionen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'typ', 'action_types', 'bezeichnung');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('actions', 'anwendungenid', 'anwendungen', 'name');


-- Create query for actions (BOUML_0x1f702_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "target", "source", "name", "typ", "anwendungenid" from "actions"', id FROM "formulare" WHERE name = 'Aktionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Aktionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionen', 1);


-- Association from Aktionen to Aktionsschrittezuordnen

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21602_0'.
	

-- Select action type IsMasterDetail: BOUML_0x21602_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x21602_0
insert into actions (name, typ, source) values ('Aktionsschrittezuordnen', 1, 'BOUML_0x21602_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Aktionsschrittezuordnen', 1, 'Aktionsschrittezuordnen', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'BOUML_0x21602_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Aktionsschrittezuordnen' and source = 'BOUML_0x21602_0'), 'action_master_detail_BOUML_0x21602_0');

update actions set source = '' where source = 'BOUML_0x21602_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Uebersetzungen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Uebersetzungen', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Uebersetzungen', 'Uebersetzungen verwalten', 'manageUebersetzungen', 'Edit data of Uebersetzungen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


-- Create query for translations (BOUML_0x1f782_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "translated", "text" from "translations"', id FROM "formulare" WHERE name = 'Uebersetzungen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Uebersetzungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Uebersetzungen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Uebersetzungen', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Uebersetzungen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Formularaktionenzuordnen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Formularaktionenzuordnen', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Formularaktionenzuordnen', 'Formularaktionenzuordnen verwalten', 'manageFormularaktionenzuordnen', 'Edit data of Formularaktionenzuordnen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'action', 'actions', 'name');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formular_actions', 'formular', 'formulare', 'name');


-- Create query for formular_actions (BOUML_0x1f802_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "event", "action", "formular" from "formular_actions"', id FROM "formulare" WHERE name = 'Formularaktionenzuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Formularaktionenzuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Formularaktionenzuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Formularaktionenzuordnen', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Formularaktionenzuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Anwendungsparameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Anwendungsparameter', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Anwendungsparameter', 'Anwendungsparameter verwalten', 'manageAnwendungsparameter', 'Edit data of Anwendungsparameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('anwendungs_parameter', 'anwendungid', 'anwendungen', 'name');


-- Create query for anwendungs_parameter (BOUML_0x1f882_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametervalue", "parametername", "anwendungid" from "anwendungs_parameter"', id FROM "formulare" WHERE name = 'Anwendungsparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Anwendungsparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Anwendungsparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Anwendungsparameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Anwendungsparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Aktionsschrittezuordnen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Aktionsschrittezuordnen', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Aktionsschrittezuordnen', 'Aktionsschrittezuordnen verwalten', 'manageAktionsschrittezuordnen', 'Edit data of Aktionsschrittezuordnen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'type', 'action_types', 'bezeichnung');

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('action_steps', 'actionid', 'actions', 'name');


-- Create query for action_steps (BOUML_0x1f902_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "bezeichnung", "what", "a_order_nr", "type", "actionid" from "action_steps"', id FROM "formulare" WHERE name = 'Aktionsschrittezuordnen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Aktionsschrittezuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Aktionsschrittezuordnen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Aktionsschrittezuordnen', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Aktionsschrittezuordnen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Reportdefinitionen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Reportdefinitionen', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportdefinitionen', 'Reportdefinitionen verwalten', 'manageReportdefinitionen', 'Edit data of Reportdefinitionen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


-- Create query for reports (BOUML_0x1f982_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "description", "name" from "reports"', id FROM "formulare" WHERE name = 'Reportdefinitionen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Reportdefinitionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Reportdefinitionen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Reportdefinitionen', 1);


-- Association from Reportdefinitionen to Reportparameter

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x21902_0'.
	

-- Select action type IsMasterDetail: BOUML_0x21902_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x21902_0
insert into actions (name, typ, source) values ('Reportparameter', 1, 'BOUML_0x21902_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Reportparameter', 1, 'Reportparameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Reportparameter' and source = 'BOUML_0x21902_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Reportparameter' and source = 'BOUML_0x21902_0'), 'action_master_detail_BOUML_0x21902_0');

update actions set source = '' where source = 'BOUML_0x21902_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportdefinitionen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Reportparameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Reportparameter', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Reportparameter', 'Reportparameter verwalten', 'manageReportparameter', 'Edit data of Reportparameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('report_parameters', 'reportid', 'reports', 'name');


-- Create query for report_parameters (BOUML_0x1fa02_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "value", "name", "reportid" from "report_parameters"', id FROM "formulare" WHERE name = 'Reportparameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Reportparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Reportparameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Reportparameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Reportparameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class FormularTypen of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'FormularTypen', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularTypen', 'FormularTypen verwalten', 'manageFormularTypen', 'Edit data of FormularTypen', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


-- Create query for formulartypen (BOUML_0x26502_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "handlername", "handlerfunctor", "handlerintarface", "namespace", "beschreibung" from "formulartypen"', id FROM "formulare" WHERE name = 'FormularTypen' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'FormularTypen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'FormularTypen', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'FormularTypen', 1);


-- Association from FormularTypen to Formulare

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x29582_0'.
	

-- Select action type IsMasterDetail: BOUML_0x29582_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x29582_0
insert into actions (name, typ, source) values ('Formulare', 1, 'BOUML_0x29582_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Formulare', 1, 'Formulare', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Formulare' and source = 'BOUML_0x29582_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'FormularTypen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Formulare' and source = 'BOUML_0x29582_0'), 'action_master_detail_BOUML_0x29582_0');

update actions set source = '' where source = 'BOUML_0x29582_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularTypen' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Tables of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Tables', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Tables', 'Tables verwalten', 'manageTables', 'Edit data of Tables', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbtable', 'anwendungenid', 'anwendungen', 'name');


-- Create query for dbtable (BOUML_0x28082_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "catalogname", "schemaname", "tablename", "tabletype", "tableremarks", "anwendungenid" from "dbtable"', id FROM "formulare" WHERE name = 'Tables' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Tables', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Tables', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Tables', 1);


-- Association from Tables to Columns

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b402_0'.
	

-- Select action type IsMasterDetail: BOUML_0x2b402_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x2b402_0
insert into actions (name, typ, source) values ('Columns', 1, 'BOUML_0x2b402_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Columns', 1, 'Columns', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Columns' and source = 'BOUML_0x2b402_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Columns' and source = 'BOUML_0x2b402_0'), 'action_master_detail_BOUML_0x2b402_0');

update actions set source = '' where source = 'BOUML_0x2b402_0';

	
-- Association from Tables to PrimaryKeys

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b582_0'.
	

-- Select action type IsMasterDetail: BOUML_0x2b582_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x2b582_0
insert into actions (name, typ, source) values ('PrimaryKeys', 1, 'BOUML_0x2b582_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for PrimaryKeys', 1, 'PrimaryKeys', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'PrimaryKeys' and source = 'BOUML_0x2b582_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'PrimaryKeys' and source = 'BOUML_0x2b582_0'), 'action_master_detail_BOUML_0x2b582_0');

update actions set source = '' where source = 'BOUML_0x2b582_0';

	
-- Association from Tables to ForeignKeys

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x2b602_0'.
	

-- Select action type IsMasterDetail: BOUML_0x2b602_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x2b602_0
insert into actions (name, typ, source) values ('ForeignKeys', 1, 'BOUML_0x2b602_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for ForeignKeys', 1, 'ForeignKeys', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'ForeignKeys' and source = 'BOUML_0x2b602_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'ForeignKeys' and source = 'BOUML_0x2b602_0'), 'action_master_detail_BOUML_0x2b602_0');

update actions set source = '' where source = 'BOUML_0x2b602_0';

	
-- Association from Tables to TableParameter

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x37002_0'.
	

-- Select action type IsMasterDetail: BOUML_0x37002_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x37002_0
insert into actions (name, typ, source) values ('TableParameter', 1, 'BOUML_0x37002_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for TableParameter', 1, 'TableParameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'TableParameter' and source = 'BOUML_0x37002_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'TableParameter' and source = 'BOUML_0x37002_0'), 'action_master_detail_BOUML_0x37002_0');

update actions set source = '' where source = 'BOUML_0x37002_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Tables' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class Columns of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'Columns', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'Columns', 'Columns verwalten', 'manageColumns', 'Edit data of Columns', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbcolumn', 'dbtableid', 'dbtable', '');


-- Create query for dbcolumn (BOUML_0x28102_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "columnname", "columnremarks", "typename", "columnsize", "nullable", "tablename", "dbtableid" from "dbcolumn"', id FROM "formulare" WHERE name = 'Columns' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'Columns', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'Columns', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'Columns', 1);


-- Association from Columns to ColumnParameter

-- Create SQLSERVER based action
-- Select action type ActionType: lbDMF:masterdetail_action, Property: 'BOUML_0x3d802_0'.
	

-- Select action type IsMasterDetail: BOUML_0x3d802_0, IsDetailMaster: 
-- Build up a master detail action

-- STELT_BOUML_0x3d802_0
insert into actions (name, typ, source) values ('Parameter', 1, 'BOUML_0x3d802_0');	
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values ('Master detail action for Parameter', 1, 'ColumnParameter', (select id from action_types where bezeichnung = 'Open detail form'), (select id from actions where name = 'Parameter' and source = 'BOUML_0x3d802_0'));insert into formular_actions (formular, action, event) VALUES ((SELECT id FROM "formulare" WHERE "name" = 'Columns' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager')), (select id from actions where name = 'Parameter' and source = 'BOUML_0x3d802_0'), 'action_master_detail_BOUML_0x3d802_0');

update actions set source = '' where source = 'BOUML_0x3d802_0';

	

-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'Columns' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class PrimaryKeys of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'PrimaryKeys', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'PrimaryKeys', 'PrimaryKeys verwalten', 'managePrimaryKeys', 'Edit data of PrimaryKeys', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbprimarykey', 'dbtableid', 'dbtable', '');


-- Create query for dbprimarykey (BOUML_0x28202_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "tablecatalog", "tableschema", "tablename", "columnname", "columnname2", "keysequence", "dbtableid" from "dbprimarykey"', id FROM "formulare" WHERE name = 'PrimaryKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'PrimaryKeys', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'PrimaryKeys', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'PrimaryKeys', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'PrimaryKeys' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class ForeignKeys of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'ForeignKeys', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ForeignKeys', 'ForeignKeys verwalten', 'manageForeignKeys', 'Edit data of ForeignKeys', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbforeignkey', 'dbtableid', 'dbtable', '');


-- Create query for dbforeignkey (BOUML_0x28182_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "pkcatalog", "pkschema", "pktable", "pkcolumn", "fkcatalog", "fkschema", "fktable", "fkcolumn", "dbtableid" from "dbforeignkey"', id FROM "formulare" WHERE name = 'ForeignKeys' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'ForeignKeys', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'ForeignKeys', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'ForeignKeys', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ForeignKeys' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class TableParameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'TableParameter', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'TableParameter', 'TableParameter verwalten', 'manageTableParameter', 'Edit data of TableParameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';


-- Create query for dbtableparameter (BOUML_0x30382_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "tableid" from "dbtableparameter"', id FROM "formulare" WHERE name = 'TableParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'TableParameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'TableParameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'TableParameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'TableParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class ColumnParameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'ColumnParameter', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'ColumnParameter', 'ColumnParameter verwalten', 'manageColumnParameter', 'Edit data of ColumnParameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('dbcolumnparameter', 'dbcolumnid', 'dbcolumn', '');


-- Create query for dbcolumnparameter (BOUML_0x31d82_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "dbcolumnid" from "dbcolumnparameter"', id FROM "formulare" WHERE name = 'ColumnParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'ColumnParameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'ColumnParameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'ColumnParameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'ColumnParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

		-- Class FormularFieldParameter of type FORM found.

-- Generate DMF form definition for lbDMF Manager in MSSQL database


exec DropFormular 'lbDMF Manager', 'FormularFieldParameter', @Success


INSERT INTO "formulare" (name, menuname, eventname, menuhilfe, toolbarimage, anwendungid, typ) select 'FormularFieldParameter', 'FormularFieldParameter verwalten', 'manageFormularFieldParameter', 'Edit data of FormularFieldParameter', '', id, 1 FROM "anwendungen" where name = 'lbDMF Manager';

INSERT INTO "foreignkey_visibledata_mapping" ("fktable", "fkname", "pktable", "pkname") VALUES ('formularfieldparameter', 'formularfieldid', 'formularfields', '');


-- Create query for formularfieldparameter (BOUML_0x33702_4)
INSERT INTO "formular_parameters" (parametername, parametervalue, formularid)
SELECT 'query', 'select "parametername", "parametervalue", "formularfieldid" from "formularfieldparameter"', id FROM "formulare" WHERE name = 'FormularFieldParameter' and anwendungid in (select id from anwendungen where name = 'lbDMF Manager');

INSERT INTO "column_types" (name, tablename, ro) values ('ID', 'FormularFieldParameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('id', 'FormularFieldParameter', 1);
INSERT INTO "column_types" (name, tablename, ro) values ('Id', 'FormularFieldParameter', 1);



-- Create operation definitions

INSERT INTO "anwendungen_formulare" (anwendungid, formularid) SELECT anwendungid, id FROM "formulare" WHERE "name" = 'FormularFieldParameter' AND "anwendungid" IN (SELECT id  FROM "anwendungen" WHERE "name" = 'lbDMF Manager');

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


INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'id', 'BOUML_0x22602_1', 'int4', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametername', 'BOUML_0x22682_1', 'bpchar', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'parametervalue', 'BOUML_0x22702_1', 'bpchar', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

INSERT INTO dbcolumn (columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid) select 'formularid', 'BOUML_0x20e82_0', 'int4', -1, 0, 'formular_parameters', id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';
	
	
INSERT INTO dbprimarykey (tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid) select '', '', 'formular_parameters', 'id',  '', 0, id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';


INSERT INTO dbforeignkey (pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid) 
select '', '', 'formulare', 'id', '', '', 'formular_parameters', 'formularid', 0, 0, 0, id from dbtable where tablename = 'formular_parameters' AND tableremarks = 'BOUML_0x20302_4';

		-- Class formulare of type ENTITY found.

INSERT INTO dbtable (catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid) select '', '', 'formulare', '', 'BOUML_0x20382_4', id from anwendungen where name = 'lbDMF Manager';


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
			
-- Create activity nodes for Sqlite

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x22982_70', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x22a02_72', '2', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24202_56', '3', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', './wxWrapper.app/Contents/Resources/XSLT/TurboVision/gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24302_56', '4', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('SaveApplicationID', '{SaveApplicationID}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'exportApplicationToXMLBuffer', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x25c82_56', '5', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'writeStringToFile', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{memorybuffer}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x28f82_56', '6', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Info', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Only Mac, Windows and Unix flavoured machines are supported.', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29002_56', '7', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '\develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\XSLT_Templates\TurboVision\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29082_56', '8', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '/usr/share/lbdmf/TurboVision/gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x29102_46', '9', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2aa82_56', '10', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Operating system and selected application...', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'Os Type is {OSType}. ApplicationId is {SaveApplicationID}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24382_73', '11', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24402_73', '12', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x24482_73', '13', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2c402_56', '14', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'fileExists', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('filename', '\\develop\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\TurboVision\\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x25e02_73', '15', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x20e02_39');
DELETE FROM "actions" where "target" = 'BOUML_0x20e02_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x20e02_39'), 'BOUML_0x2c482_56', '16', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'transformXSLT', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('source', '{file}', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('stylesheet', '\lbDMF\XSLT\TurboVision\gen_TurboVisionFixedFormularClasses.xsl', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

-- Create activity transitions

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22982_70'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'));

UPDATE "action_step_transitions" set "expression" = 'file = lala.xml' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24302_56') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56');

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25c82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22a02_72'));

UPDATE "action_step_transitions" set "expression" = 'result = 1' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22a02_72');

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2aa82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Unix"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24382_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29082_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Mac"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24402_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24202_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x28f82_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('OSType == "Windows"', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x24482_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c402_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('result == 1', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29002_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('result == 0', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x25e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x20e02_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x2c482_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x29102_46'));

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
			
-- Create activity nodes for Sqlite

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
		
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20d82_70', '1', (select "id" from "action_types" where "bezeichnung" = 'InitialNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e02_73', '2', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e82_72', '3', (select "id" from "action_types" where "bezeichnung" = 'FinalNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20f02_73', '4', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20f82_73', '5', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x21002_73', '6', (select "id" from "action_types" where "bezeichnung" = 'DecisionNode'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20d82_56', '7', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The name of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e02_46', '8', (select "id" from "action_types" where "bezeichnung" = 'OpaqueAction'), '');
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x20e82_56', '9', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The interface of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x22802_56', '10', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The functor must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_steps" ("actionid", "bezeichnung", "a_order_nr", "type", "what") VALUES ((select "id" from "actions" where "target" = 'BOUML_0x1f482_39'), 'BOUML_0x22882_56', '11', (select "id" from "action_types" where "bezeichnung" = 'SendSignalAction'), '');

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('title', 'Error', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('signal', 'showMsgBox', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT INTO "action_step_parameter" ("name", "value", "interface", "description", "action_step_id") VALUES ('msg', 'The modulename of the application must not be empty', 'lb_I_String', 'A description ...', (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('name', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('interface', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('functor', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
DELETE FROM "action_step_transitions" 
WHERE "src_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
   OR "dst_actionid" IN (SELECT "id" FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'))
DELETE FROM "action_step_parameter" WHERE "action_step_id" IN (select "id" from "action_steps" where "bezeichnung" = 'BOUML_0x1f482_22');
DELETE FROM "action_steps" WHERE "actionid" = (select "id" from "actions" where "target" = 'BOUML_0x1f482_39');
DELETE FROM "actions" where "target" = 'BOUML_0x1f482_39';
	
INSERT INTO "action_parameters" ("name", "value", "interface", "description", "actionid") VALUES ('modulename', '', 'lb_I_String', 'A description ...', (select "id" from "actions" where "target" = 'BOUML_0x1f482_39'));
		
-- Create activity transitions

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_70'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f02_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('name == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f82_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('interface == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f02_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f82_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('functor == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20f82_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72'));

UPDATE "action_step_transitions" set "expression" = 'result = 1' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72');

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('modulename == ""', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x21002_73'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20d82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72'));

UPDATE "action_step_transitions" set "expression" = 'result = 0' where "src_actionid" = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46') and dst_actionid = (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_72');

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e82_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22802_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

INSERT INTO "action_step_transitions" ("expression", "description", "src_actionid", "dst_actionid") VALUES ('', '_BOUML_0x1f482_39', (select id from "action_steps" where "bezeichnung" = 'BOUML_0x22882_56'), (select id from "action_steps" where "bezeichnung" = 'BOUML_0x20e02_46'));

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


UPDATE anwendungen
SET model_errors = CONCAT(model_errors, CHAR(10), 'Import completed')
WHERE name = 'lbDMF Manager';



		

-- Script ready.
COMMIT;
