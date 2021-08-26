#include <stdio.h>
#include <cs50.h>

void swap(int one, int two, string unswapped[]);
void printArr(string arr[]);

const int LENGTH = 5;
int array[] = {1, 2, 0, 3, 5};
string array1[] = {"first", "second", "zero", "third", "fifth"};
int main(void)
{
    int counter = 0;
    for (int j = LENGTH - 1; j >= 0; j--)
    {
        counter = 0;
        for (int i = 0; i < j; i++)
        {
            if (array[i] < array[i+1])
            {
                swap(i, i+1, array1);
                counter++;
            }
        }
        if (counter == 0)
        {
            break;
        }
    }



    printArr(array1);
}

void swap(int one, int two, string unswapped[])
{
    string elem1 = unswapped[one];
    string elem2 = unswapped[two];
    unswapped[one] = elem2;
    unswapped[two] = elem1;
}

void printArr(string arr[])
{
    for (int k = 0; k < LENGTH; k++)
    {
        printf("%s, ", arr[k]);
    }
    printf("\n");
}
