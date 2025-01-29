##
# libcomm
# @file
# @version 0.1
#
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I./src -I./src/protocols
LDFLAGS = -L./build -lcomm
SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./build

SRC_FILES = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_FILES))

all: $(BUILD_DIR)/libcomm.so $(TEST_EXECUTABLES)

$(BUILD_DIR)/libcomm.so: $(OBJ_FILES)
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(BUILD_DIR)/libcomm.so
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

test: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do \
		LD_LIBRARY_PATH=$(BUILD_DIR) $$test; \
	done

.PHONY: all clean test

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
