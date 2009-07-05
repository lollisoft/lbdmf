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
            Heinrich-Scheufelen-Platz 2

            73252 Lenningen (germany)
*/
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.58 $
 * $Name:  $
 * $Id: lbDatabaseForm.h,v 1.58 2009/07/05 00:57:31 lollisoft Exp $
 *
 * $Log: lbDatabaseForm.h,v $
 * Revision 1.58  2009/07/05 00:57:31  lollisoft
 * Added new tableview dialog class and enabled switching
 * between table view and form view. This does not interfer
 * with panel and dialog view - as these are different flags.
 *
 * Revision 1.57  2009/06/30 09:04:33  lollisoft
 * Added flag to avoid validation while adding. But it seems to fail.
 *
 * Revision 1.56  2009/06/18 16:54:34  lollisoft
 * Corrected watcom related stuff.
 *
 * Revision 1.55  2009/06/17 20:37:17  lollisoft
 * Implemented non linear actions. These are 'flow' controlled action steps that could be modelled in UML activity diagrams. Export is not yet implemented but import from UML works.
 *
 * Revision 1.54  2009/01/10 10:38:06  lollisoft
 * Added some class variables to access them.
 *
 * Revision 1.53  2008/12/15 09:11:00  lollisoft
 * Added handlers for some user interaction.
 *
 * Revision 1.52  2008/12/09 18:08:50  lollisoft
 * Begun with the additional table view variant. This is currently active for the
 * wxNotebook variant. The wxDialog is still the old version.
 *
 * Revision 1.51  2008/11/13 19:03:09  lollisoft
 * Added a new action 'open application'.
 *
 * Revision 1.50  2008/10/03 14:28:06  lollisoft
 * Added a functionality to refresh the database forms.
 * This may be usefull when a database lock occures.
 *
 * Revision 1.49  2008/09/25 10:19:35  lollisoft
 * Added a function to notify on closing a form. This did not
 * really helped due to cached action classes contained also
 * a pointer to the formular, but it may be helpful in general.
 *
 * Revision 1.48  2008/06/29 17:15:26  lollisoft
 * Asking for showing visible fields for foreign keys now works. It get saved and also the usual form editing actions would be saved.
 *
 * There is still aproblem when only one field gets asked. So it will result in an index out of range error. And propably asking while opening a detail form is buggy.
 *
 * Revision 1.47  2008/04/10 06:43:44  lollisoft
 * Corrected non select statement handling.
 *
 * Revision 1.46  2008/03/16 20:26:12  lollisoft
 * Added a refresh button.
 *
 * Revision 1.45  2008/01/26 20:24:44  lollisoft
 * Implemented more functions regarding to meta data for sqlite database gateway. Some interface functions have
 * been changed to get proper working test application.
 *
 * These are getTableName and getColumnName in lb_I_Query interface.
 *
 * Revision 1.44  2007/11/22 16:16:32  lollisoft
 * Indicate, if window has been created.
 *
 * Revision 1.43  2007/10/12 16:16:32  lollisoft
 * React with error message, if action field was not found in formular. This is a configuration error either in UML or later in designer.
 *
 * Also tried to deactivate actions on empty query. This does
 * not fully work when deleting data entries.
 *
 * Revision 1.42  2007/10/11 13:38:40  lollisoft
 * Propably completed offline capability from system database.
 *
 * Revision 1.41  2007/10/06 16:41:34  lollisoft
 * Begun to move out code into visitor classes. But it does
 * not yet work. Deactivated.
 *
 * Revision 1.40  2007/10/04 13:10:43  lollisoft
 * Replaced more SQL queries by data model usage.
 *
 * Revision 1.39  2007/10/03 17:39:19  lollisoft
 * Changes to use data model classes instead of SQL queries.
 * At the end the SQL queries for the system data should
 * reside in visitor operations.
 *
 * Revision 1.38  2007/08/08 19:48:50  lollisoft
 * Changes to allow using BLOB data fields. Not completely finished.
 *
 * Revision 1.37  2007/07/07 16:22:57  lollisoft
 * Added reopen implementation.
 *
 * Revision 1.36  2007/06/06 21:33:24  lollisoft
 * Made bugfixes and enhancements that were required.
 *
 * Revision 1.35  2007/05/12 17:50:32  lollisoft
 * Added getFormName to enable bugfix in wxWrapperDLL.cpp.
 * Will also be usefull in general.
 *
 * Revision 1.34  2007/02/11 22:37:29  lollisoft
 * Working icon configuration on formulars.
 * These icons would be shown in toolbar.
 *
 * Revision 1.33  2007/01/29 20:12:59  lollisoft
 * Checkin for Linux.
 *
 * Revision 1.32  2006/07/02 13:12:54  lollisoft
 * Begun with data model classes support.
 *
 * Revision 1.31  2006/02/21 19:35:51  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.30  2006/01/30 15:54:15  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.29  2005/12/13 23:41:09  lollisoft
 * Code may work properly, but doesn't compile well. Compiler bug ?
 * I know about a macro bug when missing one backslash, but I haven't
 * created one in my last changes - I think.
 *
 * Revision 1.28  2005/12/02 17:45:31  lollisoft
 * Added members (deleteButton, allNaviDisabled).
 *
 * Revision 1.27  2005/11/18 23:41:32  lollisoft
 * More memory leaks have been fixed. There are currently less than 200
 * chunks unfreed, wich may be located in the plugin mechanism.
 *
 * Revision 1.26  2005/11/11 22:51:30  lollisoft
 * Memory leaks removed. There are currently only 4 chunks leaky.
 * These may be false positives, because one of them is an allocated
 * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
 * wxMenuBar gets an owner (see wxWidgets documentation).
 *
 * Revision 1.25  2005/10/31 15:17:17  lollisoft
 * Changed plugin classes to be singletons.
 *
 * Revision 1.24  2005/10/03 17:15:14  lollisoft
 * Latest changes for release 0.5.1 under Linux
 *
 * Revision 1.23  2005/10/02 16:51:48  lollisoft
 * New wxNotebook layout completed. Not yet changeable at runtime, but it works.
 *
 * Revision 1.22  2005/10/01 15:36:27  lollisoft
 * Added lbDatabasePanel class. lbDatabaseForm now works with the
 * panel implementation, so it may be possible to implement a tabbed
 * layout.
 *
 * Revision 1.21  2005/09/11 22:10:24  lollisoft
 * Better handling of inserting data on empty result set.
 * If the result set is empty, the navigation buttons are
 * deactivated and adding/updating added data is done
 * with the add button.
 *
 * All other buttons else should also be deactivated in
 * adding mode.
 *
 * Revision 1.20  2005/08/24 20:41:46  lollisoft
 * Bugfix in selecting actions based on untranslated,
 * but with some text appended formular name.
 *
 * Revision 1.19  2005/08/15 17:48:04  lollisoft
 * Access to all controls.
 *
 * Revision 1.18  2005/08/10 21:54:37  lollisoft
 * Translation works correctly. There was a lookup problem with translated
 * formular names.
 *
 * Revision 1.17  2005/08/07 15:31:14  lollisoft
 * Added functions needed to implement detail -> master formulars.
 *
 * Revision 1.16  2005/07/25 20:56:12  lollisoft
 * Collect the master detail relation data to be used as default values,
 * when new data will be added in the detail form.
 *
 * So hidden fields gets set up correctly without user interaction.
 *
 * Revision 1.15  2005/07/24 16:58:29  lollisoft
 * Much changes to get master detail forms nearly run.
 *
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
#include "wx/grid.h"

