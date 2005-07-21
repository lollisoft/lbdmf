/*...sLicense:0:*/
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
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.14 $
 * $Name:  $
 * $Id: lbDatabaseForm.h,v 1.14 2005/07/21 17:03:19 lollisoft Exp $
 *
 * $Log: lbDatabaseForm.h,v $
 * Revision 1.14  2005/07/21 17:03:19  lollisoft
 * Moved some code for master detail form management.
 *
 * Revision 1.13  2005/07/07 05:35:46  lollisoft
 * No MI usage (with one baseclass).
 *
 * Revision 1.12  2005/06/27 10:32:10  lollisoft
 * Mostly changes to conio.h conflicts while XCode build
 *
 * Revision 1.11  2005/06/25 12:44:50  lollisoft
 * Changed wxComboBox to wxChoice.
 *
 * Revision 1.10  2005/06/20 11:24:02  lollisoft
 * Detail form implementation as far to retrieve the detail form and upen it.
 * (Shortly).
 *
 * Revision 1.9  2005/06/15 09:37:26  lollisoft
 * Better implementation for action abstraction. Parameters that are needed
 * to be passed are done with lb_I_Parameter. It's short before fulfill the master
 * detail form implementation.
 *
 * Revision 1.8  2005/06/12 10:30:55  lollisoft
 * Moved some classes to here.
 *
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

#ifndef __LB_DatabaseForm__
#define __LB_DatabaseForm__

#include <iostream>

/*...sclass lbConfigure_FK_PK_MappingDialog:0:*/
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

	wxChoice* cBoxFKNames;
	wxChoice* cBoxPKNames;

	wxStaticText *label;
	wxStaticText *labelF;
	
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
	int pass;
};
/*...e*/

/*...sclass lbAction:0:*/
class lbAction : public lb_I_Action
{
public:
	lbAction();
	virtual ~lbAction();

	void LB_STDCALL setActionID(char* id);	
	void LB_STDCALL execute(lb_I_Parameter* params);
	
	DECLARE_LB_UNKNOWN()
	
protected:

	void LB_STDCALL delegate(lb_I_Parameter* params);
	

	char* myActionID;
	UAP(lb_I_Database, db, __FILE__, __LINE__)
	
	UAP(lb_I_Container, actions, __FILE__, __LINE__)
};
/*...e*/

/*...sclass lbDetailFormAction:0:*/
class lbDetailFormAction : public lb_I_DelegatedAction
{
public:
	lbDetailFormAction();
	virtual ~lbDetailFormAction();

	void LB_STDCALL setActionID(char* id);	
	void LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);
	
	DECLARE_LB_UNKNOWN()
	
protected:

	void LB_STDCALL openDetailForm(lb_I_String* formularname, lb_I_Parameter* params);

	char* myActionID;
	UAP(lb_I_Database, db, __FILE__, __LINE__)
	UAP(lb_I_String, app, __FILE__, __LINE__)
	UAP(lb_I_String, masterForm, __FILE__, __LINE__)
	UAP(lb_I_String, SourceFieldName, __FILE__, __LINE__)
	UAP(lb_I_String, SourceFieldValue, __FILE__, __LINE__)
	UAP(lb_I_String, DBName, __FILE__, __LINE__)
	UAP(lb_I_String, DBUser, __FILE__, __LINE__)
	UAP(lb_I_String, DBPass, __FILE__, __LINE__)

	lb_I_DatabaseForm* detailForm;
};
/*...e*/
/*...sclass lbSQLQueryAction:0:*/
class lbSQLQueryAction : public lb_I_DelegatedAction
{
public:
	lbSQLQueryAction();
	virtual ~lbSQLQueryAction();

	void LB_STDCALL setActionID(char* id);	
	void LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);
	
	DECLARE_LB_UNKNOWN()
	
protected:
	char* myActionID;
	UAP(lb_I_Database, db, __FILE__, __LINE__)
};
/*...e*/

