#include <stdio.h>
#include <cs50.h>


int main(void)
{
    char c1 = 'H',
         c2 = 'I',
         c3 = '!';

    string s = "HI!";
    string t = "BYE!";

    //printf("%i %i %i\n", c1, c2, c3);

    printf("%i %i %i %i %i %i %i %i\n", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);
    printf("%i %i %i %i %i\n", t[0], t[1], t[2], t[3], t[4]);

}