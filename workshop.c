#define _CRT_SECURE_NO_WARNINGS  // <-- Add this right here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structures
typedef enum {//creatd the alias for future item types that can be resused over and over again - track what kind of hardware each item is
	Type_Bolt = 1,
	Type_Nut,
	Type_Washer,
}ItemType;

typedef struct {
	ItemType type; //uses item type enum to assign item type then assiged to a spefic type - generic strucutre that fits any piece of hardware
	int dimension_primary;
	float pitch;
	int dimension_secondary;
	float thickness;
	int quantity;
} Item;

typedef struct {
	Item items[300];
	int item_count;
}Workshop_Inventory; //created a strcuutre for workshop inventory to clean main program 

//Function Prototypes (tells compiler these functions exist)
void display_menu(void);
void add_item(Workshop_Inventory *inv, ItemType type);
void view_inventory(Workshop_Inventory* inv);
void update_stock(Workshop_Inventory* inv);
void search_hardware(Workshop_Inventory* inv);
int find_item(Workshop_Inventory *inv, ItemType type, int dimension_primary, float pitch, int dimension_secondary, float thickness);


// Main Program
int main() {
	Workshop_Inventory inv = { 0 }; //sets all arrays and counts to 0 creates int for inventory
	int choice = 0;
	
	do {
		display_menu(); //calls to function that displays menu and runs the function
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			int sub_choice = 0;
			printf("\nWhat would you like to add: \n");
			printf("Choose: 1. Bolt  2. Nut  3. Washer \nChoice: ");
			scanf("%d", &sub_choice);

			if (sub_choice >= 1 && sub_choice <= 3) { 
				add_item(&inv, (ItemType)sub_choice);
			}else {
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
			printf("Exiting Program\n");
			break;
		default:
			printf("Invalid choice. \n\n");
			break;
		}

	} while (choice != 5);

	printf("Broken through\n");

	return 0; 
 }

//Functions 
void display_menu(void) {
	printf("=== Workshop Inventory Menu ===\n");
	printf("1. Add New Hardware\n");
	printf("2. View All Inventory\n");
	printf("3. Update Stock Quantities\n");
	printf("4. Search for Hardware\n");
	printf("5. Exit\n");
	printf("Enter your Choice: ");
}

void add_item(Workshop_Inventory *inv,ItemType type) { //function means go to memory stored in inv (inventory) and look inside and grab bolt_count variable
	if (inv->item_count >= 300) {  //arrow operator (points to struct)
		printf("Inventory is full\n");
		return;
	}
	Item *item = &inv->items[inv->item_count];
	Item->type = type;
	
	if (type ==Type_Bolt) {
	printf("\n --- Add Bolt ---\n");
	printf("Enter diamter: (mm) ");
	scanf("%d", &item->dimension_primary);
	printf("Enter Pitch: ");
	scanf("%f", &item->pitch);
	printf("Enter Length: ");
	scanf("%d", &item->dimension_secondary);
	item->thickness = 0
	}
	else if (type == Type_Nut) {
		printf("\n --- Add Nut ---\n");
		printf("Enter inner diamter: (mm) ");
		scanf("%d", &item-> dimension_primary);
		printf("Enter Pitch: ");
		scanf("%f", &item->pitch);
		printf("Enter Height: ");
		scanf("%d", &item->dimension_secondary;
		item-> thickness = 0;
	}
	else if (type = Type_Washer) {
		printf("\n --- Add Washer ---\n");
		printf("Enter hole size: (mm) ");
		scanf("%d", &item->dimension_primary);
		printf("Enter diamter: ");
		scanf("%f", &item->dimension_secondary);
		printf("Enter Thickness: ");
		scanf("%d", &b->thickness);
		item->pitch = 0;
	}

	printf("Enter Quantity: ");
	scanf("%d", &item->quantity);

	inv->item_count++;
	printf("Hardware Succesfully added.);
}

void view_inventory(Workshop_Inventory* inv) {
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
				i+1,
				item->dimension_primary,
				item->pitch,
				item->dimension_secondary,
				item->quantity);
		} else if (item->type == Type_Nut) {
			printf("[%d] [Nut] M%d x %.1f | Length: %dmm | Qty: %d\n",
				i+1,
				item->dimension_primary,
				item->pitch,
				item->dimension_secondary,
				item->quantity);
		}else if (item->type == Type_Washer) {
			printf("[%d] [Washer]  M%d Hole | Outer Diam: %dmm | Thick: %dmm | Qty: %d\n",
				i+1,
				item->dimension_primary,
				item->dimension_secondary,
				item->thickness,
				item->quantity);
		}
	}
}

int find_item(Workshop_Inventory* inv, int dimension_primary, float pitch, int dimension_secondary, float thickness) {
	for (int i = 0; i < inv->item_count; i++) {
		Item *item = &inv->items[i];

		if (item->type == type && //logical AND operator evualtes both conditions in a chart for specefic results
			item->dimension_primary == dimension_primary &&
			item->pitch == pitch &&
			item->dimension_secondary == dimension_secondary &&
			item->thickness == thickness) {
			return i; //found duplicate 
		}
	}
	return -1; //no matching bolt found
}

void update_stock(Workshop_Inventory* inv) { //function that updates stock 
	int type_index = 0;
	int new_quantity = 0;

	printf("\n=== Update Stock Quantities ===\n");

	if (inv->item_count == 0) {
		printf("No items in inventory");
		return;
	}
	
	view_inventory(inv);
		
	printf("Enter the number [%d-%d] of the item to update: ", 1, inv->item_count);
	scanf("%d", &item_index);

	if (item_index < 1 || item_index > inv->item_count) {
		printf("Invalid item number. \n\n");
		return;
	}

	printf("Enter new quantity: ");
	scanf("%d", &new_quantity);

	inv->items[item_index - 1].quantity = new_quantity;
	printf("Quantity updated succesfully!\n\n");
}

void search_hardware(Workshop_Inventory* inv) {
	int search_diam = 0;
	int found_any = 0; //Flag to check if we found at least 1 item

	printf("\n=== Search Harware ===\n");
	printf("Enter the target diameter to search for (mm): ");
	scanf("%d", &search_diam);

	printf("\n--- Results for %dmm Hardware ---\n", search_diam);

	//1. Search bolts
	for (int i = 0; i < inv->item_count; i++) {
		Item *item =&inv->items[i];
		
		if(item->dimension_primary == search_diam) {
			if (item->item == Type_Bolt){
				printf("[Bolt] M%d x %.1f | Length: %dmm | Qty: %d\n",
				item->dimension_primary,
				item->pitch,
				item->dimension_secondary,
				item->quantity);
			}else if (item->item == Type_Nut) {
				printf("[Nut] M%d x %.1f | Length: %dmm | Qty: %d\n",
				item->dimension_primary,
				item->pitch,
				item->dimension_secondary,
				item->quantity);
			}else if (item->type == Type_Washer) {
				printf("[Washer] M%d Hole | Outer Diameter %dmm | Thickness: %.1fmm | Qty: %d\n",
				item->dimension_primary,
				item->dimension_secondary,
				item->thickness,
				item->quantity);
			}
			found_any = 1;
		}
	}
	
	if(!found_any) {
		printf("No Hardware found with %dmm diameter.\n", search_diam);
	}
	printf("\n");
}
