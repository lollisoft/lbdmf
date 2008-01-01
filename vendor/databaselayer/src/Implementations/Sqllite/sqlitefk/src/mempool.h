#ifndef MEMPOOL_H
#define MEMPOOL_H

typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

typedef struct mem_pool_zone
{
    char *pos;
    char *maxpos;
    struct mem_pool_zone *next;
    struct mem_pool_zone *prev;
    char data[1];
} MemPoolZone;

typedef struct
{
    MemPoolZone *firstzone;
    MemPoolZone *currentzone;
    size_t zonesize;
    //Mutex mutex;
} MemPool;

bool MemPoolCreate(MemPool *pool, size_t zonesize);
void MemPoolDestroy(MemPool *pool);

void *MemPoolAlloc(MemPool *pool, size_t size);
char *MemPoolStrdup(MemPool *pool, char *s);

#define pstrdup(p,s) MemPoolStrdup(p, s);

#endif