/*...sclass lbConfigure_FK_PK_MappingDialog:0:*/
class lbConfigure_FK_PK_MappingDialog :
//	public lb_I_Unknown,
	public lb_I_Window,
	public lb_I_EventHandler,
	public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
	 */
	lbConfigure_FK_PK_MappingDialog();
	lbConfigure_FK_PK_MappingDialog(long FormularID);

	/**
	 * Destructor
	 */
	virtual ~lbConfigure_FK_PK_MappingDialog();

	int prepareDialogHandler();

	void LB_STDCALL create(int parentId) { }
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL init(lb_I_Query* query, char* DBName, char* DBUser, char* DBPass);

	void LB_STDCALL show() { ShowModal (); };
	void LB_STDCALL destroy() {
		Destroy();
	};

	void LB_STDCALL windowIsClosing(lb_I_Window* w);

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

	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)

	/**
	 * \brief Maps positions to id's for each displayed combo box.
	 *
	 * Store a container for each combo box with key(pos) and data(id).
	 */
	UAP(lb_I_Container, ComboboxMapperList)
	UAP(lb_I_Query, sourceQuery)
	UAP(lb_I_Database, queryDB)

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
	char* _DBUser;
	char* _DBName;
	char* _DBPass;
	long _FoimularID;
};
/*...e*/

