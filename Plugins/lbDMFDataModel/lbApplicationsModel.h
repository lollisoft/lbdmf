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


class lbApplications : public lb_I_Applications {
public:
	lbApplications();
	virtual ~lbApplications();

	long	LB_STDCALL addApplication(const char* application, const char* titel, const char* modulename, const char* functor, const char* _interface, long _id);
	
	bool	LB_STDCALL selectApplication(const char* application);
	bool	LB_STDCALL selectApplication(long _id);
	
	int		LB_STDCALL getApplicationCount();
	
	bool	LB_STDCALL hasMoreApplications();
	void	LB_STDCALL setNextApplication();
	void	LB_STDCALL finishApplicationIteration();
	
	char*	LB_STDCALL getApplicationName();
	long	LB_STDCALL getApplicationID();
	char*	LB_STDCALL getApplicationTitle();
	char*	LB_STDCALL getApplicationFunctor();
	char*	LB_STDCALL getApplicationModule();
	char*	LB_STDCALL getApplicationInterface();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Container, Applications)
	
	UAP(lb_I_String, currentApplication)
	UAP(lb_I_String, currentTitel)
	UAP(lb_I_String, currentModuleName)
	UAP(lb_I_String, currentFunctor)
	UAP(lb_I_String, currentInterface)

	UAP(lb_I_Long, currentApplicationUID)
	
	UAP(lb_I_Long, marked)	
};

DECLARE_FUNCTOR(instanceOflbApplications)
