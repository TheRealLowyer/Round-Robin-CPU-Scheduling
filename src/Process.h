#ifndef PROCESS_H
#define PROCESS_H

// Structure for process
typedef struct {
    char id[4];                     // ID of the process
    int the_first_arrival_time;     // Arrival time of the process
    int burst_time;                 // burst time of the process
    int finish_time;                // finish time of the process
    int priority;                   // Priority of the process
    char type[50];                  // Type of the process (string)
    int instruction_times[25];      // List of instruction times
    int f_a_t;                      // first arrival time 
    int index_of;                   // Index of the which instruction is to be executed 
    int type_change_count;          // Count of type change cases  
    int total_instr;                // Aging of process
    int rr_time;                    // round robin enter time 
} Process;

#endif // PROCESS_H
