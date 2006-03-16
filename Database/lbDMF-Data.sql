-- +---------------------------------------------------------
-- | MODEL       : lbDMF
-- | AUTHOR      : Lothar Behrens
-- +---------------------------------------------------------

insert into column_types (name, tablename, ro) values('kundennr', 'kunden', 'true');
insert into column_types (name, tablename, ro) values('id', 'chart', 'true');
insert into column_types (name, tablename, ro) values('language', 'translations', 'true');

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
insert into formular_actions (formular, action, event) values(5, 1, 'evt_Reserve_Customer_Trip');
insert into formular_actions (formular, action, event) values(5, 2, 'evt_Some_Test_Action');

insert into formular_actions (formular, action, event) values(21, 3, 'evt_Manage_Train_Trip_Name');

insert into formular_actions (formular, action, event) values(6, 7, 'evt_Print_Customer_Reservations');

-- Actions for 'lbDMF Manager' application

insert into formular_actions (formular, action, event) values(1, 4, 'evt_Manage_User_Apps');
insert into formular_actions (formular, action, event) values(19, 5, 'evt_Manage_Apps_Forms');
insert into formular_actions (formular, action, event) values(2, 6, 'evt_Manage_Form_Parameters');


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
insert into report_texts (report, line, text) values('dummy', 1, 'Sehr geehrte{Ansprache} {Name},');
insert into report_texts (report, line, text) values('dummy', 2, '');
insert into report_texts (report, line, text) values('dummy', 3, 'hiermit best�tigen wir Ihnen ihre Reservierung f�r unten aufgelistete Fahrten.');
insert into report_texts (report, line, text) values('dummy', 4, 'Die Reservierung bleibt bis zum Zahlungseingang unter Vorbehalt. Hierf�r');
insert into report_texts (report, line, text) values('dummy', 5, 'bitten wir um Verst�ndniss.');
insert into report_texts (report, line, text) values('dummy', 6, '');
insert into report_texts (report, line, text) values('dummy', 7, 'Bitte verwenden Sie als Verwendungszweck folgende Nummer: {Reservierungsnummer}');
insert into report_texts (report, line, text) values('dummy', 8, '');
insert into report_texts (report, line, text) values('dummy', 9, 'Wir bedanken uns f�r Ihre Reservierung und verbleiben.');

-- +---------------------------------------------------------
-- | DATA
-- +---------------------------------------------------------

insert into Users (Name, Vorname, userid, passwort) Values ('User', 'Test', 'user', 'TestUser');

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
insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Benutzer', 
'Benutzer verwalten', 
'manageUser', 
'Verwaltung der Benutzer in lbDMF',
1 , 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Formulare', 
'Formulare verwalten', 
'manageFormulars', 
'Verwaltung der Formulare in lbDMF',
1, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Kunden', 
'Kunden verwalten',
'manageCustomers', 
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
2 , 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Reservierungen', 
'Reservierungen verwalten', 
'manageReservations', 
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
2, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'DynKunden', 
'Kunden verwalten', 
'manageCustomers', 
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
3, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'DynReservierungen', 
'Reservierungen verwalten', 
'manageReservations', 
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
3, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Formular_Parameter',
'Formularparameter verwalten', 
'manageFormularparameters', 
'Verwaltung der Formularparameter in lbDMF',
1, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Benutzer -> Anwendungen', 
'Anwendungen Benutzern zuordnen', 
'manageAppsUsers', 
'Verwaltung der Zuordnung von Benutzern zu Anwendungen',
1, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Benutzer',
'Benutzer verwalten',
'manageUser',
'Verwaltung der Benutzer in lbDMF',
4, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Formulare',
'Formulare verwalten',
'manageFormulars',
'Verwaltung der Formulare in lbDMF',
4, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Formular_Parameter',
'Formularparameter verwalten',
'manageFormularparameters',
'Verwaltung der Formularparameter in lbDMF',
4, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Benutzer -> Anwendungen',
'Anwendungen Benutzern zuordnen',
'manageAppsUsers',
'Verwaltung der Zuordnung von Benutzern zu Anwendungen',
4, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Kunden',
'Kunden verwalten',
'manageCustomers',
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
2, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Reservierungen',
'Reservierungen verwalten',
'manageReservations',
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
4, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'DynKunden',
'Kunden verwalten',
'manageDynCustomers',
'Bietet Verwaltungsm�glichkeiten f�r Kunden',
3, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'DynReservierungen',
'Reservierungen verwalten',
'manageDynReservierungen',
'Bietet Verwaltungsm�glichkeiten f�r Reservierungen von Fahrkarten',
4, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Formulare -> Anwendung',
'Formulare Anwendungen zuordnen',
'manageFormularsToApps',
'Einrichtung der Formulare zu Anwendungen',
1, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Sachkonten',
'Sachkontenverwaltung',
'manageGeneralLedger',
'-',
5 , 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Anwendungen',
'Anwendungen',
'manageAnwendungen',
'-',
1 , 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Anwendungen -> Formulare',
'Anwendungen -> Formulare',
'manageAnwendungenFormulare',
'-',
1, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Planfahrten',
'Planfahrten verwalten',
'managePlanfahrten',
'-',
3, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Planstrecken',
'Planstrecken verwalten',
'managePlanstrecken',
'-',
3, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Streckennamen',
'Streckennamen verwalten',
'manageStreckennamen',
'-',
3, 1);

insert into Formulare (Name, MenuName, EventName, MenuHilfe, AnwendungID, Typ) Values (
'Formularaktionen',
'Formularaktionen verwalten',
'manageFormularaktionen',
'-',
1, 1);
insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'anwendungid',
'Formulare',
'name',
'Anwendungen');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'typ',
'Formulare',
'beschreibung',
'Formulartypen');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'formularid',
'Formular_Parameters',
'name',
'Formulare');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'anwendungid',
'Anwendungs_Parameter',
'name',
'Anwendungen');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'userid',
'User_Anwendungen',
'userid',
'Users');

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values (
'anwendungenid',
'User_Anwendungen',
'name',
'anwendungen');

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select kundennr, name, vorname, ort, plz, strasse, vorwahl, telefon from kunden order by kundennr',
5);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select erwachsene, kinder, planfahrtid, kundenid from reservierungen',
6);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select name, vorname, userid, passwort from Users',
1);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select name, menuname, eventname, menuhilfe, anwendungid, typ from Formulare',
2);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select parametername, parametervalue, formularid from Formular_Parameters',
7);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select userid, anwendungenid from User_Anwendungen',
8);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select anwendungid, formularid from Anwendungen_Formulare',
17);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select * from chart order by id',
18);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select name, titel, modulename, functor, interface from Anwendungen order by id',
19);

insert into Formular_Parameters (ParameterName, ParameterValue, FormularID) Values (
'query',
'select anwendungid, formularid from Anwendungen_Formulare order by id',
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
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 1);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 2);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 3);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 4);
insert into User_Anwendungen (userid, AnwendungenId) Values (1, 5);

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
