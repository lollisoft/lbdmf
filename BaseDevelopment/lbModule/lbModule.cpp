/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.36 $
 * $Name:  $
 * $Id: lbModule.cpp,v 1.36 2002/10/01 19:22:59 lothar Exp $
 *
 * $Log: lbModule.cpp,v $
 * Revision 1.36  2002/10/01 19:22:59  lothar
 * Broken
 *
 * Revision 1.35  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
 * Revision 1.34  2002/08/31 10:49:14  lothar
 * Deactivated IR_USAGE
 *
 * Revision 1.33  2002/08/21 18:01:37  lothar
 * Implemented the new container functions for direct access
 *
 * Revision 1.32  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.31  2002/06/20 22:16:47  lothar
 * Found bug (really not a bug) about container deletion message.
 * Message removed by another order of UAP instances.
 *
 * Revision 1.30  2002/06/20 21:04:29  lothar
 * Using tracking for better debugging
 *
 * Revision 1.29  2002/06/01 09:16:06  lothar
 * Removed some unneccesary code
 *
 * Revision 1.28  2002/05/30 17:53:01  lothar
 * Current development seems to run
 *
 * Revision 1.27  2002/05/01 14:17:10  lothar
 * This version does not compile
 *
 * Revision 1.26  2002/04/25 18:07:57  lothar
 * Added Skiplist implementation
 *
 * Revision 1.25  2002/04/24 18:36:19  lothar
 * Dump references and print references
 *
 * Revision 1.24  2002/04/18 19:23:43  lothar
 * Does not compile ???
 *
 * Revision 1.23  2002/04/15 18:24:31  lothar
 * Huge changes - works good
 *
 * Revision 1.22  2002/02/25 06:17:19  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 * Revision 1.21  2001/12/15 17:53:26  lothar
 * Reactivated deleteValue usage
 *
 * Revision 1.19  2001/12/12 17:12:44  lothar
 * Hehe - runs on linux
 *
 * Revision 1.18  2001/10/08 20:11:22  lothar
 * This module now compiles under linux
 *
 * Revision 1.17  2001/10/08 19:34:27  lothar
 * Include lbXMLConfig.h no longer used
 *
 * Revision 1.15  2001/10/04 19:28:32  lothar
 * Current version seems to work good (without big memory holes)
 *
 * Revision 1.14  2001/08/18 07:38:55  lothar
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.13  2001/07/18 22:43:55  lothar
 * Using more UAP's - works, but mem leak still there ?
 *
 * Revision 1.12  2001/07/18 05:50:18  lothar
 * Seems to work now (lbDOMNode::parent - refcount must be corrected)
 *
 * Revision 1.11  2001/07/12 20:45:46  lothar
 * Test UNKNOWN_AUTO_PTR, but a declaration does not
 * work in a class, because of the explicit reference argument.
 *
 * Revision 1.10  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.9  2001/06/23 07:18:53  lothar
 * Interface repository now works with the basic test
 *
 **************************************************************/
/*...e*/


#define IR_USAGE

/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <conio.h>

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <malloc.h>

#include <lbInterfaces.h>
#include <lbConfigHook.h>

/*...sLB_MODULE_DLL scope:0:*/
#define LB_MODULE_DLL
#include <lbmodule-module.h>
/*...e*/

#include <lbModule.h>
//#include <lbXMLConfig.h>
#include <lbkey.h>
/*...e*/

class lbSkipListElement;
typedef lb_I_Element* Elem;
#define MAXLEVEL 9


/*...sclass SkipNode:0:*/
class SkipNode {
  public:
    int myLevel;
    UAP(lb_I_Element, value, __FILE__, __LINE__)
    SkipNode** forward;
    
    SkipNode();
    SkipNode(lb_I_Element* r, int level);
    virtual ~SkipNode();
    
};
/*...e*/
/*...sclass SkipList:0:*/
class SkipList : public lb_I_Container {
private:
      SkipNode* head;
      SkipNode* skipiterator;
      int level;
      int flag;

      void AdjustHead(int& level) {level = MAXLEVEL;}

public:
	SkipList();
	virtual ~SkipList();
	
	
	DECLARE_LB_UNKNOWN()
	DECLARE_LB_I_CONTAINER_IMPL()

public:


	lb_I_Unknown* search(lb_I_KeyBase*);
	void insert(Elem);
      
      
      
	void remove(Elem);
	int can_dump();
	Elem dump_next();
};
/*...e*/
/*...sclass lbSkipListElement:0:*/
class lbSkipListElement : public lb_I_Element {
public:
    lbSkipListElement() { 
    	ref = STARTREF; 
    	next = NULL; 
    	data = NULL; 
    	key = NULL; 
    	manager = NULL;
    }
    virtual ~lbSkipListElement();
	
    lbSkipListElement(const lb_I_Element &e) { 
    	ref = STARTREF; 
    	next = e.getNext(); 
	manager = NULL;
    }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbSkipListElement)
#ifndef UNIX
    lb_I_Unknown* getObject() const;
#endif
};
/*...e*/

/*...sclass lbSkipListContainer:0:*/
/*...sSkipNode implementation:0:*/
SkipNode::SkipNode() {
    	myLevel = MAXLEVEL;
    	value = NULL;
    	forward = new SkipNode* [myLevel+1];
    	for (int i=0; i<=myLevel; i++)
    	    forward[i] = NULL;
}
    
SkipNode::SkipNode(lb_I_Element* r, int level) {
        myLevel = level;
        value = r;
        forward = new SkipNode* [level+1];
        for (int i=0; i<=level; i++)
            forward[i] = NULL;
}
SkipNode::~SkipNode() { 
      LOG("SkipNode destructor called")
      delete [] forward; 
      LOG("Deleted forward array")
      
      if (value != NULL) RELEASE(value)
      LOG("Released value of this element")
}
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(SkipList)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL SkipList::setData(lb_I_Unknown* uk) {
	LOG("SkipList::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}
SkipList::SkipList() {
	iteration = 0;
	head = new SkipNode();
	skipiterator = NULL;
	flag = 1;
	level = MAXLEVEL;
}

SkipList::~SkipList() {
	delete head;
}
/*...sSkipList\58\\58\Count\40\\41\:0:*/
int LB_STDCALL SkipList::Count() { 
        return count; 
} 
/*...e*/
/*...sSkipList\58\\58\deleteAll\40\\41\:0:*/
void LB_STDCALL SkipList::deleteAll() { 
	LOG("DeleteAll() called")
	delete head;
	LOG("Deleted head")
	head = new SkipNode();
	LOG("New head created")
	level = MAXLEVEL;

	iteration = 0;
	skipiterator = NULL;
} 
/*...e*/
/*...sSkipList\58\\58\exists\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
int LB_STDCALL SkipList::exists(lb_I_KeyBase** const key) { 
    lb_I_Unknown* s = search(*key);
    
    if (s == NULL) return 0;	

    return 1; 
} 
/*...e*/
/*...sSkipList\58\\58\insert\40\lb_I_Unknown\42\\42\ const e\44\ lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { 
        lbErrCodes err = ERR_NONE; 
        
        lbSkipListElement* el = new lbSkipListElement(*e, *key);

        insert(el);
        
        return err; 
} 
/*...e*/
/*...sSkipList\58\\58\remove\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::remove(lb_I_KeyBase** const key) { 
        lbErrCodes err = ERR_NONE; 
        lbSkipListElement* el = new lbSkipListElement(NULL, *key);
        
        remove(el);
        
        delete el;

        return err; 
} 
/*...e*/
/*...sSkipList\58\\58\_insert\40\lb_I_Unknown\42\\42\ const e\44\ lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::_insert(lb_I_Unknown** const e, lb_I_KeyBase** const key) { 
/*...sbla:0:*/
#ifdef bla
    if (container_data == NULL) { 
        lbElement* _data = new lbElement(*e, *key); 
        _data->setModuleManager(manager.getPtr(), __FILE__, __LINE__); 

        _data->queryInterface("lb_I_Element", (void**) &container_data, __FILE__, __LINE__); 
        if (container_data == NULL) LOG("Could not get unknown interface of lbElement!"); 

        lb_I_Unknown* uk_o = NULL; 
        if ((uk_o = container_data->getObject()) == NULL) { 
                LOG("Failed to insert first element in SkipList::insert"); 
                return ERR_CONTAINER_INSERT; 
        } else RELEASE(uk_o); 
    } 
    else { 
        lb_I_Element* temp; 
        for (temp = container_data; temp != NULL; temp = temp->getNext()) { 
            lb_I_Element* next = temp->getNext(); 

            if (next != NULL) { 
                if (next->getKey() < *key) { 
                    lbElement* el = new lbElement(*e, *key, next); 
                    el->setModuleManager(manager.getPtr(), __FILE__, __LINE__); 
                    temp->setNext(el); 
                    return ERR_NONE; 
                } 
            } 
            else { 
            	lbElement* el = new lbElement(*e, *key, next); 
            	el->setModuleManager(manager.getPtr(), __FILE__, __LINE__); 
                temp->setNext(el); 
                return ERR_NONE; 
            } 
        } 
    } 
#endif    
/*...e*/
    return ERR_NONE; 
} 
/*...e*/
/*...sSkipList\58\\58\_remove\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lbErrCodes LB_STDCALL SkipList::_remove(lb_I_KeyBase** const key) { 
/*...sbla:0:*/
#ifdef bla
    if (container_data == NULL) { 
        LOG("Error: Can't remove from empty container!"); 
        return ERR_CONTAINER_REMOVE; 
    } 

    lb_I_Element* pre = container_data; 
    container_data = container_data->getNext(); 

    if (pre->getKey() == *key) { 
        RELEASE(pre); 
        return ERR_NONE; 
    } 

    for (lb_I_Element* temp = container_data; temp != NULL; temp = container_data->getNext()) { 
        if (temp->getKey() == *key) { 
            pre->setNext(temp->getNext()); 
            RELEASE(temp); 
            return ERR_NONE; 
        } 
    } 
#endif
    LOG("Error: No object with that key"); 
/*...e*/
    return ERR_CONTAINER_REMOVE; 
} 
/*...e*/
/*...sSkipList\58\\58\hasMoreElements\40\\41\:0:*/
int LB_STDCALL SkipList::hasMoreElements() { 
    return can_dump();
} 
/*...e*/
/*...sSkipList\58\\58\nextElement\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL SkipList::nextElement() { 

	Elem e = dump_next();
	
	if(e != NULL) {
		return e->getObject();
	} else {
	        LOG("Error: Please call hasMoreElements first to check if any elements are available!"); 
        	getch(); 
	        return NULL; 
	}
} 
/*...e*/
/*...sSkipList\58\\58\getElement\40\lb_I_KeyBase\42\\42\ const key\41\:0:*/
lb_I_Unknown* LB_STDCALL SkipList::getElement(lb_I_KeyBase** const key) { 

    return search(*key);
} 
/*...e*/
/*...sSkipList\58\\58\setElement\40\lb_I_KeyBase\42\\42\ key\44\ lb_I_Unknown \42\\42\ const e\41\:0:*/
void LB_STDCALL SkipList::setElement(lb_I_KeyBase** key, lb_I_Unknown ** const e) { 
    remove(key); 
    insert(e, key); 
}
/*...e*/
lb_I_Unknown* LB_STDCALL SkipList::getElementAt(int i) {
        LOG("SkipList::getElementAt(int i) not implemented")
        int ii = 0;
        lb_I_Element* temp = container_data;
        while (temp != NULL) {
                if (ii == i) return temp->getObject();
                temp = temp->getNext();
        }
        return NULL;
}
lb_I_KeyBase* LB_STDCALL SkipList::getKeyAt(int i) {
        LOG("SkipList::getKeyAt(int i) not implemented")
        int ii = 0;
        lb_I_Element* temp = container_data;
        while (temp != NULL) {
                if (ii == i) return temp->getKey();
                temp = temp->getNext();
        }
        return NULL;
}


