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

#ifndef __MICO_ARRAY_H__
#define __MICO_ARRAY_H__


/*
 * The following #define's define the memory management functions
 * for array slices as described in [16.12(9)].
 * The first argument denotes the name prefix for the array memory
 * management function, the second argument denotes the element type of
 * the array, the third argument denotes the name for the array slice
 * and the fourth argument the number of T_elem contained in
 * the array (this is the product of all the dimension bounds).
 */

#define DECLARE_ARRAY_ALLOC( T_name, T_elem, T_slice, n )  \
static inline T_slice* T_name ## _alloc()                  \
{                                                          \
  return (T_slice*) new T_elem[ n ];                       \
}

#define DECLARE_ARRAY_DUP( T_name, T_elem, T_slice, n )        \
static inline T_slice* T_name ## _dup( const T_slice* slice )  \
{                                                              \
  T_slice* s = (T_slice*) new T_elem[ n ];                     \
  for( int i = 0; i < n; i++ )                                 \
    ((T_elem*) s)[ i ] = ((T_elem*) slice)[ i ];               \
  return s;                                                    \
}

#define DECLARE_ARRAY_COPY( T_name, T_elem, T_slice, n )            \
static inline void T_name ## _copy( T_slice* d, const T_slice* s )  \
{                                                                   \
  for( int i = 0; i < n; i++ )                                      \
    ((T_elem*) d)[ i ] = ((T_elem*) s)[ i ];                        \
}

#define DECLARE_ARRAY_FREE( T_name, T_elem, T_slice, n )  \
static inline void T_name ## _free( T_slice* slice )      \
{                                                         \
  if( slice != NULL )                                     \
    delete[] slice;                                       \
}


/*
 * The following template defines the _var type for an array
 * of a fixed length data type as described in [20.14].
 * The first argument denotes the element type of the array,
 * the second argument denotes the type for the array slice,
 * the third argument is the type of the array itself and
 * the fourth argument the number of T_elem contained in
 * the array (this is the product of all the dimension bounds).
 */

template<class T_elem, class T_slice, class T, MICO_ULong n>
class ArrayFixVar
{
private:
  T_slice *_ptr;
  T_slice *_ptr_backup;
  MICO_Boolean _autofree;

  void check();
  void free();
  void copy( T_slice* ptr );
  void reset( T_slice* ptr )
  {
    free();
    _ptr = _ptr_backup = ptr;
  }
  
public:
  ArrayFixVar()
  {
    // This initialization is needed because an ArrayVar may be
    // used as an out-parameter without prior initialization
    // (see example in [16.12])
    _ptr = _ptr_backup = (T_slice*) new T_elem[ n ];
    _autofree = TRUE;
  }
  ArrayFixVar (MICO_Boolean autofree)
  {
    // This initialization is needed because an ArrayVar may be
    // used as an out-parameter without prior initialization
    // (see example in [16.12])
    _ptr = _ptr_backup = (T_slice*) new T_elem[ n ];
    _autofree = autofree;
  }
  ArrayFixVar( T_slice *slice )
  {
    _ptr = _ptr_backup = slice;
    _autofree = TRUE;
  }
  ArrayFixVar( const ArrayFixVar<T_elem, T_slice, T, n> &arr )
  {
    _ptr = _ptr_backup = 0;
    copy (arr._ptr);
    _autofree = TRUE;
  }
  ArrayFixVar( const T &arr )
  {
    _ptr = _ptr_backup = 0;
    copy ((T_slice *)&arr);
    _autofree = TRUE;
  }
  ~ArrayFixVar()
  {
    free();
  }
  ArrayFixVar<T_elem, T_slice, T, n> &
  operator=( const ArrayFixVar<T_elem, T_slice, T, n> &arr )
  {
    if( this != &arr ) {
      copy (arr._ptr);
    }
    return *this;
  }
  ArrayFixVar<T_elem, T_slice, T, n> &
  operator=( T_slice *slice )
  {
    if( _ptr != slice )
      reset( slice );
    return *this;
  }
  void autofree (MICO_Boolean val)
  {
    _autofree = val;
  }
  T_slice& operator[]( MICO_ULong i )
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  const T_slice& operator[]( MICO_ULong i ) const
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  // g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
  operator T_slice*() const
  {
    return _ptr;
  }
  operator T_slice*&()
  {
    check();
    return _ptr;
  }
#else
  operator T_slice*&() const
  {
    ((ArrayFixVar<T_elem, T_slice, T, n>*)this)->check();
    return (T_slice*&) _ptr;
  }
#endif
  const T_slice *in() const
  {
    return _ptr;
  }
  T_slice *inout()
  {
    return _ptr;
  }
  T_slice *out()
  {
    return _ptr;
  }
  T_slice *_retn()
  {
    check();
    T_slice *_p = _ptr;
    _ptr_backup = _ptr = NULL;
    return _p;
  }
};


