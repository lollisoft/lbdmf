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

#ifndef __mico_ir_fwd_h__
#define __mico_ir_fwd_h__

// The following definitions are forward definitions which are
// required in typecode.h
// They are eventually defined in ir.h
typedef SequenceIndTmpl<String_var,String_var,1> EnumMemberSeq;
typedef TSeqVar<EnumMemberSeq> EnumMemberSeq_var;

struct StructMember;
typedef SequenceIndTmpl<StructMember,StructMember,1> StructMemberSeq;
typedef TSeqVar<StructMemberSeq> StructMemberSeq_var;

struct UnionMember;
typedef SequenceIndTmpl<UnionMember,UnionMember,1> UnionMemberSeq;
typedef TSeqVar<UnionMemberSeq> UnionMemberSeq_var;

struct ValueMember;
typedef SequenceIndTmpl<ValueMember,ValueMember,1> ValueMemberSeq;
typedef TSeqVar<ValueMemberSeq> ValueMemberSeq_var;

#endif // __mico_ir_fwd_h__