/*...srandomLevel\40\void\41\:0:*/
int randomLevel(void) { // Pick a level on exponential distribution
  int level;
  for (level=0; (rand()%2) == 0; level++); // Do nothing
  return level;
}
/*...e*/
/*...sSkipList\58\\58\search\40\lb_I_KeyBase\42\ searchKey\41\:0:*/
lb_I_Unknown* SkipList::search(lb_I_KeyBase* searchKey) { // Skiplist Search
  SkipNode *x = head;                  // Dummy header node
  
  if (x == NULL) LOG("Error: NULL pointer while searching in skiplist");
  
  for (int i=level; i>=0; i--) {
    while ((x->forward[i] != NULL) && (*(x->forward[i]->value) < searchKey)) {
      x = x->forward[i];
    }
  }
  x = x->forward[0];  // Move to actual record, if it exists
  if ((x != NULL) && (*(x->value) == searchKey)) {
  	return x->value->getObject();
  } else return NULL;
}
/*...e*/
/*...sSkipList\58\\58\insert\40\Elem newValue\41\:0:*/
void SkipList::insert(Elem newValue) { // Insert into skiplist
  SkipNode *x = head;           // Start at header node
  int i;
  int newLevel = randomLevel(); // Select level for new node

  if (newLevel > level) {       // New node will be deepest in list
    AdjustHead(newLevel);       // Add null pointers to header
    level = newLevel;
  }
	  
  SkipNode** update = NULL;    // Update tracks end of each level
  
  update = new SkipNode* [level+1]; 

  for(i=level; i>=0; i--) { // Search for insert position
    lb_I_Element* e = (x->forward[i] != NULL) ? x->forward[i]->value.getPtr() : NULL;
    while((x->forward[i] != NULL) && (*e < newValue->getKey())) {
      x = x->forward[i];
      e = x->forward[i] != NULL ? x->forward[i]->value.getPtr() : NULL;
    }
    update[i] = x;              // Keep track of end at level i
  }
  
  x = new SkipNode(newValue, newLevel); // Create new node
  
  for (i=0; i<=newLevel; i++) { // Splice into list
    x->forward[i] = update[i]->forward[i]; // Who x points to
    update[i]->forward[i] = x;             // Who y points to
  }
}
/*...e*/
/*...sSkipList\58\\58\remove\40\Elem searchKey\41\:0:*/
void SkipList::remove(Elem searchKey) {
    // update holds pointers to next elements of each level
    SkipNode** update = NULL;    // Update tracks end of each level
  
    update = new SkipNode* [level+1]; 
    
    SkipNode *x = head;                  // Dummy header node
    SkipNode *found = NULL;
    
    for (int i=level; i>=0; i--) {

      while ((x->forward[i] != NULL) && (*(x->forward[i]->value) < searchKey->getKey())) {
        x = x->forward[i];
      }
        
      update[i] = x;
    }

    x = x->forward[0];  // Move to actual record, if it exists
    
    if ((x != NULL) && (*(x->value) == searchKey->getKey())) found = x;
    else return;

    // element found, so rebuild list without node:
    if (*(found->value) == searchKey->getKey()) {
      for (int i=0; i<=level; i++) {
        if (update[i]->forward[i] == found) {
          update[i]->forward[i] = found->forward[i];
        }
      }
      
      // element can be freed now (would happen automatically):
      delete found;
      
      // maybe we have to downcorrect the level of the list: 
      while (level>0  &&  head->forward[level] != NULL && head->forward[level]->value==NULL) {
        level--;
      }
    }
  }


/*...e*/
/*...sSkipList\58\\58\can_dump\40\\41\:0:*/
int SkipList::can_dump() {
	if (iteration == 0) { 
        	iteration = 1; 
	        skipiterator = head; 
		flag = 1;
	} 

	if (skipiterator == NULL) { 
	        iteration = 0; 
	        flag = 1;
	        return 0; 
	} 
	
//	if (flag == 0) return 0;
	
	return 1;
}
/*...e*/
/*...sSkipList\58\\58\dump_next\40\\41\:0:*/
Elem SkipList::dump_next() {
	if (skipiterator != NULL) {
		Elem e = skipiterator->value.getPtr();
		
		while (e == NULL) {
			skipiterator = skipiterator->forward[0];
			e = skipiterator->value.getPtr();
		}

		skipiterator = skipiterator->forward[0];
/*...sbla:0:*/
#ifdef bla		
		for(int i=0; i<=skipiterator->myLevel && flag != 0; i++)
			if (skipiterator->forward[i] == NULL){
				printf("No more elements in skiplist\n");
		        	flag = 0;
			}
#endif		
/*...e*/
		return e;
	} else {
		printf("Return NULL because skipiterator is NULL\n");
		return NULL;
	}
}

/*...sbla:0:*/
#ifdef bla
void dump() {
    SkipNode* temp = head;
    int flag = 1;

    for ( ; temp!= NULL; temp = temp->forward[0]) {
        cout << "temp->value is " << temp->value << endl;
        for(int i=0; i<=temp->myLevel && flag != 0; i++)
            if (temp->forward[i] == NULL){
                cout << " rest of list is empty" << endl;
                flag = 0;
            }
            else
                cout<<"  point to "<<temp->forward[i]->value<<"\n";
    }
}
#endif
/*...e*/
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbSkipListElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbSkipListElement)

