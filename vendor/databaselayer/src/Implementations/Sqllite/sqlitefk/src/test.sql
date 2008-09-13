-- Association Templates -> Template
-- Drop a constraint

-- Association Templates -> Includes
-- Drop a constraint

-- Association Template -> TemplateParameters
-- Drop a constraint

-- Association Template -> Dependencies
-- Drop a constraint

-- Association Template -> Dependencies
-- Drop a constraint

-- Association Template -> Includes
-- Drop a constraint

-- Association Cartridge -> Templates
-- Drop a constraint

-- Class is TemplatesDatabaseLayerGateway
CREATE TABLE "Templates" (
"ID" INTEGER PRIMARY KEY,

"Name" CHAR(100),

"Purpose" CHAR(100),

"Description" TEXT,

"Aproved" BOOL,

"Cartridge" INTEGER
);


-- Class is TemplateDatabaseLayerGateway
CREATE TABLE "Template" (
"ID" INTEGER PRIMARY KEY,

"Name" CHAR(100),

"Description" TEXT,

"Code" TEXT,

"Aproved" BOOL,

"Templates" INTEGER
);


-- Class is TemplateParametersDatabaseLayerGateway
CREATE TABLE "TemplateParameters" (
"ID" INTEGER PRIMARY KEY,

"Name" CHAR(100),

"Description" TEXT,

"Template" INTEGER
);


-- Class is ValidatorDatabaseLayerGateway
CREATE TABLE "Validator" (
"ID" INTEGER PRIMARY KEY
);


-- Class is DependenciesDatabaseLayerGateway
CREATE TABLE "Dependencies" (
"ID" INTEGER PRIMARY KEY,

"Description" TEXT,

"Purpose" CHAR(100),

"Template" INTEGER,

"Template" INTEGER
);


-- Class is IncludesDatabaseLayerGateway
CREATE TABLE "Includes" (
"ID" INTEGER PRIMARY KEY,

"Description" TEXT,

"Purpose" CHAR(100),

"Templates" INTEGER,

"Template" INTEGER
);


-- Class is CartridgeDatabaseLayerGateway
CREATE TABLE "Cartridge" (
"ID" INTEGER PRIMARY KEY,

"Name" CHAR(100),

"Descrption" TEXT,

"Purpose" CHAR(100)
);




-- Association Template -> Templates with name 
ALTER TABLE "Template" ADD CONSTRAINT "fk_Template_Templates_ID" FOREIGN KEY ( "Templates" )
   REFERENCES "Templates" ( "ID" );



-- Association Includes -> Templates with name XSLTFile
ALTER TABLE "Includes" ADD CONSTRAINT "fk_Includes_TemplatesXSLTFile_ID" FOREIGN KEY ( "TemplatesXSLTFile" )
   REFERENCES "Templates" ( "ID" );



-- Association TemplateParameters -> Template with name 
ALTER TABLE "TemplateParameters" ADD CONSTRAINT "fk_TemplateParameters_Template_ID" FOREIGN KEY ( "Template" )
   REFERENCES "Template" ( "ID" );



-- Association Dependencies -> Template with name RequiredBy
ALTER TABLE "Dependencies" ADD CONSTRAINT "fk_Dependencies_TemplateRequiredBy_ID" FOREIGN KEY ( "TemplateRequiredBy" )
   REFERENCES "Template" ( "ID" );



-- Association Dependencies -> Template with name Requires
ALTER TABLE "Dependencies" ADD CONSTRAINT "fk_Dependencies_TemplateRequires_ID" FOREIGN KEY ( "TemplateRequires" )
   REFERENCES "Template" ( "ID" );



-- Association Includes -> Template with name Template
ALTER TABLE "Includes" ADD CONSTRAINT "fk_Includes_TemplateTemplate_ID" FOREIGN KEY ( "TemplateTemplate" )
   REFERENCES "Template" ( "ID" );



-- Association Templates -> Cartridge with name 
ALTER TABLE "Templates" ADD CONSTRAINT "fk_Templates_Cartridge_ID" FOREIGN KEY ( "Cartridge" )
   REFERENCES "Cartridge" ( "ID" );

