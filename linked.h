#ifndef LINKED_H
#define LINKED_H
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

Link *create_link(char, int);
Link *insert(Link *, char, int);
Link *insert_at_end(Link *, char, int);
Link *remove_node(Link *);
Link *merge_nodes(Link *, Node *, Node *);
void traverse(Link *);

#endif // LINKED_H
