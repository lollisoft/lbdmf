#ifndef __ORACLE_RESULT_SET_METADATA_H__
#define __ORACLE_RESULT_SET_METADATA_H__

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

#include "occi.h"
#include <vector>

class DLLEXPORT OracleResultSetMetaData : public ResultSetMetaData
{
public:
  // ctor
  OracleResultSetMetaData(std::vector<oracle::occi::MetaData> metaData);

  // dtor
  virtual ~OracleResultSetMetaData() { }

  virtual int GetColumnType(int i);
  virtual int GetColumnSize(int i);
  virtual wxString GetColumnName(int i);
  virtual int GetColumnCount();
  virtual int GetPrimaryKeys() { return 0; }
  virtual wxString GetPrimaryKey(int i) { return wxString(""); }
  
private:
  std::vector<oracle::occi::MetaData> m_MetaData;
};

#endif // __ORACLE_RESULT_SET_METADATA_H__
