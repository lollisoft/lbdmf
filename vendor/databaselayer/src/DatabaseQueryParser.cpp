#include "../include/DatabaseLayerDLLExport.h"
#include "../include/DatabaseQueryParser.h"

bool IsEmptyQuery(const wxString& strQuery)
{
  wxString strQueryCopy(strQuery);
  strQueryCopy.Replace(_(";"), _(""));  // Remove all query delimiting semi-colons
  return (strQueryCopy.Trim(true).Trim(false) == wxEmptyString);
}

wxArrayString ParseQueries(const wxString& strQuery)
{
  wxArrayString returnArray;
  bool bInQuote = false;
  int nLast = 0;

  for ( int i=0; i<(int)strQuery.Length(); i++ )
  {
      if ( strQuery.SubString(i, i) == _T("'") || strQuery.SubString(i, i) == _T("\""))
          bInQuote = !bInQuote;
      else if ( strQuery.SubString(i, i) == _T(";") && !bInQuote )
      {
          wxString str;
          str << strQuery.SubString(nLast, i);
          if (!IsEmptyQuery(str))
		  {
			printf("ParseQueries('%s') found a query: %s.\n", strQuery.c_str(), str.c_str());
            returnArray.Add( str );
		  }
          nLast = i + 1;
      }
  }

  if ( nLast < (int)strQuery.Length() -1 )
  {
      wxString str;
      str << strQuery.SubString(nLast, strQuery.Length() - 1) << _T(";");
      if (!IsEmptyQuery(str))
	  {
		printf("ParseQueries('%s') found a query: %s.\n", strQuery.c_str(), str.c_str());
        returnArray.Add( str );
	  }
  }

  return returnArray;
}

