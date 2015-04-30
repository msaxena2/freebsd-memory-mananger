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

#define OCCUPIED 1

#define UNOCCUPIED 0

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
	/* Simple rounding up in this case, can have more complicated operations as well */
	return ((size + GRAIN_SIZE - 1) / GRAIN_SIZE) * GRAIN_SIZE;
}

void split_setter(size_t adjusted_size, struct indicator_data* block_ptr_node, int occupied) {
	block_ptr_node->block_size = adjusted_size;
	block_ptr_node->occupied = occupied;
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
	void * void_block_ptr = block_ptr;
	size_t adjusted_size = find_fit_size(size);
	printf("requested adjusted size is %zu\n", adjusted_size);
	void * rear_ptr = void_block_ptr + sizeof(struct indicator_data) + block_ptr_node->block_size;
	printf("size from rear is %zu\n", ((struct indicator_data *) rear_ptr)->block_size);
	while (1) {
		if ((!block_ptr_node->occupied)
				&& (block_ptr_node->block_size >= adjusted_size)) {
			break;
		}
		/* move forward to the next suitable one */
		void_block_ptr = void_block_ptr + (2 * sizeof(struct indicator_data))
				+ (block_ptr_node->block_size);

		if ((void_block_ptr + sizeof(struct indicator_data))
				>= (block_ptr) + BLOCK_SIZE) {
			/* no suitable block in this node */
			return NULL;
		}
		block_ptr_node = (struct indicator_data *) void_block_ptr;
	}

	/* suitable block has been found */

	/* finding if splitting should happen */
	if ((block_ptr_node->block_size - (adjusted_size))
			< (2 * sizeof(struct indicator_data) + find_fit_size(1))) {
		return void_block_ptr + sizeof(struct indicator_data);
	}

	/* splitting can occur */
	int original_capacity = block_ptr_node->block_size;
	split_setter(adjusted_size, block_ptr_node, OCCUPIED);
	void_block_ptr = void_block_ptr + sizeof(struct indicator_data)
			+ adjusted_size;
	split_setter(adjusted_size, (struct indicator_data *) void_block_ptr, OCCUPIED);
	void_block_ptr = void_block_ptr + sizeof(struct indicator_data);
	size_t new_capacity = original_capacity - adjusted_size - (2 * sizeof(struct indicator_data));
	split_setter(new_capacity, (struct indicator_data *) void_block_ptr, UNOCCUPIED);
	void_block_ptr = void_block_ptr + sizeof(struct indicator_data)
			+ new_capacity;
	split_setter(new_capacity, (struct indicator_data *) void_block_ptr, UNOCCUPIED);
	return ((void *) (block_ptr_node + 1));
}
/*
 * Helper function to create a new node block for the linked list.
 */
void * create_block() {
	struct main_block_list * block_list_ptr = (struct main_block_list*) malloc(
			sizeof(struct main_block_list));
	block_list_ptr->block_ptr = malloc(
	BLOCK_SIZE + 2 * sizeof(struct indicator_data));
	void * data_ptr = (void *) block_list_ptr->block_ptr;
	struct indicator_data * indicator_ptr = (struct indicator_data *) data_ptr;
	indicator_ptr->block_size = BLOCK_SIZE;
	indicator_ptr->occupied = 0;
	data_ptr = data_ptr + sizeof(struct indicator_data) + BLOCK_SIZE;
	indicator_ptr = (struct indicator_data *) data_ptr;
	indicator_ptr->block_size = BLOCK_SIZE;
	indicator_ptr->occupied = 0;
	INIT_LIST_HEAD(&(block_list_ptr->node));
	return block_list_ptr;
}

void * compressed_alloc(size_t size) {
	/* case of first alloc */
	if (!block_list_ptr) {
		block_list_ptr = create_block();
	}
	/* First fit strategy for the blocks */
	struct list_head *pos;
	struct main_block_list * curr_node;

	/*traverse each block to find an empty block */
	list_for_each(pos, &(block_list_ptr->node))
	{
		curr_node = list_entry(pos, struct main_block_list, node);
		void * ret_ptr = first_fit_add(curr_node->block_ptr, size);
		/* successful addition happened at one of the blocks */
		if (ret_ptr) {
			return ret_ptr;
		}
	}
	/* create a new block, guaranteed to have enough space */
	struct main_block_list * new_block = create_block();
	list_add_tail(&(new_block->node), &(block_list_ptr->node));
	return first_fit_add(new_block->block_ptr, size);
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

