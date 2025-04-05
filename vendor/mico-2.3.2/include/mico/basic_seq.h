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

#if !defined(__BASIC_SEQ_H__) || defined(MICO_NO_TOPLEVEL_MODULES)
#define __BASIC_SEQ_H__

#ifndef MICO_NO_TOPLEVEL_MODULES
MICO_NAMESPACE_DECL CORBA {
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

typedef SequenceTmpl<CORBA::Any,MICO_TID_DEF> AnySeq;
#ifdef _WINDOWS
static AnySeq _dummy2_AnySeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Any,MICO_TID_DEF> > AnySeq_var;
typedef AnySeq_var AnySeq_out;

typedef SequenceTmpl<CORBA::Boolean,MICO_TID_BOOL> BooleanSeq;
#ifdef _WINDOWS
static BooleanSeq _dummy_BooleanSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Boolean,MICO_TID_BOOL> > BooleanSeq_var;
typedef BooleanSeq_var BooleanSeq_out;

typedef SequenceTmpl<CORBA::Char,MICO_TID_CHAR> CharSeq;
#ifdef _WINDOWS
static CharSeq _dummy_CharSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Char,MICO_TID_CHAR> > CharSeq_var;
typedef CharSeq_var CharSeq_out;

typedef SequenceTmpl<CORBA::WChar,MICO_TID_WCHAR> WCharSeq;
#ifdef _WINDOWS
static WCharSeq _dummy_WCharSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::WChar,MICO_TID_WCHAR> > WCharSeq_var;
typedef WCharSeq_var WCharSeq_out;

typedef SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> OctetSeq;
#ifdef _WINDOWS
static OctetSeq _dummy2_OctetSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> > OctetSeq_var;
typedef OctetSeq_var OctetSeq_out;

typedef SequenceTmpl<CORBA::Short,MICO_TID_DEF> ShortSeq;
#ifdef _WINDOWS
static ShortSeq _dummy_ShortSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Short,MICO_TID_DEF> > ShortSeq_var;
typedef ShortSeq_var ShortSeq_out;

typedef SequenceTmpl<CORBA::UShort,MICO_TID_DEF> UShortSeq;
#ifdef _WINDOWS
static UShortSeq _dummy_UShortSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::UShort,MICO_TID_DEF> > UShortSeq_var;
typedef UShortSeq_var UShortSeq_out;

typedef SequenceTmpl<CORBA::Long,MICO_TID_DEF> LongSeq;
#ifdef _WINDOWS
static LongSeq _dummy_LongSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Long,MICO_TID_DEF> > LongSeq_var;
typedef LongSeq_var LongSeq_out;

typedef SequenceTmpl<CORBA::ULong,MICO_TID_DEF> ULongSeq;
#ifdef _WINDOWS
static ULongSeq _dummy_ULongSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::ULong,MICO_TID_DEF> > ULongSeq_var;
typedef ULongSeq_var ULongSeq_out;

typedef SequenceTmpl<CORBA::LongLong,MICO_TID_DEF> LongLongSeq;
#ifdef _WINDOWS
static LongLongSeq _dummy_LongLongSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::LongLong,MICO_TID_DEF> > LongLongSeq_var;
typedef LongLongSeq_var LongLongSeq_out;

typedef SequenceTmpl<CORBA::ULongLong,MICO_TID_DEF> ULongLongSeq;
#ifdef _WINDOWS
static ULongLongSeq _dummy_ULongLongSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::ULongLong,MICO_TID_DEF> > ULongLongSeq_var;
typedef ULongLongSeq_var ULongLongSeq_out;

typedef SequenceTmpl<CORBA::Float,MICO_TID_DEF> FloatSeq;
#ifdef _WINDOWS
static FloatSeq _dummy_FloatSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Float,MICO_TID_DEF> > FloatSeq_var;
typedef FloatSeq_var FloatSeq_out;

typedef SequenceTmpl<CORBA::Double,MICO_TID_DEF> DoubleSeq;
#ifdef _WINDOWS
static DoubleSeq _dummy_DoubleSeq;
#endif
typedef TSeqVar<SequenceTmpl<CORBA::Double,MICO_TID_DEF> > DoubleSeq_var;
typedef DoubleSeq_var DoubleSeq_out;

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE_CORBA)

#ifndef MICO_NO_TOPLEVEL_MODULES

};
#endif

