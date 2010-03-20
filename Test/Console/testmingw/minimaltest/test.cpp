#include "testdll.h"

#include <stdio.h>

int main() {
    test("From text.exe");
    ITest* t = gettest();
    
    t->test("From object out of test.exe", "p2");
    
    if (getbool()) printf("Have true.\n");
    
    t->release();
    
    return 0;
}
