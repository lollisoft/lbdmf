#include "parse_tree.h"

#include <iostream.h>
#include <assert.h>

bool ParseTreeOR::eval( ParseContext *_context )
{
  ParseContext c1( _context );
  ParseContext c2( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( !m_pRight->eval( &c2 ) )
    return false;
  if ( c1.type != ParseContext::T_BOOL )
    return false;
  if ( c2.type != ParseContext::T_BOOL )
    return false;
  
  _context->b = ( c1.b || c2.b );
  _context->type = ParseContext::T_BOOL;
  
  return true;
}

bool ParseTreeAND::eval( ParseContext *_context )
{
  _context->type = ParseContext::T_BOOL;

  ParseContext c1( _context );
  ParseContext c2( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( c1.type != ParseContext::T_BOOL )
    return false;
  if ( !c1.b )
  {
    _context->b = false;
    return true;
  }
  
  if ( !m_pRight->eval( &c2 ) )
    return false;
  if ( c2.type != ParseContext::T_BOOL )
    return false;

  _context->b = ( c1.b && c2.b );
  
  return true;
}

bool ParseTreeCALC::eval( ParseContext *_context )
{
  ParseContext c1( _context );
  ParseContext c2( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( !m_pRight->eval( &c2 ) )
    return false;

  // Bool extension
  if ( c1.type != ParseContext::T_NUM && c1.type != ParseContext::T_FLOAT && c1.type != ParseContext::T_BOOL )
    return false;
  // Bool extension
  if ( c2.type != ParseContext::T_NUM && c2.type != ParseContext::T_FLOAT && c2.type != ParseContext::T_BOOL )
    return false;
  // Bool extension
  if ( c1.type == ParseContext::T_BOOL && c2.type == ParseContext::T_BOOL )
    return false;
  
  /**
   * Make types compatible
   */
  if ( c1.type == ParseContext::T_NUM && c2.type == ParseContext::T_FLOAT )
  {      
    c1.type = ParseContext::T_FLOAT;
    c1.f = (float)c1.i;
  }
  else if ( c1.type == ParseContext::T_FLOAT && c2.type == ParseContext::T_NUM )
  {      
    c2.type = ParseContext::T_FLOAT;
    c2.f = (float)c2.i;
  }
  // Bool extension
  else if ( c1.type == ParseContext::T_BOOL && c2.type == ParseContext::T_NUM )
  {      
    c1.type = ParseContext::T_NUM;
    if ( c1.b )
      c1.i = 1;
    else
      c1.i = -1;
  }
  // Bool extension
  else if ( c1.type == ParseContext::T_BOOL && c2.type == ParseContext::T_FLOAT )
  {      
    c1.type = ParseContext::T_FLOAT;
    if ( c1.b )
      c1.f = 1.0;
    else
      c1.f = -1.0;
  }
  // Bool extension
  else if ( c1.type == ParseContext::T_NUM && c2.type == ParseContext::T_BOOL )
  {      
    c2.type = ParseContext::T_NUM;
    if ( c2.b )
      c2.i = 1;
    else
      c2.i = -1;
  }
  // Bool extension
  else if ( c1.type == ParseContext::T_FLOAT && c2.type == ParseContext::T_BOOL )
  {      
    c2.type = ParseContext::T_FLOAT;
    if ( c2.b )
      c2.f = 1.0;
    else
      c2.f = -1.0;
  }

  _context->type = c1.type;
  
  /**
   * Calculate
   */
  switch( m_cmd )
  {
  case 1: /* Add */
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->f = ( c1.f + c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->i = ( c1.i + c2.i );
      return true;
    }
    break;
  case 2: /* Sub */
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->f = ( c1.f - c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->i = ( c1.i - c2.i );
      return true;
    }
    break;
  case 3: /* Mul */
    if ( c1.type == ParseContext::T_FLOAT )
    {
      cout << "Float Mult" << endl;
      _context->f = ( c1.f * c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->i = ( c1.i * c2.i );
      return true;
    }
    break;
  case 4: /* Div */
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->f = ( c1.f / c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->i = ( c1.i / c2.i );
      return true;
    }
    break;
  }
  
  return false;
}

bool ParseTreeCMP::eval( ParseContext *_context )
{
  cout << "CMP 1 cmd=" << m_cmd << endl;
  ParseContext c1( _context );
  ParseContext c2( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;

  if ( !m_pRight->eval( &c2 ) )
    return false;

  /**
   * Make types compatible
   */
  if ( c1.type == ParseContext::T_NUM && c2.type == ParseContext::T_FLOAT )
  {      
    c1.type = ParseContext::T_FLOAT;
    c1.f = (float)c1.i;
  }
  else if ( c1.type == ParseContext::T_FLOAT && c2.type == ParseContext::T_NUM )
  {      
    c2.type = ParseContext::T_FLOAT;
    c2.f = (float)c2.i;
  }

  /**
   * Compare
   */
  _context->type = ParseContext::T_BOOL;
  
  switch( m_cmd )
  {
  case 1: /* EQ */
    if ( c1.type != c2.type )
    {
      _context->b = false;
      return true;
    }
    if ( c1.type == ParseContext::T_STRING )
    {
      _context->b = ( c1.str == c2.str );
      return true;
    }
    if ( c1.type == ParseContext::T_BOOL )
    {
      _context->b = ( c1.b == c2.b );
      return true;
    }
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->b = ( c1.f == c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->b = ( c1.i == c2.i );
      return true;
    }
    break;
  case 2: /* NEQ */
    if ( c1.type != c2.type )
    {
      _context->b = true;
      return true;
    }
    if ( c1.type == ParseContext::T_STRING )
    {
#if 0
      //AP
      _context->b = ( c1.str != c2.str );
#else
      _context->b = ( !(c1.str == c2.str) );
#endif
      return true;
    }
    if ( c1.type == ParseContext::T_BOOL )
    {
      _context->b = ( c1.b != c2.b );
      return true;
    }
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->b = ( c1.f != c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->b = ( c1.i != c2.i );
      return true;
    }
    break;
  case 3: /* GEQ */
    if ( c1.type != c2.type )
    {
      _context->b = false;
      return true;
    }
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->b = ( c1.f >= c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->b = ( c1.i >= c2.i );
      return true;
    }
    _context->b = false;
    return true;

  case 4: /* LEQ */
    if ( c1.type != c2.type )
    {
      _context->b = false;
      return true;
    }
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->b = ( c1.f <= c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->b = ( c1.i <= c2.i );
      return true;
    }
    _context->b = false;
    return true;

  case 5: /* < */
    if ( c1.type != c2.type )
    {
      _context->b = false;
      return true;
    }
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->b = ( c1.f < c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->b = ( c1.i < c2.i );
      return true;
    }
    _context->b = false;
    return true;

  case 6: /* > */
    if ( c1.type != c2.type )
    {
      _context->b = false;
      return true;
    }
    if ( c1.type == ParseContext::T_FLOAT )
    {
      _context->b = ( c1.f > c2.f );
      return true;
    }
    if ( c1.type == ParseContext::T_NUM )
    {
      _context->b = ( c1.i > c2.i );
      return true;
    }
    _context->b = false;
    return true;

  }
  
  return false;
}

bool ParseTreeNOT::eval( ParseContext *_context )
{
  ParseContext c1( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( c1.type != ParseContext::T_BOOL )
    return false;
  
  _context->b = !c1.b;
  _context->type = ParseContext::T_BOOL;
  
  return true;
}

bool ParseTreeEXIST::eval( ParseContext *_context )
{
  _context->type = ParseContext::T_BOOL;

  int max = _context->seq->length();
  int i;
  for( i = 0; i < max; i++ )
  {
    cout << "Comparing " << (const char*)((*_context->seq)[i].name) << " with " << m_pId << endl;
    if ( strcmp( (const char*)((*_context->seq)[i].name), m_pId ) == 0 )
    {
      _context->b = true;
      return true;
    }
  }
  
  _context->b = false;
  return true;
}

bool ParseTreeMATCH::eval( ParseContext *_context )
{
  _context->type = ParseContext::T_BOOL;
  
  ParseContext c1( _context );
  ParseContext c2( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( !m_pRight->eval( &c2 ) )
    return false;
  if ( c1.type != ParseContext::T_STRING || c2.type != ParseContext::T_STRING )
  {
    cout << "Wrong types" << endl;
    return false;
  }

  cout << "Matching " << c1.str.c_str() << " against " << c2.str.c_str() << endl;
  
  if ( strstr( c2.str.c_str(), c1.str.c_str() ) != 0L )
    _context->b = true;
  else
    _context->b = false;

  return true;
}

bool ParseTreeIN::eval( ParseContext *_context )
{
  cout << "IN" << endl;

  _context->type = ParseContext::T_BOOL;
  
  ParseContext c1( _context );
  ParseContext c2( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( !m_pRight->eval( &c2 ) )
    return false;

  if ( c1.type == ParseContext::T_NUM && c2.type == ParseContext::T_NUM_SEQ )
  {
    int max = c2.numSeq.length();
    int i;
    for( i = 0; i < max; i++ )
    {
      if ( c1.i == c2.numSeq[i] )
      {
	_context->b = true;
	return true;
      }
    }
    _context->b = false;
    return true;    
  }

  if ( c1.type == ParseContext::T_FLOAT && c2.type == ParseContext::T_FLOAT_SEQ )
  {
    int max = c2.numSeq.length();
    int i;
    for( i = 0; i < max; i++ )
    {
      if ( c1.f == c2.floatSeq[i] )
      {
	_context->b = true;
	return true;
      }
    }
    _context->b = false;
    return true;    
  }

  if ( c1.type == ParseContext::T_STRING && c2.type == ParseContext::T_STR_SEQ )
  {
    int max = c2.numSeq.length();
    int i;
    for( i = 0; i < max; i++ )
    {
      if ( strcmp( c1.str.c_str(), c2.strSeq[i] ) == 0 )
      {
	_context->b = true;
	return true;
      }
    }
    _context->b = false;
    return true;    
  }

  cout << "Wrong types" << endl;
  return false;
}

bool ParseTreeID::eval( ParseContext *_context )
{
  int max = _context->seq->length();
  int i;
  for( i = 0; i < max; i++ )
  {
    if ( strcmp( (const char*)((*_context->seq)[i].name), m_str.c_str() ) == 0 )
      break;
  }
  // Identifier unknown ?
  if ( i == max )
    return false;
  
  char *p;
  if ( (*_context->seq)[i].value >>= p )
  {
    _context->str = p;
    _context->type = ParseContext::T_STRING;
    return true;
  }

  CORBA::Long l;
  if ( (*_context->seq)[i].value >>= l )
  {
    _context->i = l;
    _context->type = ParseContext::T_NUM;
    return true;
  }

  CORBA::ULong ul;
  if ( (*_context->seq)[i].value >>= ul )
  {
    _context->i = ul;
    _context->type = ParseContext::T_NUM;
    return true;
  }

  CORBA::Boolean b;
  if ( ( (*_context->seq)[i].value >>= CORBA::Any::to_boolean( b ) ) )
  {
    _context->b = b;
    _context->type = ParseContext::T_BOOL;
    return true;
  }
  
  CORBA::Float f;
  if ( (*_context->seq)[i].value >>= f )
  {
    _context->f = f;
    _context->type = ParseContext::T_FLOAT;
    return true;
  }

  if ( ( (*_context->seq)[i].value >>= _context->numSeq ) )
  {
    cout << "List " << _context->numSeq.length();
    _context->type = ParseContext::T_NUM_SEQ;
    return true;
  }

  if ( ( (*_context->seq)[i].value >>= _context->floatSeq ) )
  {
    cout << "Float List " << _context->floatSeq.length() << endl;
    _context->type = ParseContext::T_FLOAT_SEQ;
    return true;
  }

  if ( ( (*_context->seq)[i].value >>= _context->strSeq ) )
  {
    cout << "List Str " << _context->strSeq.length() << endl;
    _context->type = ParseContext::T_STR_SEQ;
    return true;
  }

  cout << "Any does not work" << endl;
  
  // Value has unknown type 
  return false;
}

bool ParseTreeWITH::eval( ParseContext *_context )
{
  ParseContext c1( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( c1.type != ParseContext::T_BOOL )
    return false;
  
  _context->b = c1.b;
  _context->type = ParseContext::T_BOOL;
  
  return true;
}

bool ParseTreeMIN::eval( ParseContext *_context )
{
  ParseContext c1( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  if ( c1.type == ParseContext::T_NUM )
  {
    _context->i = c1.i;
    _context->type = ParseContext::T_NUM;
    return true;
  }
  else if ( c1.type == ParseContext::T_FLOAT )
  {
    _context->f = c1.f;
    _context->type = ParseContext::T_FLOAT;
    return true;
  }

  return false;
}

bool ParseTreeMAX::eval( ParseContext *_context )
{
  ParseContext c1( _context );
  if ( !m_pLeft->eval( &c1 ) )
    return false;
  
  if ( c1.type == ParseContext::T_NUM )
  {
    _context->i = c1.i;
    _context->type = ParseContext::T_NUM;
    return true;
  }
  else if ( c1.type == ParseContext::T_FLOAT )
  {
    _context->f = c1.f;
    _context->type = ParseContext::T_FLOAT;
    return true;
  }

  return false;
}

bool ParseTreeFIRST::eval( ParseContext *_context )
{
  _context->b = true;
  _context->type = ParseContext::T_BOOL;
  
  return true;
}

bool ParseTreeRANDOM::eval( ParseContext *_context )
{
  _context->b = true;
  _context->type = ParseContext::T_BOOL;
  
  return true;
}

int matchConstraint( ParseTreeBase *_tree, CosTrading::PropertySeq *_props )
{
  if ( !_tree )
    return 1;
  
  ParseContext c( _props );

  if ( !_tree->eval( &c ) )
    return -1;
  
  if ( c.type != ParseContext::T_BOOL )
    return -2;

  if ( c.b )
    return 1;
  return 0;
}

int matchPreferences( ParseTreeBase *_tree, CosTrading::PropertySeq *_props, PreferencesReturn &_ret )
{
  if ( !_tree )
  {
    _ret.type = PreferencesReturn::PRT_ERROR;    
    return -1;
  }
  
  if ( _tree->isA( "ParseTreeRandom" ) || _tree->isA( "ParseTreeFirst" ) )
  {
    _ret.type = PreferencesReturn::PRT_NUM;
    _ret.i = 0;
    return 1;
  }
 
  ParseContext c( _props );

  if ( !_tree->eval( &c ) )
  {
    _ret.type = PreferencesReturn::PRT_ERROR;
    return -2;
  }

  if ( _tree->isA( "ParseTreeWith" ) )
  {
    if ( c.type != ParseContext::T_BOOL )
    {
      _ret.type = PreferencesReturn::PRT_ERROR;
      return -3;
    }
    
    _ret.type = PreferencesReturn::PRT_NUM;
    if ( c.b )
      _ret.i = 1;
    else
      _ret.i = 0;
    
    return 1;
  }

  // ParseTreeMin and ParseTreeMax are handled here
  assert( _tree->isA( "ParseTreeMin" ) || _tree->isA( "ParseTreeMax" ) );
  
  if ( c.type == ParseContext::T_NUM )
  {
    _ret.type = PreferencesReturn::PRT_NUM;
    _ret.i = c.i;
  }
  else if ( c.type == ParseContext::T_FLOAT )
  {
    _ret.type = PreferencesReturn::PRT_FLOAT;
    _ret.f = c.f;
  }
  else
  {
    _ret.type = PreferencesReturn::PRT_ERROR;    
    return -4;
  }
  
  return 1;
}
