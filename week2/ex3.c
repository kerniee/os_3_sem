#include <stdio.h>
#include <stdlib.h>

void print_triangle(int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 1-n; j < n; j++) {
            if (abs(j) <= i) putchar('*'); else putchar(' ');
        }
        putchar('\n');
    }
}

int main(int argc, char *argv[]) {
    int n;
    sscanf(argv[1], "%d", &n);
    print_triangle(n);
    return 0;
}