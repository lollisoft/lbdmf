
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens at lollisoft.de)

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

// This code is inactive since when?
#ifdef IMPLEMENT_PROXY_PLUGIN
#define ApplicationBus_DLL

#include <string.h>
#include <conio.h>
#include <lbConfigHook.h>

// The headers here are from before complete project redesign as of it is now.
#include <appcs.h>
#include <appbus.h>


IMPLEMENT_FUNCTOR(instanceOfPluginServerModule, lbServerModul)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbServerModul)
	ADD_INTERFACE(lb_I_ApplicationServerModul)
END_IMPLEMENT_LB_UNKNOWN()

BEGIN_PLUGINS(lbServerModul)
      
END_PLUGINS()

lbServerModul::lbServerModul() {
	
}

lbServerModul::~lbServerModul() {

}

void LB_STDCALL lbServerModul::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbServerModul::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbServerModul::setData(...) for ApplicationBus not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

char* LB_STDCALL lbServerModul::getServiceName() {
	return "localhost/ApplicationBus";
}

void LB_STDCALL lbServerModul::registerModul(lb_I_ProtocolManager* pMgr) {

}

#endif //IMPLEMENT_PROXY_PLUGIN
