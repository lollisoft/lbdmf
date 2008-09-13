/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {      
#endif            
#ifndef OSX
#include <conio.h>
#endif
#ifdef __cplusplus
}
#endif            

#include <stdio.h>
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif
//#include "testdll.h"

#include <lbConfigHook.h>

lb_I_Unknown* findPluginByInterfaceAndNamespace(char* _interface, char* _namespace) {
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Plugin, pl)
		
	pl = PM->getFirstMatchingPlugin(_interface, _namespace);
	
		
	if (pl != NULL) {
				_CL_LOG << "References to plugin wrapper instance: " << pl->getRefCount() LOG_
       	        uk = pl->getImplementation();
       	        uk++;
       	        return uk.getPtr();
	}
	return NULL;
}

lb_I_Database* loadDatabase() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Database, DatabaseWrapper)
	UAP(lb_I_Unknown, ukDatabaseWrapper)
	ukDatabaseWrapper = findPluginByInterfaceAndNamespace("lb_I_Database", "DatabaseLayerGateway");
	
	if (ukDatabaseWrapper == NULL) {
		_CL_LOG << "Database regression tests failed. Database gateway plugin not found." LOG_
		//preloaddb.resetPtr();
		//preloaddb = NULL;
		PM->unload();
		unHookAll();
		exit(1);
	} else {
		QI(ukDatabaseWrapper, lb_I_Database, DatabaseWrapper)
		if (DatabaseWrapper == NULL) {
			_CL_LOG << "Database regression tests failed. Database gateway plugin has not the expected interface." LOG_
			//preloaddb.resetPtr();
			PM->unload();
			unHookAll();
			exit(1);
		}
	}
	DatabaseWrapper++;
	return DatabaseWrapper.getPtr();
}

void initAndConnect(lb_I_Database* db, char* dbname) {
	db->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	db->connect(dbname, dbname, lbDMFUser, lbDMFPasswd);
}

void dropTables(lb_I_Query* q) {
	q->skipFKCollecting();
	q->query("-- Skip rewrite\n" "drop table regressiontest");
	q->query("-- Skip rewrite\n" "drop table test");
	q->query("-- Skip rewrite\n" "drop table test1");
}

void createTables(lb_I_Query* q) {
	char* buf = "-- Skip rewrite\n"
	"create table regressiontest ("
	"id INTEGER PRIMARY KEY, "
	//"test char(100) DEFAULT 'Nothing', "
	"test BPCHAR DEFAULT 'Nothing', "
	"btest bool DEFAULT false, "
	"btest1 bool DEFAULT false)";
	
	q->skipFKCollecting();
	q->query(buf);
	
	
	buf = 
	"CREATE TABLE \"test\" ("
	"	id INTEGER PRIMARY KEY,"
	"	test TEXT,"
	"	id_reg INTEGER"
	");\n"
	"CREATE TABLE \"test1\" ("
	"	id1 INTEGER PRIMARY KEY,"
	"	test1 BPCHAR,"
	"	id_reg INTEGER"
	");\n"
	"ALTER TABLE \"test1\" ADD CONSTRAINT \"cst_test_id_reg1\" FOREIGN KEY ( \"id_reg\" ) REFERENCES \"regressiontest\" ( \"id\" );\n"
	"ALTER TABLE \"test\" ADD CONSTRAINT \"cst_test_id_reg\" FOREIGN KEY ( \"id_reg\" ) REFERENCES \"regressiontest\" ( \"id\" )\n";
	
	//printf("\n\nCreate database schema:\n%s\n\n", buf);
	
	// I have problems which collecting foreign key data, if no result sets are there.
	q->skipFKCollecting();
	q->query(buf);
}

