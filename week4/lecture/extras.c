#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // pointer variables. i.e give me a pointer to the integer called x and y
    // i.e give a variable called x that can store the address of an int in.
    int *x; 
    int *y;

    x = malloc(sizeof(int)); // we are not assigning any memory allocation until this line

    *x = 42;
    *y = 13;

    y = x;

    *y = 13;
}