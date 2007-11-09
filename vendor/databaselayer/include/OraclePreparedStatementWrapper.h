#ifndef __ORACLE_PREPARED_STATEMENT_WRAPPER_H__
#define __ORACLE_PREPARED_STATEMENT_WRAPPER_H__

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

#include "DatabaseStringConverter.h"

#include "occi.h"

class DLLEXPORT OraclePreparedStatementWrapper : public DatabaseStringConverter
{
  public:
    // ctor
    OraclePreparedStatementWrapper(oracle::occi::Connection* m_pDatabase, const wxString& strSQL);

    // dtor
    virtual ~OraclePreparedStatementWrapper();

    oracle::occi::Statement* GetStatement() { return m_pStatement; }
    int GetParameterCount() { return m_nParameterCount; }

  private:
    wxString TranslateSQL(const wxString& strOriginalSQL);

    oracle::occi::Statement* m_pStatement;
    int m_nParameterCount;
};

#endif // __ORACLE_PREPARED_STATEMENT_WRAPPER_H__

