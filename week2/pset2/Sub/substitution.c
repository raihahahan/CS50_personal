#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

    // CHECKS IF KEY HAS LENGTH 26
    if (l != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // CHECKS IF KEY HAS MORE THAN 1 ARGUMENT OR IF KEY HAS NON ALPHABETS
    for (int m = 0; m < l; m++)
    {
        if (!isalpha(argv[1][m]) || argc != 2)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // CHECKS IF KEY HAS DUPLICATE LETTERS
    string key = argv[1]; // easy reference to key

    for (int p = 0; p < l; p++)
    {
        for (int q = p + 1; q < l; q++)
        {
            if (key[p] == key[q])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    //***********ENCRYPTION ALGORITHM**********//
    // user input
    string plaintext = get_string("plaintext: ");
    int plaintext_len = strlen(plaintext);

    //***********START ALGORITHM**********//
    char ciphered[plaintext_len]; // creates an array of characters to be output as string
    char result; // stores the encrypted individual character
    char ALPHABETS[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    // algorithm to encrypt letters
    for (int i = 0; i < plaintext_len; i++)
    {
        char ref = plaintext[i];
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
                else
                {
                    continue;
                }
            }
        }
        else
        {
            result = ref;
        }
        ciphered[i] = result;
    }
    ciphered[plaintext_len] = '\0';
    //***********END ALGORITHM**********//

    //***********FINAL RESULT**********//
    printf("ciphertext: %s\n", ciphered);

    return 0;
}


