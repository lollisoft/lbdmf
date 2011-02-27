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
 * $Revision: 1.13 $
 * $Name:  $
 * $Id: lbDOMConfig.h,v 1.13 2011/02/27 10:30:36 lollisoft Exp $
 *
 * $Log: lbDOMConfig.h,v $
 * Revision 1.13  2011/02/27 10:30:36  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.12  2005/03/31 09:01:27  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.11  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.10  2003/08/16 18:13:37  lollisoft
 * Added my new address due to move
 *
 * Revision 1.9  2003/07/31 20:10:54  lollisoft
 * Changed functor name
 *
 * Revision 1.8  2003/07/17 18:51:42  lollisoft
 * Begin develop a hopefully faster and less memory consuming
 * XML wrapper.
 *
 * Revision 1.7  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.6  2002/06/01 10:18:41  lothar
 * pragma warning don't affect here
 *
 * Revision 1.5  2002/05/30 17:53:02  lothar
 * Current development seems to run
 *
 * Revision 1.4  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.3  2001/12/08 11:51:12  lothar
 * Modified line 896 due to compilation errors
 *
 * Revision 1.2  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.1  2000/10/20 04:24:52  lothar
 * Initial
 *
 **************************************************************/

/*...e*/

#ifndef __LB_DOM_CONFIG__
#define __LB_DOM_CONFIG__

/*...sincludes:0:*/
#include <lbErrcodes.h>
#include <lbInterfaces.h>
/*...e*/


/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
#ifdef WINDOWS
extern "C" {
#endif
#endif
/*...e*/

DECLARE_FUNCTOR(getlbDOMConfigInstance)
DECLARE_FUNCTOR(instanceOfInterfaceRepository)
/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
#ifdef WINDOWS
}
#endif
#endif
/*...e*/

#endif
