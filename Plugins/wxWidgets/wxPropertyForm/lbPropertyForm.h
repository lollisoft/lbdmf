/*...sLicense:0:*/
/*
 DMF Distributed Multiplatform Framework (the initial goal of this library)
 This file is part of lbDMF.
 Copyright (C) 2015  Lothar Behrens (lothar.behrens@lollisoft.de)
 
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
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1.2.1 $
 * $Name:  $
 * $Id: lbPropertyForm.h,v 1.1.2.1 2015/07/12 10:05:50 lollisoft Exp $
 *
 * $Log: lbPropertyForm.h,v $
 * Revision 1.1.2.1  2015/07/12 10:05:50  lollisoft
 * Added new property dialog and panel implementations. A first step toward workflow enabled dialogs.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_PropertyForm__
#define __LB_PropertyForm__

#include <iostream>

/*...sclass lbDatabasePanel:0:*/
/**
 * This is the sample database dialog for a wxWidgets based GUI.
 */
class lbPropertyPanel :
	public lb_I_Form,
	public wxPanel {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
	 */
	lbPropertyPanel();

	/**
	 * Destructor
	 */
	virtual ~lbPropertyPanel();

	// From lb_I_Form (here unused)
	void LB_STDCALL init();
	void LB_STDCALL init(lb_I_Parameter* parameter);

	lbErrCodes	LB_STDCALL setName(const char* name, const char* appention);
		
	char*		LB_STDCALL getName() { return base_formName; }

	char*		LB_STDCALL getFormName() { return formName; }

	lbErrCodes	LB_STDCALL addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes	LB_STDCALL addLabel(const char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes	LB_STDCALL addTextField(const char* name, int x, int y, int w, int h) { return ERR_NONE; };

	lbErrCodes	LB_STDCALL addOwnerDrawn(const char* name, int x, int y, int w, int h) { return ERR_NONE; };

	void		LB_STDCALL addLabel(const char* text, wxSizer* sizer, bool hideThisColumn);

	void		LB_STDCALL create(int parentId);
	int			LB_STDCALL getId() { return GetId(); }
	void		LB_STDCALL windowIsClosing(lb_I_Window* w);

	void		LB_STDCALL show() { Show (TRUE); };
	void		LB_STDCALL destroy();

	

/*...sfrom EventHandler interface:8:*/
	/**
	 * This function acts in a special way for registering the above navigation handlers
	 *
	 * It uses a string of the this pointer + a name for the respective eventhandler.
	 * This is neccessary for handling more than one database dialog per application.
	 *
	 * This is a good sample, if you need to be able to handle more than one instance of
	 * your registered event handlers.
	 */
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);
		
	lb_I_Unknown* LB_STDCALL getUnknown();
/*...e*/

		
	void OnDispatch(wxCommandEvent& event);

	char* base_formName;
	char* formName;
	char* untranslated_formName;
		
	bool _created;	
	DECLARE_LB_UNKNOWN()
};
/*...e*/

/*...sclass lbDatabaseDialog:0:*/
class lbPropertyDialog :
	public lb_I_Form,
	public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
	 */
	lbPropertyDialog();

	/**
	 * Destructor
	 */
	virtual ~lbPropertyDialog();

		// From lb_I_Form (here unused)
		void LB_STDCALL init();
		void LB_STDCALL init(lb_I_Parameter* parameter);
		
		lbErrCodes	LB_STDCALL setName(const char* name, const char* appention);
		
		char*		LB_STDCALL getName() { return base_formName; }
		
		char*		LB_STDCALL getFormName() { return formName; }
		
		lbErrCodes	LB_STDCALL addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
		lbErrCodes	LB_STDCALL addLabel(const char* text, int x, int y, int w, int h) { return ERR_NONE; };
		lbErrCodes	LB_STDCALL addTextField(const char* name, int x, int y, int w, int h) { return ERR_NONE; };
		
		lbErrCodes	LB_STDCALL addOwnerDrawn(const char* name, int x, int y, int w, int h) { return ERR_NONE; };
		
		void		LB_STDCALL addLabel(const char* text, wxSizer* sizer, bool hideThisColumn);
		
		void		LB_STDCALL create(int parentId);
		int			LB_STDCALL getId() { return GetId(); }
		void		LB_STDCALL windowIsClosing(lb_I_Window* w);
		
		void		LB_STDCALL show() { Show (TRUE); };
		void		LB_STDCALL destroy();
		
		
		
		/*...sfrom EventHandler interface:8:*/
		/**
		 * This function acts in a special way for registering the above navigation handlers
		 *
		 * It uses a string of the this pointer + a name for the respective eventhandler.
		 * This is neccessary for handling more than one database dialog per application.
		 *
		 * This is a good sample, if you need to be able to handle more than one instance of
		 * your registered event handlers.
		 */
		lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);
		
		lb_I_Unknown* LB_STDCALL getUnknown();
		/*...e*/
		
		
		void OnDispatch(wxCommandEvent& event);
		
		char* base_formName;
		char* formName;
		char* untranslated_formName;
		
		lbPropertyPanel* panel;
		bool _created;
		
		DECLARE_LB_UNKNOWN()
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOfPluginModule)

DECLARE_FUNCTOR(instanceOflbPropertyPanel)
DECLARE_FUNCTOR(instanceOflbPluginPropertyPanel)
DECLARE_FUNCTOR(instanceOflbPropertyDialog)
DECLARE_FUNCTOR(instanceOflbPluginPropertyDialog)

#ifdef __cplusplus
}
#endif


#endif // __LB_PropertyForm__


