/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

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

/* Implementation class for fixed database formular header file
 * Application: lbDMFManager
 * Formular: Formulare
 */
 
// Generated class for FormularID = 6
class Formulare : public wxSFDesignerBase {
public:
	Formulare();
	virtual ~Formulare();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL init();

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);
	
	lbErrCodes LB_STDCALL lbSetFormularFieldMode(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbSetFormularFieldConnectMode(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbMouseDown(lb_I_Unknown* uk);	

	lbErrCodes LB_STDCALL lbMouseUp(lb_I_Unknown* uk);
};
