#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a, b;
    printf("Enter first number\n");
    scanf("%d", &a);
    printf("Enter second number\n");
    scanf("%d", &b);

    swap(&a, &b);
    printf("Swapping.. First number: %d, Second number: %d\n", a, b);
    return 0;
}