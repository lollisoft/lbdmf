/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#ifdef __MINGW32__
#include <cstring>
#endif
#include <CORBA.h>
#include <mico/throw.h>
#include <mico/template_impl.h>

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::IOP::ServiceContext::ServiceContext()
{
}

CORBA::IOP::ServiceContext::ServiceContext( const ServiceContext& _s )
{
  context_id = ((ServiceContext&)_s).context_id;
  context_data = ((ServiceContext&)_s).context_data;
}

CORBA::IOP::ServiceContext::~ServiceContext()
{
}

CORBA::IOP::ServiceContext&
CORBA::IOP::ServiceContext::operator=( const ServiceContext& _s )
{
  context_id = ((ServiceContext&)_s).context_id;
  context_data = ((ServiceContext&)_s).context_data;
  return *this;
}
#endif


#ifdef HAVE_NAMESPACE
namespace CORBA { namespace IOP { const CORBA::ULong TransactionService = 0; }; };
#else
const CORBA::ULong CORBA::IOP::TransactionService = 0;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { namespace IOP { const CORBA::ULong CodeSets = 1; }; };
#else
const CORBA::ULong CORBA::IOP::CodeSets = 1;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { namespace IOP { const CORBA::ULong BI_DIR_IIOP = 5; }; };
#else
const CORBA::ULong CORBA::IOP::BI_DIR_IIOP = 5;
#endif

#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::IOP::TaggedComponent::TaggedComponent()
{
}

CORBA::IOP::TaggedComponent::TaggedComponent( const TaggedComponent& _s )
{
  tag = ((TaggedComponent&)_s).tag;
  component_data = ((TaggedComponent&)_s).component_data;
}

CORBA::IOP::TaggedComponent::~TaggedComponent()
{
}

CORBA::IOP::TaggedComponent&
CORBA::IOP::TaggedComponent::operator=( const TaggedComponent& _s )
{
  tag = ((TaggedComponent&)_s).tag;
  component_data = ((TaggedComponent&)_s).component_data;
  return *this;
}
#endif









#ifdef HAVE_NAMESPACE
namespace CORBA { namespace GIOP { const CORBA::Short KeyAddr = 0; }; };
#else
const CORBA::Short CORBA::GIOP::KeyAddr = 0;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { namespace GIOP { const CORBA::Short ProfileAddr = 1; }; };
#else
const CORBA::Short CORBA::GIOP::ProfileAddr = 1;
#endif
#ifdef HAVE_NAMESPACE
namespace CORBA { namespace GIOP { const CORBA::Short ReferenceAddr = 2; }; };
#else
const CORBA::Short CORBA::GIOP::ReferenceAddr = 2;
#endif
#ifdef HAVE_EXPLICIT_STRUCT_OPS
CORBA::IIOP::Version::Version()
{
}

CORBA::IIOP::Version::Version( const Version& _s )
{
  major = ((Version&)_s).major;
  minor = ((Version&)_s).minor;
}

CORBA::IIOP::Version::~Version()
{
}

CORBA::IIOP::Version&
CORBA::IIOP::Version::operator=( const Version& _s )
{
  major = ((Version&)_s).major;
  minor = ((Version&)_s).minor;
  return *this;
}
#endif

struct __tc_init_IOPTYPES {
  __tc_init_IOPTYPES()
  {
  }
};

static __tc_init_IOPTYPES __init_IOPTYPES;

