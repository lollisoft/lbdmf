#define UAPDECL(classname) \
class UAPDECL##classname { \
public:\
	UAPDECL##classname() {} \
\
	virtual ~UAPDECL##classname() { \
	} \
};

UAPDECL(lb_I_String)
UAPDECL(lb_I_MetaApplication)
