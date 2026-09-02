#ifndef GAME_H
#define GAME_H

// The minimum terminal floor resolution required to play
#define MIN_ROWS 24
#define MIN_COLS 80

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct {
    int x;
    int y;
    char symbol;
} Tile;

typedef struct {
    int total_ticks;
    int minutes;
    int hours;
    int days;
} ClockData;

typedef struct {
    Tile grid[MAP_HEIGHT][MAP_WIDTH];
    ClockData clock;
} GameWorld;

void init_world(GameWorld *world);
// Updated to accept layout boundaries
void render_world(const GameWorld *world, int current_rows, int current_cols);

int check_screen_size(int *current_rows, int *current_cols);
void render_too_small_screen(int current_rows, int current_cols);

void init_clock(GameWorld *world);
void update_clock(GameWorld *world);

#endif
