/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    lbModule.h is part of DMF.
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
            Borsteler Bogen 4

            22453 Hamburg (germany)
*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.4 $
 * $Name:  $
 * $Id: lbGlobal.h,v 1.4 2002/12/29 16:09:29 lothar Exp $
 *
 * $Log: lbGlobal.h,v $
 * Revision 1.4  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.3  2000/06/24 21:14:16  lolli
 * Many changes
 *
 * Revision 1.2  2000/05/04 23:51:43  lolli
 * Added define for logfile mutex
 *
 * Revision 1.1  2000/04/30 14:28:43  lolli
 * Initial
 *
 **************************************************************/

/*...e*/


#ifndef __LB_GLOBAL__
#define __LB_GLOBAL__

/*...sComponentTypes:0:*/
enum ComponentTypes {
	GUI,		// 
	EVENTHANDLER,	// A GUI component can recieve events
	EVENTRAISER,	// This is an active component
};
/*...e*/
/*...sGUITypes:0:*/
enum GUITypes { 
	LB_MENUBAR, 
	LB_MENU, 
	LB_MENUENTRY, 
	LB_APP_TITLE
};
/*...e*/

#define LB_LOGFILE_MUTEX 1
#define LB_SEND_MUTEX 2
#define LB_RECV_MUTEX 3

#endif

