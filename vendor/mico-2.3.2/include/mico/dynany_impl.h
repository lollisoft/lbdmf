// -*- c++ -*-
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

#ifndef __dynany_impl_h__
#define __dynany_impl_h__


class DynAny_impl : virtual public DynamicAny::DynAny {
protected:
    vector<DynamicAny::DynAny_var> _elements;
    CORBA::Long _index;
    CORBA::TypeCode_var _type;

    static DynamicAny::DynAnyFactory_ptr _factory();

    virtual void update_element (CORBA::Long idx);
public:
    DynAny_impl ();
    virtual ~DynAny_impl ();

    void assign (DynamicAny::DynAny_ptr dyn_any);
    DynamicAny::DynAny_ptr copy ();

    CORBA::TypeCode_ptr type ();
    virtual void destroy ();
    CORBA::Boolean equal (DynamicAny::DynAny_ptr dyn_any);

    void insert_boolean (CORBA::Boolean value);
    void insert_octet (CORBA::Octet value);
    void insert_char (CORBA::Char value);
    void insert_wchar (CORBA::WChar value);
    void insert_short (CORBA::Short value);
    void insert_ushort (CORBA::UShort value);
    void insert_long (CORBA::Long value);
    void insert_longlong (CORBA::LongLong value);
    void insert_ulong (CORBA::ULong value);
    void insert_ulonglong (CORBA::ULongLong value);
    void insert_float (CORBA::Float value);
    void insert_double (CORBA::Double value);
    void insert_longdouble (CORBA::LongDouble value);
    void insert_string (const char* value);
    void insert_wstring (const CORBA::WChar* value);
    void insert_reference (CORBA::Object_ptr value);
    void insert_typecode (CORBA::TypeCode_ptr value);
    void insert_any (const CORBA::Any &value);
    void insert_dyn_any (DynamicAny::DynAny_ptr value);
    void insert_val (CORBA::ValueBase *value);

    CORBA::Boolean get_boolean ();
    CORBA::Octet get_octet ();
    CORBA::Char get_char ();
    CORBA::WChar get_wchar ();
    CORBA::Short get_short ();
    CORBA::UShort get_ushort ();
    CORBA::Long get_long ();
    CORBA::LongLong get_longlong ();
    CORBA::ULong get_ulong ();
    CORBA::ULongLong get_ulonglong ();
    CORBA::Float get_float ();
    CORBA::Double get_double ();
    CORBA::LongDouble get_longdouble ();
    char* get_string ();
    CORBA::WChar* get_wstring ();
    CORBA::Object_ptr get_reference ();
    CORBA::TypeCode_ptr get_typecode ();
    CORBA::Any* get_any ();
    DynamicAny::DynAny_ptr get_dyn_any ();
    CORBA::ValueBase* get_val ();

    DynamicAny::DynAny_ptr current_component ();
    CORBA::ULong component_count ();
    CORBA::Boolean next ();
    CORBA::Boolean seek (CORBA::Long index);
    void rewind ();

    virtual void from_any (const CORBA::Any& value) = 0;
    virtual CORBA::Any* to_any () = 0;
};


class DynBasic_impl : virtual public DynAny_impl,
		      virtual public DynamicAny::DynBasic {
private:
    CORBA::Any _value;

public:
    DynBasic_impl (CORBA::TypeCode_ptr);
    DynBasic_impl (const CORBA::Any &);
    virtual ~DynBasic_impl ();

    void destroy ();
    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();
};

class DynFixed_impl : virtual public DynAny_impl,
		      virtual public DynamicAny::DynFixed {
private:
    CORBA::Any _value;

public:
    DynFixed_impl (CORBA::TypeCode_ptr);
    DynFixed_impl (const CORBA::Any &);
    virtual ~DynFixed_impl ();

    void destroy ();
    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();

    char* get_value ();
    void set_value (const char *val);
};

class DynEnum_impl : virtual public DynAny_impl,
		     virtual public DynamicAny::DynEnum {
private:
    CORBA::Any _value;

public:
    DynEnum_impl (CORBA::TypeCode_ptr);
    DynEnum_impl (const CORBA::Any &);
    virtual ~DynEnum_impl ();

    void destroy ();
    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();

    char* get_as_string ();
    void set_as_string (const char* value);
    CORBA::ULong get_as_ulong ();
    void set_as_ulong (CORBA::ULong value);
};


