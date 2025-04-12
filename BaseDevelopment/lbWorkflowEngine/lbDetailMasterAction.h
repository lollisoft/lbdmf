/*...sLicense:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Odenwaldstra�e 14

            63150 Heusenstamm (germany)
*/
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1.2.3 $
 * $Name:  $
 * $Id: lbDetailMasterAction.h,v 1.1.2.3 2025/04/12 10:09:26 lothar Exp $
 *
 * $Log: lbDetailMasterAction.h,v $
 * Revision 1.1.2.3  2025/04/12 10:09:26  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.1.2.2  2025/04/05 16:16:30  lothar
 * This file seems to clash with HEAD bransh when migrating to git.
 * So update it in the bransh to probably fix this. Why does the
 * migration fails here?
 *
 * Revision 1.1.2.1  2012/05/12 04:40:17  lollisoft
 * Moved action implementation out of DatabaseForm plugin and replaced wx related code with my own.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_MasterDetailAction__
#define __LB_MasterDetailAction__

#include <iostream>

/*...sclass lbMasterFormAction:0:*/
class lbMasterFormAction : public lb_I_DelegatedAction
{
public:
	lbMasterFormAction();
	virtual ~lbMasterFormAction();

	void LB_STDCALL setActionID(long id);
	long LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);

	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	DECLARE_LB_UNKNOWN()

protected:

	bool LB_STDCALL openMasterForm(lb_I_String* formularname, lb_I_Parameter* params);

	long myActionID;
	UAP(lb_I_Database, db)
	UAP(lb_I_String, app)
	UAP(lb_I_String, detailForm)
	UAP(lb_I_String, SourceFieldName)
	UAP(lb_I_String, SourceFieldValue)
	UAP(lb_I_String, DBName)
	UAP(lb_I_String, DBUser)
	UAP(lb_I_String, DBPass)

	lb_I_DatabaseForm* masterForm;
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOflbMasterDetailAction)

#ifdef __cplusplus
}
#endif


#endif // __LB_MasterDetailAction__


