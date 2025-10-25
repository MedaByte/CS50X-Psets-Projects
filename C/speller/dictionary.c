// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Done-0: Choose number of buckets in hash table
const unsigned int N = 17576;
const unsigned int ALPHABET = 26;
// Hash table
node *table[N];

long loaded = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Done-0
    unsigned int index = hash(word);

    // create lower cased word
    char *lowerCase = malloc(sizeof(char) * strlen(word) + 1);
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        lowerCase[i] = tolower(word[i]);
    }
    lowerCase[length] = '\0';

    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(lowerCase, cursor->word) == 0)
        {
            free(lowerCase);
            return true;
        }
        cursor = cursor->next;
    }
    free(lowerCase);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Done-0: Improve this hash function
    const int length = strlen(word);
    const int letters = (length >= 3) ? 3 : length;
    unsigned int index = 0;
    int exp = 2;

    for (int i = 0; i < letters; i++)
    {
        index += (toupper(word[i]) - 'A') * pow(ALPHABET, exp - i);
    }

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Done-0
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char *buffer = malloc(sizeof(char) * LENGTH + 1);
    if (buffer == NULL)
    {
        return false;
    }
    while (fscanf(dict, "%s", buffer) != EOF)
    {
        unsigned int index = hash(buffer);
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }
        strcpy(new->word, buffer);
        new->next = table[index];

        table[index] = new;

        loaded++;
    }
    free(buffer);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Done-0
    return loaded;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Done-0
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