void initDatabaseA(lb_I_Query* q) {
	char* buf = "-- Skip rewrite\n"
	"create table regressiontest ("
	"id INTEGER PRIMARY KEY, "
	//"test char(100) DEFAULT 'Nothing', "
	"test BPCHAR DEFAULT 'Nothing', "
	"btest bool DEFAULT false, "
	"btest1 bool DEFAULT false)";
	
	q->skipFKCollecting();
	q->query(buf);

	buf = 
	"CREATE TABLE \"test\" ("
	"	id INTEGER PRIMARY KEY,"
	"	test BPCHAR,"
	"	id_reg INTEGER"
	");\n"
	"CREATE TABLE \"test1\" ("
	"	id1 INTEGER PRIMARY KEY,"
	"	test1 BPCHAR,"
	"	id_reg1 INTEGER"
	");\n"
	"ALTER TABLE \"test1\" ADD CONSTRAINT \"cst_test_id_reg1\" FOREIGN KEY ( \"id_reg1\" ) REFERENCES \"regressiontest\" ( \"id\" );\n"
	"ALTER TABLE \"test\" ADD CONSTRAINT \"cst_test_id_reg\" FOREIGN KEY ( \"id_reg\" ) REFERENCES \"regressiontest\" ( \"id\" )\n";
	
	//printf("\n\nCreate database schema:\n%s\n\n", buf);
	
	// I have problems which collecting foreign key data, if no result sets are there.
	q->skipFKCollecting();
	q->query(buf);
}

void initDatabaseB(lb_I_Query* q) {
	char* buf = "-- Skip rewrite\n"
	"create table regressiontest ("
	"	\"ID\" INTEGER PRIMARY KEY,"
	"	test BPCHAR DEFAULT 'Nothing', "
	"	btest bool DEFAULT false, "
	"	btest1 bool DEFAULT false)";
	
	q->skipFKCollecting();
	q->query(buf);
	
	buf = 
	"CREATE TABLE \"test\" ("
	"	\"ID\" INTEGER PRIMARY KEY,"
	"	test BPCHAR,"
	"	id_reg INTEGER"
	");\n"
	"CREATE TABLE \"test1\" ("
	"	\"ID\" INTEGER PRIMARY KEY,"
	"	test BPCHAR,"
	"	id_reg INTEGER"
	");\n"
	"ALTER TABLE \"test1\" ADD CONSTRAINT \"cst_test_id_reg1\" FOREIGN KEY ( \"id_reg\" ) REFERENCES \"regressiontest\" ( \"ID\" );\n"
	"ALTER TABLE \"test\" ADD CONSTRAINT \"cst_test_id_reg\" FOREIGN KEY ( \"id_reg\" ) REFERENCES \"regressiontest\" ( \"ID\" )\n";
	
	//printf("\n\nCreate database schema:\n%s\n\n", buf);
	
	// I have problems which collecting foreign key data, if no result sets are there.
	q->skipFKCollecting();
	q->query(buf);
}

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

