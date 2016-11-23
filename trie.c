#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "trie.h"


void print_node(node* n) {
    printf("node -> is_word %d\n", n -> is_word);
    for (int i = 0; i < LENGTH_NODE; i++) {
        printf("node -> children[%d] = %p \n", i, n -> children[i]);
    }
}

node* new_node() {
    node *n = (node*) malloc(sizeof(node));
    n -> is_word = false;
    for (int i = 0; i < LENGTH_NODE; i++) {
        n -> children[i] = NULL;
    }

    return n;
}

void insert_word(char* word, int length, node* trie) {
    node* current = trie;

    for (int i = 0; i < length; i++) {

        if (current -> children[char_position(word[i])] == NULL) {
            current -> children[char_position(word[i])] = new_node();
        }
        
        current = current -> children[char_position(word[i])];
        
        // mark the last node (== last char) as being a word in a trie
        if (i == length-1) {
            current -> is_word = true;
        }
    }
}

int char_position(char c) {
    if (c == '\'') {
        return 26;
    }
    else if (isupper(c)) {
        return c - 'A';
    }
    else if (islower(c)) {
        return c - 'a';
    } else {
        printf("unexpected case: char_position(%c)\n", c);
        return -1;
    }
}

void free_node(node* current) {

    //Iterate through the current_node's children
    for (int i = 0; i < LENGTH_NODE; i++) {
        //For each child, if that child isn't NULL, call free_node() 
        if (current -> children[i] != NULL) {
            free_node(current -> children[i]);
        }
    }
    
    //Free this node itself
    free(current);
} 


