
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

/** \brief class Column_Types.
 * Documentation for Column_Types
 */
class Column_TypesModel : public lb_I_Column_Types {
public:
	Column_TypesModel();
	virtual ~Column_TypesModel();

	long		LB_STDCALL addColumn_Types(const char* _name, const char* _tablename, bool _ro, bool _specialcolumn, const char* _controltype,  long _Column_TypesID = -1);

	bool		LB_STDCALL selectColumn_Types(long _id);
	int			LB_STDCALL getColumn_TypesCount();
	bool		LB_STDCALL hasMoreColumn_Types();
	void		LB_STDCALL setNextColumn_Types();
	void		LB_STDCALL finishColumn_TypesIteration();


	char*		LB_STDCALL get_name();
	char*		LB_STDCALL get_tablename();
	bool		LB_STDCALL get_ro();
	bool		LB_STDCALL get_specialcolumn();
	char*		LB_STDCALL get_controltype();

	long		LB_STDCALL get_id();

	bool		LB_STDCALL ismarked();
	void		LB_STDCALL mark();
	void		LB_STDCALL unmark();

	void		LB_STDCALL deleteUnmarked();
	void		LB_STDCALL deleteMarked();

	DECLARE_LB_UNKNOWN()
	DECLARE_EXTENSIBLEOBJECT()

	UAP(lb_I_Container, objectExtensions)
	

	UAP(lb_I_Container, Column_Types)
	

	UAP(lb_I_String, currentname)
			
	UAP(lb_I_String, currenttablename)
			
	UAP(lb_I_Boolean, currentro)
			
	UAP(lb_I_Boolean, currentspecialcolumn)
			
	UAP(lb_I_String, currentcontroltype)
			

	
	UAP(lb_I_Long, currentColumn_TypesID)

	UAP(lb_I_Long, marked)
};

DECLARE_FUNCTOR(instanceOflbColumn_TypesModel)
