#include <linux/input.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define KEY_PRESSED 1
#define KEY_RELEASED 0
#define KEY_HOLD 2


int main() {
    int file = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);

    struct input_event ev;

    while (1) {
        int rb = read(file, &ev, sizeof(ev));
        if (ev.type != EV_KEY || ev.value == KEY_HOLD)
            continue;
        if (ev.value == KEY_PRESSED) {
            printf("PRESSED 0x%x (%d)\n", ev.code, ev.code);
        } else {
            printf("RELEASED 0x%x (%d)\n", ev.code, ev.code);
        }
    }
    return 0;
}