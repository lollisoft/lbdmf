CREATE TABLE "Activities" (
	"ID" INTEGER,
	"Name" BPCHAR,
	"UmlId" BPCHAR
);

ALTER TABLE "Activities" ADD CONSTRAINT "Activities_pkey" PRIMARY KEY ("ID");

CREATE TABLE "Activities1" (
	"ID" INTEGER,
	"Name" BPCHAR,
	"UmlId" BPCHAR
);
ALTER TABLE "Activities1" ADD CONSTRAINT "Activities1_pkey" PRIMARY KEY ("ID");

ALTER TABLE "ActivityNodes" ADD CONSTRAINT "cst_Activities_ID_ActivityNodes_Activities_20" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );

ALTER TABLE "ActivityNodes" ADD CONSTRAINT "cst_Activities_ID_ActivityNodes_Activities_20" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );

