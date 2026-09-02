#include <stdio.h>
#include <unistd.h>
#include "../include/game.h"

int main() {
    GameWorld world;
    init_world(&world);
    init_clock(&world);


    printf("\033[?1049h\033[?25l");
    fflush(stdout);

    int current_rows = 0;
    int current_cols = 0;

    while (1) {
        if (check_screen_size(&current_rows, &current_cols)) {
            update_clock(&world);
            render_world(&world, current_rows, current_cols);
        } else {
            render_too_small_screen(current_rows, current_cols);
        }
        
        fflush(stdout);
        usleep(200000); 
    }

    printf("\033[?1049l\033[?25h");
    return 0;
}