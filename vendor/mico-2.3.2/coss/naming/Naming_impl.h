// -*- c++ -*-
/*
 *  Implementation of COSS Naming Service for MICO
 *  Copyright (C) 1997 Kai-Uwe Sattler
 *  Interoperable Naming Service extension by Frank Pilhofer
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

#ifndef Naming_impl_h_
#define Naming_impl_h_

#include <mico/CosNaming.h>
#include <mico/template_impl.h>

struct NmCtxBinding {
  CosNaming::BindingType btype;
  CORBA::Object_ptr obj;
};

class NamingContext_impl :
  virtual public POA_CosNaming::NamingContext,
  virtual public PortableServer::RefCountServantBase
{
private:
  struct str_less : binary_function<CosNaming::NameComponent,
		    CosNaming::NameComponent, bool>
  {
    bool operator() (const CosNaming::NameComponent& s1, 
		     const CosNaming::NameComponent& s2) const {
      int i = strcmp (s1.id.in(), s2.id.in());
      return i ? (i < 0) : (strcmp (s1.kind.in(), s2.kind.in()) < 0);
    }
  };

  typedef map<CosNaming::NameComponent, NmCtxBinding,
      str_less> BindingTable;
  BindingTable table;

protected:
  void _do_bind (const CosNaming::Name& n, CORBA::Object_ptr obj,
		 CosNaming::BindingType btype, CORBA::Boolean rebind);

public:
  NamingContext_impl (CORBA::ORB_ptr, PortableServer::POA_ptr, const char *);
  NamingContext_impl ();
  ~NamingContext_impl ();

  void bind (const CosNaming::Name& n, CORBA::Object_ptr obj);
  void rebind (const CosNaming::Name& n, CORBA::Object_ptr obj);
  void bind_context (const CosNaming::Name& n, 
		     CosNaming::NamingContext_ptr nc);
  void rebind_context (const CosNaming::Name& n, 
		       CosNaming::NamingContext_ptr nc);
  CORBA::Object_ptr resolve (const CosNaming::Name& n);
  void unbind (const CosNaming::Name& n);
  CosNaming::NamingContext_ptr new_context ();
  CosNaming::NamingContext_ptr bind_new_context (const CosNaming::Name& n);
  void destroy ();
  void list (CORBA::ULong how_many, CosNaming::BindingList*& bl, 
	     CosNaming::BindingIterator_ptr& bi);

  void save (const char *);
  void restore (const char *);

  typedef map<PortableServer::Servant,
    NamingContext_impl *,
    less<PortableServer::Servant> > ServantMap;
  static ServantMap svmap;

private:
  static string impl_name;
  static CORBA::ORB_ptr useorb;
  static PortableServer::POA_ptr usepoa;
  static NamingContext_impl * root;
};

class BindingIterator_impl :
  virtual public POA_CosNaming::BindingIterator,
  virtual public PortableServer::RefCountServantBase
{
private:
  CORBA::ULong idx;
  CosNaming::BindingList blist;
  CORBA::ORB_var useorb;

public:
  BindingIterator_impl (CORBA::ORB_ptr, const CosNaming::BindingList& bl);

  CORBA::Boolean next_one (CosNaming::Binding*& b);
  CORBA::Boolean next_n (CORBA::ULong how_many, CosNaming::BindingList*& bl);
  void destroy ();
};

class NamingContextExt_impl :
  virtual public NamingContext_impl,
  virtual public POA_CosNaming::NamingContextExt
{
public:
  NamingContextExt_impl (CORBA::ORB_ptr, PortableServer::POA_ptr,
			 const char *);

private:
  string StringifyEscape (const char *);
  string StringifyComponent (const CosNaming::NameComponent &);

public:
  char * to_string (const CosNaming::Name & n);
  CosNaming::Name * to_name (const char * sn);
  char * to_url (const char * addr, const char * sn);
  CORBA::Object_ptr resolve_str (const char * sn);
};

#endif
