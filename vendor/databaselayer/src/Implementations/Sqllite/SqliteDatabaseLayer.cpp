#include "../include/DatabaseLayerDLLExport.h"
#include "../include/SqliteDatabaseLayer.h"
#include "../include/SqliteResultSet.h"
#include "../include/SqlitePreparedStatement.h"
#include "../include/DatabaseErrorCodes.h"
#include "../include/DatabaseLayerException.h"

#ifdef __WATCOMC__
extern "C" {
#include <sqlitefk/src/sql.h>
}
#endif

#ifndef __WATCOMC__
#include <sqlitefk/src/sql.h>
#endif

#include <wx/tokenzr.h>

// ctor()
SqliteDatabaseLayer::SqliteDatabaseLayer()
 : DatabaseLayer()
{
  m_pDatabase = NULL; //&m_Database; //new sqlite3;
  wxCSConv conv(_("UTF-8"));
  SetEncoding(&conv);
  m_fklist = NULL;
  m_schema = NULL;
}

SqliteDatabaseLayer::SqliteDatabaseLayer(const wxString& strDatabase)
 : DatabaseLayer()
{
  m_pDatabase = NULL; //new sqlite3;
  wxCSConv conv(_("UTF-8"));
  SetEncoding(&conv);
  Open(strDatabase);
  m_fklist = NULL;
  m_schema = NULL;
}

// dtor()
SqliteDatabaseLayer::~SqliteDatabaseLayer()
{
  //wxPrintf(_("~SqliteDatabaseLayer()\n"));

  if (m_fklist) list_destroy((List*)m_fklist);

  Close();
  //wxDELETE(m_pDatabase);
}

// open database
bool SqliteDatabaseLayer::Open(const wxString& strDatabase)
{
  ResetErrorCodes();

  //if (m_pDatabase == NULL)
  //  m_pDatabase = new sqlite3;

  dbName = strDatabase;

  wxCharBuffer databaseNameBuffer = ConvertToUnicodeStream(strDatabase);
  int nReturn = sqlite3_open(databaseNameBuffer, &m_pDatabase);
  if (nReturn != SQLITE_OK)
  {
    SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
    SetErrorMessage(ConvertFromUnicodeStream(sqlite3_errmsg(m_pDatabase)));
    ThrowDatabaseException();
    return false;
  }
  
#ifdef SUPPORT_FOREIGN_KEYS

#endif
  
  return true;
}

// close database  
bool SqliteDatabaseLayer::Close()
{
  ResetErrorCodes();

  CloseResultSets();
  CloseStatements();

  if (m_pDatabase != NULL)
  {
#ifdef SUPPORT_FOREIGN_KEYS

#endif
  
    int nReturn = sqlite3_close(m_pDatabase);
    if (nReturn != SQLITE_OK)
    {
      const char* err_msg = NULL;
      char* open_statements = NULL;

      sqlite3_stmt* pStmt = NULL;
      const char* zSql = NULL;
      pStmt = sqlite3_next_stmt(m_pDatabase, pStmt);

      err_msg = sqlite3_errmsg(m_pDatabase);
      SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));


      if (pStmt != NULL) {
          zSql = sqlite3_sql(pStmt);
          open_statements = (char*) malloc(strlen(err_msg) + strlen(zSql) + 2 + 1);
          open_statements[0] = 0;
          open_statements = strcat(open_statements, err_msg);
          open_statements = strcat(open_statements, zSql);
          open_statements = strcat(open_statements, ", \n");

        while ((pStmt = sqlite3_next_stmt(m_pDatabase, pStmt)) != NULL) {
          char* temp = NULL;
          temp = (char*) malloc(strlen(open_statements) + strlen(zSql) + 2 + 1);
          temp[0] = 0;
          temp = strcat(temp, open_statements);
          temp = strcat(temp, zSql);
          temp = strcat(temp, ", \n");
          free(open_statements);
          open_statements = temp;
        }
        SetErrorMessage(open_statements);
      } else {
        SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
        SetErrorMessage(ConvertFromUnicodeStream(err_msg));
      }

    
      ThrowDatabaseException();
      return false;
    }
    m_pDatabase = NULL;
  }

  return true;
}

