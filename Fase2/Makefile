# Definições
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
AR = ar
ARFLAGS = rcs

# Diretórios
SRC_DIR = src
INC_DIR = include
LIB_DIR = lib
OBJ_DIR = $(LIB_DIR)

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBRARY = $(LIB_DIR)/libgrafo.a
EXEC = proj_antenas

# Regra principal
all: $(EXEC)

# Compilar objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar biblioteca estática
$(LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Compilar executável
$(EXEC): main.c $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ main.c $(LIBRARY) -lm

# Criar diretório da biblioteca, se não existir
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Limpeza
tidy:
	rm -f $(OBJS)

clean: tidy
	rm -f $(LIBRARY) $(EXEC)
