#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

typedef struct
{
    person husband;
    person wife;
    int yearMarried;
}
couple;

typedef struct
{
    couple parents;
    person child_1;
    person child_2;
}
family;

int NUMBER;

int main(void)
{
    NUMBER = get_int("Number of people");

    person people[NUMBER];

    for (int i = 0; i < NUMBER; i++)
    {
        people[i].name = get_string("Whats the name?");
        people[i].number = get_string("What's their number?");
    }

    string find = get_string("FIND: ");


    for (int i = 0; i < NUMBER; i++)
    {
        if (strcmp(people[i].name, find) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
