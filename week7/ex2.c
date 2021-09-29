#include <stdio.h>
#include <stdlib.h>

void input(int *a) {
    scanf("%d", a);
    if (*a < 0) {
        printf("Must not be negative\n");
        input(a);
    }
}

void print_arr(int size, int arr[]) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int N;
    printf("Enter the size of array: ");
    input(&N);

    int *arr = malloc(N*sizeof(int));
    for (int i = 0; i < N; ++i) {
        arr[i] = i;
    }
    print_arr(N, arr);
    free(arr);
    return 0;
}