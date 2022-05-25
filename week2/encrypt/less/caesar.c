#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

string ciphertext(string word, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        puts("Usage: ./caesar key");
        return 1;
    }
    else
    {
        // If not a digit, close application
        for (int c = 0; argv[1][c] != '\0'; c++)
        {
            if (argv[1][c] < 48 || argv[1][c] > 57)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // Prompt for Plaintext
        string plaintext = get_string("plaintext:  ");
        // Print Ciphertext
        printf("ciphertext: %s\n", ciphertext(plaintext, atoi(argv[1])));
        return 0;
    }
}

string ciphertext(string word, int key)
{
    // Rotate key
    key = (key > 25) ? key % 26 : key;
    // Switch word by word
    for (int c = 0; word[c] != '\0'; c++)
    {
        for (int i = 0; i < key; i++)
        {
            // Rotate ascii or ++
            if (word[c] >= 97 && word[c] <= 122)
            {
                word[c] += word[c] == 122 ? -25 : 1;
            }
            if (word[c] >= 65 && word[c] <= 90)
            {
                word[c] += word[c] == 90 ? -25 : 1;
            }
        }
    }
    return word;
}
