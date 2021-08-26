#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int get_letters(string paragraph);
int get_words(string paragraph);
int get_sentences(string paragraph);
int compute_grade(int c, int w, int s);

int main(void)
{
    // initialise variables
    int grade = 0,
        letters = 0,
        words = 0,
        sentences = 0;
    float index;

    // get paragraph input and compute relevant details
    string paragraph = get_string("Text: ");

    // overwriting variables with returned values
    letters = get_letters(paragraph);
    words = get_words(paragraph);
    sentences = get_sentences(paragraph);
    grade = compute_grade(letters, words, sentences);

    // checker for grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// helper function to get letter count
int get_letters(string paragraph)
{
    int letters = 0;
    for (int i = 0; paragraph[i] != '\0'; i++)
    {
        if (paragraph[i] != ' ' && isalpha(paragraph[i]))
        {
            letters++;
        }
    }
    return letters;
}

// helper function to get word count
int get_words(string paragraph)
{
    int words = 0;
    for (int i = 0; paragraph[i] != '\0'; i++)
    {
        if (paragraph[i] == ' ')
        {
            words++;
        }
    }
    return ++words;
}

// helper function to get paragraph count
int get_sentences(string paragraph)
{
    int sentences = 0;
    for (int i = 0; paragraph[i] != '\0'; i++)
    {
        if (paragraph[i] == '.' || paragraph[i] == '!' || paragraph[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

// helper function to compute grade
int compute_grade(int c, int w, int s)
{
    float L = ((float) c / w) * 100;
    float S = ((float) s / w) * 100;

    // algorithm used to compute grade level
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}


