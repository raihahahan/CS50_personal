#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int convert_scrabble(char c);

int main(void)
{
    string result;
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        result = "Player 1 wins!";
    }
    else if (score1 == score2)
    {
        result = "Tie!";
    }
    else
    {
        result = "Player 2 wins!";
    }

    printf("%s\n", result);
}

// helper function to compute score given string as argument
int compute_score(string word)
{
    int sum = 0;
    for (int j = 0, n = strlen(word); j < n; j++)
    {
        sum += convert_scrabble(toupper(word[j]));
    }

    return sum;
}

// helper function to convert a character into scrabble points
int convert_scrabble(char c)
{
    int value = 0;
    char ALPHABETS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 26; i++)
    {
        if (c == ALPHABETS[i])
        {
            value = POINTS[i];
            break;
        }
    }
    return value;
}

/*
Workings:
    - Create a function which converts characters into scrabble number
    - Iterate over string array.
    - For each character, pass in char as arg to scrabbleConverter(char)
    - sum += scrabbleConverter(char)
    - return sum
*/