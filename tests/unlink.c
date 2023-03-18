#include <unistd.h>
int unlink(const char *pathname);
#include <fcntl.h>
int main()
{
    int fd = open ("a", O_RDWR, 0644);
    int id = fork();

    
    if (id == 0)
        while (1)
            ;
        unlink("a");
    return (0);
}