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
            Heinrich-Scheufelen-Platz 2

            73252 Lenningen (germany)
*/
/*...e*/

class lbActionStepsModel : public lb_I_Action_Steps {
public:
	lbActionStepsModel();
	virtual ~lbActionStepsModel();

	DECLARE_LB_UNKNOWN()

	long		LB_STDCALL addActionStep(const char* bezeichnung, long actionid, long orderNo, long type, const char* what, long _id = -1);
	bool		LB_STDCALL selectActionStep(long _id);
	
	int		LB_STDCALL getActionStepCount();
	bool		LB_STDCALL hasMoreActionSteps();
	void		LB_STDCALL setNextActionStep();
	void		LB_STDCALL finishActionStepIteration();
	
	char*		LB_STDCALL getActionStepBezeichnung();
	long		LB_STDCALL getActionStepID();
	long		LB_STDCALL getActionStepActionID();
	long		LB_STDCALL getActionStepOrderNo();
	long		LB_STDCALL getActionStepType();
	char*		LB_STDCALL getActionStepWhat();
	
	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	UAP(lb_I_Container, Actions)
	UAP(lb_I_Long, currentActionStepID)
	UAP(lb_I_String, currentActionStepBezeichnung)
	UAP(lb_I_Long, currentActionStepActionID)
	UAP(lb_I_Long, currentActionStepOrderNo)
	UAP(lb_I_Long, currentActionStepType)
	UAP(lb_I_String, currentActionStepWhat)

	UAP(lb_I_Long, marked)
};

class lbActionStepTransitionsModel : public lb_I_Action_Step_Transitions {
public:
	lbActionStepTransitionsModel();
	virtual ~lbActionStepTransitionsModel();

	DECLARE_LB_UNKNOWN()

	long		LB_STDCALL addTransition(const char* expression, long src_actionid, long dst_actionid, const char* description, long _id = -1);
	bool		LB_STDCALL selectTransition(long _id);
	int			LB_STDCALL getActionStepTransitionsCount();
	bool		LB_STDCALL hasMoreActionStepTransitions();
	void		LB_STDCALL setNextActionStepTransition();
	void		LB_STDCALL finishActionStepTransitionIteration();
	
	long		LB_STDCALL getActionStepTransitionID();
	long		LB_STDCALL getActionStepTransitionSrcActionID();
	long		LB_STDCALL getActionStepTransitionDstActionID();

	char*		LB_STDCALL getActionStepTransitionDecision();
	char*		LB_STDCALL getActionStepTransitionDescription();
	
	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();
	
	UAP(lb_I_Container, Actions)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentSrcActionId)
	UAP(lb_I_Long, currentDstActionId)
	UAP(lb_I_String, currentDescription)
	UAP(lb_I_String, currentDecision)

	UAP(lb_I_Long, marked)

};


DECLARE_FUNCTOR(instanceOflbActionStepsModel)
DECLARE_FUNCTOR(instanceOflbActionStepTransitionsModel)
