// -*- c++ -*-
/*
 *  Implementation of COSS Event Service for MICO
 *  Copyright (C) 1997 Kai-Uwe Sattler, Kay Roemer
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
 *                 kus@iti.cs-uni-magdeburg.de
 */

#ifndef CosEvent_impl_h_
#define CosEvent_impl_h_

#include "CosEventComm.h"
#include "CosEventChannelAdmin.h"

class EventChannel_impl;

// PUSH

class ProxyPushConsumer_impl :
  virtual public CosEventComm::PushConsumer_skel,
  virtual public CosEventChannelAdmin::ProxyPushConsumer_skel {
public:
    ProxyPushConsumer_impl (EventChannel_impl* impl);

    void connect_push_supplier (CosEventComm::PushSupplier_ptr push_supplier);
    void push (const CORBA::Any& data);
    void disconnect_push_consumer ();

private:
    EventChannel_impl* channel;
    CosEventComm::PushSupplier_var supplier;
    CORBA::Boolean connected;
};


class ProxyPushSupplier_impl :
  virtual public CosEventComm::PushSupplier_skel,
  virtual public CosEventChannelAdmin::ProxyPushSupplier_skel,
  public CORBA::RequestCallback {
public:
    ProxyPushSupplier_impl (EventChannel_impl* impl);

    void connect_push_consumer (CosEventComm::PushConsumer_ptr push_consumer);
    void disconnect_push_supplier ();

    void notify (const CORBA::Any &any);

private:

    void callback (CORBA::Request_ptr req, CORBA::RequestCallback::Event);
    EventChannel_impl* channel;
    CosEventComm::PushConsumer_var consumer;
    list<CORBA::Request_var> requests;
};


// PULL

class PullSupplier_skel2 : virtual public CosEventComm::PullSupplier_skel {
public:
    PullSupplier_skel2 (const CORBA::BOA::ReferenceData & =
                        CORBA::BOA::ReferenceData());
    PullSupplier_skel2 (CORBA::Object_ptr _obj);
    virtual ~PullSupplier_skel2();

    virtual bool dispatch (CORBA::StaticServerRequest_ptr _req,
                           CORBA::Environment &_env);

    virtual void pull (CORBA::StaticServerRequest_ptr req) = 0;
};

class ProxyPullSupplier_impl :
  virtual public PullSupplier_skel2,
  virtual public CosEventChannelAdmin::ProxyPullSupplier_skel {
public:
    ProxyPullSupplier_impl (EventChannel_impl *impl);

    void connect_pull_consumer (CosEventComm::PullConsumer_ptr pull_consumer);
    void disconnect_pull_supplier ();

    void pull (CORBA::StaticServerRequest_ptr req);
      
    CORBA::Any* pull ();
    CORBA::Any* try_pull (CORBA::Boolean &has_event);

    void notify (const CORBA::Any &any);
private:
    EventChannel_impl* channel;
    CosEventComm::PullConsumer_var consumer;
    CORBA::Boolean connected;

    list<CORBA::StaticServerRequest_var> requests;
    list<CORBA::Any> events;
};

class ProxyPullConsumer_impl :
  virtual public CosEventComm::PullConsumer_skel,
  virtual public CosEventChannelAdmin::ProxyPullConsumer_skel,
  public CORBA::RequestCallback {
public:
    ProxyPullConsumer_impl (EventChannel_impl *impl);

    void connect_pull_supplier (CosEventComm::PullSupplier_ptr pull_supplier);
    void disconnect_pull_consumer ();

    void listen ();
private:
    void callback (CORBA::Request_ptr, CORBA::RequestCallback::Event);

    EventChannel_impl* channel;
    CosEventComm::PullSupplier_var supplier;

    CORBA::Request_var request;
};

// ADMIN

class ConsumerAdmin_impl : public CosEventChannelAdmin::ConsumerAdmin_skel {
public: 
    ConsumerAdmin_impl (EventChannel_impl *channel);

    CosEventChannelAdmin::ProxyPushSupplier_ptr obtain_push_supplier ();
    CosEventChannelAdmin::ProxyPullSupplier_ptr obtain_pull_supplier ();

private:
    EventChannel_impl* event_channel;
};

class SupplierAdmin_impl : public CosEventChannelAdmin::SupplierAdmin_skel {
public: 
    SupplierAdmin_impl (EventChannel_impl *channel);

    CosEventChannelAdmin::ProxyPushConsumer_ptr obtain_push_consumer ();
    CosEventChannelAdmin::ProxyPullConsumer_ptr obtain_pull_consumer ();

private:
    EventChannel_impl* event_channel;
};

// EVENT CHANNEL

class EventChannel_impl : public CosEventChannelAdmin::EventChannel_skel {
    CORBA::ULong _listeners;
protected:
    EventChannel_impl (const CORBA::BOA::ReferenceData&);

public:
    EventChannel_impl (CORBA::Object_ptr obj);
    EventChannel_impl ();

    CORBA::Boolean _save_object ();

    CosEventChannelAdmin::ConsumerAdmin_ptr for_consumers ();
    CosEventChannelAdmin::SupplierAdmin_ptr for_suppliers ();
    void destroy ();

    void _reg_push_consumer (CosEventChannelAdmin::ProxyPushConsumer_ptr);
    void _reg_push_supplier (CosEventChannelAdmin::ProxyPushSupplier_ptr);
    void _reg_pull_consumer (CosEventChannelAdmin::ProxyPullConsumer_ptr);
    void _reg_pull_supplier (CosEventChannelAdmin::ProxyPullSupplier_ptr);
    void _disconnect ();

    void notify (const CORBA::Any &any);
    void listen (CORBA::Boolean on);
    CORBA::Boolean listen ();

private:
    list<CosEventChannelAdmin::ProxyPushSupplier_var> _push_supp;
    list<CosEventChannelAdmin::ProxyPushConsumer_var> _push_cons;
    list<CosEventChannelAdmin::ProxyPullSupplier_var> _pull_supp;
    list<CosEventChannelAdmin::ProxyPullConsumer_var> _pull_cons;

    CosEventChannelAdmin::SupplierAdmin_var supplier_admin;
    CosEventChannelAdmin::ConsumerAdmin_var consumer_admin;
};

// FACTORY

class EventChannelFactory_impl : 
  public SimpleEventChannelAdmin::EventChannelFactory_skel {
protected:
    EventChannelFactory_impl (const CORBA::BOA::ReferenceData&);

public:
    EventChannelFactory_impl (CORBA::Object_ptr obj);
    EventChannelFactory_impl ();

    CosEventChannelAdmin::EventChannel_ptr create_eventchannel ();

    static void _shutdown ();
};


class EventChannelLoader : public CORBA::BOAObjectRestorer {
public:
  CORBA::Boolean restore (CORBA::Object_ptr);
};

#endif
