#ifndef __SQLITE_RESULT_SET_METADATA_H__
#define __SQLITE_RESULT_SET_METADATA_H__

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

#include "ResultSetMetaData.h"

#include "sqlite3.h"

class DLLEXPORT SqliteResultSetMetaData : public ResultSetMetaData
{
public:
  // ctor
  SqliteResultSetMetaData(sqlite3_stmt* pStmt);

  virtual int GetColumnType(int i);
  virtual int GetColumnSize(int i);
  virtual wxString GetColumnName(int i);
  virtual int GetColumnCount();
  virtual wxString GetTableForColumn(int i);
  virtual wxString GetTableForColumn(wxString column);

private:
  sqlite3_stmt* m_pSqliteStatement;
};

#endif // __SQLITE_RESULT_SET_METADATA_H__
