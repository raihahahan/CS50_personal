#include <stdio.h>
#include <cs50.h>

const int LENGTH = 8;

int array[] = {1, 3, 2, 5, 4, 6, 8, 7};
string array1[] = {"one", "three", "two", "five", "four", "six", "eight", "seven"};

int main(void)
{
    for (int i = 0; i < LENGTH; i++)
    {
        int largestIndex = i;
        int current = array[i];
        int largest;

        string current1 = array1[i];
        string largest1;

        for (int j = i; j < LENGTH; j++)
        {
            if (array[j] > array[largestIndex])
            {
                largestIndex = j;
            }
        }

        largest = array[largestIndex];

        largest1 = array1[largestIndex];

        array[largestIndex] = current;
        array[i] = largest;

        array1[largestIndex] = current1;
        array1[i] = largest1;
    }

    for (int k = 0; k < LENGTH; k++)
    {
        printf("%s, ", array1[k]);
    }
}
