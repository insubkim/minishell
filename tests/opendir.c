#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

DIR *opendir(const char *name);

int main()
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("./")) != 0) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != 0) {
			printf ("%s\n", ent->d_name);
		}
		closedir (dir);
	}
	
	
}