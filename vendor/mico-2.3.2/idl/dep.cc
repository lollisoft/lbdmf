/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#include "dep.h"


/*
 * Class IDLDep computes the dependencies between IDL definitions.
 * This is required for IDL specifications like (see mico/test/idl/28):
 * 
 *   module M1 {
 *     typedef char A1;
 *   };
 * 
 *   module M2 {
 *     typedef M1::A1 A2;
 *   };
 * 
 *   module M1 {
 *     typedef M2::A2 A3;
 *   };
 * 
 * The interface repository will only contain two modules, so
 * that a simple depth first search of the IR will yield the
 * (wrong) order during code generation: M1::A1, M1::A3, M2::A2
 * The correct order is determined via a dependency graph. The class
 * IDLDep will generate the following dependency graph for the
 * above IDL specification:
 *                               _top
 *                              /  |  \
 *                             /   |   \
 *                            /  M1::A3 \
 *                           |        \  \
 *                           |        M2::A2
 *                           |         /
 *                           \        /
 *                            \      /
 *                             M1::A1
 *
 * A simple depth-first, left-to-right, post-order travsersal will
 * yield the correct order of IDL definitions.
 */

IDLDep::IDLDep( CORBA::Container_ptr con )
{
  _top = new Dep;
  _top->obj = CORBA::IRObject::_nil();
  _bottom = new Dep;
  _bottom->obj = CORBA::IRObject::_nil();
  _container = con;
}

IRObjSeq&
IDLDep::build_dependencies()
{
  set_current_iface( CORBA::Container::_nil() );
  traverse_container( _container );
  compute_dependencies();
  return _ordered_objs;
};

void
IDLDep::print (Dep * where)
{
  if (!where) {
    set_visited_flag (_top, false);
    where = (Dep*) _top;
  }

  if (where->visited) {
    return;
  }

  where->visited = true;

  CORBA::Contained_var co = CORBA::Contained::_narrow (where->obj);
  if (!CORBA::is_nil (co)) {
    CORBA::String_var n = co->absolute_name ();
    cout << "Dependencies for " << n.in();
    if (where->iface_as_forward) {
      cout << " (forward decl)" << endl;
    }
    cout << ":" << endl;
  }
  else {
    cout << "Dependencies for (anonymous type):" << endl;
  }

  for (CORBA::ULong i0=0; i0<where->deps.size(); i0++) {
    if (!where->deps[i0]) {
      continue;
    }
    CORBA::Contained_var d = CORBA::Contained::_narrow (where->deps[i0]->obj);
    if (CORBA::is_nil (d)) {
      continue;
    }
    CORBA::String_var dn = d->absolute_name();
    cout << "  ... " << dn.in();
    if (where->deps[i0]->iface_as_forward) {
      cout << "  (forward decl)";
    }
    cout << endl;
  }

  cout << endl;

  for (CORBA::ULong i1=0; i1<where->deps.size(); i1++) {
    if (!where->deps[i1] || where->deps[i1]->iface_as_forward) {
      continue;
    }
    print (where->deps[i1]);
  }
}

void
IDLDep::set_current_iface( CORBA::Container_ptr in )
{
  _current_iface = CORBA::Container::_duplicate( in );
}

CORBA::Container_ptr
IDLDep::get_current_iface( void )
{
  return CORBA::Container::_duplicate (_current_iface);
}

/*
 * return true if there exists a dependency path from "to" to "from"
 */
bool
IDLDep::is_circular_dep( Dep* from, Dep* to )
{
  CORBA::IRObject_ptr o1, o2;
  o1 = (CORBA::IRObject_ptr) from->obj;
  o2 = (CORBA::IRObject_ptr) to->obj;

  if( CORBA::is_nil( o1 ) || CORBA::is_nil( o2 ) )
    return false;

  if( o1->_is_equivalent( o2 ) )
    return true;
  
  for( int i = 0; i < to->deps.size(); i++ ) {
    if( is_circular_dep( from, to->deps[ i ] ) )
      return true;
  }
  
  return false;
}

