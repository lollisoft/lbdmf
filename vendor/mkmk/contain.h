// Container class library
// Luis Crespo, lcrespo@ergos.es, 4/97
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.3.4.1 $
 * $Name:  $
 * $Id: contain.h,v 1.3.4.1 2025/04/05 16:16:40 lothar Exp $
 *
 * $Log: contain.h,v $
 * Revision 1.3.4.1  2025/04/05 16:16:40  lothar
 * This file seems to clash with HEAD bransh when migrating to git.
 * So update it in the bransh to probably fix this. Why does the
 * migration fails here?
 *
 * Revision 1.3  2001/10/20 19:45:43  lothar
 * Added revision history
 *
 **************************************************************/

/*...e*/


#ifndef _containers_included
#define _containers_included



/*...sclass TDynArray:0:*/
class TDynArray {      // Dynamic array
  public:
    TDynArray(int iLimit, int iDelta, int iItemSize);
    ~TDynArray();
    void Set(int Index, void *Item);
    void Get(int Index, void *Item);
    void Insert(void *Item) { Set(Count++,Item); }
    void Delete(void *Item);
    void * operator [] (int Index) { return &Data[ItemSize*Index]; }
    int Count;
  protected:
    void SetLimit(int NewLimit);
    int Limit,Delta,ItemSize;
    char *Data;
};
/*...e*/
/*...sclass TCollection:0:*/
class TCollection {    // Dynamic array of pointers to objects
  private:
    TCollection() {}
  public:
    TCollection(int iLimit, int iDelta);
    ~TCollection();
    void Insert(void *pItem);
    void InsertAt(int Pos, void *pItem);
    void Delete(void *pItem);
    void DeleteAt(int Pos);
    int IndexOf(void *pItem);
    virtual void FreeItem(void */*pItem*/){}
    void *At(int Index) { return Data[Index]; }
    void * operator [] (int Index) { return At(Index); }
    int Count;
  protected:
    void SetLimit(int NewLimit);
    int Limit,Delta;
    void **Data;
};
/*...e*/
/*...sclass TSortedCollection:0:*/
class TSortedCollection:public TCollection {
  public:
    void Insert(void *pItem);
    int Search(void *pItem, int *Pos);
    virtual int Compare(void *pItem1, void *pItem2)=0;
};
/*...e*/

#endif
