#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "Segdisp.h"
#include "../advio.h"

static int fd = -1;
unsigned char seg7table[16] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

void SegDispShow(char c)
{
    fd = open("/dev/seg", O_RDWR);
    if (fd < 0)
        die("Can not open device");
    ioctl(fd, 0, c);
    close(fd);
}