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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/

/** \brief XML transformer.
 *
 * This class is used to transform any XML files.
 */
class lbDMFXslt :
    public lb_I_DelegatedAction {
public:
	long LB_STDCALL execute(lb_I_Parameter* params);	
	void LB_STDCALL setActionID(long id);
	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	void LB_STDCALL setDatabase(lb_I_Database* _db);
	bool LB_STDCALL fileFromAction(lb_I_InputStream* stream);
	
	DECLARE_LB_UNKNOWN()
	
public:
	lbDMFXslt();
	virtual ~lbDMFXslt();

protected:
	long myActionID;
	UAP(lb_I_Database, db)
	UAP(lb_I_String, app)	
	UAP(lb_I_Action_Step_Transitions, transitions)
};

DECLARE_FUNCTOR(instanceOflbDMFXslt)

