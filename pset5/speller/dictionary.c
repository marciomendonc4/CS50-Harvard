// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 200000;

// Variable to count the number of words read
int wordCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Hashing the word
    int index = hash(word);
    //Creating a temporary node that points to the first element of the hash table
    node *temp = table[index];
    //Traversing the list, searching for a mach
    while (temp)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        //Moving to the next
        temp = temp->next;
    }
    //If match not found
    return false;
}
//Creating a new node
node *createNode(char *word)
{
    //Allocating space for a new node
    node *newNode = malloc(sizeof(node));
    if (!newNode)
    {
        return NULL;
    }
    //Copying the word to the node
    strcpy(newNode->word, word);
    newNode->next = NULL;
    wordCounter++;
    //Returning
    return newNode;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int len = strlen(word);
    int hashCode = 0;
    for (int i = 0; i < len; i++)
    {
        //Performing several rounds of multiplication to generate a random number
        //My hashcode formula was inspired on a video from Jacob Sorber's Youtube Channel
        hashCode = hashCode * N + tolower(word[i]);
    }
    //Making sure the number is between 0 ~ N - 1
    hashCode %= N;
    //Returning the hash code
    return hashCode;
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *spellerFile = fopen(dictionary, "r");
    char newWord[LENGTH + 1];
    //Checking if an error occurred
    if (!spellerFile)
    {
        printf("Couldn't open.\n");
        return false;
    }
    //Looping through each word till the end of file is reached
    while (fscanf(spellerFile, "%s", newWord) != -1)
    {
        //Creating a new node that holds the word
        node *n = createNode(newWord);
        //Hashing the word
        int index = hash(newWord);
        //Checking if it's the first Node to be inserted at the given location
        if (!table[index])
        {
            table[index] = n;
        }
        //If not, add at the top of the list
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }
    fclose(spellerFile);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Creating 2 temporaty nodes to traverse the list
    node *current, *previous;
    for (int i = 0; i < N; i++)
    {
        //Node *current receives the first node of the hash table
        current = table[i];
        previous = NULL;
        while (current)
        {
            previous = current;
            //Moves to the next node
            current = current->next;
            //Delete the previous node
            free(previous);
        }
    }
    return true;
}
