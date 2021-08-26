#include <stdio.h>
#include <cs50.h>

bool valid_triangle(float x, float y, float z);

int main(void)
{
    float x, y, z;
    do
    {
        x = get_float("x: ");
        y = get_float("y: ");
        z = get_float("z: ");
    }
    while (x <= 0 && y <= 0 && z <= 0);

    if (valid_triangle(x, y, z))
    {
        printf("VALID\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool valid_triangle(float x, float y, float z)
{
    if (x <= 0 || y <= 0 || z <= 0) { return false; }
    return x + y > z && x + z > y && y + z > x;
}