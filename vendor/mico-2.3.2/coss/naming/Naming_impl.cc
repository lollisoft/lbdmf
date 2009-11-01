/*
 *  Implementation of COSS Naming Service for MICO
 *  Copyright (C) 1997 Kai-Uwe Sattler
 *  Interoperable Naming Service extension by Frank Pilhofer
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

#define MICO_CONF_IMR
#define MICO_CONF_POA

#include <CORBA-SMALL.h>
#include <iostream.h>
#include <fstream.h>
#include <Naming_impl.h>
#include <mico/util.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

/*
 * NamingContext
 */

string NamingContext_impl::impl_name;
CORBA::ORB_ptr NamingContext_impl::useorb;
PortableServer::POA_ptr NamingContext_impl::usepoa;
NamingContext_impl * NamingContext_impl::root;
NamingContext_impl::ServantMap NamingContext_impl::svmap;

NamingContext_impl::NamingContext_impl (CORBA::ORB_ptr orb,
					PortableServer::POA_ptr poa,
					const char * in)
{
  useorb = CORBA::ORB::_duplicate (orb);
  usepoa = PortableServer::POA::_duplicate (poa);
  root = this;

  if (in) {
    impl_name = in;
  }
}

NamingContext_impl::NamingContext_impl ()
{
}

NamingContext_impl::~NamingContext_impl ()
{
  if (this == root) {
    root = NULL;
    CORBA::release (usepoa);
    CORBA::release (useorb);
    usepoa = PortableServer::POA::_nil ();
    useorb = CORBA::ORB::_nil ();
  }
}

void
NamingContext_impl::save (const char * name)
{
  if (impl_name.length() == 0 || table.size() == 0) {
    return;
  }

  string fname = impl_name;
  fname += name;
  fname += ".inf";

  ofstream out (fname.c_str());

  BindingTable::iterator i = table.begin ();
  for (; i != table.end (); i++) {
    NmCtxBinding b = (*i).second;
    CORBA::String_var ior;

    if (!CORBA::is_nil (b.obj)) {
      ior = useorb->object_to_string (b.obj);
    }
    else {
      ior = (const char *) "(null)";
    }

    out << b.btype << " \"" << (*i).first.id.in() << "\" \""
	<< (*i).first.kind.in() << "\" "
	<< ior.in()
	<< endl;
  }
}

void
NamingContext_impl::restore (const char * name)
{
  if (impl_name.length() == 0) {
    return;
  }

  string fname = impl_name;
  fname += name;
  fname += ".inf";

  ifstream in (fname.c_str());

  if (!in) {
    return;
  }

  cout << "restore persistent state from " << fname.c_str() << endl;

  while (! in.eof ()) {
    int flag;
    string id, kind;
    string objref;
    string tmp;

    in >> flag >> id >> kind >> objref;
    /*
    cout << "type = " << flag << "\nid = " << id
	 << "\nkind = " << kind << "\nobjref = "
         << objref << endl;
	 */
    if (objref.size () == 0)
      continue;
    NmCtxBinding binding;
    CosNaming::NameComponent nc;

    tmp = kind.substr (1, kind.size () - 2);
    nc.kind = CORBA::string_dup (tmp.c_str ());
    tmp = id.substr (1, id.size () - 2);
    nc.id = CORBA::string_dup (tmp.c_str ());
    binding.btype = (flag == 1 ? CosNaming::ncontext : CosNaming::nobject);

    if (strcmp (objref.c_str(), "(null)") == 0) {
      binding.obj = CORBA::Object::_nil ();
    }
    else {
      binding.obj = useorb->string_to_object (objref.c_str());
    }

    table[nc] = binding;
    /*
    cout << "-- bound name = " << tmp
         << " to object = " << objref << endl;
	 */
  }

  unlink (fname.c_str());
}

