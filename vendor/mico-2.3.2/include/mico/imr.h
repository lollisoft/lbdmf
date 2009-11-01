/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#if !defined(__IMR_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __IMR_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
#include <CORBA.h>
#endif

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)


class ImplementationDef;
typedef ImplementationDef *ImplementationDef_ptr;
typedef ImplementationDef_ptr ImplementationDefRef;
typedef ObjVar<ImplementationDef> ImplementationDef_var;
typedef ImplementationDef_var ImplementationDef_out;


// Common definitions for interface ImplementationDef
class ImplementationDef : 
  virtual public CORBA::Object
{
  public:
    virtual ~ImplementationDef();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ImplementationDef_ptr _ptr_type;
    typedef ImplementationDef_var _var_type;
    #endif

    static ImplementationDef_ptr _narrow( CORBA::Object_ptr obj );
    static ImplementationDef_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ImplementationDef_ptr _duplicate( ImplementationDef_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ImplementationDef_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    enum ActivationMode {
      ActivateShared = 0,
      ActivateUnshared,
      ActivatePerMethod,
      ActivatePersistent,
      ActivateLibrary,
      ActivatePOA
    };

    typedef ActivationMode& ActivationMode_out;

    static CORBA::TypeCodeConst _tc_ActivationMode;

    typedef SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> ObjectTag;
    #ifdef _WINDOWS
    static ObjectTag _dummy_ObjectTag;
    #endif
    typedef TSeqVar<SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> > ObjectTag_var;
    typedef ObjectTag_var ObjectTag_out;

    static CORBA::TypeCodeConst _tc_ObjectTag;

    struct ObjectInfo;
    typedef TVarVar<ObjectInfo> ObjectInfo_var;
    typedef ObjectInfo_var ObjectInfo_out;

    struct ObjectInfo {
      #ifdef HAVE_TYPEDEF_OVERLOAD
      typedef ObjectInfo_var _var_type;
      #endif
      #ifdef HAVE_EXPLICIT_STRUCT_OPS
      ObjectInfo();
      ~ObjectInfo();
      ObjectInfo( const ObjectInfo& s );
      ObjectInfo& operator=( const ObjectInfo& s );
      #endif //HAVE_EXPLICIT_STRUCT_OPS

      CORBA::String_var repoid;
      ObjectTag tag;
    };

    static CORBA::TypeCodeConst _tc_ObjectInfo;

    typedef SequenceTmpl<ObjectInfo,MICO_TID_DEF> ObjectInfoList;
    #ifdef _WINDOWS
    static ObjectInfoList _dummy_ObjectInfoList;
    #endif
    typedef TSeqVar<SequenceTmpl<ObjectInfo,MICO_TID_DEF> > ObjectInfoList_var;
    typedef ObjectInfoList_var ObjectInfoList_out;

    static CORBA::TypeCodeConst _tc_ObjectInfoList;

    virtual ActivationMode mode() = 0;
    virtual void mode( ActivationMode value ) = 0;
    virtual ObjectInfoList* objs() = 0;
    virtual void objs( const ObjectInfoList& value ) = 0;
    virtual char* name() = 0;
    virtual char* command() = 0;
    virtual void command( const char* value ) = 0;
    virtual char* tostring() = 0;

  protected:
    ImplementationDef() {};
  private:
    ImplementationDef( const ImplementationDef& );
    void operator=( const ImplementationDef& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ImplementationDef;

// Stub for interface ImplementationDef
class ImplementationDef_stub:
  virtual public ImplementationDef
{
  public:
    virtual ~ImplementationDef_stub();
    ActivationMode mode();
    void mode( ActivationMode value );
    ObjectInfoList* objs();
    void objs( const ObjectInfoList& value );
    char* name();
    char* command();
    void command( const char* value );
    char* tostring();

  private:
    void operator=( const ImplementationDef_stub& );
};

class ImplementationDef_skel :
  virtual public StaticMethodDispatcher,
  virtual public ImplementationDef
{
  public:
    ImplementationDef_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ImplementationDef_skel();
    ImplementationDef_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ImplementationDef_ptr _this();

};

class ImplRepository;
typedef ImplRepository *ImplRepository_ptr;
typedef ImplRepository_ptr ImplRepositoryRef;
typedef ObjVar<ImplRepository> ImplRepository_var;
typedef ImplRepository_var ImplRepository_out;


// Common definitions for interface ImplRepository
class ImplRepository : 
  virtual public CORBA::Object
{
  public:
    virtual ~ImplRepository();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ImplRepository_ptr _ptr_type;
    typedef ImplRepository_var _var_type;
    #endif

    static ImplRepository_ptr _narrow( CORBA::Object_ptr obj );
    static ImplRepository_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ImplRepository_ptr _duplicate( ImplRepository_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ImplRepository_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    typedef IfaceSequenceTmpl<ImplementationDef_var,ImplementationDef_ptr> ImplDefSeq;
    #ifdef _WINDOWS
    static ImplDefSeq _dummy_ImplDefSeq;
    #endif
    typedef TSeqVar<IfaceSequenceTmpl<ImplementationDef_var,ImplementationDef_ptr> > ImplDefSeq_var;
    typedef ImplDefSeq_var ImplDefSeq_out;

    static CORBA::TypeCodeConst _tc_ImplDefSeq;

    virtual ImplementationDef_ptr restore( const char* asstring ) = 0;
    virtual ImplementationDef_ptr create( ImplementationDef::ActivationMode mode, const ImplementationDef::ObjectInfoList& objs, const char* name, const char* command ) = 0;
    virtual void destroy( ImplementationDef_ptr impl_def ) = 0;
    virtual ImplDefSeq* find_by_name( const char* name ) = 0;
    virtual ImplDefSeq* find_by_repoid( const char* repoid ) = 0;
    virtual ImplDefSeq* find_by_repoid_tag( const char* repoid, const ImplementationDef::ObjectTag& tag ) = 0;
    virtual ImplDefSeq* find_all() = 0;

  protected:
    ImplRepository() {};
  private:
    ImplRepository( const ImplRepository& );
    void operator=( const ImplRepository& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_ImplRepository;

// Stub for interface ImplRepository
class ImplRepository_stub:
  virtual public ImplRepository
{
  public:
    virtual ~ImplRepository_stub();
    ImplementationDef_ptr restore( const char* asstring );
    ImplementationDef_ptr create( ImplementationDef::ActivationMode mode, const ImplementationDef::ObjectInfoList& objs, const char* name, const char* command );
    void destroy( ImplementationDef_ptr impl_def );
    ImplDefSeq* find_by_name( const char* name );
    ImplDefSeq* find_by_repoid( const char* repoid );
    ImplDefSeq* find_by_repoid_tag( const char* repoid, const ImplementationDef::ObjectTag& tag );
    ImplDefSeq* find_all();

  private:
    void operator=( const ImplRepository_stub& );
};

class ImplRepository_skel :
  virtual public StaticMethodDispatcher,
  virtual public ImplRepository
{
  public:
    ImplRepository_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ImplRepository_skel();
    ImplRepository_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    ImplRepository_ptr _this();

};

class OAServer;
typedef OAServer *OAServer_ptr;
typedef OAServer_ptr OAServerRef;
typedef ObjVar<OAServer> OAServer_var;
typedef OAServer_var OAServer_out;


// Common definitions for interface OAServer
class OAServer : 
  virtual public CORBA::Object
{
  public:
    virtual ~OAServer();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef OAServer_ptr _ptr_type;
    typedef OAServer_var _var_type;
    #endif

    static OAServer_ptr _narrow( CORBA::Object_ptr obj );
    static OAServer_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static OAServer_ptr _duplicate( OAServer_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static OAServer_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    typedef IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> ObjSeq;
    #ifdef _WINDOWS
    static ObjSeq _dummy_ObjSeq;
    #endif
    typedef TSeqVar<IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> > ObjSeq_var;
    typedef ObjSeq_var ObjSeq_out;

    static CORBA::TypeCodeConst _tc_ObjSeq;

    virtual void restore_request( const ObjSeq& objs ) = 0;
    virtual void obj_inactive( CORBA::Object_ptr obj ) = 0;
    virtual void impl_inactive() = 0;

  protected:
    OAServer() {};
  private:
    OAServer( const OAServer& );
    void operator=( const OAServer& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_OAServer;

// Stub for interface OAServer
class OAServer_stub:
  virtual public OAServer
{
  public:
    virtual ~OAServer_stub();
    void restore_request( const ObjSeq& objs );
    void obj_inactive( CORBA::Object_ptr obj );
    void impl_inactive();

  private:
    void operator=( const OAServer_stub& );
};

class OAServer_skel :
  virtual public StaticMethodDispatcher,
  virtual public OAServer
{
  public:
    OAServer_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~OAServer_skel();
    OAServer_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    OAServer_ptr _this();

};

class OAMediator;
typedef OAMediator *OAMediator_ptr;
typedef OAMediator_ptr OAMediatorRef;
typedef ObjVar<OAMediator> OAMediator_var;
typedef OAMediator_var OAMediator_out;


// Common definitions for interface OAMediator
class OAMediator : 
  virtual public CORBA::Object
{
  public:
    virtual ~OAMediator();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef OAMediator_ptr _ptr_type;
    typedef OAMediator_var _var_type;
    #endif

    static OAMediator_ptr _narrow( CORBA::Object_ptr obj );
    static OAMediator_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static OAMediator_ptr _duplicate( OAMediator_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static OAMediator_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    typedef SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> RefData;
    #ifdef _WINDOWS
    static RefData _dummy_RefData;
    #endif
    typedef TSeqVar<SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> > RefData_var;
    typedef RefData_var RefData_out;

    static CORBA::TypeCodeConst _tc_RefData;

    typedef IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> ObjSeq;
    #ifdef _WINDOWS
    static ObjSeq _dummy_ObjSeq;
    #endif
    typedef TSeqVar<IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> > ObjSeq_var;
    typedef ObjSeq_var ObjSeq_out;

    static CORBA::TypeCodeConst _tc_ObjSeq;

    typedef CORBA::ULong ServerId;
    static CORBA::TypeCodeConst _tc_ServerId;

    virtual void create_obj( CORBA::Object_ptr objref, const RefData& id, CORBA::Object_ptr& remote_objref, ServerId svid ) = 0;
    virtual void restore_obj( CORBA::Object_ptr objref, CORBA::Object_ptr& remote_objref, RefData*& id, ServerId svid ) = 0;
    virtual void activate_obj( CORBA::Object_ptr objref, ServerId svid ) = 0;
    virtual void deactivate_obj( CORBA::Object_ptr objref, ServerId svid ) = 0;
    virtual void migrate_obj( CORBA::Object_ptr objref, ServerId svid, ImplementationDef_ptr impl ) = 0;
    virtual void orphan_obj( CORBA::Object_ptr objref, ServerId svid ) = 0;
    virtual void dispose_obj( CORBA::Object_ptr objref, ServerId svid ) = 0;
    virtual void create_impl( ImplementationDef_ptr impl, OAServer_ptr server, ServerId& id ) = 0;
    virtual void activate_impl( ServerId id ) = 0;
    virtual void deactivate_impl( ServerId id ) = 0;
    virtual CORBA::Object_ptr get_remote_object( const RefData& key ) = 0;
    virtual void dispose_impl( ServerId id ) = 0;
    virtual ObjSeq* get_restore_objs( ServerId id ) = 0;
    virtual CORBA::Boolean force_activation( ImplementationDef_ptr impl ) = 0;

  protected:
    OAMediator() {};
  private:
    OAMediator( const OAMediator& );
    void operator=( const OAMediator& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_OAMediator;

// Stub for interface OAMediator
class OAMediator_stub:
  virtual public OAMediator
{
  public:
    virtual ~OAMediator_stub();
    void create_obj( CORBA::Object_ptr objref, const RefData& id, CORBA::Object_ptr& remote_objref, ServerId svid );
    void restore_obj( CORBA::Object_ptr objref, CORBA::Object_ptr& remote_objref, RefData*& id, ServerId svid );
    void activate_obj( CORBA::Object_ptr objref, ServerId svid );
    void deactivate_obj( CORBA::Object_ptr objref, ServerId svid );
    void migrate_obj( CORBA::Object_ptr objref, ServerId svid, ImplementationDef_ptr impl );
    void orphan_obj( CORBA::Object_ptr objref, ServerId svid );
    void dispose_obj( CORBA::Object_ptr objref, ServerId svid );
    void create_impl( ImplementationDef_ptr impl, OAServer_ptr server, ServerId& id );
    void activate_impl( ServerId id );
    void deactivate_impl( ServerId id );
    CORBA::Object_ptr get_remote_object( const RefData& key );
    void dispose_impl( ServerId id );
    ObjSeq* get_restore_objs( ServerId id );
    CORBA::Boolean force_activation( ImplementationDef_ptr impl );

  private:
    void operator=( const OAMediator_stub& );
};

class OAMediator_skel :
  virtual public StaticMethodDispatcher,
  virtual public OAMediator
{
  public:
    OAMediator_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~OAMediator_skel();
    OAMediator_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    OAMediator_ptr _this();

};

class POAMediator;
typedef POAMediator *POAMediator_ptr;
typedef POAMediator_ptr POAMediatorRef;
typedef ObjVar<POAMediator> POAMediator_var;
typedef POAMediator_var POAMediator_out;


// Common definitions for interface POAMediator
class POAMediator : 
  virtual public CORBA::Object
{
  public:
    virtual ~POAMediator();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef POAMediator_ptr _ptr_type;
    typedef POAMediator_var _var_type;
    #endif

    static POAMediator_ptr _narrow( CORBA::Object_ptr obj );
    static POAMediator_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static POAMediator_ptr _duplicate( POAMediator_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static POAMediator_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );
    static vector<CORBA::Narrow_proto> *_narrow_helpers;
    static bool _narrow_helper2( CORBA::Object_ptr obj );

    virtual char* create_impl( const char* svid, const char* ior ) = 0;
    virtual void activate_impl( const char* svid ) = 0;
    virtual void deactivate_impl( const char* svid ) = 0;
    virtual CORBA::Boolean force_activation( ImplementationDef_ptr impl ) = 0;

  protected:
    POAMediator() {};
  private:
    POAMediator( const POAMediator& );
    void operator=( const POAMediator& );
};

MICO_EXPORT_VAR_DECL CORBA::TypeCodeConst _tc_POAMediator;

// Stub for interface POAMediator
class POAMediator_stub:
  virtual public POAMediator
{
  public:
    virtual ~POAMediator_stub();
    char* create_impl( const char* svid, const char* ior );
    void activate_impl( const char* svid );
    void deactivate_impl( const char* svid );
    CORBA::Boolean force_activation( ImplementationDef_ptr impl );

  private:
    void operator=( const POAMediator_stub& );
};

class POAMediator_skel :
  virtual public StaticMethodDispatcher,
  virtual public POAMediator
{
  public:
    POAMediator_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~POAMediator_skel();
    POAMediator_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr _req, CORBA::Environment &_env );
    POAMediator_ptr _this();

};

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif



#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

void operator<<=( CORBA::Any &a, const ::CORBA::ImplementationDef::ActivationMode &e );

CORBA::Boolean operator>>=( const CORBA::Any &a, ::CORBA::ImplementationDef::ActivationMode &e );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ImplementationDef_ActivationMode;

void operator<<=( CORBA::Any &_a, const ::CORBA::ImplementationDef::ObjectInfo &_s );
void operator<<=( CORBA::Any &_a, ::CORBA::ImplementationDef::ObjectInfo *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ImplementationDef::ObjectInfo &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, ::CORBA::ImplementationDef::ObjectInfo *&_s );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ImplementationDef_ObjectInfo;

void operator<<=( CORBA::Any &a, const CORBA::ImplementationDef_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ImplementationDef_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ImplementationDef_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ImplementationDef;

void operator<<=( CORBA::Any &a, const CORBA::ImplRepository_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::ImplRepository_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::ImplRepository_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_ImplRepository;

void operator<<=( CORBA::Any &a, const CORBA::OAServer_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::OAServer_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::OAServer_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_OAServer;

void operator<<=( CORBA::Any &a, const CORBA::OAMediator_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::OAMediator_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::OAMediator_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_OAMediator;

void operator<<=( CORBA::Any &a, const CORBA::POAMediator_ptr obj );
void operator<<=( CORBA::Any &a, CORBA::POAMediator_ptr* obj_ptr );
CORBA::Boolean operator>>=( const CORBA::Any &a, CORBA::POAMediator_ptr &obj );

extern CORBA::StaticTypeInfo *_marshaller_CORBA_POAMediator;

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> *&_s );

void operator<<=( CORBA::Any &_a, const SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a, SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, SequenceTmpl<CORBA::ImplementationDef::ObjectInfo,MICO_TID_DEF> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ImplementationDef_ObjectInfo;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> &_s );
void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::ImplementationDef_var,CORBA::ImplementationDef_ptr> *&_s );

extern CORBA::StaticTypeInfo *_marshaller__seq_CORBA_ImplementationDef;

void operator<<=( CORBA::Any &_a, const IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> &_s );
void operator<<=( CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a, IfaceSequenceTmpl<CORBA::Object_var,CORBA::Object_ptr> *&_s );

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)


#if !defined(MICO_NO_TOPLEVEL_MODULES) && !defined(MICO_IN_GENERATED_CODE)
#include <mico/template_impl.h>
#endif

#endif
