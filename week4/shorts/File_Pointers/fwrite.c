#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* ptr = fopen("file.txt", "w");

    // int *arr2 = malloc(sizeof(int) * 12);
    char c = 'a';

    // for (int i = 0; i < 12; i++)
    // {
    //     *(arr2 + i) = i;
    // }


    fwrite(&c, sizeof(char), 1, ptr);

    fclose(ptr);
    return 0;
}