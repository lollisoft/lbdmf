#include "typerepo_impl.h"

#include <string>
#include <list>
#include <iostream.h>

#include <string.h>

// moved operators here for Sun CC ...
bool operator!= ( const CosTradingRepos::ServiceTypeRepository::PropStruct& p1,
		  const CosTradingRepos::ServiceTypeRepository::PropStruct& p2 )
{
  if ( p1.mode != p2.mode )
    return true;
  
  if ( !p1.value_type->equal( p2.value_type ) )
    return true;
  
  return false;
}

bool operator< ( const CosTradingRepos::ServiceTypeRepository::IncarnationNumber& i1,
		 const CosTradingRepos::ServiceTypeRepository::IncarnationNumber& i2 )
{
  if ( i1.high < i2.high )
    return true;
  if ( i1.high > i2.high )
    return false;
  if ( i1.low < i2.low )
    return true;
  return false;
}


TypeRepository_impl::TypeRepository_impl( Trader* _trader )
{
  m_pTrader = _trader;

  m_incarnation.high = 0;
  m_incarnation.low = 0;
}

CosTradingRepos::ServiceTypeRepository::IncarnationNumber TypeRepository_impl::incarnation()
{
  return m_incarnation;
}

CosTradingRepos::ServiceTypeRepository::IncarnationNumber
TypeRepository_impl::add_type( const char* name,
			  const char* if_name,
			  const CosTradingRepos::ServiceTypeRepository::PropStructSeq& props,
			  const CosTradingRepos::ServiceTypeRepository::ServiceTypeNameSeq& super_types )
{
  /**
   * Find duplicate entries
   */
#if 0
  //AP
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct>::iterator it = m_mapTypes.find( static_cast<const char*>(name) );
#else
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct, less<string> >::iterator it = m_mapTypes.find( (const char *)name );
#endif
  if ( it != m_mapTypes.end() )
  {
    CosTradingRepos::ServiceTypeRepository::DuplicateServiceTypeName exc;
    exc.name = CORBA::string_dup( name );
    mico_throw( exc );
  }

  /**
   * Do all super types exist ?
   */
  int len = super_types.length();
  for( int i = 0; i < len; i++ )
  {
#if 0
    //AP
    map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct>::iterator it =
      m_mapTypes.find( static_cast<const char*>( super_types[ i ] ) );
#else
    map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct, less<string> >::iterator it =
      m_mapTypes.find( (const char*)( super_types[ i ] ) );
#endif

    if ( it == m_mapTypes.end() )
    {
      CosTrading::UnknownServiceType exc;
      exc.type = CORBA::string_dup( super_types[ i ] );
      mico_throw( exc );
    }
  }
    
  /**
   * Create the new type
   */
  TypeStruct type;

  type.if_name = CORBA::string_dup( if_name );
  type.props = props;
  type.super_types = super_types;
  type.masked = false;
  type.incarnation = m_incarnation;
  
  /**
   * Check for duplicate property names
   */
#if 0
  //AP
  map<string,bool> mp;
#else
  map<string,bool,less<string> > mp;
#endif
  for( int j = 0; j < type.props.length(); j++ )
  {
#if 0
    //AP
    map<string,bool>::iterator it = mp.find( static_cast<const char*>(type.props[j].name) );
#else
    map<string,bool,less<string> >::iterator it = mp.find( (const char*)(type.props[j].name) );
#endif

    if ( it != mp.end() )
    {
      CosTrading::DuplicatePropertyName exc;
      exc.name = CORBA::string_dup( type.props[j].name );
      mico_throw( exc );
    }
    mp[ (const char*)(type.props[j].name) ] = true;
  }
  
  /**
   * Check for redefinitions of properties
   */
  // Make a copy
  TypeStruct t2 = type;
  // Recursion over all super types to get all properties
  for( int k = 0; k < type.super_types.length(); k++ )
  {
#if 0
    //AP
    map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct>::iterator it2 = checkServiceType( type.super_types[ k ] );
#else
    map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it2 = checkServiceType( type.super_types[ k ] );
#endif
    fully_describe_type( &t2, (*it2).second );
  }
  // Find duplicate properties
#if 0
  //AP
  map<string,CosTradingRepos::ServiceTypeRepository::PropStruct> map2;
#else
  map<string,CosTradingRepos::ServiceTypeRepository::PropStruct,less<string> > map2;
#endif

  for( int l = 0; l < t2.props.length(); l++ )
  {
#if 0
    //AP
    map<string,CosTradingRepos::ServiceTypeRepository::PropStruct>::iterator it =
#else
    map<string,CosTradingRepos::ServiceTypeRepository::PropStruct,less<string> >::iterator it =
#endif
      map2.find( (const char*)(t2.props[l].name) );
    if ( it != map2.end() )
    {
      // Compare properties
      if ( t2.props[l] != (*it).second )
      {
	CosTradingRepos::ServiceTypeRepository::ValueTypeRedefinition exc;
	exc.type_1 = CORBA::string_dup( "HACK" );
	exc.type_2 = CORBA::string_dup( "HACK" );
	exc.definition_1 = t2.props[l];
	exc.definition_2 = (*it).second;
	mico_throw( exc );
      }
    }
    map2[ (const char*)(t2.props[l].name) ] = t2.props[l];
  }

  // TODO: Check wethe the interface is really a subtype of the super types interfaces.
  //       Use the IR. Dont throw an error if the interfaces are unknown

  /**
   * Add the new type
   */
  m_mapTypes[ (const char*)( name ) ] = type;
  
  incIncarnationNumber();
  
  return type.incarnation;
}

