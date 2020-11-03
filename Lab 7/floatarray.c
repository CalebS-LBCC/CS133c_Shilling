#include <stdio.h>
#include <Windows.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>

#define size 20

void sortFloatAscending(float *array, int length){
    /**
     * sortFloatAscending(float *array, int length) 
     * 
     * Grab a pointer from the input array and iterate through the array.
     * For every value n in the array, swap it for the nth lowest by omitting
     * the values already iterated upon.
    **/ 

    float* pointer;
    pointer = array;

    for(int i=0; i<length; i++){
        // Record the starting value and iterate over the array,
        // overwriting this value if a smaller number is found.
        float* lowestValue = pointer+i;
        for(int j = i; j < length; j++){
            if(*(pointer+j) < *lowestValue){
                lowestValue = pointer+j;
            }
        }
        // If the lowest value is the current pointer, don't swap.
        // If the lowest value has been changed, swap the current
        // pointer value and the new lowest value.
        if(lowestValue != pointer+i){
            float storedValue = *(pointer+i);
            float storedLow = *lowestValue;
            *(pointer+i) = storedLow;
            *lowestValue = storedValue;
        }
    }
}

void sortFloatDescending(float *array, int length){
    /**
     * sortFloatDescending(float *array, int length) 
     * 
     * Grab a pointer from the input array and iterate through the array.
     * For every value n in the array, swap it for the nth highest by omitting
     * the values already iterated upon.
    **/ 

    float* pointer;
    pointer = array;

    for(int i=0; i<length; i++){
        // Record the starting value and iterate over the array,
        // overwriting this value if a highest number is found.
        float* highestValue = pointer+i;
        for(int j = i; j < length; j++){
            if(*(pointer+j) > *highestValue){
                highestValue = pointer+j;
            }
        }
        // If the highest value is the current pointer, don't swap.
        // If the highest value has been changed, swap the current
        // pointer value and the new lowest value.
        if(highestValue != pointer+i){
            float storedValue = *(pointer+i);
            float storedHigh = *highestValue;
            *(pointer+i) = storedHigh;
            *highestValue = storedValue;
        }
    }
}

void printArray(float *array, int length){
    /**
     * printArray(float *array, int length)
     * 
     * Print a float array using a for loop.
    **/ 
    for(int i=0; i<length; i++){
        printf("%f\n", array[i]);
    }
}

void main(){
    float array[size] = {6.73, 1.062, 10.6892, 20.9, 37, 94.1, 37.5, 92.1, 21.11, 21.22, 37.9, 111.11, 3.21, 31.4, 2.56, 5.11, 67.88, 13.3, 12, 17.2};
    float* ptr;
    ptr = array;

    printf("Printing array without sort:\n");
    printArray(array, size);
    printf("\nPrinting array with ascending sort:\n");
    sortFloatAscending(array, size);
    printArray(array, size);
    printf("\nPrinting array with descending sort:\n");
    sortFloatDescending(array, size);
    printArray(array, size);
    
    Sleep(100000);
}