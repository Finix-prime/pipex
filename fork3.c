#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    int fd_copy;
    int reader;
    char buffer[15];

    // Let's print the process' PID
    // for reference
    printf("My PID is %d\n", getpid());
    // Open our file and get the fd
    fd = open("infle.txt", O_RDONLY);
    if (!fd)
        return (1);
    // Duplicate that fd to the smallest unused fd
    fd_copy = dup(fd);
    if (!fd_copy)
        return (1);
    // Read from fd
    reader = read(fd, buffer, 10);
    if (reader == -1)
        return (1);
    buffer[reader] = '\0';
    printf("fd %d contains : %s\n", fd, buffer);
    // Read from fd copy
    reader = read(fd_copy, buffer, 10);
    if (reader == -1)
        return (0);
    buffer[reader] = '\0';
    printf("fd %d contains : %s\n", fd_copy, buffer);
    // Infinite loop to be able to go check
    // the open fds by this process
    // with ls -la /proc/PID/fd
    while (1)
        ;
}
