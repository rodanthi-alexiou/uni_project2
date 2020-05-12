INCLUDE = ../../include
MODULE = ../../UsingDynamicArray
LIB = ../../lib

# compiler 
GCC = gcc

GCCFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

OBJS = vector_insert_steps.o $(MODULE)/ADTVector.c

EXEC = vector_insert_steps

$(EXEC): $(OBJS)        
$(GCC)  $(OBJS) -o  $(EXEC) $(GCCFLAGS)

#ARGS = real
run: $(EXEC) 
    ./$(EXEC) $(ARGS)