/*...sclass FormularActions:0:*/
/** \brief Management of formular actions.
 *
 * This class is used to concentrate the code for formular actions.
 */
class FormularActions {

public:

	FormularActions() {
		actions = NULL;
	}
	
	virtual ~FormularActions() {
		_CL_LOG << "FormularActions::~FormularActions() called." LOG_
	}
	
	/** \brief ID of action target.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when 
	 */
	char* getActionTargetID(char* what);
	
	/** \brief Source field of the action. */
	char* getActionSourceDataField(char* what);

	/** \brief ID for the action. */
	char* getActionID(char* what);

	/** \brief Get the action instance. */
	lb_I_Action* getAction(char* id);
	
protected:
	UAP(lb_I_Container, actions, __FILE__, __LINE__)
	char buffer[100];
};
/*...e*/

/*...sclass FormularFieldInformation:0:*/
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

/*...sclass lbMasterDetailFormDefinition:0:*/
class lbMasterDetailFormDefinition : 
	public lb_I_MasterDetailFormDefinition {

public:
	lbMasterDetailFormDefinition();
	virtual ~lbMasterDetailFormDefinition();

        void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master);
        
        void LB_STDCALL addMasterColumn(char* column);
         
        int LB_STDCALL getMasterColumns();
 
        lb_I_String* LB_STDCALL getMasterColumn(int pos);
 
        lb_I_DatabaseForm* LB_STDCALL getMasterForm();
         
        void LB_STDCALL setCharacterColumn(int pos, bool is = true);
         
        bool LB_STDCALL isCharacterColumn(int pos);
        
	DECLARE_LB_UNKNOWN()        	
	
private:
	lb_I_DatabaseForm* masterForm;
	
	UAP(lb_I_Container, masterColumns, __FILE__, __LINE__)
};
/*...e*/

/*...sclass lbDatabaseDialog:0:*/
/**
 * This is the sample database dialog for a wxWidgets based GUI.
 */


class lbDatabaseDialog :
	public lb_I_DatabaseForm,
	public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
	 */
	lbDatabaseDialog();

	/**
	 * Destructor
	 */
	virtual ~lbDatabaseDialog();

	lbErrCodes LB_STDCALL setName(char const * name) {
		free(formName);
		formName = strdup(name);	
		
		return ERR_NONE;
	}

	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	lbErrCodes LB_STDCALL addOwnerDrawn(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() { Destroy(); };
	
/*...sfrom DatabaseForm interface:8:*/
	void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass);

	char* LB_STDCALL getQuery();

	void LB_STDCALL setFilter(char* filter);
	
	const char* LB_STDCALL getControlValue(char* name);
	
/*...e*/

	void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);
	
	void LB_STDCALL updateFromMaster();

	int LB_STDCALL getPrimaryColumns();
	
	lb_I_String* LB_STDCALL getPrimaryColumn(int pos);
	   
	bool LB_STDCALL isCharacterColumn(char* name);

	lb_I_String* getTableName(char* columnName);

/*...sData navigation and other handlers:8:*/
	/**
	 * Database navigation
	 * 
	 * Moves to the first row.
	 */
	lbErrCodes LB_STDCALL lbDBFirst(lb_I_Unknown* uk);

	/**
	 * Database navigation
	 * 
	 * Moves to the next row.
	 */
	lbErrCodes LB_STDCALL lbDBNext(lb_I_Unknown* uk);

	/**
	 * Database navigation
	 * 
	 * Moves to the previous row.
	 */
	lbErrCodes LB_STDCALL lbDBPrev(lb_I_Unknown* uk);

	/**
	 * Database navigation
	 * 
	 * Moves to the last row.
	 */
	lbErrCodes LB_STDCALL lbDBLast(lb_I_Unknown* uk);
	
	/**
	 * Database manipulation
	 * 
	 * This adds a new row, while it copies the values of the actual form into the row.
	 */
	lbErrCodes LB_STDCALL lbDBAdd(lb_I_Unknown* uk);

	/**
	 * Database manipulation
	 * 
	 * Deletes the current row.
	 */
	lbErrCodes LB_STDCALL lbDBDelete(lb_I_Unknown* uk);

	/**
	 * Database manipulation
	 * 
	 * Internally used to update the current row.
	 */
	lbErrCodes LB_STDCALL lbDBUpdate();

	/**
	 * Database manipulation
	 *
	 * Clear the form.
	 */

	lbErrCodes LB_STDCALL lbDBClear();

	/**
	 * Database manipulation
	 * 
	 * Internally used to read data from the cursor to the current row.
	 */
	lbErrCodes LB_STDCALL lbDBRead();
