#include <fcntl.h>
#include "Led.h"
#include "../advio.h"

int LedSwitch(char c)
{
    static char nnstat[4];
    int fd = open("/dev/gled", O_RDWR);
    if (fd < 0)
    {
        die("Device open failed");
    }
    printf("Curr=%x\n", nnstat[c]);
    nnstat[c] = !nnstat[c];
    if (nnstat[c])
    {
        ioctl(fd, 1, c);
    }
    else
    {
        ioctl(fd, 0, c);
    }
    close(fd);
    return nnstat[c];
}