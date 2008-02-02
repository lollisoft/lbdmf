#ifndef __SQLITE_DATABASE_LAYER_H__
#define __SQLITE_DATABASE_LAYER_H__

#ifdef WINDOWS
 #ifndef DLLEXPORT
  #define DLLEXPORT __declspec(dllimport)
 #endif
#endif
#ifndef WINDOWS
 #define DLLEXPORT
#endif


// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/arrstr.h"

#include "DatabaseLayer.h"

#include <sqlite3.h>

class PreparedStatement;

class DLLEXPORT SqliteDatabaseLayer : public DatabaseLayer
{
public:
  // ctor()
  SqliteDatabaseLayer();
  SqliteDatabaseLayer(const wxString& strDatabase);
  SqliteDatabaseLayer(sqlite3* pDatabase) { m_pDatabase = pDatabase; }
  
  // dtor()
  virtual ~SqliteDatabaseLayer();
  
  // open database
  virtual bool Open(const wxString& strDatabase);
  
  // close database  
  virtual bool Close();
  
  // Is the connection to the database open?
  virtual bool IsOpen();

  // transaction support
  virtual void BeginTransaction();
  virtual void Commit();
  virtual void RollBack();
  
  // query database
  virtual bool RunQuery(const wxString& strQuery, bool bParseQuery);
  virtual DatabaseResultSet* RunQueryWithResults(const wxString& strQuery);
  
  // PreparedStatement support
  virtual PreparedStatement* PrepareStatement(const wxString& strQuery);
  PreparedStatement* PrepareStatement(const wxString& strQuery, bool bLogForCleanup);
  
  // Database schema API contributed by M. Szeftel (author of wxActiveRecordGenerator)
  virtual bool TableExists(const wxString& table);
  virtual bool ViewExists(const wxString& view);
  virtual wxArrayString GetTables();
  virtual wxArrayString GetViews();
  virtual wxArrayString GetColumns(const wxString& table);

  virtual int GetPrimaryKeys(const wxString& table);

  virtual wxString& GetPrimaryKeyColumn(const int index);

  virtual wxString& GetPrimaryKeySequence(const int index);

  virtual int GetForeignKeys(const wxString& table);

  /// Retrieve the foreign key column name
  virtual wxString& GetForeignKeyFKColumn(const int index);

  /// Retrieve the primary key column name of the current foreign key
  virtual wxString& GetForeignKeyPKColumn(const int index);

  /// Retrieve the primary key table name of the current foreign key
  virtual wxString& GetForeignKeyPKTable(const int index);

  static int TranslateErrorCode(int nCode);

private:
  wxArrayString arrFKCols;
  wxArrayString arrPKCols;
  wxArrayString arrPKTables;
  
  wxArrayString arrPrimaryColumns;
  wxArrayString arrPrimarySequence;
  
  void* m_fklist;
  sqlite3* m_pDatabase;
};

#endif // __SQLITE_DATABASE_LAYER_H__

