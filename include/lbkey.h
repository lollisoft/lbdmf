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
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lbkey.h,v 1.1 2009/11/08 11:49:32 lollisoft Exp $
 * $Log: lbkey.h,v $
 * Revision 1.1  2009/11/08 11:49:32  lollisoft
 * Implemented 'unit test' like capabilities. The TestPlugin in the Plugins directory demonstrates the usage. Yet missing is a real test listener and stuff to display results. But it shows a working unit test mechanism using plugins.
 *
 * Corrected mkmk to find also include files in <> brackets.
 *
 * Corrected make system to work correctly with the new mkmk version. There may be a performance problem when compiling tvision code, thus that target is deactivated.
 *
 * Fixed some warnings.
 *
 * Revision 1.22  2005/03/31 09:02:42  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.21  2005/02/12 13:57:34  lollisoft
 * Changed lbKey to lbKey_ to enable built on Mac
 *
 * Revision 1.19  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.18  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.17  2003/01/19 18:07:46  lothar
 * MSC variant runs now under Linux
 *
 * Revision 1.16  2003/01/15 22:42:22  lolli
 * Compiles with MSC
 *
 * Revision 1.15  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.14  2002/11/29 19:50:27  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.13  2002/06/20 21:02:56  lolli
 * Added missing code for _MSC_VER
 *
 * Revision 1.12  2002/05/30 17:53:03  lolli
 * Current development seems to run
 *
 * Revision 1.11  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.10  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.9  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.8  2001/06/21 06:34:42  lolli
 * Now using interface macros
 *
 * Revision 1.7  2001/03/30 20:08:07  lolli
 * Commit due to possible head crash on anakin (Linux)
 *
 * Revision 1.6  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.5  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.4  2000/07/06 06:09:32  lolli
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
 * Revision 1.4  2000/01/23 14:32:55  lolli
 * Corrected error in revision conflict
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/

#ifndef LB_KEY
#define LB_KEY

/*...sclass lbKeyUL \58\ public lb_I_KeyBase:0:*/
class lbKeyUL : public lb_I_KeyBase {
public:
#ifdef _MSC_VER
	lbKeyUL(char* file, int line);// { key = 0; strcpy(keyType, "UL"); }
#endif
    lbKeyUL();
    lbKeyUL(unsigned long _key);
    lbKeyUL(const lb_I_KeyBase* k);
    virtual ~lbKeyUL();

    DECLARE_LB_UNKNOWN()
    
    DECLARE_LB_KEYBASE()

private:

    char keyType[10];
    unsigned long key;
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif            

DECLARE_FUNCTOR(instanceOfIntegerKey)

#ifdef __cplusplus
}
#endif            

#endif //LB_ELEMENT
