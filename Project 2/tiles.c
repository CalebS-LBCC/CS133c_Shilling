#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>

/**
 * Written by Caleb Shilling
 * 11-16-2020
 * LBCC CS 133C
**/ 

void main(){

    srand(time(0));

    // Fill the array and create a pointer to it.
    int full_array[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int *fa = full_array;

    // Using our seeded random number, swap values inside the array
    // to generate a pseudo-random distribution
    for(int i = 0; i <= 15; i++){
        int value_to_swap = rand() % 16;

        if(i != value_to_swap){
            int current_value = *(fa + i);
            int swap_value = *(fa + value_to_swap);
            *(fa + i) = swap_value;
            *(fa + value_to_swap) = current_value;
        }
    }

    int space_x = 0;
    int space_y = 0;
    int move = 0;
    bool won = false;

    // Repeat until game is won.
    while(!won){
        // Display the board.
        for(int y = 0; y != 4; y++){
            for(int x = 0; x!= 4; x++){

                int value = *(fa + y*4 + x);
                
                if(value < 10){
                    // Provide an extra space in front of the number if it is smaller than 10.
                    printf("  %d ", value);
                }else if(value == 16){
                    // If number is 16, replace it with a space and record its location.
                    space_x = x;
                    space_y = y;
                    printf("    ");
                }else{
                    printf(" %d ", value);
                }
                
            }
            printf("\n");
        }

        // Record the user's input.
        printf("What number should be moved?\n");
        scanf("%d", &move);

        // Check if the current space has a specified position next to it, then check if the numbers
        // are the same.
        bool left_legal = (space_x != 0 && move == *(fa + space_y*4 + space_x - 1));
        if(left_legal){
            *(fa + space_y*4 + space_x - 1) = 16;
            *(fa + space_y*4 + space_x) = move;
        }

        bool right_legal = (space_x != 3 && move == *(fa + space_y*4 + space_x + 1));
        if(right_legal){
            *(fa + space_y*4 + space_x + 1) = 16;
            *(fa + space_y*4 + space_x) = move;
        }

        bool top_legal = (space_y != 0 && move == *(fa + space_y*4 + space_x - 4));
        if(top_legal){
            *(fa + space_y*4 + space_x - 4) = 16;
            *(fa + space_y*4 + space_x) = move;
        }

        bool bottom_legal = (space_y != 3 && move == *(fa + space_y*4 + space_x + 4));
        if(bottom_legal){
            *(fa + space_y*4 + space_x + 4) = 16;
            *(fa + space_y*4 + space_x) = move;
        }

        // Check if the game has been won by iterating over the array and checking if
        // the values in the array increase by one per element.
        won = true;
        for(int i = 0; i <= 15; i++){
            if(*(fa + i) != i+1){
                won = false;
            }
        }
    }

    // Print the array one last time and display that the user has won.
    for(int y = 0; y != 4; y++){
        for(int x = 0; x!= 4; x++){

            int value = *(fa + y*4 + x);
            
            if(value < 10){
                // Provide an extra space in front of the number if it is smaller than 10.
                printf("  %d ", value);
            }else if(value == 16){
                // If number is 16, replace it with a space and record its location.
                space_x = x;
                space_y = y;
                printf("    ");
            }else{
                printf(" %d ", value);
            }
            
        }
        printf("\n");
    }
    printf("You won the game!");
        

}