/*...sclass lbAction:0:*/
class lbAction : public lb_I_Action
{
public:
	lbAction();
	virtual ~lbAction();

	void LB_STDCALL setActionID(long id);
	void LB_STDCALL execute(lb_I_Parameter* params);

	DECLARE_LB_UNKNOWN()

protected:
	void LB_STDCALL loadDataModel();
	long LB_STDCALL delegate(lb_I_Parameter* params);

	/** \brief Create a list of transitions for the current action step.
	 * In a linear action there are no transitions and this function therefore will return a NULL pointer.
	 * If there is a linear step with a transition, then one transition could be in the object only.
	 * If there is a decision step then transitions must be configured and minimally two should be there.
	 * Only one transition could have an empty expression. This is the else alternative flow.
	 * Currently I do not know how the order in a UML decision is implemented. I expect a order in the same
	 * as the designer has added the transitions.
	 *
	 * If allTransitions is not NULL, then the data has been loaded prior and no direct database query is needed.
	 */
	lb_I_Action_Step_Transitions* LB_STDCALL loadTransitionsForActionStep(lb_I_Long* step, lb_I_Action_Step_Transitions* allTransitions = NULL);

	lb_I_ActionStep_Parameters* LB_STDCALL loadParametersForActionStep(lb_I_Long* step, lb_I_ActionStep_Parameters* allActionStepParameters = NULL);

	long LB_STDCALL getNextStepId(lb_I_Action_Step_Transitions* trans, lb_I_Parameter* params, long id);

	bool initialized;
	long myActionID;
	UAP(lb_I_Database, db)

	UAP(lb_I_Container, actions)

	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)
	UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)

};
/*...e*/

/*...sclass lbDetailFormAction:0:*/
class lbDetailFormAction : public lb_I_DelegatedAction
{
public:
	lbDetailFormAction();
	virtual ~lbDetailFormAction();

	void LB_STDCALL setActionID(long id);
	long LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);

	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	DECLARE_LB_UNKNOWN()

protected:

	bool LB_STDCALL openDetailForm(lb_I_String* formularname, lb_I_Parameter* params);

	long myActionID;
	UAP(lb_I_Database, db)
	UAP(lb_I_String, app)
	UAP(lb_I_String, masterForm)
	UAP(lb_I_String, SourceFieldName)
	UAP(lb_I_String, SourceFieldValue)
	UAP(lb_I_String, DBName)
	UAP(lb_I_String, DBUser)
	UAP(lb_I_String, DBPass)

	lb_I_DatabaseForm* detailForm;
};
/*...e*/
/*...sclass lbMasterFormAction:0:*/
class lbMasterFormAction : public lb_I_DelegatedAction
{
public:
	lbMasterFormAction();
	virtual ~lbMasterFormAction();

	void LB_STDCALL setActionID(long id);
	long LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);

	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	DECLARE_LB_UNKNOWN()

protected:

	bool LB_STDCALL openMasterForm(lb_I_String* formularname, lb_I_Parameter* params);

	long myActionID;
	UAP(lb_I_Database, db)
	UAP(lb_I_String, app)
	UAP(lb_I_String, detailForm)
	UAP(lb_I_String, SourceFieldName)
	UAP(lb_I_String, SourceFieldValue)
	UAP(lb_I_String, DBName)
	UAP(lb_I_String, DBUser)
	UAP(lb_I_String, DBPass)

	lb_I_DatabaseForm* masterForm;
};
/*...e*/
/*...sclass lbSQLQueryAction:0:*/
class lbSQLQueryAction : public lb_I_DelegatedAction
{
public:
	lbSQLQueryAction();
	virtual ~lbSQLQueryAction();

	void LB_STDCALL setActionID(long id);
	long LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);

	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	DECLARE_LB_UNKNOWN()

protected:
	long myActionID;
	UAP(lb_I_Database, db)
};
/*...e*/
/*...sclass lbExecuteAction:0:*/
class lbExecuteAction : public lb_I_DelegatedAction
{
public:
	lbExecuteAction();
	virtual ~lbExecuteAction();

