// -*- c++ -*-
/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1998 Kay Roemer & Arno Puder
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

#ifndef __POLICY_IMPL_H__
#define __POLICY_IMPL_H__

class Policy_impl : virtual public CORBA::Policy {
    CORBA::PolicyType pt;
protected:
    Policy_impl (CORBA::PolicyType);
public:
    virtual ~Policy_impl ();
    CORBA::PolicyType policy_type ();
    void destroy ();
};

class DomainManager_impl : virtual public CORBA::DomainManager {
    // inherits _policies from CORBA::Object
    // inherits _managers from CORBA::Object
public:
    DomainManager_impl ();
    virtual ~DomainManager_impl ();

    CORBA::Policy_ptr get_domain_policy (CORBA::PolicyType policy_type);
    void set_domain_policy (CORBA::Policy_ptr policy);
    CORBA::DomainManager_ptr copy ();
};

class ConstructionPolicy_impl : virtual public Policy_impl,
				virtual public CORBA::ConstructionPolicy {
    typedef map<string, CORBA::Boolean, less<string> > IdConstrMap;
    IdConstrMap _constr;
public:
    ConstructionPolicy_impl ();
    virtual ~ConstructionPolicy_impl ();

    void make_domain_manager (CORBA::InterfaceDef_ptr object_type,
			      CORBA::Boolean constr_policy);

    CORBA::Boolean constr_policy (CORBA::Object_ptr object);

    CORBA::Policy_ptr copy ();
};

class TransportPrefPolicy_impl :
    virtual public Policy_impl,
    virtual public MICOPolicy::TransportPrefPolicy
{
    ProfileTagSeq _prefs;
public:
    TransportPrefPolicy_impl (const ProfileTagSeq &prefs);
    TransportPrefPolicy_impl ();
    virtual ~TransportPrefPolicy_impl ();

    ProfileTagSeq *preferences();
    void preferences (const ProfileTagSeq &prefs);
    ProfileTagSeq *preferences_nocopy();

    CORBA::Policy_ptr copy ();
};

class BidirectionalPolicy_impl :
    virtual public Policy_impl,
    virtual public BiDirPolicy::BidirectionalPolicy
{
    BiDirPolicy::BidirectionalPolicyValue _value;
public:
    BidirectionalPolicy_impl (BiDirPolicy::BidirectionalPolicyValue);
    BidirectionalPolicy_impl ();
    virtual ~BidirectionalPolicy_impl ();

    BiDirPolicy::BidirectionalPolicyValue value();

    CORBA::Policy_ptr copy ();
};

#endif
