/**
 * trie.h
 *
 * Custom trie implementation
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#define LENGTH_NODE 27

// node is our trie
typedef struct node {
    bool is_word;
    struct node* children[LENGTH_NODE];
} node;


// Display node info on stdout
void print_node(node* n);

// Allocate a new node and return a pointer to it
node* new_node();

// insert a word into a trie
void insert_word(char* word, int len, node* trie);

// give the position of a given char in the trie children array
int char_position(char c);

// frees the node
void free_node(node* current);

#endif // TRIE_H