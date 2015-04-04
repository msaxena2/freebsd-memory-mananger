
# Makefile for CS/ECE438 MP3

EXE = tester

OBJS = test_alloc.o pool_memory_manager.o

COMPILER = gcc
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror  $(WARNINGS)
LINKER = g++

all : $(EXE) 

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) -o $(EXE)


test_alloc.o : test/test_alloc.c
	$(COMPILER) $(COMPILER_OPTS) test/test_alloc.c

pool_memory_manager.o : pool_memory_manager.c
	$(COMPILER) $(COMPILER_OPTS) pool_memory_manager.c	


clean :
	-rm -f *.o $(EXE) 