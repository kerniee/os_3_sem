#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input(int *a) {
    scanf("%d", a);
    if (*a < 0) {
        printf("Must not be negative\n");
        input(a);
    }
}

#define COUNTER_SIZE_IN_BITS 2

struct counter {
    unsigned int value: COUNTER_SIZE_IN_BITS;
};

struct page_table_entry {
    int id;
    struct counter counter;
} const page_table_entry_default = {-1, 0};

int main() {
    int page_num;
    printf("Enter the number of pages\n");
    input(&page_num);
    struct page_table_entry pages[page_num];
    for (int i = 0; i < page_num; ++i) {
        pages[i] = page_table_entry_default;
    }

//    char fpath[] = "Lab 09 input.txt";
    char fpath[] = "my_input.txt";
    FILE *file = fopen(fpath, "r");

    unsigned int page_id;
    double hits = 0, counter = 0;
    while (1) {
        int flag = fscanf(file, "%u", &page_id);
        if (flag == -1) {
            // End of file
            break;
        } else {
            counter++;
        }
        // Print
        for (int i = 0; i < page_num; ++i) {
            printf("i = %i id = %i counter = %u\n", i, pages[i].id, pages[i].counter.value);
        }
        printf("current page number: %i\n\n", page_id);
        // Update counter
        int found = 0;
        for (int i = 0; i < page_num; ++i) {
            if (pages[i].id == page_id) {
                found = 1;
                pages[i].counter.value = pages[i].counter.value |= 1 << (COUNTER_SIZE_IN_BITS - 1);
            } else {
                pages[i].counter.value >>= 1;
            }
        }
        // Miss
        if (found == 0) {
            struct page_table_entry *min_page = &pages[0];
            if (min_page->id != -1) {
                for (int i = 1; i < page_num; ++i) {
                    if (pages[i].id == -1) {
                        min_page = &pages[i];
                        break;
                    }
                    if (pages[i].counter.value < min_page->counter.value) {
                        min_page = &pages[i];
                    }
                }
            }
            min_page->id = page_id;
            min_page->counter.value = 1 << (COUNTER_SIZE_IN_BITS - 1); // Max value
        }
        hits += found;
    }
    // 10 data frames: Hit: 9.000000; Miss: 1.000000; Ratio: 9.000000
    // 50 data frames: Hit: 51.000000; Miss: 949.000000; Ratio: 0.053741
    // 10 data frames: Hit: 94.000000; Miss: 906.000000; Ratio: 0.103753
    printf("Hit: %f; Miss: %f; Ratio: %f\n", hits, counter - hits, hits / (counter - hits));
    fclose(file);
    return 0;
}