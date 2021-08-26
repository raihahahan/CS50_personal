#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int locked_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// Additional helper function prototypes
void selection_sort(int int_arr[], int LENGTH, pair array_to_sort[]);
bool is_cycle(int cycle_start, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    /*
        Workings:
            - create an array for the values of preferences[ranks[i]][ranks[j]] which are > 0 each
            - pass this array into selection sort desc algo, but instead of swapping the elements in that array, swap elements in pair array
    */
    int preferenceArr[pair_count];
    int counter = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                preferenceArr[counter] = preferences[i][j];
                counter++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                preferenceArr[counter] = preferences[j][i];
                counter++;
            }
        }
    }

    selection_sort(preferenceArr, pair_count, pairs);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Searched solution from Stack Overflow.
    // Read through solution in order to understand it myself.
    // Provided my own explanation for the algorithm below
    for (int i = 0; i < pair_count; i++)
    {
        // iterate through all the locked pairs
        // for each locked pair (i.e pairs[i].winner and pairs[i].loser),
        // pass the pair to the is_cycle checker function
        if (!is_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Function to check if graph is circular
bool is_cycle(int cycle_start, int loser) // current cycle_start and current loser
{
    // Note: cycle_start do not change throughout the recursion
    // cycle_start is pairs[i].winner from main function: we are keeping track of this winner

    /*
    Algorithm explanation:
        - Before locking candidate i to candidate j, we check if j locks another element k, and then we check if k locks l and so on until we reach an element p which locks i
        - If the above occurs, then we have reached a circle where we start from i and ends with i. We return true.
        - Else, return false.

    Implementation explanation:
        - Before locking i to j, we pass in i and j as arguments to is_cycle. i is the current winner to be locked to j, the current loser.
        - i is also the start of the cycle for the current iteration.
        - The first check is loser == cycle_start. This just means that if the loser is the start of the cycle, then we have actually reached a circle.
            - i.e if i is the start of the circle, and somewhere through the recursive calls, i is the loser of that recursion, then and only then will we reach a circle.
            - Returns true if circle
        - If first check is false, then we iterate through ALL candidates to check which candidate is locked by candidate j, the current loser.
            - If j locks k, then j will be the new current winner, and k is the new current loser.
            - We pass in the same start_cycle and k as the new arguments to is_cycle.
            - This is because as stated above, for every start_cycle, we want to iterate through ALL candidates to check if the locking of subsequent elements result in the loop reaching the start_cycle again.
            - We keep repeating until:
                - an element p locks i, so we pass is_cycle(i, i). i == i so we return true.
                - no element p locks i and we've already reached the max candidate_count. So we return false.
        - Finally, depending on the checker, we lock element i to j if no circle will occur.
        - Then we check if locking the next element j to k will result in a circle. This will be done for EVERY TIME we want to lock a pair.
    */
    if (loser == cycle_start)
    {
        // if current loser is the cycle start
        // then the entry results in a cycle
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[loser][j])
        {
            if (is_cycle(cycle_start, j))
            {
                // progress through the circle
                return true;
            }
        }
    }
    return false;
}


// Print the winner of the election
void print_winner(void)
{
    // TODO
    int counter = 0;
    string winners[candidate_count];
    int winners_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                counter++;
            }
        }
        if (counter == 0)
        {
            winners[counter] = candidates[i];
            winners_count++;
        }
        counter = 0;
    }

    for (int k = 0; k < winners_count; k++)
    {
        printf("%s\n", winners[k]);
    }

    return;
}

// Selection Sort
void selection_sort(int int_arr[], int LENGTH, pair array_to_sort[])
{
    for (int i = 0; i < LENGTH; i++)
    {
        int largestIndex = i;
        int current = int_arr[i];
        int largest;

        pair current1 = array_to_sort[i];
        pair largest1;

        for (int j = i; j < LENGTH; j++)
        {
            if (int_arr[j] > int_arr[largestIndex])
            {
                largestIndex = j;
            }
        }

        largest = int_arr[largestIndex];

        largest1 = array_to_sort[largestIndex];

        int_arr[largestIndex] = current;
        int_arr[i] = largest;

        array_to_sort[largestIndex] = current1;
        array_to_sort[i] = largest1;
    }
}

// END