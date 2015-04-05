/*
 * pool_memory_manager.h
 *
 *  Created on: Apr 4, 2015
 *      Author: manasvi
 */

#include <stdio.h>
#include "resources/list.h"

#ifndef POOL_MEMORY_MANAGER_H_
#define POOL_MEMORY_MANAGER_H_


/*
 * Function to return a pointer to the requested size of memory
 */
void * compressed_alloc(size_t size);


/*
 * Function to free memory at the given pointer
 */
void compressed_free(void * ptr);

#endif /* POOL_MEMORY_MANAGER_H_ */
