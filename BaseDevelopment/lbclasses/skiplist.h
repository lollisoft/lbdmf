#ifndef LB_SKIPLIST
#define LB_SKIPLIST

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
    	data = e.getObject();
    	key = e.getKey();
	manager = NULL;
    }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbSkipListElement)
#ifndef UNIX
    lb_I_Unknown* getObject() const;
#endif
};
/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FUNCTOR(instanceOfSkipList)

#ifdef __cplusplus
}
#endif

#endif
