/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.20 $
 * $Name:  $
 * $Id: lbInterfaces-sub-classes.h,v 1.20 2002/02/27 21:00:35 lothar Exp $
 *
 * $Log: lbInterfaces-sub-classes.h,v $
 * Revision 1.20  2002/02/27 21:00:35  lothar
 * Unused code
 *
 * Revision 1.19  2002/02/25 06:18:31  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 * Revision 1.18  2001/12/15 18:19:39  lothar
 * ZThread not on windows
 *
 * Revision 1.17  2001/12/12 17:27:54  lothar
 * Hehe - runs under linux
 *
 * Revision 1.16  2001/10/06 11:20:54  lothar
 * Compiles module lbHook under linux now
 *
 * Revision 1.15  2001/10/04 19:29:15  lothar
 * Current version seems to work good (without big memory holes)
 *
 * Revision 1.14  2001/08/18 07:38:55  lothar
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.13  2001/07/18 05:52:57  lothar
 * Seems to work now (lbDOMNode::parent - refcount must be corrected)
 *
 * Revision 1.12  2001/07/11 16:03:13  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.11  2001/06/21 06:41:56  lothar
 * Changed lb_I_String base
 *
 * Revision 1.10  2001/05/08 20:55:12  lothar
 * Change of lb_I_KeyBase interface
 *
 * Revision 1.9  2001/05/01 15:51:49  lothar
 * First instance could be loaded over the new module management
 *
 * Revision 1.8  2001/04/27 18:57:32  lothar
 * Commit for removing some getch()'s
 *
 * Revision 1.7  2001/04/13 07:39:27  lothar
 * Commit for backup
 *
 **************************************************************/
/*...e*/

#ifndef __LB_INTERFACES_SUB_CLASSES__
#define __LB_INTERFACES_SUB_CLASSES__

/*...sclass lb_I_KeyBase:0:*/
class lb_I_KeyBase : public lb_I_Unknown {
protected:
        lb_I_KeyBase() {}
        virtual ~lb_I_KeyBase() {}
public:

    virtual int LB_STDCALL operator == (const lb_I_KeyBase* _key) const {
        return this->equals(_key);
    }
    
    virtual int LB_STDCALL operator > (const lb_I_KeyBase* _key) const {
        return this->greater(_key);
    }

    virtual int LB_STDCALL equals(const lb_I_KeyBase* _key) const = 0;
    virtual int LB_STDCALL greater(const lb_I_KeyBase* _key) const = 0;

    virtual char* LB_STDCALL getKeyType() = 0;

    virtual char* LB_STDCALL charrep() = 0;
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
                //setName(o.getName());
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

// Keyable interfaces
/*...sclass lb_I_String:0:*/
class lb_I_String : public lb_I_KeyBase {
protected:
        lb_I_String() {}
        virtual ~lb_I_String() {}

public:
        
        virtual void LB_STDCALL setData(char* p) = 0;
        virtual char* LB_STDCALL getData() const = 0;
        
};
/*...e*/
/*...sclass lb_I_Integer:0:*/
class lb_I_Integer : public lb_I_KeyBase {
protected:
        lb_I_Integer() {}
        virtual ~lb_I_Integer() {}

public:
        
        virtual void LB_STDCALL setData(int p) = 0;
        virtual int LB_STDCALL getData() const = 0;
        
};
/*...e*/
/*...sclass lb_I_Long:0:*/
class lb_I_Long : public lb_I_KeyBase {
protected:
        lb_I_Long() {}
        virtual ~lb_I_Long() {}

public:
        
