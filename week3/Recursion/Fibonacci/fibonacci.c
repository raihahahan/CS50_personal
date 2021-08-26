#include <stdio.h>
#include <cs50.h>

long fib(int n);
long iter(int a, int b, int count);
long fibIter(int n);

int main(void)
{
    int m = get_int("Number: ");
    printf("Linear recursive process: %li\n", fib(m));
    printf("Linear iterative process: %li\n", fibIter(m));
}

long fib(int n)
{
    if (n == 1)
    {
        return 0;
    }

    if (n == 2)
    {
        return 1;
    }

    return fib(n-2) + fib(n-1);
}

long fibIter(int n)
{
    return iter(0, 1, n);
}

long iter(int a, int b, int count)
{
    if (count == 1)
    {
        return a;
    }
    return iter(a+b, a, count - 1);
}
