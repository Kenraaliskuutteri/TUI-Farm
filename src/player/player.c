#include <stdio.h> // Is this used anywhere even? idfk
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/game.h"

static struct termios orig_termios;

void enable_raw_mode(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void init_player(GameWorld *world) {
    world->player.x = MAP_WIDTH / 2;
    world->player.y = MAP_HEIGHT / 2;
    world->player.symbol = '@';
}

void handle_input(GameWorld *world) {
    char ch;
    while (read(STDIN_FILENO, &ch, 1) > 0) {
        if ((ch == 'w' || ch == 'W') && world->player.y > 0) world->player.y--;
        if ((ch == 's' || ch == 'S') && world->player.y < MAP_HEIGHT - 1) world->player.y++;
        if ((ch == 'a' || ch == 'A') && world->player.x > 0) world->player.x--;
        if ((ch == 'd' || ch == 'D') && world->player.x < MAP_WIDTH - 1) world->player.x++;
    }
}