/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__POLICY_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __POLICY_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)


//typedef CORBA::ULong PolicyType;
class Policy;
//typedef Policy *Policy_ptr;
typedef Policy_ptr PolicyRef;
//typedef ObjVar<Policy> Policy_var;
typedef Policy_var Policy_out;


// Common definitions for interface Policy
class Policy : 
  virtual public CORBA::Object
{
  public:
    virtual ~Policy();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef Policy_ptr _ptr_type;
    typedef Policy_var _var_type;
    #endif

    static Policy_ptr _narrow( CORBA::Object_ptr obj );
    static Policy_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static Policy_ptr _duplicate( Policy_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static Policy_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual PolicyType policy_type() = 0;

    virtual Policy_ptr copy() = 0;
    virtual void destroy() = 0;

  protected:
    Policy() {};
  private:
    Policy( const Policy& );
    void operator=( const Policy& );
};


//typedef IfaceSequenceTmpl<Policy_var,Policy_ptr> PolicyList;
#ifdef _WINDOWS
static PolicyList _dummy_PolicyList;
#endif
typedef TSeqVar<IfaceSequenceTmpl<Policy_var,Policy_ptr> > PolicyList_var;
typedef PolicyList_var PolicyList_out;

//enum SetOverrideType {
//  SET_OVERRIDE = 0,
//  ADD_OVERIDE
//};

typedef SetOverrideType& SetOverrideType_out;

class DomainManager;
//typedef DomainManager *DomainManager_ptr;
typedef DomainManager_ptr DomainManagerRef;
//typedef ObjVar<DomainManager> DomainManager_var;
typedef DomainManager_var DomainManager_out;


// Common definitions for interface DomainManager
class DomainManager : 
  virtual public CORBA::Object
{
  public:
    virtual ~DomainManager();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef DomainManager_ptr _ptr_type;
    typedef DomainManager_var _var_type;
    #endif

    static DomainManager_ptr _narrow( CORBA::Object_ptr obj );
    static DomainManager_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static DomainManager_ptr _duplicate( DomainManager_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static DomainManager_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual Policy_ptr get_domain_policy( PolicyType policy_type ) = 0;
    virtual void set_domain_policy( Policy_ptr policy ) = 0;
    virtual DomainManager_ptr copy() = 0;

  protected:
    DomainManager() {};
  private:
    DomainManager( const DomainManager& );
    void operator=( const DomainManager& );
};


MICO_EXPORT_CONST_DECL const CORBA::ULong SecConstruction;
class ConstructionPolicy;
typedef ConstructionPolicy *ConstructionPolicy_ptr;
typedef ConstructionPolicy_ptr ConstructionPolicyRef;
typedef ObjVar<ConstructionPolicy> ConstructionPolicy_var;
typedef ConstructionPolicy_var ConstructionPolicy_out;


// Common definitions for interface ConstructionPolicy
class ConstructionPolicy : 
  virtual public ::CORBA::Policy
{
  public:
    virtual ~ConstructionPolicy();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ConstructionPolicy_ptr _ptr_type;
    typedef ConstructionPolicy_var _var_type;
    #endif

    static ConstructionPolicy_ptr _narrow( CORBA::Object_ptr obj );
    static ConstructionPolicy_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ConstructionPolicy_ptr _duplicate( ConstructionPolicy_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ConstructionPolicy_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void make_domain_manager( InterfaceDef_ptr object_type, CORBA::Boolean constr_policy ) = 0;
    virtual CORBA::Boolean constr_policy( CORBA::Object_ptr object ) = 0;

  protected:
    ConstructionPolicy() {};
  private:
    ConstructionPolicy( const ConstructionPolicy& );
    void operator=( const ConstructionPolicy& );
};


//typedef IfaceSequenceTmpl<DomainManager_var,DomainManager_ptr> DomainManagerList;
#ifdef _WINDOWS
static DomainManagerList _dummy_DomainManagerList;
#endif
typedef TSeqVar<IfaceSequenceTmpl<DomainManager_var,DomainManager_ptr> > DomainManagerList_var;
typedef DomainManagerList_var DomainManagerList_out;

typedef CORBA::Short PolicyErrorCode;
MICO_EXPORT_CONST_DECL const CORBA::Short BAD_POLICY;
MICO_EXPORT_CONST_DECL const CORBA::Short UNSUPPORTED_POLICY;
MICO_EXPORT_CONST_DECL const CORBA::Short BAD_POLICY_TYPE;
MICO_EXPORT_CONST_DECL const CORBA::Short BAD_POLICY_VALUE;
MICO_EXPORT_CONST_DECL const CORBA::Short UNSUPPORTED_POLICY_VALUE;
struct PolicyError : public UserException {
  #ifdef HAVE_EXPLICIT_STRUCT_OPS
  PolicyError();
  ~PolicyError();
  PolicyError( const PolicyError& s );
  PolicyError& operator=( const PolicyError& s );
  #endif //HAVE_EXPLICIT_STRUCT_OPS

  #ifndef HAVE_EXPLICIT_STRUCT_OPS
  PolicyError();
  #endif //HAVE_EXPLICIT_STRUCT_OPS
  PolicyError( PolicyErrorCode _m0 );

  #ifdef HAVE_STD_EH
  PolicyError *operator->() { return this; }
  PolicyError& operator*() { return *this; }
  operator PolicyError*() { return this; }
  #endif // HAVE_STD_EH

  void _throwit() const;
  const char *_repoid() const;
  void _encode( CORBA::DataEncoder &en ) const;
  void _encode_any( CORBA::Any &a ) const;
  CORBA::Exception *_clone() const;
  static PolicyError *EXCEPTION_DOWNCAST( CORBA::Exception *ex );
  static const PolicyError *EXCEPTION_DOWNCAST( const CORBA::Exception *ex );
  PolicyErrorCode reason;
};

#ifdef HAVE_STD_EH
typedef PolicyError PolicyError_catch;
#else
typedef ExceptVar<PolicyError> PolicyError_var;
typedef PolicyError_var PolicyError_out;
typedef PolicyError_var PolicyError_catch;
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