/*...e*/

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
/*...e*/

	/** \brief Handler for button actions
	 *
	 * This handler should be used if a button action will be added to the form.
	 */
	lbErrCodes LB_STDCALL OnActionButton(lb_I_Unknown* uk);

	void OnDispatch(wxCommandEvent& event);

	/** \brief Paint the control.
	 *
	 * This handler should be used to paint an 'ownerdrawn' control.
	 * As in my Power++ code 'EditSymbol', this should also work under
	 * wxWidgets.
	 *
	 * The only problem would be the selection of which control currently
	 * fires the event. 'EditSymbol' only handles one such control.
	 */
	void OnPaint(wxCommandEvent& event);

	DECLARE_LB_UNKNOWN()

/*...svariables:8:*/
	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)
	UAP(lb_I_String, SQLString, __FILE__, __LINE__)
	UAP(lb_I_String, SQLWhere, __FILE__, __LINE__)

	UAP(lb_I_String, _DBName, __FILE__, __LINE__)
	UAP(lb_I_String, _DBUser, __FILE__, __LINE__)
	UAP(lb_I_String, _DBPass, __FILE__, __LINE__)
	
	/*
	 * Maps positions to id's for each displayed combo box.
	 *
	 * Store a container for each combo box with key(pos) and data(id). 
	 */
	UAP(lb_I_Container, ComboboxMapperList, __FILE__, __LINE__)
	
	/* Storage for all yet loaded actions. */
	UAP(lb_I_Container, actions, __FILE__, __LINE__)
	
	lb_I_DatabaseForm* _master;
	lb_I_Parameter* _params;

	UAP(lb_I_String, app, __FILE__, __LINE__)
	UAP(lb_I_String, masterForm, __FILE__, __LINE__)
	UAP(lb_I_String, SourceFieldName, __FILE__, __LINE__)
	UAP(lb_I_String, SourceFieldValue, __FILE__, __LINE__)
	UAP(lb_I_String, DBName, __FILE__, __LINE__)
	UAP(lb_I_String, DBUser, __FILE__, __LINE__)
	UAP(lb_I_String, DBPass, __FILE__, __LINE__)


	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];
	
	wxWindow* firstButton;
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
	char* formName;

	FormularFieldInformation* FFI;
	FormularActions* fa;
/*...e*/
};
/*...e*/


#ifdef __cplusplus
extern "C" {
#endif

DECLARE_SINGLETON_FUNCTOR(instanceOfPluginModule)

DECLARE_FUNCTOR(instanceOflbDatabaseDialog)
DECLARE_FUNCTOR(instanceOflbPluginDatabaseDialog)
DECLARE_FUNCTOR(instanceOflbAction)

DECLARE_FUNCTOR(instanceOflbDetailFormAction)
DECLARE_FUNCTOR(instanceOflbSQLQueryAction)

// Based on the 'group box' this control can be used to draw lines and so on.
DECLARE_FUNCTOR(instanceOflbOwnerDrawControl)

#ifdef __cplusplus
}
#endif


#endif // __LB_DatabaseForm__


