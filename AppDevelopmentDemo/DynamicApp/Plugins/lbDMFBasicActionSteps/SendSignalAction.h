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
