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

#ifndef __mico_basic_h__
#define __mico_basic_h__

// basic types
typedef MICO_Short  Short;
typedef MICO_Short& Short_out;
typedef MICO_Long  Long;
typedef MICO_Long& Long_out;
typedef MICO_LongLong  LongLong;
typedef MICO_LongLong& LongLong_out;
typedef MICO_UShort  UShort;
typedef MICO_UShort& UShort_out;
typedef MICO_ULong  ULong;
typedef MICO_ULong& ULong_out;
typedef MICO_ULongLong  ULongLong;
typedef MICO_ULongLong& ULongLong_out;
typedef MICO_Float  Float;
typedef MICO_Float& Float_out;
typedef MICO_Double  Double;
typedef MICO_Double& Double_out;
typedef MICO_LongDouble  LongDouble;
typedef MICO_LongDouble& LongDouble_out;
typedef MICO_Char Char;
typedef MICO_WChar  WChar;
typedef MICO_WChar& WChar_out;
typedef MICO_Boolean Boolean;
typedef MICO_Octet Octet;


typedef ULong Flags;


// forwards
class Environment;
class NamedValue;
class NVList;
class ExceptionList;
class ContextList;
class Request;
class Context;
class Principal;
class TypeCode;
class TypeCodeChecker;
class BOA;
class ORB;
class ImplementationDef;
class ImplRepository;
class Repository;
class InterfaceDef;
class OperationDef;
class ServerRequestBase;
class ServerRequest;
class ImplementationBase;
class DynamicImplementation;
class ValueDef;

class String_var;
class WString_var;
class Object;
class Exception;
class SystemException;
class UserException;
class UnknownUserException;
class Any;

class StaticTypeInfo;
class StaticAny;

class DataEncoder;
class DataDecoder;

class ValueBase;
class AbstractBase;

typedef Environment *Environment_ptr;
typedef Environment *EnvironmentRef;
typedef NamedValue *NamedValue_ptr;
typedef NamedValue *NamedValueRef;
typedef NVList *NVList_ptr;
typedef NVList *NVListRef;
typedef ExceptionList *ExceptionList_ptr;
typedef ExceptionList *ExceptionListRef;
typedef ContextList *ContextList_ptr;
typedef ContextList *ContextListRef;
typedef Request *Request_ptr;
typedef Request *RequestRef;
typedef Context *Context_ptr;
typedef Context *ContextRef;
typedef Principal *Principal_ptr;
typedef Principal *PrincipalRef;
typedef TypeCode *TypeCode_ptr;
typedef TypeCode *TypeCodeRef;
typedef ObjVar<TypeCode> TypeCode_var;
typedef BOA *BOA_ptr;
typedef BOA *BOARef;
typedef ORB *ORB_ptr;
typedef ORB *ORBRef;
typedef InterfaceDef *InterfaceDef_ptr;
// InterfaceDefRef is defined in ir.h
typedef OperationDef *OperationDef_ptr;
// OperationDefRef is defined in ir.h
typedef ValueDef *ValueDef_ptr;
typedef ServerRequest *ServerRequest_ptr;
typedef ServerRequest *ServerRequestRef;
typedef ServerRequestBase *ServerRequestBase_ptr;
typedef ServerRequestBase *ServerRequestBaseRef;
typedef Object *Object_ptr;
typedef Object *ObjectRef;


#endif // __mico_basic_h__
