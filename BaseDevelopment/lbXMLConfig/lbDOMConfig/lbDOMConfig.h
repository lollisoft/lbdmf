/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lbDOMConfig.h,v 1.1 2000/10/20 04:24:52 lothar Exp $
 *
 * $Log: lbDOMConfig.h,v $
 * Revision 1.1  2000/10/20 04:24:52  lothar
 * Initial
 *
 **************************************************************/

/*...e*/

#ifndef __LB_DOM_CONFIG__
#define __LB_DOM_CONFIG__

/*...s\35\ifdef LBXMLCONFIG_EXPORTS:0:*/
#ifdef LBDOMCONFIG_EXPORTS
#define LBDOMCONFIG_API __declspec(dllexport)
#else
#define LBDOMCONFIG_API __declspec(dllimport)
#endif
/*...e*/

/*...sincludes:0:*/
#include <lbErrCodes.h>
#include <lbInterfaces.h>
/*...e*/

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

lbErrCodes LBDOMCONFIG_API __cdecl getlbDOMConfigInstance(lb_I_XMLConfig*& inst);

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif
