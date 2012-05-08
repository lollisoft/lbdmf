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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/

/** \brief XML transformer.
 *
 * This class is used to transform any XML files.
 */
class lbDMFSSP :
	public lb_I_SecurityProvider {
public:
	
	DECLARE_LB_UNKNOWN()
	
	bool			LB_STDCALL autologin(const char* user, const char* secret);
	lb_I_String*	LB_STDCALL getOrCreateSecret();
	bool			LB_STDCALL login(const char* user, const char* pass);
	bool			LB_STDCALL setCurrentApplicationId(long id);
	long 			LB_STDCALL getApplicationID();
	lb_I_Container* LB_STDCALL getApplications();
	lb_I_Unknown*	LB_STDCALL getApplicationModel();

	lb_I_String*	LB_STDCALL getApplicationModule();
	lb_I_String*	LB_STDCALL getApplicationFunctor();

	lbErrCodes 		LB_STDCALL save();
	lbErrCodes 		LB_STDCALL load();
	lbErrCodes		LB_STDCALL uninitialize();

public:
	lbDMFSSP();
	virtual ~lbDMFSSP();

protected:

	void 			LB_STDCALL setAllowedApplications(long userid);
	bool			LB_STDCALL isApplicationIDAllowed(long ApplicationID);


	/// \brief Applications stored in file or database.
	UAP(lb_I_Container, AllowedApplications)
	/// \brief Applications stored in file or database.
	UAP(lb_I_Applications, Applications)
	/// \brief Users stored in file or database.
	UAP(lb_I_UserAccounts, Users)
	/// \brief Users to Applications mapping stored in file or database.
	UAP(lb_I_User_Applications, User_Applications)
	
	bool _logged_in;
	bool _loading_object_data;
	bool _force_use_database;
	bool _loaded;
	
	long CurrentApplicationID;
	long CurrentUserID;
	
	UAP(lb_I_String, LogonApplication)
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonSecret)
	UAP(lb_I_MetaApplication, meta)
};

DECLARE_SINGLETON_FUNCTOR(instanceOflbDMFSSP)