lbErrCodes LB_STDCALL lbSkipListElement::setData(lb_I_Unknown* uk) {
	LOG("lbSkipListElement::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...sclass InstanceRepository:0:*/
/*...sreferenceList:0:*/
typedef struct _referenceList {
        char* file;
        int line;
        int count;
        
        _referenceList* next;
} referenceList, *preferenceList;
/*...e*/
/*...sinstanceList:0:*/
typedef struct _instanceList {
        char* addr;
        char* classname;
        char* file;
        int line;
        referenceList* rList;
        
        _instanceList* next;
} instanceList, *pinstanceList;
/*...e*/
/*...sclassnameList:0:*/
typedef struct _classnameList {
        char* classname;
        instanceList* instances;
        
        _classnameList* next;
} classnameList, *pclassnameList;
/*...e*/

class InstanceRepository;
InstanceRepository* IR = NULL;

/*...sclass lbInstance:0:*/
/*...sclass lbInstance:0:*/
class lbInstance : 
public lb_I_Instance
{
private:
        char* addr;
        char* classname;
        char* file;
        int line;
        char* key;

	DECLARE_LB_UNKNOWN()
	DECLARE_LB_KEYBASE()
	
public:
	lbInstance();
	virtual ~lbInstance();
	
	virtual char* LB_STDCALL getAddress();
	virtual char* LB_STDCALL getInstanceClassname();
	virtual char* LB_STDCALL getFile();
	virtual int LB_STDCALL getLine();
	
	virtual void LB_STDCALL setAddress(char* a);
	virtual void LB_STDCALL setClassname(char* c);
	virtual void LB_STDCALL setFile(char* f);
	virtual void LB_STDCALL setLine(int l);
	
	/**
	 * Build a string with classname + _ + file + _ + line as a key for the reference.
	 * If the release function is used directly, it shows me an unregistered reference,
	 * so I will find all non UAP pointers.
	 */
	virtual void LB_STDCALL addReference(char* classname, char* file, int line);
	virtual void LB_STDCALL delReference(char* classname, char* file, int line);
	
	UAP(lb_I_Container, references, __FILE__, __LINE__)
	lbErrCodes err;
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInstance)
	ADD_INTERFACE(lb_I_KeyBase)
	ADD_INTERFACE(lb_I_Instance)
END_IMPLEMENT_LB_UNKNOWN()

lbInstance::lbInstance() {
	addr = NULL;
	classname = NULL;
	file = NULL;
	line = -1;
	key = NULL;
}

lbInstance::~lbInstance() {
	
}

/*...svoid LB_STDCALL lbInstance\58\\58\addReference\40\char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbInstance::addReference(char* classname, char* file, int line) {
	if (references == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, references)
	}
	char* buf = new char[strlen(classname)+strlen(file)+10];
	buf[0] = 0;
	
	sprintf(buf, "%s_%s_%d", classname, file, line);
	
	lbStringKey* key = new lbStringKey(buf);

	if (manager == NULL) LOG("Error: InstanceRepository has got a NULL pointer for the manager");
	key->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
	QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)

	UAP(lb_I_Unknown, element, __FILE__, __LINE__)
	element = references->getElement(&_key);
	
	if (element != NULL) {
		UAP(lb_I_InstanceReference, instance, __FILE__, __LINE__)
		QI(element, lb_I_InstanceReference, instance, __FILE__, __LINE__)
		if (instance != NULL) {
			instance->setCount(instance->getCount() + 1);
		}
	}
	
	delete [] buf;
}
/*...e*/
/*...svoid LB_STDCALL lbInstance\58\\58\delReference\40\char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbInstance::delReference(char* classname, char* file, int line) {
        if (references == NULL) {
                REQUEST(manager.getPtr(), lb_I_Container, references)
        }

	char* buf = new char[strlen(classname)+strlen(file)+10];
	buf[0] = 0;
	
	sprintf(buf, "%s_%s_%d", classname, file, line);
	
	lbStringKey* key = new lbStringKey(buf);

	if (manager == NULL) LOG("Error: InstanceRepository has got a NULL pointer for the manager");
	key->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
	QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)

	UAP(lb_I_Unknown, element, __FILE__, __LINE__)
	element = references->getElement(&_key);

	if (element != NULL) {
		UAP(lb_I_InstanceReference, instance, __FILE__, __LINE__)
		QI(element, lb_I_InstanceReference, instance, __FILE__, __LINE__)
		if (instance != NULL) {
			if (instance->getCount() == 0) {
				//LOG("Warning: Reference count goes under 0!")
				DebugBreak();
			}
			instance->setCount(instance->getCount() - 1);
		}
	}
	
	delete [] buf;
}
/*...e*/
/*...sper instance functions:0:*/
char* LB_STDCALL lbInstance::getAddress() {
	return addr;
}

char* LB_STDCALL lbInstance::getInstanceClassname() {
	return classname;
}

char* LB_STDCALL lbInstance::getFile() {
	return file;
}
	
int LB_STDCALL lbInstance::getLine() {
	return line;
}

void LB_STDCALL lbInstance::setAddress(char* a) {
	if (addr != NULL) free(addr);
	addr = strdup(a);
}

void LB_STDCALL lbInstance::setClassname(char* c) {
	if (classname != NULL) free(classname);
	classname = strdup(c);
}

void LB_STDCALL lbInstance::setFile(char* f) {
	if (file != NULL) free(file);
	file = strdup(f);
}

void LB_STDCALL lbInstance::setLine(int l) {
	line = l;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbInstance\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbInstance::setData(lb_I_Unknown* uk) {

	if (strcmp("lbInstance", uk->getClassName()) == 0) {
		lb_I_Instance* i;
		
		if (uk->queryInterface("lb_I_Instance", (void**) &i, __FILE__, __LINE__) != ERR_NONE) {
			LOG("Error: Failed to get interface lb_I_Instance")
		}
		
		if (i != NULL) {
			file = strdup(i->getFile());
			line = i->getLine();
			addr = strdup(i->getAddress());
			classname = strdup(i->getInstanceClassname());
		}
		return ERR_NONE;
	}
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...sImplementation for key:0:*/
// Implementation for key

char* LB_STDCALL lbInstance::getKeyType() const {
    return "string";
}

int LB_STDCALL lbInstance::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(addr, ((const lbInstance*) _key)->addr) == 0);
}

int LB_STDCALL lbInstance::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(addr, ((const lbInstance*) _key)->addr) > 0);
}

int LB_STDCALL lbInstance::lessthan(const lb_I_KeyBase* _key) const {
    return (strcmp(addr, ((const lbInstance*) _key)->addr) < 0);
}

char* LB_STDCALL lbInstance::charrep() const {
    return addr;
}
/*...e*/
/*...e*/
/*...sclass lbInstanceReference:0:*/
class lbInstanceReference : 
public lb_I_InstanceReference
{
private:
        char* file;
        int line;
        int count;

	DECLARE_LB_UNKNOWN()
	
public:
        lbInstanceReference();
        virtual ~lbInstanceReference();	

	virtual char* LB_STDCALL getFile();
	virtual int LB_STDCALL getLine();
	virtual int LB_STDCALL getCount();

	virtual void LB_STDCALL setFile(char* f);
	virtual void LB_STDCALL setLine(int l);
	virtual void LB_STDCALL setCount(int c);

};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInstanceReference)
	ADD_INTERFACE(lb_I_InstanceReference)
END_IMPLEMENT_LB_UNKNOWN()

lbInstanceReference::lbInstanceReference() {
}

lbInstanceReference::~lbInstanceReference() {
}

int LB_STDCALL lbInstanceReference::getLine() {
	return line;
}

int LB_STDCALL lbInstanceReference::getCount() {
	return count;
}

char* LB_STDCALL lbInstanceReference::getFile() {
	return file;
}

void LB_STDCALL lbInstanceReference::setLine(int l) {
	line = l;
}

void LB_STDCALL lbInstanceReference::setCount(int c) {
	count = c;
}

void LB_STDCALL lbInstanceReference::setFile(char* f) {

}
	
lbErrCodes LB_STDCALL lbInstanceReference::setData(lb_I_Unknown* uk) {
	LOG("lbInstanceReference::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}
#ifdef bla
/*...skey:0:*/
char* LB_STDCALL lbInstanceReference::getKeyType() const {
    return "lbInstanceReference";
}

int LB_STDCALL lbInstanceReference::equals(const lb_I_KeyBase* _key) const {
    return strcmp(key, ((lbInstanceReference*) _key)->key) == 0;
}

int LB_STDCALL lbInstanceReference::greater(const lb_I_KeyBase* _key) const {
    return strcmp(key, ((lbInstanceReference*) _key)->key) > 0;
}

int LB_STDCALL lbInstanceReference::lessthan(const lb_I_KeyBase* _key) const {
    return strcmp(key, ((lbInstanceReference*) _key)->key) < 0;
}

char* lbInstanceReference::charrep() const {
    
    return key;
}
/*...e*/
#endif
/*...e*/

char* Upper(char* string) {
	for (int i = 0; i < strlen(string); i++) string[i] = toupper(string[i]);
	return string;
}

/*...sclass InstanceRepository:0:*/
class InstanceRepository {
private:
        InstanceRepository() {}
public:
	InstanceRepository(lb_I_Module* m);
        virtual ~InstanceRepository();
        
        void LB_STDCALL createInstance(char* addr, char* classname, char* file, int line);
        void LB_STDCALL addReference(char* addr, char* classname, char* file, int line);
        void LB_STDCALL delReference(char* addr, char* classname, char* file, int line);
        void LB_STDCALL destroyInstance(char* addr, char* classname, char* file, int line);
        
	char* LB_STDCALL getCreationLoc(char* addr);
	void LB_STDCALL printReferences(char* addr);	
	void LB_STDCALL dumpReference(instanceList* i);

	void LB_STDCALL loadContainer(lb_I_Module* m);
        
        instanceList* iList;
        classnameList* cList;
        
        UAP(lb_I_Container, lb_iList, __FILE__, __LINE__)
        UAP(lb_I_Container, lb_cList, __FILE__, __LINE__)

private:
	int loadedContainer;
	int instances;
	int references;
	lb_I_Module* manager;
	int skip;
};
/*...e*/
/*...sInstanceRepository\58\\58\InstanceRepository\40\lb_I_Module\42\ m\41\:0:*/
InstanceRepository::InstanceRepository(lb_I_Module* m) {
	manager = m;
        iList = NULL;
        cList = NULL;
        loadedContainer = 0;
        instances = 0;
        references = 0;
        skip = 0;
        lb_iList = NULL;
}
/*...e*/
/*...sInstanceRepository\58\\58\\126\InstanceRepository\40\\41\:0:*/
InstanceRepository::~InstanceRepository() {
        while (iList != NULL) {
                instanceList* temp = iList;
                iList = iList->next;
                dumpReference(temp);
                delete temp;
        }
        
        while (cList != NULL) {
                classnameList* temp = cList;
                cList = cList->next;
                delete temp;
        }
}
/*...e*/

/*...sInstanceRepository\58\\58\createInstance\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::createInstance(char* addr, char* classname, char* file, int line) {
	// First check, if there is no instance
	
	if (skip == 1) return;
	
	instanceList* temp = iList;
	instances++;
	
	if (strcmp("lbInstance", classname) == 0) return;
	if (strcmp("lbStringKey", classname) == 0) return;
	
	if (loadedContainer == 1) {
		
		//DebugBreak();
		
		lbInstance* inst = new lbInstance();
		inst->setModuleManager(manager, __FILE__, __LINE__);
	
		inst->setAddress(addr);
		inst->setClassname(classname);
		inst->setFile(file);
		inst->setLine(line);
		
		lbStringKey *key = new lbStringKey(addr);

		if (manager == NULL) LOG("Error: InstanceRepository has got a NULL pointer for the manager");		
		key->setModuleManager(manager, __FILE__, __LINE__);

		//Stack overflow, because key get's cloned.
		skip = 1;		
		lb_iList->insert((lb_I_Unknown**) &inst, (lb_I_KeyBase**) &key);
		skip = 0;
	} else {
/*...sfirst element:8:*/
	if (iList == NULL) {
		iList = new instanceList;
		char address[20] = "";
		sprintf(address, "%p", iList);
		iList->next = NULL;
		iList->rList = NULL;
		iList->addr = strdup(addr);
		iList->classname = strdup(classname);
		iList->file = strdup(file);
		iList->line = line;
		return;
	}
/*...e*/
/*...smore than one elements:8:*/
	while (temp != NULL) {
		if ((strcmp(Upper(temp->addr), Upper(addr)) == 0) && (strcmp(temp->classname, classname) == 0)) {
			// Error. This instance is always registered
			char buf[1000] = "";
			sprintf(buf, "Error: Instance %s in %s at %d already registered", classname, file, line);
			LOG(buf)
		} else if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			LOG("Error: Found a registered object with the same address. Was it not deleted correctly?")
		} else if (temp->next == NULL) {
			// Insert it here
			instanceList* neu = new instanceList;
			
			neu->next = NULL;
			neu->rList = NULL;
			neu->addr = strdup(addr);
			neu->classname = strdup(classname);
			neu->file = strdup(file);
			neu->line = line;

			temp->next = neu;
			return;
		}
		temp = temp->next;
	}
/*...e*/
	}
}
/*...e*/
/*...sInstanceRepository\58\\58\addReference\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::addReference(char* addr, char* classname, char* file, int line) {
	if (skip == 1) return;
	skip = 1;
	instanceList* temp = iList;
	lbErrCodes err;
	int foundReference = 0;
	
	if (strcmp(classname, "lbModule") == 0) return;
	if (loadedContainer == 1) {
		//DebugBreak();
		lbStringKey *key = new lbStringKey(addr);
		
		if (manager == NULL) LOG("Error: InstanceRepository has got a NULL pointer for the manager");
		key->setModuleManager(manager, __FILE__, __LINE__);
		UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
		QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)
		
		UAP(lb_I_Unknown, element, __FILE__, __LINE__)
		element = lb_iList->getElement(&_key);
		
		if (element != NULL) {
			UAP(lb_I_Instance, instance, __FILE__, __LINE__)
			QI(element, lb_I_Instance, instance, __FILE__, __LINE__)
			if (instance != NULL) {
				//instance->addReference(classname, file, line);
			}
		}
	} else
	while (temp != NULL) {
/*...ssearch instance address:16:*/
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			// Found the entry for this instance
			if (strcmp(temp->classname, classname) == 0) {
				referenceList* rL = temp->rList;
					
				while(rL != NULL) {
					if ((strcmp(rL->file, file) == 0) && (rL->line == line)) {
						rL->count++;
						foundReference = 1;
						break;
					}
					rL = rL->next;
				}
					
				if (foundReference == 0) {
					rL = new referenceList;
					rL->next = temp->rList;
					temp->rList = rL;
					
					rL->file = strdup(file);
					rL->line = line;
					rL->count = 1;
				}
			} else {
				char *buf = NULL;
				buf = (char*) malloc(1000);
				sprintf(buf, 
				"Error: InstanceRepository::addReference() classname differs.\nStored: %s Given: %s\nStored was created in %s at %d with pointer %s", 
				temp->classname, classname, temp->file, temp->line, addr);
				LOG(buf);
				free ((void*) buf);
				return;
			}
		}
