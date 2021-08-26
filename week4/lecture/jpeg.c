#include <stdint.h>
#include <stdio.h>

typedef uint8_t BYTE; // declares a datatype called BYTE

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }
}