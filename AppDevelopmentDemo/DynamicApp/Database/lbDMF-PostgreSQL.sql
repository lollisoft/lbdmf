-- +---------------------------------------------------------
-- | MODEL       : lbDMF
-- | AUTHOR      :
-- | GENERATED BY: Data Architect
-- +---------------------------------------------------------

--USE jedi;

-- +---------------------------------------------------------
-- | TABLE: Anwendungen
-- +---------------------------------------------------------


CREATE TABLE Anwendungen
(
  id SERIAL,
  Name VARCHAR(100),
  Titel VARCHAR(100),
  ModuleName VARCHAR(100),
  Functor VARCHAR(100),
  Interface VARCHAR(100),
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_Anwendungen ON Anwendungen
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: Anwendungs_Parameter
-- +---------------------------------------------------------

CREATE TABLE Anwendungs_Parameter
(
  id SERIAL,
  ParameterName VARCHAR(30),
  ParameterValue VARCHAR(255),
  AnwendungID INTEGER,
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_Anwendungs_Parameter ON Anwendungs_Parameter
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: Formulare
-- +---------------------------------------------------------
CREATE TABLE Formulare
(
  id SERIAL,
  Name VARCHAR(30),
  MenuName VARCHAR(30),
  EventName VARCHAR(30),
  MenuHilfe VARCHAR(100),
  AnwendungID INTEGER,
  Typ INTEGER NOT NULL,
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_Formulare ON Formulare
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: Formular_Parameters
-- +---------------------------------------------------------
CREATE TABLE Formular_Parameters
(
  id SERIAL,
  ParameterName VARCHAR(30),
  ParameterValue VARCHAR(255),
  FormularID INTEGER,
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_Formular_Parameters ON Formular_Parameters
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: ForeignKey_VisibleData_Mapping
-- +---------------------------------------------------------

CREATE TABLE ForeignKey_VisibleData_Mapping
(
  id SERIAL,
  FKName	VARCHAR(100),
  FKTable	VARCHAR(100),
  PKName	VARCHAR(100),
  PKTable	VARCHAR(100),
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_ForeignKey_VisibleData_Mapping ON ForeignKey_VisibleData_Mapping
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: Anwendungen_Formulare
-- +---------------------------------------------------------
CREATE TABLE Anwendungen_Formulare
(
  id SERIAL,
  AnwendungID INTEGER NOT NULL,
  FormularID INTEGER NOT NULL,
  PRIMARY KEY (id)
);

-- +---------------------------------------------------------
-- | TABLE: Anwendungsberechtigungen
-- +---------------------------------------------------------
CREATE TABLE Anwendungsberechtigungen
(
  id SERIAL,
  idUser INTEGER,
  idFormular INTEGER,
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_Anwendungsberechtigungen ON Anwendungsberechtigungen
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: Formulartypen
-- +---------------------------------------------------------
CREATE TABLE Formulartypen
(
  id SERIAL,
  HandlerModule VARCHAR(30),
  HandlerFunctor VARCHAR(100),
  HandlerInterface VARCHAR(100),
  Beschreibung VARCHAR(254),
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_Formulartypen ON Formulartypen
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: User
-- +---------------------------------------------------------
CREATE TABLE Users
(
  id SERIAL,
  Name VARCHAR(30),
  Vorname VARCHAR(30),
  userid VARCHAR(30),
  passwort VARCHAR(30),
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id ON Users
(
  id
);

-- +---------------------------------------------------------
-- | TABLE: User_Anwendungen
-- +---------------------------------------------------------
CREATE TABLE User_Anwendungen
(
  id SERIAL,
  userid INTEGER NOT NULL,
  AnwendungenId INTEGER NOT NULL,
  PRIMARY KEY (id)
);

CREATE UNIQUE INDEX pk_id_User_Anwendungen ON User_Anwendungen
(
  id
);

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
ALTER TABLE User_Anwendungen 
ADD CONSTRAINT cst_User_Anwendungen_AnwendungenId FOREIGN KEY ( AnwendungenId )
   REFERENCES Anwendungen ( id );
ALTER TABLE Formular_Parameters
ADD CONSTRAINT cst_Formular_Parameters_FormularID FOREIGN KEY ( FormularID )
   REFERENCES Formulare (id );

-- +---------------------------------------------------------
-- | DATA
-- +---------------------------------------------------------

insert into Users Values (1, 'Behrens', 'Lothar', 'behrens', 'einerlei');

insert into Anwendungen Values (1, 'lbDMF Manager', 'Dynamic App Manager', 'lbDynApp', 'instanceOfApplication', 'lb_I_Application');
insert into Anwendungen Values (2, 'Demo application', 'Demonstration', 'Application', 'instanceOfApplication', 'lb_I_Application');
insert into Anwendungen Values (3, 'FRS', 'Fahrkarten Reservierungssystem', 'lbDynApp', 'instanceOfApplication', 'lb_I_Application');

insert into Formulartypen Values (1, '-',                   '-',        'lb_I_DatabaseForm', 'Dynamisch aufgebautes Datenbankformular');
insert into Formulartypen Values (2, 'lbTrainresBaseForms', 'lbKunden', 'lb_I_FixWiredForm', 'Fest verdrahtetes Formular');

insert into Formulare Values (1, 'Benutzer', 'Benutzer verwalten', 'manageUser', 'Verwaltung der Benutzer in lbDMF',1 , 1);
insert into Formulare Values (2, 'Formulare', 'Formulare verwalten', 'manageFormulars', 'Verwaltung der Formulare in lbDMF',1 , 1);
insert into Formulare Values (7, 'Formular_Parameter', 'Formularparameter verwalten', 'manageFormularparameters', 'Verwaltung der Formularparameter in lbDMF',1 , 1);
insert into Formulare Values (8, 'Benutzer -> Anwendungen', 'Anwendungen Benutzern zuordnen', 'manageAppsUsers', 'Verwaltung der Zuordnung von Benutzern zu Anwendungen', 1, 1);
insert into Formulare Values (3, 'Kunden', 'Kunden verwalten', 'manageCustomers', 'Bietet Verwaltungsmöglichkeiten für Kunden',2 , 1);
insert into Formulare Values (4, 'Reservierungen', 'Reservierungen verwalten', 'manageReservations', 'Bietet Verwaltungsmöglichkeiten für Reservierungen von Fahrkarten',2 , 1);
insert into Formulare Values (5, 'DynKunden', 'Kunden verwalten', 'manageCustomers', 'Bietet Verwaltungsmöglichkeiten für Kunden',3 , 1);
insert into Formulare Values (6, 'DynReservierungen', 'Reservierungen verwalten', 'manageReservations', 'Bietet Verwaltungsmöglichkeiten für Reservierungen von Fahrkarten',3 , 1);

insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values ('anwendungid', 'formulare', 'name', 'anwendungen');
insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values ('typ', 'formulare', 'beschreibung', 'formulartypen');
insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values ('formularid', 'formular_parameters', 'name', 'formulare');
insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values ('anwendungid', 'anwendungs_parameter', 'name', 'anwendungen');
insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values ('userid', 'user_anwendungen', 'userid', 'users');
insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) Values ('anwendungenid', 'user_anwendungen', 'name', 'anwendungen');


insert into Formular_Parameters Values (1, 'query', 'select "anrede", "name", "vorname", "ort", "plz", "strasse", "vorwahl", "telefon" from kunden', 5);
insert into Formular_Parameters Values (2, 'query', 'select "name", "vorname", "erwachsene", "kinder" from reservierungen inner join kunden on reservierungen.kundenid = kunden.id', 6);
insert into Formular_Parameters Values (3, 'query', 'select "name", "vorname", "userid", "passwort" from "users"', 1);
insert into Formular_Parameters Values (4, 'query', 'select "name", "menuname", "eventname", "menuhilfe", "anwendungid", "typ" from "formulare"', 2);
insert into Formular_Parameters Values (5, 'query', 'select "parametername", "parametervalue", "formularid" from "formular_parameters"', 7);
insert into Formular_Parameters Values (6, 'query', 'select "anwendungenid", "userid" from "user_anwendungen"', 8);

insert into Anwendungs_Parameter Values (1, 'DBName', 'trainres', 3);
insert into Anwendungs_Parameter Values (2, 'DBUser', 'dba', 3);
insert into Anwendungs_Parameter Values (3, 'DBPass', 'trainres', 3);
insert into Anwendungs_Parameter Values (4, 'DBName', 'lbDMF', 1);
insert into Anwendungs_Parameter Values (5, 'DBUser', 'dba', 1);
insert into Anwendungs_Parameter Values (6, 'DBPass', 'trainres', 1);

insert into Anwendungen_Formulare Values (1, 1, 1);
insert into Anwendungen_Formulare Values (2, 1, 2);
insert into Anwendungen_Formulare Values (3, 1, 7);
insert into Anwendungen_Formulare Values (4, 1, 8);
insert into Anwendungen_Formulare Values (5, 2, 1);
insert into Anwendungen_Formulare Values (6, 2, 2);
insert into Anwendungen_Formulare Values (7, 3, 5);
insert into Anwendungen_Formulare Values (8, 3, 6);

insert into User_Anwendungen Values (1, 1, 1);
insert into User_Anwendungen Values (2, 1, 2);
insert into User_Anwendungen Values (3, 1, 3);