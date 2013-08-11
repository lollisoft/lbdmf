
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

/** \brief class Actions.
 * Documentation for Actions
 */
class ActionsModel : public lb_I_Actions {
public:
	ActionsModel();
	virtual ~ActionsModel();

	long		LB_STDCALL add(const char* _target, const char* _source, const char* _name, long _typ, long _anwendungenid,  long _ActionsID = -1);

	bool		LB_STDCALL selectById(long _id);
	int			LB_STDCALL Count();
	bool		LB_STDCALL hasMoreElements();
	void		LB_STDCALL setNextElement();
	void		LB_STDCALL finishIteration();


	char*		LB_STDCALL get_target();
	char*		LB_STDCALL get_source();
	char*		LB_STDCALL get_name();
	long		LB_STDCALL get_typ();
	
	long		LB_STDCALL get_anwendungenid();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	UAP(lb_I_Container, objectExtensions)
	

	UAP(lb_I_Container, Actions)
	

	UAP(lb_I_String, currenttarget)
			
	UAP(lb_I_String, currentsource)
			
	UAP(lb_I_String, currentname)
			
	UAP(lb_I_Long, currenttyp)
	
	UAP(lb_I_Long, currentanwendungenid)
	

	
	UAP(lb_I_Long, currentActionsID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbActionsModel)
