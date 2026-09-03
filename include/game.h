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
    int x;
    int y;
    char symbol;
} Player;

typedef struct {
    int water;          
    int no_water;       
    int water_amount;   // Remaining water in Liters
} Water;

typedef struct {
    int plant_info;
    int grow_status;
//    int genetics - This is for a later date. I really cant be asked with making this yet. We will see when it comes. 
} Info;

typedef struct {
    Tile grid[MAP_HEIGHT][MAP_WIDTH];
    ClockData clock;
    Player player;
    Water water;
    Info info;
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

void init_water(void);
void update_water(void);

void init_info(void); // i am SO lost... I don't think the init water and info should be a thing. BUT THEY WORK OKAY? I'll stop ripping out my hair for it.
void update_info(void);

#endif