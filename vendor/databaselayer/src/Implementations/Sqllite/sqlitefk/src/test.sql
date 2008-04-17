
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
