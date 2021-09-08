#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    pid_t pid_real = getpid();
    int n = 10;
    for (int i = 1; i <= n; ++i) {
        if (pid > 0) {
            // parent process
            printf("Hello from parent [%d - %d]\n", pid_real, i);
        } else if (pid == 0) {
            printf("Hello from child [%d - %d]\n", pid_real, i);
        } else {
            return 1;
        }
    }
    return 0;
}