
/*
    DMF Distributed Multiplatform Framework
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
    p-Mail:
            Old
            Lothar Behrens
            Borsteler Bogen 4

            22453 Hamburg (germany)

            New
            Lothar Behrens
            Rosmarinstra·e 3

            40235 DÅsseldorf

*/

/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.12 $
 * $Name:  $
 * $Id: lbcontainer.h,v 1.12 2003/08/16 18:07:00 lollisoft Exp $
 * $Log: lbcontainer.h,v $
 * Revision 1.12  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.11  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.10  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.9  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.8  2001/06/23 07:18:54  lolli
 * Interface repository now works with the basic test
 *
 * Revision 1.7  2001/06/21 06:32:55  lolli
 * Using IMPLEMENT_FUNCTOR(instanceOfContainer, lbContainer)
 *
 * Revision 1.6  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.5  2001/03/04 18:30:25  lolli
 * Compiles now with interface support
 *
 * Revision 1.4  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
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
 * Revision 1.3  1999/12/14 21:07:38  lolli
 * Many changes, also bugfixes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/

#ifndef LB_CONTAINER
#define LB_CONTAINER

#include <lbInterfaces-sub-classes.h>
/**
 * lbContainer represents the interface to all containers used.
 * 
 *
 *
 *
 */

class lbObject; // THE base class
class lbElement; // Container for one lbObject
class lbKey; // Search criteria


/*...sclass lbContainer:0:*/
class lbContainer : 	public lb_I_Container
{

public:
    lbContainer(const lb_I_Container* c);
    lb_I_Container* operator= (const lb_I_Container* c);

public:

    lbContainer();
    virtual ~lbContainer();

    DECLARE_LB_UNKNOWN()

// This may be a string container

    DECLARE_LB_I_CONTAINER_IMPL()

};
/*...e*/

#ifndef UNIX
extern lbCritSect critsect;
#endif
/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/
DECLARE_FUNCTOR(instanceOfContainer)
/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif //LB_CONTAINER