	void LB_STDCALL setActionID(long id);
	long LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);

	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	DECLARE_LB_UNKNOWN()

protected:
	long myActionID;
	UAP(lb_I_Database, db)
};
/*...e*/
/*...sclass lbExecuteAction:0:*/
/** \brief Used to dynamically call a dispatcher function.
 * Send signal normally means an asyncron message. This implementation currently is based on the sample activity diagram to
 * call a dispatchable function. The dispatcher function to be used in the sample is the msgBox function to show an error message.
 *
 * To enable proper functionality, the action step parameters must be configured properly. The message is not passed into the action
 * and thus you don't need an action parameter for it. But the action step needs a list of parameters. The list of parameters is stored
 * in the table action_step_parameter who is related to the current action step.
 *
 * The dispatchable function 'msgBox' needs two parameters to properly function. This function also is implemented in lb_I_MetaApplication,
 * but here it demonstrates the purpose of dynamic invocation like function call.
 *
 * @title	lb_I_String	The message box title you will see.
 * @msg		lb_I_String	The message to display.
 */
class lbSendSignalAction : public lb_I_DelegatedAction
	{
	public:
		lbSendSignalAction();
		virtual ~lbSendSignalAction();

		void LB_STDCALL setActionID(long id);
		long LB_STDCALL execute(lb_I_Parameter* params);

		void LB_STDCALL setDatabase(lb_I_Database* _db);

		void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
		void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

		DECLARE_LB_UNKNOWN()

	protected:

		/** \brief Replaces a placeholder with the data from params.
		 * This function replaces a placeholder ({<Placeholder>}) with it's corresponding value from params.
		 */
		lb_I_String* LB_STDCALL substitutePlaceholder(lb_I_String* value, lb_I_Parameter* params);

		long myActionID;
		UAP(lb_I_Database, db)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_ActionStep_Parameters, SignalParams)
	};
/*...e*/
/*...sclass lbDesicionAction:0:*/
class lbDecisionAction : public lb_I_DelegatedAction
{
public:
	lbDecisionAction();
	virtual ~lbDecisionAction();

	void LB_STDCALL setActionID(long id);
	long LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);

	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	DECLARE_LB_UNKNOWN()

protected:
	long myActionID;
	UAP(lb_I_Database, db)
	UAP(lb_I_Action_Step_Transitions, transitions)
};
/*...e*/
/*...sclass lbDesicionAction:0:*/
class lbOpAqueOperation : public lb_I_DelegatedAction
	{
	public:
		lbOpAqueOperation();
		virtual ~lbOpAqueOperation();

		void LB_STDCALL setActionID(long id);
		long LB_STDCALL execute(lb_I_Parameter* params);

		void LB_STDCALL setDatabase(lb_I_Database* _db);

		void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
		void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

		DECLARE_LB_UNKNOWN()

	protected:
		long myActionID;
		UAP(lb_I_Database, db)
	};
/*...e*/

/*...sclass FormularActions:0:*/
/** \brief Management of formular actions.
 *
 * This class is used to concentrate the code for formular actions.
 *
 * These includes opening detail or master forms, performing validations,
 * calculating combined values and so on.
 *
 * All  these actions should be configurable and activated at initializion
 * time.
 *
 * Upon the fact, that this class knows about open detail/master forms, it
 * should be also responsible to update the detail/master views when the user
 * changes the peer.
 */
class FormularActions {

public:

	FormularActions() {
		//actions = NULL;
	}

	virtual ~FormularActions() {
		_CL_LOG << "FormularActions::~FormularActions() called." LOG_

		if (actions != NULL) _CL_LOG << "Actions has " << actions->getRefCount() << " references." LOG_
	}


	/** \brief Add a mapping from event name to it's action ID.
	 */
	void addRegisteredAction(long ActionID, char* eventName);

	/** \brief ID of action target.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when
	 */
	char* getActionTargetID(char* reversed_event);

	/** \brief ID of action target as long.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when
	 */
	long getActionTargetIDLong(char* reversed_event);

	/** \brief Source field of the action. */
	char* getActionSourceDataField(char* reversed_event);

	/** \brief ID for the action. */
	long getActionID(char* reversed_event);

	/** \brief Get the action instance.
	 *
	 * This function creates the requested action instance, stores it for caching and
	 * then returns a reference to it.
	 */
	lb_I_Action* getAction(long id);