template<class T_elem, class T_slice, class T, MICO_ULong n>
inline void
ArrayFixVar<T_elem, T_slice, T, n>::check()
{
    if( _ptr != _ptr_backup ) {
	if (_ptr_backup && _autofree)
	    delete[] (T_elem*) _ptr_backup;
	_ptr_backup = _ptr;
    }
}

template<class T_elem, class T_slice, class T, MICO_ULong n>
inline void
ArrayFixVar<T_elem, T_slice, T, n>::free()
{
    check();
    if (_ptr)
	delete[] (T_elem*) _ptr;
    _ptr = _ptr_backup = NULL;
}

template<class T_elem, class T_slice, class T, MICO_ULong n>
inline void
ArrayFixVar<T_elem, T_slice, T, n>::copy( T_slice* ptr )
{
    if (!ptr) {
	reset (0);
	return;
    }
    T_slice* s = (T_slice*) new T_elem[ n ];
    reset( s );
    T_elem *dest = (T_elem*) _ptr;
    T_elem *src = (T_elem*) ptr;
    int i = 0;
    while( i < n ) {
	*dest = *src;
	++dest;
	++src;
	i++;
    }
    /*
     * If the previous 5 lines are substituted with:
     *  for( int i = 0; i < n; i++ )
     *    dest[ i ] = src[ i ];
     * then g++ 2.7.2 gives an "internal compiler error"!
     * There are four other places in this file with
     * the same problem.
     */
}


/*
 * The following template defines the _var type for an array
 * of a variable length data type as described in [12.14].
 * The first argument denotes the element type of the array,
 * the second argument denotes the type for the array slice,
 * the third argument is the type of the array itself and
 * the fourth argument the number of T_elem contained in
 * the array (this is the product of all the dimension bounds).
 */

template<class T_elem, class T_slice, class T, MICO_ULong n>
class ArrayVarVar
{
private:
  T_slice *_ptr;
  T_slice *_ptr_backup;
  MICO_Boolean _autofree;
  
  void check();
  void free();
  void copy( T_slice* ptr );
  void reset( T_slice* ptr )
  {
    free();
    _ptr = _ptr_backup = ptr;
  }
  
public:
  ArrayVarVar()
  {
    // This initialization is needed because an ArrayVar may be
    // used as an out-parameter without prior initialization
    // (see example in [16.12])
    _ptr = _ptr_backup = (T_slice*) new T_elem[ n ];
    _autofree = TRUE;
  }
  ArrayVarVar (MICO_Boolean autofree)
  {
    // This initialization is needed because an ArrayVar may be
    // used as an out-parameter without prior initialization
    // (see example in [16.12])
    _ptr = _ptr_backup = (T_slice*) new T_elem[ n ];
    _autofree = autofree;
  }
  ArrayVarVar( T_slice *slice )
  {
    _ptr = _ptr_backup = slice;
    _autofree = TRUE;
  }
  ArrayVarVar( const ArrayVarVar<T_elem, T_slice, T, n> &arr )
  {
    _ptr = _ptr_backup = 0;
    copy (arr._ptr);
    _autofree = TRUE;
  }
  ArrayVarVar( const T &arr )
  {
    _ptr = _ptr_backup = 0;
    copy ((T_slice *)&arr);
    _autofree = TRUE;
  }
  ~ArrayVarVar()
  {
    free();
  }
  ArrayVarVar<T_elem, T_slice, T, n> &
  operator=( const ArrayVarVar<T_elem, T_slice, T, n> &arr )
  {
    if( this != &arr ) {
      copy (arr._ptr);
    }
    return *this;
  }
  ArrayVarVar<T_elem, T_slice, T, n> &
  operator=( T_slice *slice )
  {
    if( _ptr != slice )
      reset( slice );
    return *this;
  }
  void autofree (MICO_Boolean val)
  {
    _autofree = val;
  }
  T_slice& operator[]( MICO_ULong i )
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  const T_slice& operator[]( MICO_ULong i ) const
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  // g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
  operator const T_slice*() const
  {
    return _ptr;
  }
  operator T_slice* &()
  {
    check();
    return _ptr;
  }
#else
  operator T_slice*&() const
  {
    ((ArrayVarVar<T_elem, T_slice, T, n>*)this)->check();
    return (T_slice*&) _ptr;
  }
#endif
  const T_slice *in() const
  {
    return _ptr;
  }
  T_slice *inout()
  {
    check();
    return _ptr;
  }
  T_slice *&out()
  {
    check();
    return _ptr;
  }
  T_slice *_retn()
  {
    check();
    T_slice *_p = _ptr;
    _ptr_backup = _ptr = NULL;
    return _p;
  }
};

