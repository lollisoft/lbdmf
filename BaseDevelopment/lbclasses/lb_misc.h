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

/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.10 $
 * $Name:  $
 * $Id: lb_misc.h,v 1.10 2005/03/31 09:02:42 lollisoft Exp $
 * $Log: lb_misc.h,v $
 * Revision 1.10  2005/03/31 09:02:42  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.9  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.8  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.7  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.6  2001/07/11 16:04:34  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.5  2001/05/04 17:14:43  lolli
 * Use of MACRO DECLARE_FUNCTOR works
 *
 * Revision 1.4  2001/05/01 15:51:52  lolli
 * First instance could be loaded over the new module management
 *
 * Revision 1.3  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.2  2001/02/06 20:38:18  lolli
 * Commit for backup the data
 *
 * Revision 1.1  2000/07/06 06:19:40  lolli
 * Readded (possibly to new location)
 *
 * Revision 1.6  2000/03/16 08:58:07  lolli
 * Version crashes
 *
 * Revision 1.5  2000/01/18 21:13:17  lolli
 * Current version
 *
 * Revision 1.4  1999/10/12 06:34:47  Lothar_Behrens
 * Added logging / and a new class for debug via log
 *
 **************************************************************/
/*...e*/

#ifndef _MISC_
#define _MISC_

/*...sincludes:0:*/
#include <time.h>
#include <string.h>
#include <iostream.h>
#include <stdio.h>

#include <lbInterfaces.h>
/*...e*/


/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/
void lb_sleep(int ms);

DECLARE_FUNCTOR(instanceOfLogger)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#define TRUE 1
#define FALSE 0

class lbMutex;



extern lbCritSect sect;

#endif