void
IDLDep::create_dep( Dep* from, Dep* to )
{
  // if there is a circular dependency (which would occur for
  // recursive data structures), we don't need to register a dependency
  if( is_circular_dep( from, to ) ) {
    
    // Actually, if "to" denotes an InterfaceDef, then we had a
    // forward declaration before "from" was defined. Therefore
    // we need to add this dependency to the forward declaration
    // at this time.
    if( !CORBA::is_nil( to->obj ) &&
	(to->obj->def_kind() == CORBA::dk_Interface ||
	 to->obj->def_kind() == CORBA::dk_Value)) {
      Dep *d = locate_dep_for_forward_iface( to->obj );
      from->deps.push_back( d );
    }
    
    return;
  }
  
  from->deps.push_back( to );
}

void
IDLDep::create_iface_dep( Dep* to )
{
  // while we are traversing the contents of an interface,
  // we need to create a dependency from the interface to
  // the contained object
  if( !CORBA::is_nil( _current_iface ) ) {
    Dep* from = locate_dep( _current_iface, true );
    create_dep( from, to );
  }
}

Dep*
IDLDep::locate_dep_for_forward_iface( CORBA::IRObject_ptr obj )
{
  MapObjDep::iterator i = _fwd_iface_deps.find( obj );
  
  if( i == _fwd_iface_deps.end() ) {
    // We haven't created a node for this forward decl yet
    // Create a new node in the dependency graph
    Dep* d = new Dep;
    d->obj = CORBA::IRObject::_duplicate( obj );
    
    // Mark it as a forward declaration of this interface
    d->iface_as_forward = true;
    
    _fwd_iface_deps[ obj ] = d;
  }
  
  return _fwd_iface_deps[ obj ];
}

Dep*
IDLDep::locate_dep( CORBA::IRObject_ptr obj, bool create_iface )
{
  MapObjDep::iterator i = _all_deps.find( obj );

  if( i == _all_deps.end() ) {
    // This object is not yet registered

    if( obj->def_kind() == CORBA::dk_Primitive ) {
      // For primitive data types, we return _bottom
      return _bottom;
    }

    if( (obj->def_kind() == CORBA::dk_Interface ||
	 obj->def_kind() == CORBA::dk_Value) && !create_iface ) {
      // We're trying to find an interface that has not yet been
      // registered and no dependecy node should be generated.
      // This means that the interface is used in a forward
      // declaration. We need to generate a special forward
      // node.
      return locate_dep_for_forward_iface( obj );
    }
    
    // Create a new node in the dependency graph
    Dep* d = new Dep;
    d->obj = CORBA::IRObject::_duplicate( obj );
    _all_deps[ obj ] = d;

    // Link the new obj with _top
    create_dep( _top, d );

    // if obj is a sequence or an array we also need to register
    // recursively all nested obj
    switch( obj->def_kind() ) {
    case CORBA::dk_Sequence:
      {
	CORBA::SequenceDef_var seq = CORBA::SequenceDef::_narrow( obj );
	CORBA::IDLType_var elem = seq->element_type_def();
	Dep* elem_dep = locate_dep( elem );
	create_dep( d, elem_dep );
	break;
      }
    case CORBA::dk_Array:
      {
	CORBA::ArrayDef_var arr = CORBA::ArrayDef::_narrow( obj );
	CORBA::IDLType_var elem = arr->element_type_def();
	Dep* elem_dep = locate_dep( elem );
	create_dep( d, elem_dep );
	break;
      }
    }
  }
  
  return _all_deps[ obj ];
}

void
IDLDep::dep_Struct( CORBA::StructDef_ptr s )
{
  Dep* from = locate_dep( s );
  create_iface_dep( from );

  CORBA::Container_var old_current = get_current_iface ();
  set_current_iface (s);
  traverse_container (s);
  set_current_iface (old_current.in());

  CORBA::StructMemberSeq_var members = s->members();

  for( CORBA::ULong i = 0; i < members->length(); i++ ) {
    CORBA::TypeCode_ptr tc = members[ i ].type;
    CORBA::IDLType_ptr m = members[ i ].type_def;
    Dep* to = locate_dep( m );
    create_dep( from, to );
  }
}

