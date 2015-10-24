

EXE = tester
OBJS = test_alloc.o pool_memory_manager.o
DEPS = resources/list.h
COMPILER = cc
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror
LINKER = cc

all : $(EXE) 

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) -o $(EXE)


test_alloc.o : test/test_alloc.c
	$(COMPILER) $(COMPILER_OPTS) test/test_alloc.c


pool_memory_manager.o : pool_memory_manager.c $(DEPS)
	$(COMPILER) $(COMPILER_OPTS) pool_memory_manager.c
	

clean :
	-rm -f *.o $(EXE) 