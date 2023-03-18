#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("Terminal window size: %d rows x %d columns\n", w.ws_row, w.ws_col);
    return 0;
}