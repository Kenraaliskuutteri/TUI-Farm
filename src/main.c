#include <stdio.h>
#include <unistd.h> 
#include "../include/game.h"

int main() {
    GameWorld world;
    init_world(&world);

    
    printf("\033[?1049h\033[?25l");
    fflush(stdout);

    while (1) {
        render_world(&world);
        usleep(200000); // Refresh roughly 5 times a second 200ms
    }

    return 0;
}
