#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
    char *input;

    while (1) {
        input = readline("Enter text: ");

        if (strlen(input) >= 10) {
            printf("Error: Input must be less than 10 characters\n");
            free(input);
            continue;
        }

        if (!input) {
            break;
        }

        if (*input) {
            printf("You entered: %s\n", input);
            add_history(input);
        }

        free(input);
        rl_replace_line("", 0);
        rl_redisplay();
        rl_on_new_line();
    }

    return 0;
}