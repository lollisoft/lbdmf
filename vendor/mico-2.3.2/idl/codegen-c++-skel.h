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

#ifndef __CODEGENCPP_SKEL_H__
#define __CODEGENCPP_SKEL_H__

#include "codegen-c++-util.h"


class CodeGenCPPSkel : virtual public CodeGenCPPUtil
{
protected:
  void emit_skel();

private:
  void get_dispatcher_list( CORBA::InterfaceDef_ptr in,
			    CORBA::OpDescriptionSeq &ops,
			    CORBA::AttrDescriptionSeq &attr );
  void emit_attr_dispatcher (CORBA::AttributeDescription &attr,
			     CORBA::Flags = CORBA::PARAM_INOUT);
  void emit_sii_method_dispatcher( string &dispatch_name,
				   CORBA::OperationDescription &op,
				   CORBA::IDLType_ptr result );
  void emit_dispatcher( CORBA::OpDescriptionSeq &ops,
			CORBA::AttrDescriptionSeq &attr );
  CORBA::ULong get_prime_number( CORBA::ULong n );

public:
  CodeGenCPPSkel( DB &db, IDLParam &params );
};


#endif
