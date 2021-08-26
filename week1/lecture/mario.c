#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get positive integer from user
    int l;
    int h;
    do
    {
        l = get_int("Length: ");
        h = get_int("Height: ");

    }
    while (l < 1 && h < 1);

    // Print our that many question marks
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < l; i++)
        {
            printf("# ");
        }
        printf("\n");
    }



}
