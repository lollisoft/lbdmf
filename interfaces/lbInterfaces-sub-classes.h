#ifndef __LB_INTERFACES_SUB_CLASSES__
#define __LB_INTERFACES_SUB_CLASSES__

/*...sclass lb_I_KeyBase:0:*/
class lb_I_KeyBase {
public:

    virtual int LB_STDCALL operator == (const lb_I_KeyBase* _key) const {
        if (strcmp(this->getMainInterface(), _key->getMainInterface()) == 0)
    		return this->equals(_key);
    	else {
    		return -1;
    	}
    }
    
    virtual int LB_STDCALL operator > (const lb_I_KeyBase* _key) const {
        if (strcmp(this->getMainInterface(), _key->getMainInterface()) == 0)
	    	return this->greater(_key);
	else {
		return -1;
	}
    }

    virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const = 0;
    virtual int LB_STDCALL greater(const lb_I_KeyBase* _key) const = 0;
    virtual lb_I_KeyBase* LB_STDCALL clone() const = 0;

    virtual char* LB_STDCALL charrep() = 0;
    
    // Returns the real interface for the object
    virtual char* LB_STDCALL getMainInterface() const = 0;
};
/*...e*/
/*
	Must have a type information of the key, because a string could not be compared
	with an integer (directly). For a key, it is simply one type of interface, that
	will be returned as their type information.
	
	Here, for keys, a key can be compared with another key of the same type. It is
	simple to implement the compare function, having the type of the object.
	
	Where to define the type information function ?
	
	I tent to use a type check in the lb_I_KeyBase interface. So it is not neccesary
	to implement a typecheck for each equals/greater function.
*/
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
class lb_I_String : public lb_I_Unknown {
protected:
	lb_I_String() {}
	virtual ~lb_I_String() {}

public:
	
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
	virtual lb_I_Unknown* LB_STDCALL getObject() const = 0;
	
	/**
	 * Do a full compare. Data and key must be equal.
	 */
	virtual int LB_STDCALL equals(const lb_I_Element* a) const = 0;
	/**
	 * Do a key compare.
	 */
	virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const = 0;

	virtual lb_I_KeyBase* LB_STDCALL getKey() const = 0;

	int LB_STDCALL operator == (const lb_I_Element* a) const {
    		return (this->equals(a) == 1);
	}

	int LB_STDCALL operator == (const lb_I_KeyBase* _key) const {
		return (this->equals(_key) == 1);
	}
};

#define DECLARE_LB_ELEMENT(classname) \
classname(const lb_I_Unknown* o, const lb_I_KeyBase* _key, lb_I_Element *_next = NULL); \
virtual lb_I_Element* LB_STDCALL getNext() const; \
virtual void LB_STDCALL setNext(lb_I_Element *e); \
virtual lb_I_Unknown* LB_STDCALL getObject() const; \
virtual int LB_STDCALL equals(const lb_I_Element* a) const; \
virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const; \
virtual lb_I_KeyBase* LB_STDCALL getKey() const; \
private: \
\
    lb_I_Element* next; \
    lb_I_Unknown* data; \
    lb_I_KeyBase* key; 

#define IMPLEMENT_LB_ELEMENT(classname) \
\
classname::classname(const lb_I_Unknown* o, const lb_I_KeyBase* _key, lb_I_Element *_next) { \
    next = _next; \
    lb_I_Unknown *uk_data = o->clone(); \
    if (uk_data->queryInterface("lb_I_Object", (void**) &data) != ERR_NONE) { \
    	CL_LOG("Error while cloning"); \
    } \
    key = _key->clone(); \
    if (key == NULL) LOG("Key cloning in constructor failed. May be a memory problem"); \
} \
\
classname::~classname() { \
} \
\
lb_I_Unknown* classname::getObject() const { \
    return data; \
} \
\
lb_I_KeyBase* LB_STDCALL classname::getKey() { \
	return key; \
} \
\
void LB_STDCALL classname::setNext(lb_I_Element *e) { \
	next = e; \
} \
\
lbErrCodes LB_STDCALL lbElement::setData(lb_I_Unknown* _data) { \
	data = _data->clone(); \
\
	if (data == NULL) CL_LOG("Container element could not be copied"); \
	return ERR_NONE; \
}

