#ifndef _H_ADVIO_
#define _H_ADVIO_
#include <stdio.h>
#include <errno.h>

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

#define die(xx)                                       \
    {                                                 \
        WColor(RED,"An fatal error happened:");       \
        fprintf(stderr, "ERROR:%x\n%s\n", errno, xx); \
        exit(1);                                      \
    }

void StdInReadLine(char *buffer, int maxsize);
void WriteLine(const char *l);
void WColor(int color,const char *l);

#endif