#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/resource.h>

void print_rusage(struct rusage *usage) {
    printf("system CPU time used: %ld.%ld\n", usage->ru_stime.tv_sec, usage->ru_stime.tv_usec);
    printf("maximum resident set size: %ld\n", usage->ru_maxrss);
    printf("integral shared memory size: %ld\n", usage->ru_ixrss);
    printf("integral unshared data size: %ld\n", usage->ru_idrss);
    printf("integral unshared stack size: %ld\n", usage->ru_isrss);
    printf("\n");
}


int main() {
    // Starts with 10 MB of mem allocated on mu machine
    int SECONDS = 10;
    int **p = malloc(sizeof(int*) * SECONDS);
    struct rusage usage;
    for (int i = 0; i < SECONDS; ++i) {
        // Allocate 10 MB additional memory
        p[i] = malloc(10 * pow(2, 20));
        memset(p[i], 0, 10 * pow(2, 20));
        getrusage(RUSAGE_SELF, &usage);
        print_rusage(&usage);
        sleep(1);
    }
    return 0;
}