#include <stdio.h>

int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        printf("Usage: ./cp <originalFile> <newFile>\n");
        return 1;
    }

    FILE* ptr = fopen(argv[1], "r");
    FILE* ptr2 = fopen(argv[2], "w");

    char ch;
    while((ch = fgetc(ptr)) != EOF)
    {
        fputc(ch, ptr2);
    }
    printf("File copied successfully.\n");
}