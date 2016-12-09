#ifndef LINKED_H
#define LINKED_H

typedef struct Data Data;
struct Data {
    char letter;
    int freq;
    Data *left;
    Data *right;
};

typedef struct Link Link;
struct Link {
    Link *next;
    Data *data;
};

Link *create_link(char, int);
Link *insert(Link *, char, int);
Link *insert_at_end(Link *, char, int);
Link *remove_via_letter(Link *, char);
void traverse(Link *);

#endif // LINKED_H
