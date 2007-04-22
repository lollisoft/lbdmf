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
            
            40235 Duesseldorf (germany)
*/
/*...e*/
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.29 $
 * $Name:  $
 * $Id: lbcontainer.cpp,v 1.29 2007/04/22 13:34:11 lollisoft Exp $
 * $Log: lbcontainer.cpp,v $
 * Revision 1.29  2007/04/22 13:34:11  lollisoft
 * Minor change in include location.
 *
 * Revision 1.28  2005/06/27 10:32:09  lollisoft
 * Mostly changes to conio.h conflicts while XCode build
 *
 * Revision 1.27  2005/05/10 20:20:38  lollisoft
 * Include files changed to be more actially language compilant
 *
 * Revision 1.26  2005/05/04 22:09:39  lollisoft
 * Many memory leaks fixed. Changed _CL_LOG to _CL_VERBOSE.
 *
 * Revision 1.25  2005/03/31 09:02:42  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.24  2005/01/23 13:43:05  lollisoft
 * std:: is only under linux working
 *
 * Revision 1.23  2004/06/09 07:03:23  lollisoft
 * Still problems with undeleted container data ??
 *
 * Revision 1.22  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.21  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.20  2003/02/17 21:34:39  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.19  2003/01/15 22:42:22  lolli
 * Compiles with MSC
 *
 * Revision 1.18  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.17  2002/10/17 17:33:27  lolli
 * Use of _CL_VERBOSE macro
 *
 * Revision 1.16  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.15  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.14  2001/10/04 19:28:34  lolli
 * Current version seems to work good (without big memory holes)
 *
 * Revision 1.13  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.12  2001/06/21 06:32:40  lolli
 * Using IMPLEMENT_FUNCTOR(instanceOfContainer, lbContainer)
 *
 * Revision 1.11  2001/05/01 15:51:52  lolli
 * First instance could be loaded over the new module management
 *
 * Revision 1.10  2001/04/13 07:39:29  lolli
 * Commit for backup
 *
 * Revision 1.9  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.8  2001/03/04 18:30:24  lolli
 * Compiles now with interface support
 *
 * Revision 1.7  2001/02/06 20:38:18  lolli
 * Commit for backup the data
 *
 * Revision 1.6  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.5  2000/06/28 20:33:08  lolli
 * Deactivated some COUT messages
 *
 * Revision 1.4  2000/06/24 21:32:07  lolli
 * Socket bugfix
 *
 * Revision 1.3  2000/04/27 01:36:24  lolli
 * Commit in order of data GAU
 *
 * Revision 1.2  2000/03/06 22:55:50  lolli
 * Fold in revision log
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  1999/12/14 21:07:03  lolli
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

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __cplusplus
}
#endif

#include <iostream>

//#include <lbInclude.h>
#include <lbConfigHook.h>
#ifndef UNIX
#include <lbthread.h>
#endif
#include <lbelement.h>
#include <lbcontainer.h>
#ifndef UNIX
lbCritSect containerSection;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _MSC_VER
// Fix it
#define DLLEXPORT LB_DLLEXPORT
#endif
IMPLEMENT_FUNCTOR(instanceOfContainer, lbContainer)

#ifdef __cplusplus
}
#endif


BEGIN_IMPLEMENT_LB_UNKNOWN(lbContainer)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbContainer::lbContainer() {
    iteration = 0;
    ref = STARTREF;
    iterator = NULL;
    count = 0;
    container_data = NULL;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    _LOG << "Set manager to NULL must be done automatically!" LOG_
#endif
/*...e*/
    manager = NULL;
}

lbContainer::~lbContainer() {
	printf("lbContainer::~lbContainer() called\n");
	deleteAll();
}

lbErrCodes LB_STDCALL lbContainer::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbContainer::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbContainer)






BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)

lbErrCodes LB_STDCALL lbElement::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbElement::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}
