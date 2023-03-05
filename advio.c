#include "advio.h"


void StdInReadLine(char *buffer, int maxsize)
{
    int size = 0;
    do
    {
        char r = getchar();
        if (r == '\n')
            break;
        *buffer = r;
        buffer++;
        size++;
    } while ((size < maxsize - 1));
    *buffer = 0;
}

void WriteLine(const char *l)
{
    printf("%s\n", l);
}

void WColor(int color,const char *l){
    printf("\e[%dm%s\e[0m\n", color,l);
}