/*...e*/
		temp = temp->next;
	}
	
	skip = 0;
	
}
/*...e*/
/*...sInstanceRepository\58\\58\delReference\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::delReference(char* addr, char* classname, char* file, int line) {
	if (skip == 1) return;
	skip = 1;
	instanceList* temp = iList;
	instanceList* prev = NULL;
        lbErrCodes err;
        int foundReference = 0;

	if (strcmp(classname, "lbStringKey") == 0) return;

        if (loadedContainer == 1) {
                lbStringKey *key = new lbStringKey(addr);

                if (manager == NULL) LOG("Error: InstanceRepository has got a NULL pointer for the manager");
                key->setModuleManager(manager, __FILE__, __LINE__);
                UAP(lb_I_KeyBase, _key, __FILE__, __LINE__)
                QI(key, lb_I_KeyBase, _key, __FILE__, __LINE__)

                UAP(lb_I_Unknown, element, __FILE__, __LINE__)
                element = lb_iList->getElement(&_key);

                if (element != NULL) {
                        UAP(lb_I_Instance, instance, __FILE__, __LINE__)
                        QI(element, lb_I_Instance, instance, __FILE__, __LINE__)
                        if (instance != NULL) {
                                //instance->delReference(classname, file, line);
                        }
                }
        } else
	while (temp != NULL) {
/*...ssearch instance address:16:*/
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			// Found the entry for this instance
			if (strcmp(temp->classname, classname) == 0) {
				referenceList* rList = temp->rList;
				referenceList* rPrev = NULL;
				
				if (rList == NULL) printf("Error: Reference list is NULL\n");
/*...sSearch in the references:48:*/
				while (rList != NULL) {
					#ifdef VERBOSE
					printf("Stored reference is in %s at %d\n", rList->file, rList->line);
					#endif
					if ((strcmp(rList->file, file) == 0) && (rList->line == line)) {
						foundReference = 1;
						if (rList->count > 1) {
							rList->count--;
							return;
						} else {
							if (rList->count != 1) LOG("Error: Reference count is wrong")
							
							if (rPrev == NULL) {
								temp->rList = rList->next;
								free(rList->file);
								delete rList;
							} else {
								rPrev = rList->next;
								free(rList->file);
								delete rList;
							}
							
							if (prev == NULL) {
								prev = temp;
								temp = temp->next;
								free(prev->classname);
								free(prev->file);
								if (temp == NULL) {
									delete iList;
									iList = NULL;
								}
								else {
									delete prev;
									prev = NULL;
								}
								return;
							} else {
								prev->next = temp->next;
								free(temp->classname);
								free(temp->file);
								delete temp;
								return;
							}
						}
					}
				
					rPrev = rList;
					rList = rList->next;
				}
/*...e*/
				
				if (foundReference == 0) {
					char buf[1000] = "";
					sprintf(buf, "Error: Reference was not registered (classname=%s, file=%s, line=%d)", 
					classname, file, line);
					#ifdef VERBOSE
					LOG(buf)
					#endif
				}
			} else {
				LOG("Error: InstanceRepository::delReference() classname differs");
				return;
			}
		}
		prev = temp;
		temp = temp->next;
/*...e*/
	}
	skip = 0;
}
/*...e*/
/*...sInstanceRepository\58\\58\destroyInstance\40\char\42\ addr\44\ char\42\ classname\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL InstanceRepository::destroyInstance(char* addr, char* classname, char* file, int line) {
	if (skip == 1) return;
	skip = 1;
	instanceList* temp = iList;
	instanceList* prev = NULL;
	LOG("InstanceRepository::destroyInstance(...) called")

	//DebugBreak();
	
	while (temp != NULL) {
		if ((strcmp(Upper(temp->addr), Upper(addr)) == 0) && (strcmp(temp->classname, classname) == 0)) {
			if (prev == NULL) {
				if (temp->rList != NULL) {
					if (temp->rList->count >= 1) {
						LOG("Error: Destroying an instance, that always has references")
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							char buf[1000] = "";
							sprintf(buf, "Reference for %s is at %s: %d with %d references.\n", classname, rTemp->file, rTemp->line, rTemp->count);
							LOG(buf)
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					} else {
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							char buf[1000] = "";
							sprintf(buf, "Reference for %s is at %s: %d with %d references.\n", classname, rTemp->file, rTemp->line, rTemp->count);
							LOG(buf)
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					}
				} else {
					prev = temp;
					temp = temp->next;
					
					free(prev->addr);
					free(prev->file);
					free(prev->classname);
					delete prev;
				}
			} else {
				if (temp->rList != NULL) {
					if (temp->rList->count >= 1) {
						LOG("Error: Destroying an instance, that always has references")
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							char buf[1000] = "";
							sprintf(buf, "Reference for %s is at %s: %d with %d references.\n", classname, rTemp->file, rTemp->line, rTemp->count);
							LOG(buf)
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					} else {
						referenceList* rTemp = temp->rList;
						
						while (rTemp != NULL) {
							char buf[1000] = "";
							sprintf(buf, "Reference for %s is at %s: %d with %d references.\n", classname, rTemp->file, rTemp->line, rTemp->count);
							LOG(buf)
							referenceList* rPrev = rTemp;
							rTemp = rTemp->next;
							
							free(rPrev->file);
							delete rPrev;
						}
					}
					
				}  else {
				       prev->next = temp->next;

				       free(temp->addr);
				       free(temp->file);
				       free(temp->classname);
				       delete temp;
				}
			}
		}
		
		prev = temp;
		temp = temp->next;
	}
	skip = 0;
}
/*...e*/

/*...sInstanceRepository\58\\58\getCreationLoc\40\char\42\ addr\41\:0:*/
char* LB_STDCALL InstanceRepository::getCreationLoc(char* addr) {
	instanceList* temp = iList;
/*...sfirst element:8:*/
	if (iList == NULL) {
		return "No IR elements available";
	}
/*...e*/
/*...smore than one elements:8:*/
	while (temp != NULL) {
		static char buf[1000] = "";
		sprintf(buf, "Location File: %s, Line: %d", temp->file, temp->line);
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			return buf;
		} 
		temp = temp->next;
	}