	/** \brief Validate the form.
	 *
	 * Use this function to check, if the data has a correct state.
	 */
	bool validate() { return true; }

	/** \brief Update master/detail views and related views.
	 *
	 * Use this function to update related views. This may master/detail views and
	 * possibly views, containing data fields related to any open views.
	 */
	bool update() { return true; }

protected:
	UAP(lb_I_Container, eventmapping)
	UAP(lb_I_Container, actions)
	UAP(lb_I_Actions, appActions)
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
	virtual ~FormularFieldInformation() {
		_CL_LOG << "ROFields has " << ROFields->getRefCount() << " references." LOG_
		_CL_LOG << "SCFields has " << SCFields->getRefCount() << " references." LOG_
	}

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

	UAP(lb_I_Container, ROFields)
	UAP(lb_I_Container, SCFields)
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

	UAP(lb_I_Container, masterColumns)
};
/*...e*/

/*...sclass lbOwnerDrawControl:0:*/
class lbOwnerDrawControl :
        public lb_I_Control,
public wxControl {

public:
	lbOwnerDrawControl();

	virtual ~lbOwnerDrawControl();

	void LB_STDCALL create(int parentId) { }
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL windowIsClosing(lb_I_Window* w);
	void LB_STDCALL init(lb_I_Window* parent);

	void OnPaint(wxPaintEvent &event);

	DECLARE_LB_UNKNOWN()

	DECLARE_EVENT_TABLE()
};

/*...sclass lbDatabasePanel:0:*/
/**
 * This is the sample database dialog for a wxWidgets based GUI.
 */
class lbDatabasePanel :
	public lb_I_DatabaseForm,
	public wxPanel {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
	 */
	lbDatabasePanel();

	/**
	 * Destructor
	 */
	virtual ~lbDatabasePanel();

	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);

	char*	   LB_STDCALL getFormName() { return formName; }

	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	lbErrCodes LB_STDCALL addOwnerDrawn(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	void LB_STDCALL addLabel(char* text, wxSizer* sizer, bool hideThisColumn);

	void LB_STDCALL create(int parentId);
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() {
		if (_created) Destroy();
		_created = false;
	};

/*...sfrom DatabaseForm interface:8:*/
	void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass);

	char* LB_STDCALL getQuery();

	void LB_STDCALL setFilter(char* filter);

	const char* LB_STDCALL getControlValue(char* name);

/*...e*/

	void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);

	void LB_STDCALL setDetailForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);

	void LB_STDCALL updateFromMaster();

	void LB_STDCALL updateFromDetail();

	int LB_STDCALL getPrimaryColumns();

	const char* LB_STDCALL getControlValue(int pos);
	int LB_STDCALL getControls();

	lb_I_String* LB_STDCALL getPrimaryColumn(int pos);

	int LB_STDCALL getForeignColumns(char* primaryTable);

	lb_I_String* LB_STDCALL getForeignColumn(int pos);

	bool LB_STDCALL isCharacterColumn(char* name);

	void LB_STDCALL ignoreForeignKeys(char* toTable);

	lb_I_String* LB_STDCALL getTableName(char* columnName);

	lb_I_String* LB_STDCALL getColumnName(int pos);

	void  LB_STDCALL reopen();

	/** \brief Close database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL close();

	/** \brief Open database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL open();

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
	 * Refresh the database query and refill the dropdown listboxes.
	 */
	lbErrCodes LB_STDCALL lbDBRefresh(lb_I_Unknown* uk);

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

	void LB_STDCALL windowIsClosing(lb_I_Window* w);


	void LB_STDCALL activateActionButtons();
	void LB_STDCALL deactivateActionButtons();

	/** \brief Handler for button actions
	 *
	 * This handler should be used if a button action will be added to the form.
	 */
	lbErrCodes LB_STDCALL OnActionButton(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL DoValidation(lb_I_Unknown* uk);

	void OnDispatch(wxCommandEvent& event);
	void OnImageButtonClick(wxCommandEvent& event);
	void OnMouseMove(wxMouseEvent& evt);

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

    int LB_STDCALL lookupColumnIndex(char* name);

    // Helperfunctions that later may be factory functions for the controls.
    void LB_STDCALL addSpecialField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addComboField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addTextField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addLongField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addIntegerField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addCheckField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addDateField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addFloatField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addBinaryField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);

	DECLARE_LB_UNKNOWN()

