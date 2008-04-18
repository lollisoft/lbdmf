
-- Unknown stereotype '' for class Activities.
		
-- Generate application table Activities for lbDMF Manager
-- CREATE TABLE Activities
CREATE TABLE "Activities" (

	--,
	"Name" BPCHAR,
	--,
	"UmlId" BPCHAR,
	--,
	"ID" INTEGER PRIMARY KEY
)
;
-- Unknown stereotype '' for class ActivityNodes.
		
-- Generate application table ActivityNodes for lbDMF Manager
-- CREATE TABLE ActivityNodes
CREATE TABLE "ActivityNodes" (
--,
	--,
	"Name" BPCHAR,
	"Stereotype" BPCHAR,
	"UmlId" BPCHAR,
	"NodeType" BPCHAR,
	"Body" BPCHAR,
	--,
	--,
	--,
	"ID" INTEGER PRIMARY KEY
)
;
-- Unknown stereotype '' for class ControlFlow.
		
-- Generate application table ControlFlow for lbDMF Manager
-- CREATE TABLE ControlFlow
CREATE TABLE "ControlFlow" (
--,
	"Name" BPCHAR,
	"Expression" BPCHAR,--,
	"UmlId" BPCHAR,
	"Stereotype" BPCHAR,--,
	"ID" INTEGER PRIMARY KEY
)
;
-- Unknown stereotype '' for class DecisionPath.
		
-- Generate application table DecisionPath for lbDMF Manager
-- CREATE TABLE DecisionPath
CREATE TABLE "DecisionPath" (

	"Name" BPCHAR,
	"UmlId" BPCHAR,--,--,--,
	"Stereotype" BPCHAR,
	"ID" INTEGER PRIMARY KEY
)

-- Unknown stereotype '' for class Activities.
;
-- Generate application table Activities for lbDMF Manager
ALTER TABLE "ActivityNodes" ADD CONSTRAINT "cst_ActivityNodes_Activities_Activities" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );

ALTER TABLE "ControlFlow" ADD CONSTRAINT "cst_ControlFlow_Activities_Activities" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );

ALTER TABLE "DecisionPath" ADD CONSTRAINT "cst_DecisionPath_Activities_Activities" FOREIGN KEY ( "Activities" ) REFERENCES "Activities" ( "ID" );

-- Unknown stereotype '' for class ActivityNodes.

-- Generate application table ActivityNodes for lbDMF Manager
ALTER TABLE "ControlFlow" ADD CONSTRAINT "cst_ControlFlow_Source1_ActivityNodes" FOREIGN KEY ( "Source1" ) REFERENCES "ActivityNodes" ( "ID" );

ALTER TABLE "DecisionPath" ADD CONSTRAINT "cst_DecisionPath_Source2_ActivityNodes" FOREIGN KEY ( "Source2" ) REFERENCES "ActivityNodes" ( "ID" );

ALTER TABLE "DecisionPath" ADD CONSTRAINT "cst_DecisionPath_Target2_ActivityNodes" FOREIGN KEY ( "Target2" ) REFERENCES "ActivityNodes" ( "ID" );

ALTER TABLE "ControlFlow" ADD CONSTRAINT "cst_ControlFlow_Target1_ActivityNodes" FOREIGN KEY ( "Target1" ) REFERENCES "ActivityNodes" ( "ID" );

-- Unknown stereotype '' for class ControlFlow.

-- Generate application table ControlFlow for lbDMF Manager
-- Unknown stereotype '' for class DecisionPath.

-- Generate application table DecisionPath for lbDMF Manager