#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

/**
 * Written by Caleb Shilling
 * Last updated October 9th, 2020
 * 
 * LBCC CS 133C Lab 2
 * 
 * Determines if a room is beyond occupancy by comparing the maximum
 * amount of people in the room to the amount of people in the room.
 * Gives additional information based on the difference between these
 * numbers.
 */

int readNumber(){
    /**
     * readNumber()
     * Read in a number typed in by the user using scanf()
    **/
    int number;
    scanf("%d",&number);
    return number;
}

bool isPositive(int number){
    /**
     * isPositive()
     * Determine if a number is positive or negative.
     * Zero is considered positive.
     * True is positive, False is negative.
    **/
    bool out = false;
    if(number >= 0){
        out = true;
    }
    return out;
}

void main(){

    // Enter the maximum and current occupants.
    printf("Input the maximum room occupancy: ");
    int maximum = readNumber();
    printf("\nInput the number of people in the room: ");
    int current = readNumber();

    // Calculate the difference between max and current while finding if we are over or under occupancy.
    int difference = maximum - current;
    bool state = isPositive(difference);

    // Print out the state of the room.
    if(state){
        printf("\nThe room is under maximum occupancy. %d more people can fit in the room.", difference);
    }else{
        printf("\nThe room is over maximum occupancy. %d people must leave the room.", -difference);
    }

    // Wait 5 seconds for the window to close.
    Sleep(5000);
}