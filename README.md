#define _CRT_SECURE_NO_WARNINGS  // <-- Add this right here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structures
typedef struct {
	int diameter; //bolt diameter
	float pitch; //bolt pitch type - ex: M5x0.8 
	int length;
	int quantity;
}bolt; //created a structure defining a bolt with it's parts/parameters within the {}

typedef struct {
	int inner_diameter;
	float thread_pitch;
	int height;
	int quantity;
}nut; //created a strucutre called a nut with the parametrs of inner diameter, thread pithc, and height
// example: M5x0.8 4mm high

typedef struct {
	int hole;
	int diameter;
	float thickness;
	int quantity;
}washer;//created a structure defining a washer with it's parts/parameters being hole size, diamter
// and height ex: M5 hole diamter 10mm and thickness 0.5mm

typedef struct {
	bolt bolt_stock[100]; //created a arrary under bolts called bolt_stock allowing for 100 
	int bolt_count;
	nut nut_stock[100];//same for nut
	int nut_count;
	washer washer_stock[100];//same for washer
	int washer_count;
}Workshop_Inventory; //created a strcuutre for workshop inventory to clean main program 

//Function Prototypes (tells compiler these functions exist)
void display_menu(void);
void add_bolt(Workshop_Inventory* inv);//void function because it alters og data as opposed to returning value
//picks workshop inventory integar
void add_nut(Workshop_Inventory* inv);
void add_washer(Workshop_Inventory* inv);
void view_inventory(Workshop_Inventory* inv);
void update_stock(Workshop_Inventory* inv);
void search_hardware(Workshop_Inventory* inv);



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
			printf("Choose: 1. Bolt  2. Nut  3. Washer \n");
			scanf("%d", &sub_choice);

			if (sub_choice == 1) add_bolt(&inv);
			else if (sub_choice == 2) add_nut(&inv);
			else if (sub_choice == 3) add_washer(&inv);
			else printf("Invalid sub choice.\n");
			break;
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

void add_bolt(Workshop_Inventory *inv) { //function means go to memory stored in inv (inventory) and look inside and grab bolt_count variable
	if (inv->bolt_count >= 100) {  //arrow operator (points to struct)
		printf("Bolt Inventory is full\n");
		return;
	}
	
	bolt *b = &inv->bolt_stock[inv->bolt_count];//accesses array inside bolts, uses current number, gets exact memory location of free bolt spot

	printf("\n --- Add Bolt ---\n");
	printf("Enter diamter: (mm) ");
	scanf("%d", &b->diameter);
	printf("Enter Pitch: ");
	scanf("%f", &b->pitch);
	printf("Enter Length: ");
	scanf("%d", &b->length);
	printf("Enter Quanity: ");
	scanf("%d", &b->quantity);

	inv->bolt_count++;
	printf("Bolt added!\n\n");
}

void add_nut(Workshop_Inventory* inv) {
	if (inv->nut_count >= 100) {
		printf("Nut Inventory is Full\n");
		return;
	}

	nut *b = &inv->nut_stock[inv->nut_count];

	printf("\n --- Add Nut ---\n");
	printf("Enter inner diamter: (mm) ");
	scanf("%d", &b->inner_diameter);
	printf("Enter Pitch: ");
	scanf("%f", &b->thread_pitch);
	printf("Enter Height: ");
	scanf("%d", &b->height);
	printf("Enter Quantity: ");
	scanf("%d", &b->quantity);

	inv->nut_count++;
	printf("Nut added!\n\n");
}	

void add_washer(Workshop_Inventory* inv) {
	if (inv->washer_count >= 100) {
		printf("Washer Inventory is Full\n");
		return;
	}

	washer *b = &inv->washer_stock[inv->washer_count];
	
	printf("\n --- Add Washer ---\n");
	printf("Enter hole size: (mm) ");
	scanf("%d", &b->hole);
	printf("Enter diamter: ");
	scanf("%f", &b->diameter);
	printf("Enter Thickness: ");
	scanf("%d", &b->thickness);
	printf("Enter Quantity: ");
	scanf("%d", &b->quantity);

	inv->washer_count++;
	printf("Washer added!\n\n");
}

