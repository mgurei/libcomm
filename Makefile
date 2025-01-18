##
# libcomm
# @file
# @version 0.1
#
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I./src -I./src/protocols
LDFLAGS =

SRC = $(wildcard src/*.c src/protocols/*.c)
OBJ = $(SRC:.c=.o)

all: libcomm.so

libcomm.so: $(OBJ)
	$(CC) -shared -fPIC -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -rf *.so *.o

# Explanation:
# - `CC`: Compiler (gcc).
# - `CFLAGS`: Compiler flags for warnings and standards compliance, and include path for protocols.
# - `LDFLAGS`: Linker flags (can be added later).
# - `SRC`: All source files in the `src/` and `src/protocols/` directories.
# - `OBJ`: Object files corresponding to the source files.
# - `all`: Target to build the shared library (`libcomm.so`).
# - `libcomm.so`: Depends on the object files.
# - `clean`: Target to remove the built library files and object files.

# end
