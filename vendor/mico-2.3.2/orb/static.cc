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

#define MICO_CONF_IMR

#include <CORBA-SMALL.h>
#include <string.h>
#include <mico/throw.h>
#include <mico/util.h>
#include <mico/impl.h>
#include <mico/intercept.h>
#include <mico/template_impl.h>


//----------------


CORBA::StaticTypeInfo::~StaticTypeInfo ()
{
}

CORBA::StaticValueType
CORBA::StaticTypeInfo::copy (const StaticValueType v) const
{
    StaticValueType nv = create();
    assign (nv, v);
    return nv;
}

CORBA::TypeCode_ptr
CORBA::StaticTypeInfo::typecode ()
{
    return CORBA::TypeCode::_nil();
}


//----------------


CORBA::StaticAny::StaticAny (const StaticAny &a)
    : _info (a._info),
      _val (a._val ? a._info->copy (a._val) : 0),
      _dofree (TRUE)
{
}

CORBA::StaticAny &
CORBA::StaticAny::operator= (const StaticAny &a)
{
    if (this != &a) {
	// this and a must have same type
	assert (_info == a._info);
	if (_val) {
	    if (a._val) {
		_info->assign (_val, a._val);
	    } else {
		StaticValueType v = _info->create();
		_info->assign (_val, v);
		_info->free (v);
	    }
	} else if (a._val) {
	    _val = a._info->copy (a._val);
	    _dofree = TRUE;
	}
    }
    return *this;
}

CORBA::StaticAny::~StaticAny ()
{
    if (_dofree && _val)
	_info->free (_val);
}

void
CORBA::StaticAny::value (StaticTypeInfo *info, ConstStaticValueType val,
			 CORBA::Boolean dofree)
{
    if (_dofree && _val)
	_info->free (_val);
    _info = info;
    _val = (StaticValueType)val;
    _dofree = dofree;
}

CORBA::StaticValueType
CORBA::StaticAny::_retn ()
{
    StaticValueType val = _val;
    _val = 0;
    return val;
}

CORBA::Boolean
CORBA::StaticAny::demarshal (CORBA::DataDecoder &dc)
{
    if (!_val) {
	_val = _info->create();
	_dofree = TRUE;
    }
    return _info->demarshal (dc, _val);
}

CORBA::Boolean
CORBA::StaticAny::marshal (CORBA::DataEncoder &ec)
{
    if (!_val) {
	_val = _info->create();
	_dofree = TRUE;
    }
    _info->marshal (ec, _val);
    return TRUE;
}


//-----------------


struct TCVoid : public CORBA::StaticTypeInfo {
    StaticValueType create () const
    { return 0; }
    StaticValueType copy (const StaticValueType v) const
    { return 0; }
    void assign (StaticValueType d, const StaticValueType s) const
    {}
    void free (StaticValueType v) const
    {}
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return TRUE; }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {}
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_void; }
};


//-----------------