/*...svariables:8:*/
	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)
	UAP(lb_I_String, SQLString)
	UAP(lb_I_String, SQLWhere)

	UAP(lb_I_String, _DBName)
	UAP(lb_I_String, _DBUser)
	UAP(lb_I_String, _DBPass)

	/*
	 * Maps positions to id's for each displayed combo box.
	 *
	 * Store a container for each combo box with key(pos) and data(id).
	 */
	UAP(lb_I_Container, ComboboxMapperList)

	/*
	 * An image button will be loaded from a file name. This filename must be stored here.
	 */
	UAP(lb_I_Container, ImageButtonMapperList)

	/* Storage for all yet loaded actions. */
	UAP(lb_I_Container, actions)

	UAP(lb_I_String, app)
	UAP(lb_I_String, masterForm)
	UAP(lb_I_String, detailForm)
	UAP(lb_I_String, SourceFieldName)
	UAP(lb_I_String, SourceFieldValue)
	UAP(lb_I_String, DBName)
	UAP(lb_I_String, DBUser)
	UAP(lb_I_String, DBPass)


	UAP(lb_I_Container, ignoredPKTables)
	UAP(lb_I_Container, MasterDetailRelationData)

	// Preloaded data from database, if plugins are available.
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Parameters, appActionParameters)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)

	// List of button names to help activating / deactivating them on data availability.
	UAP(lb_I_Container, actionButtons)

    UAP(lb_I_EventManager, eman)
    UAP(lb_I_Dispatcher, dispatcher)

	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];

	wxWindow* refreshButton;
	wxWindow* firstButton;
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
	wxWindow* deleteButton;

	bool allNaviDisabled;
	bool noDataAvailable;
	bool isAdding;
	bool skipValidation;
	bool _created;

	char* base_formName;
	char* formName;
	char* untranslated_formName;

	FormularFieldInformation* FFI;
	FormularActions* fa;

	lb_I_DatabaseForm* _master;
	lb_I_DatabaseForm* _detail;
	lb_I_Parameter* _params;
/*...e*/
};
/*...e*/


class lbDatabaseTableViewPanel :
	public lb_I_DatabaseForm,
	public wxPanel {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
	 */
	lbDatabaseTableViewPanel();

	/**
	 * Destructor
	 */
	virtual ~lbDatabaseTableViewPanel();

	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);

	char*	   LB_STDCALL getFormName() { return formName; }

	void LB_STDCALL create(int parentId);
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() {
		if (_created) Destroy();
		_created = false;
	};

/*...sfrom DatabaseForm interface:8:*/
	void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass);

	char* LB_STDCALL getQuery();

	void LB_STDCALL setFilter(char* filter);

	const char* LB_STDCALL getControlValue(char* name);

