#include <stdio.h>
#include <cs50.h>

long factorial(int n);
long iter(int count, long result, int n);
long iterFact(int n);
long fact2(int n);

int main(void)
{
    int m = get_int("Factorial: ");
    printf("Linear Recursive process: %li\n", factorial(m));
    printf("Linear Iterative process: %li\n", iterFact(m));
    printf("Loop Iterative: %li\n", fact2(m));
}

long factorial(int n)
{
    if (n == 0) return 1; // base case
    else return n * factorial(n - 1); // recursive case
}

long iterFact(int n)
{
    return iter(0, 1, n);
}

long iter(int count, long result, int n)
{
    if (count == n) return result;
    else return iter(count + 1, (result * (count + 1)), n);
}

long fact2(int n)
{
    long product = 1;
    while (n > 0)
    {
        product *= n;
        n--;
    }
    return product;
}