bool SqliteDatabaseLayer::IsOpen()
{
  return (m_pDatabase != NULL);
}

void SqliteDatabaseLayer::BeginTransaction()
{
  wxLogDebug(_("Beginning transaction"));
  RunQuery(_("begin transaction;"), false);
}

void SqliteDatabaseLayer::Commit()
{
  wxLogDebug(_("Commiting transaction"));
  RunQuery(_("commit transaction;"), false);
}

void SqliteDatabaseLayer::RollBack()
{
  wxLogDebug(_("Rolling back transaction"));
  RunQuery(_("rollback transaction;"), false);
}

// query database
bool SqliteDatabaseLayer::RunQuery(const wxString& strQuery, bool bParseQuery)
{
  ResetErrorCodes();

  if (m_pDatabase == NULL)
    return false;

  wxArrayString QueryArray;
	
	//                               Skippable when this is in the query. (CREATE UNIQUE INDEX would otherwise propably fail)
	if ((!strQuery.Upper().Contains("SKIP REWRITE")) && (strQuery.Upper().Contains("CREATE") || strQuery.Upper().Contains("ALTER"))) {
		// Assume, this is a DDL. Rewrite it so that it creates the meta database with information of
		// foreign keys.
		wxString rewrittenQuery;
		if (!TableExists(wxString("lbDMF_ForeignKeys"))) {
			wxString createSystemTables;
			
			createSystemTables = 
			wxString("CREATE TABLE \"lbDMF_ForeignKeys\" (") +
			wxString("	\"PKTable\" BPCHAR,") +
			wxString("	\"PKColumn\" BPCHAR,") +
			wxString("	\"FKTable\" BPCHAR,") +
			wxString("	\"FKColumn\" BPCHAR") +
			wxString(");\n");
			rewrittenQuery = createSystemTables + wxString(rewriteSchemaOfDDL((char*) strQuery.c_str()));
		} else {
			rewrittenQuery = wxString(rewriteSchemaOfDDL((char*) strQuery.c_str()));
		}
		wxString strErrorMessage = _("");
		char* szErrorMessage = NULL;
		int nReturn = sqlite3_exec(m_pDatabase, rewrittenQuery.c_str(), 0, 0, &szErrorMessage);
		if (szErrorMessage != NULL)
		{
			SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
			strErrorMessage = ConvertFromUnicodeStream(szErrorMessage);
			printf(strErrorMessage);
			sqlite3_free(szErrorMessage);
			return NULL;
		}
		return NULL;
	}	
	
  if (bParseQuery)
    QueryArray = ParseQueries(strQuery);
  else
    QueryArray.push_back(strQuery);

  wxArrayString::iterator start = QueryArray.begin();
  wxArrayString::iterator stop = QueryArray.end();

  while (start != stop)
  {
    char* szErrorMessage = NULL;
    wxString strErrorMessage = _("");
    wxCharBuffer sqlBuffer = ConvertToUnicodeStream(*start);
    int nReturn = sqlite3_exec(m_pDatabase, sqlBuffer, 0, 0, &szErrorMessage);
  
	  if (nReturn == SQLITE_BUSY) {
		  wxLogError(_("Error, busy condition.\n"));
	  }
	  
    if (szErrorMessage != NULL)
    {
      strErrorMessage = ConvertFromUnicodeStream(szErrorMessage);
      sqlite3_free(szErrorMessage);
    }

    if (nReturn != SQLITE_OK)
    {
      SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
      SetErrorMessage(strErrorMessage);
      ThrowDatabaseException();
      return false;
    }

    start++;
  }
  return true;
}

