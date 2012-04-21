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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#ifdef __WATCOMC__
#include <direct.h>
#endif

#ifdef __MINGW32__
#include <direct.h>
#endif

#include <lbUserFeedback.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbUserFeedback)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbUserFeedback::lbUserFeedback() {
	
}

lbUserFeedback::~lbUserFeedback() {
	
}

lb_I_Unknown* lbUserFeedback::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbUserFeedback::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbUserFeedback::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbUserFeedback::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("SendPositiveFeedback", temp);
	disp->addEventHandlerFn(this, (lbEvHandler) &lbUserFeedback::SendPositiveFeedback, "SendPositiveFeedback");
	eman->registerEvent("SendNegativeFeedback", temp);
	disp->addEventHandlerFn(this, (lbEvHandler) &lbUserFeedback::SendNegativeFeedback, "SendNegativeFeedback");
	eman->registerEvent("SendPuzzledFeedback", temp);
	disp->addEventHandlerFn(this, (lbEvHandler) &lbUserFeedback::SendPuzzledFeedback, "SendPuzzledFeedback");
	eman->registerEvent("SendCoolIdeaFeedback", temp);
	disp->addEventHandlerFn(this, (lbEvHandler) &lbUserFeedback::SendCoolIdeaFeedback, "SendCoolIdeaFeedback");
	
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	char* help = strdup(_trans("&Help"));
	char* negativeentry = strdup(_trans("I am sad about this product"));
	char* positiveentry = strdup(_trans("I am happy with this product"));
	char* coolideaentry = strdup(_trans("I have a cool idea"));
	char* puzzledentry = strdup(_trans("I am puzzled, can you help me"));

	meta->addMenuEntry(help, negativeentry, "SendNegativeFeedback", "");
	meta->addMenuEntry(help, positiveentry, "SendPositiveFeedback", "");
	meta->addMenuEntry(help, coolideaentry, "SendCoolIdeaFeedback", "");
	meta->addMenuEntry(help, puzzledentry, "SendPuzzledFeedback", "");

	meta->addToolBar("User Feedback");
	meta->addToolBarButton("User Feedback", "I am happy with this product", "SendPositiveFeedback", "nicubunu_Smiley_Happy.png");
	meta->addToolBarButton("User Feedback", "I am sad about this product", "SendNegativeFeedback", "nicubunu_Smiley_Sad.png");
	meta->addToolBarButton("User Feedback", "I have a cool idea", "SendCoolIdeaFeedback", "nicubunu_Smiley_Cool.png");
	meta->addToolBarButton("User Feedback", "I am puzzled, can you help me", "SendPuzzledFeedback", "nicubunu_Smiley_Puzzled.png");
	
	free(help);
	free(negativeentry);
	free(positiveentry);
	free(coolideaentry);
	free(puzzledentry);
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbUserFeedback::SendPositiveFeedback(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	lb_I_GUI* gui;
	meta->getGUI(&gui);
	gui->openWebPage("I am happy with this product", "http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=14");
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbUserFeedback::SendNegativeFeedback(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	lb_I_GUI* gui;
	meta->getGUI(&gui);
	gui->openWebPage("I am sad about this product", "http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=15");
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbUserFeedback::SendCoolIdeaFeedback(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	lb_I_GUI* gui;
	meta->getGUI(&gui);
	gui->openWebPage("I have a cool idea", "http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=17");
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbUserFeedback::SendPuzzledFeedback(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	lb_I_GUI* gui;
	meta->getGUI(&gui);
	gui->openWebPage("I am puzzled, can you help me", "http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=16");
	return ERR_NONE;
}

class lbPluginUserFeedback : public lb_I_PluginImpl {
public:
	lbPluginUserFeedback();
	
	virtual ~lbPluginUserFeedback();
	
	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();
	
	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
	/*...e*/
	
	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUserFeedback)
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUserFeedback)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUserFeedback, lbPluginUserFeedback)

/*...slbErrCodes LB_STDCALL lbPluginUserFeedback\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginUserFeedback::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginUserFeedback::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginUserFeedback::lbPluginUserFeedback() {
	_CL_VERBOSE << "lbPluginUserFeedback::lbPluginUserFeedback() called.\n" LOG_
	
}

lbPluginUserFeedback::~lbPluginUserFeedback() {
	_CL_VERBOSE << "lbPluginUserFeedback::~lbPluginUserFeedback() called.\n" LOG_
}

bool LB_STDCALL lbPluginUserFeedback::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginUserFeedback::autorun() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)

	if (ukUserFeedback == NULL) {
		lbUserFeedback* feedback = new lbUserFeedback();
		QI(feedback, lb_I_Unknown, ukUserFeedback)
		feedback->registerEventHandler(*&disp);
	}
	
	return err;
}

void LB_STDCALL lbPluginUserFeedback::initialize() {
}

bool LB_STDCALL lbPluginUserFeedback::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUserFeedback\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginUserFeedback::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukUserFeedback == NULL) {
		lbUserFeedback* transformer = new lbUserFeedback();
		
		QI(transformer, lb_I_Unknown, ukUserFeedback)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserFeedback.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUserFeedback\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginUserFeedback::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukUserFeedback == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbUserFeedback* transformer = new lbUserFeedback();
		
		
		QI(transformer, lb_I_Unknown, ukUserFeedback)
	}
	
	lb_I_Unknown* r = ukUserFeedback.getPtr();
	ukUserFeedback.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginUserFeedback::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukUserFeedback != NULL) {
		ukUserFeedback--;
		ukUserFeedback.resetPtr();
	}
}
/*...e*/
/*...e*/



