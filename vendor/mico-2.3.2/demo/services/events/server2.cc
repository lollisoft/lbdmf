#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include <mico/CosNaming.h>
#include <mico/CosEventComm.h>
#include <mico/CosEventChannelAdmin.h>

class Consumer_impl : virtual public CosEventComm::PushConsumer_skel {
public:
  Consumer_impl () {}

  void push (const CORBA::Any& data);
  void disconnect_push_consumer ();
};

void Consumer_impl::push (const CORBA::Any& data) {
  cout << "EventConsumer2: push () called !" << endl;
}

void Consumer_impl::disconnect_push_consumer () {
  cout << "EventConsumer2: disconnected !" << endl;
}

int main (int argc, char** argv)
{
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

  Consumer_impl* consumer = new Consumer_impl ();

  CORBA::Object_var nsobj =
    orb->resolve_initial_references ("NameService");
  assert (! CORBA::is_nil (nsobj));
  
  CosNaming::NamingContext_var nc = 
    CosNaming::NamingContext::_narrow (nsobj);
  assert (! CORBA::is_nil (nc));

  CosNaming::Name name;
  name.length (1);
  name[0].id = CORBA::string_dup ("MyEventChannel");
  name[0].kind = CORBA::string_dup ("");

  cerr << "(2) looking for EventChannel" << endl;
  CORBA::Object_var obj;

#ifdef HAVE_EXCEPTIONS
  try {
    obj = nc->resolve (name);
  }
  catch (...) {
    cerr << "Cannot find EventChannel !" << endl;
    return -1;
  }
#else
  obj = nc->resolve (name);
#endif
  
  CosEventChannelAdmin::EventChannel_var event_channel;
  CosEventChannelAdmin::ConsumerAdmin_var consumer_admin;
  CosEventChannelAdmin::ProxyPushSupplier_var proxy_supplier;

  cerr << "EventChannel found !" << endl;

  event_channel = CosEventChannelAdmin::EventChannel::_narrow (obj);
  assert (! CORBA::is_nil (event_channel));
  consumer_admin = event_channel->for_consumers ();
  assert (! CORBA::is_nil (consumer_admin));

  proxy_supplier = consumer_admin->obtain_push_supplier ();
  assert (! CORBA::is_nil (proxy_supplier));
  cerr << "(2) ProxyPushSupplier obtained !" << endl;

  proxy_supplier->connect_push_consumer (CosEventComm::PushConsumer::_duplicate (consumer));
  
  boa->impl_is_ready (CORBA::ImplementationDef::_nil ());
  orb->run ();
  return 0;
}
