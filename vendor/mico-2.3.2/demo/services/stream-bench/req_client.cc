// client.cc
// test der streams 
#include <iostream.h>
#include <fstream.h>
#include <CORBA-SMALL.h>
#include "req.h"

int main(int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");


    // get passive peer
    char ref[1000];
    ifstream in("obj.ref");
    in >> ref;
    in.close();

    CORBA::Object_var obj = orb->string_to_object(ref);
    assert (!CORBA::is_nil (obj));
    bench_var server = bench::_narrow( obj );


    transtype_var chunk = new transtype;

    int i;

      for (i=1; i<5000; i++){ 
	chunk->length(i);
	server->receive(chunk);
      }
	 
    return(0);
}
