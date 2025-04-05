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

class lbFormularsModel : public lb_I_Formulars {
public:
	lbFormularsModel();
	virtual ~lbFormularsModel();

	long		LB_STDCALL addFormular(const char* name, const char* toolbarimage, const char* menuname, const char* eventname, const char* menuhilfe, long anwendung_id, long typ, long formular_id = -1);
	bool		LB_STDCALL selectFormular(long _id);
	int			LB_STDCALL getFormularCount();
	bool		LB_STDCALL hasMoreFormulars();
	void		LB_STDCALL setNextFormular();
	void		LB_STDCALL finishFormularIteration();
	
	char*		LB_STDCALL getName();
	char*		LB_STDCALL getToolbarImage();
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
	UAP(lb_I_String, currentToolbarImage)
	UAP(lb_I_String, currentEventName)
	UAP(lb_I_String, currentMenuHilfe)
	
	UAP(lb_I_Long, currentApplicationID)
	UAP(lb_I_Long, currentTyp)
	UAP(lb_I_Long, currentFormularID)

	UAP(lb_I_Long, marked)
};


class lbFormularFieldsModel : public lb_I_Formular_Fields {
public:
	lbFormularFieldsModel();
	virtual ~lbFormularFieldsModel();

	long		LB_STDCALL addField(const char* name, const char* tablename, const char* dbtype, bool isFK, const char* FKName, const char* FKTable, long formular_id, long fieldid = -1);
	bool		LB_STDCALL selectField(long _id);
	int			LB_STDCALL getFieldCount();
	bool		LB_STDCALL hasMoreFields();
	void		LB_STDCALL setNextField();
	void		LB_STDCALL finishFieldsIteration();
	
	char*		LB_STDCALL getName();
	char*		LB_STDCALL getTableName();
	char*		LB_STDCALL getDBType();
	char*		LB_STDCALL getFKName();
	char*		LB_STDCALL getFKTable();
	long		LB_STDCALL getFormularID();
	long		LB_STDCALL getID();
	bool		LB_STDCALL isFK();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Container, FormularFields)
	
	UAP(lb_I_String, currentName)
	UAP(lb_I_String, currentTableName)
	UAP(lb_I_String, currentDBType)
	UAP(lb_I_Long, currentisFK)
	UAP(lb_I_String, currentFKName)
	UAP(lb_I_String, currentFKTable)
	
	UAP(lb_I_Long, currentID)
	UAP(lb_I_Long, currentFormularID)

	UAP(lb_I_Long, marked)
	
	long uniqueID;
};


DECLARE_FUNCTOR(instanceOflbFormularFieldsModel)
DECLARE_FUNCTOR(instanceOflbFormularsModel)
