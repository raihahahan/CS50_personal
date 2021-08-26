#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// prototypes
string caesar(string word, int key, int length);
int convert_str_int(string s);
char convert_int_char(int i);

int main(int argc, string argv[])
{
    // to prevent segmentation fault
    if (argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key_converted = convert_str_int(argv[1]); // converts string integer key to integer
    int l = strlen(argv[1]); // stores the length of argv[1] string

    // algorithm to check if any digits in argv[1] is not an integer
    for (int m = 0; m < l; m++)
    {
        // integers are 48 <= i <= 71 in ascii. argc != 2 checks if more than one cli args are entered
        if ((int) argv[1][m] < 48 || (int) argv[1][m] > 71 || argc != 2)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // get plaintext from user
    string plaintext = get_string("plaintext: ");

    // create an array of characters with length of plaintext to get ciphered string
    string ciphered = caesar(plaintext, key_converted, strlen(plaintext));

    // final result
    printf("ciphertext: %s\n", ciphered);
    return 0;
}

// function to convert "string integer" into integer
int convert_str_int(string s)
{
    int result = 0;
    int m;

    if (strlen(s) > 1)
    {
        // convert to ascii
        m = ((int) s[0] - 48) * 10;
        for (int j = 1, n = strlen(s); j < n; j++)
        {
            result = (int) s[j] - 48;
            m += result;
        }
        return m;
    }
    else
    {
        return m = (int) s[0] - 48;
    }
}


// caesar algorithm: returns the ascii integer of a character in the string, given index as input
string caesar(string word, int key, int length)
{
    char ciphered[length]; // to return this array of characters

    int result = 0;

    for (int i = 0; i < length; i++)
    {
        char ref = word[i];
        if (isalpha(ref))
        {
            if (isupper(ref))
            {
                result = ((int) ref - 65 + key) % 26 + 65;
            }
            else if (islower(ref))
            {
                result = ((int) ref - 97 + key) % 26 + 97;
            }
        }
        else
        {
            result = (int) ref;
        }

        ciphered[i] = (char) result;
    }
    string c = ciphered;

    return c;
}

// convert int to char
char convert_int_char(int i)
{
    char c = (char) i;
    return c;
}



