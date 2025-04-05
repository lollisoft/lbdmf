/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__ORB_EXCEPTS_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __ORB_EXCEPTS_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)


struct Bounds : public UserException {
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  Bounds();
  ~Bounds();
  Bounds( const Bounds& s );
  Bounds& operator=( const Bounds& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS


  #ifdef HAVE_STD_EH
  Bounds *operator->() { return this; }
  Bounds& operator*() { return *this; }
  operator Bounds*() { return this; }
  #endif // HAVE_STD_EH

  void _throwit() const;
  const char *_repoid() const;
  void _encode( CORBA::DataEncoder &en ) const;
  void _encode_any( CORBA::Any &a ) const;
  CORBA::Exception *_clone() const;
  static Bounds *EXCEPTION_DOWNCAST( CORBA::Exception *ex );
  static const Bounds *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );
};

#ifdef HAVE_STD_EH
typedef Bounds Bounds_catch;
#else
typedef ExceptVar<Bounds> Bounds_var;
typedef Bounds_var Bounds_out;
typedef Bounds_var Bounds_catch;
#endif // HAVE_STD_EH

struct WrongTransaction : public UserException {
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  WrongTransaction();
  ~WrongTransaction();
  WrongTransaction( const WrongTransaction& s );
  WrongTransaction& operator=( const WrongTransaction& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS


  #ifdef HAVE_STD_EH
  WrongTransaction *operator->() { return this; }
  WrongTransaction& operator*() { return *this; }
  operator WrongTransaction*() { return this; }
  #endif // HAVE_STD_EH

  void _throwit() const;
  const char *_repoid() const;
  void _encode( CORBA::DataEncoder &en ) const;
  void _encode_any( CORBA::Any &a ) const;
  CORBA::Exception *_clone() const;
  static WrongTransaction *EXCEPTION_DOWNCAST( CORBA::Exception *ex );
  static const WrongTransaction *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );
};

#ifdef HAVE_STD_EH
typedef WrongTransaction WrongTransaction_catch;
#else
typedef ExceptVar<WrongTransaction> WrongTransaction_var;
typedef WrongTransaction_var WrongTransaction_out;
typedef WrongTransaction_var WrongTransaction_catch;
#endif // HAVE_STD_EH

struct ORB_InconsistentTypeCode : public UserException {
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ORB_InconsistentTypeCode();
  ~ORB_InconsistentTypeCode();
  ORB_InconsistentTypeCode( const ORB_InconsistentTypeCode& s );
  ORB_InconsistentTypeCode& operator=( const ORB_InconsistentTypeCode& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS


  #ifdef HAVE_STD_EH
  ORB_InconsistentTypeCode *operator->() { return this; }
  ORB_InconsistentTypeCode& operator*() { return *this; }
  operator ORB_InconsistentTypeCode*() { return this; }
  #endif // HAVE_STD_EH

  void _throwit() const;
  const char *_repoid() const;
  void _encode( CORBA::DataEncoder &en ) const;
  void _encode_any( CORBA::Any &a ) const;
  CORBA::Exception *_clone() const;
  static ORB_InconsistentTypeCode *EXCEPTION_DOWNCAST( CORBA::Exception *ex );
  static const ORB_InconsistentTypeCode *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );
};

#ifdef HAVE_STD_EH
typedef ORB_InconsistentTypeCode ORB_InconsistentTypeCode_catch;
#else
typedef ExceptVar<ORB_InconsistentTypeCode> ORB_InconsistentTypeCode_var;
typedef ORB_InconsistentTypeCode_var ORB_InconsistentTypeCode_out;
typedef ORB_InconsistentTypeCode_var ORB_InconsistentTypeCode_catch;
#endif // HAVE_STD_EH

struct ORB_InvalidName : public UserException {
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ORB_InvalidName();
  ~ORB_InvalidName();
  ORB_InvalidName( const ORB_InvalidName& s );
  ORB_InvalidName& operator=( const ORB_InvalidName& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS


  #ifdef HAVE_STD_EH
  ORB_InvalidName *operator->() { return this; }
  ORB_InvalidName& operator*() { return *this; }
  operator ORB_InvalidName*() { return this; }
  #endif // HAVE_STD_EH

  void _throwit() const;
  const char *_repoid() const;
  void _encode( CORBA::DataEncoder &en ) const;
  void _encode_any( CORBA::Any &a ) const;
  CORBA::Exception *_clone() const;
  static ORB_InvalidName *EXCEPTION_DOWNCAST( CORBA::Exception *ex );
  static const ORB_InvalidName *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );
};

#ifdef HAVE_STD_EH
typedef ORB_InvalidName ORB_InvalidName_catch;
#else
typedef ExceptVar<ORB_InvalidName> ORB_InvalidName_var;
typedef ORB_InvalidName_var ORB_InvalidName_out;
typedef ORB_InvalidName_var ORB_InvalidName_catch;
#endif // HAVE_STD_EH

struct TypeCode_Bounds : public UserException {
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  TypeCode_Bounds();
  ~TypeCode_Bounds();
  TypeCode_Bounds( const TypeCode_Bounds& s );
  TypeCode_Bounds& operator=( const TypeCode_Bounds& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS


  #ifdef HAVE_STD_EH
  TypeCode_Bounds *operator->() { return this; }
  TypeCode_Bounds& operator*() { return *this; }
  operator TypeCode_Bounds*() { return this; }
  #endif // HAVE_STD_EH

  void _throwit() const;
  const char *_repoid() const;
  void _encode( CORBA::DataEncoder &en ) const;
  void _encode_any( CORBA::Any &a ) const;
  CORBA::Exception *_clone() const;
  static TypeCode_Bounds *EXCEPTION_DOWNCAST( CORBA::Exception *ex );
  static const TypeCode_Bounds *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );
};

#ifdef HAVE_STD_EH
typedef TypeCode_Bounds TypeCode_Bounds_catch;
#else
typedef ExceptVar<TypeCode_Bounds> TypeCode_Bounds_var;
typedef TypeCode_Bounds_var TypeCode_Bounds_out;
typedef TypeCode_Bounds_var TypeCode_Bounds_catch;
#endif // HAVE_STD_EH

struct TypeCode_BadKind : public UserException {
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  TypeCode_BadKind();
  ~TypeCode_BadKind();
  TypeCode_BadKind( const TypeCode_BadKind& s );
  TypeCode_BadKind& operator=( const TypeCode_BadKind& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS


  #ifdef HAVE_STD_EH
  TypeCode_BadKind *operator->() { return this; }
  TypeCode_BadKind& operator*() { return *this; }
  operator TypeCode_BadKind*() { return this; }
  #endif // HAVE_STD_EH

  void _throwit() const;
  const char *_repoid() const;
  void _encode( CORBA::DataEncoder &en ) const;
  void _encode_any( CORBA::Any &a ) const;
  CORBA::Exception *_clone() const;
  static TypeCode_BadKind *EXCEPTION_DOWNCAST( CORBA::Exception *ex );
  static const TypeCode_BadKind *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );
};

#ifdef HAVE_STD_EH
typedef TypeCode_BadKind TypeCode_BadKind_catch;
#else
typedef ExceptVar<TypeCode_BadKind> TypeCode_BadKind_var;
typedef TypeCode_BadKind_var TypeCode_BadKind_out;
typedef TypeCode_BadKind_var TypeCode_BadKind_catch;
#endif // HAVE_STD_EH

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif



#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)


#if !defined(MICO_NO_TOPLEVEL_MODULES) && !defined(MICO_IN_GENERATED_CODE)
#include <mico/template_impl.h>
#endif

#endif
