#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
void rl_replace_line (const char *text, int clear_undo);
int main(void) {
    char *input;
    input = readline("Enter text: ");
    while (1) {
        
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
        input = readline("Enter text: ");
        
        rl_on_new_line();
        rl_redisplay();
        printf("\n");
        //sleep(3);
    }

    return 0;
}