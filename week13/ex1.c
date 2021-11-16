#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getM(const char *line);

int *splitline(char *line, int size) {
    int *arr = (int *) malloc(sizeof(int) * size);

    int c = 0;
    char *pch = strtok(line, " ");
    while (pch != NULL) {
        arr[c] = atoi(pch);
        pch = strtok(NULL, " ");
        c++;
    }
    return arr;
}

int countNumOfLinesInFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    char *read;
    int n = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (read == 2) {
            continue;
        }
        n += 1;
    }
    fclose(fp);

    return n;
}

void print_arr(int size, int arr[]) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int nlines = countNumOfLinesInFile("input.txt");

    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int c = 0;
    int m = -1;
    int n = (nlines - 2) / 2;

    int *arr_e, *arr_a;
    int *arr_c[n], *arr_r[n];
    int *terminated = malloc(n * sizeof(int));

    while ((read = getline(&line, &len, fp)) != -1) {
        if (read == 2) {
            continue;
        }
        if (m == -1) {
            m = getM(line);
            for (int j = 0; j < n; ++j) {
                arr_c[j] = (int *) malloc(sizeof(int) * m);
                arr_r[j] = (int *) malloc(sizeof(int) * m);
            }
        }

        switch (c) {
            case 0:
                arr_e = splitline(line, m);
                break;
            case 1:
                arr_a = splitline(line, m);
                break;
            default:
                if (2 <= c && c < n + 2) {
                    arr_c[c - 2] = splitline(line, m);
                } else {
                    arr_r[c - 2 - n] = splitline(line, m);
                }
        }
        c++;
    }

    int deadlock = 0, canTerminate = 0;
    for (int k = 0; k < n; ++k) {
        int anyTerminated = 0;
        for (int i = 0; i < n; ++i) {
            if (terminated[i]) continue;
            canTerminate = 1;
            // Check if all resources are met
            for (int j = 0; j < m; j++) {
                if (arr_a[j] < arr_r[i][j]) {
                    canTerminate = 0;
                    break;
                }
            }
            if (canTerminate) {
                // Add resources to available resources
                for (int j = 0; j < m; j++) {
                    arr_a[j] += arr_c[i][j];
                }

                anyTerminated = 1;
                terminated[i] = 1;

                break;
            }
        }
        if (!anyTerminated) {
            deadlock = 1;
            break;
        }
    }

    if (deadlock) {
        c = 0;
        for (int i = 0; i < n; i++) {
            if (!terminated[i]) {
                c++;
            }
        }
        printf("Deadlocked. Number of processes: %d\n", c);
    } else {
        printf("Not deadlocked.\n");
    }

    printf("");

    fclose(fp);
    return 0;
}

int getM(const char *line) {
    int m = 1;
    for (int i = 0; i < strlen(line); ++i) {
        if (line[i] == ' ') {
            m++;
        }
    }
    return m;
}