DatabaseResultSet* SqliteDatabaseLayer::RunQueryWithResults(const wxString& strQuery)
{
  ResetErrorCodes();

  if (m_pDatabase != NULL)
  {
    wxArrayString QueryArray;
	//                               Skippable when this is in the query. (CREATE UNIQUE INDEX would otherwise propably fail)
	if ((!strQuery.Upper().Contains("SKIP REWRITE")) && (strQuery.Upper().Contains("CREATE") || strQuery.Upper().Contains("ALTER"))) {
		// Assume, this is a DDL. Rewrite it so that it creates the meta database with information of
		// foreign keys.
		wxString rewrittenQuery;
		if (!TableExists(wxString("lbDMF_ForeignKeys"))) {
			wxString createSystemTables;
			
			createSystemTables = 
			wxString("CREATE TABLE \"lbDMF_ForeignKeys\" (") +
			wxString("	\"PKTable\" BPCHAR,") +
			wxString("	\"PKColumn\" BPCHAR,") +
			wxString("	\"FKTable\" BPCHAR,") +
			wxString("	\"FKColumn\" BPCHAR") +
			wxString(");\n");
			rewrittenQuery = createSystemTables + wxString(rewriteSchemaOfDDL((char*) strQuery.c_str()));
		} else {
			rewrittenQuery = wxString(rewriteSchemaOfDDL((char*) strQuery.c_str()));
		}
      wxString strErrorMessage = _("");
      char* szErrorMessage = NULL;
	  int nReturn = sqlite3_exec(m_pDatabase, rewrittenQuery.c_str(), 0, 0, &szErrorMessage);
      if (szErrorMessage != NULL)
      {
        SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
        strErrorMessage = ConvertFromUnicodeStream(szErrorMessage);
		printf(strErrorMessage);
        sqlite3_free(szErrorMessage);
        return NULL;
      }
	  return NULL;
	} else {
		if (strQuery.Upper().Contains("SKIP REWRITE")) {
			wxString strErrorMessage = _("");
			char* szErrorMessage = NULL;
			int nReturn = sqlite3_exec(m_pDatabase, strQuery.c_str(), 0, 0, &szErrorMessage);
			if (szErrorMessage != NULL)
			{
				SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
				strErrorMessage = ConvertFromUnicodeStream(szErrorMessage);
				printf("SqliteDatabaseLayer::RunQueryWithResults(...) Error: %s\n", strErrorMessage.c_str());
				sqlite3_free(szErrorMessage);
				return NULL;
			}
			printf("SqliteDatabaseLayer::RunQueryWithResults(...) Succeeded direct statement.\n");
			return NULL;
		}
		QueryArray = ParseQueries(strQuery);
    }
	 
    for (unsigned int i=0; i<(QueryArray.size()-1); i++)
    {
      char* szErrorMessage = NULL;
      wxString strErrorMessage = _("");
      wxString sqlBuffer = ConvertToUnicodeStream(QueryArray[i]);

	  int nReturn = sqlite3_exec(m_pDatabase, sqlBuffer.c_str(), 0, 0, &szErrorMessage);
	    
      if (szErrorMessage != NULL)
      {
        SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
        strErrorMessage = ConvertFromUnicodeStream(szErrorMessage);
        sqlite3_free(szErrorMessage);
        return NULL;
      }

      if (nReturn != SQLITE_OK)
      {
        SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(sqlite3_errcode(m_pDatabase)));
        SetErrorMessage(strErrorMessage);
        ThrowDatabaseException();
        return NULL;
      }
    }

    // Create a Prepared statement for the last SQL statement and get a result set from it
    SqlitePreparedStatement* pStatement = (SqlitePreparedStatement*)PrepareStatement(QueryArray[QueryArray.size()-1], false);
    SqliteResultSet* pResultSet = new SqliteResultSet(pStatement, true);
    if (pResultSet) {
      pResultSet->SetEncoding(GetEncoding());
	}
	
    LogResultSetForCleanup(pResultSet);
    return pResultSet;
  }
  else
  {
    printf("Error: SqliteDatabaseLayer::RunQueryWithResults() has no database handle!\n");
    return NULL;
  }
}

PreparedStatement* SqliteDatabaseLayer::PrepareStatement(const wxString& strQuery)
{
  return PrepareStatement(strQuery, true);
}

