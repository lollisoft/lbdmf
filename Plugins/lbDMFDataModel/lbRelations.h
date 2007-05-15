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

class lbUserApplicationRelationModel : public lb_I_User_Applications {
public:
	lbUserApplicationRelationModel();
	virtual ~lbUserApplicationRelationModel();
	
	long LB_STDCALL addRelation(long app_id, long user_id, long _id = -1);
	
	bool	LB_STDCALL selectRelation(long _id);
	bool	LB_STDCALL addFilter(const char* filter, const char* value);
	bool	LB_STDCALL resetFilter(const char* filter = "");
	
	int		LB_STDCALL getRelationCount();
	bool	LB_STDCALL hasMoreRelations();
	void	LB_STDCALL setNextRelation();
	void	LB_STDCALL finishRelationIteration();
	long	LB_STDCALL getApplicationID();
	long	LB_STDCALL getUserID();
	long	LB_STDCALL getID();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Container, Relations)
	
	UAP(lb_I_Long, currentUserID)
	UAP(lb_I_Long, currentAppID)
	UAP(lb_I_Long, currentID)

	UAP(lb_I_Long, marked)
};


DECLARE_FUNCTOR(instanceOflbUserApplicationRelationModel)
