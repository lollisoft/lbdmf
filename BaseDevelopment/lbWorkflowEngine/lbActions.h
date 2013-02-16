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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: lbActions.h,v 1.2 2013/02/16 10:36:25 lollisoft Exp $
 *
 * $Log: lbActions.h,v $
 * Revision 1.2  2013/02/16 10:36:25  lollisoft
 * Merged Release_1_0_4_stable_rc1_branch but doesn't yet compile.
 * Several files were conflicting and resolved in this checkin.
 *
 * Revision 1.1.2.1  2012/05/12 04:40:17  lollisoft
 * Moved action implementation out of DatabaseForm plugin and replaced wx related code with my own.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_SqlQueryAction__
#define __LB_SqlQueryAction__

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

	lb_I_ActionStep_Parameters* LB_STDCALL loadParametersForActionStep(lb_I_Long* step, lb_I_ActionStep_Parameters* allActionStepParameters = NULL, lb_I_Parameter* allParameters = NULL);

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

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOflbActions)

#ifdef __cplusplus
}
#endif


#endif // __LB_SqlQueryAction__


