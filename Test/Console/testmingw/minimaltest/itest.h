#define API __stdcall
//#define API __cdecl

enum lbErrCodes {
	ERR_NONE = 0,
	ERR_FAIL,
	ERR_SOWISO
};


class ITest {
public:
	virtual void API release() = 0;

	virtual lbErrCodes API getInt(char* _int) = 0;

	virtual bool API getbool() = 0;
	virtual void API test(char* text, char* p2) = 0;
};
