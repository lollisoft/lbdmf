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
            Odenwaldstr. 14

            63150 Heusenstamm (germany)
*/
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1.2.6 $
 * $Name:  $
 * $Id: lbSqlQueryAction.h,v 1.1.2.6 2025/04/12 10:54:06 lothar Exp $
 *
 * $Log: lbSqlQueryAction.h,v $
 * Revision 1.1.2.6  2025/04/12 10:54:06  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.1.2.5  2025/04/12 10:09:26  lothar
 * Changed my address and copyright start and ending year to reflect
 * my upcoming new home and timeframe of development.
 *
 * Revision 1.1.2.4  2025/04/05 16:16:30  lothar
 * This file seems to clash with HEAD bransh when migrating to git.
 * So update it in the bransh to probably fix this. Why does the
 * migration fails here?
 *
 * Revision 1.1.2.3  2025/04/05 15:46:56  lothar
 * This file seems to clash with HEAD bransh when migrating to git.
 * So update it in the bransh to probably fix this. Why does the
 * migration fails here?
 *
 * Revision 1.1.2.2  2012/05/12 21:20:09  lollisoft
 * Code cleanup and made formularactions loadable at runtime.
 *
 * Revision 1.1.2.1  2012/05/12 04:40:17  lollisoft
 * Moved action implementation out of DatabaseForm plugin and replaced wx related code with my own.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_SqlQueryAction__
#define __LB_SqlQueryAction__

#include <iostream>

/*...sclass lbSQLQueryAction:0:*/
class lbSQLQueryAction : public lb_I_DelegatedAction
{
public:
	lbSQLQueryAction();
	virtual ~lbSQLQueryAction();

	void LB_STDCALL setActionID(long id);
	long LB_STDCALL execute(lb_I_Parameter* params);

	void LB_STDCALL setDatabase(lb_I_Database* _db);

	void LB_STDCALL setTransitions(lb_I_Action_Step_Transitions* myTransitions);
	void LB_STDCALL setParameter(lb_I_ActionStep_Parameters* myParams);

	DECLARE_LB_UNKNOWN()

protected:
	long myActionID;
	UAP(lb_I_Database, db)
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOflbSQLQueryAction)

#ifdef __cplusplus
}
#endif


#endif // __LB_SqlQueryAction__