void
IDLDep::dep_Union( CORBA::UnionDef_ptr u )
{
  Dep* from = locate_dep( u );
  create_iface_dep( from );

  CORBA::Container_var old_current = get_current_iface ();
  set_current_iface (u);
  traverse_container (u);
  set_current_iface (old_current.in());

  CORBA::UnionMemberSeq_var members = u->members();

  for( CORBA::ULong i = 0; i < members->length(); i++ ) {
    CORBA::TypeCode_ptr tc = members[ i ].type;
    CORBA::IDLType_ptr m = members[ i ].type_def;
    Dep* to = locate_dep( m );
    create_dep( from, to );
  }

  CORBA::IDLType_var disc = u->discriminator_type_def();
  Dep* to = locate_dep( disc );
  create_dep( from, to );
}

void
IDLDep::dep_Constant( CORBA::ConstantDef_ptr c )
{
  Dep* from = locate_dep( c );
  create_iface_dep( from );

  CORBA::IDLType_var orig = c->type_def();
  Dep* to = locate_dep( orig );

  create_dep( from, to );
}

void
IDLDep::dep_Exception( CORBA::ExceptionDef_ptr e )
{
  Dep* from = locate_dep( e );
  create_iface_dep( from );

  CORBA::Container_var old_current = get_current_iface ();
  set_current_iface (e);
  traverse_container (e);
  set_current_iface (old_current.in());

  CORBA::StructMemberSeq_var members = e->members();

  CORBA::ULong i;
  for( i = 0; i < members->length(); i++ ) {
    CORBA::IDLType_ptr m = members[ i ].type_def;
    Dep* to = locate_dep( m );
    create_dep( from, to );
  }
}

void
IDLDep::dep_Enum( CORBA::EnumDef_ptr e )
{
  Dep* from = locate_dep( e );
  create_iface_dep( from );
}

void
IDLDep::dep_Alias( CORBA::AliasDef_ptr a )
{
  Dep* from = locate_dep( a );
  create_iface_dep( from );

  CORBA::IDLType_var orig = a->original_type_def();
  Dep* to = locate_dep( orig );

  create_dep( from, to );
}

void
IDLDep::dep_Interface( CORBA::InterfaceDef_ptr in )
{
  set_current_iface( in );

  Dep* from = locate_dep( in, true );

  // set dependencies for base interfaces
  CORBA::InterfaceDefSeq_var bases = in->base_interfaces();
  for( CORBA::ULong i0 = 0; i0 < bases->length(); i0++ ) {
    Dep* to = locate_dep( bases[ i0 ], true );
    create_dep( from, to );
  }

  // set dependencies for local declarations
  traverse_container( in );

  set_current_iface( CORBA::Container::_nil() );
}

void
IDLDep::dep_Operation( CORBA::OperationDef_ptr o )
{
  CORBA::IDLType_var res = o->result_def();
  
  Dep* d = locate_dep( res );
  create_iface_dep( d );

  CORBA::ParDescriptionSeq_var params = o->params();
  for( CORBA::ULong i = 0; i < params->length(); i++ ) {
    d = locate_dep( params[ i ].type_def );
    create_iface_dep( d );
  }
  
  CORBA::ExceptionDefSeq_var exs = o->exceptions();
  for( CORBA::ULong i0 = 0; i0 < exs->length(); i0++ ) {
    d = locate_dep( exs[ i0 ] );
    create_iface_dep( d );
  }
  
}

void
IDLDep::dep_Attribute( CORBA::AttributeDef_ptr a )
{
  CORBA::IDLType_var t = a->type_def();
  Dep* d = locate_dep( t );
  create_iface_dep( d );
}

void
IDLDep::dep_ValueBox( CORBA::ValueBoxDef_ptr vb )
{
  Dep* from = locate_dep (vb);
  create_iface_dep (from);

  CORBA::IDLType_var orig = vb->original_type_def();
  Dep* to = locate_dep (orig);
  create_dep (from, to);
}

