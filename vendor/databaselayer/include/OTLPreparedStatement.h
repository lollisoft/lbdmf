#ifndef __OTL_PREPARED_STATEMENT_H__
#define __OTL_PREPARED_STATEMENT_H__

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

#include "wx/dynarray.h"

#include "PreparedStatement.h"

#ifndef OTL_STREAM_READ_ITERATOR_ON
  #define OTL_STREAM_READ_ITERATOR_ON
#endif
#include "otlv4.h"

WX_DEFINE_ARRAY_PTR(otl_stream*, OTLStatementVector);

class DLLEXPORT OTLPreparedStatement : public PreparedStatement
{
public:
  // ctor
  OTLPreparedStatement(otl_connect* pEnvironment);
  OTLPreparedStatement(otl_connect* pEnvironment, otl_stream* pStatement);

  // dtor
  virtual ~OTLPreparedStatement();

  virtual void Close();

  void AddStatement(otl_stream* pStatement);

  // get field
  virtual void SetParamInt(int nPosition, int nValue);
  virtual void SetParamDouble(int nPosition, double dblValue);
  virtual void SetParamString(int nPosition, const wxString& strValue);
  virtual void SetParamNull(int nPosition);
  virtual void SetParamBlob(int nPosition, const void* pData, long nDataLength);
  virtual void SetParamDate(int nPosition, const wxDateTime& dateValue);
  virtual void SetParamBool(int nPosition, bool bValue);
  virtual int GetParameterCount();

  virtual void RunQuery();
  virtual DatabaseResultSet* RunQueryWithResults();

private:
  int FindStatementAndAdjustPositionIndex(int* pPosition);

  OTLStatementVector m_Statements;
  otl_connect* m_pEnvironment;  // Needed to create Date objects
};

#endif // __OTL_PREPARED_STATEMENT_H__

