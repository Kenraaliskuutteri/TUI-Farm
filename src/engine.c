#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../include/game.h"

void init_world(GameWorld *world) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            world->grid[y][x].x = x;
            world->grid[y][x].y = y;
            world->grid[y][x].symbol = '.';
        }
    }
    world->show_inventory = 0;
}

int check_screen_size(int *current_rows, int *current_cols) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    *current_rows = w.ws_row;
    *current_cols = w.ws_col;

    if (w.ws_row < MIN_ROWS || w.ws_col < MIN_COLS) {
        return 0;
    }
    return 1;
}

void render_too_small_screen(int current_rows, int current_cols) {
    printf("\033[2J");

    int msg_height = 5;
    int msg_width = 40;

    int start_row = (current_rows - msg_height) / 2;
    int start_col = (current_cols - msg_width) / 2;

    if (start_row < 1) start_row = 1;
    if (start_col < 1) start_col = 1;

    printf("\033[%d;%dH⚠️  TERMINAL WINDOW TOO SMALL", start_row, start_col);
    printf("\033[%d;%dH----------------------------------------", start_row + 1, start_col);
    printf("\033[%d;%dHCurrent Screen: %d Columns x %d Rows", start_row + 2, start_col, current_cols, current_rows);
    printf("\033[%d;%dHRequired Min:   %d Columns x %d Rows", start_row + 3, start_col, MIN_COLS, MIN_ROWS);
    printf("\033[%d;%dHPlease stretch your window to resume...", start_row + 4, start_col);
}

void render_world(const GameWorld *world, int current_rows, int current_cols) {
    printf("\033[2J");

    int content_height = MAP_HEIGHT + 4;
    int content_width = MAP_WIDTH * 2;

    int start_row = (current_rows - content_height) / 2;
    int start_col = (current_cols - content_width) / 2;

    if (start_row < 1) start_row = 1;
    if (start_col < 1) start_col = 1;

    int clock_box_row = start_row + 2;
    int clock_box_col = start_col + content_width + 4;

    printf("\033[%d;%dH+------------+", clock_box_row, clock_box_col);
    printf("\033[%d;%dH| Day: %-5d |", clock_box_row + 1, clock_box_col, world->clock.days);
    printf("\033[%d;%dH| Time: %02d:%02d|", clock_box_row + 2, clock_box_col, world->clock.hours, world->clock.minutes);
    printf("\033[%d;%dH+------------+", clock_box_row + 3, clock_box_col);

    printf("\033[%d;%dH+------------+", clock_box_row + 4, clock_box_col);
    printf("\033[%d;%dH| Water: %-3d |", clock_box_row + 5, clock_box_col, world->water.water_amount);
    printf("\033[%d;%dH| Max: %-3dL  |", clock_box_row + 6, clock_box_col, world->water.max_water);
    printf("\033[%d;%dH+------------+", clock_box_row + 7, clock_box_col);

    int info_box_row = clock_box_row + 8;
    const PlantInstance *cursor_plant = &world->plants[world->player.y][world->player.x];

    printf("\033[%d;%dH+----------------+", info_box_row, clock_box_col);
    if (cursor_plant->type == PLANT_NONE) {
        printf("\033[%d;%dH| Tile: Empty    |", info_box_row + 1, clock_box_col);
        printf("\033[%d;%dH|                |", info_box_row + 2, clock_box_col);
        printf("\033[%d;%dH|                |", info_box_row + 3, clock_box_col);
    } else {
        const PlantData *data = get_plant_data(cursor_plant->type);
        int ticks_left = data->ticks_per_stage - cursor_plant->ticks;
        printf("\033[%d;%dH| %-14s |", info_box_row + 1, clock_box_col, data->name);
        printf("\033[%d;%dH| Stage: %d/%d    |", info_box_row + 2, clock_box_col, cursor_plant->stage, data->max_stage);
        if (cursor_plant->stage >= data->max_stage) {
            printf("\033[%d;%dH| Ready!         |", info_box_row + 3, clock_box_col);
        } else if (!cursor_plant->watered) {
            printf("\033[%d;%dH| Needs water    |", info_box_row + 3, clock_box_col);
        } else {
            printf("\033[%d;%dH| Grows in: %-4d |", info_box_row + 3, clock_box_col, ticks_left);
        }
    }
    printf("\033[%d;%dH+----------------+", info_box_row + 4, clock_box_col);

    printf("\033[%d;%dH=== TEST BUILD ===", start_row, start_col);
    printf("\033[%d;%dHPress Ctrl+C to exit.", start_row + 3 + MAP_HEIGHT, start_col);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("\033[%d;%dH", start_row + 2 + y, start_col);
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == world->player.x && y == world->player.y) {
                printf("%c ", world->player.symbol);
            } else if (world->plants[y][x].type != PLANT_NONE) {
                printf("%c ", get_plant_symbol(&world->plants[y][x]));
            } else {
                printf("%c ", world->grid[y][x].symbol);
            }
        }
    }

    if (world->show_inventory) {
        render_inventory(&world->inventory, current_rows, current_cols);
    }
}