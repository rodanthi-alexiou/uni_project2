INCLUDE = ../../include
MODULES = ../../modules
# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = vector_insert_steps.o $(MODULES)/UsingDynamicArray/ADTVector.o

# Το εκτελέσιμο πρόγραμμα
EXEC = vector_insert_steps

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = amortized

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)


clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)