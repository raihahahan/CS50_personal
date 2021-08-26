#include <stdio.h>
#include <cs50.h>

int array[] = {2,1, 5, 4, 3, 6};
int LENGTH = 6;

bool isDuplicate(int arr[], int length);

int main(void)
{
    if (isDuplicate(array, LENGTH))
    {
        printf("Duplicate found\n");
    }
    else
    {
        printf("False.\n");
    }
}

bool isDuplicate(int arr[], int length)
{
    int index = 0;
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (arr[i] == arr[j])
            {
                return true;
            }
        }
    }
    return false;
}