#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "inventory.h"

int main() {
    Workshop_Inventory inv = { 0 };
    load_inventory(&inv);

    printf("Backend test startup. Currently loaded %d items.\n", inv.item_count);

    // Test adding an item programmatically (API-style)
    Item sample_bolt = { Type_Bolt, 8, 1.25, 40, 0.0, 50 };
    
    if (add_item(&inv, sample_bolt) == 0) {
        printf("Successfully added bolt via API logic!\n");
    }

    save_inventory(&inv);
    return 0;
}
