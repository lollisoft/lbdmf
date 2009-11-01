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

#ifndef __mico_var_h__
#define __mico_var_h__


/*
 * Template to generate _var types for object references [16.3.6]
 */
template<class T>
class ObjVar
{
private:
  T* _ptr;
  T* _ptr_backup;
  MICO_Boolean _autofree;

  static T* nil()
  {
      return 0;
  }

public:
  static T* duplicate (T *);
  static void release (T *);

private:
  void check();
  void free();
  void reset( T* ptr )
  {
      free();
      _ptr_backup = _ptr = ptr;
  }
public:
  ObjVar()
  {
      _ptr_backup = _ptr = nil();
      _autofree = TRUE;
  }
  ObjVar (MICO_Boolean autofree)
  {
      _ptr_backup = _ptr = nil();
      _autofree = autofree;
  }
  ObjVar( T* ptr )
  {
      _ptr = _ptr_backup = ptr;
      _autofree = TRUE;
  }
  ObjVar( const ObjVar<T>& var )
  {
      _ptr_backup = _ptr = duplicate (var._ptr);
      _autofree = TRUE;
  }
  ~ObjVar()
  {
      free();
  }
  ObjVar<T>& operator=( const ObjVar<T> &var )
  {
      if (this != &var) {
	  free();
	  _ptr_backup = _ptr = duplicate( var._ptr );
      }
      return *this;
  }
  ObjVar<T>& operator=( T* ptr )
  {
      if (_ptr != ptr)
	  reset( ptr );
      return *this;
  }
  void autofree (MICO_Boolean val)
  {
      _autofree = val;
  }
// g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
  operator T*() const
  {
      return _ptr;
  }
  operator T*&()
  {
      check();
      return _ptr;
  }
#else
  operator T*&() const
  {
      ((ObjVar<T>*)this)->check();
      return (T*&)_ptr;
  }
#endif
  T* operator->() const
  {
      ((ObjVar<T>*)this)->check();
      return _ptr;
  }

  T* in() const
  {
    ((ObjVar<T>*)this)->check();
    return _ptr;
  }
  
  T*& inout()
  {
    check();
    return _ptr;
  }
  
  T*& out()
  {
    check();
    return _ptr;
  }
  
  T* _retn()
  {
      check ();
      T *_p = _ptr;
      _ptr_backup = _ptr = nil();
      return _p;
  }
};

template<class T>
inline void
ObjVar<T>::check()
{
    if (_ptr != _ptr_backup) {
	// release() works on nil
	if (_autofree)
	    release (_ptr_backup);
	_ptr_backup = _ptr;
    }
}

template<class T>
inline void
ObjVar<T>::free()
{
    check ();
    release( _ptr );
    _ptr_backup = _ptr = nil();
}


/*
 * Template to generate _var types for value types
 */
template<class T>
class ValueVar
{
private:
  T* _ptr;
  T* _ptr_backup;
  MICO_Boolean _autofree;

  static T* nil()
  {
      return 0;
  }
  static T* duplicate (T *);
  static void release (T *);

  void check();
  void free();
  void reset( T* ptr )
  {
      free();
      _ptr_backup = _ptr = ptr;
  }
public:
  ValueVar()
  {
      _ptr_backup = _ptr = nil();
      _autofree = TRUE;
  }
  ValueVar (MICO_Boolean autofree)
  {
      _ptr_backup = _ptr = nil();
      _autofree = autofree;
  }
  ValueVar( T* ptr )
  {
      _ptr = _ptr_backup = ptr;
      _autofree = TRUE;
  }
  ValueVar( const ValueVar<T>& var )
  {
      _ptr_backup = _ptr = duplicate (var._ptr);
      _autofree = TRUE;
  }
  ~ValueVar()
  {
      free();
  }
  ValueVar<T>& operator=( const ValueVar<T> &var )
  {
      if (this != &var) {
	  free();
	  _ptr_backup = _ptr = duplicate( var._ptr );
      }
      return *this;
  }
  ValueVar<T>& operator=( T* ptr )
  {
      if (_ptr != ptr)
	  reset( ptr );
      return *this;
  }
  void autofree (MICO_Boolean val)
  {
      _autofree = val;
  }
// g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
  operator T*() const
  {
      return _ptr;
  }
  operator T*&()
  {
      check();
      return _ptr;
  }
#else
  operator T*&() const
  {
      ((ValueVar<T>*)this)->check();
      return (T*&)_ptr;
  }
#endif
  T* operator->() const
  {
      ((ValueVar<T>*)this)->check();
      return _ptr;
  }

