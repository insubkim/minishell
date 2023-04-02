#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
 #include <unistd.h>

int main()
{
	struct stat	stats;
	char *name = "..";
	
	stat(name, &stats);
	int i = S_ISDIR(stats.st_mode);
	printf("i == %d\n", i);
	//if (i == -1)
		//1. access(path | R_OK)
			//if error No permission error
		//2. access(path | R_OK )
}