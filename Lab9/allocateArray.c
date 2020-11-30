#include <stdio.h>
#include <malloc.h>
#include <string.h>

int lineCounter(FILE* fp){
    // Create a line-holding variable and rewind to top of file.
    int lines = 1;
    rewind(fp);

    // Go character by character looking for newline characters.
    for(char c = fgetc(fp); c != EOF; c = fgetc(fp)){
        if(c == '\n'){
            lines = lines + 1;     
        }
    }
    // Go back to top of file and output number of lines in file.
    rewind(fp);
    return lines;
}

int** squareArray(int size){
    /* Create a pointer of n pointers, then fill each 
       pointer with n pointers. */

    // Create a pointer of pointers and fill the first layer with pointers.
    int **array;
    array = malloc(size * sizeof(int *));

    // Assign each pointer to an int pointer.
    for(int i = 0; i < size; i++){
        *(array + i) =  malloc(size * sizeof(int));
    }

    // Return the pointer of pointers.
    return array;
}

void fillPointerArray(FILE* fp, int** arr, int size){
    /* Iterate through the file placing each new read integer into the
       appropriate pointer-of-pointers location. */

    int data;
    rewind(fp);

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            data = 0;
            // Scan for the next integer.
            fscanf(fp, "%d", &data);
            // Set the target pointer to the scanned integer.
            *(*(arr + i)+j) = data;
        }  
    }
    rewind(fp);
}

void doubleArray(int** inputArray, int** outputArray, int size){
    /* Take every position in inputArray, multiply it by 2, then
       place it in outputArray. */

    int data;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            data = *(*(inputArray + i)+j) * 2;
            *(*(outputArray + i)+j) = data;
        }  
    }

}

void multiplyArrays(int** inputArray1, int** inputArray2, int** outputArray, int size){
    /* How to multiply arrays can be found here:
       https://www.mathsisfun.com/algebra/matrix-multiplying.html
       For each position on the n x n matrices, follow the instructions at the link
       above. */

    int data;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){

            data = 0;

            for(int k = 0; k < size; k++){
                data = data + *(*(inputArray1 + i)+k) * *(*(inputArray2 + k)+j);
            }
            
            *(*(outputArray + i)+j) = data;
        }  
    }

}

void displayArray(int** array, int size){
    /* Display the array by printing n values out on n lines.
       Add extra spaces based on how many fewer places the printed
       valye has. */

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){

            printf("%d   ", *(*(array + i)+j));
            if(*(*(array + i)+j) < 10){
                printf(" ");
            }
            if(*(*(array + i)+j) < 100){
                printf(" ");
            }
            
        }  

        printf("\n");
    }
}

void main(){

    // Array 1:
    FILE* fp;
    fp = fopen("arr1.txt", "r");
    int arraySize = lineCounter(fp);
    int **initalArray = squareArray(arraySize);
    int **doubledArray = squareArray(arraySize);
    int **multipliedArray = squareArray(arraySize);

    fillPointerArray(fp, initalArray, arraySize);
    printf("Array 1 Initial Array:\n");
    displayArray(initalArray, arraySize);
    doubleArray(initalArray, doubledArray, arraySize);
    printf("\nArray 1 Doubled Array:\n");
    displayArray(doubledArray, arraySize);
    multiplyArrays(initalArray, doubledArray, multipliedArray, arraySize);
    printf("\nArray 1 Multiplied Array:\n");
    displayArray(multipliedArray, arraySize);

    // Array 2:  
    fp = fopen("arr2.txt", "r");
    arraySize = lineCounter(fp);
    initalArray = squareArray(arraySize);
    doubledArray = squareArray(arraySize);
    multipliedArray = squareArray(arraySize);

    fillPointerArray(fp, initalArray, arraySize);
    printf("\nArray 2 Initial Array:\n");
    displayArray(initalArray, arraySize);
    doubleArray(initalArray, doubledArray, arraySize);
    printf("\nArray 2 Doubled Array:\n");
    displayArray(doubledArray, arraySize);
    multiplyArrays(initalArray, doubledArray, multipliedArray, arraySize);
    printf("\nArray 2 Multiplied Array:\n");
    displayArray(multipliedArray, arraySize);

    // Array 3:  
    fp = fopen("arr3.txt", "r");
    arraySize = lineCounter(fp);
    initalArray = squareArray(arraySize);
    doubledArray = squareArray(arraySize);
    multipliedArray = squareArray(arraySize);

    fillPointerArray(fp, initalArray, arraySize);
    printf("\nArray 3 Initial Array:\n");
    displayArray(initalArray, arraySize);
    doubleArray(initalArray, doubledArray, arraySize);
    printf("\nArray 3 Doubled Array:\n");
    displayArray(doubledArray, arraySize);
    multiplyArrays(initalArray, doubledArray, multipliedArray, arraySize);
    printf("\nArray 3 Multiplied Array:\n");
    displayArray(multipliedArray, arraySize);
    
    free(initalArray);
    free(doubledArray);
    free(multipliedArray);

}