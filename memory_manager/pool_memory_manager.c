/*
 * pool_memory_manager.c
 *
 *  Created on: Apr 4, 2015
 *      Author: manasvi
 */

#include "pool_memory_manager.h"

/*
 * Struct for the dictionary containing the list of blocks
 */

struct main_block_list {
	/* pointer to the main block*/
	void * block_ptr;
	/* list node */
	struct list_head * node;
};

void * compressed_alloc(size_t size)
{
	printf("%s \n", "alloc");
	return NULL;
}


void free(void * ptr)
{
	printf("%s \n", "free");
}

