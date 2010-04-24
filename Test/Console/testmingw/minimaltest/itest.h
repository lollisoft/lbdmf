#define API __stdcall
//#define API __cdecl

enum lbErrCodes {
	ERR_NONE = 0,
	ERR_FAIL = 1,
	ERR_SOWISO = 2
};

class ITest {
public:
	virtual lbErrCodes API getInt(char* _int, bool showmsg) = 0;
	virtual bool API getbool() = 0;
	virtual void API test(char* text, char* p2) = 0;
	virtual void API release() = 0;
};
