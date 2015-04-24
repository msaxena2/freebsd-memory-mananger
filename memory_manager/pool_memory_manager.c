/*
 * pool_memory_manager.c
 *
 *  Created on: Apr 4, 2015
 *      Author: manasvi
 */

#include "pool_memory_manager.h"
#include <stdlib.h>
/* Block size is 8 MB */
#define BLOCK_SIZE 8000000

/* Smallest memory block size */
#define GRAIN_SIZE 8

/*
 * Struct for the dictionary containing the list of blocks
 */

struct main_block_list {
	/* pointer to the main block*/
	void * block_ptr;
	/* list node */
	struct list_head node;
};

/*
 * Struct to hold the size of the data, and indicate whether its occupied or not.
 */
struct indicator_data {
	size_t block_size;
	int occupied;
};

/*
 * List containing the block pointers
 */
struct main_block_list * block_list_ptr = NULL;

/* Given a size, finds the best size to allow for fit.
 * Might be needed later for more complex arithmatic.
 *
 */
int find_fit_size(size_t size) {
	return (size + (GRAIN_SIZE / 2)) / GRAIN_SIZE;
}

/*
 * Given a block, method follows first fit strategy to find the
 * first memory space which can accommodate the requested space.
 *
 * Implemented strategy follows implicit lists with bidirectional
 * coalescing.
 */
void * first_fit_add(void * block_ptr, size_t size) {
	struct indicator_data *block_ptr_node = (struct indicator_data *) block_ptr;


}

void * compressed_alloc(size_t size) {
	/* case of first alloc */
	if (!block_list_ptr) {
		block_list_ptr = (struct main_block_list *) malloc(
				sizeof(struct main_block_list));
		block_list_ptr->block_ptr = malloc(sizeof(BLOCK_SIZE));
		INIT_LIST_HEAD(&(block_list_ptr->node));
	}

	/* First fit strategy for the blocks */
	struct list_head * pos;
	struct main_block_list * curr_node;

	/*traverse each block to find an empty block */
	list_for_each(pos, &(block_list_ptr->node))
	{
		curr_node = list_entry(pos, struct main_block_list, node);
		void * ret_ptr = first_fit_add(curr_node, size);
		/* successful addition happened at one of the blocks */
		if (!ret_ptr) {
			return ret_ptr;
		}
	}
	return NULL;
}

void free(void * ptr) {
	/*
	 int *block_ptr_node = (int *)ptr;

	 int size_of_ptr_block = *block_ptr_node;
	 *block_ptr_node |= 0;
	 *(block_ptr_node + size_of_ptr_block) |= 0;

	 // Check left neighbor
	 if (((block_ptr_node - 1) & 1) == 0) { // TODO: Check left boundary
	 int *left_neigbor = block_ptr_node - *block_ptr_node;
	 *left_neigbor = (*left_neigbor + size_of_ptr_block);
	 *(left_neigbor + (*left_neigbor - 1)) = *left_neigbor;
	 block_ptr_node = left_neigbor;
	 }

	 // Check right neighbor
	 if (((block_ptr_node + *block_ptr_node) & 1) == 0) { // TODO: Check right boundary;
	 int *right_neighbor = block_ptr_node + *block_ptr_node;
	 *block_ptr_node = *block_ptr_node + *right_neighbor;
	 *(block_ptr_node + (*block_ptr_node -1)) = *block_ptr_node;
	 }
	 */
}