void TypeRepository_impl::remove_type( const char* name )
{
  /**
   * Does the service type exist ?
   */
#if 0
  //AP
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct>::iterator it = checkServiceType( name );
#else
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = checkServiceType( name );
#endif
  
  /**
   * Check wether it has sub types.
   */
  // Iterate over all registered sub types
#if 0
  //AP
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct>::iterator it2 = m_mapTypes.begin();
#else
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it2 = m_mapTypes.begin();
#endif
  for( ; it2 != m_mapTypes.end(); ++it2 )
  {
    // Iterate over all super types
    for( int i = 0; (*it2).second.super_types.length(); i++ )
    {
      if ( strcmp( (*it2).second.super_types[i], name ) == 0  )
      {
	CosTradingRepos::ServiceTypeRepository::HasSubTypes exc;
	exc.the_type = name;
	exc.sub_type = CORBA::string_dup( (*it2).first.c_str() );
	mico_throw( exc );
      }
    }
  }
  
  /**
   * Remove the service type.
   */
  m_mapTypes.erase( it );
}

CosTradingRepos::ServiceTypeRepository::ServiceTypeNameSeq*
TypeRepository_impl::list_types( const CosTradingRepos::ServiceTypeRepository::SpecifiedServiceTypes& which_types )
{
  /**
   * Handle the switch
   */
  bool all = true;
  CosTradingRepos::ServiceTypeRepository::IncarnationNumber inc;
  
  if ( which_types._d() == CosTradingRepos::ServiceTypeRepository::since )
  {
    all = false;
    inc = which_types.incarnation();
  }

  /**
   * Find list of service types
   */
  list<string> lst;
#if 0
  //AP
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct>::iterator it = m_mapTypes.begin();
#else
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = m_mapTypes.begin();
#endif
  for( ; it != m_mapTypes.end(); ++it )
  {
    if ( all )
    {
      lst.push_back( (*it).first );
    }
    else
    {
      CosTradingRepos::ServiceTypeRepository::IncarnationNumber i = (*it).second.incarnation;
      if ( m_incarnation < i)
	lst.push_back( (*it).first );
    }
  }
  
  /**
   * Create answer
   */
  CosTradingRepos::ServiceTypeRepository::ServiceTypeNameSeq *seq = new CosTradingRepos::ServiceTypeRepository::ServiceTypeNameSeq;
  seq->length( lst.size() );
  
  list<string>::iterator it2 = lst.begin();
  int k = 0;
  for( ; it2 != lst.end(); ++it2 )
    (*seq)[ k++ ] = CORBA::string_dup( (*it2).c_str() );
    
  return seq;
}

CosTradingRepos::ServiceTypeRepository::TypeStruct* TypeRepository_impl::describe_type( const char* name )
{
  /**
   * Does the service type exist ?
   */
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = checkServiceType( name );
  
  CosTradingRepos::ServiceTypeRepository::TypeStruct* t = new CosTradingRepos::ServiceTypeRepository::TypeStruct;
  *t = (*it).second;
  
  return t;
}