        virtual void LB_STDCALL setData(long p) = 0;
        virtual long LB_STDCALL getData() const = 0;
        
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
    lb_I_KeyBase* key; 

#define IMPLEMENT_LB_ELEMENT(classname) \
\
classname::classname(const lb_I_Unknown* o, const lb_I_KeyBase* _key, lb_I_Element *_next) { \
    ref = STARTREF; \
    manager = NULL; \
    if (_next == NULL) next = _next; \
    if (_next != NULL) { \
        _next->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__); \
    } \
    if (o == NULL) CL_LOG("Error! Can't clone a NULL pointer"); \
    data = o->clone(__FILE__, __LINE__); \
    char ptr[20] = ""; \
    sprintf(ptr, "%x", data); \
    if (strcmp(ptr, "d693d0") == 0) CL_LOG("Object d693d0 cloned"); \
    if (data->getRefCount() > 1) { \
        CL_LOG("Refcount after cloning is more than 1 !!!"); \
    } \
    lb_I_Unknown* uk_key = NULL; \
    key = (lb_I_KeyBase*) _key->clone(__FILE__, __LINE__); \
    if (key == NULL) CL_LOG("Key cloning in constructor failed. May be a memory problem"); \
} \
\
classname::~classname() { \
        char buf[1000] = ""; \
        if (key != NULL) { \
                key->setDebug(1); \
                if (key->deleteState() != 1) CL_LOG("Key wouldn't deleted in container element!"); \
                RELEASE(key); \
        } \
        if (data != NULL) { \
                if (data->deleteState() != 1) { \
                /* \
                	if (strcmp(data->getClassName(), "lbDOMNode") == 0) { \
                		lb_I_ConfigObject* cO = NULL; \
                		data->queryInterface("lb_I_ConfigObject", (void**) &cO, __FILE__, __LINE__); \
                		printf("Name von lbDOMNode: %s.\n", cO->getName()); \
                		RELEASE(cO); \
                	} \
                	*/ \
                        sprintf(buf, "Data (at %x) (created at: %s) (refcount=%d) (classname='%s') wouldn't deleted in container element!", data, data->getCreationLoc(), data->getRefCount(), data->getClassName()); \
                        CL_LOG(buf); \
                        getch(); \
                        RELEASE(data); \
                        getch(); \
                } \
        } \
        key = NULL; \
        data = NULL; \
} \
\
lb_I_Unknown* classname::getObject() const { \
    lb_I_Unknown* uk = NULL; \
    data->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); \
    return uk; \
} \
\
lb_I_KeyBase* LB_STDCALL classname::getKey() const { \
        lb_I_KeyBase* kbase = NULL; \
        return key; \
} \
\
void LB_STDCALL classname::setNext(lb_I_Element *e) { \
        e->queryInterface("lb_I_Element", (void**) &next, __FILE__, __LINE__); \
} \
\
lb_I_Element* LB_STDCALL classname::getNext() const { \
        return next; \
}
/*...e*/
/*...sclass lb_I_Container:0:*/
class lb_I_Container : public lb_I_Unknown {

protected:
    lb_I_Container() {}
    virtual ~lb_I_Container() {}

public:
    virtual int LB_STDCALL Count() = 0;

    virtual lbErrCodes LB_STDCALL insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) = 0;
    virtual lbErrCodes LB_STDCALL remove(lb_I_KeyBase** const key) = 0;
    virtual int LB_STDCALL exists(lb_I_KeyBase** const e) = 0;
    virtual int LB_STDCALL hasMoreElements() = 0;
    virtual lb_I_Unknown* LB_STDCALL nextElement() = 0;

        /**
         * Direct access over key
         */
    virtual lb_I_Unknown* LB_STDCALL getElement(lb_I_KeyBase** const key) = 0;
    virtual void LB_STDCALL setElement(lb_I_KeyBase** key, lb_I_Unknown** const e) = 0;

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
        virtual int LB_STDCALL exists(lb_I_KeyBase** const e); \
        virtual int LB_STDCALL Count(); \
        \
        virtual lbErrCodes LB_STDCALL _insert(lb_I_Unknown** const e, lb_I_KeyBase** const key); \
        virtual lbErrCodes LB_STDCALL insert(lb_I_Unknown** const e, lb_I_KeyBase** const key); \
        \
        virtual lbErrCodes LB_STDCALL remove(lb_I_KeyBase** const key); \
        virtual lbErrCodes LB_STDCALL _remove(lb_I_KeyBase** const key); \
        \
        virtual lb_I_Unknown* LB_STDCALL getElement(lb_I_KeyBase** const key); \
        virtual lb_I_Unknown* LB_STDCALL nextElement(); \
        \
        \
        virtual void LB_STDCALL setElement(lb_I_KeyBase** key, lb_I_Unknown** const e); \
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

/*...sbla \40\Does not work in VC if it is in next macro\41\:0:*/
/*
classname::classname() { \
    iteration = 0; \
    ref = 0; \
    iterator = NULL; \
    count = 0; \
} \
\
classname::~classname() { \
} \
*/
/*...e*/

