/*
CASE STUDY AOL
Nama	: Sheren Aura Vi Paramitha
NIM		: 2802444246
Class	: LA20
*/

#include <stdio.h>

struct Item {
	int id;
	char item_name[50];
	float price;
};

struct Supplier {
	int id;
	char supp_name[50];
	char phone_number[20];
};

struct Inventory {
	int item_id;
	int supp_id;
	int quantity;
};

void showMenu(int *inputMenu) {
	printf("What do you want to do?\n");
	printf("- Insert Record\n");
	printf("- Show Record\n");
	printf("- Select Data\n");
	printf("- Delete Record\n");
	printf("- Update Record\n");
	
	do {
		printf("Your choice: ");
		scanf("%d", inputMenu);
	} while(*inputMenu < 1 || *inputMenu > 5);
}

void insertItem(struct Item *items, int *itemCount) {
	do {
		printf("Enter item ID [!= 0]: ");
	    scanf("%d", &items[*itemCount].id);
	    getchar();
	} while(items[*itemCount].id == 0);

	do {
		printf("Enter item name [1..50]: ");
    	scanf("%49[^\n]", items[*itemCount].item_name);
    	getchar();
	} while(strlen(items[*itemCount].item_name) < 1 || strlen(items[*itemCount].item_name) > 50);

    printf("Enter item price: ");
    scanf("%f", &items[*itemCount].price);
    getchar();

    (*itemCount)++;  
    printf("Item added successfully!\n\n");
}

void insertSupplier(struct Supplier *suppliers, int *suppCount) {
    do {
        printf("Enter supplier ID [!= 0]: ");
        scanf("%d", &suppliers[*suppCount].id);
        getchar();  
    } while (suppliers[*suppCount].id == 0);

    do {
        printf("Enter supplier name [1..50]: ");
        scanf("%49[^\n]", suppliers[*suppCount].supp_name);
        getchar();  
    } while (strlen(suppliers[*suppCount].supp_name) < 1 || strlen(suppliers[*suppCount].supp_name) > 50);

    printf("Enter supplier's phone number: ");
    scanf("%19[^\n]", suppliers[*suppCount].phone_number);  

    (*suppCount)++;
    printf("Supplier added successfully!\n\n");
}

void insertInventory(struct Inventory *inventories, int *invenCount, struct Item *items, int itemCount, struct Supplier *suppliers, int suppCount) {
    int item_id, supp_id, quantity;
    int valid_item = 0, valid_supplier = 0;

    do {
        printf("Enter item ID: ");
        scanf("%d", &item_id);

        for (int i = 0; i < itemCount; i++) {
            if (items[i].id == item_id) {
                valid_item = 1;
                break;
            }
        }

        if (!valid_item) {
            printf("Item ID not found!\n");
        }
    } while (!valid_item);

    do {
        printf("Enter supplier ID: ");
        scanf("%d", &supp_id);

        for (int i = 0; i < suppCount; i++) {
            if (suppliers[i].id == supp_id) {
                valid_supplier = 1;
                break;
            }
        }

        if (!valid_supplier) {
            printf("Supplier ID not found!\n");
        }
    } while (!valid_supplier);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    inventories[*invenCount].item_id = item_id;
    inventories[*invenCount].supp_id = supp_id;
    inventories[*invenCount].quantity = quantity;

    (*invenCount)++;
    printf("Inventory record added successfully!\n\n");
}

