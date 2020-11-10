#include <stdio.h>

/**
 * Written by Caleb Shilling
 * Last edited 11-9-20
 * LBCC CS 133C
 * 
 * salary.c
 * This program takes a list of employees with rank, hours worked, and hourly wage.
 * It then takes that data, calculates base, bonus, and total compensation for each
 * worker, then outputs that data into two files, one with all executives and one
 * with the rest of the employees.
**/ 

void main(int argc, char* argv[]){

    if(argc >= 2){

        // Initialize all arrays to hold values with an arbitrary length.
        int id[1024];
        char type[1024];
        double wage[1024];
        double hours[1024];
        double bonus_rate[1024];
        double yearly_comp[1024];
        double bonus_comp[1024];
        double total_comp[1024];
        int total = 0;

        // Initalize file pointers.
        FILE* fp;
        FILE* fp_out_2;
		fp = fopen(argv[1], "r");
        fseek(fp, 0, 0);

        // Load all arrays with their corresponding column, while also changing total to correspond
        // with how many employees are in the list.
        for(int i = 0; fscanf(fp, "%d %c %lf %lf %lf\n", &id[i], &type[i], &wage[i], &hours[i], &bonus_rate[i]) != EOF; i++){
            total = i;
        }

        fclose(fp);

        // Loop through all arrays and compute each compensation value.
        for(int i = 0; i <= total; i++){

            if(&type[i] == "P"){
                yearly_comp[i] = wage[i] * hours[i];
                bonus_comp[i] = 0;
                total_comp[i] = yearly_comp[i];
            }else if(&type[i] == "N"){
                yearly_comp[i] = wage[i] * hours[i];
                bonus_comp[i] = bonus_rate[i] * yearly_comp[i];
                total_comp[i] = yearly_comp[i] + bonus_comp[i];
            }else{
                yearly_comp[i] = wage[i] * hours[i];
                bonus_comp[i] = bonus_rate[i] * yearly_comp[i];
                total_comp[i] = (yearly_comp[i] + bonus_comp[i])*1.1;
            }

        }

        // Write to each file with the data calculated.
		fp = fopen("Non-Executive.txt", "w");
        fp_out_2 = fopen("Executive.txt", "w");

        for(int i = 0; i <= total; i++){
            if(type[i] != 'E'){
                fprintf(fp, "%d %c %lf %lf %lf\n", id[i], type[i], yearly_comp[i], bonus_comp[i], total_comp[i]);
            }else{
                double extra_bonus = total_comp[i] - bonus_comp[i] - yearly_comp[i];
                fprintf(fp_out_2, "%d %c %lf %lf %lf %lf\n", id[i], type[i], yearly_comp[i], bonus_comp[i], extra_bonus, total_comp[i]);
            }
            
        }
        
        fclose(fp);
        fclose(fp_out_2);

    }

}