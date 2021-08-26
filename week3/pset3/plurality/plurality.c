#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

// Added helper functions
void swap(int one, int two, candidate unswapped[]);
void bubble_sort_votes(candidate array[], int len);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // populate name of candidate
        candidates[i].votes = 0; // populate votes of candidate. initial value == 0
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name) // Linear search to find if name matches any candidates
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int maxIndex = 0;
    int numWinners = 1;
    bubble_sort_votes(candidates, candidate_count); // sort function into ascending order first

    for (int j = 0; j < candidate_count; j++) // counts the number of winners
    {
        if (candidates[j].votes > candidates[maxIndex].votes)
        {
            maxIndex = j;
            numWinners = 1;
        }
        else if (candidates[j].votes == candidates[maxIndex].votes)
        {
            maxIndex = j;
            numWinners++;
        }
    }


    for (int k = candidate_count - 1; k > candidate_count - 1 - numWinners; k--) // prints the candidates who won the election
    {
        if (!candidates[k].name)
        {
            break;
        }
        printf("%s\n", candidates[k].name);
    }
    return;
}

void swap(int one, int two, candidate unswapped[])
{
    // helper function to swap two elements in an array
    candidate elem1 = unswapped[one];
    candidate elem2 = unswapped[two];
    unswapped[one] = elem2;
    unswapped[two] = elem1;
}

void bubble_sort_votes(candidate array[], int len)
{
    // helper function to sort array in ascending order using bubble sort
    int counter = 0;
    for (int j = len - 1; j >= 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if (array[i].votes > array[i + 1].votes)
            {
                swap(i, i + 1, array);
                counter++;
            }
        }
        if (counter == 0)
        {
            break;
        }
    }
}

// WORKINGS //

/*
Linear Search:
- Iterate through array of voters
- if strcmp returns 0, then return true,
- else continue until end of iteration, then return false
*/

/*
Get max:
- Sort candidates name in an array from highest to lowest votes ---- (*)
- initialise integer for number of winners
- loop over array (*) and end when we finish iterating over winners only
*/