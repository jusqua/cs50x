#include <cs50.h>
#include <stdio.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Prompt for words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");
    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    printf("s1: %d\ns2: %d\n", score1, score2);
    // Print the winner
    if (score1 > score2)
    {
        puts("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        puts("Player 2 wins!");
    }
    else
    {
        puts("Tie!");
    }
}

// Compute and return score for string
int compute_score(string word)
{
    int points = 0;
    for (int c = 0; word[c] != '\0'; c++)
    {
        if (word[c] >= 65 && word[c] <= 90)
        {
            points += POINTS[word[c] - 65];
        }
        else if (word[c] >= 97 && word[c] <= 122)
        {
            points += POINTS[word[c] - 97];
        }
    }
    return points;
}
