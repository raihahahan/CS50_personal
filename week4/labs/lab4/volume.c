// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44; // use uint8_t to iterate through these 44 bytes

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]); // converts string argument argv[3] into a float

    // TODO: Copy header from input file to output file
    uint8_t *header = malloc(sizeof(uint8_t) * HEADER_SIZE); // dynamically allocate memory for header
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t *sample = malloc(sizeof(int16_t));
    while (fread(sample, sizeof(int16_t), 1, input))
    {
        sample = malloc(sizeof(int16_t));
        *sample *= factor;
        fwrite(sample, sizeof(int16_t), 1, output);
        free(sample);
    }

    free(header);

    // Close files
    fclose(input);
    fclose(output);
}

/*
WORKINGS

    1. create an array of bytes to store the data from the WAV file header that you'll read from the input file ==> represent in array with 44 uint8_t elements, because the header file is 44 bytes long
    2. use fwrite to write the header file from the array into the output file
    3. use fread to read 2 byte samples from input file until we reach EOF and store in a buffer ==> represent samples using int16_t: 8 bytes
    4. use fwrite to write the samples from buffer into the output file.

*/