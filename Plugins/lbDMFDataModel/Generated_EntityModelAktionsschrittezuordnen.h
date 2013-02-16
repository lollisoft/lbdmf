
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

/** \brief class Aktionsschrittezuordnen.
 * Documentation for Aktionsschrittezuordnen
 */
class AktionsschrittezuordnenModel : public lb_I_Aktionsschrittezuordnen {
public:
	AktionsschrittezuordnenModel();
	virtual ~AktionsschrittezuordnenModel();

	long		LB_STDCALL addAktionsschrittezuordnen(const char* _bezeichnung, const char* _what, long _a_order_nr, long _type, long _actionid,  long _AktionsschrittezuordnenID = -1);

	bool		LB_STDCALL selectAktionsschrittezuordnen(long _id);
	int			LB_STDCALL getAktionsschrittezuordnenCount();
	bool		LB_STDCALL hasMoreAktionsschrittezuordnen();
	void		LB_STDCALL setNextAktionsschrittezuordnen();
	void		LB_STDCALL finishAktionsschrittezuordnenIteration();


	char*		LB_STDCALL get_bezeichnung();
	char*		LB_STDCALL get_what();
	long			LB_STDCALL get_a_order_nr();
	long		LB_STDCALL get_type();
	
	long		LB_STDCALL get_actionid();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	UAP(lb_I_Container, objectExtensions)
	

	UAP(lb_I_Container, Aktionsschrittezuordnen)
	

	UAP(lb_I_String, currentbezeichnung)
			
	UAP(lb_I_String, currentwhat)
			
	UAP(lb_I_Long, currenta_order_nr)
			
	UAP(lb_I_Long, currenttype)
	
	UAP(lb_I_Long, currentactionid)
	

	
	UAP(lb_I_Long, currentAktionsschrittezuordnenID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbAktionsschrittezuordnenModel)
