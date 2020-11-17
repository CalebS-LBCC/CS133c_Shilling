#include <stdio.h>
#include <time.h>
#include "string.h"

/**
 * Written by Caleb Shilling
 * Last edited 11-16-20
 * LBCC CS 133C
 * 
 * supply.c
 * This program takes a list of products and companies as an input,
 * then provides a purchasing interface for users to simulate buying.
 * Once the user performs a legal transaction, the program will decrement
 * the amount of stock left and update the file while outputing a transaction
 * list in another file.
**/ 

struct Supplier
{
    int id;
    char name[32];
    char state[32];
    int phone[32];
    char address[32];
};

struct Product
{
    int product_id;
    char name[32];
    char company_name[32];
    int company_id;
    int cost;
    int stock; 
};

void main(){
    // Load in the suppliers' data.
    int total_suppliers = 0;
    struct Supplier suppliers[32];
    char customer_name[] = "Caleb Shilling";

    FILE* fp;
    fp = fopen("suppliers.txt", "r");
    fseek(fp, 0, 0);

    for(int i = 0; fscanf(fp, "%d %s %s %d %s\n", &suppliers[i].id, &suppliers[i].name,
        &suppliers[i].state, &suppliers[i].phone, &suppliers[i].address) != EOF; i++){
        total_suppliers = i;
    }

    fclose(fp);

    
    struct Product products[32];
    int total_products = 0;

    // Read in the list of products.
    fp = fopen("products.txt", "r");
    fseek(fp, 0, 0);

    for(int i = 0; fscanf(fp, "%d %s %d %d %d\n", &products[i].product_id, &products[i].name,
        &products[i].company_id, &products[i].cost, &products[i].stock) != EOF; i++){
        total_products = i;

        // Scan the supplier list for the accompaning company then add it to the product
        // information.
        for(int j = 0; j <= total_suppliers; j++){
            if(products[i].company_id == suppliers[j].id){
                strcpy(products[i].company_name, suppliers[j].name);
            }
        }
    }

    fclose(fp);

    int running = 1;
    while(running){

        // Output all products with some associated information.
        printf("Product Name, Product ID, Company Name, Price");
        for(int i = 0; i <= total_products; i++){
            printf("\n%s, %d, %s, %d", products[i].name, products[i].product_id,
                products[i].company_name, products[i].cost);
        }

        // Loop until a valid product ID has been given, then record the
        // location of that ID.
        int selection = 0;
        int location = 0;
        int selected = 0;
        while(!selected){
            printf("\nPlease enter a product ID to purchase. Enter 0 to end the program.\n");
            scanf("%d", &selection);
            if(selection == 0){
                running = 0;
                continue;
            }
            for(int i = 0; i <= total_products; i++){
                if(products[i].product_id == selection){
                    selected = 1;
                    location = i;
                }
            }
        }

        // Input the amount the user wants to purchase.
        int amount = 0;
        printf("Please enter an amount to purchase.\n");
        scanf("%d", &amount);
        
        // If the program hasn't ran out of stock, update the in-program
        // values and the data in the file.
        int total = products[location].stock;
        if(total - amount >= 0){
            products[location].stock = total - amount;
            fp = fopen("products.txt", "w+");
            for(int i = 0; i <= total_products; i++){
                fprintf(fp, "%d %s %d %d %d\n", products[i].product_id, products[i].name,
                    products[i].company_id, products[i].cost, products[i].stock);
            }
            fclose(fp);

            // Date code from https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            // Append the orders file with the latest transaction.
            fp = fopen("orders.txt", "a");
            fprintf(fp, "%s, %s, %s, %d-%02d-%02d, %d, %d, %d\n", products[location].name,
                products[location].company_name, customer_name, tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, amount, products[location].cost,
                products[location].cost * amount);
            fclose(fp);

        }else{
            printf("Unable to fill the order.\n");
        }
    }
}