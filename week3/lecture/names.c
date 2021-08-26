#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]) // linear search
{
    if (argc != 2)
    {
        printf("Usage: ./names name\n");
        return 1;
    }
    string name = argv[1];
    string names[] = {"Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"}; // alphabetical order
    int length = 7;
    for (int i = 0; i < length; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;

}

/*
strcmp:
     - if strings are identical letter by letter, return 0
     - if first string come before 2nd string in ASCII, return -ve value
     - if first string come after 2nd string in ASCII, return +ve value
     - checks ASCII value character by character
*/