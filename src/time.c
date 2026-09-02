#include "../include/game.h"

void init_clock(GameWorld *world) {
    world->clock.total_ticks = 0;
    world->clock.minutes = 0;
    world->clock.hours = 8;
    world->clock.days = 1;
}

void update_clock(GameWorld *world) {

    world->clock.total_ticks++;

    if (world->clock.total_ticks >= 25) {
        world->clock.minutes += 1;
        world->clock.total_ticks = 0;
    }

    if (world->clock.minutes >= 60) {
        world->clock.minutes = 0;
        world->clock.hours++;
    }
    if (world->clock.hours >= 24) {
        world->clock.hours = 0;
        world->clock.days++;
    }
}