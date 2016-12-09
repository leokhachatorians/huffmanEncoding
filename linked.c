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

void insert(Link **, char, int);
void insert_at_end(Link **, char, int);

int main() {
    //Link *head = (Link*) malloc(sizeof(Link));
    Link *head = NULL;
    insert(&head, 'a', 1);
    insert_at_end(&head, 'b', 2);
    insert_at_end(&head, 'c', 3);
    printf("%c\t%d\n", head->data->letter, head->data->freq);
    return 0;
}

void insert(Link **head, char letter, int freq) {
    Data d = {letter, freq, NULL, NULL};
    Link *new_node = (Link*) malloc(sizeof(Link));
    new_node->data = &d;
    new_node->next = *head;
    (*head) = new_node;
}

void insert_at_end(Link **head, char letter, int freq) {
    Data d = {letter, freq, NULL, NULL};
    Link *new_node = (Link*) malloc(sizeof(Link));
    new_node->data = &d;
    new_node->next = NULL;

    Link *p = *head;
    while (p->next != NULL) {
        p = p->next;
    }
    *p = *new_node;
}
