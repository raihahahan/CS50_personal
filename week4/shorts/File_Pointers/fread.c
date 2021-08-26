#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* ptr = fopen("../../lecture/phonebook.csv", "r");

    char *arr2 = malloc(sizeof(char) * 12);
    fread(arr2, sizeof(char), 12, ptr);

    for (int i = 0; i < 12; i++) {
        printf("%c", *(arr2 + i));
    }

    printf("\n");
}