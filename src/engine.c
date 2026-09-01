#include <stdio.h>
#include "../include/game.h"

void init_world(GameWorld *world) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            world->grid[y][x].x = x;
            world->grid[y][x].y = y;
            world->grid[y][x].symbol = '.'; // Empty dirt character
        }
    }
}

void render_world(const GameWorld *world) {

    printf("\033[H"); 
    
    printf("Test build, type shit. \n\n");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("%c ", world->grid[y][x].symbol);
        }
        printf("\n");
    }
    printf("\n Since this is test, ig you can just Ctrl+C to exit.\n");
}
