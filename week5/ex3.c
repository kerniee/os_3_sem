#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_COUNTER 5
#define CYCLES 10000
#define CYCLES_PRINT 500

struct thread_data {
    int cycle;
    int count;
    int MAX;
    int producer_alive;
    int consumer_alive;
};

void cond_sleep(int *flag) {
    while (*flag == 0) {
        usleep(1e2);
    }
}

void cond_wakeup(int *flag) {
    *flag = 1;
}

void *producerThread(void *arg) {
    struct thread_data *data = arg;
    while (data->cycle < CYCLES) {
        if (data->count == data->MAX) {
            data->cycle++;
            data->producer_alive = 0;
            if (data->cycle % CYCLES_PRINT == 0) {
                printf("cycle: %d, producer_alive: %d, consumer_alive: %d\n",
                       data->cycle,
                       data->producer_alive,
                       data->consumer_alive);
            }
            cond_sleep(&data->producer_alive);
        } else {
            data->count++;
        }
        if (data->count == data->MAX - 1) {
            cond_wakeup(&data->consumer_alive);
        }
    }
}

void *consumerThread(void *arg) {
    struct thread_data *data = arg;
    while (data->cycle < CYCLES) {
        if (data->count == 0) {
            data->consumer_alive = 0;
            if (data->cycle % CYCLES_PRINT == 0) {
                printf("cycle: %d, producer_alive: %d, consumer_alive: %d\n",
                       data->cycle,
                       data->producer_alive,
                       data->consumer_alive);
            }
            cond_sleep(&data->consumer_alive);
        } else {
            data->count--;
        }
        if (data->count == 1) {
            cond_wakeup(&data->producer_alive);
        }
    }
}

int main() {
    pthread_t producer_thread;
    pthread_t consumer_thread;
    struct thread_data args;
    args.cycle = 0;
    args.count = 0;
    args.MAX = MAX_COUNTER;
    args.producer_alive = 1;
    args.consumer_alive = 0;

    pthread_create(&producer_thread, NULL, producerThread, &args);
    pthread_create(&consumer_thread, NULL, consumerThread, &args);


    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}