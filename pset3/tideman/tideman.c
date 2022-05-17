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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;    
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int len = (candidate_count * (candidate_count - 1)) / 2;
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                for (int k = 0; k < len; k++)
                {
                    if (pairs[k].winner == 0 & pairs[k].loser == 0)
                    {
                        pairs[k].winner = i;
                        pairs[k].loser = j;
                        break;
                    }
                }
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int len = (candidate_count * (candidate_count - 1)) / 2;
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                int temp1 = pairs[j].winner;
                pairs[j].winner = pairs[i].winner;
                pairs[i].winner = temp1;
                
                int temp2 = pairs[j].loser;
                pairs[j].loser = pairs[i].loser;
                pairs[i].loser = temp2;
            }
        }
    }
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //int count[pair_count];
    for (int i = 0; i < pair_count; i ++)
    {
        // Setting variables for easy access
        int loser_i = pairs[i].loser;
        int winner_i = pairs[i].winner;
        
        locked[winner_i][loser_i] = true;
        
        for (int j = 0; j < pair_count; j++)
        {
            // Setting variables for easy access
            int winner_j = pairs[j].winner;
            int loser_j = pairs[j].loser;
            
            if (loser_i == pairs[j].winner && locked[pairs[j].winner][loser_j] == true)
            {
                if (j == 0)
                {
                    break;
                }
                if (winner_i > loser_j || i == pair_count - 1)
                {
                    locked[winner_i][loser_i] = false;
                    break;
                }
            }
        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //Boolean variable always set to true if the loop is restarted 
        bool no_true = true;
        for (int j = 0; j < candidate_count; j++)
        {
            //Looking for true values
            if (locked[j][i] == true)
            {
                no_true = false;
                break;
            }
        }
        if (no_true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    // TODO
    return;
}
