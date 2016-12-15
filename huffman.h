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
    unsigned long int value;
};

typedef struct Hashtable Hashtable;
struct Hashtable {
    Bucket table[500];
};

Link *create_link(char, int);
Link *insert(Link *, char, int);
void insert2(Link **, Link *);
Link *insert_at_end(Link *, char, int);
Link *remove_node(Link *);
Link *merge_nodes(Link *, Node *, Node *, Link *, Node *);

unsigned long hash(char);
void insert_hash_value(Hashtable **, char, unsigned long int);
unsigned long int get_hash_value(Hashtable **, char);

void dive(Node *, Hashtable **, char, int [], int);
void traverse(Link *);

#endif // HUFFMAN_
