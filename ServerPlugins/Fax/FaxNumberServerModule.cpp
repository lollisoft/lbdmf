
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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/

#define Fax_DLL

#include <string.h>
#include <conio.h>
#include <lbConfigHook.h>

#include <appcs.h>
//#include <appbus.h>

class lbServerModul : public lb_I_ApplicationServerModul {
public:
	lbServerModul();
	virtual ~lbServerModul();
	
	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
	
	char* LB_STDCALL getServiceName();
	void LB_STDCALL registerModul(lb_I_ProtocolManager* pMgr);
	
private:
	UAP(lb_I_Container, protocolHandlers)
	UAP(lb_I_Container, protocolHandlerInstances)
	
};

IMPLEMENT_FUNCTOR(instanceOfPluginServerModule, lbServerModul)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbServerModul)
	ADD_INTERFACE(lb_I_ApplicationServerModul)
END_IMPLEMENT_LB_UNKNOWN()

BEGIN_PLUGINS(lbServerModul)
      
	ADD_PLUGIN(lbPluginFaxNumberServer, ProtocolHandler)
          
END_PLUGINS()

lbServerModul::lbServerModul() {
	ref = STARTREF;
}

lbServerModul::~lbServerModul() {

}

void LB_STDCALL lbServerModul::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbServerModul::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbServerModul::setData(...) for Fax not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

char* LB_STDCALL lbServerModul::getServiceName() {
	return "localhost/Fax";
}

void LB_STDCALL lbServerModul::registerModul(lb_I_ProtocolManager* pMgr) {

}

    