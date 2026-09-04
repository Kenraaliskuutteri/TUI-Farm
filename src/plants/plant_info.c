#include "../../include/game.h"

void init_plants(GameWorld *world) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            world->plants[y][x].type = PLANT_NONE;
            world->plants[y][x].stage = 0;
            world->plants[y][x].ticks = 0;
            world->plants[y][x].watered = 0;
        }
    }
    init_inventory(&world->inventory);
}

void plant_action(GameWorld *world, PlantType type) {
    PlantInstance *tile = &world->plants[world->player.y][world->player.x];
    if (tile->type != PLANT_NONE) return;

    const PlantData *data = get_plant_data(type);
    if (!has_item(&world->inventory, data->seed_item, 1)) return;

    remove_item(&world->inventory, data->seed_item, 1);
    tile->type = type;
    tile->stage = 0;
    tile->ticks = 0;
    tile->watered = 0;
}

void gather_action(GameWorld *world) {
    PlantInstance *tile = &world->plants[world->player.y][world->player.x];
    if (tile->type == PLANT_NONE) return;

    const PlantData *data = get_plant_data(tile->type);
    if (tile->stage < data->max_stage) return;

    add_item(&world->inventory, data->yield_item, data->yield_amount);
    tile->type = PLANT_NONE;
    tile->stage = 0;
    tile->ticks = 0;
    tile->watered = 0;
}

void update_plants(GameWorld *world) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            PlantInstance *tile = &world->plants[y][x];
            if (tile->type == PLANT_NONE) continue;

            const PlantData *data = get_plant_data(tile->type);
            if (tile->stage >= data->max_stage) continue;
            if (!tile->watered) continue;

            tile->ticks++;
            if (tile->ticks >= data->ticks_per_stage) {
                tile->ticks = 0;
                tile->stage++;
                tile->watered = 0;
            }
        }
    }
}

char get_plant_symbol(const PlantInstance *plant) {
    if (plant->type == PLANT_NONE) return '.';
    const PlantData *data = get_plant_data(plant->type);
    if (data->max_stage <= 0) return '.';

    static const char fill_chars[4] = {'.', 'o', 'O', '#'};
    int index = (plant->stage * 3) / data->max_stage;
    if (index > 3) index = 3;
    return fill_chars[index];
}