#ifndef __LB_INTERFACES_SUB_CLASSES__
#define __LB_INTERFACES_SUB_CLASSES__

/*...sclass lb_I_KeyBase:0:*/
class lb_I_KeyBase {
public:

    virtual int operator == (const lb_I_KeyBase &_key) const {
    	return this->equals(_key);
    }
    
    virtual int operator > (const lb_I_KeyBase &_key) const {
    	return this->greater(_key);
    }

    virtual int equals(const lb_I_KeyBase &_key) const = 0;
    virtual int greater(const lb_I_KeyBase &_key) const = 0;
    virtual lb_I_KeyBase* clone() const = 0;

    virtual char* charrep() = 0;
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
                     LB_EVENT };
/*...e*/

class lb_I_Object {
protected:
    lb_I_Object() {}
    lb_I_Object(const lb_I_Object &o) {
		setName(o.getName());
	}
    
    virtual ~lb_I_Object() {}

public:

    virtual ObjectTyp getType() const = 0;

    virtual void setName(const char* d) = 0;
    virtual const char* getName() const = 0;

    virtual void setType() = 0;
    virtual lb_I_Object* clone() const = 0;
};

/*...e*/

/*...sclass lb_I_Element:0:*/
class lb_I_Element {
protected:
	lb_I_Element() {}
	virtual ~lb_I_Element();

public:

	virtual lb_I_Element* getNext() const = 0;
	virtual void setNext(lb_I_Element *e) = 0;
	virtual lb_I_Object* getObject() const = 0;
	virtual int equals(const lb_I_Element &a) const = 0;
	virtual int equals(const lb_I_KeyBase &key) const = 0;

	virtual lb_I_KeyBase *getKey() const = 0;

	int operator == (const lb_I_Element &a) const {
    		return (this->equals(a) == 1);
	}

	int operator == (const lb_I_KeyBase &key) const {
		return (this->equals(key) == 1);
	}
};
/*...e*/
/*...sclass lb_I_Container:0:*/
class lb_I_Container {

protected:
    lb_I_Container(const lb_I_Container & c);
    lb_I_Container& operator= (const lb_I_Container & c);

    lb_I_Container() {}
    virtual ~lb_I_Container() {}

public:


    virtual int Count() = 0;

    virtual lbErrCodes insert(const lb_I_Object &e, const lb_I_KeyBase &key) = 0;
    virtual lbErrCodes remove(const lb_I_KeyBase &key) = 0;
    virtual int exists(const lb_I_KeyBase& e) = 0;
    virtual int hasMoreElements() = 0;
    virtual lb_I_Object* nextObject() = 0;
//    virtual lb_I_Element* nextElement() = 0;

	/**
	 * Direct access over key
	 */
    virtual lb_I_Object* getElement(const lb_I_KeyBase &key) = 0;
    virtual void setElement(lb_I_KeyBase &key, const lb_I_Object &e) = 0;

// Is this needed externally ?
//    virtual lb_I_Container* clone() = 0;

    virtual void deleteAll() = 0;
};
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
	virtual lbErrCodes getObjectInstance(char* name, lb_I_Container*& inst) = 0;
};
/*...e*/

#endif // __LB_INTERFACES_SUB_CLASSES__