/*...e*/
	return strdup("No location stored");	
}
/*...e*/
/*...sInstanceRepository\58\\58\printReferences\40\char\42\ addr\41\:0:*/
void LB_STDCALL InstanceRepository::printReferences(char* addr) {
	instanceList* temp = iList;
LOG("InstanceRepository::printReferences(char* addr) called")	
	while(temp != NULL) {
		if (strcmp(Upper(temp->addr), Upper(addr)) == 0) {
			referenceList* rTemp = temp->rList;
			
			while(rTemp != NULL) {
				printf("Reference for %s in %f at %d with %d stored count's\n", 
				temp->classname, rTemp->file, rTemp->line, rTemp->count);
				rTemp = rTemp->next;
			}
		}
		temp = temp->next;
	}
LOG("InstanceRepository::printReferences(char* addr) leaving")
}
/*...e*/
/*...sInstanceRepository\58\\58\dumpReference\40\instanceList\42\ i\41\:0:*/
void LB_STDCALL InstanceRepository::dumpReference(instanceList* i) {
	referenceList* rTemp = i->rList;
	while(rTemp != NULL) {
		printf("Instance for %s has a reference in %s at %d\n", 
			i->classname, rTemp->file, rTemp->line);
		rTemp = rTemp->next;
	}
}
/*...e*/
/*...sInstanceRepository\58\\58\loadContainer\40\lb_I_Module\42\ m\41\:0:*/
void LB_STDCALL InstanceRepository::loadContainer(lb_I_Module* m) {
	if (loadedContainer == 1) return;
	loadedContainer = 1;

	SkipList* instances = new SkipList();

	lb_iList = instances;
	
	instanceList* temp = iList;
	LOG("Info: InstanceRepository::loadContainer(...) is not implemented completely")
	while (temp != NULL) {
		printf("Have an instance %s in %s at %d\n", temp->classname, temp->file, temp->line);
		temp = temp->next;
	}

}
/*...e*/
/*...e*/

T_pLB_GET_UNKNOWN_INSTANCE DLL_LB_GET_UNKNOWN_INSTANCE;
/*...sclass lbModuleContainer:0:*/
class lbModuleContainer :       public lb_I_Container
{

public:
    lbModuleContainer(const lb_I_Container* c);
    lb_I_Container* operator= (const lb_I_Container* c);

public:

    lbModuleContainer();
    virtual ~lbModuleContainer();

    DECLARE_LB_UNKNOWN()

// This may be a string container

    DECLARE_LB_I_CONTAINER_IMPL()

};
/*...e*/

lb_I_Container* moduleList = NULL;
/*...sclass lbModule and implementation:0:*/
/*...sclass lbModule:0:*/
class lbModule : 
                public lb_I_Module
{
public:
        lbModule() {
                ref = STARTREF+1;
                loadedModules = NULL;
                internalInstanceRequest = 0;
                xml_Instance = NULL;
                system_up = 0;
                initializing = 0;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
                LOG("lbModule init manager");
#endif
/*...e*/
                manager = this;
                setModuleManager(this, __FILE__, __LINE__);
        }
        
        virtual ~lbModule() {
                if (ref != STARTREF) cout << "Error: Reference count mismatch" << endl;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
                LOG("lbModule::~lbModule() called");
#endif
/*...e*/
        }

        DECLARE_LB_UNKNOWN()

        virtual lbErrCodes LB_STDCALL initialize();
        virtual lbErrCodes LB_STDCALL request(const char* request, lb_I_Unknown** result);
        virtual lbErrCodes LB_STDCALL uninitialize();
        
	virtual void LB_STDCALL printReferences(char* addr);        

	virtual char* LB_STDCALL getCreationLoc(char* addr);
        virtual void LB_STDCALL notify_create(lb_I_Unknown* that, char* implName, char* file = "", int line = 0);
        virtual void LB_STDCALL notify_add(lb_I_Unknown* that, char* implName, char* file, int line);
        virtual void LB_STDCALL notify_release(lb_I_Unknown* that, char* implName, char* file, int line);
        virtual int  LB_STDCALL can_delete(lb_I_Unknown* that, char* implName, char* file = "", int line = 0);
        
        virtual lbErrCodes LB_STDCALL load(char* name);
        virtual lbErrCodes LB_STDCALL getObjectInstance(const char* name, lb_I_Container*& inst);

        virtual lbErrCodes LB_STDCALL getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
        virtual lbErrCodes LB_STDCALL getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
        virtual lbErrCodes LB_STDCALL getDefaultImpl(char* interfacename, lb_I_ConfigObject** node, char*& implTor, char*& module);
        
protected:

        void LB_STDCALL getXMLConfigObject(lb_I_XMLConfig** inst);
        lb_I_ConfigObject* LB_STDCALL findFunctorNode(lb_I_ConfigObject** _node, const char* request);
        char* LB_STDCALL findFunctorModule(lb_I_ConfigObject** _node);
        char* LB_STDCALL findFunctorName(lb_I_ConfigObject** ___node);

        lbErrCodes LB_STDCALL makeInstance(char* functor, char* module, lb_I_Unknown** instance);
        
        int internalInstanceRequest;
        UAP(lb_I_Container, loadedModules, __FILE__, __LINE__)
        UAP(lb_I_XMLConfig, xml_Instance, __FILE__, __LINE__)
        int system_up;
        int initializing;
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbModule)
        ADD_INTERFACE(lb_I_Module)
END_IMPLEMENT_LB_UNKNOWN()

/*...slb_I_XMLConfig\42\ LB_STDCALL lbModule\58\\58\getXMLConfigObject\40\\41\:0:*/
typedef lbErrCodes (* LB_STDCALL T_pLB_GETXML_CONFIG_INSTANCE) (lb_I_XMLConfig** inst, lb_I_Module* m, char* file, int line);
T_pLB_GETXML_CONFIG_INSTANCE DLL_LB_GETXML_CONFIG_INSTANCE;

void LB_STDCALL lbModule::getXMLConfigObject(lb_I_XMLConfig** inst) {
	lbErrCodes err = ERR_NONE;
        char *libname = getenv("LBXMLLIB");
        char *ftrname = getenv("LBXMLFUNCTOR");
        char *cfgname = getenv("LBHOSTCFGFILE");
	/**
	 * The UAP seems to try release it self. Because of the macro, it couldn't
	 * register a reference. The instance is not created yet!
	 *
	 * The reference will be created at the line with the QI macro, or a queryInterface()
	 *
	 *
	 */


	/**
	 * Because of not directly using this instance, I do not query an interface for it.
	 * Therefore it will generate the warning, that UAP is not set up correctly.
	 *
	 * The functor cannot use any interface, because it creates instances from real
	 * implementations. So I have to use a macro for using functors. Then I am able to set
	 * the file and line for this instance creation (also a reference !!!!)
	 */



        UAP(lb_I_XMLConfig, xml_I, __FILE__, __LINE__)

        if (libname == NULL) return;
        if (ftrname == NULL) return;
        if (cfgname == NULL) return;

	HINSTANCE h = getModuleHandle();

        if (lbLoadModule(libname, h) != ERR_NONE) {
                exit(1);
        }
        
        setModuleHandle(h);

        if ((err = lbGetFunctionPtr(ftrname, getModuleHandle(), (void**) &DLL_LB_GETXML_CONFIG_INSTANCE)) != ERR_NONE) {
            char buf[1000] = "";
            sprintf(buf, "Kann Funktion '%s' nicht finden.\n", ftrname);  
            LOG(buf);
            exit(1);
        }
	
	
	// !!!!
	
        err = DLL_LB_GETXML_CONFIG_INSTANCE(&xml_I, this, __FILE__, __LINE__);
        // Debug helper
        xml_I.setLine(__LINE__);
        xml_I.setFile(__FILE__);


        if (xml_I == NULL) {
            LOG("Konnte XML Konfigurationsinstanz nicht bekommen.\n");
            exit(1);
        }
/*...sdoc:8:*/
        /**
         * Because of UNKNOWN_AUTO_PTR, here I must ensure, having one reference more than
         * it is returned by the functor. Increase it by a dummy call.
         *
         * The functor *MUST* call queryInterface it self. Using the macro, it should.
         */
        
        /**
         * The prior functor caused a object lock due to missing manager.
         * Because the functor is not designed to pass this manager, it's
         * internal use of queryInterface() locks the object.
         *
         * The object can be used, but there is no possibility to query
         * other interfaces (eg. do refcounting).
         *
         * Later, if the object will be deleted, it generates an error
         * due to it's locking.
         *
         * The setModuleManager() function resets this locking state and
         * corrects the values in module manager.
         */ 
/*...e*/

	UAP(lb_I_XMLConfig, _inst, __FILE__, __LINE__)

        QI(xml_I, lb_I_XMLConfig, _inst, __FILE__, __LINE__) 
        
        _inst++;
        *inst = *&_inst;
        
        /**
         * Set a flag, that say's system is up.
         */
        
        system_up = 1;
        
        if (*inst == NULL) { 
        	LOG("Error: queryInterface() does not return a pointer!")
        }
}
/*...e*/