/*...e*/

	void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);

	void LB_STDCALL setDetailForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);

	void LB_STDCALL updateFromMaster();

	void LB_STDCALL updateFromDetail();

	int LB_STDCALL getPrimaryColumns();

	const char* LB_STDCALL getControlValue(int pos);
	int LB_STDCALL getControls();

	lb_I_String* LB_STDCALL getPrimaryColumn(int pos);

	int LB_STDCALL getForeignColumns(char* primaryTable);

	lb_I_String* LB_STDCALL getForeignColumn(int pos);

	bool LB_STDCALL isCharacterColumn(char* name);

	void LB_STDCALL ignoreForeignKeys(char* toTable);

	lb_I_String* LB_STDCALL getTableName(char* columnName);

	lb_I_String* LB_STDCALL getColumnName(int pos);

	void  LB_STDCALL reopen();

	/** \brief Close database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL close();

	/** \brief Open database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL open();

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
	 * Refresh the database query and refill the dropdown listboxes.
	 */
	lbErrCodes LB_STDCALL lbDBRefresh(lb_I_Unknown* uk);

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

	void LB_STDCALL windowIsClosing(lb_I_Window* w);


	void LB_STDCALL activateActionButtons();
	void LB_STDCALL deactivateActionButtons();

	/** \brief Handler for button actions
	 *
	 * This handler should be used if a button action will be added to the form.
	 */
	lbErrCodes LB_STDCALL OnActionButton(lb_I_Unknown* uk);

	void OnDispatch(wxCommandEvent& event);
	void OnImageButtonClick(wxCommandEvent& event);
	void OnMouseMove(wxMouseEvent& evt);

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

    void LB_STDCALL fillRow(int position);
    void LB_STDCALL fillTable();
    int LB_STDCALL lookupColumnIndex(char* name);

    // Helperfunctions that later may be factory functions for the controls.
    void LB_STDCALL addSpecialField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addComboField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addTextField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addLongField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addIntegerField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addCheckField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addDateField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addFloatField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addBinaryField(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);

    void LB_STDCALL addSpecialColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addComboColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addTextColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addLongColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addIntegerColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addCheckColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addDateColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addFloatColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);
    void LB_STDCALL addBinaryColumn(char* name, wxSizer* sizerMain, wxSizer* sizerControl, wxSizer* sizerLabel, bool hideThisColumn = false);

    // wxGrid event handler
    void OnCellValueChanged( wxGridEvent& ev );
    void OnSelectCell( wxGridEvent& ev );

    // Old factory methods (obsolede ?)
	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	lbErrCodes LB_STDCALL addOwnerDrawn(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	void LB_STDCALL addLabel(char* text, wxSizer* sizer, bool hideThisColumn);

    // wxGrid based functions
    void LB_STDCALL setColumnReadonly(int column);
    void LB_STDCALL setColumnLabel(int column, char* name);

    void LB_STDCALL setCellCombo(int row, int col, lb_I_Container* s, lb_I_Long* current);
    void LB_STDCALL setCellText(int row, int col, lb_I_String* s);
    void LB_STDCALL setCellInteger(int row, int col, lb_I_Integer* s);
    void LB_STDCALL setCellLong(int row, int col, lb_I_Long* s);
    void LB_STDCALL setCellBool(int row, int col, lb_I_Boolean* s);
    void LB_STDCALL setCellDate(int row, int col, lb_I_String* s);
    void LB_STDCALL setCellFloat(int row, int col, lb_I_String* s);

    void LB_STDCALL createTableViewControls(int columns);

	DECLARE_LB_UNKNOWN()

/*...svariables:8:*/
	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)
	UAP(lb_I_String, SQLString)
	UAP(lb_I_String, SQLWhere)

	UAP(lb_I_String, _DBName)
	UAP(lb_I_String, _DBUser)
	UAP(lb_I_String, _DBPass)

	/*
	 * Maps positions to id's for each displayed combo box.
	 *
	 * Store a container for each combo box with key(pos) and data(id).
	 */
	UAP(lb_I_Container, ComboboxMapperList)

	/*
	 * An image button will be loaded from a file name. This filename must be stored here.
	 */
	UAP(lb_I_Container, ImageButtonMapperList)

	/* Storage for all yet loaded actions. */
	UAP(lb_I_Container, actions)

	UAP(lb_I_String, app)
	UAP(lb_I_String, masterForm)
	UAP(lb_I_String, detailForm)
	UAP(lb_I_String, SourceFieldName)
	UAP(lb_I_String, SourceFieldValue)
	UAP(lb_I_String, DBName)
	UAP(lb_I_String, DBUser)
	UAP(lb_I_String, DBPass)


	UAP(lb_I_Container, ignoredPKTables)
	UAP(lb_I_Container, MasterDetailRelationData)

	// Preloaded data from database, if plugins are available.
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)

	// List of button names to help activating / deactivating them on data availability.
	UAP(lb_I_Container, actionButtons)

    UAP(lb_I_EventManager, eman)
    UAP(lb_I_Dispatcher, dispatcher)

	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];

	wxWindow* refreshButton;
	wxWindow* firstButton;
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
	wxWindow* deleteButton;

	bool allNaviDisabled;
	bool noDataAvailable;
	bool isAdding;
	bool _created;

	char* base_formName;
	char* formName;
	char* untranslated_formName;

	FormularFieldInformation* FFI;
	FormularActions* fa;

	lb_I_DatabaseForm* _master;
	lb_I_DatabaseForm* _detail;
	lb_I_Parameter* _params;

	/// \brief The table with the data.
	wxGrid* TableView;

	/// \brief The sizer that contains the buttons.
	wxBoxSizer* buttonSizer;

	UAP(lb_I_Parameter, currentRow)
    /// Current page of numRows
	long page;
	int numRows;

/*...e*/
};

