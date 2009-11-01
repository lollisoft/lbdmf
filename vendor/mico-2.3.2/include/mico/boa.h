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

#ifndef __mico_boa_h__
#define __mico_boa_h__


/************************* Interfaces ******************************/

class ORBRequest;

class BOA : public ServerlessObject {
public:
    //typedef BoundedSequenceTmpl<Octet, MICO_TID_OCTET, 1024> ReferenceData;
    typedef SequenceTmpl<Octet,MICO_TID_OCTET> ReferenceData;
    typedef TSeqVar<ReferenceData> ReferenceData_var;

    virtual Object_ptr create (const ReferenceData &,
			       InterfaceDef *,
			       ImplementationDef *,
			       ImplementationBase * = NULL,
                               const char *repoid = 0) = 0;
    // begin-mico-extension
    virtual ~BOA ();
    virtual Boolean restoring () = 0;
    virtual Object_ptr restore (Object_ptr orig,
				const ReferenceData &,
				InterfaceDef *,
				ImplementationDef *,
				ImplementationBase *) = 0;
    virtual ORB_ptr orb () = 0;
    virtual const char *impl_name () = 0;
    virtual void save_objects () = 0;
    virtual void dispose_objects () = 0;
    // end-mico-extension

    virtual void dispose (Object_ptr) = 0;
    virtual ReferenceData *get_id (Object_ptr) = 0;
    virtual void change_implementation (Object_ptr,
					ImplementationDef *) = 0;
    virtual Principal_ptr get_principal (Object_ptr, Environment_ptr) = 0;

    virtual void impl_is_ready (ImplementationDef *) = 0;
    virtual void deactivate_impl (ImplementationDef *) = 0;
    virtual void obj_is_ready (Object_ptr, ImplementationDef *) = 0;
    virtual void deactivate_obj (Object_ptr) = 0;

    static BOA_ptr _duplicate (BOA_ptr o)
    {
	if (o)
	    o->_ref();
	return o;
    }
    static BOA_ptr _nil ()
    {
	return 0;
    }
};

typedef ObjVar<BOA> BOA_var;


class BOAObjectRestorer {
    ServerlessObject *_boa_interceptor;
public:
    BOAObjectRestorer ();
    virtual ~BOAObjectRestorer ();

    virtual Boolean restore (Object_ptr);
    virtual Boolean bind (const char *repoid,
                          const SequenceTmpl<Octet,MICO_TID_OCTET> &tag);
};


#endif // __mico_boa_h__
