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

class lbFormularParameters : public lb_I_FormularParameter {
public:
	lbFormularParameters();
	virtual ~lbFormularParameters();

	bool		LB_STDCALL selectParameter(long _id);

	char*		LB_STDCALL getParameter(const char* name, long formular_id);
	
	int			LB_STDCALL getParameterCount();
	bool		LB_STDCALL hasMoreParameters();
	void		LB_STDCALL setNextParameter();
	void		LB_STDCALL finishParameterIteration();

	long		LB_STDCALL getParameterID();
	char*		LB_STDCALL getParameterName();
	char*		LB_STDCALL getParameterValue();

	long		LB_STDCALL addParameter(const char* name, const char* value, long formular_id, long _id = -1);
	long		LB_STDCALL getFormularID();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Container, Parameters)
	
	UAP(lb_I_String, currentParameterName)
	UAP(lb_I_String, currentParameterValue)
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentFormularID)

	UAP(lb_I_Long, marked)
};

class lbApplicationParameters : public lb_I_ApplicationParameter {
public:
	lbApplicationParameters();
	virtual ~lbApplicationParameters();
	
	bool		LB_STDCALL selectParameter(long _id);

	char*		LB_STDCALL getParameter(const char* name, long application_id);
	
	int			LB_STDCALL getParameterCount();
	bool		LB_STDCALL hasMoreParameters();
	void		LB_STDCALL setNextParameter();
	void		LB_STDCALL finishParameterIteration();

	long		LB_STDCALL getParameterID();
	char*		LB_STDCALL getParameterName();
	char*		LB_STDCALL getParameterValue();

	long		LB_STDCALL addParameter(const char* name, const char* value, long anwendungs_id, long _id = -1);
	long		LB_STDCALL getApplicationID();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Container, Parameters)
	
	UAP(lb_I_String, currentParameterName)
	UAP(lb_I_String, currentParameterValue)
	
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentApplicationID)

	UAP(lb_I_Long, marked)
};


DECLARE_FUNCTOR(instanceOflbFormularParameters)
DECLARE_FUNCTOR(instanceOflbApplicationParameters)
