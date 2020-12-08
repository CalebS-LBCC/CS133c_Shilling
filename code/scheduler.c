#include <stdio.h>
#include <malloc.h>
#include "string.h"

typedef enum {Schedule, DisplayAllVansTime, DisplayVanTime,
    DisplaySchedule, Exit}modes;

int monthEnd[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

struct Stop{
    int id;
    char building[32];
};

struct Van{
    int van_id;
    int start;
    int stop;
    int lunch;
    int bld_id[5];
    char bld_name[5][32];
    char schedule[12][32];
    int scheduleID[12];
};

struct ScheduledVan{
    int van_id;
    int bld_id;
    char bld_name[32];
    int month;
    int date;
    int year;
    int time;
};

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

int toMilitary(int standard_time){
    /* Convert a standard time into military time */
    if(standard_time < 6){
        return standard_time + 12;
    }
    return standard_time;
}

void loadStopsIntoVan(int total_stops, struct Stop * stops, struct Van * vans){
    /* Load the names of stops into all vans in a pointer.*/
    for(int j = 0; j < total_stops; j++){
        for(int k = 0; k < 5; k++){
            if((stops+j)->id == vans->bld_id[k]){              
                strcpy(vans->bld_name[k], (stops+j)->building);          
            }
        }     
    }
}

void generateSchedules(struct Van * vans){
    /* Generate a schedule based on predetermined logic.
    *  A van has 5 different stops per day but works for more
    *  than 5 hours. Therefore, the program must fill in the gaps
    *  by generating a schedule for the van to follow each hour.*/
    int currentTime = 6;
    int sectionCount = 0;
    for(int j = 0; j < 12; j++){
        // If the van is at lunch, set the name of that time in the
        // schedule to either. Don't increment any counters.
        if(currentTime < vans->start || currentTime >= vans->stop){
            strcpy(vans->schedule[j], "Closed");
        }else if(currentTime ==  vans->lunch){
            strcpy(vans->schedule[j], "Lunch");
        }else{
            // Take the modulo of 5 of the current section of the schedule
            // we are on and copy that into the schedule field at j.
            strcpy(vans->schedule[j], vans->bld_name[sectionCount % 5]);
            vans->scheduleID[j] = vans->bld_id[sectionCount % 5];
            sectionCount++;
        }
        currentTime++;
    }

}

void updateDateArray(int *inputPointer){
    /*Ask the user for the date they want to schedule and
      modify a pointer to hold the value.*/
    char scheduledDate[32];
    int dateAllowed = 0;
    // Verify if the entered date is allowed
    while(dateAllowed != 1){
        printf("Enter the scheduled date in the format MM-DD-YYYY: ");
        // Scan the input string and set parts of the string to their
        // associated pointer value
        scanf("%s", &scheduledDate);
        sscanf(scheduledDate, "%d-%d-%d", &(*inputPointer), &(*(inputPointer+1)), &(*(inputPointer+2)));
        int month = *inputPointer;
        int date = *(inputPointer+1);
        int year = *(inputPointer+2);
        // Verify the date exists by comparing it against both basic date logic and
        // an array full of the last days of each month.
        if(monthEnd[month-1] >= date && date > 0 && year >= 2020 && month < 13){
            dateAllowed = 1;
        }
        
    }
}

int getTimeFromUser(char phrase[1024]){
    /* Asks the user for a time. Takes a value between 1 and 12
        and ignores all other values.*/

    int targetTime = 0;
    int timeAllowed = 0;
    // Verify if the entered time is allowed
    while(timeAllowed != 1){
        printf("Enter the start time from 6 AM to 5 PM (omit the AM/PM): ");
        scanf("%d", &targetTime);
        // If the time can exist, end the loop.
        if(targetTime < 13 && targetTime > 0){
            timeAllowed = 1;
        }
    }
    return targetTime;

}

void combAndUpdateIDPointer(int * idPointer, int van_amount, int converted_time,
    struct Van *vans, char dest[32]){
    // Comb through all van schedules and find if a time matches
    // the target destination.
    for(int i = 0; i < van_amount; i++){
        if(!strcmp((vans+i)->schedule[converted_time], dest)){
            *idPointer = (vans+i)->van_id;
            *(idPointer+1) = (vans+i)->scheduleID[converted_time];
        }
    }
}

void main(){

    // Have the user enter their name for the output file.
    char user[32];
    printf("Please enter your name: ");
    scanf("%s", &user);

    // Count the amount of lines in the stops file to load the
    // amount of stops stored.
    FILE* fp;
    fp = fopen(".\\IO_Files\\stops.txt", "r");
    int stopAmount = lineCounter(fp);

    // Define a pointer for holding all stops via malloc
    struct Stop *stops = malloc(stopAmount * sizeof(struct Stop));
    for(int i = 0; i < stopAmount; i++){
        // Fill all stops with their data inside the stop file.
        fscanf(fp, "%d %s", &(stops+i)->id, &(stops+i)->building);
    }   
    fclose(fp);

    // Count the amount of vans in the vans file.
    fp = fopen(".\\IO_Files\\vans.txt", "r");
    int vanAmount = lineCounter(fp);

    // Define a pointer for holding all vans via malloc
    struct Van *vans = malloc(vanAmount * sizeof(struct Van));
    for(int i = 0; i < vanAmount; i++){
        // Import all values from the file
        int van_id;
        int start;
        int stop;
        int lunch;
        int bld_id[5];
        fscanf(fp, "%d %d %d %d %d %d %d %d %d", &van_id, &start, &stop, 
            &lunch, &bld_id[0], &bld_id[1], &bld_id[2], &bld_id[3], &bld_id[4]);
        (vans+i)->van_id = van_id;
        // Store time information in military time to make calculations easier.
        (vans+i)->start = toMilitary(start);
        (vans+i)->stop = toMilitary(stop);
        (vans+i)->lunch = toMilitary(lunch);

        // Load the building ids taken from the file into the array located
        // inside the Van struct.
        for(int j = 0; j < 5; j++){
            (vans+i)->bld_id[j] = bld_id[j];
        }

        loadStopsIntoVan(stopAmount, stops, (vans+i));
        generateSchedules(vans+i);     
        
    }
    fclose(fp);
    
    // Variables and pointers needed to be defined
    // outside of the program loop.
    modes currentMode;
    int toContinue = 1;
    int toDatePointer[3] = {0,0,0};
    int * dateArray = toDatePointer;
    int searchID = 0;
    int idFound = 0;
    int ptrPos = 0;
    int startTime;
    int convertedStartTime;
    int endTime;
    int convertedEndTime;  

    while(toContinue == 1){

        int enteredSelection = 0;
        int legalSelection = 0;
        // Loops until user gives legal mode to enter.
        while(legalSelection != 1){
            printf("\nTo schedule a van, enter 1.\n");
            printf("To display the schedules of all vans between 2 times, enter 2.\n");
            printf("To display the schedule of one van between 2 times, enter 3.\n");
            printf("To display scheduled vans on a date and between times, enter 4.\n");
            printf("To exit, enter 5.\n");
            scanf("%d", &enteredSelection);
            switch(enteredSelection){
                case 1:
                    currentMode = Schedule;
                    legalSelection = 1;
                    break;
                case 2:
                    currentMode = DisplayAllVansTime;
                    legalSelection = 1;
                    break;
                case 3:
                    currentMode = DisplayVanTime;
                    legalSelection = 1;
                    break;
                case 4:
                    currentMode = DisplaySchedule;
                    legalSelection = 1;
                    break;
                case 5:
                    currentMode = Exit;
                    legalSelection = 1;
                    break;
                default: break;
            }
        }
        
        switch(currentMode){
            case Schedule: // Schedule a van
                
                printf("Transport Scheduler:\n\nDestinations:\n");
                char destination[32];
                int destinationExists = 0;
                // Print all destinations
                for(int i = 0; i < stopAmount; i++){
                    printf("%s Station\n", (stops+i)->building);
                }

                // Verify if the entered destination exists
                while(destinationExists != 1){
                    printf("Please select a destination: ");
                    scanf("%s", &destination);
                    for(int i = 0; i < stopAmount; i++){
                        if(!strcmp(destination, (stops+i)->building)){
                            destinationExists = 1;
                        }
                    }
                }

                // Ask the user for a date to schedule the transport.
                updateDateArray(dateArray);

                int targetTime = getTimeFromUser("Enter the start time from 6 AM to 5 PM (omit the AM/PM): ");
                // Zeros the time, making the start of the day be 0.
                // This makes accessing arrays easier.
                int convertedTime = toMilitary(targetTime) - 6;
            
                // Creates a 2 element int pointer
                int toIDPointer[2] = {0,0};
                int * idArray = toIDPointer;
                // Set pointer values to a van ID and building ID
                combAndUpdateIDPointer(idArray, vanAmount, convertedTime, vans,
                    destination);

                // Verify that nothing is scheduled at the time.
                // This code is copied from the section below, I didn't see this requirement until late.
                // This should be a seperate function at this point, but I ran out of time to do so.
                fp = fopen("IO_Files\\out.txt", "r");
                int amount = lineCounter(fp);
                int goSchedule = 1;

                if(amount > 0){
                    // Define a scheduling object via malloc
                    struct ScheduledVan *schedule = malloc(amount * sizeof(struct ScheduledVan));

                    for(int i = 0; i < amount; i++){
                        // Define holder variables and assign them to file output.
                        char user[32];
                        int van_id;
                        int bld_id;
                        char bld_name[32];
                        int month;
                        int date;
                        int year;
                        int time;
                        fscanf(fp, "%s %d %d %d-%d-%d %d\n", &user, &bld_id, &van_id, 
                        &month, &date, &year, &time);

                        // Assign the pointer values to the holder variables.
                        (schedule+i)->van_id = van_id;
                        (schedule+i)->bld_id = bld_id;
                        (schedule+i)->month = month;
                        (schedule+i)->date = date;
                        (schedule+i)->year = year;
                        (schedule+i)->time = time;

                        // Search for the building name the building ID corresponds to
                        // and add it to the pointer
                        for(int j = 0; j < stopAmount; j++){
                            if(bld_id == (stops + j)->id){
                                strcpy((schedule+i)->bld_name, (stops + j)->building);
                            }
                        }      
                    }
                    fclose(fp);

                    // Verify that the van number isn't active at the given time.                 
                    for(int i = 0; i < amount; i++){
                        if((schedule+i)->time == targetTime && (schedule+i)->van_id == *idArray
                            && (schedule+i)->date == *(dateArray+1)
                            && (schedule+i)->month == *(dateArray) 
                            && (schedule+i)->year == *(dateArray+2)){
                            goSchedule = 0;
                        }
                    }

                    free(schedule);
                }

                if(*idArray == 0 || goSchedule != 1){
                    // This value returns zero if no van could be scheduled.
                    printf("No van could be scheduled at that time and destination.\n");
                }else{
                    // Build the file output
                    fp = fopen("IO_Files\\out.txt", "a");
                    fprintf(fp, "%s %d %d %d-%d-%d %d\n", user, *(idArray+1), *idArray, 
                        *(dateArray), *(dateArray+1), *(dateArray+2), targetTime);
                    fclose(fp);
                }

                break;
            case DisplayAllVansTime: // Display all vans' schedule at a date within time bounds

                // Get the date from the user.
                updateDateArray(dateArray);

                // Get the time bounds from the user.
                startTime = getTimeFromUser("Enter the start time from 6 AM to 5 PM (omit the AM/PM): ");
                convertedStartTime = toMilitary(startTime) - 6;
                endTime = getTimeFromUser("Enter the end time from 6 AM to 5 PM (omit the AM/PM): ");
                convertedEndTime = toMilitary(endTime) - 6;

                // Display the schedule for each van.
                for(int i = 0; i < vanAmount; i++){
                    // Displays header van and date information
                    printf("\nVan: %d\n", (vans+i)->van_id);
                    printf("Date: %d-%d-%d\n", *dateArray, *(dateArray+1), *(dateArray+2));
                    
                    for(int j = convertedStartTime; j <= convertedEndTime; j++){
                        // Converts military zeroed time to a real time value
                        // for display
                        int realTime = (j+6)%12;
                        if(realTime == 0){ realTime = 12; }

                        // If the van is not operating, don't print.
                        if(strcmp((vans+i)->schedule[j], "Closed")){
                            if(realTime > 9){
                                printf("%d:00   %s\n", realTime, (vans+i)->schedule[j]);
                            }else{
                                printf("%d:00    %s\n", realTime, (vans+i)->schedule[j]);
                            }
                        }            
                    }
                }
                break;

            case DisplayVanTime: // Display the schedule of one van within time bounds

                searchID = 0;
                idFound = 0;
                // Loop until the user inputs a valid van ID.
                while(idFound != 1){
                    printf("Please enter the van ID: ");
                    scanf("%d", &searchID);
                    for(int i = 0; i < vanAmount; i++){
                        if((vans+i)->van_id == searchID){
                            idFound = 1;
                            ptrPos = i;
                        }
                    }
                }

                // Obtain a date from the user.
                updateDateArray(dateArray);

                // Get the time bounds from the user.
                startTime = getTimeFromUser("Enter the start time from 6 AM to 5 PM (omit the AM/PM): ");
                convertedStartTime = toMilitary(startTime) - 6;
                endTime = getTimeFromUser("Enter the end time from 6 AM to 5 PM (omit the AM/PM): ");
                convertedEndTime = toMilitary(endTime) - 6;

                // Print header information
                printf("\nVan: %d\n", (vans+ptrPos)->van_id);
                printf("Date: %d-%d-%d\n", *dateArray, *(dateArray+1), *(dateArray+2));

                for(int i = convertedStartTime; i <= convertedEndTime; i++){
                    // Convert military zeroed time to real time
                    int realTime = (i+6)%12;
                    if(realTime == 0){ realTime = 12; }

                    // add extra space if need be
                    if(realTime > 9){
                        printf("%d:00   %s\n", realTime, (vans+ptrPos)->schedule[i]);
                    }else{
                        printf("%d:00    %s\n", realTime, (vans+ptrPos)->schedule[i]);
                    }           
                }

                break;

            case DisplaySchedule:
            
                // Open the output schedule file and count how many
                // vans are scheduled.
                fp = fopen("IO_Files\\out.txt", "r");
                int amountScheduled = lineCounter(fp);

                if(amountScheduled > 0){
                    // Define a scheduling object via malloc
                    struct ScheduledVan *schedules = malloc(amountScheduled * sizeof(struct ScheduledVan));

                    for(int i = 0; i < amountScheduled; i++){
                        // Define holder variables and assign them to file output.
                        char user[32];
                        int van_id;
                        int bld_id;
                        char bld_name[32];
                        int month;
                        int date;
                        int year;
                        int time;
                        fscanf(fp, "%s %d %d %d-%d-%d %d\n", &user, &bld_id, &van_id, 
                        &month, &date, &year, &time);

                        // Assign the pointer values to the holder variables.
                        (schedules+i)->van_id = van_id;
                        (schedules+i)->bld_id = bld_id;
                        (schedules+i)->month = month;
                        (schedules+i)->date = date;
                        (schedules+i)->year = year;
                        (schedules+i)->time = time;

                        // Search for the building name the building ID corresponds to
                        // and add it to the pointer
                        for(int j = 0; j < stopAmount; j++){
                            if(bld_id == (stops + j)->id){
                                strcpy((schedules+i)->bld_name, (stops + j)->building);
                            }
                        }      
                    }
                    fclose(fp);

                    // Ask for time bounds and the date to look up
                    startTime = getTimeFromUser("Enter the start time from 6 AM to 5 PM (omit the AM/PM): ");
                    convertedStartTime = toMilitary(startTime);
                    endTime = getTimeFromUser("Enter the end time from 6 AM to 5 PM (omit the AM/PM): ");
                    convertedEndTime = toMilitary(endTime);
                    updateDateArray(dateArray);


                    for(int i = 0; i < amountScheduled; i++){
                        if(*(dateArray+2) == (schedules+i)->year
                            && *(dateArray) == (schedules+i)->month
                            && *(dateArray+1) == (schedules+i)->date 
                            && toMilitary((schedules+i)->time) >= convertedStartTime
                            && toMilitary((schedules+i)->time) <= convertedEndTime){
                            
                            int realTime = (i)%12;
                            if(realTime == 0){ realTime = 12; }

                            printf("\nVan: %d\n", (schedules+i)->van_id);
                            printf("Date: %d-%d-%d\n", *dateArray, *(dateArray+1), *(dateArray+2));
                            
                            // Add extra space if need be
                            if(realTime > 9){
                                printf("%d:00   %s\n", realTime, (schedules+i)->bld_name);
                            }else{
                                printf("%d:00    %s\n", realTime, (schedules+i)->bld_name);
                            }   

                        }else{
                        }
                    }
                    
                    // Free the schedule file
                    free(schedules);

                }else{
                    printf("Nothing is scheduled yet.\n");
                }

                break;

            case Exit:
                toContinue = 0;
                break;

            default:
                break;
        }

    }

    free(vans);
    free(stops);
    free(dateArray);
    
}