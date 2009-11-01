/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__IOPTYPES_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __IOPTYPES_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

MICO_NAMESPACE_DECL IOP {


typedef CORBA::ULong ServiceID;
struct ServiceContext;
typedef TVarVar<ServiceContext> ServiceContext_var;
typedef ServiceContext_var ServiceContext_out;

struct ServiceContext {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef ServiceContext_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  ServiceContext();
  ~ServiceContext();
  ServiceContext( const ServiceContext& s );
  ServiceContext& operator=( const ServiceContext& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  ServiceID context_id;
  typedef SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> _context_data_seq;
  _context_data_seq context_data;
};

typedef SequenceTmpl<ServiceContext,MICO_TID_DEF> ServiceContextList;
#ifdef _WINDOWS
static ServiceContextList _dummy_ServiceContextList;
#endif
typedef TSeqVar<SequenceTmpl<ServiceContext,MICO_TID_DEF> > ServiceContextList_var;
typedef ServiceContextList_var ServiceContextList_out;

MICO_EXPORT_CONST_DECL const CORBA::ULong TransactionService;
MICO_EXPORT_CONST_DECL const CORBA::ULong CodeSets;
MICO_EXPORT_CONST_DECL const CORBA::ULong BI_DIR_IIOP;
typedef CORBA::ULong ComponentId;
struct TaggedComponent;
typedef TVarVar<TaggedComponent> TaggedComponent_var;
typedef TaggedComponent_var TaggedComponent_out;

struct TaggedComponent {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef TaggedComponent_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  TaggedComponent();
  ~TaggedComponent();
  TaggedComponent( const TaggedComponent& s );
  TaggedComponent& operator=( const TaggedComponent& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  ComponentId tag;
  typedef SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> _component_data_seq;
  _component_data_seq component_data;
};

typedef SequenceTmpl<TaggedComponent,MICO_TID_DEF> MultipleComponentProfile;
#ifdef _WINDOWS
static MultipleComponentProfile _dummy_MultipleComponentProfile;
#endif
typedef TSeqVar<SequenceTmpl<TaggedComponent,MICO_TID_DEF> > MultipleComponentProfile_var;
typedef MultipleComponentProfile_var MultipleComponentProfile_out;

};


MICO_NAMESPACE_DECL GIOP {


enum MsgType_1_1 {
  Request = 0,
  Reply,
  CancelRequest,
  LocateRequest,
  LocateReply,
  CloseConnection,
  MessageError,
  Fragment
};

typedef MsgType_1_1& MsgType_1_1_out;

typedef MsgType_1_1 MsgType;
enum ReplyStatusType_1_2 {
  NO_EXCEPTION = 0,
  USER_EXCEPTION,
  SYSTEM_EXCEPTION,
  LOCATION_FORWARD,
  LOCATION_FORWARD_PERM,
  NEEDS_ADDRESSING_MODE
};

typedef ReplyStatusType_1_2& ReplyStatusType_1_2_out;

typedef ReplyStatusType_1_2 ReplyStatusType;
enum LocateStatusType_1_2 {
  UNKNOWN_OBJECT = 0,
  OBJECT_HERE,
  OBJECT_FORWARD,
  OBJECT_FORWARD_PERM,
  LOC_SYSTEM_EXCEPTION,
  LOC_NEEDS_ADDRESSING_MODE
};

typedef LocateStatusType_1_2& LocateStatusType_1_2_out;

typedef LocateStatusType_1_2 LocateStatusType;
typedef CORBA::Short AddressingDisposition;
MICO_EXPORT_CONST_DECL const CORBA::Short KeyAddr;
MICO_EXPORT_CONST_DECL const CORBA::Short ProfileAddr;
MICO_EXPORT_CONST_DECL const CORBA::Short ReferenceAddr;
};


MICO_NAMESPACE_DECL IIOP {


struct Version;
typedef TFixVar<Version> Version_var;
typedef Version_var Version_out;

struct Version {
  #ifdef HAVE_TYPEDEF_OVERLOAD
  typedef Version_var _var_type;
  #endif
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  Version();
  ~Version();
  Version( const Version& s );
  Version& operator=( const Version& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  CORBA::Char major;
  CORBA::Char minor;
};

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif

};


#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)


#if !defined(MICO_NO_TOPLEVEL_MODULES) && !defined(MICO_IN_GENERATED_CODE)
#include <mico/template_impl.h>
#endif

#endif
