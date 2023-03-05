#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <math.h>
#include "../advio.h"
#include "Stepper.h"
//#define L_DEBUG
#include "../debug.h"

static int fd = -1;
volatile static double speed = 0;

void rollrollroll();

void StepperSetSpeed(int c)
{
    speed = c / 100.0;
    printf("Speed=%f", speed);
}

void StepperMThreadInit()
{
    static pthread_t rollll;
    pthread_create(&rollll, NULL, (void *)&rollrollroll, NULL);
}

void rollrollroll()
{
    int i = 0;
    double ospeed = speed;
    fd = open("/dev/stepper", O_RDWR);
    if (fd < 0)
    {
        die("Device open failed");
    }
    else
    {
        printf("Device handler = %x\n", fd);
    }
    DEBUG_POINT;
    while (1)
    {
        DEBUG_POINT;
        /*if (ospeed != speed)
        {
            ospeed = speed;
            printf("TSpeed Changed: %f\n", speed);
        }*/
        DEBUG_POINT;
        ospeed = speed;
        for (i = 0; i < 4; i++)
        {
            DEBUG_POINT;
            if (ospeed > 0)
            {
                ioctl(fd, 0, i);
                usleep((int)(7000.0 / ospeed));
            }
            else if (ospeed < 0)
            {
                ioctl(fd, 0, 3 - i);
                usleep((int)(-7000.0 / ospeed));
            }
            DEBUG_POINT;
        }
        DEBUG_POINT;
    }
}