void showRecords(struct Item *items, int itemCount, struct Supplier *suppliers, int suppCount, struct Inventory *inventories, int invenCount) {
	if(itemCount == 0) {
		printf("There's no item. Input first!\n\n");
	} else {
	    printf("----------------------------------------------------------------------------------\n");
	    printf("ITEM_ID   SUPPLIER_ID   ITEM_NAME        PRICE       QUANTITY      SALES\n");
	    printf("----------------------------------------------------------------------------------\n");
	
		int total_qty = 0;
	    float total_sales = 0.0;
	    
	    for (int i = 0; i < invenCount; i++) {
	        int item_index = -1, supp_index = -1;
	
	        for (int j = 0; j < itemCount; j++) {
	            if (items[j].id == inventories[i].item_id) {
	                item_index = j;
	                break;
	            }
	        }
	
	        for (int k = 0; k < suppCount; k++) {
	            if (suppliers[k].id == inventories[i].supp_id) {
	                supp_index = k;
	                break;
	            }
	        }
	
	        if (item_index != -1 && supp_index != -1) {
	        	float sales = items[item_index].price * inventories[i].quantity; 
	            total_qty += inventories[i].quantity;                          
	            total_sales += sales;
	        	
	            printf("A%-9dS%-13d%-17s%-15.2f%-11d%-10.2f\n",
	                   items[item_index].id,
	                   suppliers[supp_index].id,
	                   items[item_index].item_name,
	                   items[item_index].price,
	                   inventories[i].quantity,
	                   items[item_index].price * inventories[i].quantity);
	        }
	    }
	    
	    printf("----------------------------------------------------------------------------------\n");
	    printf("Grand Total\t\t\t\t\t\t%-11d%.2f\n\n", total_qty, total_sales);
	}
}

void selectRecords(struct Item *items, int itemCount, struct Supplier *suppliers, int suppCount, struct Inventory *inventories, int invenCount) {
    int search_id;

    printf("Enter item ID to search [A followed by number, e.g., A1]: ");
    scanf("%d", &search_id);

    for (int i = 0; i < invenCount; i++) {
        if (inventories[i].item_id == search_id) {
            int item_index = -1, supp_index = -1;

            for (int j = 0; j < itemCount; j++) {
                if (items[j].id == inventories[i].item_id) {
                    item_index = j;
                    break;
                }
            }

            for (int k = 0; k < suppCount; k++) {
                if (suppliers[k].id == inventories[i].supp_id) {
                    supp_index = k;
                    break;
                }
            }

            if (item_index != -1 && supp_index != -1) {
                printf("Item found:\n");
                printf("----------------------------------------------------------------------------------\n");
                printf("ITEM_ID   SUPPLIER_ID   ITEM_NAME        PRICE       QUANTITY      SALES\n");
                printf("----------------------------------------------------------------------------------\n");
                printf("A%-9dS%-13d%-17s%-15.2f%-11d%-10.2f\n",
                       items[item_index].id,
                       suppliers[supp_index].id,
                       items[item_index].item_name,
                       items[item_index].price,
                       inventories[i].quantity,
                       items[item_index].price * inventories[i].quantity);
                printf("----------------------------------------------------------------------------------\n\n");
                return;
            }
        }
    }

    printf("Item with ID A%d not found!\n", search_id);
}

void deleteRecords(struct Item *items, int *itemCount, struct Supplier *suppliers, int *suppCount, struct Inventory *inventories, int *invenCount) {
    int delete_id;
    int found = 0;

    printf("Enter item ID to delete [A followed by number, e.g., A1]: ");
    scanf("%d", &delete_id);

    for (int i = 0; i < *invenCount; i++) {
        if (inventories[i].item_id == delete_id) {
            found = 1;
            for (int j = i; j < *invenCount - 1; j++) {
                inventories[j] = inventories[j + 1];
            }
            (*invenCount)--;  
            printf("Inventory record with item ID A%d deleted successfully!\n\n", delete_id);
            break;
        }
    }

    if (found) {
        for (int i = 0; i < *itemCount; i++) {
            if (items[i].id == delete_id) {
                for (int j = i; j < *itemCount - 1; j++) {
                    items[j] = items[j + 1];
                }
                (*itemCount)--;  
                break;
            }
        }
        
        for (int k = 0; k < *suppCount; k++) {
            if (suppliers[k].id == delete_id) {
                for (int l = k; l < *suppCount - 1; l++) {
                    suppliers[l] = suppliers[l + 1];
                }
                (*suppCount)--;  
                break;
            }
        }
        
    } else {
        printf("Item with ID A%d not found in inventory!\n\n", delete_id);
    }
}

