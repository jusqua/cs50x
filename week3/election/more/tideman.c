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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    // Checking name on the list
    for (int c = 0; c < candidate_count; c++)
    {
        if (!strcmp(name, candidates[c]))
        {
            // Voted
            ranks[rank] = c;
            return true;
        }
    }
    // Is not on the list, then there is no vote
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Initializing auxiliary variable
    int c = 0;
    // Adding pair
    for (int i = 0 + c; i < candidate_count; i++)
    {
        for (int j = 0 + c; j < candidate_count; j++)
        {
            // Can't be itself && Can't tie
            if (i != j && preferences[i][j] != preferences[j][i])
            {
                pairs[pair_count].winner = preferences[i][j] > preferences[j][i] ? i : j;
                pairs[pair_count].loser = preferences[i][j] > preferences[j][i] ? j : i;
                pair_count++;
            }
        }
        c++;
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Initializing auxiliary variables
    int winner_value[pair_count];
    int swap;
    int c;
    pair pair_swap;
    // Geting winner vote count of the pair
    for (c = 0; c < pair_count; c++)
    {
        winner_value[c] = preferences[pairs[c].winner][pairs[c].loser];
    }
    // Classic Bubble Sorting
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < c - i; j++)
        {
            if (winner_value[j] < winner_value[j + 1])
            {
                swap = winner_value[j];
                winner_value[j] = winner_value[j + 1];
                winner_value[j + 1] = swap;
                pair_swap = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = pair_swap;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // The first winner has no parameters to check
    locked[pairs[0].winner][pairs[0].loser] = true;
    for (int i = 1; i < candidate_count; i++)
    {
        // Is a winner until something contradicts him
        locked[pairs[i].winner][pairs[i].loser] = true;
        // Cycle check
        for (int j = i - 1; j >= 0; j--)
        {
            // Were previous winners defeated by your loser?
            if (locked[pairs[i].loser][pairs[j].winner])
            {
                // The contradiction
                locked[pairs[i].winner][pairs[i].loser] = false;
            }
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Initializing auxiliary variables
    int count;
    // Getting winner
    for (int i = 0; i < candidate_count; i++)
    {
        count = 0;
        // Searching source
        for (int j = 0; j < candidate_count; j++)
        {
            count += locked[j][i] ? 0 : 1;
        }
        // Nothing points to the source, so it has no lose
        if (count == candidate_count)
        {
            // Print winner
            printf("%s\n", candidates[i]);
        }
    }
}
