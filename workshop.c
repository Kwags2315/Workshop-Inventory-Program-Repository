#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structures
typedef enum {
    Type_Bolt = 1,
    Type_Nut,
    Type_Washer
} ItemType;

typedef struct {
    ItemType type;
    int dimension_primary;
    float pitch;
    int dimension_secondary;
    float thickness;
    int quantity;
} Item;

typedef struct {
    Item items[300];
    int item_count;
} Workshop_Inventory;

// Function Prototypes
void display_menu(void);
void add_item(Workshop_Inventory *inv, ItemType type);
void view_inventory(Workshop_Inventory *inv);
void update_stock(Workshop_Inventory *inv);
void search_hardware(Workshop_Inventory *inv);
int find_item(Workshop_Inventory *inv, ItemType type, int dimension_primary, float pitch, int dimension_secondary, float thickness);
void save_inventory(Workshop_Inventory *inv);
void load_inventory(Workshop_Inventory *inv);

// Main Program
int main() {
    Workshop_Inventory inv = { 0 };
    load_inventory(&inv);

    int choice = 0;

    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 1: { // Added curly brace for switch case scope
            int sub_choice = 0;
            printf("\nWhat would you like to add: \n");
            printf("Choose: 1. Bolt  2. Nut  3. Washer \nChoice: ");
            scanf("%d", &sub_choice);

            if (sub_choice >= 1 && sub_choice <= 3) {
                add_item(&inv, (ItemType)sub_choice);
            } else {
                printf("Invalid Choice.\n");
            }
            break;
        }
        case 2:
            view_inventory(&inv);
            printf("\n");
            break;
        case 3:
            update_stock(&inv);
            printf("Choice 3\n\n");
            break;
        case 4:
            search_hardware(&inv);
            printf("\n");
            break;
        case 5:
            printf("Saving and Exiting program...\n");
            save_inventory(&inv);
            break;
        default:
            printf("Invalid choice. \n\n");
            break;
        }

    } while (choice != 5);

    return 0;
}

// Functions 
void display_menu(void) {
    printf("=== Workshop Inventory Menu ===\n");
    printf("1. Add New Hardware\n");
    printf("2. View All Inventory\n");
    printf("3. Update Stock Quantities\n");
    printf("4. Search for Hardware\n");
    printf("5. Exit\n");
    printf("Enter your Choice: ");
}

void add_item(Workshop_Inventory *inv, ItemType type) {
    if (inv->item_count >= 300) {
        printf("Inventory is full\n");
        return;
    }
    Item *item = &inv->items[inv->item_count];
    item->type = type;
    
    if (type == Type_Bolt) {
        printf("\n --- Add Bolt ---\n");
        printf("Enter diameter: (mm) ");
        scanf("%d", &item->dimension_primary);
        printf("Enter Pitch: ");
        scanf("%f", &item->pitch);
        printf("Enter Length: ");
        scanf("%d", &item->dimension_secondary);
        item->thickness = 0;
    }
    else if (type == Type_Nut) {
        printf("\n --- Add Nut ---\n");
        printf("Enter inner diameter: (mm) ");
        scanf("%d", &item->dimension_primary);
        printf("Enter Pitch: ");
        scanf("%f", &item->pitch);
        printf("Enter Height: ");
        scanf("%d", &item->dimension_secondary);
        item->thickness = 0;
    }
    else if (type == Type_Washer) {
        printf("\n --- Add Washer ---\n");
        printf("Enter hole size: (mm) ");
        scanf("%d", &item->dimension_primary);
        printf("Enter outer diameter: ");
        scanf("%d", &item->dimension_secondary); // Fixed %f to %d
        printf("Enter Thickness: ");
        scanf("%f", &item->thickness);
        item->pitch = 0;
    }

    printf("Enter Quantity: ");
    scanf("%d", &item->quantity);

    inv->item_count++;
    printf("Hardware Successfully added.\n\n");
}

