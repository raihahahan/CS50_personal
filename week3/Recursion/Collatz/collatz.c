#include <stdio.h>
#include <cs50.h>

int collatzFinal(int n);
int collatzSteps(int n);
int collatz2(int n);

int steps = 0;

int main(void)
{
    int m = get_int("Int: ");
    printf("Final: %i\n",collatzFinal(m));
    printf("Steps: %i\n", collatzSteps(m));
    printf("Steps: %i\n", collatz2(m));
}

int collatzFinal(int n)
{
    if (n == 1) return n;
    return n%2 == 0 ? collatzFinal(n/2) : collatzFinal(3*n + 1);
}

int  collatzSteps(int n)
{
    if (n == 1) return steps;
    if (!(n%2))
    {
        steps++;
        return collatzSteps(n/2);
    }
    else
    {
        steps++;
        return collatzSteps(3*n + 1);
    }
}

int collatz2(int n)
{
    return n == 1 ? 0 : (n % 2) == 0 ? 1 + collatz2(n/2) : 1 + collatz2(3*n + 1);
}

// if n even, then  n/2
// if n odd, then 3n + 1