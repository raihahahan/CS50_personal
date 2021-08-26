#include <stdio.h>

void printArr(int arr[]);
void bubbleSort(int arr[]);
void swap(int one, int two, int unswapped[]);
const int LENGTH = 21;

int array[] = {2, 3, 6, 1, 5, 7, 9, 10, 4, 8, 15, 11, 13, 18, 12, 14, 20, 17, 19, 16, 21};

int main(void)
{

}

void printArr(int arr[])
{
    for (int k = 0; k < LENGTH; k++)
    {
        printf("%i, ", arr[k]);
    }
    printf("\n");
}

void bubbleSort(int arr[])
{
    int counter = 0;
    for (int j = LENGTH - 1; j > 1; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if (arr[i] > arr[i+1])
            {
                swap(i, i+1, arr);
                counter++;
            }
        }
        if (counter == 0)
        {
            break;
        }
    }
}

void swap(int one, int two, int unswapped[])
{
    int elem1 = unswapped[one];
    int elem2 = unswapped[two];
    unswapped[one] = elem2;
    unswapped[two] = elem1;
}