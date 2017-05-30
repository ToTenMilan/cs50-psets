// dictionary.c * Computer Science 50 * Problem Set 5 * Implements a dictionary's functionality.
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define LENGTH 45
#define SIZE 100
// hash function from Lauren Carvalho's 'short' video
int hash_function(char* key);

// struct node
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;
// for head
node* hashtable[SIZE];
// for size()
int words = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char flatword[LENGTH+2];
    // convert word to all lower
    for (int i = 0; i < strlen(word); i++)
    {
        flatword[i] = tolower(word[i]);
    }
    // terminate the lowered string
    flatword[strlen(word)] = '\0';
    // get index from flatword
    int index = hash_function(flatword);
    // if head is not empty
    if (hashtable[index] != NULL)
    {
        // set temp node to head
        node *trav = hashtable[index];
        // compare the two strings, if not match...
        while (strcmp(trav->word, flatword) != 0)
        {
            // move to next node
            trav = trav->next;
            // if word not exist, return false
            if (trav == NULL)
            {
                return false;
            }
        }
    }
    return true;
}

// /**
//  * Loads dictionary into memory.  Returns true if successful else false.
//  */

bool load(const char* dictionary)
{
    // open dictionary
    FILE* pdict = fopen(dictionary, "r");
    if(pdict == NULL) { return 1; }
    
    // initialize buffer for file to read
    char buffer[LENGTH+2];
    
    // while end of file
    while (fgets(buffer, sizeof(buffer), pdict))
    {
        // overwrite the \n with \0
        buffer[strlen(buffer) - 1] = '\0';
        
        // create space for new node
        node* new_node = malloc(sizeof(node));
        if(new_node == NULL) { return 1; }
        
        // read one word at a time and put it in the new_node->word
        strncpy(new_node->word, buffer, LENGTH + 1);
        new_node->next = NULL;
                        // printf("word: %s\n", new_node->word);
        // hash this word
        int index = hash_function(new_node->word);

        // insert into a linked list (hashtable[index] is head (bucket))
        if(hashtable[index] == NULL)
        {
            // new_node becomes head
            hashtable[index] = new_node;
            // pointer of head points to null
            hashtable[index]->next = NULL;
            words++;
        }
        else // add the new node at the beginning
        {
            // new_node points to head which already exists
            new_node->next = hashtable[index];
            // new_node becomes head
            hashtable[index] = new_node;
            words++;
        }
    }
    fclose(pdict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for ( int i = 0; i < SIZE; i++)
    {
        node* cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }    
    return true;
}

int hash_function(char* key)
{
    int hash = toupper(key[0]) - 'A';
    return hash % 100;
}
