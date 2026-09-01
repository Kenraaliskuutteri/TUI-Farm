#ifndef GAME_H
#define GAME_H

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct {
    int x;
    int y;
    char symbol;
} Tile;

typedef struct {
    Tile grid[MAP_HEIGHT][MAP_WIDTH];
} GameWorld;

// Functions that engine.c will implement
void init_world(GameWorld *world);
void render_world(const GameWorld *world);

#endif
