#define DEBUG_POINT _debugp(__LINE__)

void _debugp(int line)
{
    #ifdef L_DEBUG
    printf("[DEBUG POINT] Line %d", line);
    getchar();
    #endif
}