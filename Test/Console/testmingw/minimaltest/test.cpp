#include "testdll.h"

#include <stdio.h>

int main() {
    test("From text.exe");
    ITest* t = gettest();
    
    t->test("From object out of test.exe", "p2");
    
    if (getbool()) printf("Have true.\n");
    
	if (t->getInt() != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);
	if (t->getInt() == ERR_FAIL) printf("Success: ITest->getInt() returns %d\n", ERR_FAIL);

    t->release();
    
    return 0;
}
