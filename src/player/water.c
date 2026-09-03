// src/plants/water.c
#include <stdio.h>
#include "../../include/game.h"

void water_plant_action(GameWorld *world) {
    // Check if player has water left
    if (world->water.water_amount > 0) {
        world->water.water_amount--; // Use 1L
        
        if (world->water.water_amount == 0) {
            world->water.water = 0;
            world->water.no_water = 1; // Trigger warning flag
        }
    }
}