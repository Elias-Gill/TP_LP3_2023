# evita que make imprima comandos en la terminal
.SILENT:
# compilador
CC := g++
CFLAGS := -Wall -Wextra -lpthread -D_XOPEN_SOURCE

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
	if [ "$(listing)" = "listing1.1" ]; then \
		$(CC) $(CFLAGS) -c $(obj_dir)/main.c -o main.o; \
		$(CC) $(CFLAGS) -c src/Cap1/listing1.2/reciprocal.cpp -o reciprocal.o; \
		$(CC) main.o reciprocal.o -o $(arch_dest); \
		rm *.o; \
	elif [ "$(listing)" = "listing1.2" ]; then \
		$(CC) $(CFLAGS) -c $(obj_dir)/reciprocal.cpp -o reciprocal.o; \
		$(CC) $(CFLAGS) -c src/Cap1/listing1.1/main.c -o main.o; \
		$(CC) main.o reciprocal.o -o $(arch_dest); \
		rm *.o; \
	elif [ "$(listing)" = "listing1.3" ]; then \
		$(CC) $(CFLAGS) -c src/Cap1/listing1.1/main.c -o main.o; \
		$(CC) $(CFLAGS) -c src/Cap1/listing1.2/reciprocal.cpp -o reciprocal.o; \
		$(CC) main.o reciprocal.o -o $(arch_dest); \
		rm *.o; \
	else \
		$(CC) $(CFLAGS) -o $(arch_dest) $(obj_dir)/* ; \
	fi
	

# Define a variable with the list of files in the source directory
$(eval DIRS := $(shell basename -a $(shell find $(SRC_DIR) -type d -name "listing*")))

# Create a target that applies the rule to each file
all: $(DIRS)
	@for file in $^; do \
		$(MAKE) "$$file"; \
	done

clean: 
	@rm $(BUILD_DIR) -rf
