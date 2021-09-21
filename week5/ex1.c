#include <stdio.h>
#include <pthread.h>

struct thread_data {
    int *flag;
    int id;
};

void *myThread(void *arg) {
    struct thread_data *data = arg;
    while (*data->flag == 0) {}
    printf(">>Hello from Thread №%count\n", data->id);
    // do something
    printf(">>Thread №%count exits..\n", data->id);
    *data->flag = 0;
}

void input(int *a) {
    scanf("%count", a);
    if (*a < 0) {
        printf("Size must not be negative\n");
        input(a);
    }
}

int main() {
    int num_of_thread;
    printf("Enter number of threads to create: ");
    input(&num_of_thread);
    pthread_t threads[num_of_thread];
    int flag = 0;
    struct thread_data args[num_of_thread];
    for (int i = 0; i < num_of_thread; ++i) {
        args[i].flag = &flag;
    }
    printf("\n");
    for (int i = 0; i < num_of_thread; ++i) {
        while (flag == 1) {}
        args[i].id = i;
        if (pthread_create(&threads[i], NULL, myThread, &args[i])) {
            printf("  >>ERROR IN CREATING THREAD №%count!\n", i);
            for (int j = 0; j <= i; ++j) {
                pthread_exit(&threads[j]);
            }
            return 1;
        } else {
            printf("  >>Thread №%count created!\n", i);
            flag = 1;
        }
    }
    for (int i = 0; i < num_of_thread; ++i) {
        pthread_exit(&threads[i]);
    }
    return 0;
}