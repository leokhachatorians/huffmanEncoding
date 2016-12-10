#ifndef LINKED_H
#define LINKED_H

typedef struct Node Node;
struct Node {
    char letter;
    int freq;
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
Link *remove_via_letter(Link *, char);
Link *merge_nodes(Link *, Node *, Node *);
void traverse(Link *);

#endif // LINKED_H