/*...e*/
/*...sclass lb_I_Container:0:*/
class lb_I_Container : public lb_I_Unknown {

protected:
//    lb_I_Container(const lb_I_Container & c);
//    lb_I_Container& operator= (const lb_I_Container & c);

    lb_I_Container() {}
    virtual ~lb_I_Container() {}

public:


    virtual int LB_STDCALL Count() = 0;

    virtual lbErrCodes LB_STDCALL insert(const lb_I_Unknown* e, const lb_I_KeyBase* key) = 0;
    virtual lbErrCodes LB_STDCALL remove(const lb_I_KeyBase* key) = 0;
    virtual int LB_STDCALL exists(const lb_I_KeyBase* e) = 0;
    virtual int LB_STDCALL hasMoreElements() = 0;
    virtual lb_I_Unknown* LB_STDCALL nextElement() = 0;

	/**
	 * Direct access over key
	 */
    virtual lb_I_Unknown* LB_STDCALL getElement(const lb_I_KeyBase* key) = 0;
    virtual void LB_STDCALL setElement(lb_I_KeyBase* key, const lb_I_Unknown* e) = 0;

    virtual void LB_STDCALL deleteAll() = 0;
};

/*...sDECLARE_LB_I_CONTAINER_IMPL_CO \40\co_Interface\41\:0:*/
#define DECLARE_LB_I_CONTAINER_IMPL_CO(co_Interface) \
	virtual lb_I_Unknown* LB_STDCALL nextObject(); \
	virtual int LB_STDCALL hasMoreElements(); \
	virtual int LB_STDCALL exists(const lb_I_KeyBase* e); \
	virtual int LB_STDCALL Count(); \
	\
	virtual lbErrCodes LB_STDCALL insert(const co_Interface* e, const lb_I_KeyBase* key); \
	virtual lbErrCodes LB_STDCALL _insert(const lb_I_Unknown* e, const lb_I_KeyBase* key); \
	virtual lbErrCodes LB_STDCALL insert(const lb_I_Unknown* e, const lb_I_KeyBase* key); \
	\
	virtual lbErrCodes LB_STDCALL remove(const lb_I_KeyBase* key); \
	\
	virtual lb_I_Unknown* LB_STDCALL getElement(const lb_I_KeyBase* key); \
	virtual lb_I_Unknown* LB_STDCALL nextElement(); \
	\
	\
	virtual void LB_STDCALL setElement(lb_I_KeyBase* key, const co_Interface* e); \
	virtual void LB_STDCALL setElement(lb_I_KeyBase* key, const lb_I_Unknown* e); \
	\
	virtual void LB_STDCALL deleteAll(); \
protected: \
    int count; \
    int iteration; \
    lb_I_Element* iterator;
/*...e*/
/*...sDECLARE_LB_I_CONTAINER_IMPL \40\\41\:0:*/
#define DECLARE_LB_I_CONTAINER_IMPL() \
	virtual int LB_STDCALL hasMoreElements(); \
	virtual int LB_STDCALL exists(const lb_I_KeyBase* e); \
	virtual int LB_STDCALL Count(); \
	\
	virtual lbErrCodes LB_STDCALL _insert(const lb_I_Unknown* e, const lb_I_KeyBase* key); \
	virtual lbErrCodes LB_STDCALL insert(const lb_I_Unknown* e, const lb_I_KeyBase* key); \
	\
	virtual lbErrCodes LB_STDCALL remove(const lb_I_KeyBase* key); \
	virtual lbErrCodes LB_STDCALL _remove(const lb_I_KeyBase* key); \
	\
	virtual lb_I_Unknown* LB_STDCALL getElement(const lb_I_KeyBase* key); \
	virtual lb_I_Unknown* LB_STDCALL nextElement(); \
	\
	\
	virtual void LB_STDCALL setElement(lb_I_KeyBase* key, const lb_I_Unknown* e); \
	\
	virtual void LB_STDCALL deleteAll(); \