#if !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Any,MICO_TID_DEF> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Any,MICO_TID_DEF> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Any,MICO_TID_DEF> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Any,MICO_TID_DEF> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Char,MICO_TID_CHAR> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Char,MICO_TID_CHAR> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Char,MICO_TID_CHAR> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Char,MICO_TID_CHAR> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Boolean,MICO_TID_BOOL> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Boolean,MICO_TID_BOOL> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Boolean,MICO_TID_BOOL> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Boolean,MICO_TID_BOOL> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Octet,MICO_TID_OCTET> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::UShort,MICO_TID_DEF> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::UShort,MICO_TID_DEF> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::UShort,MICO_TID_DEF> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::UShort,MICO_TID_DEF> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::ULong,MICO_TID_DEF> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::ULong,MICO_TID_DEF> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::ULong,MICO_TID_DEF> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::ULong,MICO_TID_DEF> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Short,MICO_TID_DEF> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Short,MICO_TID_DEF> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Short,MICO_TID_DEF> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Short,MICO_TID_DEF> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Long,MICO_TID_DEF> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Long,MICO_TID_DEF> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Long,MICO_TID_DEF> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Long,MICO_TID_DEF> *&s );

void operator<<=( CORBA::Any &_a,
		  const SequenceTmpl<CORBA::LongLong,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a,
		  SequenceTmpl<CORBA::LongLong,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::LongLong,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::LongLong,MICO_TID_DEF> *&_s );

void operator<<=( CORBA::Any &_a,
		  const SequenceTmpl<CORBA::ULongLong,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a,
		  SequenceTmpl<CORBA::ULongLong,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::ULongLong,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::ULongLong,MICO_TID_DEF> *&_s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Float,MICO_TID_DEF> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Float,MICO_TID_DEF> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Float,MICO_TID_DEF> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Float,MICO_TID_DEF> *&s );

void operator<<=( CORBA::Any &a,
		  const SequenceTmpl<CORBA::Double,MICO_TID_DEF> &s );
void operator<<=( CORBA::Any &a,
		  SequenceTmpl<CORBA::Double,MICO_TID_DEF> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Double,MICO_TID_DEF> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    SequenceTmpl<CORBA::Double,MICO_TID_DEF> *&s );

void operator<<=( CORBA::Any &_a,
		  const SequenceTmpl<CORBA::LongDouble,MICO_TID_DEF> &_s );
void operator<<=( CORBA::Any &_a,
		  SequenceTmpl<CORBA::LongDouble,MICO_TID_DEF> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::LongDouble,MICO_TID_DEF> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::LongDouble,MICO_TID_DEF> *&_s );

void operator<<=( CORBA::Any &_a,
		  const SequenceTmpl<CORBA::WChar,MICO_TID_WCHAR> &_s );
void operator<<=( CORBA::Any &_a,
		  SequenceTmpl<CORBA::WChar,MICO_TID_WCHAR> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::WChar,MICO_TID_WCHAR> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    SequenceTmpl<CORBA::WChar,MICO_TID_WCHAR> *&_s );

void operator<<=( CORBA::Any &_a,
		  const WStringSequenceTmpl<CORBA::WString_var> &_s );
void operator<<=( CORBA::Any &_a,
		  WStringSequenceTmpl<CORBA::WString_var> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    WStringSequenceTmpl<CORBA::WString_var> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    WStringSequenceTmpl<CORBA::WString_var> *&_s );

void operator<<=( CORBA::Any &a,
		  const StringSequenceTmpl<CORBA::String_var> &s );
void operator<<=( CORBA::Any &a,
		  StringSequenceTmpl<CORBA::String_var> *s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    StringSequenceTmpl<CORBA::String_var> &s );
CORBA::Boolean operator>>=( const CORBA::Any &a,
			    StringSequenceTmpl<CORBA::String_var> *&s );

void operator<<=( CORBA::Any &_a,
		  const IfaceSequenceTmpl<CORBA::Object_var, CORBA::Object_ptr> &_s );
void operator<<=( CORBA::Any &_a,
		  IfaceSequenceTmpl<CORBA::Object_var, CORBA::Object_ptr> *_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    IfaceSequenceTmpl<CORBA::Object_var,
			                      CORBA::Object_ptr> &_s );
CORBA::Boolean operator>>=( const CORBA::Any &_a,
			    IfaceSequenceTmpl<CORBA::Object_var,
			                      CORBA::Object_ptr> *&_s );

#endif // !defined(MICO_NO_TOPLEVEL_MODULES) || defined(MICO_MODULE__GLOBAL)

#endif
