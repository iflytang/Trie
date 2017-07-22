#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Trie_node {

    int count;  // account frequency of prefix of words
    char character; // one character in words, value
    struct Trie_node * next[26];  // pointer to child trie
    bool exist;   // flag to represent whether here can be end

} TrieNode, *Trie;


TrieNode * createTrieNode() {
    // create and init
    TrieNode * node = (TrieNode *) malloc(sizeof(TrieNode));
    node->count = 0;
    node->character = '\0';
    node->exist = false;
    memset(node->next, 0, sizeof(node->next));

    return node;
}

void Trie_insert(Trie root, char * word) {
    TrieNode * node = root;
    char * p = word;
    int id;

    while(*p) {
        id = *p - 'a';
        if(node->next[id] == NULL) {   // if next NULL, create new one
            node->next[id] = createTrieNode();
        }

        node = node->next[id];  // point to next
        node->count++;  // account the times of prefix of words
        p++;  // next character in word
    }

    node->exist = true;
}

int Trie_search_count(Trie root, char * word) {
    TrieNode * node = root;
    char * p = word;
    int id;

    while(*p) {
        id = *p - 'a';  // key
        node = node->next[id];  // pointer to next vertex
        p++;

        if(node == NULL) {
            break;
        }
    }

    // return times of whole words
    /*if(node->exist == true) {
        return node->count;
    } else {
        return 0;
    }*/

    // return times of prefix of words
    return node->count;
}

char * Trie_serach_char(Trie root, char * word) {
    TrieNode * node = root;
    char * p = word;
    int id;
    int i = 0;
    //char temp[26] = "\0";
    char * prefix; // store the prefix of word, include word itself

    while(*p) {
        id = *p - 'a';
        node = node->next[id];

        if(node == NULL) {
            break;
        }
        prefix[i++] = *p;
        p++;
    }

    // return the whole word
   /* if(node->exist == true) {
        return prefix;
    } else {
        return NULL;
    }
    */
    // return the prefix
    printf("prefix: %s\n", prefix);
    return prefix;

}

int main() {
    Trie root = createTrieNode();  // root pointer is NULL
    char str[12];
//    char prefix[26] = "\0";
    bool flag = false;

    printf("please input words into Trie structure (one Enter to store, double Enter to quit):");

    while(gets(str)) {
        if(flag){
            printf("%d\n", Trie_search_count(root , str));
            printf("%s\n", Trie_serach_char(root , str));
        }
        else
        {
            if(strlen(str) != 0)
            {
                Trie_insert(root , str);
            }
            else{
                flag = true;
                printf("please input the prefix of word what you want to seek:");
            }
        }
    }

    if(flag){
        printf("%d\n", Trie_search_count(root , str));
        printf("%s\n", Trie_serach_char(root , str));
    }

    return 0;
}