#define LB_MODULE_DLL

#include "testdll.h"

test::test() {
}

test::~test() {
}

void test::release() {
    delete this;
}


void DLLEXPORT getInstance(lb_I_test*& inst) {
        inst = new test;
}

