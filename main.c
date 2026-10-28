
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int price;
    int stock;
} Product;

typedef struct {
    char name[50];
    int points;
} Member;

void showProducts(Product products[], int size) {
    printf("\n--- PRODUCT CATALOG ---\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - Rp%d (Stock: %d)\n",
               i + 1, products[i].name,
               products[i].price, products[i].stock);
    }
}

void showMembers(Member members[], int size) {
    printf("\n--- MEMBER DATA ---\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - Points: %d\n",
               i + 1, members[i].name, members[i].points);
    }
}

void updatePrice(Product *p, int newPrice) {
    if (newPrice <= 0) {
        printf("Price must be greater than zero.\n");
        return;
    }
    p->price = newPrice;
    printf("Product price updated successfully!\n");
}

void updateName(Product *p, char newName[]) {
    if (strlen(newName) == 0) {
        printf("Product name cannot be empty.\n");
        return;
    }
    strcpy(p->name, newName);
    printf("Product name updated successfully!\n");
}

void buyProduct(Product *p, Member *m, int qty) {
    if (qty <= 0) {
        printf("Quantity must be greater than zero.\n");
        return;
    }

    if (p->stock < qty) {
        printf("[FAILED] Insufficient stock for %s!\n", p->name);
        return;
    }

    int total = p->price * qty;

    if (m != NULL && m->points >= 1000) {
        m->points -= 1000;
        total = total * 90 / 100;
        printf("1000 points redeemed! 10%% discount applied.\n");
    }

    p->stock -= qty;

    printf("\n[TRANSACTION SUCCESSFUL]\n");
    printf("Product: %s\n", p->name);
    printf("Quantity: %d\n", qty);
    printf("Total payment: Rp%d\n", total);

    if (m != NULL && total >= 20000) {
        m->points += 100;
        printf("%s earned 100 points!\n", m->name);
    }
}

int main(void) {
    Product products[5] = {
        {"Soap", 5000, 10},
        {"Shampoo", 15000, 5},
        {"Bread", 12000, 8},
        {"Milk", 25000, 15},
        {"Coffee", 22000, 20}
    };

    Member members[2] = {
        {"Anisa", 500},
        {"Budi", 100}
    };

    int choice;

    do {
        printf("\n===== MINIMARKET CLI APP =====\n");
        printf("1. View Products\n");
        printf("2. Buy Product\n");
        printf("3. View Members\n");
        printf("4. Update Product Price\n");
        printf("5. Update Product Name\n");
        printf("6. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Enter a number.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                showProducts(products, 5);
                break;

            case 2: {
                int productChoice, memberChoice, qty;

                showProducts(products, 5);
                printf("Choose product number: ");
                if (scanf("%d", &productChoice) != 1) {
                    printf("Invalid input.\n");
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }

                if (productChoice < 1 || productChoice > 5) {
                    printf("Invalid product number.\n");
                    break;
                }

                printf("Enter quantity: ");
                if (scanf("%d", &qty) != 1) {
                    printf("Invalid input.\n");
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }

                printf("Member (1. Anisa, 2. Budi, 0. Non-member): ");
                if (scanf("%d", &memberChoice) != 1) {
                    printf("Invalid input.\n");
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }

                if (memberChoice == 0) {
                    buyProduct(&products[productChoice - 1], NULL, qty);
                } else if (memberChoice >= 1 && memberChoice <= 2) {
                    buyProduct(&products[productChoice - 1],
                               &members[memberChoice - 1], qty);
                } else {
                    printf("Invalid member choice.\n");
                }
                break;
            }

            case 3:
                showMembers(members, 2);
                break;

            case 4: {
                int productChoice, newPrice;
                showProducts(products, 5);
                printf("Choose product number: ");

                if (scanf("%d", &productChoice) != 1) {
                    printf("Invalid input.\n");
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }

                if (productChoice < 1 || productChoice > 5) {
                    printf("Invalid product number.\n");
                    break;
                }

                printf("Enter new price: ");
                if (scanf("%d", &newPrice) != 1) {
                    printf("Invalid input.\n");
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }

                updatePrice(&products[productChoice - 1], newPrice);
                break;
            }

            case 5: {
                int productChoice;
                char newName[50];

                showProducts(products, 5);
                printf("Choose product number: ");

                if (scanf("%d", &productChoice) != 1) {
                    printf("Invalid input.\n");
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }

                if (productChoice < 1 || productChoice > 5) {
                    printf("Invalid product number.\n");
                    break;
                }

                printf("Enter new product name (one word): ");
                if (scanf("%49s", newName) != 1) {
                    printf("Invalid input.\n");
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }

                updateName(&products[productChoice - 1], newName);
                break;
            }

            case 6:
                printf("Thank you for using Minimarket CLI App!\n");
                break;

            default:
                printf("Invalid option. Choose 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}
