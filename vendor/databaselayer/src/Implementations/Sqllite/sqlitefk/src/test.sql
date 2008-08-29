
-- Association Adresse -> Lieferant
-- Drop a constraint

-- Association Adresse -> Kunde
-- Drop a constraint

-- Association Adresse -> Konkurrenten
-- Drop a constraint

-- Association Kunde -> Rechnung
-- Drop a constraint

-- Association Kunde -> Auftrag
-- Drop a constraint

-- Association Kunde -> Angebot
-- Drop a constraint

-- Association Auftrag -> Auftragspositionen
-- Drop a constraint

-- Association Auftrag -> Rechnung
-- Drop a constraint

-- Association Auftragspositionen -> Auftrag
-- Drop a constraint

-- Association Artikel -> Angebotspositionen
-- Drop a constraint

-- Association Artikel -> Auftragspositionen
-- Drop a constraint

-- Association Artikel -> Rechnungspositionen
-- Drop a constraint

-- Association Angebot -> Angebotspositionen
-- Drop a constraint

-- Association Angebot -> Auftrag
-- Drop a constraint

-- Association Rechnung -> Rechnungspositionen
-- Drop a constraint

-- Association Lieferant -> Artikel
-- Drop a constraint

-- Association Kontakte -> Kunde
-- Drop a constraint

-- Association Kontakte -> Konkurrenten
-- Drop a constraint

-- Class is AdresseDatabaseLayerGateway
CREATE TABLE "Adresse" (
"ID" INTEGER PRIMARY KEY,

"Strasse" CHAR(100),

"Hausnummer" CHAR(100),

"Stadt" CHAR(100),

"Plz" CHAR(100),

"Lieferant" INTEGER,

"Kunde" INTEGER,

"Konkurrenten" INTEGER
);


-- Class is KundeDatabaseLayerGateway
CREATE TABLE "Kunde" (
"ID" INTEGER PRIMARY KEY,

"Kundennummer" INTEGER,

"Firmenname" CHAR(100),

"Notiz" TEXT,

"Rechnung" INTEGER,

"Auftrag" INTEGER,

"Angebot" INTEGER
);


-- Class is AuftragDatabaseLayerGateway
CREATE TABLE "Auftrag" (
"ID" INTEGER PRIMARY KEY,

"Auftragsdatum" DATE,

"Gesamtpreis" DECIMAL,

"Auftragsnummer" INTEGER,

"Auftragspositionen" INTEGER,

"Rechnung" INTEGER
);


-- Class is AuftragspositionenDatabaseLayerGateway
CREATE TABLE "Auftragspositionen" (
"ID" INTEGER PRIMARY KEY,

"Preis" DECIMAL,

"Menge" INTEGER,

"Auftrag" INTEGER
);


-- Class is ArtikelDatabaseLayerGateway
CREATE TABLE "Artikel" (
"ID" INTEGER PRIMARY KEY,

"Name" CHAR(100),

"Preis" DECIMAL,

"Einheit" INTEGER,

"Beschreibung" CHAR(100),

"Menge" DECIMAL,

"Angebotspositionen" INTEGER,

"Auftragspositionen" INTEGER,

"Rechnungspositionen" INTEGER
);


-- Class is AngebotDatabaseLayerGateway
CREATE TABLE "Angebot" (
"ID" INTEGER PRIMARY KEY,

"Angebotsnummer" INTEGER,

"Angebotsdatum" DATE,

"Gesamtpreis" DECIMAL,

"Angebotspositionen" INTEGER,

"Auftrag" INTEGER
);


-- Class is AngebotspositionenDatabaseLayerGateway
CREATE TABLE "Angebotspositionen" (
"ID" INTEGER PRIMARY KEY,

"Menge" DECIMAL,

"Preis" DECIMAL
);


-- Class is RechnungDatabaseLayerGateway
CREATE TABLE "Rechnung" (
"ID" INTEGER PRIMARY KEY,

"Rechnungsnummer" INTEGER,

"Rechnungsdatum" DATE,

"Gesamtpreis" DECIMAL,

"Rechnungspositionen" INTEGER
);


-- Class is RechnungspositionenDatabaseLayerGateway
CREATE TABLE "Rechnungspositionen" (
"ID" INTEGER PRIMARY KEY,

"Preis" DECIMAL,

"menge" INTEGER
);


-- Class is LieferantDatabaseLayerGateway
CREATE TABLE "Lieferant" (
"ID" INTEGER PRIMARY KEY,

"Lieferantennummer" INTEGER,

"Name" CHAR(100),

"Artikel" INTEGER
);


-- Class is KontakteDatabaseLayerGateway
CREATE TABLE "Kontakte" (
"ID" INTEGER PRIMARY KEY,

"Name" CHAR(100),

"Vorname" CHAR(100),

"Telefon" CHAR(100),

"Fax" CHAR(100),

"eMail" CHAR(100),

"Bild" BYTEA,

"Notiz" TEXT,

"Kunde" INTEGER,

"Konkurrenten" INTEGER
);