PreparedStatement* SqliteDatabaseLayer::PrepareStatement(const wxString& strQuery, bool bLogForCleanup)
{
  ResetErrorCodes();

  if (m_pDatabase != NULL)
  {
    SqlitePreparedStatement* pReturnStatement = new SqlitePreparedStatement(m_pDatabase);
    if (pReturnStatement)
      pReturnStatement->SetEncoding(GetEncoding());
    
    wxArrayString QueryArray = ParseQueries(strQuery);

    wxArrayString::iterator start = QueryArray.begin();
    wxArrayString::iterator stop = QueryArray.end();

    while (start != stop)
    {
      const char* szTail=0;
      wxCharBuffer sqlBuffer;
      do
      {
        sqlite3_stmt* pStatement;
        wxString strSQL;
        if (szTail != 0)
        {
          strSQL = (wxChar*)szTail;
        }
        else
        {
          strSQL = (*start);
        }
        sqlBuffer = ConvertToUnicodeStream(strSQL);
#if SQLITE_VERSION_NUMBER>=3003009
        int nReturn = sqlite3_prepare_v2(m_pDatabase, sqlBuffer, -1, &pStatement, &szTail);
#else
        int nReturn = sqlite3_prepare(m_pDatabase, sqlBuffer, -1, &pStatement, &szTail);
#endif
   
        if (nReturn != SQLITE_OK)
        {
          SetErrorCode(SqliteDatabaseLayer::TranslateErrorCode(nReturn));
          SetErrorMessage(ConvertFromUnicodeStream(sqlite3_errmsg(m_pDatabase)));
          wxDELETE(pReturnStatement);
          ThrowDatabaseException();
          return NULL;
        }
        pReturnStatement->AddPreparedStatement(pStatement);

	  }
#if wxUSE_UNICODE
      while (strlen(szTail) > 0);
#else
      while (wxStrlen(szTail) > 0);
#endif    
      
      start++;
    }

    if (bLogForCleanup)
      LogStatementForCleanup(pReturnStatement);
    return pReturnStatement;
  }
  else
  {
    return NULL;
  }
}

