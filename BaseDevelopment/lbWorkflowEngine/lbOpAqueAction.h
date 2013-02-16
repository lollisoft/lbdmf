/*...sLicense:0:*/
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
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: lbOpAqueAction.h,v 1.2 2013/02/16 10:36:26 lollisoft Exp $
 *
 * $Log: lbOpAqueAction.h,v $
 * Revision 1.2  2013/02/16 10:36:26  lollisoft
 * Merged Release_1_0_4_stable_rc1_branch but doesn't yet compile.
 * Several files were conflicting and resolved in this checkin.
 *
 * Revision 1.1.2.1  2012/05/12 04:40:17  lollisoft
 * Moved action implementation out of DatabaseForm plugin and replaced wx related code with my own.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_OpAqueAction__
#define __LB_OpAqueAction__

/*...sclass lbDesicionAction:0:*/
class lbOpAqueOperation : public lb_I_DelegatedAction
	{
	public:
		lbOpAqueOperation();
		virtual ~lbOpAqueOperation();

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

DECLARE_FUNCTOR(instanceOflbOpAqueOperation)

#ifdef __cplusplus
}
#endif


#endif // __LB_DatabaseForm__


