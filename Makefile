##
# libcomm
# @file
# @version 0.1
#
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS =

all: libcomm.so

libcomm.so: $(wildcard src/*.c)
	gcc -shared -fPIC -o libcomm.so $(CFLAGS) $(LDFLAGS) $(wildcard src/*.c)

clean:
	rm -rf *.so *.a


# **Explanation:**
# 	  *   `CC`: Compiler (gcc).
#     *   `CFLAGS`: Compiler flags for warnings and standards compliance.
#     *   `LDFLAGS`: Linker flags (can be added later).
#     *   `all`: Target to build the shared library (`libcomm.so`).
#     *   `libcomm.so`: Depends on all source files in the `src/` directory.
#     *   `clean`: Target to remove the built library files.

# end
