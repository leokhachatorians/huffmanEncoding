#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

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

void dive(Node *node, Hashtable **table, char dir, char path[], int pathlen) {
    if (node == NULL) {
        return;
    }
    path[pathlen] = dir;
    pathlen++;

    if (node->left == NULL && node->right == NULL) {
        int num, count;
        count = 0;
        for (int i = 0; i < pathlen; i++) {
            count++;
        }
        int num_arr[count];
        for (int i = 0; i < pathlen; i++) {
            if (path[i] == 32) { // handle the space char?
                num = (path[i] - 31);
            }
            else {
                num = (path[i] - '0');
            }
            num_arr[i] = num;
        }
        unsigned int k = 0;
        for (int i = 0; i < count; i++) {
            k = 10 * k + num_arr[i];
        }
        //printf("%u\n", k);
        insert_hash_value(table, node->letter, k);
        printf("%d \n", get_hash_value(table, node->letter));
    }
    else {
        dive(node->left, table, '0', path, pathlen);
        dive(node->right, table, '1', path, pathlen);
    }
}

void traverse(Link *head) {
    while (head != NULL) {
        printf("%c\t%d\n", head->data->letter, head->data->freq);
        head = head->next;
    }
    printf("\n");
}

unsigned long hash(char str) {
    unsigned long hash = 5381;
    int c = str;
    hash = ((hash << 5) + hash) + c;
    return hash % 500;
}

void insert_hash_value(Hashtable **table, char letter, int encoding) {
    int bucket = hash(letter);
    for (int tries = 0; tries < 500; tries++) {
        if ((*table)->table[bucket].in_use == false) {
            (*table)->table[bucket].in_use = true;
            (*table)->table[bucket].value = encoding;
            //printf("%u", (*table)->table[bucket].value);
        }
        bucket = (bucket + 1) % 500;
    }
   // printf("Bucket: %i\nEncoding: %3d\nChecking %i\n",
   //         bucket, encoding, (*table)->table[bucket].value);
}

int get_hash_value(Hashtable **table, char letter) {
    unsigned long c = hash(letter);
    return (*table)->table[c].value;
}
