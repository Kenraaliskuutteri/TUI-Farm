#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/game.h"

int main() {
    GameWorld world;
    init_world(&world);
    init_clock(&world);
    init_player(&world);
    init_plants(&world);
    init_water(&world);

    enable_raw_mode();
    atexit(disable_raw_mode);

    printf("\033[?1049h\033[?25l");
    fflush(stdout);

    int current_rows = 0;
    int current_cols = 0;

    while (1) {
        if (check_screen_size(&current_rows, &current_cols)) {
            handle_input(&world);
            update_clock(&world);
            update_plants(&world);
            render_world(&world, current_rows, current_cols);
        } else {
            render_too_small_screen(current_rows, current_cols);
        }

        fflush(stdout);
        usleep(100000);
    }

    printf("\033[?1049l\033[?25h");
    return 0;
}