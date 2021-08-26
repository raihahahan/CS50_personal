#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // only accept exactly one command line argument
    {
        printf("Usage: ./recover imageName\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r"); // fopen() returns a file pointer. opens a memory card file
    if (input == NULL)
    {
        printf("Error: Cannot open file!\n");
        return 1;
    }

    int counter = 0; // counter to check number of JPEG files opened
    uint8_t *buffer = malloc(512 * sizeof(uint8_t)); // array to store data from input
    char *fileName = malloc(sizeof(char) * 8); // name of output file
    FILE *output = NULL; // output is pointer to fileName

    while (fread(buffer, 512, 1, input) == 1) // read 512 bytes of data from input into buffer
    {
        // check if JPEG file
        // read the first four bytes of the file
        // Byte: use uint8_t
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) ==
            0xe0) // take the bitwise & of buffer[3] and 0xf0. just look at the first four bits of this 8-bit byte and set the remaining 4 bits to 0.
        {
            if (counter == 0)
            {
                // first JPEG file
                sprintf(fileName, "%03i.jpg", counter); // initialises char *fileName = 00counter.jpg;
                output = fopen(fileName, "w"); // open a file: output is a pointer to the file name of fileName
                if (output == NULL)
                {
                    printf("File not working.\n");
                    return 1;
                }
                fwrite(buffer, 512, 1, output); // write 512 bytes of data from buffer to output
                counter++;
            }
            else
            {
                // not first JPEG file: fclose() current JPEG file, create new JPEG file
                fclose(output); // close current JPEG
                sprintf(fileName, "%03i.jpg", counter); // initialise char *fileName = 00counter.jpg;
                output = fopen(fileName, "w"); // set output pointer to the new JPEG file
                if (output == NULL)
                {
                    printf("File not working.\n");
                    return 1;
                }
                fwrite(buffer, 512, 1, output);
                counter++;
            }
        }
        else
        {
            if (counter > 0)
            {
                // if jpeg header not found but we are already inside a jpeg file
                fwrite(buffer, 512, 1, output);
            }

            // else, if jpeg header not found and we are still not inside a jpeg file, continue iteration without writing into any file.
        }
    }

    // close input and output files
    fclose(input);
    fclose(output);

    // free dynamically allocated memory from buffer and fileName
    free(buffer);
    free(fileName);

    return 0;
}

/*
TODO
- Open memory card
- Look for a beginning of a JPEG
- Open a new JPEG file
- Write 512 bytes until a new JPEG is found.

JPEG format:
-[0xff, 0xd8, 0xff, 0xen], where 0 <= n<=e

*/