#include "../minishell.h"

int main()
{
	access("x", F_OK | X_OK);
	printf("%d\n", errno);
}
/*
	없는 파일은 errno = 2
	권한이 없는 파일은 errno = 13

*/