{
#ifdef WINDOWS
	TRMemOpen();
	TRMemSetModuleName(__FILE__);
#endif	
	
	mm = getModuleInstance();

	UAP_REQUEST(mm, lb_I_String, preload)
	UAP_REQUEST(mm, lb_I_PluginManager, PM)
	
	PM->initialize();

#ifdef bla
	_CL_LOG << "Database regression tests..." LOG_
	{
		//UAP_REQUEST(mm, lb_I_Database, preloaddb)
		UAP(lb_I_Database, DatabaseWrapper)
		UAP(lb_I_Database, DatabaseWrapper1)
		UAP(lb_I_Database, DatabaseWrapper2)
		
		DatabaseWrapper = loadDatabase();
		DatabaseWrapper1 = loadDatabase();
		DatabaseWrapper2 = loadDatabase();
			
		initAndConnect(*&DatabaseWrapper, "lbDMF");

		UAP(lb_I_Query, query2)
		UAP(lb_I_Query, query3)
		UAP(lb_I_Query, queryA)
		UAP(lb_I_Query, query)
		UAP(lb_I_Query, query1)
		
		query = DatabaseWrapper->getQuery("lbDMF", 0);
		query1 = DatabaseWrapper->getQuery("lbDMF", 0);

		dropTables(*&query1);	
		
		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_

		createTables(*&query);
		
		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_

		insertTestdata(*&query1);

		UAP(lb_I_Query, queryread1)
		UAP(lb_I_Query, queryinsert1)
		UAP(lb_I_Query, queryinsert2)

		queryread1 = DatabaseWrapper->getQuery("lbDMF", 0);
		queryread1->enableFKCollecting();

		queryinsert1 = DatabaseWrapper->getQuery("lbDMF", 0);

		err = queryinsert1->query("--Skip Rewrite\ndelete from \"foreignkey_visibledata_mapping\" where \"fkname\" = '...'");
		err = queryinsert1->query("--Skip Rewrite\ninsert into \"foreignkey_visibledata_mapping\" (\"fkname\", \"fktable\", \"pkname\", \"pktable\") values('...', '...', '...', '...')");
		err = queryinsert1->query("--Skip Rewrite\ninsert into \"foreignkey_visibledata_mapping\" (\"fkname\", \"fktable\", \"pkname\", \"pktable\") values('...', '...', '...', '...')");

		queryinsert1->query("select id, fkname, fktable, pkname, pktable from foreignkey_visibledata_mapping");
		queryinsert1->PrintData();

		err = queryread1->query("select id, test, id_reg from test");

		if (err != ERR_NONE) {
			_CL_LOG << "Error: Query 'select id, test, id_reg from test' failed." LOG_
		}

		err = queryread1->first();
		
		if ((err == ERR_NONE) || (err == ERR_DB_NODATA)) {
			_CL_LOG << "Error: No data found for query." LOG_
		}

		queryread1->close();
		DatabaseWrapper->close();

		DatabaseWrapper->open("lbDMF");
		queryinsert2 = DatabaseWrapper->getQuery("lbDMF", 0);
		err = queryinsert2->query("--Skip Rewrite\ninsert into \"foreignkey_visibledata_mapping\" (\"fkname\", \"fktable\", \"pkname\", \"pktable\") values('...', '...', '...', '...')");

		queryread1->open();

		queryinsert2->query("select id, fkname, fktable, pkname, pktable from foreignkey_visibledata_mapping");
		queryinsert2->PrintData();

		//query1->enableFKCollecting();
		
		query1 = DatabaseWrapper->getQuery("lbDMF", 0);
		query1->query("select id, test, btest, btest1 from regressiontest");
		
		query1->PrintData();
		query1->PrintData(true);
		
		DatabaseWrapper1->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		DatabaseWrapper1->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		DatabaseWrapper2->init();
		
		lbDMFPasswd = getenv("lbDMFPasswd");
		lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		DatabaseWrapper2->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		query2 = DatabaseWrapper1->getQuery("lbDMF", 0);
		query2->skipPeeking();
		query2->query("select test, id, btest, btest1 from regressiontest");
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, column)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		
		query2->last();
		*column = "test";
		*value = "Updated column";
		query2->setString(*&column, *&value);
		*column = "btest";
		*value = "0";
		query2->setString(*&column, *&value);
		query2->update();
		
		query2->add();
		*column = "test";
		*value = "Inserted column";
		query2->setString(*&column, *&value);
		*column = "btest";
		*value = "0";
		query2->setString(*&column, *&value);
		query2->update();
		
		query2->PrintData();
		query2->enableFKCollecting();
		query2->query("select * from test1");
		int fkcolumns = query2->getFKColumns();
		
		UAP(lb_I_String, tn)
		UAP(lb_I_String, cn)
		cn = query2->getColumnName(1);
		tn = query2->getTableName(cn->charrep());
		
		_CL_LOG << "Have " << fkcolumns << " foreign keys in table " << tn->charrep() << "." LOG_

		for (int i = 1; i <= fkcolumns; i++) {
			UAP(lb_I_String, s)
			s = query2->getFKColumn(i);
			_CL_LOG << "Foreign key " << s->charrep() LOG_
		}

		query3 = DatabaseWrapper2->getQuery("lbDMF", 0);

		query3->enableFKCollecting();
		query3->query("select * from test");
		fkcolumns = query3->getFKColumns();
		
		cn = query3->getColumnName(1);
		tn = query3->getTableName(cn->charrep());

		_CL_LOG << "Have " << fkcolumns << " foreign keys in table " << tn->charrep() << "." LOG_
		
		for (int ii = 1; ii <= fkcolumns; ii++) {
			UAP(lb_I_String, s)
			s = query3->getFKColumn(ii);
			_CL_LOG << "Foreign key " << s->charrep() LOG_
		}
		
		UAP(lb_I_Container, tables)
		
		tables = DatabaseWrapper2->getTables("lbDMF");
		
		_CL_LOG << "Tables in database: "  LOG_

		while (tables->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_String, s)
			
			uk = tables->nextElement();
			
			QI(uk, lb_I_String, s)

			if (s != NULL) {
				if (s->charrep() == NULL) {
					_CL_LOG << "Table: ''" LOG_
				} else {
					_CL_LOG << "Table: " << s->charrep() LOG_
				}
			} else {
				_CL_LOG << "Error: Haven't got a table string object." LOG_
			}
		}

		UAP(lb_I_Container, columns)
		
		columns = DatabaseWrapper2->getColumns("lbDMF");
		
		_CL_LOG << "Columns in tables: "  LOG_

		while (columns->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_Parameter, param)
			
			uk = columns->nextElement();
			
			QI(uk, lb_I_Parameter, param)
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP_REQUEST(getModuleInstance(), lb_I_String, tableName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, columnName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, columnType)
			
			*name = "TableName";
			param->getUAPString(*&name, *&tableName);

			*name = "ColumnName";
			param->getUAPString(*&name, *&columnName);

			*name = "TypeName";
			param->getUAPString(*&name, *&columnType);
			
			_CL_LOG << "TableName: " << tableName->charrep() << ", ColumnName: " << columnName->charrep() << ", TypeName: " << columnType->charrep() LOG_
		}
		
		UAP(lb_I_Container, foreignkeys)
		
		foreignkeys = DatabaseWrapper2->getForeignKeys("lbDMF");
		
		_CL_LOG << "Foreign keys in lbDMF: "  LOG_
		_CL_LOG << "********************** "  LOG_

		while (foreignkeys->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_Parameter, param)
			
			uk = foreignkeys->nextElement();
			
			QI(uk, lb_I_Parameter, param)
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP_REQUEST(getModuleInstance(), lb_I_String, pktableName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, pkcolumnName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, fktableName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, fkcolumnName)
			
			*name = "PKTableName";
			param->getUAPString(*&name, *&pktableName);

			*name = "PKTableColumnName";
			param->getUAPString(*&name, *&pkcolumnName);

			*name = "FKTableName";
			param->getUAPString(*&name, *&fktableName);

			*name = "FKTableColumnName";
			param->getUAPString(*&name, *&fkcolumnName);
			
			_CL_LOG << "PKTableName: " << pktableName->charrep() << ", PKTableColumnName: " << pkcolumnName->charrep() << ", FKTableName: " << fktableName->charrep() << ", FKTableColumnName: " << fkcolumnName->charrep() LOG_
		}
		
		UAP(lb_I_Container, primarykeys)
		
		primarykeys = DatabaseWrapper2->getPrimaryKeys("lbDMF");
		
		_CL_LOG << "Primary keys in lbDMF: "  LOG_
		_CL_LOG << "********************** "  LOG_

		while (primarykeys->hasMoreElements() == 1) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_Parameter, param)
			
			uk = primarykeys->nextElement();
			
			QI(uk, lb_I_Parameter, param)
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP_REQUEST(getModuleInstance(), lb_I_String, pktableName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, pkcolumnName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, pkkeySequence)
			
			*name = "TableName";
			param->getUAPString(*&name, *&pktableName);

			*name = "ColumnName";
			param->getUAPString(*&name, *&pkcolumnName);

			*name = "KeySequence";
			param->getUAPString(*&name, *&pkkeySequence);
			
			_CL_LOG << "TableName: " << pktableName->charrep() << ", ColumnName: " << pkcolumnName->charrep() << ", KeySequence: " << pkkeySequence->charrep() LOG_
		}
		
		UAP(lb_I_Query, queryread)
		UAP(lb_I_Query, queryinsert)
			
		queryread = DatabaseWrapper->getQuery("lbDMF", 0);
		err = queryread->query("select * from test");

		if (err != ERR_NONE) {
			_CL_LOG << "Error: Query 'select * from test' failed." LOG_
		}

		err = queryread->first();
		
		if ((err == ERR_NONE) || (err == ERR_DB_NODATA)) {
			_CL_LOG << "Error: No data found for query." LOG_
		}
		
		queryinsert = DatabaseWrapper->getQuery("lbDMF", 0);

		err = queryinsert->query("insert into test1 (test1) values ('bla')");

		if (err != ERR_NONE) {
			_CL_LOG << "Error: Insert into table failed." LOG_
		}
		
		_CL_LOG << "Done testing DatabaseLayer wrapper." LOG_

		//preloaddb.resetPtr();
	}
