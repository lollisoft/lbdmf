


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.12 $
 * $Name:  $
 * $Id: lbcontainer.cpp,v 1.12 2001/06/21 06:32:40 lolli Exp $
 * $Log: lbcontainer.cpp,v $
 * Revision 1.12  2001/06/21 06:32:40  lolli
 * Using IMPLEMENT_FUNCTOR(instanceOfContainer, lbContainer)
 *
 * Revision 1.11  2001/05/01 15:51:52  lolli
 * First instance could be loaded over the new module management
 *
 * Revision 1.10  2001/04/13 07:39:29  lolli
 * Commit for backup
 *
 * Revision 1.9  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.8  2001/03/04 18:30:24  lolli
 * Compiles now with interface support
 *
 * Revision 1.7  2001/02/06 20:38:18  lolli
 * Commit for backup the data
 *
 * Revision 1.6  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.5  2000/06/28 20:33:08  lolli
 * Deactivated some cout messages
 *
 * Revision 1.4  2000/06/24 21:32:07  lolli
 * Socket bugfix
 *
 * Revision 1.3  2000/04/27 01:36:24  lolli
 * Commit in order of data GAU
 *
 * Revision 1.2  2000/03/06 22:55:50  lolli
 * Fold in revision log
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  1999/12/14 21:07:03  lolli
 * Many changes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/
//Define DLL here for implementing the module

#define LB_CONTAINER_DLL

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream.h>

//#include <lbInclude.h>
#include <lbInterfaces.h>

#include <lbThread.h>
#include <lbConfigHook.h>
#include <lbElement.h>
#include <lbContainer.h>

lbCritSect containerSection;



IMPLEMENT_FUNCTOR(instanceOfContainer, lbContainer)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbContainer)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbContainer::lbContainer() {
    iteration = 0;
    ref = 0;
    iterator = NULL;
    count = 0;
    container_data = NULL;
}

lbContainer::~lbContainer() {
}

lbErrCodes LB_STDCALL lbContainer::setData(lb_I_Unknown* uk) {
	CL_LOG("lbContainer::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbContainer)






BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)

int LB_STDCALL lbElement::equals(const lb_I_Element* a) const {
	return 0;
}

int LB_STDCALL lbElement::equals(const lb_I_KeyBase* key) const {
	return 0;
}

lbErrCodes LB_STDCALL lbElement::setData(lb_I_Unknown* uk) {
	CL_LOG("lbElement::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}