/*...sclass lbDatabaseDialog:0:*/
class lbDatabaseDialog :
	public lb_I_DatabaseForm,
	public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
	 */
	lbDatabaseDialog();

	/**
	 * Destructor
	 */
	virtual ~lbDatabaseDialog();

	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);

	char*      LB_STDCALL getFormName();

	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	lbErrCodes LB_STDCALL addOwnerDrawn(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	void LB_STDCALL create(int parentId);
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() { if (_created) Destroy(); };

/*...sfrom DatabaseForm interface:8:*/
	void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass);

	char* LB_STDCALL getQuery();

	void LB_STDCALL setFilter(char* filter);

	const char* LB_STDCALL getControlValue(char* name);

/*...e*/

	void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);

	void LB_STDCALL setDetailForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);

	void LB_STDCALL updateFromMaster();

	void LB_STDCALL updateFromDetail();

	int LB_STDCALL getPrimaryColumns();

	const char* LB_STDCALL getControlValue(int pos);
	int LB_STDCALL getControls();

	lb_I_String* LB_STDCALL getPrimaryColumn(int pos);

	int LB_STDCALL getForeignColumns(char* primaryTable);

	lb_I_String* LB_STDCALL getForeignColumn(int pos);

	bool LB_STDCALL isCharacterColumn(char* name);

	void LB_STDCALL ignoreForeignKeys(char* toTable);

	lb_I_String* LB_STDCALL getTableName(char* columnName);

	lb_I_String* LB_STDCALL getColumnName(int pos);

	void  LB_STDCALL reopen();

	/** \brief Close database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL close();

	/** \brief Open database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL open();

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

	void LB_STDCALL windowIsClosing(lb_I_Window* w);

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

	lbDatabasePanel* panel;
	bool _created;
};
/*...e*/

class lbDatabaseTableViewDialog :
public lb_I_DatabaseForm,
public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
	 */
	lbDatabaseTableViewDialog();
	
	/**
	 * Destructor
	 */
	virtual ~lbDatabaseTableViewDialog();
	
	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);
	
	char*      LB_STDCALL getFormName();
	
	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };
	
	lbErrCodes LB_STDCALL addOwnerDrawn(char* name, int x, int y, int w, int h) { return ERR_NONE; };
	
	void LB_STDCALL create(int parentId);
	int  LB_STDCALL getId() { return GetId(); }
	
	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() { if (_created) Destroy(); };
	
	/*...sfrom DatabaseForm interface:8:*/
	void LB_STDCALL init(char* SQLString, char* DBName, char* DBUser, char* DBPass);
	
	char* LB_STDCALL getQuery();
	
	void LB_STDCALL setFilter(char* filter);
	
	const char* LB_STDCALL getControlValue(char* name);
	
	/*...e*/
	
	void LB_STDCALL setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);
	
	void LB_STDCALL setDetailForm(lb_I_DatabaseForm* master, lb_I_Parameter* params);
	
	void LB_STDCALL updateFromMaster();
	
	void LB_STDCALL updateFromDetail();
	
	int LB_STDCALL getPrimaryColumns();
	
	const char* LB_STDCALL getControlValue(int pos);
	int LB_STDCALL getControls();
	
	lb_I_String* LB_STDCALL getPrimaryColumn(int pos);
	
	int LB_STDCALL getForeignColumns(char* primaryTable);
	
	lb_I_String* LB_STDCALL getForeignColumn(int pos);
	
	bool LB_STDCALL isCharacterColumn(char* name);
	
	void LB_STDCALL ignoreForeignKeys(char* toTable);
	
	lb_I_String* LB_STDCALL getTableName(char* columnName);
	
	lb_I_String* LB_STDCALL getColumnName(int pos);
	
	void  LB_STDCALL reopen();
	
	/** \brief Close database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL close();
	
	/** \brief Open database query.
	 * Used when multiple forms should be reopened. Then all should be closed first before one get's reopened.
	 * This avoids invalid errors I think would happen.
	 */
	lbErrCodes LB_STDCALL open();
	
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
	
	void LB_STDCALL windowIsClosing(lb_I_Window* w);
	
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
	
	lbDatabaseTableViewPanel* panel;
	bool _created;
};


#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOfPluginModule)

DECLARE_FUNCTOR(instanceOflbDatabasePanel)
DECLARE_FUNCTOR(instanceOflbPluginDatabasePanel)
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


