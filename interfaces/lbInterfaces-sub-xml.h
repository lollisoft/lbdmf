#ifndef __LB_CONFIGOBJECT__
#define __LB_CONFIGOBJECT__
/*...sclass lb_I_Attribute:0:*/
class lb_I_Attribute {
protected:
	lb_I_Attribute() {}
	virtual ~lb_I_Attribute() {}
	
public:
	virtual lbErrCodes getName(char*& name) = 0;
	virtual lbErrCodes getValue(char*& value) = 0;
	virtual lbErrCodes getType(char*& type) = 0;
};
/*...e*/
/*...sclass lb_I_ConfigObject:0:*/
class lb_I_ConfigObject : public lb_I_Unknown {
protected:
	lb_I_ConfigObject() {}
	~lb_I_ConfigObject() {}
public:
	virtual lbErrCodes LB_STDCALL findObject(const char* name, lb_I_ConfigObject*& object) = 0;
	virtual lbErrCodes LB_STDCALL getAttribute(const char* name, lb_I_Attribute*& attr) = 0;

};
/*...e*/
/*...sclass lb_I_XMLConfig:0:*/
class lb_I_XMLConfig : public lb_I_Unknown
{
protected:
	lb_I_XMLConfig() {}
	~lb_I_XMLConfig() {}
public:
	
	virtual lbErrCodes LB_STDCALL parse() = 0;
	
	/**
	 * Generic access to an xml config file. This should allow to ask
	 * for any parameter in the config file.
	 */
	 
	virtual lbErrCodes LB_STDCALL hasConfigObject(const char* cfgObjectName) = 0;
	
	/**
	 * This returns an instancepointer to the config object. The pointer
	 * must not be deleted by client. Client must call release for that.
	 */
	virtual lbErrCodes LB_STDCALL getConfigObject(lb_I_ConfigObject*& cfgObj, const char* const cfgObjectName) = 0;
};
/*...e*/

#endif // __LB_CONFIGOBJECT__
