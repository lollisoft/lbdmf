// skiplist.cpp
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: skiplist.cpp,v 1.1 2002/03/03 08:33:57 lolli Exp $
 *
 * $Log: skiplist.cpp,v $
 * Revision 1.1  2002/03/03 08:33:57  lolli
 * Initial non interface based skiplist
 *
 **************************************************************/
/*...e*/

#ifdef bla
/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/
#endif

#include <iostream.h>
#include <stdlib.h>

#ifdef bla
#ifdef __cplusplus
extern "C" {
#endif

IMPLEMENT_FUNCTOR(instanceOfSkipListContainer, SkipList)

#ifdef __cplusplus
}
#endif
#endif

typedef int Elem;

#define MAXLEVEL 9

/*...sclass SkipNode:0:*/
class SkipNode {
  public:
    int myLevel;
    Elem value;
    SkipNode** forward;
    SkipNode() {
    	myLevel = MAXLEVEL;
    	value = -1;
    	forward = new SkipNode* [myLevel+1];
    	for (int i=0; i<=myLevel; i++)
    	    forward[i] = NULL;
    }
    
    SkipNode(Elem r, int level) {
        myLevel = level;
        value = r;
        forward = new SkipNode* [level+1];
        for (int i=0; i<=level; i++)
            forward[i] = NULL;
  }
  ~SkipNode() { 
      delete [] forward; 
  }
};
/*...e*/
/*...sclass SkipList:0:*/
class SkipList {
  private:
      SkipNode* head;
      int level;

      void AdjustHead(int& level) {level = MAXLEVEL;}
  public:
      SkipList() {
          head = new SkipNode(-1, MAXLEVEL);
          level = MAXLEVEL;
      }
      Elem search(int);
      void insert(Elem);
      void remove(Elem);
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
};
/*...e*/


#ifdef bla
/*...sMacrobased container:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbContainer)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbContainer::lbContainer() {
    iteration = 0;
    ref = STARTREF;
    iterator = NULL;
    count = 0;
    container_data = NULL;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    CL_LOG("Set manager to NULL must be done automatically!");
#endif
/*...e*/
    manager = NULL;
}

lbContainer::~lbContainer() {
}

lbErrCodes LB_STDCALL lbContainer::setData(lb_I_Unknown* uk) {
	CL_LOG("lbContainer::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbContainer)
/*...e*/
#endif




/*...srandomLevel\40\void\41\:0:*/
int randomLevel(void) { // Pick a level on exponential distribution
  int level;
  for (level=0; (rand()%2) == 0; level++); // Do nothing
  return level;
}
/*...e*/
/*...sSkipList\58\\58\search\40\int searchKey\41\:0:*/
Elem SkipList::search(int searchKey) { // Skiplist Search
  SkipNode *x = head;                  // Dummy header node
  for (int i=level; i>=0; i--)
    while ((x->forward[i] != NULL) &&
           (x->forward[i]->value < searchKey))
      x = x->forward[i];
  x = x->forward[0];  // Move to actual record, if it exists
  if ((x != NULL) && (x->value == searchKey)) return x->value;
  else return -1;
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
    while((x->forward[i] != NULL) &&
          (x->forward[i]->value < newValue))
      x = x->forward[i];
    update[i] = x;              // Keep track of end at level i
  }
  
  x = new SkipNode(newValue, newLevel); // Create new node
  
  for (i=0; i<=newLevel; i++) { // Splice into list
    x->forward[i] = update[i]->forward[i]; // Who x points to
    update[i]->forward[i] = x;             // Who y points to
  }
}
/*...e*/
/*...sSkipList\58\\58\remove\40\int searchKey\41\:0:*/
void SkipList::remove(Elem searchKey) {
    // update holds pointers to next elements of each level
    SkipNode** update = NULL;    // Update tracks end of each level
  
    update = new SkipNode* [level+1]; 
    
    SkipNode *x = head;                  // Dummy header node
    SkipNode *found = NULL;
    
    for (int i=level; i>=0; i--) {

      while ((x->forward[i] != NULL) && (x->forward[i]->value < searchKey)) {
        x = x->forward[i];
      }
        
      update[i] = x;
    }

    x = x->forward[0];  // Move to actual record, if it exists
    
    if ((x != NULL) && (x->value == searchKey)) found = x;
    else return;

    // element found, so rebuild list without node:
    if (found->value == searchKey) {
      for (int i=0; i<=level; i++) {
        if (update[i]->forward[i] == found) {
          update[i]->forward[i] = found->forward[i];
        }
      }
      
      // element can be freed now (would happen automatically):
      delete found;
      
      // maybe we have to downcorrect the level of the list: 
      while (level>0  &&  head->forward[level] != NULL && head->forward[level]->value==-1) {
        level--;
      }
    }
  }


/*...e*/
