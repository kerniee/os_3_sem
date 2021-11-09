#include<linux/input.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define KEY_RELEASED 0
#define KEY_PRESSED 1
#define KEY_HOLD 2
#define BUFF_LEN 3
#define SEQS_LEN 3
#define SEQ_LEN 3

int seqs[SEQS_LEN][SEQ_LEN] = {
    { 18, 25, -1 },
    { 25, 30, 46 },
    { 31, 24, -1 }
};

int curr_i = 0;

char* text[SEQS_LEN];

void check_buff(int* circ_buff)
{
    for (int seq_i = 0; seq_i < SEQS_LEN; seq_i++) {
        int valid = 1;

        for (int i = 0; i < SEQ_LEN; i++) {
            int buff_i = curr_i - i;
            if (buff_i < 0)
                buff_i += BUFF_LEN;

            if (seqs[seq_i][i] != circ_buff[buff_i] && seqs[seq_i][i] != -1) {
                valid = 0;
            }
        }
        if (valid == 1) {
            printf("\n%s\n", text[seq_i]);
        }
    }
}

int main()
{
    int file = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);

    text[0] = "I passed the Exam!";
    text[1] = "Get some cappuccino!";
    text[2] = "THE BEST COURSE EVEEEEEEEER!!!!!!!";

    printf("Shortcuts: P + E: %s\n", text[0]);
    printf("Shortcuts: C + A + P: %s\n", text[1]);
    printf("Shortcuts: O + S: %s\n", text[2]);

    int circ_buff[BUFF_LEN];
    for (int i = 0; i < BUFF_LEN; i++) {
        circ_buff[i] = 0;
    }

    struct input_event event;

    while (1) {
        read(file, &event, sizeof(event));

        if (event.value == KEY_RELEASED && event.type == EV_KEY) {
            for (int i = 0; i < BUFF_LEN; i++) {
                curr_i = 0;
                circ_buff[i] = 0;
            }
        }

        if (event.type != EV_KEY || event.value != KEY_PRESSED) {
            continue;
        }

        circ_buff[curr_i] = event.code;

        check_buff(circ_buff);

        curr_i++;
        if (curr_i == BUFF_LEN)
            curr_i = 0;
    }
    return 0;
}
