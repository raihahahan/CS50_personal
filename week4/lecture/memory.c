#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // manual way of making a string
    char *s = malloc(4);
    s[0] = 'H';
    s[1] = 'I';
    s[2] = '!';
    s[3] = '\0';
    printf("%s\n", s);
    free(s);
}