void view_inventory(Workshop_Inventory* inv) {
	printf("\n === Current Inventory === \n");

	printf("--- Bolts (%d) ---\n", inv->bolt_count);
	if (inv->bolt_count == 0) {
		printf("No bolts stored.\n\n");
	}else {
		for (int i = 0; i < inv->bolt_count; i++) {
			printf("[%d] M%d x %.1f (%dmm length) - Quantity: %d\n\n",
				i + 1,
				inv->bolt_stock[i].diameter,
				inv->bolt_stock[i].pitch,
				inv->bolt_stock[i].length,
				inv->bolt_stock[i].quantity);
		}
	}

	printf("--- Nuts (%d) ---\n", inv->nut_count);
	if (inv->nut_count == 0) {
		printf("No nuts stored.\n\n");
	}else {
		for (int i = 0; i < inv->nut_count; i++) {
			printf("[%d] M%d x %.1f (%dmm height) - Quantity: %d\n\n",
				i+1,
				inv->nut_stock[i].inner_diameter,
				inv->nut_stock[i].thread_pitch,
				inv->nut_stock[i].height,
				inv->nut_stock[i].quantity);
		}
	}

	printf("--- Washers (%d) ---\n", inv->washer_count);
	if (inv->washer_count == 0) {
		printf("No Washers stored.\n\n");
	}else {
		for (int i = 0; i < inv->washer_count; i++) {
			printf("[%d] Hole  %d Diameter (%.1fmm thick) - Quantity: %d\n\n",
				i+1,
				inv->washer_stock[i].hole,
				inv->washer_stock[i].diameter,
				inv->washer_stock[i].thickness,
				inv->washer_stock[i].quantity);
		}
	}
}

int find_bolt(Workshop_Inventory* inv, int diameter, float pitch, int length) {
	for (int i = 0; i < inv->bolt_count; i++) {
		if (inv->bolt_stock[i].diameter == diameter && //logical AND operator evualtes both conditions in a chart for specefic results
			inv->bolt_stock[i].pitch == pitch &&
			inv->bolt_stock[i].length == length) {
			return i; //found duplicate 
		}
	}
	return -1; //no matching bolt found
}

