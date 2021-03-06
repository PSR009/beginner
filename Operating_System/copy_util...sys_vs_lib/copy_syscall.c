#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#define BUFF_SIZE 64

int main(int argc, char *argv[])
{
    int fd_s, fd_d, in, out;
    char buff[BUFF_SIZE];

    fd_s = open("source.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
    if (fd_s == -1)
    {
        perror("Error opening the source file\n");
        exit(EXIT_FAILURE);
    }
    //write(fd_s, "Hello\n", size);
    fd_d = open("dest.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
    if (fd_d == -1)
    {
        perror("Error opening the dest. file\n");
        exit(EXIT_FAILURE);
    }
    while ((in = read(fd_s, buff, BUFF_SIZE)) > 0)
    {
        out = write(fd_d, buff, in);
        if (out != in)
        {
            perror("Error copying");
        }
    }
    write(STDOUT_FILENO, "FILES COPIED\n", 15);
    close(fd_s);
    close(fd_d);
    return 0;
}