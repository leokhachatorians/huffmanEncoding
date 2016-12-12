#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

Link *create_link(char letter, int freq) {
    Node *d = (Node*) malloc(sizeof(Node));
    d->letter = letter;
    d->freq = freq;

    Link *new_node = (Link*) malloc(sizeof(Link));
    new_node->data = d;
    return new_node;
}

Link *merge_nodes(Link *head, Node *first, Node *second) {
    Node *d = (Node*) malloc(sizeof(Node));
    d->left = first;
    d->right = second;
    d->freq = first->freq + second->freq;

    Link *new_node = (Link*) malloc(sizeof(Link));
    new_node->data = d;
    new_node->next = head;
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

Link *remove_node(Link *head) {
    if (head == NULL) {
        return head;
    }

    if (head->data->del) {
        Link *found = head;
        head = found->next;
        free(found);
        return head;
    }

    Link *cursor = head;
    while (cursor != NULL) {
        if (cursor->next != NULL && cursor->next->data->del) {
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

void dive(Node *node, char dir, char path[], int pathlen) {
    if (node == NULL) {
        return;
    }
    path[pathlen] = dir;
    pathlen++;

    if (node->left == NULL && node->right == NULL) {
        printf("%c - ", node->letter);
        for (int i = 0; i < pathlen; i++) {
            printf("%c", path[i]);
        }
        printf("\n");
    }
    else {
        dive(node->left, '0', path, pathlen);
        dive(node->right, '1', path, pathlen);
    }
}

void traverse(Link *head) {
    while (head != NULL) {
        printf("%c\t%d\n", head->data->letter, head->data->freq);
        head = head->next;
    }
    printf("\n");
}