void updateItem(struct Item *items, int itemCount) {
    int update_id;
    printf("Enter item ID to update [A followed by number, e.g., A1]: ");
    scanf("%d", &update_id);
    getchar();

    int item_index = -1;
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == update_id) {
            item_index = i;
            break;
        }
    }

    if (item_index != -1) {
        printf("Enter new item name [1..50]: ");
        scanf("%49[^\n]", items[item_index].item_name);
        getchar();

        printf("Enter new item price: ");
        scanf("%f", &items[item_index].price);
        getchar();

        printf("Item updated successfully!\n\n");
    } else {
        printf("Item with ID A%d not found!\n\n", update_id);
    }
}

void updateSupplier(struct Supplier *suppliers, int suppCount) {
    int update_id;
    printf("Enter supplier ID to update [S followed by number, e.g., S1]: ");
    scanf("%d", &update_id);

    int supp_index = -1;
    for (int i = 0; i < suppCount; i++) {
        if (suppliers[i].id == update_id) {
            supp_index = i;
            break;
        }
    }

    if (supp_index != -1) {
        printf("Enter new supplier name [1..50]: ");
        scanf("%49[^\n]", suppliers[supp_index].supp_name);
        getchar();

        printf("Enter new supplier phone number: ");
        scanf("%19[^\n]", suppliers[supp_index].phone_number);

        printf("Supplier updated successfully!\n\n");
    } else {
        printf("Supplier with ID S%d not found!\n\n", update_id);
    }
}

void updateInventory(struct Inventory *inventories, int invenCount, struct Item *items, int itemCount, struct Supplier *suppliers, int suppCount) {
    int update_id;
    printf("Enter inventory item ID to update [A followed by number, e.g., A1]: ");
    scanf("%d", &update_id);

    int inven_index = -1;
    for (int i = 0; i < invenCount; i++) {
        if (inventories[i].item_id == update_id) {
            inven_index = i;
            break;
        }
    }

    if (inven_index != -1) {
        printf("Enter new quantity: ");
        scanf("%d", &inventories[inven_index].quantity);

        printf("Inventory updated successfully!\n\n");
    } else {
        printf("Inventory with item ID A%d not found!\n\n", update_id);
    }
}

void updateRecord(struct Item *items, int itemCount, struct Supplier *suppliers, int suppCount, struct Inventory *inventories, int invenCount) {
    int choice;
    printf("What do you want to update?\n");
    printf("1. Update Item\n");
    printf("2. Update Supplier\n");
    printf("3. Update Inventory\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            updateItem(items, itemCount);   // Update Item
            break;
        case 2:
            updateSupplier(suppliers, suppCount);    // Update Supplier
            break;
        case 3:
            updateInventory(inventories, invenCount, items, itemCount, suppliers, suppCount); // Update Inventory
            break;
        default:
            printf("Invalid choice!\n\n");
            break;
    }
}



int main() {
	struct Item items[100];
	struct Supplier suppliers[100];
	struct Inventory inventories[100];
	
	int inputMenu;
	int itemCount = 0, suppCount = 0, invenCount = 0;
	
	printf("INVENTORY SYSTEM\n");
	printf("INVENTORY DATA MAIN MENU\n\n");
	
	while(1) {
		showMenu(&inputMenu);
		printf("\n");
		
		switch(inputMenu) {
			case 1:
                insertItem(items, &itemCount);
                insertSupplier(suppliers, &suppCount);
                insertInventory(inventories, &invenCount, items, itemCount, suppliers, suppCount);
                break;
				
			case 2: 
				showRecords(items, itemCount, suppliers, suppCount, inventories, invenCount);
				break;
				
			case 3:
				selectRecords(items, itemCount, suppliers, suppCount, inventories, invenCount);
				break;
			
			case 4: 
				deleteRecords(items, &itemCount, suppliers, &suppCount, inventories, &invenCount);
				break;
				
			case 5:
                updateRecord(items, itemCount, suppliers, suppCount, inventories, invenCount);
				break;
		}
	}	
}


