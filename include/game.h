#ifndef GAME_H
#define GAME_H

#include "plants_and_seeds.h"
#include "inventory.h"

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
    int x;
    int y;
    char symbol;
} Player;

typedef struct {
    int water_amount;
    int max_water;
    int no_water;
} Water;

typedef struct {
    Tile grid[MAP_HEIGHT][MAP_WIDTH];
    PlantInstance plants[MAP_HEIGHT][MAP_WIDTH];
    ClockData clock;
    Player player;
    Water water;
    Inventory inventory;
    int show_inventory;
} GameWorld;

void init_world(GameWorld *world);
void render_world(const GameWorld *world, int current_rows, int current_cols);

int check_screen_size(int *current_rows, int *current_cols);
void render_too_small_screen(int current_rows, int current_cols);

void init_clock(GameWorld *world);
void update_clock(GameWorld *world);

void init_player(GameWorld *world);
void handle_input(GameWorld *world);

void enable_raw_mode(void);
void disable_raw_mode(void);

void init_water(GameWorld *world);
void water_plant_action(GameWorld *world);

void init_plants(GameWorld *world);
void update_plants(GameWorld *world);
void plant_action(GameWorld *world, PlantType type);
void gather_action(GameWorld *world);

#endif