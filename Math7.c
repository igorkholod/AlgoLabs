#include <stdio.h>
#include <stdarg.h>

int sum(int k, ...);

int main()
{
    printf("1 * 2 + 3 * 4 + 5 * 6 + 7 * 8 = %d\n", sum(8, 1, 2, 3, 4, 5, 6, 7, 8));
    printf("1 * 3 + 5 * 9 + 6 * 7 + 2 * 4 + 10 * 8 = %d\n", sum(10, 1, 3, 5, 9, 6, 7, 2, 4, 10, 8));
    printf("5 * 2 + 3 * 9 + 4 * 1 + 8 * 10 + 11 * 7 + 12 * 6 = %d\n", sum (12, 5, 2, 3, 9, 4, 1, 8, 10, 11, 7, 12, 6));
    
    return 0;
}

int sum(int k, ...)
{
    int s = 0;
    int m;
    va_list ptr;
    va_start(ptr, k);
    for (int i = 0; i < k; i += 2)
    {
        m = va_arg(ptr, int);
        m *= va_arg(ptr, int);
        s += m;
    }
    va_end(ptr);
    
    return s;
}