void NamingContext_impl::_do_bind (const CosNaming::Name& n, 
				   CORBA::Object_ptr obj,
				   CosNaming::BindingType btype,
				   CORBA::Boolean rebind)
{
  if (n.length () == 0) 
    mico_throw (CosNaming::NamingContext::InvalidName ());

  BindingTable::iterator i = table.find (n[0]);
  if (n.length () == 1) {
    if (i != table.end () && !rebind) {
      mico_throw (CosNaming::NamingContext::AlreadyBound ());
    }
    else {
      NmCtxBinding binding;

      binding.btype = btype;
      binding.obj = CORBA::Object::_duplicate (obj);
      table[n[0]] = binding;
      /*
      cout << "bound name = " << n[0].id 
           << " to object = " << _orbnc()->object_to_string (obj) << endl;
       */
    }
  }
  else {
    if (i == table.end ()) {
      CosNaming::NamingContext::NotFound exc;
      exc.why = CosNaming::NamingContext::missing_node;
      exc.rest_of_name = n;
      mico_throw (exc);
    }

    NmCtxBinding binding = (*i).second;
    if (binding.btype != CosNaming::ncontext)
      mico_throw (CosNaming::NamingContext::CannotProceed ());

    CosNaming::NamingContext_var nc = 
      CosNaming::NamingContext::_narrow (binding.obj);
    assert (!CORBA::is_nil (nc));

    CosNaming::Name rest;
    rest.length (n.length () - 1);

    for (CORBA::ULong k = 0; k < rest.length (); k++)
      rest[k] = n[k + 1];

    switch (btype) {
    case CosNaming::nobject:
      if (rebind)
	nc->rebind (rest, obj);
      else
	nc->bind (rest, obj);
      break;

    case CosNaming::ncontext:
      CosNaming::NamingContext_var nc2 =
	CosNaming::NamingContext::_narrow (obj);

      if (rebind)
	nc->rebind_context (rest, nc2);
      else
	nc->bind_context (rest, nc2);
      break;
    }
  }
}

void NamingContext_impl::bind (const CosNaming::Name& n, 
			       CORBA::Object_ptr obj)
{
  _do_bind (n, obj, CosNaming::nobject, FALSE);
}

void NamingContext_impl::rebind (const CosNaming::Name& n, 
				 CORBA::Object_ptr obj)
{
  _do_bind (n, obj, CosNaming::nobject, TRUE);
}

void NamingContext_impl::bind_context (const CosNaming::Name& n, 
				       CosNaming::NamingContext_ptr nc)
{
  _do_bind (n, nc, CosNaming::ncontext, FALSE);
}

void NamingContext_impl::rebind_context (const CosNaming::Name& n, 
					 CosNaming::NamingContext_ptr nc)
{
  _do_bind (n, nc, CosNaming::ncontext, TRUE);
}

CORBA::Object_ptr NamingContext_impl::resolve (const CosNaming::Name& n)
{
  if (n.length () == 0)
    mico_throw (CosNaming::NamingContext::InvalidName ());

  BindingTable::iterator i = table.find (n[0]);
  if (i == table.end ()) {
    CosNaming::NamingContext::NotFound exc;
    exc.why = CosNaming::NamingContext::missing_node;
    exc.rest_of_name = n;
    mico_throw (exc);
  }

  NmCtxBinding binding = (*i).second;

  if (n.length () == 1) {
    /*
    cout << "resolved objref = " 
	 << _orbnc()->object_to_string (binding.obj) << endl;
    */
    return CORBA::Object::_duplicate (binding.obj);
  }
  else {
    if (binding.btype != CosNaming::ncontext)
      mico_throw (CosNaming::NamingContext::CannotProceed ());

    CosNaming::Name rest;
    rest.length (n.length () - 1);
    for (CORBA::ULong k = 0; k < rest.length (); k++)
      rest[k] = n[k + 1];

    CosNaming::NamingContext_var nc = 
      CosNaming::NamingContext::_narrow (binding.obj);
    assert (!CORBA::is_nil (nc));
    return nc->resolve (rest);
  }
}

void NamingContext_impl::unbind (const CosNaming::Name& n)
{
  if (n.length () == 0)
    mico_throw (CosNaming::NamingContext::InvalidName ());

  BindingTable::iterator i = table.find (n[0]);
  if (i == table.end ()) {
    CosNaming::NamingContext::NotFound exc;
    exc.why = CosNaming::NamingContext::missing_node;
    exc.rest_of_name = n;
    mico_throw (exc);
  }

  NmCtxBinding binding = (*i).second;

  if (n.length () == 1) {
    table.erase (i);
  }
  else {
    if (binding.btype != CosNaming::ncontext) 
      mico_throw (CosNaming::NamingContext::CannotProceed ());

    CosNaming::Name rest;
    rest.length (n.length () - 1);
    for (CORBA::ULong k = 0; k < rest.length (); k++)
      rest[k] = n[k + 1];

    CosNaming::NamingContext_var nc = 
      CosNaming::NamingContext::_narrow (binding.obj);
    assert (!CORBA::is_nil (nc));
    nc->unbind (rest);
  }
}

