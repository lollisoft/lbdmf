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
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif
/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <conio.h>

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <iostream>
#ifndef OSX
#include <malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...e*/

#ifdef WINDOWS
class cleanUp {
public:
        cleanUp() {
        }

        virtual ~cleanUp() {
                unHookAll();
        }

};

cleanUp clean_up;
#endif


int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Test parameter class" LOG_

	// Preload lbClasses DLL with this line !
	UAP_REQUEST(mm, lb_I_String, s)

	UAP_REQUEST(mm, lb_I_Parameter, param)
	UAP_REQUEST(mm, lb_I_String, name)
	UAP_REQUEST(mm, lb_I_String, value)

	*name = "Param1";
	*value = "Value1";
	param->setUAPString(*&name, *&value);
	*name = "Param2";
	*value = "Value2";
	param->setUAPString(*&name, *&value);
	*name = "Param3";
	*value = "Value3";
	param->setUAPString(*&name, *&value);


	UAP_REQUEST(mm, lb_I_String, result)

	*name = "Param2";
	param->getUAPString(*&name, *&result);

	_CL_LOG << "Got back '" << result->charrep() << "'" LOG_


	UAP_REQUEST(mm, lb_I_Container, container)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, uk)
	QI(name, lb_I_KeyBase, key)

	*name = "Parameters";

	container->insert(&uk, &key);



        return 0;
}

