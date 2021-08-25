#include <limits.h>
#include <float.h>
#include <stdio.h>

int main() {
    int i = INT_MAX;
    float f = FLT_MAX;
    double d = DBL_MAX;

    printf("Value of integer: %d\nValue of float: %f\nValue of double: %f\n\n", i, f, d);
    printf("Size of integer: %lu, size of float: %lu, size of double: %lu\n", sizeof(i), sizeof(f), sizeof(d));
    return 0;
}