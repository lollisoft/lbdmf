-- +---------------------------------------------------------
-- | MODEL       : lbDMF
-- | AUTHOR      : Lothar Behrens
-- | GENERATED BY: Data Architect
-- +---------------------------------------------------------

--USE jedi;
SET SESSION AUTHORIZATION 'dba';

--...sCREATE TABLE column_types:0:
CREATE TABLE column_types
(
  id SERIAL,
  name char(30) NOT NULL,
  tablename char(30) NOT NULL,
  ro BOOL DEFAULT false,
  specialColumn BOOL DEFAULT false,
  controlType char(30) DEFAULT ''
) WITH OIDS;
--...e
insert into column_types (name, tablename, ro) values('kundennr', 'kunden', TRUE);
insert into column_types (name, tablename, ro) values('id', 'chart', TRUE);
insert into column_types (name, tablename, ro) values('language', 'translations', TRUE);
--...sActions:0:
--...sCREATE TABLE actions:0:
-- +---------------------------------------------------------
-- | TABLE: Actions
-- | This defines custom actions for an application. These
-- | actions may be displayed in formulars as buttons or later
-- | as detail views in a tab view manner.
-- +---------------------------------------------------------
CREATE TABLE actions
(
  id SERIAL,
  name char(50) NOT NULL,
  typ  INTEGER,
  source char(100),
  target INTEGER,
  PRIMARY KEY (id)
) WITH OIDS;
--...e
--...sCREATE TABLE action_types:0:
-- +---------------------------------------------------------
-- | TABLE: action_types
-- | This table defines general action types, that could be
-- | used for actions. This may be 'button press'
-- | 
-- +---------------------------------------------------------

CREATE TABLE action_types
(
  id SERIAL,
  bezeichnung char(100),
  action_handler char(100),	-- the functor with the implementation of the handler
  module	 char(100),	-- the module with the implementation of the handler
  PRIMARY KEY (id)
) WITH OIDS;

ALTER TABLE actions
ADD CONSTRAINT cst_action_types_TypID FOREIGN KEY ( typ )
   REFERENCES action_types ( id );

--...e
--...sCREATE TABLE action_steps:0:
-- +------------------------------------------------------------
-- | TABLE: action_steps
-- | 
-- | The target of an action may be more than one 'action'.
-- | It may be an action to open a form, or execute a SQL query.
-- +------------------------------------------------------------

CREATE TABLE action_steps
(
  id 		SERIAL,
  actionid	INTEGER,
  bezeichnung	char(100),
  a_order_nr	INTEGER,
  type		INTEGER, -- May be NULL for the first target
  what		char(100),
  PRIMARY KEY (id)
) WITH OIDS;

ALTER TABLE action_steps
ADD CONSTRAINT cst_action_target_ActionID FOREIGN KEY ( actionid )
   REFERENCES actions ( id );

ALTER TABLE action_steps
ADD CONSTRAINT cst_action_target_TypeID FOREIGN KEY ( type )
   REFERENCES action_types ( id );
