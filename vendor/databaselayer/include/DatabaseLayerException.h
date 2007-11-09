#ifndef __DATABASE_LAYER_EXCEPTION_H__
#define __DATABASE_LAYER_EXCEPTION_H__

#ifdef WINDOWS
 #ifndef DLLEXPORT
  #define DLLEXPORT __declspec(dllimport)
 #endif
#endif
#ifndef WINDOWS
 #define DLLEXPORT
#endif

#ifndef DONT_USE_DATABASE_LAYER_EXCEPTIONS

class DLLEXPORT DatabaseLayerException
{
public:
  DatabaseLayerException(int nCode, const wxString& strError)
  {
    m_nErrorCode = nCode;
    m_strErrorMessage = strError;
  }

  const wxString& GetErrorMessage() const { return m_strErrorMessage; }
  const int GetErrorCode() const { return m_nErrorCode; }
  
  // Add functions for stack traces ??
private:
  wxString m_strErrorMessage;
  int m_nErrorCode;  
};

#endif // DONT_USE_DATABASE_LAYER_EXCEPTIONS

#endif // __DATABASE_LAYER_EXCEPTION_H__
