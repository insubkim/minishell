#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(void)
{
    char *s = readline(">");
    //printf("\n%s\n", s);
    rl_replace_line("hello", 5);
    printf("%s  ", s);
    rl_redisplay();
    printf("%s  ", s);
    s = readline(">");
    
}