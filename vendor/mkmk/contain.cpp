#include <stdlib.h>
#include <string.h>

#include "contain.h"

/*...sDymamic Array:0:*/
//------------------------- Dymamic Array -------------------------

TDynArray::TDynArray(int iLimit, int iDelta, int iItemSize)
{
  Limit=iLimit;
  Delta=iDelta;
  ItemSize=iItemSize;
  Data=(char*)malloc(Limit*ItemSize);
  Count=0;
}

TDynArray::~TDynArray()
{
  free(Data);
}

void TDynArray::SetLimit(int NewLimit)
{
  Limit=NewLimit+Delta-NewLimit%Delta;
  Data=(char*)realloc(Data,Limit*ItemSize);
}

void TDynArray::Set(int Index, void *Item)
{
  if (Index>=Limit) SetLimit(Index);
  if (Index>=Count) Count=Index+1;
  memcpy(&Data[ItemSize*Index],Item,ItemSize);
}

void TDynArray::Get(int Index, void *Item)
{
  memcpy(Item,&Data[ItemSize*Index],ItemSize);
}

void TDynArray::Delete(void *Item)
{
  char *p;
  int Size,Offset;

  Size=Count*ItemSize;
  p=(char*)Item;
  Offset=Data-p;
  if (Offset>=Size || Offset<0 || Offset%ItemSize) return;
  memmove(&Data[Offset],&Data[Offset+ItemSize],Size-Offset-ItemSize);
  Count--;
}
/*...e*/
/*...sCollection:0:*/
//------------------------- Collection -------------------------

TCollection::TCollection(int iLimit, int iDelta)
{
  Limit=iLimit;
  Delta=iDelta;
  Data=(void**)malloc(Limit*sizeof(void*));
  Count=0;
}

TCollection::~TCollection()
{
  for (int i=0; i<Count; i++) FreeItem(At(i));
  free(Data);
}

void TCollection::SetLimit(int NewLimit)
{
  int OldLimit;

  OldLimit=Limit;
  Limit=NewLimit+Delta-NewLimit%Delta;
  if (OldLimit!=Limit) Data=(void**)realloc(Data,Limit*sizeof(void*));
}

void TCollection::Insert(void *pItem)
{
  if (Count>=Limit) SetLimit(Count);
  Data[Count++]=pItem;
}

void TCollection::InsertAt(int Pos, void *pItem)
{
  if (Pos==Count) Insert(pItem);
  else if (Pos>Count) return;
  if (Count>=Limit) SetLimit(Count);
  memmove(&Data[Pos+1],&Data[Pos],(Count-Pos)*sizeof(void*));
  Data[Pos]=pItem;
  Count++;
}

int TCollection::IndexOf(void *pItem)
{
  for (int i=0; i<Count; i++)
    if (pItem==Data[i]) return i;
  return -1;
}

void TCollection::Delete(void *pItem)
{
  DeleteAt(IndexOf(pItem));
}

void TCollection::DeleteAt(int Pos)
{
  if (Pos<0 || Pos>=Count) return;
  FreeItem(At(Pos));
  if (Pos<Count-1)
    memmove(&Data[Pos],&Data[Pos+1],(Count-Pos-1)*sizeof(void*));
  Count--;
  SetLimit(Count);
}
/*...e*/
/*...sSorted collection:0:*/
//------------------------- Sorted collection -------------------------

void TSortedCollection::Insert(void *pItem)
{
  int Pos;

  if (!Search(pItem,&Pos)) InsertAt(Pos,pItem);
}

int TSortedCollection::Search(void *pItem, int *Pos)   // binary search
{
  int min,max,i,oldi,Comp;

  if (Count==0) { *Pos=0; return 1; }
  min=0;
  max=Count-1;
  i=-1;
  do {
    oldi=i;
    i=(min+max)/2;
    if (i!=oldi)
    {
      Comp=Compare(pItem,At(i));
      if (Comp<0) max=i;       // Item is smaller
      else if (Comp>0) min=i;  // Item is bigger
    }
  } while (Comp!=0 && i!=oldi);
  if (Comp<=0) *Pos=i;
  else *Pos=i+1;
  return Comp==0;
}
/*...e*/
