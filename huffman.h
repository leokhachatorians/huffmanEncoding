#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdbool.h>

typedef struct Node Node;
struct Node {
    char letter;
    int freq;
    bool del;
    Node *left;
    Node *right;
};

typedef struct Link Link;
struct Link {
    Link *next;
    Node *data;
};

typedef struct Bucket Bucket;
struct Bucket {
    bool in_use;
    char encoding[10];
    int size;
};

typedef struct Hashtable Hashtable;
struct Hashtable {
    Bucket table[500];
};

Hashtable *init_hashtable_table(Hashtable *);

Link *create_link_and_push_to_front(Link *, char, int);
Link *push_merge_to_linked_list(Link *, Link *);
Link *insert_at_end(Link *, char, int);
Link *remove_node(Link *);
Link *merge_nodes(Link *, Node *, Node *, Link *, Node *);
Link *combine_smallest_linked_nodes(Node *, Node*);

unsigned long hash(char);
void insert_hash_value(Hashtable **, char, char [], int);
Bucket get_bucket(Hashtable *, char);

void dive(Node *, Hashtable **, char, char [], int);

// Sorting
void MergeSort(Link **);
Link *SortedMerge(Link *, Link *);
void FrontBackSplit(Link *, Link**, Link**);

// Utility
void traverse(Link *);
void remove_newline(char *);
void traverse_tree(Node *);
void find_loop(Link *);
void display_encoding_per_character(int [], Hashtable *);
#endif // HUFFMAN_