void update_stock(Workshop_Inventory* inv) { //function that updates stock 
	int type_choice = 0;
	int item_index = 0;
	int new_quantity = 0;

	printf("\n=== Update Stock Quantities ===\n");
	printf("\n Choose hardware to update: \n");
	printf("1. Bolts.     2. Nuts.    3. Washers. \n");
	printf("Enter choice: ");
	scanf("%d", &type_choice);

	if (type_choice == 1) {
		if (inv->bolt_count == 0) {
			printf("No Bolts aviable to update.\n");
			return;
		}
		//listing Bolts
		printf("\n--- Aviable Bolts ---\n");
		for (int i = 0; i < inv->bolt_count; i++) {
			printf("[%d] M%d x %.1f (%dmm lenght) - Quantity: %d\n",
				i + 1,
				inv->bolt_stock[i].diameter,
				inv->bolt_stock[i].pitch,
				inv->bolt_stock[i].length,
				inv->bolt_stock[i].quantity);
		}
		printf("Enter the number [%d-%d] of the bolt to update: ", 1, inv->bolt_count);
		scanf("%d", &item_index);

		if (item_index < 1 || item_index > inv->bolt_count) {
			printf("Invalid item number. \n\n");
			return;
		}

		printf("Enter new quantity: ");
		scanf("%d", &new_quantity);
		inv->bolt_stock[item_index - 1].quantity = new_quantity;
		printf("Quantity updated succesfully!\n\n");

	}
	else if (type_choice == 2) {
		if (inv->nut_count == 0) {
			printf("No nuts aviable to update.\n\n");
			return;
		}
		printf("\n --- Aviaible Nuts ---\n");
		for (int i = 0; i < inv->nut_count; i++) {
			printf("[%d] M%d x %.1f (%dmm height) - Quantity: %d\n",
				i + 1,
				inv->nut_stock[i].inner_diameter,
				inv->nut_stock[i].thread_pitch,
				inv->nut_stock[i].height,
				inv->nut_stock[i].quantity);
		}
		printf("Enter the number [%d - %d] of the nut to update: ", 1, inv->nut_count);
		scanf("%d", &item_index);

		if (item_index < 1 || item_index > inv->nut_count) {
			printf("Invalid item number.\n\n");
			return;
		}
		printf("Enter new Quantity: ");
		scanf("%d", &new_quantity);
		inv->nut_stock[item_index - 1].quantity = new_quantity;
		printf("Quantity updated succesfully!\n\n");
	}
	else if (type_choice == 3) {
		if (inv->washer_count == 0) {
			printf("No Washers aviable to update.\n\n");
			return;
		}
		printf("\n --- Aviaible Washers ---\n");
		for (int i = 0; i < inv->washer_count; i++) {
			printf("[%d] M%d x %.1f (%dmm height) - Quantity: %d\n",
				i + 1,
				inv->washer_stock[i].hole,
				inv->washer_stock[i].diameter,
				inv->washer_stock[i].thickness,
				inv->washer_stock[i].quantity);
		}
		printf("Enter the number [%d - %d] of the nut to update: ", 1, inv->washer_count);
		scanf("%d", &item_index);

		if (item_index < 1 || item_index > inv->washer_count) {
			printf("Invalid item number.\n\n");
			return;
		}
		printf("Enter new Quantity: ");
		scanf("%d", &new_quantity);
		inv->washer_stock[item_index - 1].quantity = new_quantity;
		printf("Quantity updated succesfully!\n\n");
	}
	else {
		printf("Invalid choice.\n\n");
	}
}

void search_hardware(Workshop_Inventory* inv) {
	int search_diam = 0;
	int found_any = 0; //Flag to check if we found at least 1 item

	printf("\n=== Search Harware ===\n");
	printf("Enter the target diameter to search for (mm): ");
	scanf("%d", &search_diam);

	printf("\n--- Results for %dmm Hardware ---\n", search_diam);

	//1. Search bolts
	for (int i = 0; i < inv->bolt_count; i++) {
		if (inv->bolt_stock[i].diameter == search_diam) {
			printf("[Bolt] M%d x %.1f | Length: %dmm | Quantity: %d\n",
				inv->bolt_stock[i].diameter,
				inv->bolt_stock[i].pitch,
				inv->bolt_stock[i].length,
				inv->bolt_stock[i].quantity);
			found_any = 1;
		}
	}

	//2. Search Nuts
	for (int i = 0; i < inv->nut_count; i++) {
		if (inv->nut_stock[i].inner_diameter == search_diam) {
			printf("[Nut] M%d x %.1f | Length: %dmm | Quantity: %d\n",
				inv->nut_stock[i].inner_diameter,
				inv->nut_stock[i].thread_pitch,
				inv->nut_stock[i].height,
				inv->nut_stock[i].quantity);
			found_any = 1;
		}
	}

	//3. Search Washers
	for (int i = 0; i < inv->washer_count; i++) {
		if (inv->washer_stock[i].hole == search_diam) {
			printf("[Washer] M%d x %.1f | Length: %dmm | Quantity: %d\n",
				inv->washer_stock[i].hole,
				inv->washer_stock[i].diameter,
				inv->washer_stock[i].thickness,
				inv->washer_stock[i].quantity);
			found_any = 1;
		}
	}

	//if no hardware matched
	if (!found_any) {
		printf("No hardware found with a %dmm diameter.\n", search_diam);
	}
}


