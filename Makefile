# compilador
CC := gcc
CFLAGS := -Wall -Wextra -lpthread

# direcciones
SRC_DIR := src
BUILD_DIR := build

# Compilacion manual 1 a 1
listing%:
	$(eval listing := $(@))
	$(eval obj_dir := $(shell find $(SRC_DIR) -type d -name $(listing)))
	$(eval arch_dest := $(shell echo $(obj_dir) | sed 's/$(SRC_DIR)/$(BUILD_DIR)/g'))
	$(eval build_dir := $(shell dirname $(arch_dest)))
	@mkdir -p $(build_dir) 
	$(CC) $(CFLAGS) -o $(arch_dest) $(obj_dir)/* ;


# Define a variable with the list of files in the source directory
$(eval FILES := $(shell basename --suffix=.c -a $(shell find $(SRC_DIR) -name "*.c" | sed 's|src/||g')))

# Create a target that applies the rule to each file
all: $(FILES)
	@for file in $^; do \
		$(MAKE) "$$file"; \
		done

clean: 
	@rm $(BUILD_DIR) -rf
