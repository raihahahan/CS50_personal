#include <stdio.h>
#include <math.h>

void printArr(int arr[], int len);
int mergeSort(int arr[], int len);
// void merge(int arr, int len1, int len2) ;

int counter = 0;

const int LENGTH = 21;
const int LENGTH2 = 6;

int result[LENGTH2];
int array[] = {2, 4, 1, 5, 3, 6};

int main(void)
{
    mergeSort(array, LENGTH2);
    printArr(result, LENGTH2);
    return 0;

}

int mergeSort(int arr[], int len)
{
    int m = (int) ceil(len / 2); // midpoint index of array
    int f = (int) floor(len / 2); // length of new truncated array
    int interArr[(int) f]; // intermediate array

    if (len == 1)
    {
        result[counter] = arr[0];
        counter++;
        return 0;
    }
    else
    {
        int newArr1[(int) f]; // LHS array
        int newArr2[(int) f]; // RHS array

        // create LHS array
        for (int j = 0, i = 0; j < f && i < f; j++, i++)
        {
            newArr1[j] = arr[i]; // creates LHS of array
        }

        // create RHS of array
        for (int j = 0, i = m + 1; j < f && i < len; j++, i++)
        {
            newArr2[j] = arr[i]; // creates RHS of array
        }

        return mergeSort(newArr1, f);
        return mergeSort(newArr2, f);
    }

}


void printArr(int arr[], int len)
{
    for (int k = 0; k < len; k++)
    {
        printf("%i, ", arr[k]);
    }
    printf("\n");
}


// }