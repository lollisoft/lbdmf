


/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.3 $
 * $Name:  $
 * $Id: lbkey.cpp,v 1.3 2000/06/24 21:32:08 lolli Exp $
 * $Log: lbkey.cpp,v $
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

//Define DLL here for implementing the module

#define LB_CONTAINER_DLL

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <lbInclude.h>

int lbKeyBase::operator == (const lbKeyBase &_key) {
    return (equals(_key));
}

int lbKeyBase::operator > (const lbKeyBase &_key) {
    return (greater(_key));
}

/*...slbKey:0:*/
lbKey::lbKey() {
    key = 0;
}

lbKey::lbKey(int _key) {
    key = _key;
}

lbKey::lbKey(const lbKeyBase & k) {
    key = ((lbKey) k).key;
}


lbKey::~lbKey(){
}

int lbKey::equals(const lbKeyBase &_key) {
    return key == ((lbKey) _key).key;
}

int lbKey::greater(const lbKeyBase &_key) {
    return key > ((lbKey) _key).key;
}

lbKeyBase* lbKey::clone() const{
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

lbKeyUL::lbKeyUL(const lbKeyBase & k) {
    key = ((lbKeyUL) k).key;
}


lbKeyUL::~lbKeyUL(){
}

int lbKeyUL::equals(const lbKeyBase &_key) {
    return key == ((lbKeyUL) _key).key;
}

int lbKeyUL::greater(const lbKeyBase &_key) {
    return key > ((lbKeyUL) _key).key;
}

lbKeyBase* lbKeyUL::clone() const{
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
lbStringKey::lbStringKey(char* _key) {
    key = strdup(_key);
}

lbStringKey::lbStringKey(const lbStringKey & k) {
    key = strdup(((lbStringKey) k).key);
}


lbStringKey::~lbStringKey(){
}

int lbStringKey::equals(const lbKeyBase &_key) {
    return (strcmp(key, ((const lbStringKey &) _key).key) == 0);
}

int lbStringKey::greater(const lbKeyBase &_key) {
    return (strcmp(key, ((const lbStringKey &) _key).key) > 0);
}

lbKeyBase* lbStringKey::clone() const {
    lbStringKey *k = new lbStringKey(key);
    return k;
}

char* lbStringKey::charrep() {
    return key;
}
/*...e*/