CosTradingRepos::ServiceTypeRepository::TypeStruct*
TypeRepository_impl::fully_describe_type( const char* name )
{
  /**
   * Does the service type exist ?
   */
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = checkServiceType( name );
  
  CosTradingRepos::ServiceTypeRepository::TypeStruct* t = new CosTradingRepos::ServiceTypeRepository::TypeStruct;
  *t = (*it).second;

  /**
   * Recursion over all super types
   */
  for( int i = 0; i < t->super_types.length(); i++ )
  {
    map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it2 = checkServiceType( t->super_types[ i ] );
    fully_describe_type( t, (*it2).second );
  }

  return t;
}

void TypeRepository_impl::fully_describe_type( CosTradingRepos::ServiceTypeRepository::TypeStruct* result,
					  CosTradingRepos::ServiceTypeRepository::TypeStruct& super_type )
{
  /**
   * Add properties
   */
  int len = result->props.length();
  result->props.length( len + super_type.props.length() );
  for( int k = 0; k < super_type.props.length(); k++ )
  {
    result->props[ len + k ] = super_type.props[ k ];
  }

  /**
   * Recursion over all super types
   */
  for( int i = 0; i < super_type.super_types.length(); i++ )
  {
    // Add supertypes
    int len = result->super_types.length();
    result->super_types.length( len + 1 );
    result->super_types[ len ] = super_type.super_types[ i ];

    // Recursion
    map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = checkServiceType( super_type.super_types[ i ] );
    fully_describe_type( result, (*it).second );
  }
}

void TypeRepository_impl::mask_type( const char* name )
{
  /**
   * Does the service type exist ?
   */
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = checkServiceType( name );

  /**
   * Is it already masked ?
   */
  if ( (*it).second.masked )
  {
    CosTradingRepos::ServiceTypeRepository::AlreadyMasked esc;
    esc.name = CORBA::string_dup( name );
    mico_throw( esc );
  }
  
  /**
   * Mask it
   */
  (*it).second.masked = true;
}

void TypeRepository_impl::unmask_type( const char* name )
{
  /**
   * Does the service type exist ?
   */
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = checkServiceType( name );

  /**
   * Is it not masked ?
   */
  if ( !(*it).second.masked )
  {
    CosTradingRepos::ServiceTypeRepository::NotMasked esc;
    esc.name = CORBA::string_dup( name );
    mico_throw( esc );
  }
  
  /**
   * Unmask it
   */
  (*it).second.masked = false;
}

/*******************************************************************
 *
 * Extensions for the internal use
 *
 *******************************************************************/

bool TypeRepository_impl::isSubTypeOf( const char* sub, const char* super )
{
  // Check the trivial case
  if ( strcmp( sub, super ) == 0 )
    return true;
  
  CosTradingRepos::ServiceTypeRepository::TypeStruct_var v = fully_describe_type( sub );
  
  for( int i = 0; i < v->super_types.length(); i++ )
    if ( strcmp( v->super_types[i], super ) == 0 )
      return true;
  
  return false;
}

bool TypeRepository_impl::isServiceTypeKnown( const char* name )
{
  /**
   * Does the service type exist ?
   */
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = m_mapTypes.find( (const char*)(name) );

  return ( it != m_mapTypes.end() );
}

/*******************************************************************
 *
 * Helper functions
 *
 *******************************************************************/

#include <stdio.h>
#include <sys/stat.h>

void TypeRepository_impl::incIncarnationNumber()
{
  m_incarnation.low++;
  if ( m_incarnation.low == 0 )
    m_incarnation.high++;
}

map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator
TypeRepository_impl::checkServiceType( const char* name )
{
  /**
   * Does the service type exist ?
   */
  map<string,CosTradingRepos::ServiceTypeRepository::TypeStruct,less<string> >::iterator it = m_mapTypes.find( (const char*)(name) );
  if ( it == m_mapTypes.end() )
  {
    CosTrading::UnknownServiceType exc;
    exc.type = CORBA::string_dup( name );
    mico_throw( exc );
  }

  return it;
}
