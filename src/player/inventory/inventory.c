#include <stdio.h>
#include "../../../include/inventory.h"
#include "../../../include/plants_and_seeds.h"

void init_inventory(Inventory *inv) {
    for (int i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        inv->slots[i].item_id = ITEM_NONE;
        inv->slots[i].count = 0;
    }
}

int add_item(Inventory *inv, int item_id, int amount) {
    for (int i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        if (inv->slots[i].item_id == item_id) {
            inv->slots[i].count += amount;
            return 1;
        }
    }
    for (int i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        if (inv->slots[i].item_id == ITEM_NONE) {
            inv->slots[i].item_id = item_id;
            inv->slots[i].count = amount;
            return 1;
        }
    }
    return 0;
}

int remove_item(Inventory *inv, int item_id, int amount) {
    for (int i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        if (inv->slots[i].item_id == item_id && inv->slots[i].count >= amount) {
            inv->slots[i].count -= amount;
            if (inv->slots[i].count == 0) inv->slots[i].item_id = ITEM_NONE;
            return 1;
        }
    }
    return 0;
}

int has_item(const Inventory *inv, int item_id, int amount) {
    for (int i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        if (inv->slots[i].item_id == item_id && inv->slots[i].count >= amount) return 1;
    }
    return 0;
}

static const char *item_name(int item_id) {
    switch (item_id) {
        case ITEM_WHEAT: return "Wheat";
        case ITEM_WHEAT_SEED: return "Wheat Seed";
        default: return "Unknown";
    }
}

void render_inventory(const Inventory *inv, int current_rows, int current_cols) {
    int box_width = 23;
    int box_height = MAX_INVENTORY_SLOTS + 3;

    int start_row = (current_rows - box_height) / 2;
    int start_col = (current_cols - box_width) / 2;

    if (start_row < 1) start_row = 1;
    if (start_col < 1) start_col = 1;

    printf("\033[%d;%dH+----- Inventory -----+", start_row, start_col);

    int line = 0;
    for (int i = 0; i < MAX_INVENTORY_SLOTS; i++) {
        if (inv->slots[i].item_id == ITEM_NONE) continue;
        printf("\033[%d;%dH| %-15s x%-3d |", start_row + 1 + line, start_col, item_name(inv->slots[i].item_id), inv->slots[i].count);
        line++;
    }
    if (line == 0) {
        printf("\033[%d;%dH| (empty)              |", start_row + 1, start_col);
        line = 1;
    }

    printf("\033[%d;%dH+----------------------+", start_row + 1 + line, start_col);
    printf("\033[%d;%dHPress Q to close", start_row + 2 + line, start_col);
}   