class TCShort : public CORBA::StaticTypeInfo {
    typedef CORBA::Short _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_short (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_short (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_short; }
};


//-----------------


class TCLong : public CORBA::StaticTypeInfo {
    typedef CORBA::Long _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_long (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_long (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_long; }
};


//-----------------


class TCLongLong : public CORBA::StaticTypeInfo {
    typedef CORBA::LongLong _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_longlong (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_longlong (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_longlong; }
};


//-----------------


class TCUShort : public CORBA::StaticTypeInfo {
    typedef CORBA::UShort _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_ushort (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_ushort (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_ushort; }
};


//-----------------


class TCULong : public CORBA::StaticTypeInfo {
    typedef CORBA::ULong _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_ulong (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_ulong (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_ulong; }
};


//-----------------


class TCULongLong : public CORBA::StaticTypeInfo {
    typedef CORBA::ULongLong _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_ulonglong (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_ulonglong (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_ulonglong; }
};


//-----------------


class TCFloat : public CORBA::StaticTypeInfo {
    typedef CORBA::Float _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_float (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_float (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_float; }
};


//-----------------


class TCDouble : public CORBA::StaticTypeInfo {
    typedef CORBA::Double _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_double (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_double (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_double; }
};


//-----------------


class TCLongDouble : public CORBA::StaticTypeInfo {
    typedef CORBA::LongDouble _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v);}
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_longdouble (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_longdouble (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_longdouble; }
};


//-----------------


class TCChar : public CORBA::StaticTypeInfo {
    typedef CORBA::Char _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_char (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_char (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_char; }
};


//-----------------


class TCWChar : public CORBA::StaticTypeInfo {
    typedef CORBA::WChar _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_wchar (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_wchar (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_wchar; }
};


//-----------------


class TCOctet : public CORBA::StaticTypeInfo {
    typedef CORBA::Octet _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_octet (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_octet (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_octet; }
};


//-----------------


class TCBoolean : public CORBA::StaticTypeInfo {
    typedef CORBA::Boolean _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_boolean (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_boolean (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_boolean; }
};


//-----------------


class TCString : public CORBA::StaticTypeInfo {
    typedef char *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (CORBA::string_dup (*(_MICO_T *)v)); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = CORBA::string_dup (*(_MICO_T *)s); }
    void free (StaticValueType v) const
    { CORBA::string_free (*(_MICO_T *)v); delete (_MICO_T *)v; }
    // XXX calling this multiple times with same v causes mem leaks
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_string (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_string (*(_MICO_T *)v ? *(_MICO_T *)v : ""); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_string; }
};


//------------------


class TCWString : public CORBA::StaticTypeInfo {
    typedef wchar_t *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (CORBA::wstring_dup (*(_MICO_T *)v)); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = CORBA::wstring_dup (*(_MICO_T *)s); }
    void free (StaticValueType v) const
    { CORBA::wstring_free (*(_MICO_T *)v); delete (_MICO_T *)v; }
    // XXX calling this multiple times with same v causes mem leaks
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_wstring (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_wstring (*(_MICO_T *)v ? *(_MICO_T *)v : L""); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_wstring; }
};


//-----------------


class TCAny : public CORBA::StaticTypeInfo {
    typedef CORBA::Any _MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    { return dc.get_any (*(_MICO_T *)v); }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    { ec.put_any (*(_MICO_T *)v); }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_any; }
};


//-----------------


class TCTypeCode : public CORBA::StaticTypeInfo {
    typedef CORBA::TypeCode *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (CORBA::TypeCode::_duplicate (*(_MICO_T *)v)); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = CORBA::TypeCode::_duplicate (*(_MICO_T *)s); }
    void free (StaticValueType v) const
    { CORBA::release (*(_MICO_T *)v); delete (_MICO_T *)v; }
    // XXX calling this multiple times with same v causes mem leaks
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	*(_MICO_T *)v = new CORBA::TypeCode;
	return dc.get_typecode (**(_MICO_T *)v);
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	if (*(_MICO_T *)v)
	    ec.put_typecode (**(_MICO_T *)v);
	else {
	    CORBA::TypeCode tc;
	    ec.put_typecode (tc);
	}
    }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_TypeCode; }
};


//-----------------


class TCPrincipal : public CORBA::StaticTypeInfo {
    typedef CORBA::Principal *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (CORBA::Principal::_duplicate (*(_MICO_T *)v)); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = CORBA::Principal::_duplicate (*(_MICO_T *)s); }
    void free (StaticValueType v) const
    { CORBA::release (*(_MICO_T *)v); delete (_MICO_T *)v; }
    // XXX calling this multiple times with same v causes mem leaks
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	*(_MICO_T *)v = new CORBA::Principal;
	return dc.get_principal (**(_MICO_T *)v);
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	if (*(_MICO_T *)v)
	    ec.put_principal (**(_MICO_T *)v);
	else {
	    CORBA::Principal pr;
	    ec.put_principal (pr);
	}
    }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_Principal; }
};


//-----------------


class TCContext : public CORBA::StaticTypeInfo {
    typedef CORBA::Context *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (CORBA::Context::_duplicate (*(_MICO_T *)v)); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = CORBA::Context::_duplicate (*(_MICO_T *)s); }
    void free (StaticValueType v) const
    { CORBA::release (*(_MICO_T *)v); delete (_MICO_T *)v; }
    // XXX calling this multiple times with same v causes mem leaks
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	*(_MICO_T *)v = new CORBA::Context ("");
	return dc.get_context (**(_MICO_T *)v);
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	if (*(_MICO_T *)v)
	    ec.put_context (**(_MICO_T *)v);
	else {
	    CORBA::Context ctx ("");
	    ec.put_context (ctx);
	}
    }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_Context; }
};


//-----------------


class TCObject : public CORBA::StaticTypeInfo {
    typedef CORBA::Object *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (CORBA::Object::_duplicate (*(_MICO_T *)v)); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = CORBA::Object::_duplicate (*(_MICO_T *)s); }
    void free (StaticValueType v) const
    { CORBA::release (*(_MICO_T *)v); delete (_MICO_T *)v; }
    // XXX calling this multiple times with same v causes mem leaks
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::IOR *ior = new CORBA::IOR;
	if (!dc.get_ior (*ior)) {
	    delete ior;
	    return FALSE;
	}
	CORBA::ORB_var orb = CORBA::ORB_instance ("mico-local-orb");
	*(_MICO_T *)v = orb->ior_to_object (ior);
	return TRUE;
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	if (*(_MICO_T *)v) {
	    /*
	     * XXX should raise MARSHAL for locality constrained objects,
	     * but this would require a bool return value for all marshal
	     * methods ...
	     */
	    assert ((*(_MICO_T *)v)->_ior());
	    ec.put_ior (*(*(_MICO_T *)v)->_ior());
	} else {
	    CORBA::IOR ior;
	    ec.put_ior (ior);
	}
    }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_Object; }
};


//-----------------


class TCValueBase : public CORBA::StaticTypeInfo {
    typedef CORBA::ValueBase *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { CORBA::add_ref (*(_MICO_T *)v); return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { CORBA::add_ref (*(_MICO_T *)s); *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { CORBA::remove_ref (*(_MICO_T *)v); delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	return CORBA::ValueBase::_demarshal (
	    dc, *(_MICO_T *)v, "IDL:omg.org/CORBA/ValueBase:1.0");
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ValueBase::_marshal (ec, *(_MICO_T *)v);
    }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_ValueBase; }
};


//-----------------


class TCAbstractBase : public CORBA::StaticTypeInfo {
    typedef CORBA::AbstractBase *_MICO_T;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T (0); }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (CORBA::AbstractBase::_duplicate (*(_MICO_T *)v)); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = CORBA::AbstractBase::_duplicate (*(_MICO_T *)s); }
    void free (StaticValueType v) const
    { CORBA::release (*(_MICO_T *)v); delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	return CORBA::AbstractBase::_demarshal (dc, *(_MICO_T *)v);
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::AbstractBase::_marshal (ec, *(_MICO_T *)v);
    }
    CORBA::TypeCode_ptr typecode ()
    { return CORBA::_tc_AbstractBase; }
};


//-----------------


