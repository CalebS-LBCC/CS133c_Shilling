#include <stdio.h>
/**
 * Written by Caleb Shilling
 * Last updated October 3rd, 2020
 * 
 * LBCC CS 133C Project 1
 * 
 * Demonstrate ability to use C datatypes and use the printf function
 * to print variables alongside text.
 */
void main() {

	// Print one of each primitive datatype
	printf("%c is a char.\n",'k');
	printf("%d is an int.\n",10);
	printf("%f is a float.\n",1.006662);
	printf("%lf is a double.\n",30.2);

	// Add two integers together and print the result
	int int_1 = 10;
	int int_2 = 5;
	printf("\nThe sum of int_1 and int_2 is %d.\n", int_1 + int_2);

	// Add two floats together and print the result
	float float_1 = 1.621;
	float float_2 = 5.5721;
	printf("\nThe sum of float_1 and float_2 is %.2f.\n", float_1 + float_2);

	// Multiply two doubles together and print the result rounded to 2 decimal points
	double double_1 = 15.521;
	double double_2 = 9.3401;
	printf("\nThe product of double_1 and double_2 is %.2f.\n", double_1*double_2);

	// Print a sentence with three char variables
	// Using multiple arguments in printf: 
	// https://stackoverflow.com/questions/34598089/how-can-you-print-multiple-variables-inside-a-string-using-printf
	char char_1 = '3';
	char char_2 = 'b';
	char char_3 = 's';
	printf("\nThi%c sentence has %c char varia%cles in it.", char_3, char_1, char_2);

	// Stops the program running until enter is pressed
	getchar();
}