#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdbool.h>

typedef struct Node Node;
struct Node {
    char letter;
    int freq;
    bool del;
    bool use;
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
    unsigned int value;
};

typedef struct Hashtable Hashtable;
struct Hashtable {
    Bucket table[500];
};

Link *create_link(char, int);
Link *insert(Link *, char, int);
Link *insert_at_end(Link *, char, int);
Link *remove_node(Link *);
Link *merge_nodes(Link *, Node *, Node *);

unsigned long hash(char);
void insert_hash_value(Hashtable **, char, unsigned int);
int get_hash_value(Hashtable **, char);

void dive(Node *, Hashtable **, char, char [], int);
void traverse(Link *);

#endif // HUFFMAN_H
