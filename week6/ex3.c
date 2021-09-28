#include <stdio.h>
#include <stdlib.h>

#define COL_WIDTH 10
#define NUM_OF_HEADERS 6

struct process {
    int arrival_time; // AT
    int burst_time; // BT
    int completion_time; // CT
    // TAT = CT - AT
    // WT = TAT - BT
    int running_time;
};


void input(int *a) {
    scanf("%d", a);
    if (*a < 0) {
        printf("Must not be negative\n");
        input(a);
    }
}

void read_process_data(struct process *p, int i) {
    printf("process[%d]: \n", i);
    scanf("%d %d", &p->arrival_time, &p->burst_time);
    if (p->arrival_time < 0 || p->burst_time < 1) {
        printf("Arrival time must be not negative, Burst time should be greater then zero\n");
        read_process_data(p, i);
    }
}

void print_processes(struct process *processes, int size) {
    printf("\n");
    char headers[NUM_OF_HEADERS][COL_WIDTH] = {
            "P[i]",
            "AT",
            "BT",
            "CT",
            "TAT",
            "WT"
    };
    for (int i = 0; i < NUM_OF_HEADERS; ++i) {
        printf("%-*s", COL_WIDTH, headers[i]);
    }
    printf("\n");

    double total_TAT = 0;
    double total_WT = 0;
    for (int i = 0; i < size; ++i) {
        struct process p = processes[i];
        char p_s[COL_WIDTH];
        sprintf(p_s, "P%d", i);
        printf("%-*s", COL_WIDTH, p_s);
        printf("%-*d", COL_WIDTH, p.arrival_time);
        printf("%-*d", COL_WIDTH, p.burst_time);
        printf("%-*d", COL_WIDTH, p.completion_time);
        int TAT = p.completion_time - p.arrival_time;
        printf("%-*d", COL_WIDTH, TAT);
        total_TAT += TAT;
        int WT = TAT - p.burst_time;
        printf("%-*d\n", COL_WIDTH, WT);
        total_WT += WT;
    }
    printf("Average Turnaround Time = %.6f\n", total_TAT / size);
    printf("Average Waiting Time = %.6f\n", total_WT / size);
}

int comp_robin(const void *elem1, const void *elem2) {
    int a1 = ((struct process *) elem1)->arrival_time;
    int a2 = ((struct process *) elem2)->arrival_time;
    if (a1 > a2) return 1;
    if (a1 < a2) return -1;
    return 0;
}

void run_processes_robin(struct process *processes, int num_of_processes, int quantum) {
    // Sort processes by arrival time
    qsort(processes, num_of_processes, sizeof(struct process), comp_robin);

    int current_time = 0;
    int num_of_complete_processes = 0;
    while (num_of_complete_processes != num_of_processes) {
        for (int i = 0; i < num_of_processes; ++i) {
            struct process *p = &processes[i];
            if (p->completion_time != -1) {
                // process complete
                continue;
            }
//            if (p->arrival_time > current_time) {
//                // Wait for process to arrive
//                current_time = p->arrival_time;
//            }
            // Run process for the max of quantum
            if (quantum + p->running_time < p->burst_time) {
                // Will not be complete after quantum
                int time_to_run = quantum;
                current_time += time_to_run;
                p->running_time += time_to_run;
            } else {
                // Complete now
                int time_to_run = p->burst_time - p->running_time;
                current_time += time_to_run;
                p->running_time += time_to_run;
                p->completion_time = current_time;
                num_of_complete_processes++;
            }
            // Go to next process in queue
        }
        // No new processes, start queue from beginning
    }
}


int comp_fcfs(const void *elem1, const void *elem2) {
    int a1 = ((struct process *) elem1)->arrival_time;
    int a2 = ((struct process *) elem2)->arrival_time;
    if (a1 > a2) return 1;
    if (a1 < a2) return -1;
    return 0;
}

void run_processes_fcfs(struct process *processes, int num_of_processes) {
    // Sort processes by arrival time
    qsort(processes, num_of_processes, sizeof(struct process), comp_fcfs);

    int current_time = 0;
    for (int i = 0; i < num_of_processes; ++i) {
        struct process *p = &processes[i];
        if (p->arrival_time > current_time) {
            // Wait for process to arrive
            current_time = p->arrival_time;
        }
        // Run process
        current_time += p->burst_time;
        p->completion_time = current_time;
        // Go to next process in queue
    }
}


int comp_sjn(const void *elem1, const void *elem2) {
    int a1 = ((struct process *) elem1)->arrival_time;
    int a2 = ((struct process *) elem2)->arrival_time;
    if (a1 > a2) return 1;
    if (a1 < a2) return -1;

    int b1 = ((struct process *) elem1)->burst_time;
    int b2 = ((struct process *) elem2)->burst_time;
    if (b1 > b2) return 1;
    if (b1 < b2) return -1;
    return 0;
}

void run_processes_sjn(struct process *processes, int num_of_processes) {
    // Sort processes by arrival time, and then by burst time
    qsort(processes, num_of_processes, sizeof(struct process), comp_sjn);

    int current_time = 0;
    for (int i = 0; i < num_of_processes; ++i) {
        struct process *p = &processes[i];
        if (p->arrival_time > current_time) {
            // Wait for process to arrive
            current_time = p->arrival_time;
        }
        // Run process
        current_time += p->burst_time;
        p->completion_time = current_time;
        // Go to next process in queue
    }
}

int main() {
    int num_of_processes;
    int quantum;

    printf("Enter number of processes to create: \n");
    input(&num_of_processes);
    printf("Enter quantum: \n");
    input(&quantum);
    struct process processes[num_of_processes];
    printf("Enter arrival and burst time for each process in new line\n");
    for (int i = 0; i < num_of_processes; ++i) {
        read_process_data(&processes[i], i);
        processes[i].running_time = 0;
        processes[i].completion_time = -1;
    }

    printf("\nRound Robin: \n");
    run_processes_robin(&processes, num_of_processes, quantum);
    print_processes(processes, num_of_processes);

    printf("\nShortest Job First: \n");
    run_processes_sjn(&processes, num_of_processes);
    print_processes(processes, num_of_processes);

    printf("\nFirst Come, First Served: \n");
    run_processes_fcfs(&processes, num_of_processes);
    print_processes(processes, num_of_processes);
    // Average waiting time (WT) strongly depends on average turnaround time (TAT)
    // Because WT = TAT - BT, where bt is constant and does not depends on algorithm
    // So, they both represent same metrics.
    //
    // First Come, First Served algorithm will have large average TAT and WT if long jobs come first
    // They will execute firstly, postponing fast jobs, avr TAT and WT large
    //
    // Shortest Job First algorithm will have large average TAT and WT if there are a lot of long jobs
    // They will execute at last, so avr TAT and WT will became large.
    //
    // Round Robin algorithm designed to maximize avr TAT and WT.
    // It have best avr TAT in theory, but takes time to switch between processes in practice
    return 0;
}