class TCSeqShort : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Short,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_shorts (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_shorts (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_short)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqShort::_tc = 0;

//-----------------


class TCSeqLong : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Long,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_longs (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_longs (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_long)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqLong::_tc = 0;


//-----------------


class TCSeqLongLong : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::LongLong,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_longlongs (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_longlongs (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_longlong)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqLongLong::_tc = 0;


//-----------------


class TCSeqUShort : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::UShort,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_ushorts (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_ushorts (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_ushort)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqUShort::_tc = 0;


//-----------------


class TCSeqULong : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::ULong,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_ulongs (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_ulongs (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_ulong)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqULong::_tc = 0;


//-----------------


class TCSeqULongLong : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::ULongLong,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_ulonglongs (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_ulonglongs (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_ulonglong)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqULongLong::_tc = 0;


//-----------------


class TCSeqFloat : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Float,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_floats (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_floats (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_float)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqFloat::_tc = 0;


//-----------------


class TCSeqDouble : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Double,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_doubles (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_doubles (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_double)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqDouble::_tc = 0;


//-----------------


class TCSeqLongDouble : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::LongDouble,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_longdoubles (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_longdoubles (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc(0, CORBA::_tc_longdouble)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqLongDouble::_tc = 0;


//-----------------


class TCSeqChar : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Char,MICO_TID_CHAR> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_chars ((CORBA::Char *)&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_chars ((CORBA::Char *)&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_char)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqChar::_tc = 0;


//-----------------


class TCSeqWChar : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::WChar,MICO_TID_WCHAR> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_wchars (&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_wchars (&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_wchar)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqWChar::_tc = 0;


//-----------------


class TCSeqBoolean : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Boolean,MICO_TID_BOOL> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_booleans ((CORBA::Boolean *)&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_booleans ((CORBA::Boolean *)&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_boolean)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqBoolean::_tc = 0;


//-----------------


class TCSeqAny : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Any,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    if (!dc.get_any ((*(_MICO_T *)v)[i]))
		return FALSE;
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    ec.put_any ((*(_MICO_T *)v)[i]);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_any)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqAny::_tc = 0;


//-----------------


class TCSeqOctet : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	if (len > 0) {
	    if (!dc.get_octets ((CORBA::Octet *)&(*(_MICO_T *)v)[0], len))
		return FALSE;
	}
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	if (len > 0)
	    ec.put_octets ((CORBA::Octet *)&(*(_MICO_T *)v)[0], len);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_octet)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqOctet::_tc = 0;


//-----------------


class TCSeqString : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::String_var,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    if (!dc.get_string ((*(_MICO_T *)v)[i].out()))
		return FALSE;
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    ec.put_string ((*(_MICO_T *)v)[i]);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_string)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqString::_tc = 0;


//-----------------


class TCSeqWString : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::WString_var,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    if (!dc.get_wstring ((*(_MICO_T *)v)[i]))
		return FALSE;
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    ec.put_wstring ((*(_MICO_T *)v)[i]);
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_wstring)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqWString::_tc = 0;


//-----------------


class TCSeqObject : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::Object_var,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    if (!CORBA::_stc_Object->demarshal (dc, &((*(_MICO_T *)v)[i]).inout()))
		return FALSE;
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    CORBA::_stc_Object->marshal (ec, &((*(_MICO_T *)v)[i]).inout());
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_Object)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqObject::_tc = 0;


//-----------------


class TCSeqValueBase : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::ValueBase_var,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    if (!CORBA::_stc_ValueBase->demarshal (dc, &((*(_MICO_T*)v)[i]).inout()))
		return FALSE;
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    CORBA::_stc_ValueBase->marshal (ec, &((*(_MICO_T *)v)[i]).inout());
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_ValueBase)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqValueBase::_tc = 0;


//-----------------


class TCSeqAbstractBase : public CORBA::StaticTypeInfo {
    typedef SequenceTmpl<CORBA::AbstractBase_var,MICO_TID_DEF> _MICO_T;
    static CORBA::TypeCode_ptr _tc;
public:
    StaticValueType create () const
    { return (StaticValueType)new _MICO_T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new _MICO_T (*(_MICO_T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(_MICO_T *)d = *(_MICO_T *)s; }
    void free (StaticValueType v) const
    { delete (_MICO_T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	CORBA::ULong len;
	if (!dc.seq_begin (len))
	    return FALSE;
	((_MICO_T *)v)->length (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    if (!CORBA::_stc_AbstractBase->demarshal (dc, &((*(_MICO_T*)v)[i]).inout()))
		return FALSE;
	return dc.seq_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	CORBA::ULong len = ((_MICO_T *)v)->length();
	ec.seq_begin (len);
	for (CORBA::ULong i = 0; i < len; ++i)
	    CORBA::_stc_AbstractBase->marshal (ec, &((*(_MICO_T *)v)[i]).inout());
	ec.seq_end ();
    }
    CORBA::TypeCode_ptr typecode ()
    {
	if (!_tc)
	    _tc = CORBA::TypeCode::create_sequence_tc (0, CORBA::_tc_AbstractBase)
		->mk_constant();
	return _tc;
    }
};
CORBA::TypeCode_ptr TCSeqAbstractBase::_tc = 0;


//-------------------


#ifdef HAVE_NAMESPACE
namespace CORBA {
    CORBA::StaticTypeInfo *_stc_void;
    CORBA::StaticTypeInfo *_stc_short;
    CORBA::StaticTypeInfo *_stc_long;
    CORBA::StaticTypeInfo *_stc_longlong;
    CORBA::StaticTypeInfo *_stc_ushort;
    CORBA::StaticTypeInfo *_stc_ulong;
    CORBA::StaticTypeInfo *_stc_ulonglong;
    CORBA::StaticTypeInfo *_stc_float;
    CORBA::StaticTypeInfo *_stc_double;
    CORBA::StaticTypeInfo *_stc_longdouble;
    CORBA::StaticTypeInfo *_stc_char;
    CORBA::StaticTypeInfo *_stc_wchar;
    CORBA::StaticTypeInfo *_stc_octet;
    CORBA::StaticTypeInfo *_stc_boolean;
    CORBA::StaticTypeInfo *_stc_string;
    CORBA::StaticTypeInfo *_stc_wstring;
    CORBA::StaticTypeInfo *_stc_any;
    CORBA::StaticTypeInfo *_stc_TypeCode;
    CORBA::StaticTypeInfo *_stc_Principal;
    CORBA::StaticTypeInfo *_stc_Context;
    CORBA::StaticTypeInfo *_stc_Object;
    CORBA::StaticTypeInfo *_stc_ValueBase;
    CORBA::StaticTypeInfo *_stc_AbstractBase;
    CORBA::StaticTypeInfo *_stcseq_short;
    CORBA::StaticTypeInfo *_stcseq_long;
    CORBA::StaticTypeInfo *_stcseq_longlong;
    CORBA::StaticTypeInfo *_stcseq_ushort;
    CORBA::StaticTypeInfo *_stcseq_ulong;
    CORBA::StaticTypeInfo *_stcseq_ulonglong;
    CORBA::StaticTypeInfo *_stcseq_float;
    CORBA::StaticTypeInfo *_stcseq_double;
    CORBA::StaticTypeInfo *_stcseq_longdouble;
    CORBA::StaticTypeInfo *_stcseq_char;
    CORBA::StaticTypeInfo *_stcseq_wchar;
    CORBA::StaticTypeInfo *_stcseq_octet;
    CORBA::StaticTypeInfo *_stcseq_boolean;
    CORBA::StaticTypeInfo *_stcseq_any;
    CORBA::StaticTypeInfo *_stcseq_string;
    CORBA::StaticTypeInfo *_stcseq_wstring;
    CORBA::StaticTypeInfo *_stcseq_Object;
    CORBA::StaticTypeInfo *_stcseq_ValueBase;
    CORBA::StaticTypeInfo *_stcseq_AbstractBase;
};
#else
CORBA::StaticTypeInfo *CORBA::_stc_void;
CORBA::StaticTypeInfo *CORBA::_stc_short;
CORBA::StaticTypeInfo *CORBA::_stc_long;
CORBA::StaticTypeInfo *CORBA::_stc_longlong;
CORBA::StaticTypeInfo *CORBA::_stc_ushort;
CORBA::StaticTypeInfo *CORBA::_stc_ulong;
CORBA::StaticTypeInfo *CORBA::_stc_ulonglong;
CORBA::StaticTypeInfo *CORBA::_stc_float;
CORBA::StaticTypeInfo *CORBA::_stc_double;
CORBA::StaticTypeInfo *CORBA::_stc_longdouble;
CORBA::StaticTypeInfo *CORBA::_stc_char;
CORBA::StaticTypeInfo *CORBA::_stc_wchar;
CORBA::StaticTypeInfo *CORBA::_stc_octet;
CORBA::StaticTypeInfo *CORBA::_stc_boolean;
CORBA::StaticTypeInfo *CORBA::_stc_string;
CORBA::StaticTypeInfo *CORBA::_stc_wstring;
CORBA::StaticTypeInfo *CORBA::_stc_any;
CORBA::StaticTypeInfo *CORBA::_stc_TypeCode;
CORBA::StaticTypeInfo *CORBA::_stc_Principal;
CORBA::StaticTypeInfo *CORBA::_stc_Context;
CORBA::StaticTypeInfo *CORBA::_stc_Object;
CORBA::StaticTypeInfo *CORBA::_stc_ValueBase;
CORBA::StaticTypeInfo *CORBA::_stc_AbstractBase;
CORBA::StaticTypeInfo *CORBA::_stcseq_short;
CORBA::StaticTypeInfo *CORBA::_stcseq_long;
CORBA::StaticTypeInfo *CORBA::_stcseq_longlong;
CORBA::StaticTypeInfo *CORBA::_stcseq_ushort;
CORBA::StaticTypeInfo *CORBA::_stcseq_ulong;
CORBA::StaticTypeInfo *CORBA::_stcseq_ulonglong;
CORBA::StaticTypeInfo *CORBA::_stcseq_float;
CORBA::StaticTypeInfo *CORBA::_stcseq_double;
CORBA::StaticTypeInfo *CORBA::_stcseq_longdouble;
CORBA::StaticTypeInfo *CORBA::_stcseq_char;
CORBA::StaticTypeInfo *CORBA::_stcseq_wchar;
CORBA::StaticTypeInfo *CORBA::_stcseq_octet;
CORBA::StaticTypeInfo *CORBA::_stcseq_boolean;
CORBA::StaticTypeInfo *CORBA::_stcseq_any;
CORBA::StaticTypeInfo *CORBA::_stcseq_string;
CORBA::StaticTypeInfo *CORBA::_stcseq_wstring;
CORBA::StaticTypeInfo *CORBA::_stcseq_Object;
CORBA::StaticTypeInfo *CORBA::_stcseq_ValueBase;
CORBA::StaticTypeInfo *CORBA::_stcseq_AbstractBase;
#endif

static struct InitStaticTypeInfo {
    InitStaticTypeInfo()
    {
	CORBA::_stc_void = new TCVoid;
	CORBA::_stc_short = new TCShort;
	CORBA::_stc_long = new TCLong;
	CORBA::_stc_longlong = new TCLongLong;
	CORBA::_stc_ushort = new TCUShort;
	CORBA::_stc_ulong = new TCULong;
	CORBA::_stc_ulonglong = new TCULongLong;
	CORBA::_stc_float = new TCFloat;
	CORBA::_stc_double = new TCDouble;
	CORBA::_stc_longdouble = new TCLongDouble;
	CORBA::_stc_char = new TCChar;
	CORBA::_stc_wchar = new TCWChar;
	CORBA::_stc_octet = new TCOctet;
	CORBA::_stc_boolean = new TCBoolean;
	CORBA::_stc_string = new TCString;
	CORBA::_stc_wstring = new TCWString;
	CORBA::_stc_any = new TCAny;
	CORBA::_stc_TypeCode = new TCTypeCode;
	CORBA::_stc_Principal = new TCPrincipal;
	CORBA::_stc_Context = new TCContext;
	CORBA::_stc_Object = new TCObject;
	CORBA::_stc_ValueBase = new TCValueBase;
	CORBA::_stc_AbstractBase = new TCAbstractBase;
	CORBA::_stcseq_short = new TCSeqShort;
	CORBA::_stcseq_long = new TCSeqLong;
	CORBA::_stcseq_longlong = new TCSeqLongLong;
	CORBA::_stcseq_ushort = new TCSeqUShort;
	CORBA::_stcseq_ulong = new TCSeqULong;
	CORBA::_stcseq_ulonglong = new TCSeqULongLong;
	CORBA::_stcseq_float = new TCSeqFloat;
	CORBA::_stcseq_double = new TCSeqDouble;
	CORBA::_stcseq_longdouble = new TCSeqLongDouble;
	CORBA::_stcseq_char = new TCSeqChar;
	CORBA::_stcseq_wchar = new TCSeqWChar;
	CORBA::_stcseq_octet = new TCSeqOctet;
	CORBA::_stcseq_boolean = new TCSeqBoolean;
	CORBA::_stcseq_any = new TCSeqAny;
	CORBA::_stcseq_string = new TCSeqString;
	CORBA::_stcseq_wstring = new TCSeqWString;
	CORBA::_stcseq_Object = new TCSeqObject;
	CORBA::_stcseq_ValueBase = new TCSeqValueBase;
	CORBA::_stcseq_AbstractBase = new TCSeqAbstractBase;
    }
} __init_static_type_info;


//-----------------


CORBA::StaticRequest::StaticRequest (CORBA::Object_ptr obj, const char *opname)
{
    if (!obj->_ior())
	// locality constrained object
	mico_throw (NO_IMPLEMENT());

    _msgid = 0;
    _opname = opname;
    _res = 0;
    _ctx = 0;
    _env = 0;
    _ctx_list = 0;
    _obj = CORBA::Object::_duplicate (obj);

    _iceptreq = Interceptor::ClientInterceptor::_create_request (
	_obj, _opname, *context(), CORBA::Request::_nil());
}

CORBA::StaticRequest::~StaticRequest ()
{
    if (_msgid)
        _obj->_orbnc()->cancel (_msgid);
    CORBA::release (_ctx);
    CORBA::release (_env);
    CORBA::release (_ctx_list);
    CORBA::release (_iceptreq);
}

const char *
CORBA::StaticRequest::op_name()
{
    return _opname;
}

CORBA::Boolean
CORBA::StaticRequest::copy (StaticAnyList *dst, StaticAnyList *src,
			    CORBA::Flags f)
{
    int dst_count = dst->size();
    int src_count = src->size();

    StaticAny *dst_any, *src_any;
    for (int d = 0, s = 0;; ++d, ++s) {
	dst_any = 0;
	for ( ; d < dst_count; ++d) {
	    dst_any = (*dst)[d];
	    if (dst_any->flags() & f)
		break;
	}
	src_any = 0;
	for ( ; s < src_count; ++s) {
	    src_any = (*src)[s];
	    if (src_any->flags() & f)
		break;
	}
	if (s >= src_count || d >= dst_count) {
	    // assertion fails iff #params-to-copy in dst and src differ.
	    if (!(s >= src_count && d >= dst_count))
                return FALSE;
	    break;
	}
	// make sure we have the same type of args
	if (!((src_any->flags() & f) == (dst_any->flags() & f)))
            return FALSE;

	// XXX possibly avoid a copy here ...
	*dst_any = *src_any;
    }
    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::get_in_args (NVList_ptr iparams, Context_ptr &ctx)
{
    if (iparams->count() != _args.size())
	return FALSE;

    CORBA::NamedValue_ptr nv;
    for (mico_vec_size_type i0 = 0; i0 < _args.size(); ++i0) {
	nv = iparams->item (i0);
	if (_args[i0]->flags() != nv->flags())
	    return FALSE;
	if (_args[i0]->flags() & (CORBA::ARG_IN|CORBA::ARG_INOUT)) {
	    nv->value()->from_static_any (*_args[i0]);
	}
    }
    ctx = CORBA::Context::_duplicate (_ctx);
    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::get_in_args (StaticAnyList *iparams,
				   CORBA::Context_ptr &ctx)
{
    if (!copy (iparams, &_args, CORBA::ARG_IN|CORBA::ARG_INOUT))
        return FALSE;
    ctx = CORBA::Context::_duplicate (_ctx);
    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::get_in_args (DataEncoder *ec)
{
    if (_args.size() == 0 && CORBA::is_nil (_ctx))
	return TRUE;

    // share one state for all arguments
    CORBA::DataEncoder::ValueState vstate;
    ec->valuestate (&vstate, FALSE);

    for (mico_vec_size_type i = 0; i < _args.size(); ++i) {
	if (_args[i]->flags() & (CORBA::ARG_IN|CORBA::ARG_INOUT)) {
	    if (!_args[i]->marshal (*ec))
		return FALSE;
	}
    }

    if (!CORBA::is_nil (_ctx))
	ec->put_context (*_ctx, _ctx_list);

    ec->valuestate (0);

    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::get_out_args (Any *res, NVList_ptr oparams,
				    Exception *&ex)
{
    CORBA::Exception *e = exception();
    if (e) {
	ex = e->_clone();
	return TRUE;
    }

    if (oparams->count() != _args.size())
	return FALSE;

    if (res && _res) {
	res->from_static_any (*_res);
    }

    CORBA::NamedValue_ptr nv;
    for (mico_vec_size_type i0 = 0; i0 < _args.size(); ++i0) {
	nv = oparams->item(i0);
	if (_args[i0]->flags() != nv->flags())
	    return FALSE;
	if (_args[i0]->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)) {
	    nv->value()->from_static_any (*_args[i0]);
	}
    }
    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::get_out_args (CORBA::StaticAny *res,
				    StaticAnyList *oparams,
				    CORBA::Exception *&ex)
{
    CORBA::Exception *e = exception();
    if (e) {
	ex = e->_clone();
	return TRUE;
    }
    if (res && _res)
	*res = *_res;
    return copy (oparams, &_args, CORBA::ARG_OUT|CORBA::ARG_INOUT);
}

CORBA::Boolean
CORBA::StaticRequest::get_out_args (DataEncoder *ec, Boolean &is_except)
{
    is_except = FALSE;
    CORBA::Exception *e = exception();

    if (!e && !_res && _args.size() == 0)
	return TRUE;

    // share one state for all arguments
    CORBA::DataEncoder::ValueState vstate;
    ec->valuestate (&vstate, FALSE);

    if (e) {
	is_except = TRUE;
	e->_encode (*ec);
	return TRUE;
    }

    if (_res) {
	if (!_res->marshal (*ec))
	    return FALSE;
    }
    for (mico_vec_size_type i = 0; i < _args.size(); ++i) {
	if (_args[i]->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)) {
	    if (!_args[i]->marshal (*ec))
		return FALSE;
	}
    }
    ec->valuestate (0);

    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::set_out_args (Any *res, NVList_ptr oparams)
{
    if (oparams->count() != _args.size())
	return FALSE;

    if (res && _res) {
	if (!res->to_static_any (*_res))
	    return FALSE;
    }

    CORBA::NamedValue_ptr nv;
    for (mico_vec_size_type i0 = 0; i0 < _args.size(); ++i0) {
	nv = oparams->item(i0);
	if (_args[i0]->flags() != nv->flags())
	    return FALSE;
	if (_args[i0]->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)) {
	    if (!nv->value()->to_static_any (*_args[i0]))
		return FALSE;
	}
    }
    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::set_out_args (CORBA::StaticAny *res,
				    StaticAnyList *oparams)
{
    if (res && _res)
	*_res = *res;
    return copy (&_args, oparams, CORBA::ARG_OUT|CORBA::ARG_INOUT);
}

void
CORBA::StaticRequest::set_out_args (Exception *ex)
{
    exception (ex->_clone());
}

CORBA::Boolean
CORBA::StaticRequest::set_out_args (CORBA::DataDecoder *dc,
				    CORBA::Boolean is_ex)
{
    if (!is_ex && !_res && _args.size() == 0)
	return TRUE;

    CORBA::Boolean ret;

    // share one state for all arguments
    CORBA::DataDecoder::ValueState vstate;
    dc->valuestate (&vstate, FALSE);

    if (is_ex) {
	CORBA::Exception *e = CORBA::Exception::_decode (*dc);
	assert (e);
	exception (e);
    } else {
	if (_res) {
	    ret = _res->demarshal (*dc);
	    if (!ret) {
		dc->valuestate (0);
                return FALSE;
	    }
	}
	for (mico_vec_size_type i = 0; i < _args.size(); ++i) {
	    if (_args[i]->flags() & (CORBA::ARG_OUT|CORBA::ARG_INOUT)) {
		ret = _args[i]->demarshal (*dc);
                if (!ret) {
		    dc->valuestate (0);
                    return FALSE;
		}
	    }
	}
    }
    dc->valuestate (0);
    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::copy_out_args (ORBRequest *r)
{
    if (this == r)
	return TRUE;

    // copy service context list
    copy_svc (r);

    CORBA::Exception *ex;
    if (!r->get_out_args (_res, &_args, ex))
        return FALSE;
    if (ex)
	exception (ex);
    return TRUE;
}

CORBA::Boolean
CORBA::StaticRequest::copy_in_args (ORBRequest *r)
{
    assert (0);
    return FALSE;
}

const char *
CORBA::StaticRequest::type ()
{
    return "static";
}

void
CORBA::StaticRequest::add_in_arg (StaticAny *a)
{
    _args.push_back (a);
    a->flags (CORBA::ARG_IN);
}

void
CORBA::StaticRequest::add_out_arg (StaticAny *a)
{
    _args.push_back (a);
    a->flags (CORBA::ARG_OUT);
}

void
CORBA::StaticRequest::add_inout_arg (StaticAny *a)
{
    _args.push_back (a);
    a->flags (CORBA::ARG_INOUT);
}

void
CORBA::StaticRequest::set_context (CORBA::Context_ptr ctx)
{
    _ctx = CORBA::Context::_duplicate (ctx);
}

void
CORBA::StaticRequest::set_context_list (CORBA::ContextList_ptr ctx_list)
{
    _ctx_list = CORBA::ContextList::_duplicate (ctx_list);
}

CORBA::Exception *
CORBA::StaticRequest::exception ()
{
    if (CORBA::is_nil (_env))
	return 0;
    return _env->exception();
}

void
CORBA::StaticRequest::exception (CORBA::Exception *e)
{
    if (CORBA::is_nil (_env))
	_env = new CORBA::Environment;
    _env->exception (e);
}

CORBA::Environment_ptr
CORBA::StaticRequest::env ()
{
    if (CORBA::is_nil (_env))
	_env = new CORBA::Environment;
    return _env;
}

void
CORBA::StaticRequest::invoke ()
{
    CORBA::ORB_ptr orb = _obj->_orbnc();
    CORBA::Object_var obj;
    CORBA::ORBRequest *dummy;
    CORBA::Boolean done = FALSE;
    CORBA::ULong msgid;

    // no pending invocations please ...
    assert (!_msgid);

    if (_iceptreq && !Interceptor::ClientInterceptor::
	_exec_initialize_request ((Interceptor::LWRequest_ptr)_iceptreq,
				  env())) {
	return;
    }

    msgid = orb->invoke_async (_obj, this, CORBA::Principal::_nil());

    if (_iceptreq && !Interceptor::ClientInterceptor::
	_exec_after_marshal ((Interceptor::LWRequest_ptr)_iceptreq,
			     env())) {
	orb->cancel (msgid);
	return;
    }
    while (!done) {
	CORBA::Boolean ret = orb->wait (msgid);
	assert (ret);

	// XXX called multiple times in case of Forward
	if (_iceptreq && !Interceptor::ClientInterceptor::
	    _exec_before_unmarshal ((Interceptor::LWRequest_ptr)_iceptreq,
				    env())) {
	    orb->cancel (msgid);
	    return;
	}

	CORBA::InvokeStatus rs = orb->get_invoke_reply (msgid, obj, dummy);
	switch (rs) {
	case CORBA::InvokeForward:
	    // XXX what if _obj is not a stub ???
	    assert (_obj.in() && obj.in());
	    _obj->_forward (obj);
	    msgid = orb->invoke_async (_obj, this, Principal::_nil());
	    break;

	case CORBA::InvokeOk:
	case CORBA::InvokeUsrEx:
	    done = TRUE;
	    break;

	case CORBA::InvokeSysEx:
	    if (_obj->_is_forwarded()) {
		/*
		 * [15-44] says:
		 * "the only object address a client should
		 *  expect to continue working reliably is
		 *  the initial unforwarded address".
		 *
		 * Therefore when a system exception is raised
		 * during an invocation on the forwarded address
		 * and the invocation is not completed we fall
		 * back to the initial address and retry the
		 * invocation.
		 */
		CORBA::SystemException *sysex =
		    CORBA::SystemException::EXCEPTION_DOWNCAST (exception());
		assert (sysex);
		if (sysex->completed() == CORBA::COMPLETED_NO &&
                    (CORBA::COMM_FAILURE::EXCEPTION_DOWNCAST (sysex) ||
                     CORBA::TRANSIENT::EXCEPTION_DOWNCAST (sysex) ||
                     CORBA::OBJECT_NOT_EXIST::EXCEPTION_DOWNCAST (sysex))) {
                    _obj->_unforward();
                    env()->clear();
                    msgid = orb->invoke_async (_obj, this,
                                               Principal::_nil());
                    break;
		}
	    }
	    done = TRUE;
	    break;

	default:
	    assert (0);
	}
    }

    if (_iceptreq) {
	Interceptor::ClientInterceptor::
	    _exec_finish_request ((Interceptor::LWRequest_ptr)_iceptreq,
				  env());
    }
}

void
CORBA::StaticRequest::oneway ()
{
    if (_iceptreq && !Interceptor::ClientInterceptor::
	_exec_initialize_request ((Interceptor::LWRequest_ptr)_iceptreq,
				  env())) {
	return;
    }
    _obj->_orbnc()->invoke_async (_obj, this, CORBA::Principal::_nil(), FALSE);

    if (_iceptreq) {
	Interceptor::ClientInterceptor::
	    _exec_after_marshal ((Interceptor::LWRequest_ptr)_iceptreq,
				 env());
    }
}

void
CORBA::StaticRequest::send_deferred ()
{
    CORBA::ORB_ptr orb = _obj->_orbnc();

    if (_iceptreq && !Interceptor::ClientInterceptor::
	_exec_initialize_request ((Interceptor::LWRequest_ptr)_iceptreq,
				  env())) {
        _msgid = 0;
	return;
    }

    _msgid = orb->invoke_async (_obj, this, CORBA::Principal::_nil());

    if (_iceptreq && !Interceptor::ClientInterceptor::
	_exec_after_marshal ((Interceptor::LWRequest_ptr)_iceptreq,
			     env())) {
	orb->cancel (_msgid);
	_msgid = 0;
    }
}

void
CORBA::StaticRequest::get_response ()
{
    CORBA::ORB_ptr orb = _obj->_orbnc();
    CORBA::Object_var obj;
    CORBA::ORBRequest *dummy;
    CORBA::Boolean done = FALSE;

    assert (_msgid);

    while (!done) {
	CORBA::Boolean ret = orb->wait (_msgid);
	assert (ret);

	// XXX called multiple times in case of Forward
	if (_iceptreq && !Interceptor::ClientInterceptor::
	    _exec_before_unmarshal ((Interceptor::LWRequest_ptr)_iceptreq,
				    env())) {
	    orb->cancel (_msgid);
            _msgid = 0;
	    return;
	}

	CORBA::InvokeStatus rs = orb->get_invoke_reply (_msgid, obj, dummy);
	switch (rs) {
	case CORBA::InvokeForward:
	    // XXX what if _obj is not a stub ???
	    assert (_obj.in() && obj.in());
	    _obj->_forward (obj);
	    _msgid = orb->invoke_async (obj, this, Principal::_nil());
	    break;

	case CORBA::InvokeOk:
	case CORBA::InvokeUsrEx:
	    done = TRUE;
	    break;

	case CORBA::InvokeSysEx:
	    if (_obj->_is_forwarded()) {
		/*
		 * [15-44] says:
		 * "the only object address a client should
		 *  expect to continue working reliably is
		 *  the initial unforwarded address".
		 *
		 * Therefore when a system exception is raised
		 * during an invocation on the forwarded address
		 * and the invocation is not completed we fall
		 * back to the initial address and retry the
		 * invocation.
		 */
		CORBA::SystemException *sysex =
		    CORBA::SystemException::EXCEPTION_DOWNCAST (exception());
		assert (sysex);
		if (sysex->completed() == CORBA::COMPLETED_NO &&
                    (CORBA::COMM_FAILURE::EXCEPTION_DOWNCAST (sysex) ||
                     CORBA::TRANSIENT::EXCEPTION_DOWNCAST (sysex) ||
                     CORBA::OBJECT_NOT_EXIST::EXCEPTION_DOWNCAST (sysex))) {
                    _obj->_unforward();
                    env()->clear();
                    _msgid = orb->invoke_async (_obj, this,
                                               Principal::_nil());
                    break;
		}
	    }
	    done = TRUE;
	    break;

	default:
	    assert (0);
	}
    }

    if (_iceptreq) {
	Interceptor::ClientInterceptor::
	    _exec_finish_request ((Interceptor::LWRequest_ptr)_iceptreq,
                                  env());
    }
    _msgid = 0;
}


//-----------------


CORBA::StaticImplementation::StaticImplementation ()
{
}

CORBA::StaticImplementation::~StaticImplementation ()
{
}

CORBA::ServerRequestBase_ptr
CORBA::StaticImplementation::make_request (ORBRequest *req,
					   CORBA::Object_ptr obj,
					   CORBA::ULong msgid,
					   CORBA::ObjectAdapter *oa,
					   CORBA::Principal_ptr pr)
{
    return new StaticServerRequest (req, obj, msgid, oa, pr);
}

void
CORBA::StaticImplementation::doinvoke (ServerRequestBase_ptr req,
				       Environment &env)
{
    invoke ((StaticServerRequest_ptr)req, env);
}


//-----------------


CORBA::StaticServerRequest::StaticServerRequest (ORBRequest *req,
						 Object_ptr obj, MsgId msgid,
						 CORBA::ObjectAdapter *oa,
						 CORBA::Principal_ptr pr)
    : _oa (oa), _obj (Object::_duplicate (obj)),
      _ctx (Context::_nil()), _env (pr),
      _req (ORBRequest::_duplicate (req)),
      _res (0), _msgid (msgid), _aborted (FALSE)
{
    _iceptreq = Interceptor::ServerInterceptor::_create_request (
	_obj, req->op_name(), *req->context(), CORBA::ServerRequest::_nil());
}

CORBA::StaticServerRequest::~StaticServerRequest ()
{
    if (!_canceled) {
        // tell OA we are done
        CORBA::InvokeStatus stat = CORBA::InvokeOk;
        if (_env.exception()) {
            if (CORBA::SystemException::EXCEPTION_DOWNCAST (_env.exception())) {
                stat = CORBA::InvokeSysEx;
            } else {
                stat = CORBA::InvokeUsrEx;
            }
        }
        _oa->answer_invoke (_msgid, _obj, _req, stat);

        if (_iceptreq && !_aborted && !Interceptor::ServerInterceptor::
            _exec_finish_request ((Interceptor::LWServerRequest_ptr)_iceptreq,
                                  &_env)) {
            // XXX how to abort request here ??
        }
    }

    CORBA::release (_obj);
    CORBA::release (_ctx);
    CORBA::release (_req);
    CORBA::release (_iceptreq);
}

void
CORBA::StaticServerRequest::add_in_arg (StaticAny *a)
{
    _args.push_back (a);
    a->flags (CORBA::ARG_IN);
}

void
CORBA::StaticServerRequest::add_out_arg (StaticAny *a)
{
    _args.push_back (a);
    a->flags (CORBA::ARG_OUT);
}

void
CORBA::StaticServerRequest::add_inout_arg (StaticAny *a)
{
    _args.push_back (a);
    a->flags (CORBA::ARG_INOUT);
}

CORBA::Boolean
CORBA::StaticServerRequest::read_args ()
{
    /*
     * must call read_args() after all args haven been set up using
     * add_*_arg() in order to read arguments from ORBRequest
     */

    if (_iceptreq && !Interceptor::ServerInterceptor::
	_exec_initialize_request ((Interceptor::LWServerRequest_ptr)_iceptreq,
				  &_env)) {
	_aborted = TRUE;
	write_results ();
	return FALSE;
    }

    if (!_req->get_in_args (&_args, _ctx)) {
        MICODebug::instance()->debugger()
            << "cannot decode args" << endl;
        _aborted = TRUE;
        set_exception (new CORBA::MARSHAL());
	write_results ();
        return FALSE;
    }

    if (_iceptreq && !Interceptor::ServerInterceptor::
	_exec_after_unmarshal ((Interceptor::LWServerRequest_ptr)_iceptreq,
			       &_env)) {
	_aborted = TRUE;
	write_results ();
	return FALSE;
    }
    return TRUE;
}

void
CORBA::StaticServerRequest::write_results ()
{
    /*
     * must call write_results() before the method implementation
     * is left in order to write back results into ORBRequest ...
     */

    if (_iceptreq && !_aborted && !Interceptor::ServerInterceptor::
	_exec_before_marshal ((Interceptor::LWServerRequest_ptr)_iceptreq,
			      &_env)) {
	_aborted = TRUE;
    }

    if (_env.exception()) {
	_req->set_out_args (_env.exception());
    } else {
        if (!_req->set_out_args (_res, &_args)) {
            MICODebug::instance()->debugger()
                << "cannot set out args" << endl;
            CORBA::MARSHAL ex (0, CORBA::COMPLETED_YES);
            _req->set_out_args (&ex);
        }
    }
}