/*...sdebug helper:0:*/
/*...schar\42\ LB_STDCALL lbModule\58\\58\getCreationLoc\40\char\42\ addr\41\:0:*/
char* LB_STDCALL lbModule::getCreationLoc(char* addr) {
#ifdef IR_USAGE
	if (IR != NULL) {
		return IR->getCreationLoc(addr);
	} else {
		LOG("Error: Call sequence error!");
		return "Interface repository not initialized";
	}
#endif
#ifndef IR_USAGE
	return "IR is deactivated!";
#endif
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\printReferences\40\char\42\ addr\41\:0:*/
void LB_STDCALL lbModule::printReferences(char* addr) {
	if (IR != NULL) {
	#ifdef VERBOSE
		IR->printReferences(addr);
	#endif
	}
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\notify_create\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbModule::notify_create(lb_I_Unknown* that, char* implName, char* file, int line) {
#ifdef IR_USAGE
        char buf[1000] = "";
        char addr[20] = "";
        sprintf(addr, "%p", (void*) that);
        
        if (IR == NULL) {
        	IR = new InstanceRepository(this);
        }
        /**
         * Do not register lbInstance's itself, because they are used registering
         * other instances.
         */
        if (strcmp("lbInstance", implName) != 0) {
        	IR->createInstance(addr, implName, file, line);
        }
#ifdef VERBOSE
        LOG("lbModule::notify_create() called")
#endif
#endif
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\notify_add\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbModule::notify_add(lb_I_Unknown* that, char* implName, char* file, int line) {
#ifdef IR_USAGE
        char buf[1000] = "";
        char addr[20] = "";
        sprintf(addr, "%p", (void*) that);

	if (IR == NULL) {
		char buf[1000] = "";
		sprintf(buf, "Error: Initial lbModule::notify_create() was not done for %s in %s at %d!", implName, file, line);
		LOG(buf)
		return;
	}
	IR->addReference(addr, implName, file, line);
#endif
}
/*...e*/
/*...svoid LB_STDCALL lbModule\58\\58\notify_release\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
void LB_STDCALL lbModule::notify_release(lb_I_Unknown* that, char* implName, char* file, int line) {
	/**
	 * A buffer with to few bytes may result in crashes. Because I do not make strlen checks,
	 * I must set the buffer to 
	 */
#ifdef IR_USAGE
        char addr[20] = "";

        sprintf(addr, "%p", (void*) that);


	if (that->getRefCount() == 0) {
		//DebugBreak();
		IR->delReference(addr, implName, file, line);
	} else {
	 	IR->delReference(addr, implName, file, line);       
	}
#endif
}
/*...e*/
/*...sint  LB_STDCALL lbModule\58\\58\can_delete\40\lb_I_Unknown\42\ that\44\ char\42\ implName\44\ char\42\ file\44\ int line\41\:0:*/
int  LB_STDCALL lbModule::can_delete(lb_I_Unknown* that, char* implName, char* file, int line) {
#ifdef IR_USAGE

#endif
        return 1;
}
/*...e*/
/*...e*/

/*...slbErrCodes lbModule\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbModule::setData(lb_I_Unknown* uk) {
        LOG("lbModule::setData(...) not implemented yet");
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbModule\58\\58\initialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbModule::initialize() {
	if (initializing == 1) LOG("Warning: Initialize while initializing (loop)")

	initializing = 1;

        if (moduleList != NULL) {
                LOG("Warning: lbModule::initialize() called more than once!");
                if (((unsigned long) xml_Instance.getPtr()) == 21) {
                	LOG("Leave xml_Instance pointer undefined !!!")
                }
                return ERR_NONE;
        }
        
        if (xml_Instance == NULL) {
                getXMLConfigObject(&xml_Instance);
                if (xml_Instance == NULL) {
                	LOG("Error: Functor has not returned a pointer!");
                	exit(1);
                }
	}

        lbModuleContainer* MList = new lbModuleContainer();
               
        MList->setModuleManager(this, __FILE__, __LINE__);
        
        MList->queryInterface("lb_I_Container", (void**) &moduleList, __FILE__, __LINE__);

	if (moduleList == NULL) {
		LOG("Error: moduleList must now be initialized!")
	}
#ifdef IR_USAGE
	IR->loadContainer(this);
#endif

	initializing = 0;

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL uninitialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbModule::uninitialize() {
        if (xml_Instance != NULL) {
        #ifndef USE_UAP
                RELEASE(xml_Instance);
                xml_Instance = NULL;
        #endif
        }
        if (moduleList != NULL) {
        #ifndef USE_UAP
                RELEASE(moduleList);
                moduleList = NULL;
        #endif
        }
        return ERR_NONE;
}
/*...e*/
// Helpers to abstract XML structure
/*...slbModule\58\\58\findFunctorNode\40\\46\\46\\46\\41\:0:*/
/**
 * Creates a view of needed data in a lb_I_ConfigObject.
 * The node then contains only one subtree for a functor.
 * 
 * Input:       A list of functor nodes in a view of a lb_I_ConfigObject
 *              
 *              The request itself
 *
 * Output:      Only one node from the list in a new view
 */
lb_I_ConfigObject* LB_STDCALL lbModule::findFunctorNode(lb_I_ConfigObject** _node, const char* request) {
        UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
        lb_I_ConfigObject* node = *_node;
        
        temp_node.setDelete(0);


        lbErrCodes err = ERR_NONE;

        /**
         * This gets a reference for me. Autodeleted, if scope is leaved.
         */
        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
                /**
                 * This is the functor node !! It has no attributes. All parents also contains
                 * the 'FunctionName' node, where the search criteria is stored. So the following
                 * must be done here to check if this node is the one be searched:
                 *
                 * Go up one node (in the tree), get all 'FunctionName' nodes by calling
                 * temp_node->getParentNode(). As the given node itself is a view of the DOM document,
                 * a question must be issued here:
                 *
                 * Has my implementation for this view any parents?
                 */
                 
                if (temp_node == NULL) {
                        LOG("temp_node is NULL!");
                        getch();
                } 
                if ((strcmp(temp_node->getName(), "Functor")) == 0) {
                        /**
                         * If I get a return value. It is a new reference.
                         * If I get a value by reference. It is a new reference.
                         *
                         * If I return a pointer from any interface reference,
                         * I *MUST* add a reference.
                         */
                        temp_node++;
                        return *&temp_node;
                }
                
        } else LOG("Get first child failed");

        while ((err = node->getNextChildren(&temp_node)) == ERR_NONE) {
                if ((strcmp(temp_node->getName(), "Functor")) == 0) {
                        temp_node++;
                        return *&temp_node;
                }
        }
        
        if (err == ERR_CONFIG_NO_MORE_CHILDS) {
                LOG("No more childs found");
        }

        #ifdef USE_UAP
        if (temp_node != NULL) RELEASE(temp_node);
        #endif
        
        LOG("Returning a NULL value");
        getch();        
        return NULL;
}
/*...e*/
/*...slbModule\58\\58\findFunctorModule\40\\46\\46\\46\\41\:0:*/
char* LB_STDCALL lbModule::findFunctorModule(lb_I_ConfigObject** _node) {
        lbErrCodes err = ERR_NONE;
        lb_I_ConfigObject* node = *_node;

        char buf[100] = "";
        
        if (node == NULL) {
                LOG("NULL pointer detected!");
                return "NULL";
        }
        
        if (strcmp (node->getName(), "Module") == 0) {
                { 
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                temp_node.setLine(__LINE__);
                temp_node.setFile(__FILE__);
                temp_node.setDelete(0);
                        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
/*...swork on temp_node:32:*/
                        if ((strcmp(temp_node->getName(), "ModuleName")) == 0) {
                                char* value = NULL;
                                err = temp_node->getAttributeValue("Name", value);
                                
                                if (err != ERR_NONE) {
                                        LOG("Error while getting attribute value");
                                        LOG(value);
                                        return "NULL";
                                } else {
                                        return value;
                                }
                        }               
/*...e*/
                        }
                }

                do {
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                temp_node.setLine(__LINE__);
                temp_node.setFile(__FILE__);
                temp_node.setDelete(0);
                        err = node->getNextChildren(&temp_node);
/*...swork on temp_node:24:*/
                        if ((strcmp(temp_node->getName(), "ModuleName")) == 0) {
                                char* value = NULL;

                                err = temp_node->getAttributeValue("Name", value);
                                
                                if (err != ERR_NONE) {
                                        LOG("Error while getting attribute value");
                                        return "NULL";
                                } else {
                                        return value;
                                }
                        }
/*...e*/
                } while (err == ERR_NONE);
        }
        else {
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                temp_node.setLine(__LINE__);
                temp_node.setFile(__FILE__);
                
                err = node->getParent(&temp_node);

                if (err == ERR_NONE) {
                        char* result = findFunctorModule(&temp_node);
                        
                        return result;
                }
                
        }

        return "NULL";
}
/*...e*/
/*...slbModule\58\\58\findFunctorName\40\\46\\46\\46\\41\:0:*/
char* LB_STDCALL lbModule::findFunctorName(lb_I_ConfigObject** ___node) {
        /**
         * Go up one level and get the children 'FunctionName'
         */
         
        UAP(lb_I_ConfigObject, _node, __FILE__, __LINE__)
        _node.setLine(__LINE__);
        _node.setFile(__FILE__);
        _node.setDelete(0);
        
        UAP(lb_I_ConfigObject, __node, __FILE__, __LINE__)
	__node.setLine(__LINE__);
	__node.setFile(__FILE__);
        __node.setDelete(0);
        
        lbErrCodes err = ERR_NONE;
        lb_I_ConfigObject* node = *___node;
        char buf[100] = "";
        
        /**
         * Warning!
         * 
         * This is hard coded moving in a tree of a xml document.
         */
        
        if ((err = node->getParent(&_node)) != ERR_NONE) {
                LOG("Some errors have ocured while getting a parent node!");
        } 
        
        if ((err = _node->getParent(&__node)) != ERR_NONE) {
                LOG("Some errors have ocured while getting a parent node!");
        }
        
        if (_node != NULL) {
                int first = 1;

                
                while (err == ERR_NONE) {
                        UAP(lb_I_ConfigObject, child, __FILE__, __LINE__)
                        child.setFile(__FILE__);
                        child.setLine(__LINE__);
                        child.setDelete(0);
                        
                        if (first == 1) {
                                err = __node->getFirstChildren(&child);
                                
                                if (err != ERR_NONE) {
                                        LOG("Error. Children expected");
                                        return NULL;
                                }
                                first = 0;
                        } else err = __node->getNextChildren(&child);
                        
                        /**
                         * Check that node...
                         */
                         
                        if (err != ERR_NONE) break; 
                 
                        if (strcmp(child->getName(), "FunctionName") == 0) {
                                /**
                                 * Have the node. Here I must get an attribute...
                                 */
                                 
                                char* value = NULL; 
                                err = child->getAttributeValue("Name", value); 
                                
                                if (err != ERR_NONE) {
                                        LOG("Error while getting attribute value");
                                        return NULL;
                                } else {
                                #ifdef VERBOSE
                                        cout << "Found function name '" << value << "'" << endl;
                                        getch();
                                #endif
                                        return value;
                                }
                        }
                }
        } else {
                LOG("A parent node was not found!?");
        }
        
        char *result = new char[100];
        result[0] = 0;
        return result;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getDefaultImpl\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\\42\ node\44\ char\42\\38\ implTor\44\ char\42\\38\ module\41\:0:*/
lbErrCodes LB_STDCALL lbModule::getDefaultImpl(char* interfacename, lb_I_ConfigObject** node, char*& implTor, char*& module) {
        lbErrCodes err = ERR_NONE;
        int count = 0;
        UAP(lb_I_ConfigObject, _node, __FILE__, __LINE__)
        _node = *node;
        _node++; // UAP must check the pointer here too

        implTor = new char[100];
        module = new char[100];

{
        UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
        
        /**
         * Use _node instead of the interface pointer. Later UAP will be able to check
         * if the interface pointer is valid. (Inside the -> operator)
         */
        
/*...sget first children:8:*/
        if ((err = _node->getFirstChildren(&temp_node)) == ERR_NONE) {
                if (temp_node == NULL) {
                        LOG("temp_node is NULL!");
                        getch();
                } 

                if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
                        lb_I_Unknown* uk = NULL;
                        char* attr = NULL;
                        
                        temp_node->getAttributeValue("Interface", attr);

                        if (strcmp(interfacename, attr) == 0) {
                                temp_node->getAttributeValue("Module", module);
                                temp_node->getAttributeValue("Functor", implTor);
                                temp_node->deleteValue(attr);
                                return ERR_NONE;
                        }
                        
                        temp_node->deleteValue(attr);
                        
                }
                
        } else LOG("Get first child failed");
/*...e*/
}

/*...sget next children:0:*/
        err = ERR_NONE;
        while (err == ERR_NONE) {
                UAP(lb_I_ConfigObject, temp_node, __FILE__, __LINE__)
                
                err = _node->getNextChildren(&temp_node);
                
                if (temp_node == NULL) {
                        LOG("temp_node is NULL!");
                        getch();
                        continue;
                } 
                
                if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
                        lb_I_Unknown* uk = NULL;
                        char* attr = NULL;
                        
                        temp_node->getAttributeValue("Interface", attr);
                        
                        if (strcmp(interfacename, attr) == 0) {
                                
                                temp_node->getAttributeValue("Module", module);
                                temp_node->getAttributeValue("Functor", implTor);
                                temp_node->deleteValue(attr);
                                
                                return ERR_NONE;
                        }
                        temp_node->deleteValue(attr);
                }
        }

