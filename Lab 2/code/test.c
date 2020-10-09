#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

/**
 * Written by Caleb Shilling
 * Last updated October 9th, 2020
 * 
 * LBCC CS 133C Lab 2
 * 
 * Test functions eventually used in the firelaws.c program.
 * This is meant to be somewhere between unit tests and manual tests, as I have
 * no way to simulate console input for readNumber().
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
    /**
     * int readNumber() test:
     * 
     * The goal of this test is to determine if readNumber() is functioning properly.
     * Each test cycle will begin with an intial value, say 5. If the use inputs 5 and
     * readNumber outputs 5, then the test cycle passes. If the values are different,
     * the test will fail.
    **/
   
    int test_values[10] = {1021, 20123, 123, 0, 7, -1, -64, -888, -6021, 45};

    // For loops used in tests: https://www.programiz.com/c-programming/c-for-loop
    for(int test = 0; test < 10; test = test + 1){
        printf("readNumber() test %d: Type the number %d.\n", test+1, test_values[test]);
        int number = readNumber();
        if(number != test_values[test]){
            printf("readNumber() test %d failed!\n",test+1);
            test = -1;
            break;
        }
    }

    printf("readnumber() test finished.\n\n");
    

    /**
     * bool isPositive(int) test:
     * 
     * The goal of this test is to run the same numbers from the readNumber() test
     * and determine if they are positive or negative against a boolean array with the
     * correct answer.
    **/

    bool test_answers[10] = {true, true, true, true, true, false, false, false, false, true};

    for(int test = 0; test < 10; test = test + 1){
        if(test_answers[test] == isPositive(test_values[test])){
            printf("test_answers() test %d passed.\n", test+1);
        }else{
            printf("test_answers() test %d failed.\n", test+1);
        }
    }

    printf("isPositive() test finished.\n\n");

    // Sleep function: https://stackoverflow.com/questions/10922900/is-it-possible-to-wait-a-few-seconds-before-printing-a-new-line-in-c
    Sleep(25000);
    getchar();
}