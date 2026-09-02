CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

all:
	$(CC) $(CFLAGS) src/main.c src/engine.c -o game_engine

run:
	@$(CC) $(CFLAGS) src/main.c src/engine.c src/time.c src/player/player.c -o .tmp_game && ./.tmp_game; rm -f .tmp_game

clean:
	rm -f game_engine
