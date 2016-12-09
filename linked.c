#include <stdio.h>
#include <stdlib.h>

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
void traverse(Link *);

int main() {
    Link *head = NULL;
 //   head = insert(head, 'a', 1);
 //   head = insert(head, 'b', 1);
    head = insert_at_end(head, 'c', 1);
    traverse(head);
    return 0;
}

Link *create_link(char letter, int freq) {
    Data *d = (Data*) malloc(sizeof(Data));
    d->letter = letter;
    d->freq = freq;

    Link *new_node = (Link*) malloc(sizeof(Link));
    new_node->data = d;
    return new_node;
}

Link *insert(Link *head, char letter, int freq) {
    Link *new_node = create_link(letter, freq);
    new_node->next = head;

    return new_node;
}

Link *insert_at_end(Link *head, char letter, int freq) {
    if (head == NULL) {
        return insert(head, letter, freq);
    }

    Link *cursor = head;
    while (cursor->next != NULL) {
        cursor = cursor->next;
    }

    cursor->next = create_link(letter, freq);
    return head;
}

void traverse(Link *head) {
    while (head != NULL) {
        printf("%c\t%d\n", head->data->letter, head->data->freq);
        head = head->next;
    }
}
