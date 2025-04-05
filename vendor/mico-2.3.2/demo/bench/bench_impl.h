#include "bench.h"
#ifdef _WINDOWS
#include <iostream>
#else
#include <iostream.h>
#endif

class Bench_impl : virtual public Bench_skel {
    Bench_var _bench;
    CORBA::Long _level;
public:
    void f ()
    {
    }
    void sync ()
    {
    }
    void g ()
    {
	if (--_level > 0)
	    _bench->g();
    }
    void connect (Bench_ptr b, CORBA::Long l)
    {
	_bench = Bench::_duplicate (b);
	_level = l;
    }
};

#ifdef USE_POA
class Bench_impl3 : virtual public POA_Bench {
public:
    Bench_var _bench;
    CORBA::Long _level;
public:
    void f ()
    {
    }
    void sync ()
    {
    }
    void g ()
    {
	if (--_level > 0)
	    _bench->g();
    }
    void connect (Bench_ptr b, CORBA::Long l)
    {
	_bench = Bench::_duplicate (b);
	_level = l;
    }
};
#endif

