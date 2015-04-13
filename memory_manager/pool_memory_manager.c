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
 * List containing the block pointers
 */
struct main_block_list * block_list_ptr = NULL;


/*
 * Given a block, method follows first fit strategy to find the
 * first memory space which can accommodate the requested space.
 *
 * Implemented strategy follows implicit lists with bidirectional
 * coalescing.
 */
void * first_fit_add(void * block_ptr, size_t size) {
    int *block_ptr_node = (int *)block_ptr;
    int node_is_taken = (*block_ptr_node & 1) == 1;
    int node_is_not_big_enough = (*block_ptr_node - 2 < size);
    int block_is_not_full = (void*)block_ptr_node - block_ptr < BLOCK_SIZE;
    int found_node_for_alloc = block_is_not_full && (node_is_taken || node_is_not_big_enough);
    
    while (!found_node_for_alloc)) { // TODO: size-2 requirement should be relaxed. If the first requested size is 8MB, it should still be able to serve.
        block_ptr_node = block_ptr_node + (*block_ptr_node & -2);
        node_is_taken = (*block_ptr_node & 1);
        node_is_not_big_enough = (*block_ptr_node - 2 >= size);
        block_is_not_full = (void*)block_ptr_node - block_ptr < BLOCK_SIZE;
        found_node_for_alloc = block_is_not_full && (node_is_taken || node_is_not_big_enough);
    }

    if (!found_node_for_alloc) {
        if (!block_is_not_full) {
            printf("Block is full for block_ptr %p\n", block_ptr);
        }

        if (node_is_taken) {
            printf("All nodes are taken for block %p\n", block_ptr);
        }

        if (node_is_not_big_enough) {
            printf("Could not find a node that could fit size %i for block_ptr %p\n", size, block_ptr);
        }

        return NULL;
    }

    int new_size = ((size + 2) >> 1) << 1; // This creates a bit flag in the LSB. We use this to flag if the chunk is used
    int old_size = *block_ptr_node & -2;
    int offset_size = old_size - new_size;


    *block_ptr_node = new_size | 1;
    *(block_ptr_node + new_size - 1) = new_size | 1; // set bit for tail buffer

    int *block_ptr_node_neighbor = block_ptr_node + new_size;

    *block_ptr_node_neighbor = offset_size | 0;
    *(block_ptr_node_neighbor + offset_size) = offset_size | 0;


    //TODO: CHECK BOUNDARY CONDITIONS
    if (new_size < old_size) {
        *(block_ptr_node + new_size) = old_size - new_size;
    }

	return block_ptr_node;
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
    int *block_ptr_node = (int *)ptr;

    int size_of_ptr_block = *block_ptr_node;
    *block_ptr_node |= 0;
    *(block_ptr_node + size_of_ptr_block) |= 0;

    // Check left neighbor
    if ((block_ptr_node - 1) & 1 == 0) { // TODO: Check left boundary
        int *left_neigbor = block_ptr_node - *block_ptr_node;
        *left_neigbor = (*left_neigbor + size_of_ptr_block);
        *(left_neigbor + (*left_neigbor - 1)) = *left_neigbor;
        block_ptr_node = left_neigbor;
    }

    // Check right neighbor
    if ((block_ptr_node + *block_ptr_node) & 1 == 0) { // TODO: Check right boundary;
        int *right_neighbor = block_ptr_node + *block_ptr_node;
        *(right_neighbor + (*right_neighbor - 1)) = *block_ptr_node + *right_neighbor;// update tail buffer of right_neighbor
    }
}

