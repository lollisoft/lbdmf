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

/** \brief Storage implementation for XML.
 *
 * This class is used to export the internal representation of an application model. Thus, with this
 * file, you will be able to do what ever you want.
 *
 * Currently there is only implemented the save function.
 */
class lbDynamicAppXMLStorage :
    public lb_I_StandaloneStreamable {
public:
	lbDynamicAppXMLStorage();
	virtual ~lbDynamicAppXMLStorage();

	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setOperator(lb_I_Unknown* _op) { op = _op; op++; return ERR_NONE; }
	lbErrCodes	LB_STDCALL load(lb_I_InputStream* iStream);
	lbErrCodes	LB_STDCALL save(lb_I_OutputStream* oStream);

	lbErrCodes	LB_STDCALL load(lb_I_Database* iDB);
	lbErrCodes	LB_STDCALL save(lb_I_Database* oDB);
	
	UAP(lb_I_Unknown, op)
};

/** \brief Storage implementation for internal fileformat.
 */
class lbDynamicAppInternalStorage :
    public lb_I_StandaloneStreamable {
public:
	lbDynamicAppInternalStorage();
	virtual ~lbDynamicAppInternalStorage();

	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setOperator(lb_I_Unknown* _op) { op = _op; op++; return ERR_NONE; }
	lbErrCodes	LB_STDCALL load(lb_I_InputStream* iStream);
	lbErrCodes	LB_STDCALL save(lb_I_OutputStream* oStream);

	lbErrCodes	LB_STDCALL load(lb_I_Database* iDB);
	lbErrCodes	LB_STDCALL save(lb_I_Database* oDB);
	
	UAP(lb_I_Unknown, op)
};

/** \brief Storage implementation for importing an application model from UML (BoUML via XMI).
 */
class lbDynamicAppBoUMLImportExport :
    public lb_I_StandaloneStreamable {
public:
	lbDynamicAppBoUMLImportExport();
	virtual ~lbDynamicAppBoUMLImportExport();

	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setOperator(lb_I_Unknown* _op) { op = _op; op++; return ERR_NONE; }
	lbErrCodes	LB_STDCALL load(lb_I_InputStream* iStream);
	lbErrCodes	LB_STDCALL save(lb_I_OutputStream* oStream);

	lbErrCodes	LB_STDCALL load(lb_I_Database* iDB);
	lbErrCodes	LB_STDCALL save(lb_I_Database* oDB);
	
	UAP(lb_I_Unknown, op)
};

DECLARE_FUNCTOR(instanceOflbDynamicAppBoUMLImportExport)
DECLARE_FUNCTOR(instanceOflbDynamicAppInternalStorage)
DECLARE_FUNCTOR(instanceOflbDynamicAppXMLStorage)