void view_inventory(Workshop_Inventory *inv) {
    printf("\n === Current Inventory === \n");
    printf("Currently %d Unique Items\n", inv->item_count);

    if (inv->item_count == 0) {
        printf("No hardware stored in inventory.\n\n");
        return;
    }
    for (int i = 0; i < inv->item_count; i++) {
        Item *item = &inv->items[i];

        if (item->type == Type_Bolt) {
            printf("[%d] [Bolt] M%d x %.1f | Length: %dmm | Qty: %d\n",
                i + 1,
                item->dimension_primary,
                item->pitch,
                item->dimension_secondary,
                item->quantity);
        } else if (item->type == Type_Nut) {
            printf("[%d] [Nut] M%d x %.1f | Length: %dmm | Qty: %d\n",
                i + 1,
                item->dimension_primary,
                item->pitch,
                item->dimension_secondary,
                item->quantity);
        } else if (item->type == Type_Washer) {
            printf("[%d] [Washer] M%d Hole | Outer Diam: %dmm | Thick: %.1fmm | Qty: %d\n",
                i + 1,
                item->dimension_primary,
                item->dimension_secondary,
                item->thickness,
                item->quantity);
        }
    }
}

// Fixed missing ItemType type parameter here
int find_item(Workshop_Inventory *inv, ItemType type, int dimension_primary, float pitch, int dimension_secondary, float thickness) {
    for (int i = 0; i < inv->item_count; i++) {
        Item *item = &inv->items[i];

        if (item->type == type &&
            item->dimension_primary == dimension_primary &&
            item->pitch == pitch &&
            item->dimension_secondary == dimension_secondary &&
            item->thickness == thickness) {
            return i;
        }
    }
    return -1;
}

void update_stock(Workshop_Inventory *inv) {
    int item_index = 0;
    int new_quantity = 0;

    printf("\n=== Update Stock Quantities ===\n");

    if (inv->item_count == 0) {
        printf("No items in inventory\n\n");
        return;
    }
    
    view_inventory(inv);
        
    printf("Enter the number [1-%d] of the item to update: ", inv->item_count);
    scanf("%d", &item_index);

    if (item_index < 1 || item_index > inv->item_count) {
        printf("Invalid item number. \n\n");
        return;
    }

    printf("Enter new quantity: ");
    scanf("%d", &new_quantity);

    inv->items[item_index - 1].quantity = new_quantity;
    printf("Quantity updated successfully!\n\n");
}

void search_hardware(Workshop_Inventory *inv) {
    int search_diam = 0;
    int found_any = 0;

    printf("\n=== Search Hardware ===\n");
    printf("Enter the target diameter to search for (mm): ");
    scanf("%d", &search_diam);

    printf("\n--- Results for %dmm Hardware ---\n", search_diam);

    for (int i = 0; i < inv->item_count; i++) {
        Item *item = &inv->items[i];
        
        if (item->dimension_primary == search_diam) {
            if (item->type == Type_Bolt) {
                printf("[Bolt] M%d x %.1f | Length: %dmm | Qty: %d\n",
                item->dimension_primary,
                item->pitch,
                item->dimension_secondary,
                item->quantity);
            } else if (item->type == Type_Nut) {
                printf("[Nut] M%d x %.1f | Length: %dmm | Qty: %d\n",
                item->dimension_primary,
                item->pitch,
                item->dimension_secondary,
                item->quantity);
            } else if (item->type == Type_Washer) {
                printf("[Washer] M%d Hole | Outer Diameter %dmm | Thickness: %.1fmm | Qty: %d\n",
                item->dimension_primary,
                item->dimension_secondary,
                item->thickness,
                item->quantity);
            }
            found_any = 1;
        }
    }
    
    if (!found_any) {
        printf("No Hardware found with %dmm diameter.\n", search_diam);
    }
    printf("\n");
}

void save_inventory(Workshop_Inventory *inv) {
    FILE *file = fopen("Inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }

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
    printf("Inventory saved to file successfully.\n");
}

void load_inventory(Workshop_Inventory *inv) {
    FILE *file = fopen("Inventory.txt", "r");
    if (file == NULL) {
        printf("No existing inventory file found. Completely empty.\n\n");
        return;
    }
    
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
    printf("Loaded %d items from saved inventory.\n\n", inv->item_count);
}
