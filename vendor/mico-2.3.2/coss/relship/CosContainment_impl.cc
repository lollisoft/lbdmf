/*
 *  Relationship Service for MICO
 *  Copyright (C) 1998-99 Karel Gardas
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
 *  or to my private e-mail:
 *                 gardask@alpha.inf.upol.cz
 */

#include <fstream.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <mico/CosContainment_impl.h> 


//#define DEBUG 1


ContainsRole_impl::ContainsRole_impl ()
#ifndef _WINDOWS
  : CosGraphs_impl::Role_impl (),
    POA_CosContainment::ContainsRole ()
#endif
{
}


ContainsRole_impl::ContainsRole_impl (CosRelationships::RelatedObject_ptr obj)
#ifndef _WINDOWS
  : CosGraphs_impl::Role_impl (),
    POA_CosContainment::ContainsRole ()
#endif
{
#if DEBUG
  cout << "  <ContainsRole_impl> constructor with params\n";
#endif
  rel_obj = obj;
}


ContainedInRole_impl::ContainedInRole_impl ()
#ifndef _WINDOWS
  : CosGraphs_impl::Role_impl (),
    POA_CosContainment::ContainedInRole ()
#endif
{
}


ContainedInRole_impl::ContainedInRole_impl 
(CosRelationships::RelatedObject_ptr obj)
#ifndef _WINDOWS
  : CosGraphs_impl::Role_impl (),
    POA_CosContainment::ContainedInRole ()
#endif
{
#if DEBUG
  cout << "  <ContainedInRole_impl> constructor with params\n";
#endif
  rel_obj = obj;
}


Containment_impl::Containment_impl ()
  : Relationship_impl ()
#ifndef _WINDOWS
   , POA_CosContainment::Relationship ()
#endif
{
}


Containment_impl::Containment_impl (CosRelationships::NamedRoles nr)
  : Relationship_impl (nr)
#ifndef _WINDOWS
   , POA_CosContainment::Relationship ()
#endif
{
}





