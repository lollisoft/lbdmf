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

#ifndef __LB_CryptoStream__
#define __LB_CryptoStream__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2.2.3 $
 * $Name:  $
 * $Id: lbCryptoStream.h,v 1.2.2.3 2025/04/12 10:54:06 lothar Exp $
 *
 * $Log: lbCryptoStream.h,v $
 * Revision 1.2.2.3  2025/04/12 10:54:06  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.2.2.2  2025/04/12 10:09:26  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.2.2.1  2025/04/05 16:16:31  lothar
 * This file seems to clash with HEAD bransh when migrating to git.
 * So update it in the bransh to probably fix this. Why does the
 * migration fails here?
 *
 * Revision 1.2  2011/02/27 10:34:00  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.1  2010/01/12 19:47:52  lollisoft
 * Mostly completed plugin based interceptor functionality for events.
 *
 *
 **************************************************************/

/*...e*/

#include <iostream>

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_SINGLETON_FUNCTOR(instanceOfPluginModule)

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_CryptoStream__
