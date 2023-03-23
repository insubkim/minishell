#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include "minishell.h"

void	free_signal(int	sig, t_list *list)
{
	t_node	*cur;
	t_node	*cur_free;
	cur = list->pid_head;
		list->pid_size = 0;
		while (cur != NULL)
		{
			cur_free = cur;
			kill(cur->pid_value, sig);
			if (cur->next != NULL)
				cur = cur->next;
			free(cur_free);
		}
		list->pid_head = NULL;
}

void	signalHandler1(int sig, t_list *list)
{
	t_node	*cur;
	t_node	*cur_free;

	if (sig == SIGINT)
	{
		free_signal(sig, list);
	}
	if (sig == SIGQUIT)
	{
		free_signal(sig, list);
	}	
}

void	signalHandler2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("Parent SIGQUIT\n");
	}
}

t_list *init_list(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->pid_head = NULL;
	list->pid_size = 0;
	return (list);
}

void	add_pid_first(t_list *list, int pid_value)
{
	t_node	*tmp;

	tmp = (t_node *)malloc(sizeof(t_node));
	if (!tmp)
		return ;
	tmp->pid_value = pid_value;
	tmp->next = NULL;
	list->pid_head = tmp;
	list->pid_size++;
}

void	add_pid_list(t_list *list, int pid_value)
{
	t_node	*tmp;
	t_node	*cur;

	tmp = (t_node *)malloc(sizeof(t_node));
	if (!tmp)
		return ;
	tmp->pid_value = pid_value;
	tmp->next = NULL;
	cur = list->pid_head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = tmp;
	list->pid_size++;
}

int main()
{
    int pid;
    int status;
    t_list *test;
    t_node *cur;

	
    signal(SIGINT, signalHandler2);
    signal(SIGQUIT, signalHandler2);
    test = init_list();
    while (1)
    {
        char *line;
        int i;

        i = 0;
		if (test->pid_size == 0)
		{
        	line = readline("minishell> ");
        	if (!line)
            	break;
        	add_history(line);
		}
		if (line[0] == 'a')
        {
            if (test->pid_size == 0)
            {
                printf("firstChild\n");
                pid = fork();
				if (pid != 0)
                	add_pid_first(test, pid);
				printf("%d\n", test->pid_head->pid_value);
            }
            else
            {
                printf("anotherChild\n");
                pid = fork();
				if (pid != 0)
                	add_pid_list(test, pid);
            }
            wait(&status);
        }
        if (pid > 0)
        {
            signal(SIGINT, signalHandler2);
            signal(SIGQUIT, signalHandler2);
            wait(&status);
        }
		if (pid == 0)
        {
            signal(SIGINT, signalHandler1);
            signal(SIGQUIT, signalHandler1);
			wait(&status);
        }
    }
    return (0);
}
