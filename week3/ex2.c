#include <limits.h>
#include <float.h>
#include <stdio.h>

void swap(int *a, int *b) {
//    printf("%d %d\n", *a, *b);
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * head newnode prevnode
 */

void input_arr_size(int *a) {
    scanf("%d", a);
    if (*a < 0) {
        printf("Size must not be negative\n");
    }
}

void input_arr(int size, int arr[]) {
    for (int i = 0; i < size; ++i) {
        scanf("%d", &arr[i]);
    }
}

void print_arr(int size, int arr[]) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubble_sort(int size, int arr[]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (arr[i] < arr[j]) swap(&arr[i], &arr[j]);
        }
    }
}

int main() {
    int n;
    printf("Enter array size\n");
    input_arr_size(&n);
    if (n < 0) return 0;
    int arr[n];
    printf("Input array\n");
    input_arr(n, arr);

    bubble_sort(n, arr);

    printf("\nSorted array:\n");
    print_arr(n, arr);
    return 0;
}