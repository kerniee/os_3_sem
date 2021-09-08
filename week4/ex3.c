#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 256

int input(char *word, int n) {
    printf("> ");
    fgets(word, n, stdin);
}

int main() {
    printf("Hello! This is a little shell, which can execute commands you give to it. \n"
           "Enter 'exit_shell' to exit shell (Wow!)\n");

    char word[INPUT_SIZE] = "";
    char HALT_WORD[INPUT_SIZE] = "exit_shell\n";
    input(word, INPUT_SIZE);
    while (strcmp(word, HALT_WORD) != 0) {
        system(&word);
        input(word, INPUT_SIZE);
    }
    return 0;
}