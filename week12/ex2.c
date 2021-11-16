#include <linux/input.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define KEY_RELEASED 0
#define KEY_PRESSED 1
#define KEY_HOLD 2


int main() {
    int file = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);

    struct input_event event;

    while (1) {
        read(file, &event, sizeof(event));
        if (event.type != EV_KEY)
            continue;
        if (event.value == KEY_PRESSED) {
            printf("PRESSED 0x%x (%d)\n", event.code, event.code);
        } else if (event.value == KEY_RELEASED) {
            printf("RELEASED 0x%x (%d)\n", event.code, event.code);
        }
    }
    return 0;
}
