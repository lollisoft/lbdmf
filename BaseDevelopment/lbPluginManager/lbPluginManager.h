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

#ifndef __LB_PLUGINMANAGER__
#define __LB_PLUGINMANAGER__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.7.2.3 $
 * $Name:  $
 * $Id: lbPluginManager.h,v 1.7.2.3 2025/04/12 10:54:06 lothar Exp $
 *
 * $Log: lbPluginManager.h,v $
 * Revision 1.7.2.3  2025/04/12 10:54:06  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.7.2.2  2025/04/12 10:09:26  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.7.2.1  2025/04/05 16:16:30  lothar
 * This file seems to clash with HEAD bransh when migrating to git.
 * So update it in the bransh to probably fix this. Why does the
 * migration fails here?
 *
 * Revision 1.7  2011/02/27 10:30:36  lollisoft
 * Changed all copyright entries addresses to match my current postal address.
 *
 * Revision 1.6  2006/07/17 17:37:45  lollisoft
 * Changes dueto bugfix in plugin manager. Repeadable iterator problem.
 * Not correctly finished the iteration, thus plugins in the same DLL wouldn't
 * be found any more after first query.
 *
 * Code works well with improved trmem library, but there is still a crash in
 * database classes (pgODBC library).
 *
 * Revision 1.5  2005/05/10 20:20:36  lollisoft
 * Include files changed to be more actially language compilant
 *
 * Revision 1.4  2005/03/31 09:00:55  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.3  2005/03/14 18:59:02  lollisoft
 * Various changes and additions to make plugins also work with database forms
 *
 * Revision 1.2  2004/06/16 22:12:32  lollisoft
 * More code for plugin management
 *
 * Revision 1.1  2004/06/06 12:31:21  lollisoft
 * Initial
 *
 **************************************************************/

/*...e*/

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_SINGLETON_FUNCTOR(instanceOfPluginManager)
DECLARE_FUNCTOR(instanceOfPlugin)

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_PLUGINMANAGER__

