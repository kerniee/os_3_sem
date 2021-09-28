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
};


void input(int *a) {
    scanf("%d", a);
    if (*a < 0) {
        printf("Must not be negative\n");
        input(a);
    }
}

void read_process_data(struct process *p, int i) {
    printf("process[%d]: ", i);
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

int main() {
    int num_of_processes;
    printf("Enter number of processes to create: \n");
    input(&num_of_processes);
    struct process processes[num_of_processes];
    printf("Enter arrival and burst time for each process in new line\n");
    for (int i = 0; i < num_of_processes; ++i) {
        read_process_data(&processes[i], i);
    }

    run_processes_fcfs(&processes, num_of_processes);
    print_processes(processes, num_of_processes);
    return 0;
}