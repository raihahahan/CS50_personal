#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc >= 2) // if user types 2 words at the prompt, then true. number of words include both command and argument
    {
        for (int j = 1; j < argc; j++)
        {
            for (int i = 0, n = strlen(argv[1]); i < n; i++)
            {
                printf("%c", argv[j][i]);
            }
            printf(" ");
        }
    }
    else
    {
        printf("hello, world\n");
    }
}

// function main takes integer as one input, and an array of strings as another input
// argc: argument count => integer that represents the number of words that the user is going to type at the prompt.
// argv: argument vector => vector is a fancy way of saying list. it is a variable that is going to store in an array all of the strings that a user types at the prompt