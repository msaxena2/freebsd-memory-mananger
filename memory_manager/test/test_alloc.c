/*
 * test_alloc.c
 *
 *  Created on: Apr 4, 2015
 *      Author: manasvi
 */

#include <stdio.h>
#include "../pool_memory_manager.h"

#define DUMMY_INT 151
#define DUMMY_ITERATIONS 1
#define DUMMY_INT_ARRAY_SIZE 500

int single_alloc_test() {
	printf("--Simple Single compressed Alloc Test\n--");
	int* a = compressed_alloc(sizeof(int));
	if (a == NULL) {
		printf("--Simple Single compressed Alloc Test Failed\n--");
		return (1);
	}
	*a = DUMMY_INT;
	if ((*a) != DUMMY_INT) {
		printf("--Simple Single compressed Alloc Test Failed\n--");
		return (1);
	}
	compressed_free(a);
	printf("--Simple Single compressed Alloc Test Passed\n--");
	return 0;
}

int multiple_simple_alloc_test() {
	printf("--Simple Multiple compressed Alloc Test--\n");
	int i;
	int* a;
	for (i = 0; i < DUMMY_ITERATIONS; ++i) {
		a = (int *)compressed_alloc(sizeof(int));
		if (a == NULL) {
			printf("--Simple Single compressed Alloc Test Failed as Null returned--\n");
			return (1);
		}
		*a = DUMMY_INT;

		if ((*a) != DUMMY_INT) {
			printf("--Simple Single compressed Alloc Test Failed--\n");
			return (1);
		}
	}
	printf("--Simple Multiple compressed Alloc Test Passed--\n");
	return 0;
}

int single_big_alloc_test() {
	printf("-- Big Alloc Call Test --");
	int i;
	int * arr = malloc(DUMMY_INT_ARRAY_SIZE * sizeof(int));
	if (arr == NULL) {
		printf("--Big compressed Alloc Test Failed\n--");
		return (1);
	}
	for (i = 0; i < DUMMY_INT_ARRAY_SIZE; ++i) {
		arr[i] = DUMMY_INT;
	}
	for (i = 0; i < DUMMY_INT_ARRAY_SIZE; ++i) {
		if (arr[i] != DUMMY_INT) {
			printf("--Big compressed Alloc Test Failed\n--");
			return (1);
		}
	}
	compressed_free(arr);
	printf("--Big Alloc Test Passed\n--");
	return 0;

}

int multiple_big_allocs_test() {
	printf("-- Multiple Big Alloc Call Test --");
	int j;
	for (j = 0; j < DUMMY_ITERATIONS; ++j) {
		int i;
		int * arr = malloc(DUMMY_INT_ARRAY_SIZE * sizeof(int));
		if (arr == NULL) {
			printf("--Multiple Big compressed Allocs Test Failed\n--");
			return (1);
		}
		for (i = 0; i < DUMMY_INT_ARRAY_SIZE; ++i) {
			arr[i] = DUMMY_INT;
		}
		for (i = 0; i < DUMMY_INT_ARRAY_SIZE; ++i) {
			if (arr[i] != DUMMY_INT) {
				printf("--Multiple Big compressed Allocs Test Failed\n--");
				return (1);
			}
		}
		compressed_free(arr);
	}
	printf("--Multiple Big Alloc Test Passed\n--");
	return 0;
}

int main() {
	printf("Pool Memory Manager Tester\n");

	/* ------ SINGLE COMPRESSED ALLOC CALL TEST ---------- */
	int status = single_alloc_test();
	if (status) {
		printf("Exiting testing\n");
		return 0;
	}

	/* ----- MULTIPLE COMPRESSED ALLOC CALLS TEST -------- */
	int status = multiple_simple_alloc_test();
	if (status) {
		printf("Exiting testing\n");
		return 0;
	}

	/* ---- SINGLE BIG ALLOC CALL TEST ----*/
	int status = single_big_alloc_test();
	if (status) {
		printf("Exiting testing\n");
		return 0;
	}

	/* ---- MULTIPLE BIG ALLOC CALL TEST ----*/
	int status = multiple_big_alloc_test();
	if (status) {
		printf("Exiting testing\n");
		return 0;
	}

	/* --- ADD MORE TESTS HERE --- */
	//@Todo: Incremental memory pressure increase, and big memory tests to be added
}