bool SqliteDatabaseLayer::TableExists(const wxString& table)
{
  // Initialize variables
  bool bReturn = false;
  // Keep these variables outside of scope so that we can clean them up
  //  in case of an error
  PreparedStatement* pStatement = NULL;
  DatabaseResultSet* pResult = NULL;

#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  try
  {
#endif
    wxString query = _("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name=?;");
    pStatement = PrepareStatement(query);
    if (pStatement)
    {
      pStatement->SetParamString(1, table);
      pResult = pStatement->ExecuteQuery();
      if (pResult)
      {
        if (pResult->Next())
        {
          if(pResult->GetResultInt(1) != 0)
          {
            bReturn = true;
          }
        }
      }
    }
#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  }
  catch (DatabaseLayerException& e)
  {
    if (pResult != NULL)
    {
      CloseResultSet(pResult);
      pResult = NULL;
    }

    if (pStatement != NULL)
    {
      CloseStatement(pStatement);
      pStatement = NULL;
    }

    throw e;
  }
#endif

  if (pResult != NULL)
  {
    CloseResultSet(pResult);
    pResult = NULL;
  }

  if (pStatement != NULL)
  {
    CloseStatement(pStatement);
    pStatement = NULL;
  }

  return bReturn;
}

bool SqliteDatabaseLayer::ViewExists(const wxString& view)
{
  // Initialize variables
  bool bReturn = false;
  // Keep these variables outside of scope so that we can clean them up
  //  in case of an error
  PreparedStatement* pStatement = NULL;
  DatabaseResultSet* pResult = NULL;

#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  try
  {
#endif
    wxString query = _("SELECT COUNT(*) FROM sqlite_master WHERE type='view' AND name=?;");
    pStatement = PrepareStatement(query);
    if (pStatement)
    {
      pStatement->SetParamString(1, view);
      pResult = pStatement->ExecuteQuery();
      if (pResult)
      {
        if (pResult->Next())
        {
          if(pResult->GetResultInt(1) != 0)
          {
            bReturn = true;
          }
        }
      }
    }
#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  }
  catch (DatabaseLayerException& e)
  {
    if (pResult != NULL)
    {
      CloseResultSet(pResult);
      pResult = NULL;
    }

    if (pStatement != NULL)
    {
      CloseStatement(pStatement);
      pStatement = NULL;
    }

    throw e;
  }
#endif

  if (pResult != NULL)
  {
    CloseResultSet(pResult);
    pResult = NULL;
  }

  if (pStatement != NULL)
  {
    CloseStatement(pStatement);
    pStatement = NULL;
  }

  return bReturn;
}

bool SqliteDatabaseLayer::GetColumnNullable(const wxString& table, const wxString& column) {
	char const *pzDataType;    /* OUTPUT: Declared data type */
	char const *pzCollSeq;     /* OUTPUT: Collation sequence name */
	int pNotNull;              /* OUTPUT: True if NOT NULL constraint exists */
	int pPrimaryKey;           /* OUTPUT: True if column part of PK */
	int pAutoinc;               /* OUTPUT: True if column is auto-increment */

	sqlite3_table_column_metadata(
								  m_pDatabase,		/* Connection handle */
								  NULL,				/* Database name or NULL */
								  table.c_str(),		/* Table name */
								  column.c_str(), /* Column name */
								  &pzDataType,		/* OUTPUT: Declared data type */
								  &pzCollSeq,			/* OUTPUT: Collation sequence name */
								  &pNotNull,			/* OUTPUT: True if NOT NULL constraint exists */
								  &pPrimaryKey,		/* OUTPUT: True if column part of PK */
								  &pAutoinc			/* OUTPUT: True if column is auto-increment */
								  );

	return !pNotNull;
}

int SqliteDatabaseLayer::GetPrimaryKeys(const wxString& table) {
  int count = 0;
  char const *pzDataType;    /* OUTPUT: Declared data type */
  char const *pzCollSeq;     /* OUTPUT: Collation sequence name */
  int pNotNull;              /* OUTPUT: True if NOT NULL constraint exists */
  int pPrimaryKey;           /* OUTPUT: True if column part of PK */
  int pAutoinc;               /* OUTPUT: True if column is auto-increment */

  arrPrimaryColumns.Clear();
  arrPrimarySequence.Clear();
  
  wxArrayString columns = GetColumns(table);
  
  for (int i = 0; i < columns.Count(); i++) {
	sqlite3_table_column_metadata(
		m_pDatabase,		/* Connection handle */
		NULL,				/* Database name or NULL */
		table.c_str(),		/* Table name */
		columns[i].c_str(), /* Column name */
		&pzDataType,		/* OUTPUT: Declared data type */
		&pzCollSeq,			/* OUTPUT: Collation sequence name */
		&pNotNull,			/* OUTPUT: True if NOT NULL constraint exists */
		&pPrimaryKey,		/* OUTPUT: True if column part of PK */
		&pAutoinc			/* OUTPUT: True if column is auto-increment */
		);

	if (pPrimaryKey == 1) {
			arrPrimaryColumns.Add(columns[i]);
			arrPrimarySequence.Add(wxString(pzCollSeq));
			count++;
	}
  }
  return count;
}

wxString& SqliteDatabaseLayer::GetPrimaryKeyColumn(const int index) {
	return arrPrimaryColumns[index];
}

wxString& SqliteDatabaseLayer::GetPrimaryKeySequence(const int index) {
	return arrPrimarySequence[index];
}


int SqliteDatabaseLayer::GetForeignKeys(const wxString& table) {
	wxString sysQ = wxString("select PKColumn, PKTable, FKColumn from lbDMF_ForeignKeys where FKTable = '");
	sysQ += table;
	sysQ += "'";

	DatabaseResultSet* system_query = RunQueryWithResults(sysQ);
	arrFKCols.Clear();
	arrPKCols.Clear();
	arrPKTables.Clear();

	if (system_query != NULL) {
		while (system_query->Next()) {
			wxString PKColumn =	system_query->GetResultString(1);
			wxString PKTable =	system_query->GetResultString(2);
			wxString FKColumn =	system_query->GetResultString(3);


			arrFKCols.Add(FKColumn);
			arrPKCols.Add(PKColumn);
			arrPKTables.Add(PKTable);
		}
		
		CloseResultSet(system_query);
		system_query = NULL;
		
		return arrFKCols.Count();
	}

	return 0;
}

wxString& SqliteDatabaseLayer::GetForeignKeyFKColumn(const int index) {
	return arrFKCols[index];
}

wxString& SqliteDatabaseLayer::GetForeignKeyPKColumn(const int index) {
	return arrPKCols[index];
}

wxString& SqliteDatabaseLayer::GetForeignKeyPKTable(const int index) {
	return arrPKTables[index];
}


wxArrayString SqliteDatabaseLayer::GetTables()
{
  wxArrayString returnArray;

  DatabaseResultSet* pResult = NULL;
#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  try
  {
#endif
    wxString query = _("SELECT name FROM sqlite_master WHERE type='table';");
    pResult = ExecuteQuery(query);

    while (pResult->Next())
    {
      returnArray.Add(pResult->GetResultString(1));
    }
#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  }
  catch (DatabaseLayerException& e)
  {
    if (pResult != NULL)
    {
      CloseResultSet(pResult);
      pResult = NULL;
    }

    throw e;
  }
#endif

  if (pResult != NULL)
  {
    CloseResultSet(pResult);
    pResult = NULL;
  }

  return returnArray;
}

wxArrayString SqliteDatabaseLayer::GetViews()
{
  wxArrayString returnArray;

  DatabaseResultSet* pResult = NULL;
#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  try
  {
#endif
    wxString query = _("SELECT name FROM sqlite_master WHERE type='view';");
    pResult = ExecuteQuery(query);

    while (pResult->Next())
    {
      returnArray.Add(pResult->GetResultString(1));
    }
#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  }
  catch (DatabaseLayerException& e)
  {
    if (pResult != NULL)
    {
      CloseResultSet(pResult);
      pResult = NULL;
    }

    throw e;
  }
#endif

  if (pResult != NULL)
  {
    CloseResultSet(pResult);
    pResult = NULL;
  }

  return returnArray;
}

wxArrayString SqliteDatabaseLayer::GetColumns(const wxString& table)
{
    wxArrayString returnArray;

  // Keep these variables outside of scope so that we can clean them up
  //  in case of an error
  DatabaseResultSet* pResult = NULL;
  ResultSetMetaData* pMetaData = NULL;

#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  try
  {
#endif
    wxCharBuffer tableNameBuffer = ConvertToUnicodeStream(table);
    wxString query = wxString::Format(_("SELECT * FROM '%s' LIMIT 0;"), table.c_str());
    pResult = ExecuteQuery(query);
    pResult->Next();
    pMetaData = pResult->GetMetaData();

    // 1-based
    for(int i=1; i<=pMetaData->GetColumnCount(); i++)
    {
      returnArray.Add(pMetaData->GetColumnName(i));
    }

#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS
  }
  catch (DatabaseLayerException& e)
  {
    if (pMetaData != NULL)
    {
      pResult->CloseMetaData(pMetaData);
      pMetaData = NULL;
    }

    if (pResult != NULL)
    {
      CloseResultSet(pResult);
      pResult = NULL;
    }

    throw e;
  }
#endif

  if (pMetaData != NULL)
  {
    pResult->CloseMetaData(pMetaData);
    pMetaData = NULL;
  }

  if (pResult != NULL)
  {
    CloseResultSet(pResult);
    pResult = NULL;
  }

  return returnArray;
}

int SqliteDatabaseLayer::TranslateErrorCode(int nCode)
{
  // Ultimately, this will probably be a map of SQLite database error code values to DatabaseLayer values
  // For now though, we'll just return error
  int nReturn = nCode;
  /*
  switch (nCode)
  {
    case SQLITE_ERROR:
      nReturn = DATABASE_LAYER_SQL_SYNTAX_ERROR;
      break;
    case SQLITE_INTERNAL:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_PERM:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_ABORT:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_BUSY:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_LOCKED:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_NOMEM:
      nReturn = DATABASE_LAYER_ALLOCATION_ERROR;
      break;
    case SQLITE_READONLY:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_INTERRUPT:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_IOERR:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_CORRUPT:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_NOTFOUND:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_FULL:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_CANTOPEN:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_PROTOCOL:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_SCHEMA:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_TOOBIG:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_CONSTRAINT:
      nReturn = DATABASE_LAYER_CONSTRAINT_VIOLATION;
      break;
    case SQLITE_MISMATCH:
      nReturn = DATABASE_LAYER_INCOMPATIBLE_FIELD_TYPE;
      break;
    case SQLITE_MISUSE:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_NOLFS:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    case SQLITE_AUTH:
      nReturn = DATABASE_LAYER_ERROR;
      break;
    default:
      nReturn = DATABASE_LAYER_ERROR;
      break;
  }
  */
  return nReturn;
}

