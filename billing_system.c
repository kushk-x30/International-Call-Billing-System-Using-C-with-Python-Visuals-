#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Customer {
    char name[50];
    char phone[16];
    float usage;
    float bill;
};

struct Customer customers[100];
int count = 0;

void printLine(char ch, int length) {
    for (int i = 0; i < length; i++) printf("%c", ch);
    printf("\n");
}

float getInternationalRate(char *phone) {
    if (strncmp(phone, "+91", 3) == 0) return 0.10;
    if (strncmp(phone, "+1", 2) == 0) return 7.00;
    if (strncmp(phone, "+44", 3) == 0) return 8.50;
    if (strncmp(phone, "+61", 3) == 0) return 9.00;
    if (strncmp(phone, "+81", 3) == 0) return 10.00;
    if (strncmp(phone, "+49", 3) == 0) return 8.00;
    return 12.00;
}

const char* getUserType(float usage) {
    if (usage < 100) return "Very Low";
    else if (usage <= 300) return "Low";
    else if (usage <= 500) return "Moderate";
    else if (usage <= 1000) return "High";
    else return "Very High";
}

int isValidPhone(char phone[]) {
    if (phone[0] != '+') return 0;
    int len = strlen(phone);
    if (len < 4 || len > 15) return 0;
    for (int i = 1; i < len; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

void addCustomer() {
    if (count >= 100) {
        printf("List full.\n");
        return;
    }

    printf("Enter Name: ");
    getchar();
    fgets(customers[count].name, sizeof(customers[count].name), stdin);
    customers[count].name[strcspn(customers[count].name, "\n")] = '\0';

    char phone[16];
    printf("Enter Phone (+CCXXXXXXXXXX): ");
    scanf("%s", phone);

    if (!isValidPhone(phone)) {
        printf("Invalid phone.\n");
        return;
    }

    strcpy(customers[count].phone, phone);
    printf("Enter Usage (minutes): ");
    scanf("%f", &customers[count].usage);

    float rate = getInternationalRate(phone);
    customers[count].bill = customers[count].usage * rate;

    count++;
    printf("Customer added successfully.\n");
}

void viewCustomers() {
    if (count == 0) {
        printf("No customers to show.\n");
        return;
    }

    printLine('-', 70);
    printf("%-20s %-15s %-8s %-10s %-12s\n", "Name", "Phone", "Usage", "Bill", "UserType");
    printLine('-', 70);
    for (int i = 0; i < count; i++) {
        printf("%-20s %-15s %-8.1f Rs%-9.2f %-12s\n",
               customers[i].name,
               customers[i].phone,
               customers[i].usage,
               customers[i].bill,
               getUserType(customers[i].usage));
    }
    printLine('-', 70);
}

void searchCustomer() {
    char phone[16];
    printf("Enter phone number to search: ");
    scanf("%s", phone);

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            printf("\nCustomer Found:\n");
            printf("Name      : %s\n", customers[i].name);
            printf("Phone     : %s\n", customers[i].phone);
            printf("Usage     : %.1f mins\n", customers[i].usage);
            printf("Bill      : Rs%.2f\n", customers[i].bill);
            printf("User Type : %s\n", getUserType(customers[i].usage));
            return;
        }
    }
    printf("Customer not found.\n");
}

void modifyRecord() {
    char phone[16];
    printf("Enter phone number to modify: ");
    scanf("%s", phone);

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            printf("Are you sure you want to modify usage for %s? (y/n): ", customers[i].name);
            char confirm;
            scanf(" %c", &confirm);
            if (confirm != 'y' && confirm != 'Y') {
                printf("Modification cancelled.\n");
                return;
            }

            printf("Enter new usage (minutes): ");
            scanf("%f", &customers[i].usage);
            customers[i].bill = customers[i].usage * getInternationalRate(phone);
            printf("Record updated.\n");
            return;
        }
    }
    printf("Customer not found.\n");
}

void deleteRecord() {
    char phone[16];
    printf("Enter phone number to delete: ");
    scanf("%s", phone);

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            printf("Are you sure you want to delete %s? (y/n): ", customers[i].name);
            char confirm;
            scanf(" %c", &confirm);
            if (confirm != 'y' && confirm != 'Y') {
                printf("Deletion cancelled.\n");
                return;
            }

            for (int j = i; j < count - 1; j++) {
                customers[j] = customers[j + 1];
            }
            count--;
            printf("Record deleted.\n");
            return;
        }
    }
    printf("Customer not found.\n");
}

