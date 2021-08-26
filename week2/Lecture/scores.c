#include <stdio.h>
#include <cs50.h>

float average(int size, int scores[]);



int main(void)
{
    // int total = get_int("Total number of scores: ");
    // int scores[total];
    int TOTAL = get_int("Length: ");
    int scores[TOTAL];

    for (int i = 0; i < TOTAL; i++)
    {
        scores[i] = get_int("Score: ");
    }


    printf("Average: %f\n", average(TOTAL, scores));
}

float average(int length, int array[])
{
    int sum = 0;
    for (int j = 0; j < length; j++ )
    {
        sum += array[j];
    }
    return sum / (float) length; // only requires one float to be involved
}

