//
// Created by Manasvi Saxena on 3/24/15.
//

#include <stdlib.h>
#include <stdio.h>
#include "test_large_allocations.h"
#define BIGNUM 1000000000

int main()
{
    int * big_array = malloc(BIGNUM * sizeof(int));

    int i = 0;
    for(i = 0; i < BIGNUM; ++i)
    {
        big_array[i] = 1;
    }

    printf("Completed \n");
}