  T* in() const
  {
    ((ValueVar<T>*)this)->check();
    return _ptr;
  }
  
  T*& inout()
  {
    check();
    return _ptr;
  }
  
  T*& out()
  {
    check();
    return _ptr;
  }
  
  T* _retn()
  {
      check ();
      T *_p = _ptr;
      _ptr_backup = _ptr = nil();
      return _p;
  }
};

template<class T>
inline void
ValueVar<T>::check()
{
    if (_ptr != _ptr_backup) {
	// release() works on nil
	if (_autofree)
	    release (_ptr_backup);
	_ptr_backup = _ptr;
    }
}

template<class T>
inline void
ValueVar<T>::free()
{
    check ();
    release( _ptr );
    _ptr_backup = _ptr = nil();
}


/*
 * Template to generate _var types for fixed length data types [20.9.1]
 * See comments for CORBA::String_var concerning _ptr_backup
 */
template<class T>
class TFixVar
{
private:
  T* _ptr;
  T* _ptr_backup;
  MICO_Boolean _autofree;
  
  void check();
  void free();
  void reset( T* ptr )
  {
    free();
    _ptr = _ptr_backup = ptr;
  }
public:
  TFixVar()
  {
    _ptr = _ptr_backup = NULL;
    _autofree = TRUE;
  }
  TFixVar (MICO_Boolean autofree)
  {
    _ptr = _ptr_backup = NULL;
    _autofree = autofree;
  }
  TFixVar( T* ptr )
  {
    _ptr = _ptr_backup = ptr;
    _autofree = TRUE;
  }
  TFixVar( const TFixVar<T>& var )
  {
    if( !var._ptr )
      _ptr = _ptr_backup = NULL;
    else
      _ptr = _ptr_backup = new T (*var._ptr);
    _autofree = TRUE;
  }
  ~TFixVar()
  {
    free();
  }
  TFixVar<T>& operator=( T* ptr )
  {
    if( _ptr != ptr )
      reset( ptr );
    return *this;
  }
  TFixVar<T>& operator=( const TFixVar<T>& var )
  {
    if( this != &var ) {
      free();
      if( !var._ptr )
	_ptr = _ptr_backup = NULL;
      else
	_ptr = _ptr_backup = new T (*var._ptr);
    }
    return *this;
  }
  void autofree (MICO_Boolean val)
  {
    _autofree = val;
  }
#ifdef HAVE_CONST_OVERLOAD
  operator const T&() const
  {
    assert( _ptr );
    return *_ptr;
  }
  operator T&()
  {
    check();
    assert (_ptr);
    return *_ptr;
  }
#else
  operator T&() const
  {
    ((TFixVar<T>*)this)->check();
    assert (_ptr);
    return *_ptr;
  }
#endif
  T* operator->() const
  {
    ((TFixVar<T>*)this)->check();
    assert( _ptr );
    return _ptr;
  }
  T& operator*() const
  {
    ((TFixVar<T>*)this)->check();
    assert (_ptr);
    return *_ptr;
  }

  const T& in() const
  {
    ((TFixVar<T>*)this)->check();
    return *_ptr;
  }
  
  T& inout()
  {
    check();
    return *_ptr;
  }
  
  T& out()
  {
    check();
    return *_ptr;
  }
  
  T* _retn()
  {
    check();
    T *_p = _ptr;
    _ptr_backup = _ptr = NULL;
    return _p;
  }
};

template<class T>
inline void
TFixVar<T>::check()
{
    if( _ptr != _ptr_backup ) {
	if( _ptr_backup && _autofree )
	    delete _ptr_backup;
	_ptr_backup = _ptr;
    }
}

template<class T>
inline void
TFixVar<T>::free()
{
    check();
    if( _ptr )
	delete _ptr;
    _ptr = _ptr_backup = NULL;
}


/*
 * Template to generate _var types for variable length data types [20.9.1]
 * See comments for CORBA::String_var concerning _ptr_backup
 */
template<class T>
class TVarVar
{
private:
  T* _ptr;
  T* _ptr_backup;
  MICO_Boolean _autofree;
  
  void check();
  void free();
  void reset( T* ptr )
  {
    free();
    _ptr = _ptr_backup = ptr;
  }
public:
  TVarVar()
  {
    _ptr = _ptr_backup = NULL;
    _autofree = TRUE;
  }
  TVarVar (MICO_Boolean autofree)
  {
    _ptr = _ptr_backup = NULL;
    _autofree = autofree;
  }
  TVarVar( T* ptr )
  {
    _ptr = _ptr_backup = ptr;
    _autofree = TRUE;
  }
  TVarVar( const TVarVar<T>& var )
  {
    if( !var._ptr )
      _ptr = _ptr_backup = NULL;
    else
      _ptr = _ptr_backup = new T (*var._ptr);
    _autofree = TRUE;
  }
  ~TVarVar()
  {
    free();
  }
  TVarVar<T>& operator=( T* ptr )
  {
    if( _ptr != ptr )
      reset( ptr );
    return *this;
  }
  TVarVar<T>& operator=( const TVarVar<T>& var )
  {
    if( this != &var ) {
      free();
      if( !var._ptr )
	_ptr = _ptr_backup = NULL;
      else
	_ptr = _ptr_backup = new T (*var._ptr);
    }
    return *this;
  }
  void autofree (MICO_Boolean val)
  {
    _autofree = val;
  }
#ifdef HAVE_CONST_OVERLOAD
  operator const T&() const
  {
    assert( _ptr );
    return *_ptr;
  }
  operator T&()
  {
    check();
    assert (_ptr);
    return *_ptr;
  }
#else
  operator T&() const
  {
    ((TVarVar<T>*)this)->check();
    assert (_ptr);
    return *_ptr;
  }
#endif
  operator T*&()
  {
    check();
    return _ptr;
  }
  T* operator->() const
  {
    ((TVarVar<T>*)this)->check();
    assert( _ptr );
    return _ptr;
  }
  T& operator*() const
  {
    ((TVarVar<T>*)this)->check();
    assert (_ptr);
    return *_ptr;
  }

  const T& in() const
  {
    ((TVarVar<T>*)this)->check();
    return *_ptr;
  }
  
  T& inout()
  {
    check();
    return *_ptr;
  }
  
  T*& out()
  {
    free();
    return _ptr;
  }
  
  T* _retn()
  {
    check();
    T *_p = _ptr;
    _ptr_backup = _ptr = NULL;
    return _p;
  }
};

template<class T>
inline void
TVarVar<T>::check()
{
    if( _ptr != _ptr_backup ) {
	if( _ptr_backup && _autofree )
	    delete _ptr_backup;
	_ptr_backup = _ptr;
    }
}

template<class T>
inline void
TVarVar<T>::free()
{
    check();
    if( _ptr )
	delete _ptr;
    _ptr = _ptr_backup = NULL;
}


/*
 * Template to generate _var types for sequences. The difference
 * to the TVar template is, that operator[] is overloaded as well.
 */
template<class T>
class TSeqVar
{
private:
  T* _ptr;
  T* _ptr_backup;
  MICO_Boolean _autofree;
  
  void check();
  void free();
  void reset( T* ptr )
  {
    free();
    _ptr = _ptr_backup = ptr;
  }
public:
  TSeqVar()
  {
    _ptr = _ptr_backup = NULL;
    _autofree = TRUE;
  }
  TSeqVar (MICO_Boolean autofree)
  {
    _ptr = _ptr_backup = NULL;
    _autofree = autofree;
  }
  TSeqVar( T* ptr )
  {
    _ptr = _ptr_backup = ptr;
    _autofree = TRUE;
  }
  TSeqVar( const TSeqVar<T>& var )
  {
    if (!var._ptr)
      _ptr = _ptr_backup = NULL;
    else
      _ptr = _ptr_backup = new T (*var._ptr);
    _autofree = TRUE;
  }
  ~TSeqVar()
  {
    free();
  }
  TSeqVar<T>& operator=( T* ptr )
  {
    if (_ptr != ptr)
      reset( ptr );
    return *this;
  }
  TSeqVar<T>& operator=( const TSeqVar<T>& var )
  {
    if (this != &var) {
      free();
      if (!var._ptr)
        _ptr = _ptr_backup = NULL;
      else
        _ptr = _ptr_backup = new T (*var._ptr);
    }
    return *this;
  }
  void autofree (MICO_Boolean val)
  {
    _autofree = val;
  }
#ifdef HAVE_CONST_OVERLOAD
  operator const T&() const
  {
    assert (_ptr);
    return *_ptr;
  }
  operator T&()
  {
    check();
    assert (_ptr);
    return *_ptr;
  }
#else
  operator T&() const
  {
    ((TSeqVar<T>*)this)->check();
    assert (_ptr);
    return *_ptr;
  }
#endif
  operator T*&()
  {
    check();
    return _ptr;
  }
  T* operator->() const
  {
    ((TSeqVar<T>*)this)->check();
    assert( _ptr != NULL );
    return _ptr;
  }
  T& operator*() const
  {
    ((TSeqVar<T>*)this)->check();
    assert (_ptr);
    return *_ptr;
  }

