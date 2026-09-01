#include <stdio.h>
#include <unistd.h>
#include "../include/game.h"

int main() {
    GameWorld world;
    init_world(&world);

    
    printf("\033[?1049h\033[?25l");
    fflush(stdout);

    int current_rows = 0;
    int current_cols = 0;

    while (1) {
        // this should check metrics from engine.c right.
        if (check_screen_size(&current_rows, &current_cols)) {
            // Screen is plenty big; draw the centered game map
            render_world(&world, current_rows, current_cols);
        } else {
            // Screen collapsed below floor limit; lock and show warning
            render_too_small_screen(current_rows, current_cols);
        }
        
        fflush(stdout);
        usleep(200000); // 200ms tick delay
    }

    return 0;
}
