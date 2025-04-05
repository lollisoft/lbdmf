/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#include <CORBA.h>
#ifndef _WINDOWS
#include <string.h>
#endif
#include <iostream.h>
#include <mico/impl.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/throw.h>


//-------------------


CORBA::DefaultValueRefCountBase::DefaultValueRefCountBase ()
{
}

CORBA::DefaultValueRefCountBase::~DefaultValueRefCountBase ()
{
}

CORBA::SimpleValueRefCountBase::SimpleValueRefCountBase ()
{
}

CORBA::SimpleValueRefCountBase::~SimpleValueRefCountBase ()
{
}

//-------------------


CORBA::ValueBase::ValueBase ()
{
  _destructing = false;
}

CORBA::ValueBase::ValueBase (const ValueBase &)
{
  _destructing = false;
}

CORBA::ValueBase::~ValueBase ()
{
}

CORBA::ValueBase *
CORBA::ValueBase::_downcast (ValueBase *vb)
{
    return vb;
}

void *
CORBA::ValueBase::_narrow_helper (const char *)
{
  return 0;
}

CORBA::ValueBase *
CORBA::ValueBase::_create (const vector<string> &repoids,
			   const string &myrepoid)
{
    CORBA::ORB_var orb = CORBA::ORB_instance ("mico-local-orb");

    if (repoids.size() == 0) {
	CORBA::ValueFactoryBase_var vf =
	    orb->lookup_value_factory (myrepoid.c_str());
	if (vf.in()) {
	  return vf->create_for_unmarshal();
	}
    } else {
	for (mico_vec_size_type i = 0; i < repoids.size(); ++i) {
	    CORBA::ValueFactoryBase_var vf =
		orb->lookup_value_factory (repoids[i].c_str());
	    if (vf.in()) {
	      return vf->create_for_unmarshal();
	    }
	}
    }
    mico_throw (MARSHAL());
    return 0;
}

void
CORBA::ValueBase::_marshal (CORBA::DataEncoder &ec, ValueBase *vb)
{
    if (!vb) {
	// nil
	ec.value_ref (0);
	return;
    }
    CORBA::DataEncoder::MapValueId::iterator it =
	ec.valuestate()->visited.find (vb);
    if (it != ec.valuestate()->visited.end()) {
	// indirection
	ec.value_ref ((*it).second);
	return;
    }

    vector<string> repoids;
    CORBA::Boolean chunked;
    vb->_get_marshal_info (repoids, chunked);

    Long vid;
    ec.value_begin ("", repoids, chunked, vid);
    ec.valuestate()->visited[vb] = vid;

    vb->_marshal_members (ec);

    ec.value_end (vid);
}

CORBA::Boolean
CORBA::ValueBase::_demarshal (CORBA::DataDecoder &dc, ValueBase *&vb,
			      const string &repoid)
{
    string url;
    vector<string> repoids;
    CORBA::Long vid;
    CORBA::Boolean is_ref;

    if (!dc.value_begin (url, repoids, vid, is_ref))
	return FALSE;

    if (is_ref) {
	if (!vid) {
	    // nil
	    vb = 0;
	    return TRUE;
	}
	// indirection
	CORBA::DataDecoder::MapIdValue::iterator it =
	    dc.valuestate()->visited.find (vid);
	if (it == dc.valuestate()->visited.end())
	    // bad encoding ...
	    return FALSE;
	vb = (*it).second;
	CORBA::add_ref (vb);
	return TRUE;
    }

    vb = CORBA::ValueBase::_create (repoids, repoid);
    if (!vb)
	// no implementation ...
	return FALSE;

    dc.valuestate()->visited[vid] = vb;

    if (!vb->_demarshal_members (dc))
	return FALSE;

    return dc.value_end (vid);
}

CORBA::ValueBase *
CORBA::ValueBase::_copy_value ()
{
  MICO::SimpleEncoder ec;
  MICO::SimpleDecoder dc (ec.buffer(), FALSE);
  CORBA::DataEncoder::ValueState evstate;
  CORBA::DataDecoder::ValueState dvstate;

  CORBA::ValueBase * res;
  CORBA::Boolean ret;
  vector<string> repoids;

  ec.valuestate (&evstate, FALSE);
  dc.valuestate (&dvstate, FALSE);
  _get_marshal_info (repoids, ret);

  _marshal (ec, this);
  ret = _demarshal (dc, res, repoids[0]);
  assert (ret);
  return res;
}