/*...e*/

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getFunctors\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\ node\44\ lb_I_Unknown\42\\38\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbModule::getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
/*...sbla:0:*/
#ifdef bla
        lbModuleContainer* functors = new lbModuleContainer();

        UAP(lb_I_ConfigObject, temp_node)

        lbErrCodes err = ERR_NONE;
        int count = 0;

        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
                lb_I_Attribute* attribute;
                
                if (temp_node == NULL) {
                        LOG("temp_node is NULL!");
                        getch();
                } 
                
                if ((strcmp(temp_node->getName(), "InterfaceName")) == 0) {
                        //return temp_node;
                        lb_I_Unknown* uk = NULL;
                        
                        if (temp_node->queryInterface("lb_I_Unknown", (void**) &uk) != ERR_NONE) {
                                LOG("Error: Could not get unknown interface!");
                                exit(1);
                        }
                        
                        if (uk == NULL) {
                                LOG("Error: Don't expect a NULL pointer here!");
                                exit(1);
                        }
                        
                        char* functor = NULL;
                        char* module = NULL;
                        
                        if ((err == getDefaultImpl("lb_I_Integer", node, functor, module)) != ERR_NONE) {
                                LOG("Oops!");
                        }
                        
                        
                        
                        //lbKey* key = new lbKey(++count);
                        
                        //functors->insert(uk, key);
                }
                
        } else LOG("Get first child failed");

        while ((err = node->getNextChildren(temp_node)) == ERR_NONE) {
                if ((strcmp(temp_node->getName(), "InterfaceName")) == 0) {
                        //return temp_node;

                        lb_I_Unknown* uk = NULL;
                        
                        if (temp_node->queryInterface("lb_I_Unknown", (void**) &uk) != ERR_NONE) {
                                LOG("Error: Could not get unknown interface!");
                                exit(1);
                        }
                        
                        if (uk == NULL) {
                                LOG("Error: Don't expect a NULL pointer here!");
                                exit(1);
                        }
                        
                        //lbKey* key = new lbKey(++count);
                        
                        //functors->insert(uk, key);
                }
        }
        
        if (err == ERR_CONFIG_NO_MORE_CHILDS) {
                LOG("No more childs found");
        }

        if (temp_node != NULL) RELEASE(temp_node);
#endif
/*...e*/
        LOG("lbModule::getFunctors(...) not implemented");
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\makeInstance\40\char\42\ functor\44\ char\42\ module\44\ lb_I_Unknown\42\\42\ instance\41\:0:*/
lbErrCodes LB_STDCALL lbModule::makeInstance(char* functor, char* module, lb_I_Unknown** instance) {
char msg[1000] = "";
lbErrCodes err = ERR_NONE;
                        /**
                         * ModuleHandle is the result for this loaded module.
                         */
         		HINSTANCE h = getModuleHandle();
                        if ((err = lbLoadModule(module, h)) != ERR_NONE) {
                                // report error if still loaded
                                LOG("Error: Could not load the module")
                                
                                // return error if loading is impossible
                        }
                        
                        setModuleHandle(h);
                        
                        if (getModuleHandle() == 0) LOG("Error: Module could not be loaded");

                        if ((err = lbGetFunctionPtr(functor, getModuleHandle(), (void**) &DLL_LB_GET_UNKNOWN_INSTANCE)) != ERR_NONE) {
                                LOG("Error while loading a functionpointer!");
                        } else {
                                err = DLL_LB_GET_UNKNOWN_INSTANCE(instance, this, __FILE__, __LINE__);

                                if (err != ERR_NONE) 
                                {
                                	LOG("Could not get the instance!");
                                }
                                if ((*instance) == NULL) LOG("Something goes wrong while calling functor");
                        }

        return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbModule::getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
        return ERR_NONE;
}
/*...e*/

/*...sclass lbNamedValue:0:*/
class lbNamedValue :    public lb_I_Unknown {
public:
        lbNamedValue() {
                name = strdup("");
        }
        
        virtual ~lbNamedValue() {
                delete[] name;
        }

        DECLARE_LB_UNKNOWN()

        lbErrCodes getName(char* & _name);
        lbErrCodes setName(const char* const _name);
        
        /**
         * This is a one value container. Objects in a container are copies of inserted
         * ones. This prevents manipulation of an object outside of the container.
         *
         * A modification must explicidly set into the container via the set function.
         */
        lbErrCodes setValue(lb_I_Unknown* _value);
        lbErrCodes getValue(lb_I_Unknown* & _value);
        
        char*         name;
        lb_I_Unknown* uk_value;
};
/*...e*/
/*...sclass lbElement:0:*/
class lbElement : public lb_I_Element {
private:

public:
    lbElement() { ref = STARTREF; next = NULL; data = NULL; key = NULL; }
    virtual ~lbElement();
        
    lbElement(const lb_I_Element &e) { ref = STARTREF; next = e.getNext(); }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

    int operator == (const lb_I_Element &a) const;

    int operator == (const lb_I_KeyBase &key) const;

};
/*...e*/

