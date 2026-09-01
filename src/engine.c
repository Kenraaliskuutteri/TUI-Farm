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

    printf("\033[%d;%dH⚠️  TERMINAL WINDOW TOO SMALL", start_row, start_col); // I included a emoji to laugh at the people still using xterm :D
    printf("\033[%d;%dH----------------------------------------", start_row + 1, start_col);
    printf("\033[%d;%dHCurrent Screen: %d Columns x %d Rows", start_row + 2, start_col, current_cols, current_rows);
    printf("\033[%d;%dHRequired Min:   %d Columns x %d Rows", start_row + 3, start_col, MIN_COLS, MIN_ROWS);
    printf("\033[%d;%dHPlease stretch your window to resume...", start_row + 4, start_col); // Thanks gemini for fixing my stuff into printf train
}

void render_world(const GameWorld *world, int current_rows, int current_cols) {

    printf("\033[2J"); 
    

    int content_height = 14; 

    int content_width = 20;  

    // calculates where the middle/center or what you call it is.
    int start_row = (current_rows - content_height) / 2;
    int start_col = (current_cols - content_width) / 2;

    if (start_row < 1) start_row = 1;
    if (start_col < 1) start_col = 1;

    // prints the thing in the center
    printf("\033[%d;%dH=== TEST BUILD ===", start_row, start_col - 4);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("\033[%d;%dH", start_row + 2 + y, start_col);
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("%c ", world->grid[y][x].symbol);
        }
    }

    //  Print the Footer centered below the map
    printf("\033[%d;%dHPress Ctrl+C to exit.", start_row + 3 + MAP_HEIGHT, start_col - 1);
}
