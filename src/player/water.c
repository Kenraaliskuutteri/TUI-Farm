#include "../../include/game.h"

void init_water(GameWorld *world) {
    world->water.water_amount = 20;
    world->water.max_water = 20;
    world->water.no_water = 0;
}

void water_plant_action(GameWorld *world) {
    PlantInstance *tile = &world->plants[world->player.y][world->player.x];
    if (tile->type == PLANT_NONE) return;
    if (world->water.water_amount <= 0) return;

    world->water.water_amount--;
    if (world->water.water_amount == 0) {
        world->water.no_water = 1;
    }
    tile->watered = 1;
}