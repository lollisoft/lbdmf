#ifndef __LB_INTERFACES_SUB_CLASSES__
#define __LB_INTERFACES_SUB_CLASSES__

/*...sclass lb_I_KeyBase:0:*/
class lb_I_KeyBase {
public:

    virtual int LB_STDCALL operator == (const lb_I_KeyBase &_key) const {
    	return this->equals(_key);
    }
    
    virtual int LB_STDCALL operator > (const lb_I_KeyBase &_key) const {
    	return this->greater(_key);
    }

    virtual int LB_STDCALL equals(const lb_I_KeyBase &_key) const = 0;
    virtual int LB_STDCALL greater(const lb_I_KeyBase &_key) const = 0;
    virtual lb_I_KeyBase* LB_STDCALL clone() const = 0;

    virtual char* LB_STDCALL charrep() = 0;
};
/*...e*/
/*...sclass lb_I_Object:0:*/
/*...sdefinition of object types may cange:0:*/
    enum ObjectTyp { LB_OBJECT, 
                     LB_STRING,
                     LB_STRINGLIST,
                     LB_GUIOBJECT, 
                     LB_WXGUIOBJECT, 
                     LB_DATA_TRANSFER_OBJECT,
                     LB_CONNECTION,
                     LB_APPBUSCLIENT,
                     LB_APPCLIENT_DISPATCH_FN,
                     LB_APPSERVER_DISPATCH_PROTO,
                     LB_EVENT,
                     LB_DOM_NODE,
                     LB_DOM_ATTRIBUTE
    };
/*...e*/

/*...sclass lb_I_Object:0:*/
class lb_I_Object {
protected:
    lb_I_Object() {}
    lb_I_Object(const lb_I_Object &o) {
		setName(o.getName());
	}
    
    virtual ~lb_I_Object() {}

public:

    virtual ObjectTyp LB_STDCALL getType() const = 0;

    virtual void LB_STDCALL setName(const char* d) = 0;
    virtual const char* LB_STDCALL getName() const = 0;

    virtual void LB_STDCALL setType() = 0;
    virtual lb_I_Unknown* LB_STDCALL clone() const = 0;
};
/*...e*/

/*...sDECLARE_LB_OBJECT\40\classname\41\:0:*/
#define DECLARE_LB_OBJECT(classname) \
    virtual ObjectTyp LB_STDCALL getType() const; \
\
    virtual void LB_STDCALL setName(const char* d); \
    virtual const char* LB_STDCALL getName() const; \
\
    virtual void LB_STDCALL setType(); \
    virtual lb_I_Unknown* LB_STDCALL clone() const; \
protected: \
    char* name; \
    ObjectTyp OTyp;
/*...e*/
/*...sIMPLEMENT_LB_OBJECT\40\classname\44\ classtype\41\:0:*/
#define IMPLEMENT_LB_OBJECT(classname, classtype)    \
void LB_STDCALL classname::setName(const char* d) { \
	if (name != NULL) delete name;    \
    name = strdup(d);                     \
}                                         \
\
const char* LB_STDCALL classname::getName() const { \
    return name;                          \
}                                         \
\
ObjectTyp LB_STDCALL classname::getType() const {   \
	if (OTyp == LB_OBJECT) {          \
		LOG("Derived object has not been initialized correctly!"); \
	}                                 \
	return OTyp;                      \
}                                         \
void LB_STDCALL classname::setType() {              \
	OTyp = classtype;                 \
}                                         \

/*...e*/
/*...e*/
/*...sclass lb_I_String:0:*/
class lb_I_String {
protected:
	lb_I_String() {}
	virtual ~lb_I_String() {}

public:
	
	virtual void LB_STDCALL setType() = 0;
	virtual lb_I_Object* LB_STDCALL clone() const = 0;

	virtual void LB_STDCALL setData(char* p) = 0;
	virtual char* LB_STDCALL getData() const = 0;
	
};
/*...e*/

/*...sclass lb_I_Element:0:*/
class lb_I_Element : public lb_I_Unknown {
protected:
	lb_I_Element() {}
	virtual ~lb_I_Element() {}

public:

	virtual lb_I_Element* LB_STDCALL getNext() const = 0;
	virtual void LB_STDCALL setNext(lb_I_Element *e) = 0;
	virtual lb_I_Object* LB_STDCALL getObject() const = 0;
	virtual int LB_STDCALL equals(const lb_I_Element &a) const = 0;
	virtual int LB_STDCALL equals(const lb_I_KeyBase &key) const = 0;

	virtual lb_I_KeyBase* LB_STDCALL getKey() const = 0;

	int LB_STDCALL operator == (const lb_I_Element &a) const {
    		return (this->equals(a) == 1);
	}

	int LB_STDCALL operator == (const lb_I_KeyBase &key) const {
		return (this->equals(key) == 1);
	}
};
/*...e*/
/*...sclass lb_I_Container:0:*/
class lb_I_Container {

protected:
//    lb_I_Container(const lb_I_Container & c);
//    lb_I_Container& operator= (const lb_I_Container & c);

    lb_I_Container() {}
    virtual ~lb_I_Container() {}

public:


    virtual int LB_STDCALL Count() = 0;

    virtual lbErrCodes LB_STDCALL insert(const lb_I_Object &e, const lb_I_KeyBase &key) = 0;
    virtual lbErrCodes LB_STDCALL remove(const lb_I_KeyBase &key) = 0;
    virtual int LB_STDCALL exists(const lb_I_KeyBase& e) = 0;
    virtual int LB_STDCALL hasMoreElements() = 0;
    virtual lb_I_Object* LB_STDCALL nextObject() = 0;
//    virtual lb_I_Element* LB_STDCALL nextElement() = 0;

