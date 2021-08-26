#include <cs50.h>
#include <stdio.h>
#include <math.h>

void printArr(int arr[], int len);
// void mergeSort(int arr[], int len);
void merge(int arr1[], int len1, int arr2[], int len2);
int findSmallestIndex(int arr[], int len);
void remove_element(int array[], int index, int length);

const int LENGTH = 6;
int result[LENGTH];
int testArray[] = {2, 4, 1, 5, 3, 6};
int test1[] = {2, 3, 5, 8};
int test2[] = {1, 4, 6};

int c = 0;



int main(void)
{
    merge(test1, 3, test2, 3);
    printArr(result, 6);
    return 0;
}

int mergeSort(int arr[], int len)
{
    int m = (int) ceil(len / 2); // midpoint index of array
    int f = (int) floor(len / 2); // length of new truncated array
    int interArr[(int) f]; // intermediate array
    

    if (len == 1)
    {
        resultL[c] = arr[0];
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
        return merge(resultL, f, resultR, f);
    }
}

void remove_element(int array[], int index, int length)
{
   int i;
   for(i = index; i < length - 1; i++) array[i] = array[i + 1];
}

void merge(int arr1[], int len1, int arr2[], int len2)
{
    int count = 0;
    int length = len1 + len2;
    while (count < length - 1)
    {
        int small1Index = findSmallestIndex(arr1, len1);
        int small2Index = findSmallestIndex(arr2, len2);

        int small1 = arr1[small1Index];
        int small2 = arr2[small2Index];

        if (small1 < small2)
        {
            result[count] = small1;
            remove_element(arr1, small1Index, len1);
            count++;
        }
        else
        {
            result[count] = small2;
            remove_element(arr2, small2Index, len2);
            count++;
        }
    }
    int last1 = arr1[len1];
    int last2 = arr2[len2];
    int last = last1 > last2 ? last1 : last2;

    result[count] = last;

}


void printArr(int arr[], int len)
{
    for (int k = 0; k < len; k++)
    {
        printf("%i, ", arr[k]);
    }
    printf("\n");
}

int findSmallestIndex(int arr[], int len)
{
    int smallestIndex = 0;
    int smallest;

    for (int j = 0; j < len; j++)
    {
        if (arr[j] <= arr[smallestIndex])
        {
            smallestIndex = j;
        }
    }
    return smallestIndex;
}
