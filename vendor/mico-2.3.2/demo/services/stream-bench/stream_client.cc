// client.cc
// test der streams 
#include <iostream.h>
#include <fstream.h>
#include <CORBA-SMALL.h>
#include <mico/stream_impl.h>
#include <mico/template_impl.h>



int main(int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    // instantiate active cep

    ActiveCEP_impl stream;

    // get passive peer
    char ref[1000];
    ifstream in("obj.ref");
    in >> ref;
    in.close();

    CORBA::Object_var obj = orb->string_to_object(ref);
    assert (!CORBA::is_nil (obj));
    MICOStream::PassiveCEP_var server = MICOStream::PassiveCEP::_narrow( obj );

    stream.connect(server->bind_addr());

    MICOStream::StreamData_var chunk = new MICOStream::StreamData;

    int i;

      for (i=1; i<5000; i++){ 
	chunk->length(i);
	stream.write(chunk);
      }
	 
    return(0);
}
