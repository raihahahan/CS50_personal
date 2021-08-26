#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./cat <filename>\n");
        return 1;
    }

    FILE* ptr = fopen(argv[1], "r");
    char ch;
    while((ch = fgetc(ptr)) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");

    fclose(ptr);
    return 0;
}