
template <typename T>
class UAPTempl
{
public:
	UAPTempl()
	{
	}

	virtual ~UAPTempl() {
	}
};

class lb_I_String
{

};

class lb_I_MetaApplication
{

};

#define UAPDECL(classname) \
typedef UAPTempl<classname> UAP##classname;

UAPDECL(lb_I_String)
UAPDECL(lb_I_MetaApplication)

#define UAP(mm, classname, variable) \
	UAP##classname variable;
