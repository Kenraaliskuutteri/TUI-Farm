#ifndef SEEDS
#define SEEDS

#define TICKS_PER_STAGE 200

typedef enum {
    PLANT_NONE,
    PLANT_WHEAT,
    PLANT_COUNT
} PlantType;

typedef enum {
    ITEM_NONE,
    ITEM_WHEAT,
    ITEM_WHEAT_SEED,
    ITEM_COUNT
} ItemId;

typedef struct {
    PlantType type;
    int stage;
    int ticks;
    int watered;
} PlantInstance;

typedef struct {
    PlantType type;
    int seed_item;
    int yield_item;
    int yield_amount;
    int max_stage;
    int ticks_per_stage;
    const char *name;
} PlantData;

const PlantData *get_plant_data(PlantType type);
char get_plant_symbol(const PlantInstance *plant);

#endif