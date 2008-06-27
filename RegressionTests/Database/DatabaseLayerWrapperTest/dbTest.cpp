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
	
	//PM->initialize();
	
	{
		UAP_REQUEST(mm, lb_I_PluginManager, PM)
		//UAP_REQUEST(mm, lb_I_Database, preloaddb)
		UAP(lb_I_Unknown, ukDatabaseWrapper)
		UAP(lb_I_Database, DatabaseWrapper)
		
		UAP(lb_I_Unknown, ukDatabaseWrapper1)
		UAP(lb_I_Database, DatabaseWrapper1)

		UAP(lb_I_Unknown, ukDatabaseWrapper2)
		UAP(lb_I_Database, DatabaseWrapper2)
		
		
		ukDatabaseWrapper = findPluginByInterfaceAndNamespace("lb_I_Database", "DatabaseLayerGateway");
		
		if (ukDatabaseWrapper == NULL) {
			_CL_LOG << "Database regression tests failed. Database gateway plugin not found." LOG_
			//preloaddb.resetPtr();
			//preloaddb = NULL;
			PM->unload();
			unHookAll();
			return 0;
		} else {
			QI(ukDatabaseWrapper, lb_I_Database, DatabaseWrapper)
			if (DatabaseWrapper == NULL) {
				_CL_LOG << "Database regression tests failed. Database gateway plugin has not the expected interface." LOG_
				//preloaddb.resetPtr();
				PM->unload();
				unHookAll();
				return 0;
			}
		}
		
		ukDatabaseWrapper1 = findPluginByInterfaceAndNamespace("lb_I_Database", "DatabaseLayerGateway");
		
		if (ukDatabaseWrapper1 == NULL) {
			_CL_LOG << "Database regression tests failed. Database gateway plugin not found." LOG_
			return 0;
		} else {
			QI(ukDatabaseWrapper1, lb_I_Database, DatabaseWrapper1)
			if (DatabaseWrapper1 == NULL) {
				_CL_LOG << "Database regression tests failed. Database gateway plugin has not the expected interface." LOG_
				return 0;
			}
		}

		ukDatabaseWrapper2 = findPluginByInterfaceAndNamespace("lb_I_Database", "DatabaseLayerGateway");
		
		if (ukDatabaseWrapper2 == NULL) {
			_CL_LOG << "Database regression tests failed. Database gateway plugin not found." LOG_
			return 0;
		} else {
			QI(ukDatabaseWrapper2, lb_I_Database, DatabaseWrapper2)
			if (DatabaseWrapper2 == NULL) {
				_CL_LOG << "Database regression tests failed. Database gateway plugin has not the expected interface." LOG_
				return 0;
			}
		}
		
		_CL_LOG << "Database regression tests..." LOG_
			
		DatabaseWrapper->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		DatabaseWrapper->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		UAP(lb_I_Query, query2)
		UAP(lb_I_Query, query3)
		UAP(lb_I_Query, queryA)
		UAP(lb_I_Query, query)
		UAP(lb_I_Query, query1)
			
			
		
		query = DatabaseWrapper->getQuery("lbDMF", 0);
		
		
		query1 = DatabaseWrapper->getQuery("lbDMF", 0);
		query1->skipFKCollecting();
		query1->query("-- Skip rewrite\n" "drop table regressiontest");
		query1->query("-- Skip rewrite\n" "drop table test");
		query1->query("-- Skip rewrite\n" "drop table test1");
	
		
		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_

		char* buf = "-- Skip rewrite\n"
			"create table regressiontest ("
			"id INTEGER PRIMARY KEY, "
			//"test char(100) DEFAULT 'Nothing', "
			"test BPCHAR DEFAULT 'Nothing', "
			"btest bool DEFAULT false, "
			"btest1 bool DEFAULT false)";
			
		query->skipFKCollecting();
		query->query(buf);
			
			
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

		printf("\n\nCreate database schema:\n%s\n\n", buf);

		// I have problems which collecting foreign key data, if no result sets are there.
		query->skipFKCollecting();
		query->query(buf);
		
		_CL_LOG << "query has " << query->getRefCount() << " references." LOG_
			
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 1', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 2', 0, 1)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 3', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 4', 0, 1)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 5', 1, 0)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 6', 0, 1)");
		query1->query("insert into regressiontest (test,btest,btest1) values('Bla 7', 1, 0)");

		query1->query("insert into test (test,id_reg) values('Bla 1',1)");
		query1->query("insert into test (test,id_reg) values('Bla 2',1)");
		query1->query("insert into test (test,id_reg) values('Bla 3',1)");
		query1->query("insert into test (test,id_reg) values('Bla 4',1)");
		query1->query("insert into test (test,id_reg) values('Bla 5',1)");
		query1->query("insert into test (test,id_reg) values('Bla 6',1)");
		query1->query("insert into test (test,id_reg) values('Bla 7',1)");

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
		
		lbDMFPasswd = getenv("lbDMFPasswd");
		lbDMFUser   = getenv("lbDMFUser");
		
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
			
			_CL_LOG << "Table: " << s->charrep() LOG_
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
		PM->unload();
		unHookAll();
	}

}

        return 0;
}
