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

class lbColumnTypes : public lb_I_Column_Types {
public:
	lbColumnTypes();
	virtual ~lbColumnTypes();

	long		LB_STDCALL addType(const char* tablename, const char* name, const char* specialcolumn, const char* controltype, bool readonly);
	bool		LB_STDCALL selectType(const char* tablename, const char* name);
	int			LB_STDCALL getTypeCount();
	bool		LB_STDCALL hasMoreTypes();
	void		LB_STDCALL setNextType();
	void		LB_STDCALL finishTypeIteration();

	char*		LB_STDCALL getTableName();
	char*		LB_STDCALL getName();
	char*		LB_STDCALL getSpecialColumn();
	char*		LB_STDCALL getControlType();
	bool		LB_STDCALL getReadonly();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Container, ColumnTypes)

	UAP(lb_I_String, currentTableName)
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentSpecialColumn)
	UAP(lb_I_String, currentControlType)
	UAP(lb_I_Long, currentReadonly)

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

class lbActionParameters : public lb_I_Action_Parameters {
public:
	lbActionParameters();
	virtual ~lbActionParameters();

	long		LB_STDCALL addActionParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id = -1);
	bool		LB_STDCALL selectActionParameter(long _id);
	int			LB_STDCALL getActionParametersCount();
	bool		LB_STDCALL hasMoreActionParameters();
	void		LB_STDCALL setNextActionParameter();
	void		LB_STDCALL finishActionParameterIteration();

	long		LB_STDCALL getActionParameterID();
	long		LB_STDCALL getActionParameterActionID();

	char*		LB_STDCALL getActionParameterDescription();
	char*		LB_STDCALL getActionParameterName();
	char*		LB_STDCALL getActionParameterValue();
	char*		LB_STDCALL getActionParameterInterface();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Container, Parameters)

	UAP(lb_I_String, currentParameterDescription)
	UAP(lb_I_String, currentParameterName)
	UAP(lb_I_String, currentParameterInterface)
	UAP(lb_I_String, currentParameterValue)

	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentActionID)

	UAP(lb_I_Long, marked)
};
/*...e*/

/*...sclass lb_I_Action_Types:0:*/
class lbActionStepParameters : public lb_I_ActionStep_Parameters {
public:
	lbActionStepParameters();
	virtual ~lbActionStepParameters();

	long		LB_STDCALL addActionStepParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id = -1);
	bool		LB_STDCALL selectActionStepParameter(long _id);
	int			LB_STDCALL getActionStepParametersCount();
	bool		LB_STDCALL hasMoreActionStepParameters();
	void		LB_STDCALL setNextActionStepParameter();
	void		LB_STDCALL finishActionStepParameterIteration();

	long		LB_STDCALL getActionStepParameterID();
	long		LB_STDCALL getActionStepParameterActionID();

	char*		LB_STDCALL getActionStepParameterDescription();
	char*		LB_STDCALL getActionStepParameterName();
	char*		LB_STDCALL getActionStepParameterValue();
	char*		LB_STDCALL getActionStepParameterInterface();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Container, Parameters)

	UAP(lb_I_String, currentParameterDescription)
	UAP(lb_I_String, currentParameterName)
	UAP(lb_I_String, currentParameterInterface)
	UAP(lb_I_String, currentParameterValue)

	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentActionID)

	UAP(lb_I_Long, marked)
};


DECLARE_FUNCTOR(instanceOflbFormularParameters)
DECLARE_FUNCTOR(instanceOflbApplicationParameters)
