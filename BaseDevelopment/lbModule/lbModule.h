/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Odenwaldstr. 14

            63150 Heusenstamm (germany)
*/
/*...e*/

#ifndef __LB_MODULE__
#define __LB_MODULE__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.18.2.3 $
 * $Name:  $
 * $Id: lbModule.h,v 1.18.2.3 2025/04/12 10:54:06 lothar Exp $
 *
 * $Log: lbModule.h,v $
 * Revision 1.18.2.3  2025/04/12 10:54:06  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.18.2.2  2025/04/12 10:09:26  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.18.2.1  2025/04/05 16:16:30  lothar
 * This file seems to clash with HEAD bransh when migrating to git.
 * So update it in the bransh to probably fix this. Why does the
 * migration fails here?
 *
 * Revision 1.18  2011/02/27 10:30:36  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.17  2005/05/10 20:20:36  lollisoft
 * Include files changed to be more actially language compilant
 *
 * Revision 1.16  2005/03/31 09:00:17  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.15  2004/03/20 11:36:20  lollisoft
 * Added a hardcoded repository as an alternative to XML
 *
 * Revision 1.14  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.13  2003/08/16 18:04:20  lollisoft
 * Added my new address due to move
 *
 * Revision 1.12  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.11  2002/04/15 18:24:31  lothar
 * Huge changes - works good
 *
 * Revision 1.10  2001/12/15 17:57:01  lothar
 * Minor changes
 *
 * Revision 1.9  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.8  2001/07/18 05:49:13  lothar
 * minor changes
 *
 * Revision 1.7  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.6  2001/06/23 07:18:53  lothar
 * Interface repository now works with the basic test
 *
 **************************************************************/
/*...e*/

#include <iostream>

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst);
DECLARE_SINGLETON_FUNCTOR(getlb_ModuleInstance)

DECLARE_FUNCTOR(instanceOfHCInterfaceRepository)

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_MODULE__
