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

#ifndef __LB_DatabaseForm__
#define __LB_DatabaseForm__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.7 $
 * $Name:  $
 * $Id: lbDatabaseForm.h,v 1.7 2005/05/15 23:49:10 lollisoft Exp $
 *
 * $Log: lbDatabaseForm.h,v $
 * Revision 1.7  2005/05/15 23:49:10  lollisoft
 * Moved some classes to their own files.
 *
 * Revision 1.6  2005/05/10 20:59:18  lollisoft
 * Including made more actually language conform
 *
 * Revision 1.5  2005/04/23 10:44:31  lollisoft
 * OwnerDrawControl basically implemented and usable.
 * Some bugfixes in selecting from correct database connection.
 *
 * Revision 1.4  2005/03/31 09:07:40  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.3  2005/03/14 18:59:03  lollisoft
 * Various changes and additions to make plugins also work with database forms
 *
 * Revision 1.2  2004/06/16 22:17:27  lollisoft
 * First plugin beginnings
 *
 * Revision 1.1  2004/06/07 20:04:45  lollisoft
 * Initial
 *
 * Revision 1.1  2004/06/06 12:31:21  lollisoft
 * Initial
 *
 **************************************************************/

/*...e*/

#include <iostream>

/*...sclass lbConfigure_FK_PK_MappingDialog definition:0:*/
class lbConfigure_FK_PK_MappingDialog :
	public lb_I_EventHandler,
	public lb_I_Unknown,
	public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
	 */
	lbConfigure_FK_PK_MappingDialog();

	/**
	 * Destructor
	 */
	virtual ~lbConfigure_FK_PK_MappingDialog();

	int prepareDialogHandler();

	void LB_STDCALL init(lb_I_Database* _queryDB, lb_I_Query* query);

	void LB_STDCALL show() { ShowModal (); };
	void LB_STDCALL destroy() { Destroy(); };
	
	/**
	 * Column has been selected.
	 *
	 * Store the retrieved data in the tables and destroy the form.
	 */

	lbErrCodes LB_STDCALL selectedColumn(lb_I_Unknown* uk);

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

	void OnDispatch(wxCommandEvent& event);

	DECLARE_LB_UNKNOWN()


	void OnFKComboBoxSelected( wxCommandEvent &event );
	void OnPKComboBoxSelected( wxCommandEvent &event );
	    
/*...svariables:8:*/
	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)
	
	/**
	 * \brief Maps positions to id's for each displayed combo box.
	 *
	 * Store a container for each combo box with key(pos) and data(id). 
	 */
	UAP(lb_I_Container, ComboboxMapperList, __FILE__, __LINE__)
	UAP(lb_I_Query, sourceQuery, __FILE__, __LINE__)
	UAP(lb_I_Database, queryDB, __FILE__, __LINE__)


	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];
	
	wxWindow* firstButton;

	wxComboBox* cBoxFKNames;
	wxComboBox* cBoxPKNames;

	wxStaticText *label;
	wxStaticText *labelF;
	
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
	int pass;
/*...e*/
};
/*...e*/

/*...sclass FormularActions:0:*/
/*...sclass definition of FormularActions:0:*/
/** \brief Management of formular actions.
 *
 * This class is used to concentrate the code for formular actions.
 */
class FormularActions {

public:

	FormularActions() {}
	virtual ~FormularActions() {}
	
	/** \brief ID of action target.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when 
	 */
	char* getActionTargetID(char* what);
	
	/** \brief Source field of the action.
	 *
	 *
	 */
	char* getActionSourceDataField(char* what);

};
/*...e*/

/*...sclass FormularFieldInformation:0:*/
/*...sclass declaration FormularFieldInformation:0:*/
/** \brief Management of formular fields.
 *
 * This class is used to concentrate the code for formular field informations.
 */

class FormularFieldInformation {
public:

	FormularFieldInformation(char const * formularname, lb_I_Query* query);
	virtual ~FormularFieldInformation() {}
	
	/** \brief Get readonly status.
	 *
	 * Returns true, if the specifed field is readonly.
	 */
	bool isReadonly(char* field);

	/** \brief Check, if there must be used a special control.
	 *
	 * Returns true, if the configuration says, that there must be used a special
	 * control. This is the case if I like to use an ownerdrawn control.
	 */
	bool isSpecialColumn(char* field);

	char* getControlType(char* name);
	
protected:

	lb_I_Query* _query;

	UAP(lb_I_Container, ROFields, __FILE__, __LINE__)	
	UAP(lb_I_Container, SCFields, __FILE__, __LINE__)
};
/*...e*/


/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_SINGLETON_FUNCTOR(instanceOfPluginModule)

DECLARE_FUNCTOR(instanceOflbDatabaseDialog)
DECLARE_FUNCTOR(instanceOflbPluginDatabaseDialog)

// Based on the 'group box' this control can be used to draw lines and so on.
DECLARE_FUNCTOR(instanceOflbOwnerDrawControl)

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_DatabaseForm__

