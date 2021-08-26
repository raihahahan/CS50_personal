#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string encryption(string word, string key, int length);
int absolute(int n);

int main(int argc, string argv[])
{
    //***********TO PREVENT SEGMENTATION FAULT***********//
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //***********KEY VALIDATION***********//
    // stores the length of key
    int l = strlen(argv[1]);

    // checks if key has length 26
    if (l != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // checks if key is only has alphabets and is only 1 argument
    for (int m = 0; m < l; m++)
    {
        if (!isalpha(argv[1][m]) || argc != 2)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    //***********ENCRYPTION**********//
    // user input and encryption algorithm
    string plaintext = get_string("plaintext: ");
    int plaintext_len = strlen(plaintext);
    string ciphered = encryption(plaintext, argv[1], plaintext_len);

    //***********DEBUGGER**********//
    printf("length: %i\n", plaintext_len);
    printf("end: %c\n", ciphered[strlen(ciphered)]);
    printf("\n");

    //***********FINAL RESULT**********//
    printf("ciphertext: %s\n", ciphered);

    return 0;
}

// encryption function
string encryption(string word, string key, int length)
{
    char ciphered[length]; // creates an array of characters to be output as string
    char result; // stores the encrypted individual character
    char ALPHABETS[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    // algorithm to encrypt letters
    for (int i = 0; i < length; i++)
    {
        char ref = word[i];
        if (isalpha(ref)) // if letter is an alphabet
        {
            for (int j = 0, n = strlen(ALPHABETS); j < n; j++) // iterate through array of alphabets
            {
                if (toupper(ref) == ALPHABETS[j])
                {
                    if (isupper(ref))
                    {
                        result = toupper(key[j]);
                        break;
                    }
                    else
                    {
                        result = tolower(key[j]);
                        break;
                    }
                }
                else continue;
            }
        }
        else
        {
            result = ref;
        }
        ciphered[i] = result;
    }
    ciphered[length] = '\0';
    string c = ciphered;
    return c;
}

