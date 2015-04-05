/*
 * pool_memory_manager.c
 *
 *  Created on: Apr 4, 2015
 *      Author: manasvi
 */

#include "pool_memory_manager.h"
/* Block size is 8 MB */
#define BLOCK_SIZE 8000000

/*
 * Struct for the dictionary containing the list of blocks
 */

typedef struct main_block_list {
	/* pointer to the main block*/
	void * block_ptr;
	/* list node */
	struct list_head node;
};

/*
 * List containing the block pointers
 */
struct main_block_list * block_list_ptr = NULL;

void * compressed_alloc(size_t size) {
	/* case of first alloc */
	if (!block_list_ptr) {
		block_list_ptr = (struct main_block_list *) malloc(
				sizeof(struct main_block_list));
		block_list_ptr->block_ptr = malloc(sizeof(BLOCK_SIZE));
		INIT_LIST_HEAD(&block_list_ptr->node);
	}

}

void free(void * ptr) {
	printf("%s \n", "free");
}

