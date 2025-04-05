// -*- c++ -*-
/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1998 Frank Pilhofer
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */


#ifndef __poamediator_h__
#define __poamediator_h__

#include <iostream.h>
#include <CORBA.h>
#include <mico/impl.h>

class POAMediatorImpl : virtual public CORBA::ObjectAdapter,
			virtual public CORBA::POAMediator_skel,
			virtual public CORBA::ORBCallback,
			virtual public MICO::ProcessCallback
{
public:
  // must be public for Sun CC
  enum ServerState {
    Inactive,
    Started,
    Active,
    Failed
  };

private:
  struct SvInf {
    SvInf();
    ServerState pstate;
    CORBA::IOR ior;
    MICO::UnixProcess * proc;
    CORBA::Long failed;
  };

  typedef map<string, SvInf, less<string> > MapSvInf;
  typedef map<MsgId, MsgId, less<MsgId> > MapIdId;

  MapSvInf svmap;
  MapIdId requests;
  CORBA::ORB_var orb;
  string myior;
  CORBA::Boolean forward;

  CORBA::ImplRepository_var imr;
  MICO::RequestQueue invqueue;

public:
  POAMediatorImpl (CORBA::ORB_ptr, CORBA::Boolean forward = FALSE);
  ~POAMediatorImpl ();

  /*
   * POAMediator stuff
   */

  char * create_impl (const char *, const char *);
  void activate_impl (const char *);
  void deactivate_impl (const char *);

  CORBA::Boolean force_activation (CORBA::ImplementationDef_ptr);

  /*
   * Helper
   */

  CORBA::Boolean create_server (const char *);

  /*
   * ObjectAdapter interface
   */

  const char *get_oaid () const;
  CORBA::Boolean has_object (CORBA::Object_ptr);
  CORBA::Boolean is_local () const;
    
  CORBA::Boolean invoke (MsgId, CORBA::Object_ptr,
			 CORBA::ORBRequest *,
			 CORBA::Principal_ptr,
			 CORBA::Boolean response_exp = TRUE);
  CORBA::Boolean bind (MsgId, const char *repoid,
		       const CORBA::ORB::ObjectTag &,
		       CORBA::Address *addr);
  CORBA::Boolean locate (MsgId, CORBA::Object_ptr);
  CORBA::Object_ptr skeleton (CORBA::Object_ptr);
  void cancel (MsgId);
  void shutdown (CORBA::Boolean wait_for_completion);
    
  void answer_invoke (CORBA::ULong, CORBA::Object_ptr,
		      CORBA::ORBRequest *,
		      CORBA::InvokeStatus);

  /*
   * Callbacks (ORB, Process)
   */

  void callback (CORBA::ORB_ptr, MsgId, CORBA::ORBCallback::Event);
  void callback (MICO::Process *, MICO::ProcessCallback::Event);

  /*
   * Shutdown
   */

  void shutdown_server ();
};

#endif