-- Class is KonkurrentenDatabaseLayerGateway
CREATE TABLE "Konkurrenten" (
"ID" INTEGER PRIMARY KEY,

"Firmenname" CHAR(100),

"Webadresse" CHAR(100),

"Kurzbeschreibung" CHAR(100),

"Langbeschreibung" TEXT
);




-- Association Lieferant -> Adresse with name 
ALTER TABLE "Lieferant" ADD CONSTRAINT "fk_Lieferant_Adresse_ID" FOREIGN KEY ( "Adresse" )
   REFERENCES "Adresse" ( "ID" );



-- Association Kunde -> Adresse with name 
ALTER TABLE "Kunde" ADD CONSTRAINT "fk_Kunde_Adresse_ID" FOREIGN KEY ( "Adresse" )
   REFERENCES "Adresse" ( "ID" );



-- Association Konkurrenten -> Adresse with name 
ALTER TABLE "Konkurrenten" ADD CONSTRAINT "fk_Konkurrenten_Adresse_ID" FOREIGN KEY ( "Adresse" )
   REFERENCES "Adresse" ( "ID" );



-- Association Rechnung -> Kunde with name 
ALTER TABLE "Rechnung" ADD CONSTRAINT "fk_Rechnung_Kunde_ID" FOREIGN KEY ( "Kunde" )
   REFERENCES "Kunde" ( "ID" );



-- Association Auftrag -> Kunde with name 
ALTER TABLE "Auftrag" ADD CONSTRAINT "fk_Auftrag_Kunde_ID" FOREIGN KEY ( "Kunde" )
   REFERENCES "Kunde" ( "ID" );



-- Association Angebot -> Kunde with name 
ALTER TABLE "Angebot" ADD CONSTRAINT "fk_Angebot_Kunde_ID" FOREIGN KEY ( "Kunde" )
   REFERENCES "Kunde" ( "ID" );



-- Association Auftragspositionen -> Auftrag with name 
ALTER TABLE "Auftragspositionen" ADD CONSTRAINT "fk_Auftragspositionen_Auftrag_ID" FOREIGN KEY ( "Auftrag" )
   REFERENCES "Auftrag" ( "ID" );



-- Association Rechnung -> Auftrag with name 
ALTER TABLE "Rechnung" ADD CONSTRAINT "fk_Rechnung_Auftrag_ID" FOREIGN KEY ( "Auftrag" )
   REFERENCES "Auftrag" ( "ID" );



-- Association Auftrag -> Auftragspositionen with name 
ALTER TABLE "Auftrag" ADD CONSTRAINT "fk_Auftrag_Auftragspositionen_ID" FOREIGN KEY ( "Auftragspositionen" )
   REFERENCES "Auftragspositionen" ( "ID" );



-- Association Angebotspositionen -> Artikel with name 
ALTER TABLE "Angebotspositionen" ADD CONSTRAINT "fk_Angebotspositionen_Artikel_ID" FOREIGN KEY ( "Artikel" )
   REFERENCES "Artikel" ( "ID" );



-- Association Auftragspositionen -> Artikel with name 
ALTER TABLE "Auftragspositionen" ADD CONSTRAINT "fk_Auftragspositionen_Artikel_ID" FOREIGN KEY ( "Artikel" )
   REFERENCES "Artikel" ( "ID" );



-- Association Rechnungspositionen -> Artikel with name 
ALTER TABLE "Rechnungspositionen" ADD CONSTRAINT "fk_Rechnungspositionen_Artikel_ID" FOREIGN KEY ( "Artikel" )
   REFERENCES "Artikel" ( "ID" );



-- Association Angebotspositionen -> Angebot with name 
ALTER TABLE "Angebotspositionen" ADD CONSTRAINT "fk_Angebotspositionen_Angebot_ID" FOREIGN KEY ( "Angebot" )
   REFERENCES "Angebot" ( "ID" );



-- Association Auftrag -> Angebot with name 
ALTER TABLE "Auftrag" ADD CONSTRAINT "fk_Auftrag_Angebot_ID" FOREIGN KEY ( "Angebot" )
   REFERENCES "Angebot" ( "ID" );



-- Association Rechnungspositionen -> Rechnung with name 
ALTER TABLE "Rechnungspositionen" ADD CONSTRAINT "fk_Rechnungspositionen_Rechnung_ID" FOREIGN KEY ( "Rechnung" )
   REFERENCES "Rechnung" ( "ID" );



-- Association Artikel -> Lieferant with name 
ALTER TABLE "Artikel" ADD CONSTRAINT "fk_Artikel_Lieferant_ID" FOREIGN KEY ( "Lieferant" )
   REFERENCES "Lieferant" ( "ID" );



-- Association Kunde -> Kontakte with name 
ALTER TABLE "Kunde" ADD CONSTRAINT "fk_Kunde_Kontakte_ID" FOREIGN KEY ( "Kontakte" )
   REFERENCES "Kontakte" ( "ID" );



-- Association Konkurrenten -> Kontakte with name 
ALTER TABLE "Konkurrenten" ADD CONSTRAINT "fk_Konkurrenten_Kontakte_ID" FOREIGN KEY ( "Kontakte" )
   REFERENCES "Kontakte" ( "ID" );
