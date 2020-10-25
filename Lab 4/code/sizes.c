#include <stdio.h>
#include <Windows.h>

double hatSize(double weight, double height){
    /**
     * hatSize(double weight, double height)
     * 
     * Calculate the size of a hat the user should buy
     * based on their weight and height. 
    **/ 
    double size = (weight/height)*2.9;
    return size;
}

double jacketSize(double weight, double height, double age){
    /**
     * jacketSize(double weight, double height, double age)
     * 
     * Calculate the size of a jacket the user should buy
     * based on their weight, height, and age. 
    **/ 
    double ageOffset = 0;
    if(age > 28){
        ageOffset = (age-28)/8;
    }

    double size = height*weight/220+ageOffset;
    return size;
}

double waistSize(double weight, double age){
    /**
     * waistSize(double weight, double age)
     * 
     * Calculate the waist size of the user by using the
     * user's weight and age.
    **/ 
    double ageOffset = 0;
    if(age > 28){
        ageOffset = (age-28)/10;
    }

    double size = weight/5.7+ageOffset;
    return size;
}

void main(){

    int value = 1;

    while(value != 0){

        int age = 0;
        printf("Enter your age: ");
        scanf("%d", &age);

        int weight = 0;
        printf("\nEnter your weight: ");
        scanf("%d", &weight);

        int height = 0;
        printf("\nEnter your height: ");
        scanf("%d", &height);

        printf("\nYou entered your age as %d years old,\nyour weight as %d pounds,\nand your height as %d inches.\n", age, weight, height);
        printf("Your hat size is %f,\n", hatSize(weight,height));
        printf("Your jacket size is %f,\n", jacketSize(weight,height,age));
        printf("Your waist size is %f,\n", waistSize(weight,age));
        
        printf("Enter '0' to not calculate again.\n");
        Sleep(1000);
        scanf("%d", &value);
    }
}