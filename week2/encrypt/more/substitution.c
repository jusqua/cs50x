#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string ciphertext(string word, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        puts("Usage: ./substitution key");
        return 1;
    }
    else
    {
        // Initializing variables
        string key = argv[1];
        // Close application cases
        // Different than 26 letters
        if (strlen(key) != 26)
        {
            puts("Key must contain 26 characters.");
            return 1;
        }
        // Multiplied key values
        for (int i = 0; key[i] != '\0'; i++)
        {
            for (int j = i + 1; key[j] != '\0'; j++)
            {
                if (key[i] == key[j])
                {
                    puts("Usage: ./substitution key");
                    return 1;
                }
            }
        }
        // Is not a alpha key
        for (int c = 0; key[c] != '\0'; c++)
        {
            if ((key[c] < 97 || key[c] > 122) && (key[c] < 65 || key[c] > 90))
            {
                puts("Usage: ./substitution key");
                return 1;
            }
        }
        // Prompt for Plaintext
        string plaintext = get_string("plaintext:  ");
        // Print Ciphertext
        printf("ciphertext: %s\n", ciphertext(plaintext, key));
        return 0;
    }
}

string ciphertext(string word, string key)
{
    // Switch word by word
    for (int c = 0; word[c] != '\0'; c++)
    {
        // Substitue
        if (word[c] >= 97 && word[c] <= 122)
        {
            word[c] = tolower(key[word[c] - 97]);
        }
        if (word[c] >= 65 && word[c] <= 90)
        {
            word[c] = toupper(key[word[c] - 65]);
        }
    }
    return word;
}
