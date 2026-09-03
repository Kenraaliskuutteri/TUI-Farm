CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Automatically finds all .c files in src and all its subdirectories
SRC = $(shell find src -name "*.c")
OBJ = game_engine

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ)