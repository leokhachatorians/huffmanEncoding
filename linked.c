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
Link *remove_via_letter(Link *, char);
void traverse(Link *);

int main() {
    Link *head = NULL;
    head = insert(head, 'l', 3);
    head = insert(head, 't', 3);
    head = insert(head, 'z', 3);
    head = insert_at_end(head, 'H', 1);
    traverse(head);
    head = remove_via_letter(head, 'z');
    printf("\n");
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

Link *remove_via_letter(Link *head, char letter) {
    if (head == NULL) {
        return head;
    }

    if (head->data->letter == letter) {
        Link *found = head;
        head = found->next;
        free(found);
        return head;
    }

    Link *cursor = head;
    while (cursor != NULL) {
        if (cursor->next != NULL && cursor->next->data->letter == letter) {
            break;
        }
        cursor = cursor->next;
    }
    if (cursor != NULL) {
        Link *found = cursor->next;
        cursor->next = found->next;
        free(found);
    }
    return head;
}

void traverse(Link *head) {
    while (head != NULL) {
        printf("%c\t%d\n", head->data->letter, head->data->freq);
        head = head->next;
    }
}
