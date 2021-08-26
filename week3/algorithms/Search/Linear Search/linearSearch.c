#include <stdio.h>
#include <cs50.h>

const int LENGTH = 20;

int array[] = {2, 3, 6, 1, 5, 7, 9, 10, 4, 8, 15, 11, 13, 18, 12, 14, 20, 17, 19, 16};

int main(void)
{
    int find = get_int("Find: ");

    for (int i = 0; i < LENGTH; i++)
    {
        if (array[i] == find)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}