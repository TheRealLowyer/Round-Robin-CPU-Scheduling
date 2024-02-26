#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Process.h"
#include "Process.c"
#include <limits.h>

#define NUM_INSTRUCTIONS 21 // 20 instructions + 1 exit

int instruction_time_costs[NUM_INSTRUCTIONS];
int real_time=0;
int compareProcesses(const void *a, const void *b) {
    const Process *processA = (const Process *)a;
    const Process *processB = (const Process *)b;
    // Compare based on arrival time
    if (processA->the_first_arrival_time != processB->the_first_arrival_time) {
        return processA->the_first_arrival_time - processB->the_first_arrival_time;
    }
    // Compare based on type (Platinum >>>>)
    int typeComparison = strcmp(processA->type, processB->type);
    if (typeComparison != 0) {
        if(strcmp(processA->type, "PLATINUM")==0){
            return -1; // if processA is plat it has higher order
        }
        if(strcmp(processB->type, "PLATINUM")==0){
            return 1; // if processB is plat it has higher order
        }
    }
    // Compare based on priority (higher priority is higher)
    if (processA->priority != processB->priority) {
        return processB->priority - processA->priority; // if a process has higher priority it has higher order
    }
    if (processA->rr_time != processB->rr_time) {
        return processA->rr_time - processB->rr_time; // In round robin condition to decide first comer
    }
    if(strcmp(processA->id, "P10")==0){
        return 1; // given everything equal compare based on name 
    }
    else if (strcmp(processB->id, "P10")==0){
        return -1;// given everything equal compare based on name 
    }
    else{
        return strcmp(processA->id, processB->id); // given everything equal compare based on name 
    }
}

