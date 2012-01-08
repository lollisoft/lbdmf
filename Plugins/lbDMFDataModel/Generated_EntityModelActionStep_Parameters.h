
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

/** \brief class ActionStep_Parameters.
 * Documentation for ActionStep_Parameters
 */
class ActionStep_ParametersModel : public lb_I_ActionStep_Parameters {
public:
	ActionStep_ParametersModel();
	virtual ~ActionStep_ParametersModel();

	long		LB_STDCALL addActionStep_Parameters(const char* _description, const char* _name, const char* _value, const char* _interface, long _action_step_id,  long _ActionStep_ParametersID = -1);

	bool		LB_STDCALL selectActionStep_Parameters(long _id);
	int			LB_STDCALL getActionStep_ParametersCount();
	bool		LB_STDCALL hasMoreActionStep_Parameters();
	void		LB_STDCALL setNextActionStep_Parameters();
	void		LB_STDCALL finishActionStep_ParametersIteration();


	char*		LB_STDCALL get_description();
	char*		LB_STDCALL get_name();
	char*		LB_STDCALL get_value();
	char*		LB_STDCALL get_interface();
	long		LB_STDCALL get_action_step_id();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	UAP(lb_I_Container, objectExtensions)
	

	UAP(lb_I_Container, ActionStep_Parameters)
	

	UAP(lb_I_String, currentdescription)
			
	UAP(lb_I_String, currentname)
			
	UAP(lb_I_String, currentvalue)
			
	UAP(lb_I_String, currentinterface)
			
	UAP(lb_I_Long, currentaction_step_id)
	

	
	UAP(lb_I_Long, currentActionStep_ParametersID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbActionStep_ParametersModel)
