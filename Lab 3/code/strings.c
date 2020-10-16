#include <stdio.h>
#include <string.h>
#include <Windows.h>

void printNormal(char string[]){
    /**
     * printNormal(char[])
     * 
     * This function takes one string input. Once this happens, a for loop
     * iterates over the string and prints each character one after another
     * on a single line.
    **/
    printf("Printing normally:\n");
    int len = strlen(string);
    for(int item = 0; item < len; item++){
        printf("%c",string[item]);
    }
}

void printReverse(char string[]){ 
    /**
     * printReverse(char[])
     * 
     * This function takes one string input. Once this happens, a for loop
     * iterates over the string in reverse and prints each character in the
     * string one after another on a single line.
    **/
    printf("Printing reverse:\n");
    int len = strlen(string);
    for(int item = 0; item < len; item++){
        printf("%c",string[len-item-1]);
    }
}

void main(){

    // Have the user input a string and put it in a string variable.
    printf("Input a string:\n");
    char string[100];
    scanf("%s", string);

    // Run both print functions.
    printNormal(string);
    printf("\n");
    printReverse(string);
    
    // Wait for 10 seconds before closing the program.
    Sleep(10000);
}