/*...sLicense:0:*/
/*
 DMF Distributed Multiplatform Framework (the initial goal of this library)
 This file is part of lbDMF.
 Copyright (C) 2015  Lothar Behrens (lothar.behrens@lollisoft.de)
 
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
 * $Revision: 1.1.2.1 $
 * $Name:  $
 * $Id: lbControlFactory.h,v 1.1.2.1 2015/07/12 10:05:50 lollisoft Exp $
 *
 * $Log: lbControlFactory.h,v $
 * Revision 1.1.2.1  2015/07/12 10:05:50  lollisoft
 * Added new property dialog and panel implementations. A first step toward workflow enabled dialogs.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_PropertyForm__
#define __LB_PropertyForm__

#include <iostream>


/** \brief First control factory trial.
 * This interface is an attempt to stop copy&paste code for creating controls used in a panel or form.
 * The base types are always the same and thus I start repeating code without a factory mechanism.
 */
class lb_I_ControlFactory : 
public lb_I_VisitableHelper,
public lb_I_EventHandler {
public:
	virtual void			LB_STDCALL setParent(lb_I_Window* parent) = 0;
	
	
	/** \brief Creates a specific control and returns a lb_I_Window instance.
	 * The instance represents the control within an encapsulation for my interfaces to
	 * hide internals. The window can return it's id for accessing purposes.
	 */
	virtual lb_I_Window*	LB_STDCALL createControl(const char* typeName, const char* name, const char* title) = 0;
};

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif


#endif // __LB_PropertyForm__


