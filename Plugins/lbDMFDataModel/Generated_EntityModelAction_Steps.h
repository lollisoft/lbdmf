
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

/** \brief class Action_Steps.
 * Documentation for Action_Steps
 */
class lbAction_StepsModel : public lb_I_Action_Steps {
public:
	lbAction_StepsModel();
	virtual ~lbAction_StepsModel();

	long		LB_STDCALL addAction_Steps(const char* _bezeichnung, const char* _what, int _a_order_nr, long _type, long _actionid,  long _Action_StepsID = -1);

	bool		LB_STDCALL selectAction_Steps(long _id);
	int			LB_STDCALL getAction_StepsCount();
	bool		LB_STDCALL hasMoreAction_Steps();
	void		LB_STDCALL setNextAction_Steps();
	void		LB_STDCALL finishAction_StepsIteration();


	char*		LB_STDCALL get_bezeichnung();
	char*		LB_STDCALL get_what();
	int			LB_STDCALL get_a_order_nr();
	long		LB_STDCALL get_type();
	
	long		LB_STDCALL get_actionid();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()
	
	UAP(lb_I_Container, Action_Steps)
	

	UAP(lb_I_String, currentbezeichnung)
			
	UAP(lb_I_String, currentwhat)
			
	UAP(lb_I_Integer, currenta_order_nr)
			
	UAP(lb_I_Long, currenttype)
	
	UAP(lb_I_Long, currentactionid)
	

	
	UAP(lb_I_Long, currentAction_StepsID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbAction_StepsModel)
