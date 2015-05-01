##Memory Pool Manager for the Compressed Pager

Pool Memory Manager for the Compressed Memory Allocation Pager. 


### Directory Structure
```
memory_manager/
|-- README.md
|-- makefile
|-- pool_memory_manager.c
|-- pool_memory_manager.h
|-- resources
|   |-- list.h
|-- test
|   |-- test_alloc.c

```

### Running/Testing

The tests exists  under the test folder. The file inside has clear instructions about the procedure that must be followed to add tests.

The makefile has all warnings enabled, and also makes the compiler treat warnings as errors. This has been done on purpose. Code must compile without warnings. 

Call `make` to make the executable called `tester`. Use this to run the tests.

### Implementation Details

We use Implicit Lists with Bi-Diretional coalescing for effective memory management. Placement policy used is First Fit. For more information, see UIUC CS 241 [slides](https://courses.engr.illinois.edu/cs241/sp2012/lectures/09-malloc.pdf). Future work will focus on defragmentation of data for better space utilization, and experimenting with other placement policies like Best-Fit. 

