#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SIZE 16
char send_buff[BUFF_SIZE] = "Addition";
char recv_buff[BUFF_SIZE];

int main()
{
    int fd, ret;
    fd = open("/dev/AddDev", O_RDWR);
    if (fd < 0)
    {
        perror("\nError: Couldn't open Add device\n");
        return fd;
    }

    ret = write(fd, send_buff, strlen(send_buff));
    if (ret < 0)
    {
        perror("\nError: Couldn't write to Add device\n");
        return ret;
    }
    printf("\nAddDev: Wrote %d bytes\n", ret);

    ret = read(fd, recv_buff, BUFF_SIZE);
    if (ret < 0)
    {
        perror("Error: Couldn't read from Add device\n");
        return ret;
    }
    printf("\nAddDev: Read %d bytes : %s\n", ret, recv_buff);
    return 0;
}