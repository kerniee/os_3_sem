#include <stdio.h>
#include <unistd.h>

int main() {
    int n = 5;
    // Num of processes created with initial process
    // num = 2^n
    // num == 3: 8 = 1 + 3 + 3 + 1
    // num == 5: 32 = 1 + 5 + (4+3+2+1) + (3+2+1+2+1+1) + (2+1+1+1) + 1
    for (int i = 0; i < n; ++i) {
        fork();
        sleep(5);
    }
    return 0;
}