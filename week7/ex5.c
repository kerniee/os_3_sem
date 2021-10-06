# include <stdio.h>
#include <stdlib.h>

int main() {
    char **s;
    char foo[] = " Hello World ";
    // s is not initialized, initialize
    s = malloc(1 * sizeof(char));
    *s = foo;
    // pointer to string interpreted as string, fixing by changing print type
    printf("s is %p\n", s);
    s[0] = foo;
    printf("s [0] is %s\n", s[0]);
    // free pointer, for the sake of consistency
    free(s);
    double* const p;
    return (0);
}