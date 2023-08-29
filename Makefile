SRC_DIR := src
BUILD_DIR := build

# Find all main files
SRCS := $(shell find $(SRC_DIR) -name "listing*.c")

# Generate the corresponding object file paths
OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:.c= ))

# Generate the corresponding build directory paths
BUILD_DIRS := $(sort $(dir $(OBJS)))

# Set the compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Wextra -lpthread

.PHONY: all clean

all: $(OBJS)

# Rule to compile the main files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the build directories
$(BUILD_DIRS):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