template<class T_elem, class T_slice, class T, MICO_ULong n>
inline void
ArrayVarVar<T_elem, T_slice, T, n>::check()
{
    if( _ptr != _ptr_backup ) {
	if (_ptr_backup && _autofree)
	    delete[] (T_elem*) _ptr_backup;
	_ptr_backup = _ptr;
    }
}

template<class T_elem, class T_slice, class T, MICO_ULong n>
inline void
ArrayVarVar<T_elem, T_slice, T, n>::free()
{
    check();
    if (_ptr)
	delete[] (T_elem*) _ptr;
    _ptr = _ptr_backup = NULL;
}

template<class T_elem, class T_slice, class T, MICO_ULong n>
inline void
ArrayVarVar<T_elem, T_slice, T, n>::copy( T_slice* ptr )
{
    if (!ptr) {
	reset (0);
	return;
    }
    T_slice* s = (T_slice*) new T_elem[ n ];
    reset( s );
    T_elem *dest = (T_elem*) _ptr;
    T_elem *src = (T_elem*) ptr;
    int i = 0;
    while( i < n ) {
	*dest = *src;
	++dest;
	++src;
	i++;
    }
    /*
     * If the previous 5 lines are substituted with:
     *  for( int i = 0; i < n; i++ )
     *    dest[ i ] = src[ i ];
     * then g++ 2.7.2 gives an "internal compiler error"!
     * There are four other places in this file with
     * the same problem.
     */
}


/*
 * The following template defines the _forany type for an array
 * as described in [16.12(5)].
 * The first argument denotes the element type of the array,
 * the second argument denotes the type for the array slice,
 * the third argument is the type of the array itself and
 * the fourth argument the number of T_elem contained in
 * the array (this is the product of all the dimension bounds).
 * The last argument is used to disambiguate different *_forany
 * types, which are structurally the same. Without it, the C++
 * would complain about redefinitions under certain circumstances.
 * This is because we use C++ templates for the mapping of _forany.
 */