/*...simplementation of lbModuleContainer:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbModuleContainer)
        ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbModuleContainer::lbModuleContainer() {
    iteration = 0;
    ref = STARTREF;
    iterator = NULL;
    count = 0;
    container_data = NULL;
}

lbModuleContainer::~lbModuleContainer() {
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbModuleContainer)

lbErrCodes lbModuleContainer::setData(lb_I_Unknown* uk) {
        LOG("lbModuleContainer::setData(...) not implemented yet");
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...simplementation of lbElement:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)

lbErrCodes lbElement::setData(lb_I_Unknown* uk) {
        LOG("lbElement::setData(...) not implemented yet");
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...simplementation of lbNamedValue:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbNamedValue)
// No additionally interface, because it's not used externally yet.
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbNamedValue::setData(lb_I_Unknown* uk) {
        LOG("lbNamedValue::setData(...) not implemented yet");
        getch();
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbNamedValue\58\\58\setName\40\\41\:0:*/
lbErrCodes lbNamedValue::setName(const char* const _name) {
        name = strdup((_name == NULL) ? "" : _name);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\getName\40\\41\:0:*/
lbErrCodes lbNamedValue::getName(char* & _name) {
        _name = strdup(name);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\setValue\40\\41\:0:*/
lbErrCodes lbNamedValue::setValue(lb_I_Unknown* _value) {
        if (uk_value != NULL) RELEASE(uk_value);
        
        // clone() set's the ref counter to 1, so a release above deletes the object.
        uk_value = _value->clone(__FILE__, __LINE__);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\getValue\40\\41\:0:*/
lbErrCodes lbNamedValue::getValue(lb_I_Unknown* & _value) {
        _value = uk_value->clone(__FILE__, __LINE__);
        
        return ERR_NONE;
}
/*...e*/

lbNamedValue* namedValue = NULL;
//lb_I_Container* moduleList = NULL;

typedef struct instances_of_module {
        char* moduleName;
        int   count;
} instModule;



/*...sDocu for Module management:0:*/
/**
 * lbModule is a manager for creating instances of interfaces, regartless where
 * it came from. lbModule must be responsible for the following tasks:
 *
 * Knowing of loaded modules,
 * loading new modules,
 * releasing a module, if no more instances from there are in use.
 *
 *
 * So these functions may be declared for that issues:
 *
 * protected:
 * // Handle is managed internally
 * lbErrCodes lbModule::loadModule(const char* modulename);
 *
 * // Not the handle is needed. A module can only loaded once in a process.
 * lbErrCodes lbModule::unloadModule(const char* modulename);   
 *
 *
 * A general problem here is, that a bootstraping of some base instances must be
 * made. For the module management I need a container instance. For this problem,
 * It may be usefull to implement simple classes for that interfaces.
 *
 *
 *
 */
/*...e*/

/*...slbModule\58\\58\request\40\\46\\46\\46\\41\:0:*/
/**
 * The requestable interface simply return result of 'spoken' requests.
 * The 'spoken' request may be only one word or it may a sentence.
 *
 * A possible request may like this:
 *      get instance from interface '<parameter>'
 *
 * With this, a requestable object may be instructable by a simple script
 * language.
 */
lbErrCodes LB_STDCALL lbModule::request(const char* request, lb_I_Unknown** result) {
        lbErrCodes err = ERR_NONE;
        char buf[1000] = "";
        if (moduleList == NULL) {
                initialize();
        }
        char* functorName = NULL;
	buf[0] = 0;
        UAP(lb_I_ConfigObject, config, __FILE__, __LINE__)
        UAP(lb_I_ConfigObject, impl, __FILE__, __LINE__)
        config.setLine(__LINE__);
        config.setFile(__FILE__);

        /**
         * impl is not returned in any way, I think, so it is allowed to delete the object
         * at lost of focus.
         */
        
/*...sget my unknown interface:8:*/
        if (strcmp(request, "instance/XMLConfig") == 0) {
                //xml_Instance->hasConfigObject("Dat/object");
                //result = (lb_I_Unknown*) xml_Instance;
                
                CL_LOG("Query unknown interface of xml_Interface!");
                xml_Instance->queryInterface("lb_I_Unknown", (void**) result, __FILE__, __LINE__);
                
                return ERR_NONE;
        }
/*...e*/
        else {
/*...sget any interface:8:*/
/*...sdoc:8:*/
        /**
         * Here should be created an unknown object. The mapping of a real
         * instance is done in the xml file instead of if blocks.
         */
/*...e*/
                char* node = "#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor/InterfaceName";
                int count = 0;
                                        // request is a functor
/*...sdoc:8:*/
                /**
                 * Get the nodes that match the path in 'node'. It may simple to change this
                 * to get all 'InterfaceName' entries. It should work the same way.
                 *
                 * 1. It is better to let this as it is. In the new XML file, an interfacename
                 * is a chield of the functor. I must find the functor's that implements the
                 * requiered interface.
                 *
                 * findFunctorNode, implemented as now, has a bug: It returns every times the
                 * first element.
                 * It should be an iterator to get all the elements found by hasConfigobject.
                 * Leaving the current technique, enables the searchability for functors dirctly
                 * and also enables the search for interfaces.
                 *
                 * The only thing, that must not appear, is an interfacename is the same as a
                 * functor !
                 */
/*...e*/
		
                if (xml_Instance->hasConfigObject(node, count) == ERR_NONE) {
/*...svars:32:*/
                        char* moduleName = NULL;
                        lb_I_ConfigObject* implementations = NULL;
                        char* value = NULL;
/*...e*/
/*...sdoc:8:*/
                        /**
                         * Get the list of found objects as a list.
                         * The result is a view of notes in a max deep
                         * of one level.
                         */
/*...e*/
                        xml_Instance->getConfigObject(&config, node);
                        track_Object(*&config, "Test object given by xml_Instance->getConfigObject()");
/*...sVERBOSE:32:*/
                        #ifdef VERBOSE
                        printf("The config object has %d references\n", config->getRefCount());
			#endif
/*...e*/
/*...sdoc:8:*/
                        /**
                         * Check, which element implements the requested interface.
                         * If there are more than one for an interface, get the first.
                         * Later, get the default.
                         */
/*...e*/
                        // May be the same bug as in internal ...
                        // It was the self pointed parent member
                        // config++;
/*...sfind the needed node:32:*/
                        if ((err = config->getFirstChildren(&impl)) == ERR_NONE) {
                                impl.setLine(__LINE__);
                                impl.setFile(__FILE__);
                                err = impl->getAttributeValue("Name", value);

                                if (strcmp(value, request) == 0) {
                                        //impl is the needed object     
                                } else {
/*...ssuche weiter:72:*/
                                        int stop = 1;
                                        while (stop == 1) {
                                                RELEASE(impl);
                                                
                                                if ((err = config->getNextChildren(&impl)) != ERR_NONE) {
			                                impl.setLine(__LINE__);
                        			        impl.setFile(__FILE__);
                                                        stop = 0;
                                                        break;
                                                } else {
							impl.setLine(__LINE__);
							impl.setFile(__FILE__);
						}

                                                if (value != NULL) 
                                                {
                                                        impl->deleteValue(value);
                                                        value = NULL;
                                                }

                                                err = impl->getAttributeValue("Name", value);

                                                if (strcmp(value, request) == 0) {
                                                        stop = 0;
                                                }
                                        }
/*...e*/
                                }
                        }
/*...e*/


/*...sreturn error if value \61\ NULL:32:*/
                        if (value == NULL) {
                                CL_LOG("return ERR_MODULE_NO_INTERFACE");
                                return ERR_MODULE_NO_INTERFACE;
                        }
/*...e*/
/*...sreturn error \40\no implementation for that interface\41\:32:*/
                        if (strcmp(request, value) != 0) {
                                CL_LOG("Error: There is no implementation for wanted interface");
                                
                                if (value != NULL) {
                                        impl->deleteValue(value);
                                }
                                return ERR_MODULE_NO_INTERFACE;
                        }
/*...e*/
/*...sclean up \63\\63\\63\:32:*/
                        if (value != NULL) {
                                impl->deleteValue(value);
                        }
/*...e*/
/*...sfind up names:32:*/
                        moduleName = findFunctorModule(&impl);
                        functorName = findFunctorName(&impl);
/*...e*/
/*...sclean up \63\\63\\63\:32:*/
                        if (value != NULL) {
                                impl->deleteValue(value);
                        }
/*...e*/

                        makeInstance(functorName, moduleName, result);
/*...sLog error:32:*/
                        if ((*result) == NULL) {
                        	char buf[1000] = "";
                        	sprintf(buf, "Error: makeInstance has been failed for '%s', '%s', '%s'", request, functorName, moduleName);
                        	CL_LOG(buf)
                        }
/*...e*/
                        (*result)->setModuleManager(this, __FILE__, __LINE__);

                        notify_create(*result, (*result)->getClassName());
/*...sclean up:32:*/
                        if (moduleName != NULL) impl->deleteValue(moduleName);
//                        if (value != NULL) impl->deleteValue(value);
/*...e*/
                } else {
                        cout << "Something goes wrong!" << endl;
                        cout << "xml_Instance->hasConfigObject() returns <> ERR_NONE!" << endl;
                }
                
                
/*...e*/
        }
        if (functorName != NULL) impl->deleteValue(functorName);
        return ERR_NONE;
}
/*...e*/

IMPLEMENT_SINGLETON_FUNCTOR(getlb_ModuleInstance, lbModule)

/*...slbErrCodes lbModule\58\\58\load\40\char\42\ name\41\:0:*/
lbErrCodes lbModule::load(char* name) {
        UAP(lb_I_XMLConfig, xml_Instance, __FILE__, __LINE__)

        getXMLConfigObject(&xml_Instance);
        
        cout << "lbModule::load(char* name) called" << endl;

        if (xml_Instance != NULL) {
            if (xml_Instance->parse() != ERR_NONE) {
                LOG("Error while parsing XML document\n");
            }
        }
        
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getObjectInstance\40\const char\42\ name\44\ lb_I_Container\42\\38\ inst\41\:0:*/
lbErrCodes lbModule::getObjectInstance(const char* name, lb_I_Container*& inst) {
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance\40\lb_I_Unknown \42\ inst\41\:0:*/
lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst) {
        RELEASE(inst);
        return ERR_NONE;
}
/*...e*/

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";
        
        switch (reason) {
                case DLL_PROCESS_ATTACH:
                        if (situation) {
                                LOG("DLL statically loaded.\n");
                        }
                        else {
                                //LOG("DLL dynamically loaded.\n");
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        LOG("New thread starting.\n");
                        break;
                case DLL_PROCESS_DETACH:                        
                        if (situation)
                        {
                                LOG("DLL released by system.\n");
                        }
                        else
                        {
                                //LOG("DLL released by program.\n");
                        }
                        break;
                case DLL_THREAD_DETACH:
                        LOG("Thread terminating.\n");
                derault:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/
#endif
