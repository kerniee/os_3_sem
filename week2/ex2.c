#include <stdio.h>

int main() {
    char s[256];
    printf("Enter a string\n");
    fgets(s, 256, stdin);
    printf("Length of the string: %lu chars", strlen(s)-1);
    return 0;
}