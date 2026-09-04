#include "../../include/plants_and_seeds.h"

static const PlantData plant_table[PLANT_COUNT] = {
    { PLANT_NONE, ITEM_NONE, ITEM_NONE, 0, 0, 0, "Empty" },
    { PLANT_WHEAT, ITEM_WHEAT_SEED, ITEM_WHEAT, 3, 3, TICKS_PER_STAGE, "Wheat" }
};

const PlantData *get_plant_data(PlantType type) {
    if (type < 0 || type >= PLANT_COUNT) return &plant_table[PLANT_NONE];
    return &plant_table[type];
}