--...e
--...sCREATE TABLE Formulare:0:
-- +---------------------------------------------------------
-- | TABLE: Formulare
-- +---------------------------------------------------------
CREATE TABLE Formulare
(
  id SERIAL,
  Name CHAR(30),
  MenuName CHAR(30),
  MenuOrder INTEGER,
  EventName CHAR(30),
  MenuHilfe CHAR(100),
  AnwendungID INTEGER,
  Typ INTEGER NOT NULL,
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_Formulare ON Formulare
(
  id
);

--...sCREATE TABLE formular_actions:0:
-- +---------------------------------------------------------
-- | TABLE: formular_actions
-- | 
-- | This table defines, what actions should be accessible in
-- | a form. The application should begin reading this table
-- | to build its action elements.
-- +---------------------------------------------------------


CREATE TABLE formular_actions
(
  id 		SERIAL,
  formular	INTEGER,
  action	INTEGER,
  event		char(100),
  PRIMARY KEY (id)
) WITH OIDS;

ALTER TABLE formular_actions
ADD CONSTRAINT cst_formular_actions_formular FOREIGN KEY ( formular )
   REFERENCES formulare ( id );

ALTER TABLE formular_actions
ADD CONSTRAINT cst_formular_actions_action FOREIGN KEY ( action )
   REFERENCES actions ( id );

--...e
--...e
--...sFill actions:0:
--...sFill action_types:0:
insert into action_types (bezeichnung) values('Buttonpress'); -- Built in handler

-- Configure predefined action types, that could be used inside a form

insert into action_types (bezeichnung, action_handler, module) values(
'SQL query',
'instanceOflbSQLQueryAction',
'lbDatabaseForm');

insert into action_types (bezeichnung, action_handler, module) values(
'Open form',
'instanceOflbFormAction',
'lbDatabaseForm');

insert into action_types (bezeichnung, action_handler, module) values(
'Open detail form',
'instanceOflbDetailFormAction',
'lbDatabaseForm');

insert into action_types (bezeichnung, action_handler, module) values(
'Open master form',
'instanceOflbMasterFormAction',
'lbDatabaseForm');

-- New planned feature. Let create reports based on database queries.

insert into action_types (bezeichnung, action_handler, module) values(
'Open Database Report',
'instanceOflbDBReportAction',
'lbDatabaseReport');
--...e
--...sFill actions:0:
insert into actions (name, typ, source, target) values(
'Reserve a trip',
1,
'kundennr',
1);

insert into actions (name, typ, source, target) values(
'Remove a reserved trip',
1,
'kundennr',
2);

insert into actions (name, typ, source, target) values(
'Streckenname bearbeiten',
1,
'bezeichnung',
3);

insert into actions (name, typ, source, target) values(
'Anwendungen',
1,
'userid',
4);

insert into actions (name, typ, source, target) values(
'Formulare',
1,
'name',
5);

insert into actions (name, typ, source, target) values(
'Parameter',
1,
'name',
6);

-- Let print a reservation based on customers id for master report data.
-- The customer would have more than one reservation. In general, these
-- reservation entries should be the sub reports.

insert into actions (name, typ, source, target) values(
'Reservierungen drucken',
1,
'kundenid',
7);
--...e
--...sFill action_steps:0:
insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'Add a new empty trip',
1,
'insert,TargetTable:Reservierungen,Relation:KundenID',
2, 1);

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'Customer want to reserve a trip',
2,
'DynReservierungen',
4, 1);

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'some test action',
1,
'DynReservierungen',
4, 2);

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'Open train plan name',
1,
'Streckennamen',
5, 3);

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'Open applications for user',
1,
'Benutzer -> Anwendungen',
4, 4);

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'Open forms for applications',
1,
'Formulare',
4, 5);

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'Open parameters for formulars',
1,
'Formular_Parameter',
4, 6);

insert into action_steps (bezeichnung, a_order_nr, what, type, actionid) values(
'Print reservations for customers',
1,
'DynReservierungen',
6, 7);
--...e
--...e

--...sCREATE TABLE translations:0:
-- +---------------------------------------------------------
-- | TABLE: Translations
-- +---------------------------------------------------------


CREATE TABLE translations
(
  id SERIAL,
  text CHAR(100),
  translated CHAR(100),
  language CHAR(30) default 'german',
  PRIMARY KEY (id)
) WITH OIDS;
--...e
--...sCREATE TABLE CodegenTarget:0:
-- +---------------------------------------------------------
-- | TABLE: CodegenTarget
-- +---------------------------------------------------------

