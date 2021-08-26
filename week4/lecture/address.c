#include <stdio.h>


int main(void)
{
    int n = 50;
    int *p = &n;
    printf("%p\n", p);

    typedef char *string;

    char *my_string = "Hello World.";
    string s = "HI!";
    printf("%c\n", *my_string);
    printf("%c\n", (*s+1));
    printf("%i\n", (*(s + 3)));
    printf("%c\n", my_string[1]);
   // printf("%c\n", my_string[1900000]);
    printf("%p\n", &my_string);
    // printf("%s\n", s);
    // printf("%p\n", &s[0]);
    // printf("%c\n", s[1]);
    // printf("%c\n", s[2]);
}