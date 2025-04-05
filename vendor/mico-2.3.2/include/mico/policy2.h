/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__POLICY2_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __POLICY2_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL MICOPolicy {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_MICOPolicy)


MICO_EXPORT_CONST_DECL const CORBA::ULong TRANSPORTPREF_POLICY_TYPE;
class TransportPrefPolicy;
typedef TransportPrefPolicy *TransportPrefPolicy_ptr;
typedef TransportPrefPolicy_ptr TransportPrefPolicyRef;
typedef ObjVar<TransportPrefPolicy> TransportPrefPolicy_var;
typedef TransportPrefPolicy_var TransportPrefPolicy_out;


// Common definitions for interface TransportPrefPolicy
class TransportPrefPolicy : 
  virtual public ::CORBA::Policy
{
  public:
    virtual ~TransportPrefPolicy();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef TransportPrefPolicy_ptr _ptr_type;
    typedef TransportPrefPolicy_var _var_type;
    #endif

    static TransportPrefPolicy_ptr _narrow( CORBA::Object_ptr obj );
    static TransportPrefPolicy_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static TransportPrefPolicy_ptr _duplicate( TransportPrefPolicy_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static TransportPrefPolicy_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    typedef CORBA::ULong ProfileTag;
    static CORBA::TypeCodeConst _tc_ProfileTag;

    typedef SequenceTmpl<ProfileTag,MICO_TID_DEF> ProfileTagSeq;
    #ifdef _WINDOWS
    static ProfileTagSeq _dummy_ProfileTagSeq;
    #endif
    typedef TSeqVar<SequenceTmpl<ProfileTag,MICO_TID_DEF> > ProfileTagSeq_var;
    typedef ProfileTagSeq_var ProfileTagSeq_out;

    static CORBA::TypeCodeConst _tc_ProfileTagSeq;

    virtual ProfileTagSeq* preferences() = 0;
    virtual void preferences( const ProfileTagSeq& value ) = 0;
    virtual ProfileTagSeq* preferences_nocopy() = 0;

  protected:
    TransportPrefPolicy() {};
  private:
    TransportPrefPolicy( const TransportPrefPolicy& );
    void operator=( const TransportPrefPolicy& );
};


#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_MICOPolicy)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif



#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL BiDirPolicy {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_BiDirPolicy)


typedef CORBA::UShort BidirectionalPolicyValue;
MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_BidirectionalPolicyValue;

MICO_EXPORT_CONST_DECL const CORBA::UShort NORMAL;
MICO_EXPORT_CONST_DECL const CORBA::UShort BOTH;
MICO_EXPORT_CONST_DECL const CORBA::ULong BIDIRECTIONAL_POLICY_TYPE;
class BidirectionalPolicy;
typedef BidirectionalPolicy *BidirectionalPolicy_ptr;
typedef BidirectionalPolicy_ptr BidirectionalPolicyRef;
typedef ObjVar<BidirectionalPolicy> BidirectionalPolicy_var;
typedef BidirectionalPolicy_var BidirectionalPolicy_out;


// Common definitions for interface BidirectionalPolicy
class BidirectionalPolicy : 
  virtual public ::CORBA::Policy
{
  public:
    virtual ~BidirectionalPolicy();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef BidirectionalPolicy_ptr _ptr_type;
    typedef BidirectionalPolicy_var _var_type;
    #endif

    static BidirectionalPolicy_ptr _narrow( CORBA::Object_ptr obj );
    static BidirectionalPolicy_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static BidirectionalPolicy_ptr _duplicate( BidirectionalPolicy_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static BidirectionalPolicy_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual BidirectionalPolicyValue value() = 0;

  protected:
    BidirectionalPolicy() {};
  private:
    BidirectionalPolicy( const BidirectionalPolicy& );
    void operator=( const BidirectionalPolicy& );
};


#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_BiDirPolicy)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif



#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

void operator<<=( CORBA::Any &_a, const SequenceTmpl<MICOPolicy::TransportPrefPolicy::ProfileTag,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<MICOPolicy::TransportPrefPolicy::ProfileTag,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<MICOPolicy::TransportPrefPolicy::ProfileTag,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<MICOPolicy::TransportPrefPolicy::ProfileTag,MICO_TID_DEF> *&_s );

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)


#if !defined(MICO_NO_TOPLEVEL_MODULES) && !defined(MICO_IN_GENERATED_CODE)
#include <mico/template_impl.h>
#endif

#endif
