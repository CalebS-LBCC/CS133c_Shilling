#include <stdio.h>
#include <Windows.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>

/**
 * Written by Caleb Shilling
 * Date: 10/24/20
 * Linn Benton, CS 133C
 * 
 * This program is a number guess game. The user is expected to
 * choose either int, long, or float. Then, the program will use
 * a number for the user to guess. The user will
 * have 5 guesses. The program ends when the user runs out of guesses
 * or chooses the correct number.
**/

void main(){
    int intVal = 53;
    long longVal = 149;
    float floatVal = 16.7;


    bool looping = true;
    int choice = 0;
    // Looping code: loops until either the numbers 1, 2, or 3 are entered.
    while(looping){
        printf("Enter 1 to guess an int, 2 to guess a long, and 3 to guess a float.\n");
        scanf("%d", &choice);

        if(choice == 1 || choice == 2 || choice == 3){
            looping = false;
        }
    }

    int guesses = 5;
    int intGuess = 0;
    long longGuess = 0;
    float floatGuess = 0;
    // Looping code: loops until guesses drop below zero, which happens when guesses run out
    // or the program sets it to -1 manually, which means the user has guessed the right number.
    while(guesses >= 1){

        printf("\n%d guesses remaining.\n", guesses);

        switch(choice){
            case 1:

            printf("Please enter an int.\n");
            scanf("%d", &intGuess);

            if(intGuess > intVal){
                printf("Too High!\n");
                guesses = guesses - 1;
            }else if(intGuess < intVal){
                printf("Too Low!\n");
                guesses = guesses - 1;
            }else{
                printf("You guessed the number with %d guesses remaining!\n", guesses);
                guesses = -1;
            }

            break;

            case 2:

            printf("Please enter a long.\n");
            scanf("%lld", &longGuess);

            if(longGuess > longVal){
                printf("Too High!\n");
                guesses = guesses - 1;
            }else if(longGuess < longVal){
                printf("Too Low!\n");
                guesses = guesses - 1;
            }else{
                printf("You guessed the number with %d guesses remaining!\n", guesses);
                guesses = -1;
            }

            break;

            case 3:

            printf("Please enter a float.\n");
            scanf("%f", &floatGuess);

            if(floatGuess > floatVal){
                printf("Too High!\n");
                guesses = guesses - 1;
            }else if(floatGuess < floatVal){
                printf("Too Low!\n");
                guesses = guesses - 1;
            }else{
                printf("You guessed the number with %d guesses remaining!\n", guesses);
                guesses = -1;
            }

            break;
        }
    }

    if(guesses < 0){
        scanf("%d", guesses);
    }else{
        printf("\nYou ran out of guesses!");
        scanf("%d", guesses);
    }
    
}