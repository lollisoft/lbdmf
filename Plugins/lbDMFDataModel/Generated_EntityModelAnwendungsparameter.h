
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

/** \brief class Anwendungsparameter.
 * Documentation for Anwendungsparameter
 */
class AnwendungsparameterModel : public lb_I_Anwendungsparameter {
public:
	AnwendungsparameterModel();
	virtual ~AnwendungsparameterModel();

	long		LB_STDCALL addAnwendungsparameter(const char* _parametervalue, const char* _parametername, long _anwendungid,  long _AnwendungsparameterID = -1);

	bool		LB_STDCALL selectAnwendungsparameter(long _id);
	int			LB_STDCALL getAnwendungsparameterCount();
	bool		LB_STDCALL hasMoreAnwendungsparameter();
	void		LB_STDCALL setNextAnwendungsparameter();
	void		LB_STDCALL finishAnwendungsparameterIteration();


	char*		LB_STDCALL get_parametervalue();
	char*		LB_STDCALL get_parametername();
	long		LB_STDCALL get_anwendungid();
	

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	UAP(lb_I_Container, objectExtensions)
	

	UAP(lb_I_Container, Anwendungsparameter)
	

	UAP(lb_I_String, currentparametervalue)
			
	UAP(lb_I_String, currentparametername)
			
	UAP(lb_I_Long, currentanwendungid)
	

	
	UAP(lb_I_Long, currentAnwendungsparameterID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbAnwendungsparameterModel)
