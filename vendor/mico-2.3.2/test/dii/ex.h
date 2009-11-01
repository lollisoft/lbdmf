/*
 *  MICO --- a CORBA 2.0 implementation
 *  Copyright (C) 1997 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__EX_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __EX_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#include <mico/template_impl.h>
#include <mico/throw.h>
#endif

// Generate forward declarations for this scope
class SomeIface;
typedef SomeIface *SomeIface_ptr;
typedef SomeIface_ptr SomeIfaceRef;
typedef ObjVar<SomeIface> SomeIface_var;


struct SomeExcept : public CORBA::UserException {
  SomeExcept() {};
  SomeExcept( const SomeExcept& s )
  {
    msg = s.msg;
  };
  SomeExcept& operator=( const SomeExcept& s )
  {
    msg = s.msg;
    return *this;
  };
  CORBA::String_var msg;

  void _throwit () const;
  const char *_repoid () const;
  void _encode (CORBA::DataEncoder &) const;
  CORBA::Exception *_clone () const;

  static SomeExcept *_narrow (CORBA::Exception *ex);

#ifdef HAVE_STD_EH
  SomeExcept *operator->() { return this; }
  const SomeExcept *operator->() const { return this; }
  SomeExcept& operator*() { return *this; }
  const SomeExcept& operator*() const { return *this; }
#endif
};

#ifdef HAVE_STD_EH
typedef SomeExcept SomeExcept_catch;
#else
typedef ExceptVar<SomeExcept> SomeExcept_var;
typedef SomeExcept_var SomeExcept_catch;
#endif

extern CORBA::TypeCode_ptr _tc_SomeExcept;


// Common definitions for interface SomeIface
class SomeIface : virtual public CORBA::Object
{
  public:
    static SomeIface_ptr _duplicate( SomeIface_ptr obj );
    static SomeIface_ptr _narrow( CORBA::Object_ptr obj );
    static SomeIface_ptr _nil();

    static bool _narrow_helper( CORBA::Object_ptr obj );

    virtual void f() = 0;
  protected:
    //SomeIface();
    //virtual ~SomeIface();
  private:
    //SomeIface( const SomeIface& );
    //void operator=( const SomeIface& );
};

extern CORBA::TypeCode_ptr _tc_SomeIface;

// Stub for interface SomeIface
class SomeIface_stub : virtual public SomeIface
{
  public:
    void f();
  //protected:
    //SomeIface();
    //virtual ~SomeIface();
  private:
    //SomeIface( const SomeIface& );
    //void operator=( const SomeIface& );
};

class SomeIface_skel :
  virtual public MethodDispatcher,
  virtual public SomeIface
{
  public:
    SomeIface_skel();
    SomeIface_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::ServerRequest_ptr _req, CORBA::Environment &_env );
};

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

void operator<<=( CORBA::Any &a, const ::SomeExcept &s );

CORBA::Boolean operator>>=( const CORBA::Any &a, ::SomeExcept &s );

void operator<<=( CORBA::Any &a, const SomeIface_ptr obj );
CORBA::Boolean operator>>=( const CORBA::Any &a, SomeIface_ptr &obj );

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)


#endif