class DynStruct_impl : virtual public DynAny_impl,
		       virtual public DynamicAny::DynStruct {
private:
    CORBA::Boolean _isexcept;
public:
    DynStruct_impl (CORBA::TypeCode_ptr);
    DynStruct_impl (const CORBA::Any &);
    virtual ~DynStruct_impl ();

    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();

    DynamicAny::FieldName current_member_name ();
    CORBA::TCKind current_member_kind ();
    DynamicAny::NameValuePairSeq* get_members ();
    void set_members (const DynamicAny::NameValuePairSeq& value);
    DynamicAny::NameDynAnyPairSeq* get_members_as_dyn_any ();
    void set_members_as_dyn_any (const DynamicAny::NameDynAnyPairSeq& value);
};


class DynUnion_impl : virtual public DynAny_impl,
		      virtual public DynamicAny::DynUnion {
private:
    virtual void update_element (CORBA::Long idx);
    CORBA::Long _member_idx;

    CORBA::Boolean has_default_member();
public:
    DynUnion_impl (CORBA::TypeCode_ptr);
    DynUnion_impl (const CORBA::Any &);
    virtual ~DynUnion_impl ();

    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();
    CORBA::ULong component_count ();

    DynamicAny::DynAny_ptr get_discriminator ();
    void set_discriminator (DynamicAny::DynAny_ptr d);
    void set_to_default_member ();
    void set_to_no_active_member ();
    CORBA::Boolean has_no_active_member ();
    CORBA::TCKind discriminator_kind ();
    DynamicAny::DynAny_ptr member ();
    DynamicAny::FieldName member_name ();
    CORBA::TCKind member_kind ();
};

class DynSequence_impl : virtual public DynAny_impl,
			 virtual public DynamicAny::DynSequence {
private:
    CORBA::ULong _length;
public:
    DynSequence_impl (CORBA::TypeCode_ptr);
    DynSequence_impl (const CORBA::Any &);
    virtual ~DynSequence_impl ();

    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();

    CORBA::ULong get_length ();
    void set_length (CORBA::ULong value);
    DynamicAny::AnySeq* get_elements ();
    void set_elements (const DynamicAny::AnySeq& value);
    DynamicAny::DynAnySeq* get_elements_as_dyn_any ();
    void set_elements_as_dyn_any (const DynamicAny::DynAnySeq& value);
};


class DynArray_impl : virtual public DynAny_impl,
		      virtual public DynamicAny::DynArray {
private:
    CORBA::ULong _length;
public:
    DynArray_impl (CORBA::TypeCode_ptr);
    DynArray_impl (const CORBA::Any &);
    virtual ~DynArray_impl ();

    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();

    DynamicAny::AnySeq* get_elements ();
    void set_elements (const DynamicAny::AnySeq& value);
    DynamicAny::DynAnySeq* get_elements_as_dyn_any ();
    void set_elements_as_dyn_any (const DynamicAny::DynAnySeq& value);
};

class DynValue_impl : virtual public DynAny_impl,
		      virtual public DynamicAny::DynValue {
private:
    CORBA::Boolean _isvalue;
public:
    DynValue_impl (CORBA::TypeCode_ptr);
    DynValue_impl (const CORBA::Any &);
    virtual ~DynValue_impl ();

    void from_any (const CORBA::Any& value);
    CORBA::Any* to_any ();

    DynamicAny::FieldName current_member_name ();
    CORBA::TCKind current_member_kind ();
    DynamicAny::NameValuePairSeq* get_members ();
    void set_members (const DynamicAny::NameValuePairSeq& value);
    DynamicAny::NameDynAnyPairSeq* get_members_as_dyn_any ();
    void set_members_as_dyn_any (const DynamicAny::NameDynAnyPairSeq& value);
};

class DynAnyFactory_impl : virtual public DynamicAny::DynAnyFactory {
public:
    DynAnyFactory_impl ();
    virtual ~DynAnyFactory_impl ();

    DynamicAny::DynAny_ptr create_dyn_any (const CORBA::Any &value);
    DynamicAny::DynAny_ptr create_dyn_any_from_type_code (
        CORBA::TypeCode_ptr type);
};

#endif
