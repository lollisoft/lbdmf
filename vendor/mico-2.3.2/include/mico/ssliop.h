/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__SSLIOP_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __SSLIOP_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#include <mico/throw.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL Security {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_Security)


typedef CORBA::ULong AssociationOptions;
MICO_EXPORT_CONST_DECL const CORBA::ULong NoProtection;
MICO_EXPORT_CONST_DECL const CORBA::ULong Integrity;
MICO_EXPORT_CONST_DECL const CORBA::ULong Confidentiality;
MICO_EXPORT_CONST_DECL const CORBA::ULong DetectReplay;
MICO_EXPORT_CONST_DECL const CORBA::ULong DetectMisordering;
MICO_EXPORT_CONST_DECL const CORBA::ULong EstablishTrustInTarget;
MICO_EXPORT_CONST_DECL const CORBA::ULong EstablishTrustInClient;
#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_Security)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif



#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL SSLIOP {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_SSLIOP)


struct SSL;
typedef TFixVar<SSL> SSL_var;
typedef SSL_var SSL_out;

struct SSL {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef SSL_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  SSL();
  ~SSL();
  SSL( const SSL& s );
  SSL& operator=( const SSL& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  Security::AssociationOptions target_supports;
  Security::AssociationOptions target_requires;
  CORBA::UShort port;
};

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_SSLIOP)

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
