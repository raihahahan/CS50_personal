#include <stdio.h>
#include <cs50.h>

void draw(int h);

int main(void)
{
    int i;
    i = get_int("Height: ");
    draw(i);
}

void draw(int h)
{
    if (!h)
    {
        return;
    }

    draw(h - 1);

    for (int i = 0; i < h; i++)
    {
        printf("#");
    };
    printf("\n");
}