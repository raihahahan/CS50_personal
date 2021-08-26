#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");
    int n = strlen(s) + 1;
    char *t = malloc(n);

    if (t == NULL)
    {
        return 1;
    }

    for (int i = 0, m = strlen(s); i <= m ; i++)
    {
        *(t + i) = *(s + i);
    }

    if (strlen(t) > 0)
    {
        *t = toupper(*t);
    }

    strcpy(t, s);

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
}