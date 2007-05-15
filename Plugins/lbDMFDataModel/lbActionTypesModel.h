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

class lbActionTypesModel : public lb_I_Actions {
public:
	lbActionTypesModel();
	virtual ~lbActionTypesModel();

	DECLARE_LB_UNKNOWN()

	long		LB_STDCALL addAction(const char* name, long typ, const char* source, long target, long _id = -1);
	bool		LB_STDCALL selectAction(long _id);
	int			LB_STDCALL getActionCount();
	bool		LB_STDCALL hasMoreActions();
	void		LB_STDCALL setNextAction();
	void		LB_STDCALL finishActionIteration();
	
	long		LB_STDCALL getActionID();
	long		LB_STDCALL getActionTyp();
	long		LB_STDCALL getActionTarget();

	char*		LB_STDCALL getActionSource();
	char*		LB_STDCALL getActionName();
	
	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	UAP(lb_I_Container, Actions)
	UAP(lb_I_Long, currentActionID)
	UAP(lb_I_Long, currentActionTyp)
	UAP(lb_I_Long, currentActionTarget)
	UAP(lb_I_String, currentActionName)
	UAP(lb_I_String, currentActionSource)
	
	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbActionTypesModel)