CREATE TABLE CodegenTarget
(
  id SERIAL,
  Name CHAR(100),
  Titel CHAR(100),
  ModuleName CHAR(100),
  Functor CHAR(100),
  Interface CHAR(100),
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_CodegenTarget ON CodegenTarget
(
  id
);
--...e
--...sCREATE TABLE Anwendungen:0:
-- +---------------------------------------------------------
-- | TABLE: Anwendungen
-- +---------------------------------------------------------


CREATE TABLE Anwendungen
(
  id SERIAL,
  Name CHAR(100),
  Titel CHAR(100),
  ModuleName CHAR(100),
  Functor CHAR(100),
  Interface CHAR(100),
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_Anwendungen ON Anwendungen
(
  id
);
--...e
--...sCREATE TABLE Anwendungs_Parameter:0:
-- +---------------------------------------------------------
-- | TABLE: Anwendungs_Parameter
-- +---------------------------------------------------------

CREATE TABLE Anwendungs_Parameter
(
  id SERIAL,
  ParameterName CHAR(30),
  ParameterValue CHAR(255),
  AnwendungID INTEGER,
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_Anwendungs_Parameter ON Anwendungs_Parameter
(
  id
);
--...e
--...e
--...sCREATE TABLE Formular_Parameters:0:
-- +---------------------------------------------------------
-- | TABLE: Formular_Parameters
-- +---------------------------------------------------------
CREATE TABLE Formular_Parameters
(
  id SERIAL,
  ParameterName CHAR(30),
  ParameterValue CHAR(255),
  FormularID INTEGER,
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_Formular_Parameters ON Formular_Parameters
(
  id
);
--...e
--...sCREATE TABLE ForeignKey_VisibleData_Mapping:0:
-- +---------------------------------------------------------
-- | TABLE: ForeignKey_VisibleData_Mapping
-- +---------------------------------------------------------

CREATE TABLE ForeignKey_VisibleData_Mapping
(
  id SERIAL,
  FKName	CHAR(100),
  FKTable	CHAR(100),
  PKName	CHAR(100),
  PKTable	CHAR(100),
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_ForeignKey_VisibleData_Mapping ON ForeignKey_VisibleData_Mapping
(
  id
);
--...e
--...sCREATE TABLE Anwendungen_Formulare:0:
-- +---------------------------------------------------------
-- | TABLE: Anwendungen_Formulare
-- +---------------------------------------------------------
CREATE TABLE Anwendungen_Formulare
(
  id SERIAL,
  AnwendungID INTEGER NOT NULL,
  FormularID INTEGER NOT NULL,
  PRIMARY KEY (id)
) WITH OIDS;
--...e
--...sCREATE TABLE Anwendungsberechtigungen:0:
-- +---------------------------------------------------------
-- | TABLE: Anwendungsberechtigungen
-- +---------------------------------------------------------
CREATE TABLE Anwendungsberechtigungen
(
  id SERIAL,
  idUser INTEGER,
  idFormular INTEGER,
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_Anwendungsberechtigungen ON Anwendungsberechtigungen
(
  id
);
--...e
--...sCREATE TABLE Formulartypen:0:
-- +---------------------------------------------------------
-- | TABLE: Formulartypen
-- +---------------------------------------------------------
CREATE TABLE Formulartypen
(
  id SERIAL,
  HandlerModule CHAR(30),
  HandlerFunctor CHAR(100),
  HandlerInterface CHAR(100),
  Namespace CHAR(50),
  Beschreibung CHAR(254),
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_Formulartypen ON Formulartypen
(
  id
);
--...e
--...sCREATE TABLE Users:0:
-- +---------------------------------------------------------
-- | TABLE: User
-- +---------------------------------------------------------
CREATE TABLE Users
(
  id SERIAL,
  Name CHAR(30),
  Vorname CHAR(30),
  userid CHAR(30),
  passwort CHAR(30),
  lastapp INTEGER,
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id ON Users
(
  id
);
--...e
--...sCREATE TABLE User_Anwendungen:0:
-- +---------------------------------------------------------
-- | TABLE: User_Anwendungen
-- +---------------------------------------------------------
CREATE TABLE User_Anwendungen
(
  id SERIAL,
  userid INTEGER,
  AnwendungenId INTEGER,
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_User_Anwendungen ON User_Anwendungen
(
  id
);
--...e
--...sCREATE TABLE report_parameters:0:
--DROP TABLE report_parameters;

CREATE TABLE report_parameters
(
  id SERIAL,
  report CHAR(50),
  name CHAR(50) NOT NULL,
  value INTEGER  NOT NULL,
  PRIMARY KEY (id)
) WITH OIDS;
          
CREATE UNIQUE INDEX pk_id_report_parameters ON report_parameters
(
  id
);
            
            
insert into report_parameters (report, name, value) values ('dummy', 'colstepHDR', 41);
insert into report_parameters (report, name, value) values ('dummy', 'colstep', 30);
insert into report_parameters (report, name, value) values ('dummy', '_coly', 0);
insert into report_parameters (report, name, value) values ('dummy', 'fntBig', 12);
insert into report_parameters (report, name, value) values ('dummy', 'fntSmall', 6);
insert into report_parameters (report, name, value) values ('dummy', 'fntHdr', 10);
insert into report_parameters (report, name, value) values ('dummy', 'erwachsene', 22);
insert into report_parameters (report, name, value) values ('dummy', 'kinder', 15);
insert into report_parameters (report, name, value) values ('dummy', 'planfahrtid', 20);
insert into report_parameters (report, name, value) values ('dummy', 'kundenid', 18);
insert into report_parameters (report, name, value) values ('dummy', 'TextBlockSize', 120);
--...e
--...sCREATE TABLE report_texts:0:
-- +---------------------------------------------------------
-- | TABLE: report_texts
-- +---------------------------------------------------------
CREATE TABLE report_texts
(
  id SERIAL,
  report CHAR(50),
  line INTEGER,
  text CHAR(255),
  PRIMARY KEY (id)
) WITH OIDS;

CREATE UNIQUE INDEX pk_id_report_texts ON report_texts
(
  id
);

insert into report_texts (report, line, text) values('dummy', 1, 'Sehr geehrte{Ansprache} {Name},');
insert into report_texts (report, line, text) values('dummy', 2, '');
insert into report_texts (report, line, text) values('dummy', 3, 'hiermit best�tigen wir Ihnen ihre Reservierung f�r unten aufgelistete Fahrten.');
insert into report_texts (report, line, text) values('dummy', 4, 'Die Reservierung bleibt bis zum Zahlungseingang unter Vorbehalt. Hierf�r');
insert into report_texts (report, line, text) values('dummy', 5, 'bitten wir um Verst�ndniss.');
insert into report_texts (report, line, text) values('dummy', 6, '');
insert into report_texts (report, line, text) values('dummy', 7, 'Bitte verwenden Sie als Verwendungszweck folgende Nummer: {Reservierungsnummer}');
insert into report_texts (report, line, text) values('dummy', 8, '');
insert into report_texts (report, line, text) values('dummy', 9, 'Wir bedanken uns f�r Ihre Reservierung und verbleiben.');
--...e

--...sFOREIGN KEYS:0:
-- +---------------------------------------------------------
-- | FOREIGN KEYS
-- +---------------------------------------------------------

ALTER TABLE Anwendungen_Formulare 
ADD CONSTRAINT cst_Anwendungen_Formulare_AnwendungID FOREIGN KEY ( AnwendungID )
   REFERENCES Anwendungen ( id );
ALTER TABLE Anwendungen_Formulare 
ADD CONSTRAINT cst_Anwendungen_Formulare_FormularID FOREIGN KEY ( FormularID )
   REFERENCES Formulare ( id );
ALTER TABLE Anwendungsberechtigungen 
ADD CONSTRAINT cst_Anwendungsberechtigungen_idFormular FOREIGN KEY ( idFormular )
   REFERENCES Formulare ( id );
ALTER TABLE Anwendungsberechtigungen 
ADD CONSTRAINT cst_Anwendungsberechtigungen_idUser FOREIGN KEY ( idUser )
   REFERENCES Users ( id );
ALTER TABLE Formulare 
ADD CONSTRAINT cst_Formulare_Typ FOREIGN KEY ( Typ )
   REFERENCES Formulartypen ( id );
ALTER TABLE Formulare 
ADD CONSTRAINT cst_Formulare_AnwendungID FOREIGN KEY ( AnwendungID )
   REFERENCES Anwendungen ( id );
ALTER TABLE User_Anwendungen 
ADD CONSTRAINT cst_User_Anwendungen_userid FOREIGN KEY ( userid )
   REFERENCES Users ( id );

ALTER TABLE Users
ADD CONSTRAINT cst_Users_lastapp FOREIGN KEY ( lastapp )
   REFERENCES Anwendungen ( id );

ALTER TABLE User_Anwendungen 
ADD CONSTRAINT cst_User_Anwendungen_AnwendungenId FOREIGN KEY ( AnwendungenId )
   REFERENCES Anwendungen ( id );
ALTER TABLE Formular_Parameters
ADD CONSTRAINT cst_Formular_Parameters_FormularID FOREIGN KEY ( FormularID )
   REFERENCES Formulare (id );

ALTER TABLE Anwendungs_Parameter 
ADD CONSTRAINT cst_Anwendungs_Parameter_AnwendungID FOREIGN KEY ( AnwendungID )
   REFERENCES Anwendungen ( id );
--...e

--...sData:0:
-- +---------------------------------------------------------
-- | DATA
-- +---------------------------------------------------------

insert into Users (Name, Vorname, userid, passwort) Values ('User', 'Test', 'user', 'TestUser');

--...sFill Anwendungen:0:
insert into Anwendungen (Name, Titel, ModuleName, Functor, Interface) Values (
'lbDMF Manager',
'Dynamic App Manager',
'lbDynApp',
'instanceOfApplication',
'lb_I_Application');

insert into Anwendungen (Name, Titel, ModuleName, Functor, Interface) Values (
'Demo application',
'Demonstration',
'Application',
'instanceOfApplication',
'lb_I_Application');

insert into Anwendungen (Name, Titel, ModuleName, Functor, Interface) Values (
'FRS',
'Fahrkarten Reservierungssystem',
'lbDynApp',
'instanceOfApplication',
'lb_I_Application');

insert into Anwendungen (Name, Titel, ModuleName, Functor, Interface) Values (
'lbDMF Codegenerator',
'Generiert Code von lbDMF Daten',
'lbDMFAppWriter',
'instanceOfApplication',
'lb_I_Application');

insert into Anwendungen (Name, Titel, ModuleName, Functor, Interface) Values (
'SQL Ledger',
'Warenwirtschafts System',
'lbDynApp',
'instanceOfApplication',
'lb_I_Application');
--...e
--...sFill Formulartypen:0:
insert into Formulartypen (HandlerModule, HandlerFunctor, HandlerInterface, Beschreibung) Values (
'-',
'-',
'lb_I_DatabaseForm',
'Dynamisch aufgebautes Datenbankformular');

insert into Formulartypen (HandlerModule, HandlerFunctor, HandlerInterface, Beschreibung) Values (
'lbTrainresBaseForms',
'lbKunden',
'lb_I_FixWiredForm',
'Fest verdrahtetes Formular');
--...e
--...sFill Formulare:0:
insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
1,
'Benutzer', 
'Benutzer verwalten', 
'manageUser', 
'Verwaltung der Benutzer in lbDMF',
1 , 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
2,
'Formulare', 
'Formulare verwalten', 
'manageFormulars', 
'Verwaltung der Formulare in lbDMF',
1, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
1,
'Kunden', 
'Kunden verwalten',
'manageCustomers', 
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
2 , 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
2,
'Reservierungen', 
'Reservierungen verwalten', 
'manageReservations', 
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
2, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
1,
'DynKunden', 
'Kunden verwalten', 
'manageCustomers', 
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
3, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
2,
'DynReservierungen', 
'Reservierungen verwalten', 
'manageReservations', 
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
3, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
3,
'Formular_Parameter',
'Formularparameter verwalten', 
'manageFormularparameters', 
'Verwaltung der Formularparameter in lbDMF',
1, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
4,
'Benutzer -> Anwendungen', 
'Anwendungen Benutzern zuordnen', 
'manageAppsUsers', 
'Verwaltung der Zuordnung von Benutzern zu Anwendungen',
1, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
1,
'Benutzer',
'Benutzer verwalten',
'manageUser',
'Verwaltung der Benutzer in lbDMF',
4, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
2,
'Formulare',
'Formulare verwalten',
'manageFormulars',
'Verwaltung der Formulare in lbDMF',
4, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
3,
'Formular_Parameter',
'Formularparameter verwalten',
'manageFormularparameters',
'Verwaltung der Formularparameter in lbDMF',
4, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
4,
'Benutzer -> Anwendungen',
'Anwendungen Benutzern zuordnen',
'manageAppsUsers',
'Verwaltung der Zuordnung von Benutzern zu Anwendungen',
4, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
3,
'Kunden',
'Kunden verwalten',
'manageCustomers',
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
2, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
5,
'Reservierungen',
'Reservierungen verwalten',
'manageReservations',
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
4, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
3,
'DynKunden',
'Kunden verwalten',
'manageDynCustomers',
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
3, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
5,
'DynReservierungen',
'Reservierungen verwalten',
'manageDynReservierungen',
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
4, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
5,
'Formulare -> Anwendung',
'Formulare Anwendungen zuordnen',
'manageFormularsToApps',
'Einrichtung der Formulare zu Anwendungen',
1, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
1,
'Sachkonten',
'Sachkontenverwaltung',
'manageGeneralLedger',
'-',
5 , 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
6,
'Anwendungen',
'Anwendungen',
'manageAnwendungen',
'-',
1 , 1);

-- 20:

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
7,
'Anwendungen -> Formulare',
'Anwendungen -> Formulare',
'manageAnwendungenFormulare',
'-',
1, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
4,
'Planfahrten',
'Planfahrten verwalten',
'managePlanfahrten',
'-',
3, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
5,
'Planstrecken',
'Planstrecken verwalten',
'managePlanstrecken',
'-',
3, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
6,
'Streckennamen',
'Streckennamen verwalten',
'manageStreckennamen',
'-',
3, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
8,
'Aktionen',
'Aktionen verwalten',
'manageFormularaktionen',
'-',
1, 1);

-- 25:

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
9,
'Uebersetzungen',
'Uebersetzungen verwalten',
'manageUebersetzungen',
'-',
1, 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
2,
'Artikel',
'Artikelverwaltung',
'manageParts',
'-',
5 , 1);

insert into Formulare (MenuOrder, Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
10,
'Formularaktionen zuordnen',
'Formularaktionen zuordnen',
'manageAssignFormActions',
'-',
1 , 1);
--...e

--...sFill formular_actions:0:
insert into formular_actions (formular, action, event) values(5, 1, 'evt_Reserve_Customer_Trip');
insert into formular_actions (formular, action, event) values(5, 2, 'evt_Some_Test_Action');

insert into formular_actions (formular, action, event) values(21, 3, 'evt_Manage_Train_Trip_Name');

insert into formular_actions (formular, action, event) values(6, 7, 'evt_Print_Customer_Reservations');

-- Actions for 'lbDMF Manager' application

insert into formular_actions (formular, action, event) values(1, 4, 'evt_Manage_User_Apps');
insert into formular_actions (formular, action, event) values(19, 5, 'evt_Manage_Apps_Forms');
insert into formular_actions (formular, action, event) values(2, 6, 'evt_Manage_Form_Parameters');

--...e

--...sFill ForeignKey_VisibleData_Mapping:0:
insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'anwendungid',
'formulare',
'name',
'anwendungen');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'typ',
'formulare',
'beschreibung',
'formulartypen');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'formularid',
'formular_parameters',
'name',
'formulare');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'anwendungid',
'anwendungs_parameter',
'name',
'anwendungen');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'userid',
'user_anwendungen',
'userid',
'users');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'anwendungenid',
'user_anwendungen',
'name',
'anwendungen');
--...e
--...sFill Formular_Parameters:0:
insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select "kundennr", "name", "vorname", "ort", "plz", "strasse", "vorwahl", "telefon" from kunden order by kundennr',
5);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select "erwachsene", "kinder", "planfahrtid", "kundenid" from reservierungen',
6);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select "name", "vorname", "userid", "passwort" from "users"',
1);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select "name", "menuname", "eventname", "menuhilfe", "anwendungid", "typ" from "formulare"',
2);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select "parametername", "parametervalue", "formularid" from formular_parameters',
7);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select "userid", "anwendungenid" from "user_anwendungen"',
8);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select anwendungid, formularid from "anwendungen_formulare"',
17);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select * from chart order by id',
18);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select name, titel, modulename, functor, interface from anwendungen order by id',
19);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select anwendungid, formularid from anwendungen_formulare order by id',
20);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select bezeichnung, streckenid, datum from planfahrten order by datum',
21);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select zubahnhofa, bahnhofid, zubahnhofb, streckenid from planstrecken order by bahnhofid',
22);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select * from planstreckennamen',
23);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select * from actions',
24);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select text, translated from translations order by text',
25);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select id, partnumber, description, unit, listprice, sellprice from parts',
26);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select formular, action, event from formular_actions order by formular',
27);

