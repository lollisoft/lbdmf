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
			Ginsterweg 4
 
			65760 Eschborn (germany)
 */
/*...e*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.3 $
 * $Name:  $
 * $Id: Application.h,v 1.3 2011/02/27 10:34:00 lollisoft Exp $
 *
 * $Log: Application.h,v $
 * Revision 1.3  2011/02/27 10:34:00  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.2  2005/03/31 09:19:08  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.1  2004/03/15 20:47:32  lollisoft
 * Initial demo application module
 *
 * Revision 1.1  2004/01/29 21:56:37  lothar
 * Initial
 *
 * Revision 1.15  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.14  2003/08/22 17:38:35  lollisoft
 * Implemented a handler for a button press event and code to demonstrate
 *
 * Revision 1.13  2003/08/16 18:03:53  lollisoft
 * Added my new address due to move
 *
 * Revision 1.12  2003/03/14 16:00:38  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.11  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.10  2002/10/08 16:33:38  lothar
 * Missing LB_STDCALL
 *
 * Revision 1.9  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
 * Revision 1.8  2002/09/12 18:32:59  lothar
 * Added some UI wrapper and sub module creation
 *
 * Revision 1.7  2002/09/07 09:57:10  lothar
 * First working callback function
 *
 * Revision 1.6  2002/09/04 17:52:12  lothar
 * Problems with stack cleanup
 *
 * Revision 1.5  2002/08/21 18:00:28  lothar
 * Added UAP variables
 *
 * Revision 1.4  2002/08/06 05:41:39  lothar
 * More special Dispatcher and EventManager interface.
 * Empty bodies compiling
 *
 * Revision 1.3  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.2  2002/02/25 06:13:07  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 **************************************************************/
/*...e*/

#ifndef _LB_APP_
#define _LB_APP_

#include <stdio.h>
#include <lbInterfaces.h>



/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_FUNCTOR(instanceOfApplication)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif //LB_OBJECT
