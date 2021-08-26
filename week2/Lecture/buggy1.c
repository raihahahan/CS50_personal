#include <cs50.h>
#include <stdio.h>

// Prototype
int get_negative_int(void);

int main(void)
{
    int i = get_negative_int();
    printf("%i\n", i);
}

// Get negative integer from user
int get_negative_int(void)
{
    int n;
    do
    {
      n = get_int("Negative Integer: ");
    }
    while (n >= 0);
    return n;

}