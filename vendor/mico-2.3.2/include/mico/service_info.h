/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__SERVICE_INFO_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __SERVICE_INFO_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)


typedef CORBA::UShort ServiceType;
typedef CORBA::ULong ServiceOption;
typedef CORBA::ULong ServiceDetailType;
MICO_EXPORT_CONST_DECL const CORBA::UShort Security;
struct ServiceDetail;
typedef TVarVar<ServiceDetail> ServiceDetail_var;
typedef ServiceDetail_var ServiceDetail_out;

struct ServiceDetail {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ServiceDetail_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ServiceDetail();
  ~ServiceDetail();
  ServiceDetail( const ServiceDetail& s );
  ServiceDetail& operator=( const ServiceDetail& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  ServiceDetailType service_detail_type;
  typedef SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> _service_detail_seq;
  _service_detail_seq service_detail;
};

struct ServiceInformation;
typedef TVarVar<ServiceInformation> ServiceInformation_var;
typedef ServiceInformation_var ServiceInformation_out;

struct ServiceInformation {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ServiceInformation_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ServiceInformation();
  ~ServiceInformation();
  ServiceInformation( const ServiceInformation& s );
  ServiceInformation& operator=( const ServiceInformation& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  typedef SequenceTmpl<ServiceOption,MICO_TID_DEF> _service_options_seq;
  _service_options_seq service_options;
  typedef SequenceTmpl<ServiceDetail,MICO_TID_DEF> _service_details_seq;
  _service_details_seq service_details;
};

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
