#include <stdio.h>


// Prototype ==> hint only
void meow(int n); // Prototype


int main(void)
{
    meow(3);
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
        {
            printf("meow\n");
        }
}