CosNaming::NamingContext_ptr 
NamingContext_impl::new_context ()
{
  NamingContext_impl * nci = new NamingContext_impl;
  PortableServer::ObjectId_var oid = usepoa->activate_object (nci);
  CORBA::Object_var obj = usepoa->id_to_reference (oid.in());
  CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow (obj);
  svmap[nci] = nci;
  return nc;
}

CosNaming::NamingContext_ptr 
NamingContext_impl::bind_new_context (const CosNaming::Name& n)
{
  NamingContext_impl * nci = new NamingContext_impl;
  PortableServer::ObjectId_var oid = usepoa->activate_object (nci);
  CORBA::Object_var obj = usepoa->id_to_reference (oid.in());
  CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow (obj);
  svmap[nci] = nci;
  bind_context (n, nc);
  return nc;
}

void NamingContext_impl::destroy ()
{
  if (table.size () > 0)
    mico_throw (CosNaming::NamingContext::NotEmpty ());

  CORBA::Object_var obj = useorb->resolve_initial_references ("POACurrent");
  PortableServer::Current_var pc = PortableServer::Current::_narrow (obj);
  PortableServer::POA_var poa = pc->get_POA ();
  PortableServer::ObjectId_var oid = pc->get_object_id ();
  poa->deactivate_object (oid.in());
}

void NamingContext_impl::list (CORBA::ULong how_many, 
			       CosNaming::BindingList*& bl, 
			       CosNaming::BindingIterator_ptr& bi)
{
  CORBA::ULong num = table.size () < how_many ? table.size () : how_many;
  bl = new CosNaming::BindingList (num);
  bl->length (num);
  bi = CosNaming::BindingIterator::_nil ();
  CORBA::ULong l = 0;
  BindingTable::iterator i = table.begin ();

  for (; l < num; l++, i++) {
    CosNaming::Binding b;
    (*bl)[l].binding_name.length (1);
    (*bl)[l].binding_name[0] = (*i).first;
    (*bl)[l].binding_type = (*i).second.btype;
  }
  if (how_many < table.size ()) {
    CORBA::ULong rn = table.size () - how_many;
    CosNaming::BindingList rest (rn);
    rest.length (rn);
    for (l = 0; l < rn; l++, i++) {
      rest[l].binding_name.length (1);
      rest[l].binding_name[0] = (*i).first;
      rest[l].binding_type = (*i).second.btype;
    }
    BindingIterator_impl * bii = new BindingIterator_impl (useorb, rest);
    bi = bii->_this ();
    bii->_remove_ref ();
  }
}


/*
 * BindingIterator
 */

BindingIterator_impl::BindingIterator_impl (CORBA::ORB_ptr orb,
					    const CosNaming::BindingList& bl) 
  : idx (0), blist (bl), useorb (orb)
{
}

CORBA::Boolean BindingIterator_impl::next_one (CosNaming::Binding*& b)
{
  if (idx < blist.length ()) {
    b = new CosNaming::Binding (blist[idx++]);
    return TRUE;
  }
  else {
    b = new CosNaming::Binding;
    return FALSE;
  }
}

CORBA::Boolean 
BindingIterator_impl::next_n (CORBA::ULong how_many, 
			      CosNaming::BindingList*& bl)
{
  CORBA::ULong rlen = blist.length () - idx;
  if (rlen > 0) {
    CORBA::ULong num = how_many < rlen ? how_many : rlen;
    bl = new CosNaming::BindingList (num);
    bl->length (num);
    for (CORBA::ULong i = 0; i < num; i++, idx++)
      (*bl)[i] = blist[idx];
    return TRUE;
  }
  else {
    bl = new CosNaming::BindingList (0);
    bl->length (0);
    return FALSE;
  }
}

void BindingIterator_impl::destroy ()
{
  CORBA::Object_var obj = useorb->resolve_initial_references ("POACurrent");
  PortableServer::Current_var pc = PortableServer::Current::_narrow (obj);
  PortableServer::POA_var poa = pc->get_POA ();
  PortableServer::ObjectId_var oid = pc->get_object_id ();
  poa->deactivate_object (oid.in());
}

