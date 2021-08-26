#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE* ptr = fopen("../../lecture/phonebook.csv", "r");
    char ch = fgetc(ptr);
    printf("%c\n", ch);

    fclose(ptr);
}