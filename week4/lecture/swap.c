#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i.\n", x, y);
    swap(&x, &y); // we pass in the address of x and y. so now *a and *b are pointer variables which points to the addresses x and y respectively.
    printf("x is %i, y is %i.\n", x, y);
}

void swap(int *a, int *b)
{
    int tmp = *a; // tmp stores the value of x.
    *a = *b; // address of a stores the value of *&x; *& means look into the contents of the address
    *b = tmp;  // address of b stores the value of tmp which is the value of a.
}