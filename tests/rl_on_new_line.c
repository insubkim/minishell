#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
int main()
{
    char *s = readline(">");
    rl_replace_line("hello", 1000);
    char *p = readline(">");

    printf("[ %s ]\n",s);
    printf("[ %s ]\n",p);
    return (0);
}

