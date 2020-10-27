#include <stdio.h>
#include <Windows.h>

// Used to get around that array initalizations cannot use variables
#define array_len 100

/**
 * Written by Caleb Shilling
 * Linn Benton, CS 133C
 * 10-27-2020
 * 
 * This project details how to work with arrays using loops. The inital array
 * is initalized at a set value, and each position in the array is equal to
 * the position plus the starting number. This array is then split into
 * two arrays of half length, then every third element of both new arrays
 * are swapped.
**/ 

void printArray(int * array, int len){
    /**
     * printArray(int * array, int len)
     * 
     * Prints an array to a length specified. The array can be of
     * any length. len is expected to at least equal the length
     * of the array.
    **/ 
    for(int i = 0; i < len; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void main(){

    int array_start = 5;
    int sum = 0;
    int array[array_len];
    int array_1[array_len/2];
    int array_2[array_len/2];
    int stored_1 = 0;
    int stored_2 = 0;
    
    // Add values to the array.
    for(int i = 0; i < array_len; i++){
        array[i] = i + array_start;
    }

    // Calculate the sum of all values in the array.
    for(int i = 0; i < array_len; i++){
        sum = sum + array[i];
    }
    printf("Sum of the array: %d\n", sum);
    printf("Average of the array: %d\n", sum/array_len);
    
    // Copy each half of the inital array into two seperate arrays
    for(int i = 0; i < array_len/2; i++){
        array_1[i] = array[i];
        array_2[i] = array[i+array_len/2];
    }

    printf("\nArray 1 split into Arrays 1 and 2:\n");
    printArray(array_1, array_len/2);
    printArray(array_2, array_len/2);

    // Swap the third elements of each array
    for(int i = 2; i < array_len/2; i = i + 3){
        stored_1 = array_1[i];
        stored_2 = array_2[i];
        array_1[i] = stored_2;
        array_2[i] = stored_1;
    }

    printf("\nThird element swapped in Arrays 1 and 2:\n");
    printArray(array_1, array_len/2);
    printArray(array_2, array_len/2);

    scanf("%d", &sum);
}