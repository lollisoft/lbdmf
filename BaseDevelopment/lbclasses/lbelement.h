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
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.17 $
 * $Name:  $
 * $Id: lbelement.h,v 1.17 2011/10/15 13:14:05 lollisoft Exp $
 * $Log: lbelement.h,v $
 * Revision 1.17  2011/10/15 13:14:05  lollisoft
 * Decided to make a hash cut and removed stuff that everywhere was the cause for crashes on Mac.
 * Currently the code crashes on windows, but lets see how it is working on Mac.
 *
 * Revision 1.16  2011/09/25 09:30:14  lollisoft
 * Many bugfixes like missing variable initialization. Used CppCheck for this to get rid of the random crashes.
 * Only lbHook, lbModule, lbclasses and the Basetypes regression test (including headers and interfaces) are
 * fixed. Other modules will follow.
 *
 * Revision 1.15  2011/02/27 10:30:36  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.14  2007/08/06 19:10:29  lollisoft
 * Improved installation process on Windows.
 *
 * Revision 1.13  2005/03/31 09:02:42  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.12  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.11  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.10  2003/01/15 22:42:22  lolli
 * Compiles with MSC
 *
 * Revision 1.9  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.8  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.7  2001/08/18 07:34:48  lolli
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.6  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.5  2001/06/21 06:33:40  lolli
 * Removed some members
 *
 * Revision 1.4  2001/04/13 07:39:29  lolli
 * Commit for backup
 *
 * Revision 1.3  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.2  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  1999/12/14 21:09:02  lolli
 * Bugfixes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/

#ifndef LB_ELEMENT
#define LB_ELEMENT

#include <stdlib.h>
#include <lbInterfaces-sub-classes.h>

class lbKeyBase;
class lbObject;

class lbElement : public lb_I_Element {
private:

public:
    lbElement() { 
    	next = NULL; 
    	key = NULL; 
    	manager = NULL;
    }
    virtual ~lbElement();
	
    lbElement(const lb_I_Element &e) { 
		next = e.getNext(); 
		manager = NULL;
    	key = NULL; 
    }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)
#ifndef UNIX
#ifndef _MSC_VER
//    lb_I_Unknown* getObject() const;
#endif
#endif
    int operator == (const lb_I_Element &a) const;

    int operator == (const lb_I_KeyBase &key) const;

};
#endif //LB_ELEMENT
