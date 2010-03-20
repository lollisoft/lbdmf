#define DLL
#include "testdll.h"
#include <stdio.h>

void test_impl(char* text) {
    printf("Hello from test DLL. Text is '%s'.\n", text);
}

ITest::~ITest() {
}

/*...sclass Test:0:*/
class Test : public ITest {
public:
	Test();
	virtual ~Test();
        
        bool API getbool();
        void API test(char* text, char* p2);
        
        virtual void API release();
};

Test::Test() {
	printf("Instance of Test created.\n");
}

Test::~Test() {
	printf("Instance of Test deleted.\n");
}

bool API Test::getbool() {

}

void API Test::test(char* text, char* p2) {
	test_impl(text);
	test_impl(p2);
}

void API Test::release() {
	printf("Test::release() called.\n");
	delete this;
}
/*...e*/

extern "C" void DLLEXPORT API _test(char* text) {
	test_impl(text);
}

extern "C" bool DLLEXPORT API _getbool() {
    return true;
}

extern "C" DLLEXPORT ITest* API _gettest() {
    return new Test();
}

extern "C" void DLLEXPORT API test(char* text) {
	test_impl(text);
}

extern "C" bool DLLEXPORT API getbool() {
    return _getbool();
}

extern "C" DLLEXPORT ITest* API gettest() {
    return _gettest();
}

