/*...s\35\ifdef LBXMLCONFIG_EXPORTS:0:*/
#ifdef LBXMLCONFIG_EXPORTS
#define LBXMLCONFIG_API __declspec(dllexport)
#else
#define LBXMLCONFIG_API __declspec(dllimport)
#endif
/*...e*/

#pragma warning(disable:4786)

/*...sincludes:0:*/
#include <lbErrCodes.h>
#include <lbInterfaces.h>
/*...e*/

#ifndef __LB_HOST_CFG__
#define __LB_HOST_CFG__

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

lbErrCodes LBXMLCONFIG_API __cdecl getlbXMLConfigInstance(lb_I_XMLConfig*& inst);

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif // __LB_HOST_CFG__