--...e
--...sFill Anwendungs_Parameter:0:
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBName', 'trainres', 3);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBUser', 'dba', 3);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBPass', 'trainres', 3);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBName', 'lbDMF', 1);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBUser', 'dba', 1);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBPass', 'trainres', 1);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBName', 'lbDMF', 4);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBUser', 'dba', 4);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBPass', 'trainres', 4);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBName', 'sqlledger', 5);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBUser', 'dba', 5);
insert into Anwendungs_Parameter (ParameterName, ParameterValue, AnwendungID) Values ('DBPass', 'trainres', 5);
--...e
--...sFill Anwendungen_Formulare:0:
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 1);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 2);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 7);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 8);

insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (2, 1);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (2, 2);

insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (3, 5);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (3, 6);

insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 9);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 10);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 11);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 12);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 13);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 14);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 15);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (4, 16);

insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (5, 18);

insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 19);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 20);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (3, 21);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (3, 22);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (3, 23);

insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 24);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (1, 25);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (5, 26);
insert into Anwendungen_Formulare (AnwendungID,FormularID) Values (5, 27);
--...e
--...sFill User_Anwendungen:0:
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 1);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 2);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 3);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 4);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 5);
--...e

--...sFill CodegenTarget:0:
-- +----------------------------------------
-- | Setup for the codgeneration Target
-- +----------------------------------------

insert into CodegenTarget (Name, Titel, ModuleName, Functor, Interface) 
Values (
'lbDMFAppwriter', 
'Create an application module for lbDMF Framework', 
'ModullbDMFAppgen',
'instanceOflbDMFAppwriter',
'lb_I_CodeGenerator'
);
--...e
--...e
