#include <UAPTempl.h>

// If you remove Foo completely, gdb will tell you that there is no code. If Foo is there, code will be shown.
void Foo()
{

}

void DoTest1()
{
	UAP(NULL, lb_I_String, s)
	UAP(NULL, lb_I_MetaApplication, meta)
}

void DoTest()
{
	UAP(NULL, lb_I_String, s)
	UAP(NULL, lb_I_MetaApplication, meta)
}

// http://www.google.co.in/#hl=de&sclient=psy-ab&q=gcc+extract+dwarf+info&oq=gcc+extract+dwarf+info&gs_l=serp.3...4852.16604.0.16862.24.23.1.0.0.0.213.2453.15j7j1.23.0...0.0...1c.V9vmdrT3ctk&pbx=1&bav=on.2,or.r_gc.r_pw.r_qf.&fp=1391debd1f706dcc&biw=1920&bih=953
// http://eli.thegreenplace.net/2011/02/07/how-debuggers-work-part-3-debugging-information/
int main(int argc, char *argv[]) {

	DoTest();
	DoTest1();
	
	return 0;
}
