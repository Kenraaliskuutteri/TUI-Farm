CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = $(shell find src -name "*.c")
OBJ = TUI-Farm

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

run: all
	./$(OBJ)

clean:
	rm -f $(OBJ)