  typename T::ElementType operator[] (MICO_ULong idx)
  {
    check();
    assert( _ptr != NULL );
    return (*_ptr)[ idx ];
  }

  const T& in() const
  {
    ((TSeqVar<T>*)this)->check();
    return *_ptr;
  }
  
  T& inout()
  {
    check();
    return *_ptr;
  }
  
  T*& out()
  {
    free();
    return _ptr;
  }
  
  T* _retn()
  {
    check();
    T *_p = _ptr;
    _ptr_backup = _ptr = NULL;
    return _p;
  }
};

template<class T>
inline void
TSeqVar<T>::check()
{
    if( _ptr != _ptr_backup ) {
	if( _ptr_backup && _autofree )
	    delete _ptr_backup;
	_ptr_backup = _ptr;
    }
}

template<class T>
inline void
TSeqVar<T>::free()
{
    check();
    if( _ptr )
	delete _ptr;
    _ptr = _ptr_backup = NULL;
}


#ifndef	HAVE_STD_EH

/*
 * Template to generate _var types for exceptions. Difference to
 * TVar is that _clone() is used instead of the copy constructor.
 */
template<class T>
class ExceptVar
{
private:
  T* _ptr;
  T* _ptr_backup;
  MICO_Boolean _autofree;

  void check();
  void free();
  void reset( T* ptr )
  {
    free();
    _ptr = _ptr_backup = ptr;
  }
public:
  ExceptVar()
  {
    _ptr = _ptr_backup = NULL;
    _autofree = TRUE;
  }
  ExceptVar (MICO_Boolean autofree)
  {
    _ptr = _ptr_backup = NULL;
    _autofree = autofree;
  }
  ExceptVar( T* ptr )
  {
    _ptr = _ptr_backup = ptr;
    _autofree = TRUE;
  }
  ExceptVar( const ExceptVar<T>& var )
  {
    if (!var._ptr)
      _ptr = _ptr_backup = NULL;
    else
      _ptr = _ptr_backup = (T *)var._ptr->_clone();
    _autofree = TRUE;
  }
  ~ExceptVar()
  {
    free();
  }
  ExceptVar<T>& operator=( T* ptr )
  {
    if (_ptr != ptr)
      reset( ptr );
    return *this;
  }
  ExceptVar<T>& operator=( const ExceptVar<T>& var )
  {
    if (this != &var) {
      free();
      if (!var._ptr)
	_ptr = _ptr_backup = NULL;
      else
	_ptr = _ptr_backup = (T *)var._ptr->_clone();
    }
    return *this;
  }
  void autofree (MICO_Boolean val)
  {
    _autofree = val;
  }
  T* operator->() const
  {
    ((ExceptVar<T>*)this)->check();
    assert (_ptr);
    return _ptr;
  }
  T& operator*() const
  {
    ((ExceptVar<T>*)this)->check();
    assert (_ptr);
    return *_ptr;
  }

  T* _retn()
  {
    check();
    T *_p = _ptr;
    _ptr_backup = _ptr = NULL;
    return _p;
  }
};

template<class T>
inline void
ExceptVar<T>::check()
{
    if( _ptr != _ptr_backup ) {
	if( _ptr_backup && _autofree )
	    delete _ptr_backup;
	_ptr_backup = _ptr;
    }
}

template<class T>
inline void
ExceptVar<T>::free()
{
    check();
    if( _ptr )
	delete _ptr;
    _ptr = _ptr_backup = NULL;
}

#endif // ! HAVE_STD_EH

#endif
