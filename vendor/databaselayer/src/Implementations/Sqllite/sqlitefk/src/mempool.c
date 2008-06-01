#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mempool.h"


static MemPoolZone *
MemPoolZoneAlloc (size_t zonesize)
{
	MemPoolZone *zone;

	zone = (MemPoolZone *) malloc(zonesize + sizeof(MemPoolZone));
	if (zone)
	{
		zone->pos = zone->data;
		zone->maxpos = zone->pos + zonesize;
		zone->next = zone->prev = NULL;
	}

	return zone;
}


bool
MemPoolCreate (MemPool *pool, size_t zonesize)
{
	pool->zonesize = zonesize;

	//if (MutexCreate(&pool->mutex))
	//{
		pool->firstzone = pool->currentzone = MemPoolZoneAlloc(zonesize);
		if (!(pool->firstzone))
		{
			//MutexFree(&pool->mutex);
			return FALSE;
		}
	//}
	
	return TRUE;
}


void
MemPoolDestroy (MemPool *pool)
{
	MemPoolZone *zone;
    MemPoolZone *next;

	zone = pool->firstzone;
	while (zone)
	{
		next = zone->next;
		free(zone);
		zone = next;
	}
}


void *
MemPoolAlloc (MemPool *pool, size_t size)
{
	MemPoolZone *zone;
    MemPoolZone *next;
	void *ptr;
	size_t zonesize;

	if (size == 0)
		return NULL;

	//if (!MutexLock(&pool->mutex))
	//	return NULL;

	zone = pool->currentzone;

    /* we still have room in the current zone */
	if (zone->pos + size < zone->maxpos)
	{
		ptr = zone->pos;
		zone->pos += size;
		//MutexUnlock(&pool->mutex);
		return ptr;
	}

    /* is the requested size larger
     * then the pool's preferred size?
     */
	if (size > pool->zonesize)
		zonesize = size;
	else
		zonesize = pool->zonesize;

    /* allocate a new zone */
	next = MemPoolZoneAlloc(zonesize); 
	if (next)
	{
		next->prev = zone;
		next->next = zone->next;
		zone->next = next;

        /* update the pool's currentzone */
		pool->currentzone = next; 

		ptr = next->data;
        /* update the zone position */
		next->pos = next->data + size;
	}
	else
    {
		ptr = NULL;
    }

	//MutexUnlock(&pool->mutex);
	return ptr;
}


char *
MemPoolStrdup (MemPool *pool, char *s)
{
	char *dst = NULL;

	if (s)
	{
		dst = (char*) MemPoolAlloc (pool, strlen(s) + 1);
		if (dst)
			strcpy(dst, s);
	}

	return dst;
}


void
MemPoolDump (MemPool *pool)
{
	MemPoolZone *zone;

	printf("first=[%p] current=[%p]", zone = pool->firstzone, pool->currentzone);
	while (zone)
	{
		printf("Zone [%p]: data=[%p] pos=[%p] max=[%p]", zone, zone->data,
														zone->pos, zone->maxpos);
		zone = zone->next;
	}
}
