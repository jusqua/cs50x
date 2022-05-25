#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // I used smaller variables for better view
    
    // Initializing variables
    char lc; // Last char
    int l = 0, w = 0, s = 0; // Letter, Word, Sentences
    // Prompt for Text
    string t = get_string("Text:  ");
    
    // Grade check
    for (int c = 0; t[c] != '\0'; c++)
    {
        if (t[c] == '\'' || t[c] == ' ' || t[c] == '.' || t[c] == ',' || t[c] == '!' || t[c] == '?')
        {
            // Get words
            w += t[c] == ' ' && (c == 0 || lc == '\'' || lc == ' ' || lc == '.' || lc == ',' || lc == '!' || lc == '?') ? 0 : 1;
            // Get sentences
            s += t[c] == '.' || t[c] == '!' || t[c] == '?' ? 1 : 0;
        }
        else
        {
            l++;
        }
        // Get Last Word
        lc = t[c];
    }
    // Generating Coleman-Liau index
    float cli = (0.0588 * (l * 100 / w)) - (0.296 * (s * 100 / w)) - 15.8;
    if (cli < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cli > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", cli);
    }
}
