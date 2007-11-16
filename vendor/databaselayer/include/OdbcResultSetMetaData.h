#ifndef __ODBC_RESULT_SET_METADATA_H__
#define __ODBC_RESULT_SET_METADATA_H__

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

#include <sql.h>
#include <sqlext.h>

class DLLEXPORT OdbcResultSetMetaData : public ResultSetMetaData
{
public:
  // ctor
  OdbcResultSetMetaData(SQLHSTMT sqlOdbcStatement);

  // dtor
  virtual ~OdbcResultSetMetaData() { }

  virtual int GetColumnType(int i);
  virtual int GetColumnSize(int i);
  virtual wxString GetColumnName(int i);
  virtual int GetColumnCount();
  virtual int GetPrimaryKeys() { return 0; }
  virtual wxString GetPrimaryKey(int i) { return wxString(""); }
  virtual wxString GetTableForColumn(int) { return wxString(""); }
  virtual wxString GetTableForColumn(wxString) { return wxString(""); }
  
private:

  SQLHSTMT m_pOdbcStatement;
};

#endif // __ODBC_RESULT_SET_METADATA_H__
