#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	(*argv)[0] = 'z';
	(*argv)[1] = 0;
	
	execve("z", argv,envp);
}