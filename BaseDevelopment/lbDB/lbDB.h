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

#ifndef __LB_DATABASE__
#define __LB_DATABASE__
/*...sRevision history:0:*/
/*...e*/

#include <iostream.h>

/**
 * \brief lbFakeDelete - Does not directly delete rows, only mark it as deleted.
 *
 * This class is intented to avoid crashes due to ODBC drivers, that may crash
 * my application when deleting rows over the cursor library.
 */
class lbFakeDelete {
public:

	lbFakeDelete() {}
	virtual ~lbFakeDelete() {}

	
}


/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

//lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst);
DECLARE_FUNCTOR(instanceOfDatabase)
DECLARE_FUNCTOR(instanceOfConnection)
DECLARE_FUNCTOR(instanceOfDBInterfaceRepository)
DECLARE_FUNCTOR(instanceOfDatabaseForm)
/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_DATABASE__