void
IDLDep::dep_Value( CORBA::ValueDef_ptr vb )
{
  Dep* from = locate_dep( vb, true );
  create_iface_dep( from );

  CORBA::Container_var old_current = get_current_iface ();
  set_current_iface (vb);
  traverse_container (vb);

  // set dependencies for base values and supported interface
  CORBA::InterfaceDefSeq_var supported_interfaces = vb->supported_interfaces();
  for (CORBA::ULong i2=0; i2<supported_interfaces->length(); i2++) {
    Dep * to = locate_dep (supported_interfaces[i2], true);
    create_dep (from, to);
  }

  CORBA::ValueDef_var base_value = vb->base_value ();
  if (!CORBA::is_nil (base_value)) {
    Dep * to = locate_dep (base_value, true);
    create_dep (from, to);
  }

  CORBA::ValueDefSeq_var abv = vb->abstract_base_values ();
  for (CORBA::ULong i0=0; i0<abv->length(); i0++) {
    Dep * to = locate_dep (abv[i0], true);
    create_dep (from, to);
  }

  // set dependencies for types in initializer list
  CORBA::InitializerSeq_var isv = vb->initializers ();
  for (CORBA::ULong i1=0; i1<isv->length(); i1++) {
    for (CORBA::ULong i2=0; i2<isv[i1].members.length(); i2++) {
      CORBA::IDLType_ptr m = isv[i1].members[i2].type_def;
      Dep * to = locate_dep (m, true);
      create_dep (from, to);
    }
  }

  set_current_iface (old_current.in());
}

void
IDLDep::dep_ValueMember( CORBA::ValueMemberDef_ptr vmd )
{
  CORBA::IDLType_var t = vmd->type_def();
  Dep* d = locate_dep( t );
  create_iface_dep( d );
}

void
IDLDep::dep_Native( CORBA::NativeDef_ptr nd )
{
  Dep* from = locate_dep( nd );
  create_iface_dep (from);
}

void
IDLDep::traverse_container( CORBA::Container_ptr con )
{
  CORBA::ContainedSeq_var c;
  c = con->contents( CORBA::dk_all, 1 );
  for( CORBA::ULong i = 0; i < c->length(); i++ ) {

    switch( c[ i ]->def_kind() ) {
    case CORBA::dk_Module:
      {
	CORBA::ModuleDef_var m = CORBA::ModuleDef::_narrow( c[ i ] );
	traverse_container( m );
	break;
      }
    case CORBA::dk_Interface:
      {
	CORBA::InterfaceDef_var in = CORBA::InterfaceDef::_narrow( c[ i ] );
	dep_Interface( in );
	break;
      }
    case CORBA::dk_Struct:
      {
	CORBA::StructDef_var s = CORBA::StructDef::_narrow( c[ i ] );
	dep_Struct( s );
	break;
      }
    case CORBA::dk_Union:
      {
	CORBA::UnionDef_var u = CORBA::UnionDef::_narrow( c[ i ] );
	dep_Union( u );
	break;
      }
    case CORBA::dk_Constant:
      {
	CORBA::ConstantDef_var co = CORBA::ConstantDef::_narrow( c[ i ] );
	dep_Constant( co );
	break;
      }
    case CORBA::dk_Exception:
      {
	CORBA::ExceptionDef_var e = CORBA::ExceptionDef::_narrow( c[ i ] );
	dep_Exception( e );
	break;
      }
    case CORBA::dk_Enum:
      {
	CORBA::EnumDef_var e = CORBA::EnumDef::_narrow( c[ i ] );
	dep_Enum( e );
	break;
      }
    case CORBA::dk_Alias:
      {
	CORBA::AliasDef_var a = CORBA::AliasDef::_narrow( c[ i ] );
	dep_Alias( a );
	break;
      }
    case CORBA::dk_Operation:
      {
	CORBA::OperationDef_var o = CORBA::OperationDef::_narrow( c[ i ] );
	dep_Operation( o );
	break;
      }
    case CORBA::dk_Attribute:
      {
	CORBA::AttributeDef_var a = CORBA::AttributeDef::_narrow( c[ i ] );
	dep_Attribute( a );
	break;
      }
    case CORBA::dk_ValueBox:
      {
	CORBA::ValueBoxDef_var vb = CORBA::ValueBoxDef::_narrow( c[ i ] );
	dep_ValueBox( vb );
	break;
      }
    case CORBA::dk_Value:
      {
	CORBA::ValueDef_var val = CORBA::ValueDef::_narrow( c[ i ] );
	dep_Value( val );
	break;
      }
    case CORBA::dk_ValueMember:
      {
	CORBA::ValueMemberDef_var vm =
	  CORBA::ValueMemberDef::_narrow( c[ i ] );
	dep_ValueMember( vm );
	break;
      }
    case CORBA::dk_Native:
      {
	CORBA::NativeDef_var nd = CORBA::NativeDef::_narrow( c[ i ] );
	dep_Native( nd );
	break;
      }
    default:
      assert( 0 );
    }
  }
}

