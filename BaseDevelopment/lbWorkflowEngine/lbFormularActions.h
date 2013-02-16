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
 * $Id: lbFormularActions.h,v 1.2 2013/02/16 10:36:25 lollisoft Exp $
 *
 * $Log: lbFormularActions.h,v $
 * Revision 1.2  2013/02/16 10:36:25  lollisoft
 * Merged Release_1_0_4_stable_rc1_branch but doesn't yet compile.
 * Several files were conflicting and resolved in this checkin.
 *
 * Revision 1.1.2.2  2012/05/12 21:20:09  lollisoft
 * Code cleanup and made formularactions loadable at runtime.
 *
 * Revision 1.1.2.1  2012/05/12 04:40:17  lollisoft
 * Moved action implementation out of DatabaseForm plugin and replaced wx related code with my own.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_FormularActions__
#define __LB_FormularActions__

#include <iostream>

/*...sclass FormularActions:0:*/
/** \brief Management of formular actions.
 *
 * This class is used to concentrate the code for formular actions.
 *
 * These includes opening detail or master forms, performing validations,
 * calculating combined values and so on.
 *
 * All  these actions should be configurable and activated at initializion
 * time.
 *
 * Upon the fact, that this class knows about open detail/master forms, it
 * should be also responsible to update the detail/master views when the user
 * changes the peer.
 */
class lbFormularActions : public lb_I_FormularAction_Manager {

public:

	lbFormularActions();

	virtual ~lbFormularActions();

	DECLARE_LB_UNKNOWN()

	/** \brief Add a mapping from event name to it's action ID.
	 */
	void addRegisteredAction(long ActionID, const char* eventName);

	/** \brief ID of action target.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when
	 */
	char* getActionTargetID(const char* reversed_event);

	/** \brief ID of action target as long.
	 *
	 * Get the ID of the action target based on the 'what' data field.
	 * This is needed, when
	 */
	long getActionTargetIDLong(const char* reversed_event);

	/** \brief Source field of the action. */
	char* getActionSourceDataField(const char* reversed_event);

	/** \brief ID for the action. */
	long getActionID(const char* reversed_event);

	/** \brief Get the action instance.
	 *
	 * This function creates the requested action instance, stores it for caching and
	 * then returns a reference to it.
	 */
	lb_I_Action* getAction(long id);

	/** \brief Validate the form.
	 *
	 * Use this function to check, if the data has a correct state.
	 */
	bool validate() { return true; }

	/** \brief Update master/detail views and related views.
	 *
	 * Use this function to update related views. This may master/detail views and
	 * possibly views, containing data fields related to any open views.
	 */
	bool update() { return true; }

protected:
	UAP(lb_I_Container, eventmapping)
	UAP(lb_I_Container, actions)
	UAP(lb_I_Actions, appActions)
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOflbFormularActions)

#ifdef __cplusplus
}
#endif


#endif // __LB_FormularActions__


