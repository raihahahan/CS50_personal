#include <stdio.h>
#include <cs50.h>
#include <math.h>

void bubbleSort(int arr[]);
void printArr(int arr[]);
void swap(int one, int two, int unswapped[]);
int binarySearch(int arr[], int len, int find);
int midpoint(int len);

const int LENGTH = 15;

int array[] = {11, 23, 8, 14, 30, 9, 6, 17, 22, 28, 25, 15, 7, 10, 19};

int main(void)
{
    int search = get_int("Find: ");
    bubbleSort(array);
    int result = binarySearch(array, LENGTH, search);
    if (result == 0)
    {
        printf("Found.\n");
    }
    else
    {
        printf("Not found.\n");
    }
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

void printArr(int arr[])
{
    for (int k = 0; k < LENGTH; k++)
    {
        printf("%i, ", arr[k]);
    }
    printf("\n");
}

void swap(int one, int two, int unswapped[])
{
    int elem1 = unswapped[one];
    int elem2 = unswapped[two];
    unswapped[one] = elem2;
    unswapped[two] = elem1;
}

int binarySearch(int arr[], int len, int find)
{
    while (len > 0)
    {
        int m = midpoint(len);
        int f = floor(len / 2);
        if (arr[m] == find)
        {
            return 0;
        }
        else if (arr[m] < find)
        {
            int newArr[(int) f];
            for (int j = 0, i = m + 1; j < f && i < len; j++, i++)
            {
                newArr[j] = arr[i];
            }
            return binarySearch(newArr, f, find);
        }
        else if (arr[m] > find)
        {
            int newArr[(int) f];
            for (int j = 0, i = 0; j < f && i < f; j++, i++)
            {
                newArr[j] = arr[i];
            }
            return binarySearch(newArr, f, find);
        }
        else
        {
            return 1;
        }
    }
    return 1;
}

int midpoint(int len)
{
    return ceil(len / 2);
}