/*
 * After we have built the dependency graph via build_dependencies(),
 * we compute the actual order of all IDL definitions. This is done
 * by a depth-first, left-right, post-order traversal of the dependency
 * graph starting from _top.
 */
void
IDLDep::compute_dependencies()
{
  // Phase 1: do a depth first traversal to determine the correct
  //          order of declaration
  traverse_dep( _top );

  // Phase 2: in phase 1 all anonymous types were omitted. These are
  //          now simply appended to _ordered_objs.
  set_visited_flag( _top, false );
  add_anonymous_types( _top );
}

void
IDLDep::traverse_dep( Dep* dep )
{
  // First visit all children
  for( CORBA::ULong i = 0; i < dep->deps.size(); i++ )
    traverse_dep( dep->deps[ i ] );

  // We need to skip this node if the current object is
  // an anonymous type or it is defined inside an InterfaceDef
  bool skip_dep = false;

  if( CORBA::is_nil( dep->obj ) ) {
    skip_dep = true;
  } else {
    CORBA::DefinitionKind k = dep->obj->def_kind();
    skip_dep = k == CORBA::dk_Sequence || k == CORBA::dk_String ||
               k == CORBA::dk_Wstring || k == CORBA::dk_Array ||
               k == CORBA::dk_Fixed;

    /*
     * We can skip all objects that are declared inside an InterfaceDef.
     * During the construction of the depencendy graph we have to
     * include all declarations inside an InterfaceDef in order to
     * place the interface itself at the right spot. But during
     * code generation all nested declaration are taken directly
     * from the interface itself rather than from _ordered_objs.
     * The traversal of an InterfaceDef during the construction of
     * the dependency graph also assures that all anonymous types
     * are added to _ordered_objs.
     *
     * This is true for objects in the other container types
     * StructDef, UnionDef and ExceptionDef, too.
     */
    CORBA::Contained_var c = CORBA::Contained::_narrow( dep->obj );
    if( !CORBA::is_nil( c ) ) {
      CORBA::Container_var con = c->defined_in();
      if( con->def_kind() == CORBA::dk_Interface ||
	  con->def_kind() == CORBA::dk_Value     ||
	  con->def_kind() == CORBA::dk_Struct    ||
	  con->def_kind() == CORBA::dk_Union     ||
	  con->def_kind() == CORBA::dk_Exception )
	skip_dep = true;
    }
  }
  
  if( !skip_dep && !dep->visited ) {
    CORBA::ULong i = _ordered_objs.length();
    _ordered_objs.length( i + 1 );
    _ordered_objs[ i ] = new IRObj;
    _ordered_objs[ i ]->obj = dep->obj;
    _ordered_objs[ i ]->iface_as_forward = dep->iface_as_forward;
    dep->visited = true;
  }
}

void
IDLDep::set_visited_flag( Dep* dep, bool flag )
{
  dep->visited = flag;
  
  // Visit all children
  for( CORBA::ULong i = 0; i < dep->deps.size(); i++ )
    set_visited_flag( dep->deps[ i ], flag );
}

void
IDLDep::add_anonymous_types( Dep* dep )
{
  bool is_anonymous_type = false;

  if( !CORBA::is_nil( dep->obj ) ) {
    CORBA::DefinitionKind k = dep->obj->def_kind();
    is_anonymous_type = k == CORBA::dk_Sequence || k == CORBA::dk_Array ||
                        k == CORBA::dk_Fixed || k == CORBA::dk_String ||
                        k == CORBA::dk_Wstring;
    
  }

  if( is_anonymous_type && !dep->visited ) {
    CORBA::ULong i = _ordered_objs.length();
    _ordered_objs.length( i + 1 );
    _ordered_objs[ i ] = new IRObj;
    _ordered_objs[ i ]->obj = dep->obj;
    _ordered_objs[ i ]->iface_as_forward = dep->iface_as_forward;
    dep->visited = true;
  }
  
  // recurse over whole dependency graph
  for( int i = 0; i < dep->deps.size(); i++ )
    add_anonymous_types( dep->deps[ i ] );
}
