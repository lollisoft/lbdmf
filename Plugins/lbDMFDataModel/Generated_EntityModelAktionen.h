
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

/** \brief class Aktionen.
 * Documentation for Aktionen
 */
class AktionenModel : public lb_I_Aktionen {
public:
	AktionenModel();
	virtual ~AktionenModel();

	long		LB_STDCALL addAktionen(const char* _target, const char* _source, const char* _name, long _typ,  long _AktionenID = -1);

	bool		LB_STDCALL selectAktionen(long _id);
	int			LB_STDCALL getAktionenCount();
	bool		LB_STDCALL hasMoreAktionen();
	void		LB_STDCALL setNextAktionen();
	void		LB_STDCALL finishAktionenIteration();


	char*		LB_STDCALL get_target();
	char*		LB_STDCALL get_source();
	char*		LB_STDCALL get_name();
	long		LB_STDCALL get_typ();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	UAP(lb_I_Container, objectExtensions)
	

	UAP(lb_I_Container, Aktionen)
	

	UAP(lb_I_String, currenttarget)
			
	UAP(lb_I_String, currentsource)
			
	UAP(lb_I_String, currentname)
			
	UAP(lb_I_Long, currenttyp)
	

	
	UAP(lb_I_Long, currentAktionenID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbAktionenModel)
