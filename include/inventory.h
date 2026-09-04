#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_INVENTORY_SLOTS 16

typedef struct {
    int item_id;
    int count;
} InventorySlot;

typedef struct {
    InventorySlot slots[MAX_INVENTORY_SLOTS];
} Inventory;

void init_inventory(Inventory *inv);
int add_item(Inventory *inv, int item_id, int amount);
int remove_item(Inventory *inv, int item_id, int amount);
int has_item(const Inventory *inv, int item_id, int amount);
void render_inventory(const Inventory *inv, int current_rows, int current_cols);

#endif