template<class T_elem, class T_slice, class T, MICO_ULong n, class _dummy>
class ArrayFixForAny
{
private:
  T_slice* _ptr;
  MICO_Boolean _nocopy;

public:
  ArrayFixForAny()
  {
    _ptr = 0;
    _nocopy = FALSE;
  }
  ArrayFixForAny( T_slice *slice, MICO_Boolean nocopy = false )
  {
    _ptr = slice;
    _nocopy = nocopy;
  }
  ArrayFixForAny( const ArrayFixForAny<T_elem, T_slice, T, n, _dummy> &arr,
	       MICO_Boolean nocopy = false )
  {
    _ptr = arr._ptr;
    _nocopy = nocopy;
  }
  ArrayFixForAny<T_elem, T_slice, T, n, _dummy> &
  operator=( T_slice *slice )
  {
    _ptr = slice;
    return *this;
  }
  ArrayFixForAny<T_elem, T_slice, T, n, _dummy> &
  operator=( const ArrayFixForAny<T_elem, T_slice, T, n, _dummy> &arr )
  {
    _ptr = arr._ptr;
    return *this;
  }
  T_slice& operator[]( MICO_ULong i )
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  const T_slice& operator[]( MICO_ULong i ) const
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  // g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
  operator const T_slice*() const
  {
    return _ptr;
  }
  operator T_slice*&()
  {
    return _ptr;
  }
#else
  operator T_slice*&() const
  {
    return (T_slice*&) _ptr;
  }
#endif
  const T_slice *in() const
  {
    return _ptr;
  }
  T_slice *inout()
  {
    return _ptr;
  }
  T_slice *out()
  {
    return _ptr;
  }
  T_slice *_retn()
  {
    T_slice *_p = _ptr;
    _ptr = NULL;
    return _p;
  }
  void clear () const
  {
    ArrayFixForAny<T_elem, T_slice, T, n, _dummy> *me =
	(ArrayFixForAny<T_elem, T_slice, T, n, _dummy> *)this;
    if (me->_ptr && me->_nocopy) {
      delete[] (T_elem*)me->_ptr;
      me->_ptr = 0;
    }
  }
  void alloc () const
  {
    ArrayFixForAny<T_elem, T_slice, T, n, _dummy> *me =
	(ArrayFixForAny<T_elem, T_slice, T, n, _dummy> *)this;
    if (!me->_ptr) {
      me->_ptr = (T_slice*) new T_elem[ n ];
      me->_nocopy = TRUE;
    }
  }
};


template<class T_elem, class T_slice, class T, MICO_ULong n, class _dummy>
class ArrayVarForAny
{
private:
  T_slice* _ptr;
  MICO_Boolean _nocopy;
  
public:
  ArrayVarForAny()
  {
    _ptr = 0;
    _nocopy = TRUE;
  }
  ArrayVarForAny( T_slice *slice, MICO_Boolean nocopy = false )
  {
    _ptr = slice;
    _nocopy = nocopy;
  }
  ArrayVarForAny( const ArrayVarForAny<T_elem, T_slice, T, n, _dummy> &arr,
	       MICO_Boolean nocopy = false )
  {
    _ptr = arr._ptr;
    _nocopy = nocopy;
  }
  ArrayVarForAny<T_elem, T_slice, T, n, _dummy> &
  operator=( T_slice *slice )
  {
    _ptr = slice;
    return *this;
  }
  ArrayVarForAny<T_elem, T_slice, T, n, _dummy> &
  operator=( const ArrayVarForAny<T_elem, T_slice, T, n, _dummy> &arr )
  {
    _ptr = arr._ptr;
    return *this;
  }
  T_slice& operator[]( MICO_ULong i )
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  const T_slice& operator[]( MICO_ULong i ) const
  {
    assert (_ptr);
    return _ptr[ i ];
  }
  // g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
  operator const T_slice*() const
  {
    return _ptr;
  }
  operator T_slice*&()
  {
    return _ptr;
  }
#else
  operator T_slice*&() const
  {
    return (T_slice*&) _ptr;
  }
#endif
  const T_slice *in() const
  {
    return _ptr;
  }
  T_slice *inout()
  {
    return _ptr;
  }
  T_slice *&out()
  {
    return _ptr;
  }
  T_slice *_retn()
  {
    T_slice *_p = _ptr;
    _ptr = NULL;
    return _p;
  }
  void clear () const
  {
    ArrayVarForAny<T_elem, T_slice, T, n, _dummy> *me =
	(ArrayVarForAny<T_elem, T_slice, T, n, _dummy> *)this;
    if (me->_ptr && me->_nocopy) {
      delete[] (T_elem*)me->_ptr;
      me->_ptr = 0;
    }
  }
  void alloc () const
  {
    ArrayVarForAny<T_elem, T_slice, T, n, _dummy> *me =
	(ArrayVarForAny<T_elem, T_slice, T, n, _dummy> *)this;
    if (!me->_ptr) {
      me->_ptr = (T_slice*) new T_elem[ n ];
      me->_nocopy = TRUE;
    }
  }
};

#endif