/*
 * NamingContextExt
 */

NamingContextExt_impl::NamingContextExt_impl (CORBA::ORB_ptr orb,
					      PortableServer::POA_ptr poa,
					      const char * in)
  : NamingContext_impl (orb, poa, in)
{
}

string
NamingContextExt_impl::StringifyEscape (const char * str)
{
  string res;
  while (*str) {
    switch (*str) {
    case '/':
    case '.':
    case '\\':
      res += '\\';
    default:
      res += *str;
    }
    str++;
  }
  return res;
}

string
NamingContextExt_impl::StringifyComponent (const CosNaming::NameComponent &nc)
{
  string res = StringifyEscape (nc.id.in());

  if (!*nc.kind.in() && *nc.id.in()) {
    return res;
  }

  res += '.';
  res += StringifyEscape (nc.kind.in());
  return res;
}

char *
NamingContextExt_impl::to_string (const CosNaming::Name & name)
{
  string res;

  for (CORBA::ULong i=0; i<name.length(); i++) {
    if (i) {
      res += '/';
    }
    res += StringifyComponent (name[i]);
  }

  return CORBA::string_dup (res.c_str());
}

CosNaming::Name *
NamingContextExt_impl::to_name (const char * sn)
{
  CosNaming::Name * res = new CosNaming::Name;
  CORBA::ULong components=0, cl=0, dl=0;
  CORBA::Boolean inid=TRUE, escaped=FALSE;
  const char * ptr = sn;
  char * data;

  /*
   * Scan the name. ptr always points to the beginning of a field
   * (id or kind). cl denotes the length of this field, dl counts
   * the number of characters for the field (= cl minus escaping).
   * inid is TRUE when scanning the id and FALSE when scanning the
   * kind
   */

  while (42) {
    /*
     * Ignore escaped character
     */
    if (escaped) {
      if (!ptr[cl]) {
	mico_throw(CosNaming::NamingContext::InvalidName());
      }
      escaped=FALSE;
      cl++; dl++;
      continue;
    }

    /*
     * Handle escape
     */

    if (ptr[cl] == '\\') {
      escaped=TRUE;
      cl++;
      continue;
    }

    /*
     * An unescaped dot after the kind is illegal
     */

    if (ptr[cl] == '.' && !inid) {
      mico_throw (CosNaming::NamingContext::InvalidName());
    }

    /*
     * When a boundary character is reached, assign the field
     */

    if (!ptr[cl] || ptr[cl] == '.' || ptr[cl] == '/') {
      data = CORBA::string_alloc (dl);
      for (CORBA::ULong i=0, j=0; i<cl; i++) {
	if (ptr[i] == '\\') {
	  i++;
	}
	data[j++] = ptr[i];
      }
      data[dl] = 0;

      if (inid) {
	res->length (++components);
	(*res)[components-1].id = data;
      }
      else {
	(*res)[components-1].kind = data;
      }
    }

    /*
     * Reset ptr at the end of a field
     */

    if ((!ptr[cl] || ptr[cl] == '/') && inid) {
      ptr += cl;
      inid = FALSE;
      cl = dl = 0;
      continue;
    }
    else if (!ptr[cl]) {
      break;
    }
    else if (ptr[cl] == '/') {
      ptr += cl + 1;
      inid = TRUE;
      cl = dl = 0;
      continue;
    }
    else if (ptr[cl] == '.') {
      ptr += cl + 1;
      inid = FALSE;
      cl = dl = 0;
      continue;
    }

    /*
     * ptr[cl] is an ordinary character
     */

    cl++;
    dl++;
  }

  return res;
}

char *
NamingContextExt_impl::to_url (const char * addr,
			       const char * sn)
{
  CORBA::String_var uesn = mico_url_encode ((CORBA::Octet *) sn, strlen(sn));
  string res = "iiopname://";
  res += addr;
  res += '/';
  res += uesn.in();
  return CORBA::string_dup (res.c_str());
}

CORBA::Object_ptr
NamingContextExt_impl::resolve_str (const char * sn)
{
  CosNaming::Name_var n = to_name (sn);
  return resolve (n.in());
}
