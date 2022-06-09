# 'make' builds project
# 'make doxy' builds doxygen
# 'make all' builds project and doxygen
# 'make clean' removes all object files, executables, and doxygen

PROJ = nQueens
CC = gcc 
DOXYGEN = doxygen 

CFLAGS = -std=c99 -Wall -O -Wuninitialized -Wunreachable-code -pedantic 
LFLAGS = -lm

C_FILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(C_FILES))

$(PROJ): $(OBJS)
	$(CC) -o $(PROJ) $(OBJS) $(LFLAGS)

all:
	make
	make doxy

doxy:
	$(DOXYGEN) doxygen.conf &> doxygen.log

clean:
	rm -rf *.o nQueens doxygen.log html
