/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "trie.h"

// global vars used by our dictionary
node * trie = NULL;
int words_in_dict = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* current = trie;
    
    // See if word is in dictionary
    for (int i = 0; i < strlen(word); i++) {
        
        if (current -> children[char_position(word[i])] == NULL) {
            return false;
        }
        
        current = current -> children[char_position(word[i])];

        
        // check if is_word is true
        if (i == strlen(word) - 1) {
            if (current -> is_word == true) {
                return true;
            }
        }
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{   
    //opening dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    //Creating the "root" trie
    trie = new_node();

    int words = 0;

    char word[LENGTH+1]; /*For the termination character*/
    int i = 0;
    int c = 0;
    
    while (c != EOF) {
        c = fgetc(fp);
        if (c == '\n' || c == EOF) {
            // skip newlines
            if (i > 0) {
                insert_word(word, i, trie);
                words++;
            }
            
            // reset position in buffer
            i = 0;
            
            continue;
        }
        
        word[i] = c;
        i++;
    }

    words_in_dict = words;

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words_in_dict;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    free_node(trie);
    return true;
}
