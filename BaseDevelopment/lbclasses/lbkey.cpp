


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.6 $
 * $Name:  $
 * $Id: lbkey.cpp,v 1.6 2001/03/14 20:52:51 lolli Exp $
 * $Log: lbkey.cpp,v $
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

//Define DLL here for implementing the module

#define LB_CONTAINER_DLL

#include <windows.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <lbInterfaces.h>
#include <lbConfigHook.h>

#include <lbKey.h>

#ifdef bla
int lbKeyBase::operator == (const lb_I_KeyBase &_key) const {
    return (equals(_key));
}

int lbKeyBase::operator > (const lb_I_KeyBase &_key) const {
    return (greater(_key));
}
#endif

/*...slbKey:0:*/
lbKey::lbKey() {
    key = 0;
}

lbKey::lbKey(int _key) {
    key = _key;
}

lbKey::lbKey(const lb_I_KeyBase* k) {
    key = ((lbKey) k).key;
}


lbKey::~lbKey(){
}

int lbKey::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKey*) _key)->key;
}

int lbKey::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKey*) _key)->key;
}

lb_I_KeyBase* lbKey::clone() const{
    lbKey *k = new lbKey(key);
    return k;
}

char* lbKey::charrep() {
    char buf[100];

    itoa(key, buf, 10);
    
    return buf;
}
/*...e*/

/*...slbKeyUL:0:*/
lbKeyUL::lbKeyUL() {
    key = 0;
}

lbKeyUL::lbKeyUL(unsigned long _key) {
    key = _key;
}

lbKeyUL::lbKeyUL(const lb_I_KeyBase* k) {
    key = ((lbKeyUL*) k)->key;
}


lbKeyUL::~lbKeyUL(){
}

int lbKeyUL::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKeyUL*) _key)->key;
}

int lbKeyUL::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKeyUL*) _key)->key;
}

lb_I_KeyBase* lbKeyUL::clone() const{
    lbKeyUL *k = new lbKeyUL(key);
    return k;
}

char* lbKeyUL::charrep() {
    char buf[100];

    itoa(key, buf, 10);
    
    return buf;
}
/*...e*/

/*...slbStringKey:0:*/
lbStringKey::lbStringKey(const char* _key) {
    key = strdup(_key);
}

lbStringKey::lbStringKey(const lb_I_KeyBase* k) {
    key = strdup(((lbStringKey*) k)->key);
}


lbStringKey::~lbStringKey(){
}

int lbStringKey::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) == 0);
}

int lbStringKey::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) > 0);
}

lb_I_KeyBase* lbStringKey::clone() const {
    lbStringKey *k = new lbStringKey(key);
    return k;
}

char* lbStringKey::charrep() {
    return key;
}
/*...e*/

