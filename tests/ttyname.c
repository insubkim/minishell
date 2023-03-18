 #include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
char *ttyname(int fd);

int main()
{
	char *s =ttyname(2);
	printf("%s\n", s);
	int fd = open("a", O_RDWR, 0644);
	s =ttyname(fd);
	printf("%s\n", s);
	return (0);
}