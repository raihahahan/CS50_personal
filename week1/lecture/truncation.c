#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get numbers from user
    int x = get_int("x: ");
    int y = get_int("y: ");

    // Divide x by y
    float z = (float) x / (float) y; // x / y is an integer, truncating the digits after the int. float z will only convert this int into a floating point number. eg. 2.5 ==> 2 ==> 2.000000
    printf("Division: %f\n", z);

    printf("x is %i ", x);
    printf("and y is %i\n", y);
}