void saveToCSV() {
    FILE *fp = fopen("customers.csv", "w");
    if (fp == NULL) {
        printf("Error writing file.\n");
        return;
    }

    fprintf(fp, "Name,Phone,Usage,Bill_INR,User_Type\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%.1f,%.2f,%s\n",
                customers[i].name,
                customers[i].phone,
                customers[i].usage,
                customers[i].bill,
                getUserType(customers[i].usage));
    }

    fclose(fp);
    printf("Data saved to customers.csv (%d records)\n", count);
}

void showStatistics() {
    if (count == 0) {
        printf("No customers to analyze.\n");
        return;
    }

    float totalUsage = 0, totalBill = 0;
    int highestIndex = 0;
    for (int i = 0; i < count; i++) {
        totalUsage += customers[i].usage;
        totalBill += customers[i].bill;
        if (customers[i].bill > customers[highestIndex].bill)
            highestIndex = i;
    }

    printf("\nCustomer Statistics\n");
    printLine('-', 30);
    printf("Total Customers : %d\n", count);
    printf("Average Usage   : %.2f mins\n", totalUsage / count);
    printf("Average Bill    : Rs%.2f\n", totalBill / count);
    printf("Top Customer    : %s (Rs%.2f)\n", customers[highestIndex].name, customers[highestIndex].bill);
    printLine('-', 30);
}

int compareByName(const void *a, const void *b) {
    return strcmp(((struct Customer*)a)->name, ((struct Customer*)b)->name);
}

int compareByUsage(const void *a, const void *b) {
    float ua = ((struct Customer*)a)->usage;
    float ub = ((struct Customer*)b)->usage;
    return (ub > ua) - (ub < ua);
}

void sortCustomers() {
    int option;
    printf("Sort by:\n1. Name (A-Z)\n2. Usage (High to Low)\nChoice: ");
    scanf("%d", &option);

    if (option == 1) {
        qsort(customers, count, sizeof(struct Customer), compareByName);
        printf("Sorted by name.\n");
    } else if (option == 2) {
        qsort(customers, count, sizeof(struct Customer), compareByUsage);
        printf("Sorted by usage.\n");
    } else {
        printf("Invalid option.\n");
    }
}

void exportSingleCustomer() {
    char phone[16];
    printf("Enter phone number to export: ");
    scanf("%s", phone);

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            char filename[100];
            sprintf(filename, "customer_%s.txt", customers[i].phone + 1);

            FILE *fp = fopen(filename, "w");
            if (!fp) {
                printf("Failed to write file.\n");
                return;
            }

            fprintf(fp, "Name      : %s\n", customers[i].name);
            fprintf(fp, "Phone     : %s\n", customers[i].phone);
            fprintf(fp, "Usage     : %.1f mins\n", customers[i].usage);
            fprintf(fp, "Bill      : Rs%.2f\n", customers[i].bill);
            fprintf(fp, "User Type : %s\n", getUserType(customers[i].usage));
            fclose(fp);

            printf("Exported to %s\n", filename);
            return;
        }
    }

    printf("Customer not found.\n");
}

int main() {
    printf("============================================\n");
    printf("|                                          |\n");
    printf("|       WELCOME TO BILLING SYSTEM          |\n");
    printf("|__________________________________________|\n");
    printf("|                                          |\n");
    printf("|     Track & Manage International Calls   |\n");
    printf("|__________________________________________|\n");

    int choice;
    while (1) {
        printf("\n============================================\n");
        printf("|                 MAIN MENU                |\n");
        printf("============================================\n");
        printf("| 1.  Add Customer                         |\n");
        printf("| 2.  View All Customers                   |\n");
        printf("| 3.  Search Customer                      |\n");
        printf("| 4.  Modify Record                        |\n");
        printf("| 5.  Delete Record                        |\n");
        printf("| 6.  Save to CSV File                     |\n");
        printf("| 7.  Show Graph                           |\n");
        printf("| 8.  Show Statistics                      |\n");
        printf("| 9.  Sort Customers                       |\n");
        printf("| 10. Export Single Customer               |\n");
        printf("| 11. Exit                                 |\n");
        printf("============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: searchCustomer(); break;
            case 4: modifyRecord(); break;
            case 5: deleteRecord(); break;
            case 6: saveToCSV(); break;
            case 7: saveToCSV(); system("python analyze_customers.py"); break;
            case 8: showStatistics(); break;
            case 9: sortCustomers(); break;
            case 10: exportSingleCustomer(); break;
            case 11:
                printf("\n============================================\n");
                printf("|      Thank you for using the system!     |\n");
                printf("|     Made with love by Group-12:)         |\n");
                printf("============================================\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
