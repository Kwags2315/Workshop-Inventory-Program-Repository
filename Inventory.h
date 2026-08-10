#ifndef INVENTORY_H
#define INVENTORY_H

// Data Structures
typedef enum {
    Type_Bolt = 1,
    Type_Nut,
    Type_Washer
} ItemType;

typedef struct {
    ItemType type;
    int dimension_primary;   // Diameter / Hole size
    float pitch;             // Thread pitch
    int dimension_secondary; // Length / Height / Outer Diam
    float thickness;         // Thickness (washers)
    int quantity;
} Item;

typedef struct {
    Item items[300];
    int item_count;
} Workshop_Inventory;

// Core Pure Logic API Functions (Return 0 for success, -1 for error)
int add_item(Workshop_Inventory *inv, Item new_item);
int update_stock(Workshop_Inventory *inv, int item_index, int new_quantity);
int find_item(Workshop_Inventory *inv, ItemType type, int dim_primary, float pitch, int dim_secondary, float thickness);
void save_inventory(Workshop_Inventory *inv);
void load_inventory(Workshop_Inventory *inv);

#endif