	/**
	 * Direct access over key
	 */
    virtual lb_I_Object* LB_STDCALL getElement(const lb_I_KeyBase &key) = 0;
    virtual void LB_STDCALL setElement(lb_I_KeyBase &key, const lb_I_Object &e) = 0;

// Is this needed externally ?
    virtual lb_I_Container* LB_STDCALL clone() = 0;

    virtual void LB_STDCALL deleteAll() = 0;
};

/*...sDECLARE_LB_I_CONTAINER_IMPL:0:*/
#define DECLARE_LB_I_CONTAINER_IMPL \
	virtual lb_I_Object* LB_STDCALL nextObject(); \
	virtual int LB_STDCALL hasMoreElements(); \
	virtual int LB_STDCALL exists(const lb_I_KeyBase& e); \
	virtual int LB_STDCALL Count(); \
	virtual lbErrCodes LB_STDCALL insert(const lb_I_Object &e, const lb_I_KeyBase &key); \
	virtual lbErrCodes LB_STDCALL remove(const lb_I_KeyBase &key); \
	virtual lb_I_Object* LB_STDCALL getElement(const lb_I_KeyBase &key); \
	virtual void LB_STDCALL setElement(lb_I_KeyBase &key, const lb_I_Object &e); \
	virtual lb_I_Container* LB_STDCALL clone(); \
	virtual void LB_STDCALL deleteAll(); \
protected: \
    int count; \
    int iteration; \
    lb_I_Element* iterator; \
\
    int ref;
/*...e*/
/*...sIMPLEMENT_LB_I_CONTAINER_IMPL base:0:*/
#define IMPLEMENT_LB_I_CONTAINER_IMPL(classname, co_Interface, co_Key) \
classname::classname() { \
    iteration = 0; \
    ref = 0; \
    iterator = NULL; \
    count = 0; \
} \
\
classname::~classname() { \
} \
int classname::Count() { \
	return count; \
} \
lbErrCodes classname::insert(const co_Interface &e, const co_Key &key) { \
	lbErrCodes err = ERR_NONE; \
\
	if ((err = _insert(e, key)) != ERR_NONE) { \
		LOG("lbContainer::insert(...) Failed!"); \
		return err; \
	} \
\
	count++; \
	return err; \
} \
\
lbErrCodes classname::remove(const co_Key &key) { \
	lbErrCodes err = ERR_NONE; \
\
	if ((err = _remove(key)) != ERR_NONE) { \
		LOG("lbContainer::remove(...) Failed!"); \
		return err; \
	} \
\
	count--; \
	return err; \
} \
\
int classname::hasMoreElements() { \
    if (iteration == 0) { \
		iteration = 1; \
        iterator = data; \
    } \
\
    if (iterator == NULL) { \
        iteration = 0; \
        return 0; \
    } \
\
    return 1; \
} \
\
lbElement* classname::nextElement() { \
    lb_I_Element *temp = iterator; \
    iterator = iterator->getNext(); \
\
    return temp; \
} \
\
lb_I_Object* classname::nextObject() { \
    lb_I_Element *temp = iterator; \
    iterator = iterator->getNext(); \
\
    if (temp == NULL) cout << "Temporary iterator object is NULL!" << endl; \
\
    lb_I_Object *o = temp->getObject(); \
\
    if (o == NULL) cout << "Temporary object o is NULL!" << endl; \
\
    return temp->getObject(); \
} \
\
lb_I_Object* classname::getElement(const co_Key &key) { \
    lb_I_Element* temp = data; \
    while (temp) { \
        if ((temp) && (*(temp->getKey()) == key)) { \
          lb_I_Object *o = temp->getObject(); \
          return o; \
        } \
\
        temp = temp->getNext(); \
    } \
    return NULL; \
} \
\
void classname::setElement(co_Key &key, co_Interface const &e) { \
    remove(key); \
    insert(e, key); \
} \
\
lb_I_Object* classname::getObject() { \
    return data->getObject(); \
} \

/*...e*/

/*...e*/

/*...sclass lb_I_Module:0:*/
class lb_I_Module : 
		public lb_I_Unknown,
		public lb_I_Requestable 
{
protected:
	lb_I_Module() {}
	virtual ~lb_I_Module() {}
public:

	/**
	 * This function loads a module and stores the modulehandle in an array
	 * or a list. If the object is destroyed, the loaded modules are
	 * automatically unloaded (the array/list).
	 */
	virtual lbErrCodes load(char* name) = 0;

	
	/**
	 *
	 */
	
	//virtual lbErrCodes getObjectInstance(char* name, lb_I_Requestable*& inst) = 0; 
	virtual lbErrCodes getObjectInstance(const char* name, lb_I_Container*& inst) = 0;
};
/*...e*/

/*...sclass lb_I_Log:0:*/
class lb_I_Log : public lb_I_Unknown {

/*...sprotected:0:*/
protected:

    lb_I_Log() {}
    virtual ~lb_I_Log() {}

/*...e*/

public:
    virtual void log(const char *msg, long line, char* file) = 0;
    virtual void logdirect(const char *msg, char *f, int level) = 0;
    virtual void log(int log) = 0;
    virtual void enable(char *where) = 0;
    virtual void disable(char *where) = 0;
    virtual void event_begin(char *event) = 0;
    virtual void event_end(char *event) = 0;
    virtual void setPrefix(char* p) = 0;
};
/*...e*/

#endif // __LB_INTERFACES_SUB_CLASSES__