void
CORBA::ValueBase::_get_marshal_info (vector<string> &, Boolean &)
{
    // must be implemented for each valuetype class when using the SII
    assert (0);
}

void
CORBA::ValueBase::_marshal_members (DataEncoder &)
{
    // must be implemented for each valuetype class when using the SII
    assert (0);
}

CORBA::Boolean
CORBA::ValueBase::_demarshal_members (DataDecoder &)
{
    // must be implemented for each valuetype class when using the SII
    assert (0);
    return FALSE;
}

CORBA::Long
CORBA::ValueBase::_count_refs (visited *)
{
  return 0;
}

void
CORBA::ValueBase::_release_members ()
{
}

//-------------------


CORBA::ValueFactoryBase::ValueFactoryBase ()
{
}

CORBA::ValueFactoryBase::~ValueFactoryBase ()
{
}

CORBA::ValueFactory
CORBA::ValueFactoryBase::_downcast (ValueFactory vf)
{
  return vf;
}

void *
CORBA::ValueFactoryBase::_narrow_helper (const char *)
{
  return 0;
}


//-------------------


#if 0
CORBA::ValueFactoryBase_var::ValueFactoryBase_var ()
{
  _ptr = NULL;
}

CORBA::ValueFactoryBase_var::ValueFactoryBase_var (ValueFactoryBase * serv)
{
  _ptr = serv;
}

CORBA::ValueFactoryBase_var::ValueFactoryBase_var (const ValueFactoryBase_var & o)
{
  if ((_ptr = o._ptr) != NULL) {
    _ptr->_add_ref ();
  }
}

CORBA::ValueFactoryBase_var::~ValueFactoryBase_var ()
{
  if (_ptr) {
    _ptr->_remove_ref ();
  }
}

CORBA::ValueFactoryBase_var &
CORBA::ValueFactoryBase_var::operator= (ValueFactoryBase * p)
{
  if (_ptr) {
    _ptr->_remove_ref ();
  }
  _ptr = p;
  return *this;
}

CORBA::ValueFactoryBase_var &
CORBA::ValueFactoryBase_var::operator= (const ValueFactoryBase_var & o)
{
  if (_ptr != o._ptr) {
    if (_ptr) {
      _ptr->_remove_ref ();
    }
    if ((_ptr = o._ptr) != NULL) {
      _ptr->_add_ref ();
    }
  }
  return *this;
}

CORBA::ValueFactoryBase_var::operator CORBA::ValueFactoryBase * () const
{
  if (_ptr) {
    _ptr->_check ();
  }
  return _ptr;
}

CORBA::ValueFactoryBase *
CORBA::ValueFactoryBase_var::operator-> () const
{
  if (_ptr) {
    _ptr->_check ();
  }
  return _ptr;
}

CORBA::ValueFactoryBase *
CORBA::ValueFactoryBase_var::in () const
{
  if (_ptr) {
    _ptr->_check ();
  }
  return _ptr;
}

CORBA::ValueFactoryBase *&
CORBA::ValueFactoryBase_var::inout ()
{
  if (_ptr) {
    _ptr->_check ();
  }
  return _ptr;
}

CORBA::ValueFactoryBase *&
CORBA::ValueFactoryBase_var::out ()
{
  return _ptr;
}

CORBA::ValueFactoryBase *
CORBA::ValueFactoryBase_var::_retn ()
{
  CORBA::ValueFactoryBase * rv = _ptr;
  _ptr = NULL;
  if (rv) {
    rv->_check();
  }
  return rv;
}
#endif


//-------------------


CORBA::ValueFactory
CORBA::ORB::register_value_factory (const char *repoid, ValueFactory factory)
{
    ValueFactory vf = lookup_value_factory (repoid);
    factory->_add_ref();
    _value_facs[repoid] = factory;
    return vf;
}

void
CORBA::ORB::unregister_value_factory (const char *repoid)
{
    _value_facs.erase (repoid);
}

