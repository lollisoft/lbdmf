/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#ifndef __ERROR_H__
#define __ERROR_H__

#include <iostream.h>

#include <CORBA.h>
#include <mico/template_impl.h>
#include "parsenode.h"


class IDLError
{
private:
  int    _err_num;
  string _msg;
public:
  IDLError();
  IDLError( int err_num, ... );
  IDLError( int err_num, ParseNode *n, ... );
  IDLError( const IDLError &err );
  IDLError& operator=( const IDLError &err );

  ostream& print (ostream &o) const
  {
    o << _msg;
    return o;
  }
};

static inline ostream& operator<<( ostream& o, const IDLError& err )
{
  return err.print (o);
}


#endif
