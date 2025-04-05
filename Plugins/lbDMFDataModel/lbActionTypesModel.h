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

class lbActionTypesModel : public lb_I_Action_Types {
public:
	lbActionTypesModel();
	virtual ~lbActionTypesModel();

	DECLARE_LB_UNKNOWN()

	long		LB_STDCALL addActionTypes(const char* bezeichnung, const char* action_handler , const char* module, long _id = -1);
	bool		LB_STDCALL selectActionType(long _id);
	int			LB_STDCALL getActionTypesCount();
	bool		LB_STDCALL hasMoreActionTypes();
	void		LB_STDCALL setNextActionType();
	void		LB_STDCALL finishActionTypeIteration();
	
	long		LB_STDCALL getActionTypeID();

	char*		LB_STDCALL getActionTypeBezeichnung();
	char*		LB_STDCALL getActionTypeHandler();
	char*		LB_STDCALL getActionTypeModule();
	
	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	UAP(lb_I_Container, ActionTypes)
	UAP(lb_I_Long, currentActionTypesID)
	UAP(lb_I_String, currentActionTypesBezeichnung)
	UAP(lb_I_String, currentActionTypesHandler)
	UAP(lb_I_String, currentActionTypesModule)
	
	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbActionTypesModel)