int getLineCount(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 to indicate an error
    }
    int lineCount = 0;
    char buffer[512]; // Adjust the buffer size as needed
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineCount++;
    }
    fclose(file);
    return lineCount; // returning the linecount 
}
int getIndexOfInstr(const char *str) {
    int len = strlen(str);
    int result = 0;
    int multiplier = 1;
     if (len > 0 && str[len - 1] == '\n') {
        len--;
    }
    // Check if the string starts with "instr"
    if (strncmp(str, "instr", 5) == 0) {
        // Attempt to extract the integer value from the string
        int i = len - 1;
        while (i >= 0 && str[i] >= '0' && str[i] <= '9') {
            result = result + (str[i] - '0') * multiplier;
            multiplier *= 10;
            i--;
        }
        result--;
    } else if (strcmp(str, "exit") == 0) {
        // Special case for "exit"
        result = 20;
    }
    return result;
}
void readInstructionTimes(const char *processName , int arr[]) {
    // Construct the filename based on the process name
    char filename[10];
    snprintf(filename, sizeof(filename), "%s.txt", processName);
    // Open the file
    FILE *file = fopen(filename, "r");
    int count = 0;
    char buffer[512]; // Adjust the buffer size as needed
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int tt = getIndexOfInstr(buffer);
        // reading instruction times and creating intruction time cost array 
        arr[count] = instruction_time_costs[tt];
        count++;
    }
    fclose(file);
}
int main() {
     // Opening instructions file 
    FILE *file = fopen("instructions.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    // Arrays to store instruction names and time costs
    char instruction_names[NUM_INSTRUCTIONS][20];
    // Read instructions and their time costs from the file
    for (int i = 0; i < NUM_INSTRUCTIONS; ++i) {
        fscanf(file, "%s %d", instruction_names[i], &instruction_time_costs[i]);
    }
    // Close the file
    fclose(file);
    //creating instruction time array of P1 and reading the values from the 
    int instr_p1[12];
    readInstructionTimes("P1",instr_p1);
    //creating instruction time array of P2 and reading the values from the 
    int instr_p2[9];
    readInstructionTimes("P2",instr_p2);
    //creating instruction time array of P3 and reading the values from the 
    int instr_p3[10];
    readInstructionTimes("P3",instr_p3);
    //creating instruction time array of P4 and reading the values from the 
    int instr_p4[6];
    readInstructionTimes("P4",instr_p4);
    //creating instruction time array of P5 and reading the values from the 
    int instr_p5[11];
    readInstructionTimes("P5",instr_p5);
    //creating instruction time array of P6 and reading the values from the 
    int instr_p6[15];
    readInstructionTimes("P6",instr_p6);
    //creating instruction time array of P7 and reading the values from the 
    int instr_p7[6];
    readInstructionTimes("P7",instr_p7);
    //creating instruction time array of P8 and reading the values from the 
    int instr_p8[5];
    readInstructionTimes("P8",instr_p8);
    //creating instruction time array of P9 and reading the values from the 
    int instr_p9[6];
    readInstructionTimes("P9",instr_p9);
    //creating instruction time array of P10 and reading the values from the 
    int instr_p10[10];
    readInstructionTimes("P10",instr_p10);
    // opening definition file 
    FILE *def_file = fopen("definition.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    // creating processes array which consists of the processes in definition.txt file 
    int p_count =getLineCount("definition.txt");
    Process processes[p_count];
    int processCount = 0;
    // Read and parse each line of the file
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file) != NULL && processCount < p_count) {
        // Initialize a process from the line and store it in the array
        char id_of_p[4];
        int prio;
        int arrival_of_p;
        char tpp[10];
        if (sscanf(buffer, "%3s %d %d %9s", // reading the lines in order of Process id , priority, arrival time , type 
               id_of_p,
               &prio,
               &arrival_of_p,
               tpp) != 4) {
        // Handle parsing error
        fprintf(stderr, "Error parsing line: %s\n", buffer);
        exit(EXIT_FAILURE);
        }
        if (strncmp(id_of_p, "P", 1) == 0 && id_of_p[1] >= '1' && id_of_p[1] <= '9') {
            if(id_of_p[1] == '1'){
                if(id_of_p[2] == '0'){
                    //creating P10 and adding it to processes array
                    Process p10 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p10,10);
                    processes[processCount] = p10;
                }
                else{
                    //creating P1 and adding it to processes array
                    Process p1 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p1,12);
                    processes[processCount] = p1;
                }
            }
            else if(id_of_p[1] == '2'){Process p2 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p2,9);
            processes[processCount] = p2;}//creating P2 and adding it to processes array
            else if(id_of_p[1] == '3'){Process p3 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p3,10);
            processes[processCount] = p3;}//creating P3 and adding it to processes array
            else if(id_of_p[1] == '4'){Process p4 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p4,6);
            processes[processCount] = p4;}//creating P4 and adding it to processes array
            else if(id_of_p[1] == '5'){Process p5 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p5,11);
            processes[processCount] = p5;}//creating P5 and adding it to processes array
            else if(id_of_p[1] == '6'){Process p6 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p6,15);
            processes[processCount] = p6;}//creating P6 and adding it to processes array
            else if(id_of_p[1] == '7'){Process p7 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p7,6);
            processes[processCount] = p7;}//creating P7 and adding it to processes array
            else if(id_of_p[1] == '8'){Process p8 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p8,5);
            processes[processCount] = p8;}//creating P8 and adding it to processes array
            else if(id_of_p[1] == '9'){Process p9 = initializeProcess(id_of_p,prio,arrival_of_p,tpp,instr_p9,6);
            processes[processCount] = p9;}//creating P9 and adding it to processes array
        }
        processCount++;
    }
    // sorting the processes array 
    qsort(processes, processCount, sizeof(Process), compareProcesses);
    // getting the first elemet of the processes array 
    Process last_executed = processes[0];
    while(1){
        qsort(processes, processCount, sizeof(Process), compareProcesses);
        if(processes[0].the_first_arrival_time==INT_MAX){ 
            break; // finish iff all the processes are finished.
        }
        Process temp = processes[0];
        if (temp.the_first_arrival_time==0)
        {  // first context switch 
            real_time+=10;
            temp.the_first_arrival_time=10;
        }
        // if last executed is not equal the executing process, do context switch 
        if(strcmp(temp.id,last_executed.id)!=0){
            // if the CPU is idle proceed to the next process
            if(temp.the_first_arrival_time>real_time){real_time=temp.the_first_arrival_time;}
            real_time+=10;
            // setting the arrival time of the waiting processes the real time 
            for(int i=0;i <processCount;i++ ){
                if(processes[i].the_first_arrival_time<real_time){
                    processes[i].the_first_arrival_time=real_time;
                }
            }
        }
        // silver process execution 
        if(strcmp(temp.type, "SILVER")==0){
            int temp_quanto = 80; //  time quantum
            real_time+=temp.instruction_times[temp.index_of]; // execute the next instr
            temp_quanto-=temp.instruction_times[temp.index_of]; // decrease temp quanto by executed instr
            temp.burst_time+=temp.instruction_times[temp.index_of]; // add burst time of the process
            temp.index_of+=1; // increment intrs index by 1 
            temp.type_change_count+=1; // it got burst, increment type change count by 1 
            temp.the_first_arrival_time=real_time; // settting arrival time to the real time if cs occurs
            // settting all waiting processses arrival time to the real time 
            for(int i=0;i <processCount;i++ ){
                if(processes[i].the_first_arrival_time<real_time){
                    processes[i].the_first_arrival_time=real_time;
                }
            }
            // if index is equal to the total instr count processes terminated. 
            if(temp.index_of==temp.total_instr){ 
                temp.finish_time=real_time; // setting the finish time 
                temp.the_first_arrival_time=INT_MAX; // setting the arrival time to INT_MAX to be the at the end when array is qsorted
            }
            if(strcmp(temp.type, "SILVER")==0){
                if(temp.type_change_count==3){ // if type change count =3
                    strcpy(temp.type,"GOLD"); // chang the type to gold 
                    temp.type_change_count=0; // refresh the type change count
                    processes[0]=temp; // setting the head of the array temp
                    last_executed=temp; // last executed is temp in any probabilty of cs 
                }
            }
            processes[0]=temp;
            // sort if there is a process which has higher priorty of execution
            qsort(processes, processCount, sizeof(Process), compareProcesses);
            // if there is a processes with hihgher priorrty of execution 
            if(strcmp(temp.id,processes[0].id)!=0){
                // last executed is temp 
                last_executed= temp;
                // finding the  executed one 
                for(int k=0; k<processCount;k++){
                    if(strcmp(processes[k].id,temp.id)==0){
                        // if any case of round robin setting the round robin time to the real time due to FCFS
                        temp.rr_time=real_time;
                        processes[k]=temp;
                    }
                }
                continue;
            }
            while(temp_quanto>0){ // if there is any quantum left 
                real_time+=temp.instruction_times[temp.index_of];// execute the next instr
                temp_quanto-=temp.instruction_times[temp.index_of];// decrease temp quanto by executed instr
                temp.burst_time+=temp.instruction_times[temp.index_of];// add burst time of the process
                temp.index_of+=1;// increment intrs index by 1
                temp.the_first_arrival_time=real_time;// settting arrival time to the real time if cs occurs
                // settting all waiting processses arrival time to the real time 
                for(int i=0;i <processCount;i++ ){
                    if(processes[i].the_first_arrival_time<real_time){
                        processes[i].the_first_arrival_time=real_time;
                    }
                }
                // if index is equal to the total instr count processes terminated. 
                if(temp.index_of==temp.total_instr){ 
                    temp.finish_time=real_time; // setting the finish time 
                    temp.the_first_arrival_time=INT_MAX;// setting the arrival time to INT_MAX to be the at the end when array is qsorted
                }
                processes[0]=temp;
                // sort if there is a process which has higher priorty of execution
                qsort(processes, processCount, sizeof(Process), compareProcesses);
                if(strcmp(temp.id,processes[0].id)!=0){
                     // last executed is temp 
                    last_executed=temp;
                    // finding the  executed one 
                    for(int k=0; k<processCount;k++){
                        if(strcmp(processes[k].id,temp.id)==0){
                            // if any case of round robin setting the round robin time to the real time due to FCFS
                            temp.rr_time=real_time;
                            processes[k]=temp;
                        }
                    }
                    // break the execution
                    break;
                }
            }// if time quantim is fully executed
            if(strcmp(processes[0].id,temp.id)==0){
                // if any case of round robin setting the round robin time to the real time due to FCFS
                temp.rr_time=real_time;
                processes[0]=temp;
            }
            last_executed=temp;
            continue;
        }
        else if (strcmp(temp.type, "GOLD")==0){ // gold process
            int temp_quanto = 120; // time quanrum 
            real_time+=temp.instruction_times[temp.index_of]; // execute the next instr
            temp_quanto-=temp.instruction_times[temp.index_of];// decrease temp quanto by executed instr
            temp.burst_time+=temp.instruction_times[temp.index_of];// add burst time of the process
            temp.index_of+=1; // increment intrs index by 1 
            temp.type_change_count+=1;// it got burst, increment type change count by 1 
            temp.the_first_arrival_time=real_time; // settting arrival time to the real time if cs occurs
            // settting all waiting processses arrival time to the real time 
            for(int i=0;i <processCount;i++ ){
                if(processes[i].the_first_arrival_time<real_time){
                    processes[i].the_first_arrival_time=real_time;
                }
            }
            // if index is equal to the total instr count processes terminated. 
            if(temp.index_of==temp.total_instr){ 
                temp.finish_time=real_time; // etting the finish time 
                temp.the_first_arrival_time=INT_MAX;// setting the arrival time to INT_MAX to be the at the end when array is qsorted
            }
            if(strcmp(temp.type, "GOLD")==0){
                if(temp.type_change_count==5){// if type change count =5
                    strcpy(temp.type,"PLATINUM"); // chang the type to platinum
                    temp.type_change_count=0;// refresh the type change count
                    processes[0]=temp; // setting the head of the array temp
                    last_executed=temp; // last executed is temp in any probabilty of cs 
                    continue;
                }
            }
            processes[0]=temp;
            // sort if there is a process which has higher priorty of execution
            qsort(processes, processCount, sizeof(Process), compareProcesses);
            // if there is a processes with hihgher priorrty of execution
            if(strcmp(temp.id,processes[0].id)!=0){
                // last executed is temp 
                last_executed= temp;
                for(int k=0; k<processCount;k++){
                    if(strcmp(processes[k].id,temp.id)==0){
                        // if any case of round robin setting the round robin time to the real time due to FCFS
                        temp.rr_time=real_time;
                        processes[k]=temp;
                    }
                }
                continue;
            }
            // if there is any quantum left 
            while(temp_quanto>0){
                real_time+=temp.instruction_times[temp.index_of];// execute the next instr
                temp_quanto-=temp.instruction_times[temp.index_of];// decrease temp quanto by executed instr
                temp.burst_time+=temp.instruction_times[temp.index_of];// add burst time of the process
                temp.index_of+=1;// increment intrs index by 1
                temp.the_first_arrival_time=real_time; // settting arrival time to the real time if cs occurs
                // settting all waiting processses arrival time to the real time 
                for(int i=0;i <processCount;i++ ){
                    if(processes[i].the_first_arrival_time<real_time){
                        processes[i].the_first_arrival_time=real_time;
                    }
                }
                // if index is equal to the total instr count processes terminated. 
                if(temp.index_of==temp.total_instr){ 
                    temp.finish_time=real_time; // setting the finish time 
                    // setting the arrival time to INT_MAX to be the at the end when array is qsorted
                    temp.the_first_arrival_time=INT_MAX;
                }
                processes[0]=temp;
                // sort if there is a process which has higher priorty of execution
                qsort(processes, processCount, sizeof(Process), compareProcesses);
                if(strcmp(temp.id,processes[0].id)!=0){
                    // last executed is temp 
                    last_executed=temp;
                    // finding the  executed one 
                    for(int k=0; k<processCount;k++){
                        if(strcmp(processes[k].id,temp.id)==0){
                             // if any case of round robin setting the round robin time to the real time due to FCFS
                            temp.rr_time=real_time;
                            processes[k]=temp;
                        }
                    }
                    // break the execution
                    break;
                }
            }// if time quantim is fully executed
            if(strcmp(processes[0].id,temp.id)==0){
                // if any case of round robin setting the round robin time to the real time due to FCFS
                temp.rr_time=real_time;
                processes[0]=temp;
            }
            last_executed=temp;
            continue;
        }
        else{ // plat processes
            for(int j=temp.index_of;j<temp.total_instr;j++){ // executing all the instructions of plat process
                real_time+=temp.instruction_times[j];
                temp.burst_time+=temp.instruction_times[j];
            }
            // settting all waiting processses arrival time to the real time 
            for(int i=0;i <processCount;i++ ){
                if(processes[i].the_first_arrival_time<real_time){
                    processes[i].the_first_arrival_time=real_time;
                }
            }
            temp.finish_time=real_time; // setting the finish time 
            temp.the_first_arrival_time=INT_MAX;// setting the arrival time to INT_MAX to be the at the end when array is qsorted
            processes[0]=temp;
            last_executed=temp; // last executed is temp
            continue;
        }
    }
    int waiting_time=0; // total waiting time 
    int turnaround_time=0; // total turnaround time 
    for(int k = 0; k<processCount;k++){ // summing up waiting and turnaround time for all processes
        turnaround_time+=processes[k].finish_time-processes[k].f_a_t;
        waiting_time+=processes[k].finish_time-processes[k].f_a_t-processes[k].burst_time;
    }
    float average_waiting_time = (float)waiting_time / p_count; // calculating average
    float average_turnaround_time = (float)turnaround_time / p_count; // calculating average
    if (average_waiting_time - (int)average_waiting_time > 0) {
        printf("%.1f\n", average_waiting_time);
    } else {
        printf("%d\n", (int)average_waiting_time);
    }
    if (average_turnaround_time - (int)average_turnaround_time > 0) {
        printf("%.1f\n", average_turnaround_time);
    } else {
        printf("%d\n", (int)average_turnaround_time);
    }
    return 0 ;
}