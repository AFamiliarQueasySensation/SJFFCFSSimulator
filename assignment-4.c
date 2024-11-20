/**************************************
 * Name: Grant Von Hagen (251307427)
 * Course: CS3305
 * FileName: assignment-4c
 * Date: 11/20/2024
 * Description: Takes values from a csv file formateed by Process, Burst_time then calculates sjf, fcfs, or rr (if rr specify time quantum)
 * 
 * run like this
 * ./a.out -s (csv file)
 * ./a.out -r (time quantum) (csv file)
 ***************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct{

    int arrival;
    int wait_time;
    int turnaround;
    int complete;

} process;


int main(int argc, char *argv[]){

    //Handle gracefully if not enough args
    char keys[128][16];
    int values[128];
    int MAXIMUM = 0;


    if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-r") == 0|| strcmp(argv[1], "-f") == 0){
        
        } else{
            printf("Invalid -something type specified.\n");
            printf("%d", strcmp(argv[1], "-s") == 0);
            return 2;
        }

    //Read csv file
    FILE *file = NULL;
    int quantum = 0;
    
    if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-f") == 0){
        file = fopen(argv[2], "r");
    }
    
    // Should Grab Quantum
    if (strcmp(argv[1], "-r") == 0){
        file = fopen(argv[3], "r");
        quantum = atoi(argv[2]);
    }
   
    
    
    char line[128];
    char key[16];
    int value;

    if (file == NULL){
        printf("Error in opening the file\n");
        return 3;
    }

    while(fgets(line, sizeof(line), file)){

        if (sscanf(line, "%[^,],%d", key, &value) == 2){
            strcpy(keys[MAXIMUM], key);
            values[MAXIMUM] = value;
            MAXIMUM++;
        } else{
            printf("Failed to parse line?\n");
        }
    }

    int time_quantum = 9999;
    int wait_time = 0;
    int turn_around_time = 0;
    int count = 0;
    int task_counter = 0;

    //Computing 
    if (strcmp(argv[1],"-s") == 0){

        int current_time = 0;
        int process_loader_counter = 0;
        int last_process = 999;
        char sjf_keys[128][16];
        int sjf_values[128] = {999};
        process processes[19];
        int j = 212;
      
    

        while (1){
            int all_zero = 1;
            for (int i = 0 ; i < MAXIMUM; i++){
                if (sjf_values[i] != 0) {
                    all_zero = 0;
                    break;
                }
                else {
                    continue;
                    }
            }
            
            if (all_zero) {
                break; // break out the while loop
            }

            if (task_counter < MAXIMUM){ //we add the new process here
                strcpy(sjf_keys[task_counter], keys[task_counter]);
                sjf_values[task_counter] = values[task_counter];
                processes[task_counter].arrival = task_counter;
                processes[task_counter].wait_time = 999;

                if (sjf_values[last_process] > sjf_values[task_counter]){
                    processes[last_process].wait_time = processes[last_process].wait_time + sjf_values[task_counter];
                }
            }
          
           
            

            //Finding the process with the smallest burst value
            int smallest_value = 999;
            int smallest_process = 999;

            for (int i = 0; i < MAXIMUM; i++){

                 if (sjf_values[i] != 0 && sjf_values[i] < smallest_value){
                    smallest_value = sjf_values[i];
                    smallest_process = i;


                    // No switch
                    if (smallest_value == sjf_values[last_process]){
                        smallest_process = last_process;
                    }

                 }
            }
            
            //initialize wait time
            if (processes[smallest_process].wait_time == 999){
                processes[smallest_process].wait_time = task_counter - processes[smallest_process].arrival;
            }
            

            //turnaround time initializer
            processes[smallest_process].turnaround = task_counter - processes[smallest_process].arrival;

            printf("T%d : %s  - Burst left %d,\tWait time %d,\tTurnaround time %d\n", task_counter, sjf_keys[smallest_process], sjf_values[smallest_process], processes[smallest_process].wait_time, processes[smallest_process].turnaround);
            task_counter ++;
            sjf_values[smallest_process] -= 1;
            last_process = smallest_process;
            j--;
            if (j == 0){
                break;
            }
            

        }

        for (int i = 0; i < MAXIMUM; i++){
            printf("%s\n\tWaiting time: \t\t%d\n\tTurnaround time: \t%d\n\n", sjf_keys[i], processes[i].wait_time, processes[i].turnaround + 1);
        }

        float avg_wait = 0;
        float avg_turnaround = 0;
        for (int i = 0; i < MAXIMUM; i++){
           avg_wait += processes[i].wait_time;
           avg_turnaround += processes[i].turnaround;
        }
        avg_wait = avg_wait / 20;
        avg_turnaround = avg_turnaround / 20;

        printf("Total Average waiting time:\t%.1f\nTotal average turnaround time:\t%.1f\n",avg_wait, avg_turnaround + 1);

    }


 
    if (strcmp(argv[1],"-f") == 0){
        process processes[19];
        for (int i = 0; i < MAXIMUM; i++){

            for(int j = values[i]; j > 0; j--){
                printf("T%d : %s  - Burst left %d,\tWait time %d,\tTurnaround time %d\n", task_counter, keys[count], j, wait_time, turn_around_time);
                turn_around_time++;
                task_counter++;
            }

            processes[i].wait_time = wait_time;
            processes[i].turnaround = turn_around_time;

            turn_around_time--;
            count++;
            wait_time = turn_around_time;
        }


         for (int i = 0; i < MAXIMUM; i++){
            printf("%s\n\tWaiting time: \t\t%d\n\tTurnaround time: \t%d\n\n", keys[i], processes[i].wait_time, processes[i].turnaround + 1);
        }

        float avg_wait = 0;
        float avg_turnaround = 0;
        for (int i = 0; i < MAXIMUM; i++){
           avg_wait += processes[i].wait_time;
           avg_turnaround += processes[i].turnaround;
        }
        avg_wait = avg_wait / MAXIMUM;
        avg_turnaround = avg_turnaround / MAXIMUM;

        printf("Total Average waiting time:\t%.1f\nTotal average turnaround time:\t%.1f\n",avg_wait, avg_turnaround);


        

    }



    if (strcmp(argv[1],"-r") == 0){
        process processes[19];
        char rr_keys[128][16];
        int rr_values[128] = {999};
        int rr_second_values[128] = {0};
        int rr_processed_values[128] = {0};

        for (int i = 0; i < MAXIMUM; i++){
            strcpy(rr_keys[i],keys[i]);
            rr_values[i] = values[i];
            processes[i].arrival = i;
            processes[i].turnaround = 0;
            processes[i].complete = 1;
        }

        while (1){
            int all_zero = 1;
            for (int i = 0 ; i < MAXIMUM; i++){
                if (rr_values[i] != 0) {
                    all_zero = 0;
                    break;
                }
                else {
                    continue;
                    }
            }
            
            if (all_zero) {
                break; // break out the while loop
            }


            for (int i = 0; i < MAXIMUM; i++){

                if (rr_values[i] != 0 && processes[i].complete){
                    processes[i].wait_time = task_counter - i - rr_second_values[i];
                    processes[i].turnaround = processes[i].wait_time + rr_processed_values[i];
                   
                }

                for (int j = 0; j < quantum; j++){
                    if (rr_values[i] > 0){
                        
                        printf("T%d : %s  - Burst left %d,\tWait time %d,\tTurnaround time %d\n", task_counter, rr_keys[i], rr_values[i], processes[i].wait_time, processes[i].turnaround);
                        rr_values[i]--;
                        processes[i].turnaround++;
                        rr_processed_values[i]++;
                        task_counter++;
                        rr_second_values[i]++;

                    } else {
                        break;
                    }
                    
                }

                if (rr_values[i] == 0 && processes[i].complete){
                    processes[i].complete = 0;
                }
                

            }


        }


        for (int i = 0; i < MAXIMUM; i++){
            printf("%s\n\tWaiting time: \t\t%d\n\tTurnaround time: \t%d\n\n", keys[i], processes[i].wait_time, processes[i].turnaround);
        }

        float avg_wait = 0;
        float avg_turnaround = 0;
        for (int i = 0; i < MAXIMUM; i++){
           avg_wait += processes[i].wait_time;
           avg_turnaround += processes[i].turnaround;
        }
        avg_wait = avg_wait /MAXIMUM;
        avg_turnaround = avg_turnaround / MAXIMUM;

        printf("Total Average waiting time:\t%.1f\nTotal average turnaround time:\t%.1f\n",avg_wait, avg_turnaround);
    }

    return 0;
}