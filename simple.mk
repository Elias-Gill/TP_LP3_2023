# compilador
CC := gcc
CFLAGS := -Wall -Wextra -lpthread

# direcciones
SRC_DIR := src
BUILD_DIR := build

# Compilacion manual 1 a 1
listing%:
	# guardar el nombre del listing que se quiere compilar
	$(eval listing := $(@))
	# buscar la carpeta a compilar
	$(eval obj_dir := $(shell find $(SRC_DIR) -type d -name $(listing)))
	# formar la carpeta destino
	$(eval arch_dest := $(shell echo $(obj_dir) | sed 's/$(SRC_DIR)/$(BUILD_DIR)/g'))
	$(eval build_dir := $(shell dirname $(arch_dest)))
	@mkdir -p $(build_dir) 
	$(CC) $(CFLAGS) -o $(arch_dest) $(obj_dir)/* ;
