/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.12 $
 * $Name:  $
 * $Id: lbkey.cpp,v 1.12 2002/10/17 17:33:40 lolli Exp $
 * $Log: lbkey.cpp,v $
 * Revision 1.12  2002/10/17 17:33:40  lolli
 * Use of _CL_LOG macro
 *
 * Revision 1.11  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.10  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.9  2001/10/04 19:28:34  lolli
 * Current version seems to work good (without big memory holes)
 *
 * Revision 1.8  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.7  2001/06/21 06:34:42  lolli
 * Now using interface macros
 *
 * Revision 1.6  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.5  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.4  2000/07/06 06:09:20  lolli
 * Constructor now with const parameter
 *
 * Revision 1.3  2000/06/24 21:32:08  lolli
 * Socket bugfix
 *
 * Revision 1.2  2000/04/27 01:36:24  lolli
 * Commit in order of data GAU
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  1999/12/14 21:09:38  lolli
 * Many changes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/
/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {
#endif

#include <conio.h>

#ifdef __cplusplus
}
#endif


#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <lbInterfaces.h>
#include <lbConfigHook.h>

#include <lbkey.h>

#ifdef __cplusplus
extern "C" {
#endif

IMPLEMENT_FUNCTOR(instanceOfIntegerKey, lbKey)

#ifdef __cplusplus
}        
#endif            

/*...slbKey:0:*/
/*...sc\39\tors and d\39\tors:0:*/
lbKey::lbKey() {
    key = 0;
    strcpy(keyType, "int");
}

lbKey::lbKey(int _key) {
    key = _key;
    strcpy(keyType, "int");
}

lbKey::lbKey(const lb_I_KeyBase* k) {
    key = ((lbKey) k).key;
}

lbKey::~lbKey(){
}
/*...e*/

/*...simplement lb_I_Unknown:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbKey)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL lbKey::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lbKey::setData() not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/

char* LB_STDCALL lbKey::getKeyType() const {
    return "int";
}

int LB_STDCALL lbKey::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKey*) _key)->key;
}

int LB_STDCALL lbKey::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKey*) _key)->key;
}

int LB_STDCALL lbKey::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKey*) _key)->key;
}

char* lbKey::charrep() const {
    char buf[100];

#ifndef UNIX
    itoa(key, buf, 10);
#endif
#ifdef UNIX
    sprintf(buf, "%d", key);
#endif
    
    return buf;
}
/*...e*/
/*...slbKeyUL:0:*/


lbKeyUL::lbKeyUL() {
    key = 0;
    strcpy(keyType, "UL");
}

lbKeyUL::lbKeyUL(unsigned long _key) {
    key = _key;
    strcpy(keyType, "UL");
}

lbKeyUL::lbKeyUL(const lb_I_KeyBase* k) {
    key = ((lbKeyUL*) k)->key;
}


lbKeyUL::~lbKeyUL(){
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbKeyUL)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbKeyUL::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lbKey::setData() not implemented yet" LOG_
	return ERR_NONE;
}


char* LB_STDCALL lbKeyUL::getKeyType() const {
    return "UL";
}

int LB_STDCALL lbKeyUL::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKeyUL*) _key)->key;
}

int LB_STDCALL lbKeyUL::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKeyUL*) _key)->key;
}

int LB_STDCALL lbKeyUL::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKeyUL*) _key)->key;
}

char* lbKeyUL::charrep() const {
    char buf[100];

#ifndef UNIX
    itoa(key, buf, 10);
#endif
#ifdef UNIX
    sprintf(buf, "%d", key);
#endif
    
    return buf;
}
/*...e*/

