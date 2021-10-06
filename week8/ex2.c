#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int main() {
    // Starts with 10 MB of mem allocated on mu machine
    int SECONDS = 10;
    int **p = malloc(sizeof(int*) * SECONDS);
    for (int i = 0; i < SECONDS; ++i) {
        // Allocate 10 MB additional memory
        p[i] = malloc(10 * pow(2, 20));
        memset(p[i], 0, 10 * pow(2, 20));
        sleep(1);
    }
    return 0;
}