#endif
	
	_CL_LOG << "Test two database files reopening problem ..." LOG_
	
	{
		UAP(lb_I_Database, DatabaseWrapper)
		UAP(lb_I_Database, DatabaseWrapper1)
		UAP(lb_I_Query, query)
		UAP(lb_I_Query, query1)
		UAP(lb_I_Query, query2)
		UAP(lb_I_Query, queryLock)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		UAP_REQUEST(getModuleInstance(), lb_I_String, column)

		DatabaseWrapper = loadDatabase();
		DatabaseWrapper1 = loadDatabase();
		
		initAndConnect(*&DatabaseWrapper, "Database A");
		initAndConnect(*&DatabaseWrapper1, "Database B");

		query = DatabaseWrapper->getQuery("Database A", 0);
		query1 = DatabaseWrapper1->getQuery("Database B", 0);
		query2 = DatabaseWrapper1->getQuery("Database B", 0);

		_CL_LOG << "Print data from Database A ..." LOG_
		
		query->query("select ID, test, btest, btest1 from regressiontest");
		query->first();
		if (query->first() == ERR_NONE) {
			query->PrintData(false);
		}
		query->query("select ID, test, id_reg from test");
		query->first();
		if (query->first() == ERR_NONE) {
			query->PrintData(false);
		}
		
		_CL_LOG << "Print data from Database B ..." LOG_

		query1->query("select ID, test, btest, btest1 from regressiontest");
		query1->first();
		if (query1->first() == ERR_NONE) {
			query1->PrintData(false);
		}
		query1->query("select ID, test, id_reg from test");
		query1->first();
		if (query1->first() == ERR_NONE) {
			query1->PrintData(false);
		}
		
		_CL_LOG << "Recreate the tables ..." LOG_
		
		DatabaseWrapper->close();
		query--;
		query.resetPtr();
		query1--;
		query1.resetPtr();

		query = DatabaseWrapper->getQuery("Database A", 0);
		query1 = DatabaseWrapper1->getQuery("Database B", 0);

		dropTables(*&query);
		dropTables(*&query1);
		
		initDatabaseA(*&query);
		initDatabaseB(*&query1);
		
		_CL_LOG << " Insert test data ..." LOG_
		
		// Create initial data and close.
		query->query("insert into regressiontest (test,btest,btest1) values('Bla 1', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 1', 1, 0)");
		query->query("insert into regressiontest (test,btest,btest1) values('Bla 2', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 2', 1, 0)");
		query->query("insert into regressiontest (test,btest,btest1) values('Bla 3', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 3', 1, 0)");
		DatabaseWrapper->close();
		query--;
		query.resetPtr();
		query1--;
		query1.resetPtr();
		
		_CL_LOG << "Closed database to begin test ..." LOG_

		query1 = DatabaseWrapper1->getQuery("Database B", 0);
		query1->query("select ID, test, id_reg from test");
		query1->first();
		
		_CL_LOG << "Print data from Database B (must be empty before lock) ..." LOG_
		if (query1->first() == ERR_NONE) {
			query1->PrintData(false);
		}
		
		_CL_LOG << "Change in Database B to lock on regressiontest ..." LOG_

		queryLock = DatabaseWrapper1->getQuery("Database B", 0);
		queryLock->query("select ID, test, btest, btest1 from regressiontest");
		queryLock->first();
		
		*column = "test";
		*value = "some value";
		queryLock->setString(*&column, *&value);
		
		*column = "btest";
		*value = "false";
		queryLock->setString(*&column, *&value);
		
		*column = "btest1";
		*value = "true";
		queryLock->setString(*&column, *&value);
		queryLock->update();

		_CL_LOG << "Try add in Database B on test ..." LOG_

		query1->add();

		*column = "test";
		*value = "some other value 1 ";

		UAP_REQUEST(getModuleInstance(), lb_I_BinaryData, binary)
		
		int len = strlen(value->charrep()+1);
		void* buffer = malloc(len);
		memcpy(buffer, value->charrep(), len);
		binary->setData(buffer, len);
		free(buffer);
		query1->setBinaryData(column->charrep(), *&binary);

		*column = "id_reg";
		*value = "1";
		query1->setString(*&column, *&value);
		
		query1->update();

		query1->add();
		*column = "test";
		*value = "some other value 2 ";

		len = strlen(value->charrep()+1);
		buffer = malloc(len);
		memcpy(buffer, value->charrep(), len);
		binary->setData(buffer, len);
		free(buffer);
		query1->setBinaryData(column->charrep(), *&binary);

		*column = "id_reg";
		*value = "1";
		query1->setString(*&column, *&value);

		query1->update();
		query1->first();
		query1->PrintData(false);

		
		_CL_LOG "Now Database B, test has added data, but not finished. Try to change some of them in a new query." LOG_
		query2 = DatabaseWrapper1->getQuery("Database B", 0);

		if (query2->query("select ID, test, id_reg from test") != ERR_NONE) {
			_CL_LOG << "Error: Failed to create query." LOG_
		}
		query2->first();

		*column = "id_reg";
		*value = "1";
		query2->setString(*&column, *&value);

		*column = "test";
		*value = "some modified value 2 ";
		len = strlen(value->charrep()+1);
		buffer = malloc(len);
		memcpy(buffer, value->charrep(), len);
		binary->setData(buffer, len);
		free(buffer);
		query2->setBinaryData(column->charrep(), *&binary);
		
		query2->update();
		query2->first();
		query2->PrintData(false);
		
		query = DatabaseWrapper->getQuery("Database A", 0);
		query->query("select ID, test, btest, btest1 from regressiontest");
		query->first();
		
		*column = "test";
		*value = "some value";
		query->setString(*&column, *&value);
		
		*column = "btest";
		*value = "false";
		query->setString(*&column, *&value);
		
		*column = "btest1";
		*value = "true";
		query->setString(*&column, *&value);
		query->update();
		
		query1->close();
		DatabaseWrapper1->close();

		_CL_LOG << "Print data from Database B ..." LOG_

		query1->open();
		if (query1->first() == ERR_NONE) {
			query1->PrintData(false);
		}
		
		query1->close();
		DatabaseWrapper1->close();
		
		query1->open();
		if (query1->first() == ERR_NONE) {
			query1->PrintData(false);
		}
		
		_CL_LOG << "Print data from Database A ..." LOG_

		query->open();
		if (query->first() == ERR_NONE) {
			query->PrintData(false);
		}
		
	}
	
	PM->unload();
	//unHookAll();

}

        return 0;
}
