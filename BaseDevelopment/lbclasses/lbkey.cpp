/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Rosmarinstr. 3
            
            40235 DÅsseldorf (germany)
*/
/*...e*/

#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.17 $
 * $Name:  $
 * $Id: lbkey.cpp,v 1.17 2003/12/13 10:56:25 lollisoft Exp $
 * $Log: lbkey.cpp,v $
 * Revision 1.17  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.16  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.15  2003/02/17 21:34:40  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.14  2003/01/15 22:42:22  lolli
 * Compiles with MSC
 *
 * Revision 1.13  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
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
#ifdef _MSC_VER
// Fix it
#define DLLEXPORT LB_DLLEXPORT
#endif
IMPLEMENT_FUNCTOR(instanceOfIntegerKey, lbKey)

/*...slbKey:0:*/
/*...sc\39\tors and d\39\tors:0:*/
#ifdef _MSC_VER
lbKey::lbKey(char* file, int line) {
	key = 0; 
	strcpy(keyType, "int");
}
#endif

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
#ifdef _MSC_VER
lbKeyUL::lbKeyUL(char* file, int line) { 
	key = 0; strcpy(keyType, "UL");
}
#endif

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

