# render = src/engine/render/render.c
# global = src/engine/global.c
# math = src/math/rect.c

# files = src/main.c $(render) $(global) $(math)

# build_dir = build
# obj_name = play
# include_path = -Iinclude
# lib_paths = -L/opt/homebrew/Cellar/sdl2/2.30.2/lib/ -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib
# linker_flags = -lSDL2_image -lSDL2

# all:
# 	gcc -Wall $(include_path) $(lib_paths) $(files) $(linker_flags) -o $(build_dir)/$(obj_name)
# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Iinclude
LDFLAGS := -L/opt/homebrew/Cellar/sdl2/2.30.4/lib/ -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib
LDLIBS := -lSDL2_image -lSDL2

# Directories
SRC_DIR := src
BUILD_DIR := build

# Find all C source files recursively
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')

# Target binary
TARGET := $(BUILD_DIR)/play

# Phony target to build all
all: $(TARGET)

# Rule to link the target binary
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Phony target to clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
