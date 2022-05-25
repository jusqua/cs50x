// Implements a dictionary's functionality

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// 9 Bytes
const unsigned int N = 512;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Check word
    node *temp = table[hash(word)];
    int i = 0;
    while (temp != NULL)
    {
        while (tolower(word[i]) == temp->word[i])
        {
            if (word[i] == '\0')
            {
                return true;
            }
            i++;
        }
        i = 0;
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Based on hash function from CS50's hash tables explanation
    unsigned int sum = 0;
    for (short i = 0; word[i] != '\0'; i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    node *wordNode = NULL;
    node *temp = NULL;
    char word[LENGTH + 1] = {0};
    short wordLen = 0;
    unsigned int hashValue = 0;

    // Setup hash table to NULL
    for (short i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    while (true)
    {
        // Get word and setup node
        if (fgets(word, LENGTH + 1, file) == NULL)
        {
            fclose(file);
            return true;
        }

        // Ignore newlines
        if (word[0] == '\n')
        {
            continue;
        }

        // Alloc memory for a new word and check
        if ((wordNode = (node *)calloc(1, sizeof(node))) == NULL)
        {
            fclose(file);
            return false;
        }

        wordNode->next = NULL;
        wordLen = strlen(word);

        // Tranfer word to node
        if (wordLen != LENGTH)
        {
            strncpy(wordNode->word, word, wordLen - 1);
            wordNode->word[wordLen] = '\0';
        }
        else
        {
            strcpy(wordNode->word, word);
        }

        // Append to the hash table
        hashValue = hash(wordNode->word);
        if (table[hashValue] == NULL)
        {
            table[hashValue] = wordNode;
        }
        else
        {
            temp = table[hashValue];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = wordNode;
        }

        // Prepare for another word
        wordNode = NULL;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    node *temp;
    unsigned int count = 0;

    // Iteration on table
    for (short i = 0; i < N; i++)
    {
        temp = table[i];
        if (temp != NULL)
        {
            count++;
            while (temp->next != NULL)
            {
                temp = temp->next;
                count++;
            }
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *temp;
    for (short i = 0; i < N; i++)
    {
        while ((temp = table[i]) != NULL)
        {
            table[i] = table[i]->next;
            free(temp);
        }
    }
    return true;
}
