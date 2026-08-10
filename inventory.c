#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "inventory.h"

int add_item(Workshop_Inventory *inv, Item new_item) {
    if (inv->item_count >= 300) {
        return -1; // Error: Inventory full
    }
    
    inv->items[inv->item_count] = new_item;
    inv->item_count++;
    return 0; // Success
}

int update_stock(Workshop_Inventory *inv, int item_index, int new_quantity) {
    if (item_index < 0 || item_index >= inv->item_count) {
        return -1; // Error: Invalid index
    }
    
    inv->items[item_index].quantity = new_quantity;
    return 0; // Success
}

int find_item(Workshop_Inventory *inv, ItemType type, int dim_primary, float pitch, int dim_secondary, float thickness) {
    for (int i = 0; i < inv->item_count; i++) {
        Item *item = &inv->items[i];
        if (item->type == type &&
            item->dimension_primary == dim_primary &&
            item->pitch == pitch &&
            item->dimension_secondary == dim_secondary &&
            item->thickness == thickness) {
            return i; // Found duplicate at index i
        }
    }
    return -1; // Not found
}

void save_inventory(Workshop_Inventory *inv) {
    FILE *file = fopen("Inventory.txt", "w");
    if (file == NULL) return;

    fprintf(file, "%d\n", inv->item_count);
    for (int i = 0; i < inv->item_count; i++) {
        fprintf(file, "%d %d %.2f %d %.2f %d\n",
            inv->items[i].type,
            inv->items[i].dimension_primary,
            inv->items[i].pitch,
            inv->items[i].dimension_secondary,
            inv->items[i].thickness,
            inv->items[i].quantity);
    }
    fclose(file);
}

void load_inventory(Workshop_Inventory *inv) {
    FILE *file = fopen("Inventory.txt", "r");
    if (file == NULL) return;
    
    if (fscanf(file, "%d", &inv->item_count) != 1) {
        inv->item_count = 0;
        fclose(file);
        return;
    }

    for (int i = 0; i < inv->item_count; i++) {
        int type_int;
        fscanf(file, "%d %d %f %d %f %d",
            &type_int,
            &inv->items[i].dimension_primary,
            &inv->items[i].pitch,
            &inv->items[i].dimension_secondary,
            &inv->items[i].thickness,
            &inv->items[i].quantity);
        inv->items[i].type = (ItemType)type_int;
    }
    fclose(file);
}
