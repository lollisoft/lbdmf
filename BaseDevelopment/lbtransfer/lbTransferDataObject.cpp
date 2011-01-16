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
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <lbtransfer-module.h>

#include <conio.h>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif
#include <lbinclude.h>
#include <signal.h>

#include <lbInterfaces.h>

#include <socket.h>

#define LB_TRANSFER_DLL
#include <lbtransfer-module.h>
#include <transfer.h>

#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOflbTransferDataObject, lbTransferDataObject)
	
#ifdef __cplusplus
}
#endif            

BEGIN_IMPLEMENT_LB_UNKNOWN(lbTransferDataObject)
	ADD_INTERFACE(lb_I_Transfer_DataObject)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbTransferDataObject::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		UAP(lb_I_Transfer_DataObject, tdObject)
		QI(uk, lb_I_Transfer_DataObject, tdObject)
		if (tdObject != NULL) {
			setTransferData(tdObject->getTransferData());
			tdObject->setTransferData(NULL);
		} else {
			_LOG << "lbErrCodes LB_STDCALL lbTransferDataObject::setData() Error: Failed to copy object. (" << uk->getClassName() << ")" LOG_
		}
		
        return ERR_NOT_IMPLEMENTED;
}

/*...slbTransferDataObject:0:*/
lbTransferDataObject::lbTransferDataObject() {
	ref = STARTREF;
	setType();
}

lbTransferDataObject::~lbTransferDataObject() {
	if (mydata != NULL) delete mydata;
}

void lbTransferDataObject::setType() {
        OTyp = LB_DATA_TRANSFER_OBJECT;
}
#ifdef USE_CLONE
lbObject* lbTransferDataObject::clone() const {
        lbLock lock(*transferSection, "transferSection");
        
        char msg[100] = "";
        lbTransferDataObject* o = new lbTransferDataObject();
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE 
        LOG("lbTransferDataObject::clone() called");
#endif
/*...e*/
        pLB_TRANSFER_DATA pData = (pLB_TRANSFER_DATA) malloc(getData()->packet_size + sizeof(lbTransferData));
        memcpy(pData, getData(), getData()->packet_size + sizeof(lbTransferData));
        
        o->setData(pData);
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
        sprintf(msg, "Cloned lbTransferDataObject (pData) to address %p", (void*) pData);
        LOG(msg);
#endif  
/*...e*/
        return o;
}
#endif

void lbTransferDataObject::setTransferData(pLB_TRANSFER_DATA pData) {
        mydata = pData;
        //if (mydata == NULL) _LOG << "lbTransferDataObject::setData(): Error, data pointer is null" LOG_
}

pLB_TRANSFER_DATA lbTransferDataObject::getTransferData() const {
        if (mydata == NULL) 
			_LOG << "lbTransferDataObject::getData(): Error, data pointer is null" LOG_
        return mydata;
}
/*...e*/
