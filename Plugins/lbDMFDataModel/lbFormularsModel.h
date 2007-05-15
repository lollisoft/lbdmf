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

class lbFormularsModel : public lb_I_Formulars {
public:
	lbFormularsModel();
	virtual ~lbFormularsModel();

	long		LB_STDCALL addFormular(const char* name, const char* menuname, const char* eventname, const char* menuhilfe, long anwendung_id, long typ, long formular_id = -1);
	bool		LB_STDCALL selectFormular(long _id);
	int			LB_STDCALL getFormularCount();
	bool		LB_STDCALL hasMoreFormulars();
	void		LB_STDCALL setNextFormular();
	void		LB_STDCALL finishFormularIteration();
	
	char*		LB_STDCALL getName();
	char*		LB_STDCALL getMenuName();
	char*		LB_STDCALL getEventName();
	char*		LB_STDCALL getMenuHelp();
	long		LB_STDCALL getApplicationID();
	long		LB_STDCALL getTyp();
	long		LB_STDCALL getFormularID();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Container, Formulars)
	
	UAP(lb_I_String, currentFormularName)
	UAP(lb_I_String, currentMenuName)
	UAP(lb_I_String, currentEventName)
	UAP(lb_I_String, currentMenuHilfe)
	
	UAP(lb_I_Long, currentApplicationID)
	UAP(lb_I_Long, currentTyp)
	UAP(lb_I_Long, currentFormularID)

	UAP(lb_I_Long, marked)
};


DECLARE_FUNCTOR(instanceOflbFormularsModel)