/*...sIMPLEMENT_LB_I_CONTAINER_IMPL base \40\classname\41\ \47\\47\ only base lb_I_Unknown:0:*/
#define IMPLEMENT_LB_I_CONTAINER_IMPL(classname) \
int LB_STDCALL classname::Count() { \
        return count; \
} \
\
void LB_STDCALL classname::deleteAll() { \
\
    if (container_data == NULL) { \
        CL_LOG("Error: Can't remove from empty container!"); \
        return ;\
    } \
\
    lb_I_Element* pre = NULL; \
\
    while (container_data->getNext() != NULL) { \
        pre = container_data; \
        container_data = container_data->getNext(); \
        RELEASE(pre); \
    } \
    RELEASE(container_data); \
\
} \
\
int LB_STDCALL classname::exists(lb_I_KeyBase** const key) { \
    CL_LOG(#classname"::deleteAll() has not been implemented completly"); \
    if (getElement(key) == NULL) return 0; \
    return 1; \
} \
\
lbErrCodes LB_STDCALL classname::insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { \
        lbErrCodes err = ERR_NONE; \
\
        if ((err = _insert(e, key)) != ERR_NONE) { \
                CL_LOG("lbContainer::insert(...) Failed!"); \
                return err; \
        } \
\
        count++; \
        return err; \
} \
\
lbErrCodes LB_STDCALL classname::remove(lb_I_KeyBase** const key) { \
        lbErrCodes err = ERR_NONE; \
\
        if ((err = _remove(key)) != ERR_NONE) { \
                CL_LOG("lbContainer::remove(...) Failed!"); \
                return err; \
        } \
\
        count--; \
        return err; \
} \
\
lbErrCodes LB_STDCALL classname::_insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { \
\
    if (container_data == NULL) { \
        lbElement* _data = new lbElement(*e, *key); \
        _data->setModuleManager(manager.getPtr()); \
\
        _data->queryInterface("lb_I_Element", (void**) &container_data, __FILE__, __LINE__); \
        if (container_data == NULL) CL_LOG("Could not get unknown interface of lbElement!"); \
\
        lb_I_Unknown* uk_o = NULL; \
        if ((uk_o = container_data->getObject()) == NULL) { \
                CL_LOG("Failed to insert first element in classname::insert"); \
                return ERR_CONTAINER_INSERT; \
        } else RELEASE(uk_o); \
    } \
    else { \
        lb_I_Element* temp; \
        for (temp = container_data; temp != NULL; temp = temp->getNext()) { \
            lb_I_Element* next = temp->getNext(); \
\
            if (next != NULL) { \
                if (next->getKey() < *key) { \
                    lbElement* el = new lbElement(*e, *key, next); \
                    el->setModuleManager(manager.getPtr()); \
                    temp->setNext(el); \
                    return ERR_NONE; \
                } \
            } \
            else { \
            	lbElement* el = new lbElement(*e, *key, next); \
            	el->setModuleManager(manager.getPtr()); \
                temp->setNext(el); \
                return ERR_NONE; \
            } \
        } \
    } \
    return ERR_NONE; \
} \
lbErrCodes LB_STDCALL classname::_remove(lb_I_KeyBase** const key) { \
\
    if (container_data == NULL) { \
        CL_LOG("Error: Can't remove from empty container!"); \
        return ERR_CONTAINER_REMOVE; \
    } \
\
    lb_I_Element* pre = container_data; \
    container_data = container_data->getNext(); \
\
    if (pre->getKey() == *key) { \
        RELEASE(pre); \
        return ERR_NONE; \
    } \
\
    for (lb_I_Element* temp = container_data; temp != NULL; temp = container_data->getNext()) { \
        if (temp->getKey() == *key) { \
            pre->setNext(temp->getNext()); \
            RELEASE(temp); \
            return ERR_NONE; \
        } \
    } \
    CL_LOG("Error: No object with that key"); \
    return ERR_CONTAINER_REMOVE; \
} \
\
int LB_STDCALL classname::hasMoreElements() { \
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
lb_I_Unknown* LB_STDCALL classname::nextElement() { \
    lb_I_Element *temp = iterator; \
    if (temp == NULL) { \
        CL_LOG("Error: Please call hasMoreElements first to check if any elements are available!"); \
        getch(); \
        return NULL; \
    } \
    iterator = iterator->getNext(); \
\
    if (temp == NULL) cout << "Temporary iterator object is NULL!" << endl; \
\
    lb_I_Unknown *o = temp->getObject(); \
\
    if (o == NULL) cout << "Temporary object o is NULL!" << endl; \
\
    return o; \
} \
\
lb_I_Unknown* LB_STDCALL classname::getElement(lb_I_KeyBase** const key) { \
    lb_I_Element* temp = container_data; \
    while (temp) { \
        if ((temp) && (*(temp->getKey()) == *key)) { \
          lb_I_Unknown *o = temp->getObject(); \
          return o; \
        } \
\
        temp = temp->getNext(); \
    } \
    return NULL; \
} \
\
void LB_STDCALL classname::setElement(lb_I_KeyBase** key, lb_I_Unknown ** const e) { \
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

	virtual char* LB_STDCALL getCreationLoc(char* addr) = 0;
        virtual void LB_STDCALL notify_create(lb_I_Unknown* that, char* implName, char* file = "", int line = 0) = 0;
        virtual void LB_STDCALL notify_add(lb_I_Unknown* that, char* implName, char* file, int line) = 0;
        virtual void LB_STDCALL notify_release(lb_I_Unknown* that, char* implName, char* file, int line) = 0;

        virtual int  LB_STDCALL can_delete(lb_I_Unknown* that, char* implName, char* file = "", int line = 0) = 0;

        /**
         * This function loads a module and stores the modulehandle in an array
         * or a list. If the object is destroyed, the loaded modules are
         * automatically unloaded (the array/list).
         */
        virtual lbErrCodes LB_STDCALL load(char* name) = 0;
        
        
        /**
         * The module manager is responsible for creating any instances, that are
         * available. This implementation knows that the directory of functors
         * for instances are stored in an XML file (DTD file v1.3).
         *
         * The current implementation for this in the function request is not the
         * intention for the interface lb_I_Requestable.
         *
         * The new function for this may be:
         */


        /**
         * get back a lb_I_String for a functor or a lb_I_Container for a list of
         * them. The errcode helps to decide.
         */
        virtual lbErrCodes LB_STDCALL getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk) = 0;
        virtual lbErrCodes LB_STDCALL getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk) = 0;
        
        /**
         *
         */
        
        //virtual lbErrCodes getObjectInstance(char* name, lb_I_Requestable*& inst) = 0; 
        virtual lbErrCodes LB_STDCALL getObjectInstance(const char* name, lb_I_Container*& inst) = 0;
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

// This order does not work with visual C++ !!??
//    virtual void LB_STDCALL log(const char *msg, long line, char* file) = 0;
    virtual void LB_STDCALL logdirect(const char *msg, char *f, int level) = 0;
// Take it here...    
    virtual void LB_STDCALL log(const char *msg, long line, char* file) = 0;
    virtual void LB_STDCALL log(int log) = 0;
    virtual void LB_STDCALL enable(char *where) = 0;
    virtual void LB_STDCALL disable(char *where) = 0;
    virtual void LB_STDCALL event_begin(char *event) = 0;
    virtual void LB_STDCALL event_end(char *event) = 0;
    virtual void LB_STDCALL setPrefix(char* p) = 0;
};
/*...e*/
/*...sZThread interfaces:0:*/
#ifndef WINDOWS
class lb_I_Runnable : public lb_I_Unknown {
protected:
    lb_I_Runnable() {}
    virtual ~lb_I_Runnable() {}

public:
    virtual lbErrCodes run() = 0;
};    

class lb_I_ZThread : public lb_I_Runnable {
protected:
    lb_I_ZThread() {}
    virtual ~lb_I_ZThread() {}
    
public:
    virtual lb_I_ZThread* operator->() = 0;
    virtual bool equals(const lb_I_ZThread* t) const = 0;
    virtual bool operator==(const lb_I_ZThread* t) const = 0;
    virtual lbErrCodes kill() = 0;
    virtual lbErrCodes join() = 0;
    virtual lbErrCodes run(lb_I_Runnable* target) = 0;
    virtual lbErrCodes interrupt() = 0;
    // The set/getPriority functions are not implemented yet
    virtual bool isInterrupted() = 0;
    virtual bool isKilled() = 0;
    virtual bool isDaemon() = 0;
    virtual lbErrCodes setDaemon(bool flag) = 0;
    virtual lbErrCodes setNotify(bool flag) = 0;
    virtual bool wantNotify() = 0;
    virtual lbErrCodes sleep(unsigned long s) = 0;
    virtual lbErrCodes yield() = 0;
    // current is not implemented yet
    // FastThreadLocal is not implemented yet
};
#endif
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