CORBA::ValueFactory
CORBA::ORB::lookup_value_factory (const char *repoid)
{
    ValueFactoryMap::iterator i = _value_facs.find (repoid);
    if (i == _value_facs.end())
	return 0;
    ValueFactory vf = (*i).second.in();
    vf->_add_ref();
    return vf;
}

/*
 * Abstract Interface Stuff
 */

CORBA::AbstractBase::AbstractBase ()
{
}

CORBA::AbstractBase::AbstractBase (const AbstractBase &)
{
}

CORBA::AbstractBase::~AbstractBase ()
{
}

CORBA::AbstractBase_ptr
CORBA::AbstractBase::_duplicate (AbstractBase_ptr ab)
{
  if (!CORBA::is_nil (ab)) {
    Object_ptr obj = ab->_to_object ();
    ValueBase * val = ab->_to_value ();
    if (!CORBA::is_nil (obj)) {
      obj = Object::_duplicate (obj);
    }
    else if (val != 0) {
      CORBA::add_ref (val);
    }
  }

  return ab;
}

CORBA::AbstractBase_ptr
CORBA::AbstractBase::_narrow (AbstractBase_ptr ab)
{
  return _duplicate (ab);
}

CORBA::Object_ptr
CORBA::AbstractBase::_to_object ()
{
  return Object::_nil ();
}

CORBA::ValueBase *
CORBA::AbstractBase::_to_value ()
{
  return 0;
}

void
CORBA::AbstractBase::_marshal (DataEncoder &ec, AbstractBase *ab)
{
  Object_ptr obj;
  ValueBase * val;

  if (!CORBA::is_nil (ab)) {
    obj = ab->_to_object ();
    val = ab->_to_value ();
  }
  else {
    obj = Object::_nil ();
    val = 0;
  }

  ec.union_begin();
  if (!CORBA::is_nil (obj)) {
    ec.put_boolean (TRUE);
    CORBA::_stc_Object->marshal( ec, &obj );
  }
  else {
    ec.put_boolean (FALSE);
    CORBA::_stc_ValueBase->marshal( ec, &val );
  }
  ec.union_end();
}

CORBA::Boolean
CORBA::AbstractBase::_demarshal (DataDecoder &dc, AbstractBase *&ab)
{
  Boolean is_objref;

  if (!dc.union_begin()) {
    return FALSE;
  }
  if (!CORBA::_stc_boolean->demarshal (dc, &is_objref)) {
    return FALSE;
  }
  if (is_objref) {
    Object_ptr obj;
    if (!CORBA::_stc_Object->demarshal (dc, &obj)) {
      return FALSE;
    }
    ab = new UnknownAbstract (obj, 0);
  }
  else {
    ValueBase * val;
    if (!CORBA::_stc_ValueBase->demarshal (dc, &val)) {
      return FALSE;
    }
    if (val) {
      ab = new UnknownAbstract (Object::_nil(), val);
    }
    else {
      ab = 0;
    }
  }

  return dc.union_end();
}

void *
CORBA::AbstractBase::_narrow_helper (const char *)
{
  return 0;
}

void
CORBA::release (AbstractBase_ptr ab)
{
  if (!CORBA::is_nil (ab)) {
    Object_ptr obj = ab->_to_object ();
    ValueBase * val = ab->_to_value ();
    if (!CORBA::is_nil (obj)) {
      CORBA::release (obj);
    }
    else if (val != 0) {
      CORBA::remove_ref (val);
    }
  }
}

CORBA::MixedBase::~MixedBase ()
{
}

CORBA::UnknownAbstract::UnknownAbstract (CORBA::Object_ptr _o,
					 CORBA::ValueBase * _v)
{
  obj = _o;
  val = _v;
}

CORBA::UnknownAbstract::~UnknownAbstract ()
{
}

CORBA::Object_ptr
CORBA::UnknownAbstract::_to_object ()
{
  return obj;
}

CORBA::ValueBase *
CORBA::UnknownAbstract::_to_value ()
{
  return val;
}

void *
CORBA::UnknownAbstract::_narrow_helper (const char * repoid)
{
  if (!CORBA::is_nil (obj)) {
    return obj->_narrow_helper (repoid);
  }
  if (val) {
    return val->_narrow_helper (repoid);
  }
  return 0;
}
