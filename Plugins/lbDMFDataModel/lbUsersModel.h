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

class lbUsersModel : public lb_I_UserAccounts {
public:
	lbUsersModel();
	virtual ~lbUsersModel();

	long		LB_STDCALL addAccount(const char* _user, const char* _pass, long _id = -1);
	bool		LB_STDCALL selectAccount(const char* _user);
	bool		LB_STDCALL selectAccount(long user_id);
	long		LB_STDCALL getUserCount();
	bool		LB_STDCALL hasMoreUsers();
	void		LB_STDCALL setNextUser();
	void		LB_STDCALL finishUserIteration();
	char*		LB_STDCALL getUserName();
	long		LB_STDCALL getID();
	char*		LB_STDCALL getUserPassword();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	void		LB_STDCALL setOperator(lb_I_Unknown* db);
	lbErrCodes	LB_STDCALL ExecuteOperation(const char* operationName);

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()
	
	UAP(lb_I_Container, Users)
	
	UAP(lb_I_String, currentUserName)
	UAP(lb_I_String, currentUserPassword)
	UAP(lb_I_Long, currentUserID)

	UAP(lb_I_Long, marked)
};


DECLARE_FUNCTOR(instanceOflbUsersModel)
