// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = sizeof(LENGTH + 1) * 'Z';

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Gets the hash value to the word
    int index = hash(word);

    // Checks every word in the list at the array [index]
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int num = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        num += toupper(word[i]);
    }
    return num % N;
}

// Number of words in the dictionary
int num_words = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        return false;
    }
    // Temporary variable where new word will be stored
    node *tmp;
    char word[LENGTH + 1];
    int index;
    // Scan every word until the end of the file
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        tmp = malloc(sizeof(node));
        strcpy(tmp->word, word);
        index = hash(tmp->word);
        tmp->next = NULL;
        if (tmp == NULL)
        {
            return false;
        }
        if (table[index] == NULL)
        {
            table[index] = tmp;
        }
        else
        {
            tmp->next = table[index];
            table[index] = tmp;
        }
        num_words++;
    }
    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    int count = 0;
    // Check every bucket in hash table
    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        // Freeing linked list
        while (tmp != NULL)
        {
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
        count++;
    }
    // If unloaded every bucket in hash table then return true, else false
    if (count == N)
    {
        return true;
    }
    return false;
}
