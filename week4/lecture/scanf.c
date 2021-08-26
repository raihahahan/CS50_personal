#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // get int
    int x;
    printf("x: ");
    scanf("%i", &x);
    printf("x: %i\n", x);

    // get string
    char *s = malloc(4);
    printf("s: ");
    scanf("%s", s); // don't need &s as s is fundamentally an address. s is a pointer to the address of the first character of the string
    printf("s: %s\n", s); // doesn't work as *s has garbage value. we haven't allocate memory for *s
    free(s);
}