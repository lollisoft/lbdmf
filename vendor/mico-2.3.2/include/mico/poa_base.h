// -*- c++ -*-
/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1998 Frank Pilhofer
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#if !defined(__POA_BASE_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __POA_BASE_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL PortableServer {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_PortableServer)

MICO_EXPORT_VAR_DECL POA * _the_root_poa;
MICO_EXPORT_VAR_DECL Current * _the_poa_current;

class ServantBase
{
public:
  virtual ~ServantBase ();

  virtual POA_ptr _default_POA();
  virtual CORBA::Boolean _is_a (const char *);
  virtual CORBA::Boolean _non_existent ();
  virtual CORBA::InterfaceDef_ptr _get_interface () = 0;

  // begin-mico-extension (moved up from DynamicImplementation)
  CORBA::InterfaceDef_ptr _get_interface (const char *repoid);
  CORBA::Object_ptr _this ();
  virtual CORBA::RepositoryId _primary_interface (const ObjectId &,
						  POA_ptr) = 0;
  // end-mico-extension

  virtual void _add_ref ();
  virtual void _remove_ref ();
  
  // begin-mico-extension
  virtual void _check ();
  virtual void * _narrow_helper (const char *);
  virtual CORBA::Object_ptr _make_stub (POA_ptr, CORBA::Object_ptr);
  virtual CORBA::ServerRequestBase_ptr make_request (CORBA::ORBRequest *,
						     CORBA::Object_ptr,
						     CORBA::ULong,
						     CORBA::ObjectAdapter *,
						     CORBA::Principal_ptr) = 0;
  virtual void doinvoke (CORBA::ServerRequestBase_ptr) = 0;

  POA_ptr _activated_in ();
  void _activated_in (POA_ptr);
  // end-mico-extension

protected:
  ServantBase ();
  ServantBase (const ServantBase &);
  ServantBase & operator= (const ServantBase &);
  POA_ptr _my_poa;
};

class RefCountServantBase : virtual public ServantBase
{
public:
  virtual ~RefCountServantBase ();

  virtual void _add_ref ();
  virtual void _remove_ref ();

  // begin-mico-extension
  void _check ();
  // end-mico-extension

protected:
  RefCountServantBase ();
  RefCountServantBase (const RefCountServantBase &);
  RefCountServantBase & operator= (const RefCountServantBase &);

private:
  CORBA::ULong _magic;
  CORBA::ULong _ref_count;
};

class ValueRefCountBase :
  virtual public CORBA::DefaultValueRefCountBase,
  virtual public ServantBase
{
public:
  ValueRefCountBase ();
  virtual ~ValueRefCountBase ();

  virtual void _add_ref ();
  virtual void _remove_ref ();
  virtual CORBA::ULong _refcount_value ();

protected:
  ValueRefCountBase (const ValueRefCountBase &);

private:
  void operator= (const ValueRefCountBase &);
};

class DynamicImplementation : virtual public ServantBase
{
public:
  virtual ~DynamicImplementation ();

  CORBA::Object_ptr _this ();
  virtual void invoke (CORBA::ServerRequest_ptr) = 0;
  virtual CORBA::RepositoryId _primary_interface (const ObjectId &,
						  POA_ptr) = 0;

  /*
   * Default implementation uses _primary_interface
   */

  CORBA::Boolean _is_a (const char *);
  CORBA::InterfaceDef_ptr _get_interface ();

  // begin-mico-extension
  CORBA::ServerRequestBase_ptr make_request (CORBA::ORBRequest *,
					     CORBA::Object_ptr,
					     CORBA::ULong,
					     CORBA::ObjectAdapter *,
					     CORBA::Principal_ptr);
  void doinvoke (CORBA::ServerRequestBase_ptr);
  // end-mico-extension
};

// begin-mico-extension
class StaticImplementation : virtual public ServantBase
{
public:
  virtual ~StaticImplementation ();
  virtual void invoke (CORBA::StaticServerRequest_ptr) = 0;
  CORBA::ServerRequestBase_ptr make_request (CORBA::ORBRequest *,
					     CORBA::Object_ptr,
					     CORBA::ULong,
					     CORBA::ObjectAdapter *,
					     CORBA::Principal_ptr);
  virtual void doinvoke (CORBA::ServerRequestBase_ptr);
};
// end-mico-extension

#if 0
class ServantBase_var
{
public:
  ServantBase_var ();
  ServantBase_var (ServantBase *);
  ServantBase_var (const ServantBase_var &);
  ~ServantBase_var ();

  ServantBase_var & operator= (ServantBase *);
  ServantBase_var & operator= (const ServantBase_var &);

  ServantBase * operator->() const;
  ServantBase * in () const;
  ServantBase *& inout ();
  ServantBase *& out ();
  ServantBase * _retn ();

private:
  ServantBase * _ptr;
};
#else
typedef ValueVar<ServantBase> ServantBase_var;
#endif

// begin-mico-extension
class StubBase : virtual public CORBA::Object {
public:
  StubBase (POA_ptr);
  virtual ~StubBase ();

  ServantBase * _preinvoke ();
  void _postinvoke ();

protected:
  StubBase ();

private:
  POA_ptr _colocated_poa;
};
// end-mico-extension

MICO_EXPORT_FCT_DECL char *         ObjectId_to_string  (const ObjectId &);
MICO_EXPORT_FCT_DECL CORBA::WChar * ObjectId_to_wstring (const ObjectId &);
MICO_EXPORT_FCT_DECL ObjectId *     string_to_ObjectId  (const char *);
MICO_EXPORT_FCT_DECL ObjectId *     wstring_to_ObjectId (const CORBA::WChar *);

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_PortableServer)

#ifndef MICO_NO_TOPLEVEL_MODULES
};
#endif

/*
 * Note: This relies on <poa.h> being included inbetween.
 */

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

/*
 * Common Base class for Ties
 */

template<class T>
class POA_Tie_Base
{
protected:
  T * ptr;
  PortableServer::POA_ptr poa;
  CORBA::Boolean rel;

  POA_Tie_Base () {}

public:
  POA_Tie_Base (T *t, PortableServer::POA_ptr _poa, CORBA::Boolean _rel)
  {
    ptr = t;
    poa = PortableServer::POA::_duplicate (_poa);
    rel = _rel;
  }

  virtual ~POA_Tie_Base ()
  {
    if (rel) delete ptr;
    CORBA::release (poa);
  }

  T * _tied_object ()
  {
    return ptr;
  }
  
  void _tied_object (T &t)
  {
    if (rel) delete ptr;
    ptr = &t;
    rel = 0;
  }

  void _tied_object (T *t, CORBA::Boolean r = 1)
  {
    if (rel) delete ptr;
    ptr = t;
    rel = r;
  }

  CORBA::Boolean _is_owner ()
  {
    return rel;
  }

  void _is_owner (CORBA::Boolean _rel)
  {
    rel = _rel;
  }
};

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

#endif
