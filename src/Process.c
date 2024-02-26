#include "Process.h"
#include <string.h>
#include <stdlib.h>

Process initializeProcess(char *id ,int priority, int arrive, char *process_type,int instr_times[],int total_instr) {
    Process newProcess;
    // Set default values
    strncpy(newProcess.id, id, sizeof(newProcess.id) - 1);
    newProcess.id[sizeof(newProcess.id) - 1] = '\0';
    newProcess.the_first_arrival_time = arrive;
    newProcess.burst_time = 0;
    newProcess.finish_time = 0;
    newProcess.priority = priority;
    strncpy(newProcess.type, process_type, sizeof(newProcess.type) - 1);
    newProcess.type[sizeof(newProcess.type) - 1] = '\0';  // Ensure null-termination
    for (int i = 0; i < 25; ++i) {  // Assuming a fixed size of 25
        newProcess.instruction_times[i] = instr_times[i];
    } // Initialize to NULL
    newProcess.f_a_t= arrive;
    newProcess.index_of = 0;
    newProcess.type_change_count = 0;
    newProcess.total_instr = total_instr;  // Initialize age to 0
    newProcess.rr_time=arrive;
    return newProcess;
}
void printProcessInfo(const Process *process) {
    printf("ID: %s\n", process->id);
    printf("Arrival Time: %d\n", process->the_first_arrival_time);
    printf("Burst Time: %d\n", process->burst_time);
    printf("Finish Time: %d\n", process->finish_time);
    printf("Priority: %d\n", process->priority);
    printf("Type: %s\n", process->type);
    printf("the first arrival of process: %d\n", process->f_a_t);
    printf("Index of Instruction: %d\n", process->index_of);
    printf("Type Change Count: %d\n", process->type_change_count);
    printf("total instr of process: %d\n", process->total_instr);
    printf("time of instrucitons is::  ");
    // Print instruction times if available
    for (int i = 0; i < process->total_instr; ++i) {
        //printf("insrcutiyonss :\n");
        printf("%d ", process->instruction_times[i]);
    }
    printf("\n");
}