protected: \
    int count; \
    int iteration; \
    lb_I_Element* iterator; \
    lb_I_Element* container_data;
/*...e*/

/**
 * The second interface name is the requested interface, that must be implemented for an implementation.
 * This macro implements the interface handling. It makes no sense, wrapping an implementation down to an
 * unknown element. All Implementations must implement the unknown interface. Then it is possible to ask
 * for the needed interface that can be stored in this container.
 */

/*...sIMPLEMENT_LB_I_CONTAINER_IMPL_CO base \40\classname\44\ co_Interface\41\:0:*/
#define IMPLEMENT_LB_I_CONTAINER_IMPL_CO(classname, co_Interface) \
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
lbErrCodes classname::insert(const co_Interface* e, const lb_I_KeyBase* key) { \
	lbErrCodes err = ERR_NONE; \
\
	if ((err = insert((lb_I_Unknown*) e, key)) != ERR_NONE) { \
		LOG("lbContainer::insert(...) Failed!"); \
		return err; \
	} \
\
	count++; \
	return err; \
} \
\
lbErrCodes classname::insert(const lb_I_Unknown* e, const lb_I_KeyBase* key) { \
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
lbErrCodes classname::remove(const lb_I_KeyBase* key) { \
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
lb_I_Unknown* classname::nextElement() { \
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
lb_I_Unknown* classname::getElement(const co_Key* key) { \
    lb_I_Element* temp = data; \
    while (temp) { \
        if ((temp) && (*(temp->getKey()) == key)) { \
          lb_I_Unknown *o = temp->getObject(); \
          if (o == NULL) LOG("Temporary object o is NULL!"); \
          return o; \
        } \
\
        temp = temp->getNext(); \
    } \
    return NULL; \
} \
\
void classname::setElement(co_Key* key, co_Interface const* e) { \
    remove(key); \
    insert(e, key); \
} \


/*...e*/
/*...sIMPLEMENT_LB_I_CONTAINER_IMPL base \40\classname\41\ \47\\47\ only base lb_I_Unknown:0:*/
#define IMPLEMENT_LB_I_CONTAINER_IMPL(classname) \
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
\
void LB_STDCALL classname::deleteAll() { \
\
	LOG(#classname"::deleteAll() has not been implemented"); \
\
} \
\
int classname::exists(const lb_I_KeyBase* key) { \
    LOG(#classname"::deleteAll() has not been implemented completly"); \
    if (getElement(key) == NULL) return 0; \
    return 1; \
} \
\
lbErrCodes classname::insert(const lb_I_Unknown* e, const lb_I_KeyBase* key) { \
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
lbErrCodes classname::remove(const lb_I_KeyBase* key) { \
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
lbErrCodes classname::_insert(const lb_I_Unknown* e, const lb_I_KeyBase* key) { \
\
    if (container_data == NULL) { \
        lbElement* _data = new lbElement(e, key); \
\
        _data->queryInterface("lb_I_Element", (void**) &container_data); \
\
	if (container_data->getObject() == NULL) { \
		LOG("Failed to insert first element in classname::insert"); \
		return ERR_CONTAINER_INSERT; \
	} \
    } \
    else { \
        lb_I_Element* temp; \
        for (temp = container_data; temp != NULL; temp = temp->getNext()) { \
            lb_I_Element* next = temp->getNext(); \
\
            if (next != NULL) { \
                if (next->getKey() < key) { \
                    temp->setNext(new lbElement(e, key, next)); \
                    return ERR_NONE; \
                } \
            } \
            else { \
                temp->setNext(new lbElement(e, key)); \
                return ERR_NONE; \
            } \
        } \
    } \
    return ERR_NONE; \
} \
lbErrCodes classname::_remove(const lb_I_KeyBase* key) { \
\
    if (container_data == NULL) { \
    	LOG("Error: Can't remove from empty container!"); \
    	return ERR_CONTAINER_REMOVE; \
    } \
\
    lb_I_Element* pre = container_data; \
    container_data = container_data->getNext(); \
\
    if (pre->getKey() == key) { \
        pre->release(); \
        return ERR_NONE; \
    } \
\
    for (lb_I_Element* temp = container_data; temp != NULL; temp = container_data->getNext()) { \
        if (temp->getKey() == key) { \
            pre->setNext(temp->getNext()); \
            temp->release(); \
            return ERR_NONE; \
        } \
    } \
    LOG("Error: No object with that key"); \
    return ERR_CONTAINER_REMOVE; \
} \
\
int classname::hasMoreElements() { \
    if (iteration == 0) { \
		iteration = 1; \
        iterator = container_data; \
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
lb_I_Unknown* classname::nextElement() { \
    lb_I_Element *temp = iterator; \
    iterator = iterator->getNext(); \
\
    if (temp == NULL) cout << "Temporary iterator object is NULL!" << endl; \
\
    lb_I_Unknown *o = temp->getObject(); \
\
    if (o == NULL) cout << "Temporary object o is NULL!" << endl; \
\
    return temp->getObject(); \
} \
\
lb_I_Unknown* classname::getElement(const lb_I_KeyBase* key) { \
    lb_I_Element* temp = container_data; \
    while (temp) { \
        if ((temp) && (*(temp->getKey()) == key)) { \
          lb_I_Unknown *o = temp->getObject(); \
          return o; \
        } \
\
        temp = temp->getNext(); \
    } \
    return NULL; \
} \
\
void classname::setElement(lb_I_KeyBase* key, lb_I_Unknown const* e) { \
    remove(key); \
    insert(e, key); \
}

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

/*...sclass lb_I_Thread:0:*/
class lb_I_Thread : public lb_I_Unknown {
protected:
	lb_I_Thread() {}
	virtual ~lb_I_Thread() {}

public:	

	virtual lbErrCodes LB_STDCALL create() = 0;

	virtual lbErrCodes LB_STDCALL run() = 0; 
	virtual lbErrCodes LB_STDCALL stop() = 0;
	
	virtual lbErrCodes LB_STDCALL pause() = 0;
	virtual lbErrCodes LB_STDCALL resume() = 0;


private:
        // no copy ctor/assignment operator
        lb_I_Thread(const lb_I_Thread&) {}
        lb_I_Thread& operator=(const lb_I_Thread&) { return *this; }
};
/*...e*/
/*...sclass lb_I_Mutex:0:*/
class lb_I_Mutex {
protected:
	lb_I_Mutex() {}
	virtual ~lb_I_Mutex() {}

public:
        virtual void createMutex(int name) = 0;
        virtual void deleteMutex(int name) = 0;
        virtual void enter() = 0;
        virtual void release() = 0;
	
};
/*...e*/

class lb_I_Lock;
/*...sclass lb_I_CriticalSection:0:*/
class lb_I_CriticalSection {
protected:
	lb_I_CriticalSection() {}
	virtual ~lb_I_CriticalSection() {}

protected:
	virtual lbErrCodes enter() = 0;
	virtual lbErrCodes leave() = 0;
	
	friend class lb_I_Lock;
};
/*...e*/
/*...sclass lb_I_Lock:0:*/
class lb_I_Lock {
protected:
	lb_I_Lock(lb_I_CriticalSection*& _cso, char* _name) {}
	virtual ~lb_I_Lock() {}

	lb_I_Lock() {}
	lb_I_Lock(const lb_I_Lock&) {}
};
/*...e*/


/*...sthread stuff:0:*/
#ifdef bla
/*...sclass lb_I_Mutex:0:*/
/*...e*/

class DLLEXPORT lbCritSect {
public:
	lbCritSect();
	virtual ~lbCritSect();

private:
	//lbCritSect(const lbCritSect&) {}

protected:
	lbErrCodes enter();
	lbErrCodes leave();
	
	void* critsect;	
	
	friend class lbLock;
};

class DLLEXPORT lbLock {
public:
	lbLock(lbCritSect& _cso, char* _name);
	virtual ~lbLock();
private:
	lbLock() {}
	lbLock(const lbLock&) {}

	char* name;
	lbCritSect* cso;
};

#endif // bla
/*...e*/

#endif // __LB_INTERFACES_SUB_CLASSES__

