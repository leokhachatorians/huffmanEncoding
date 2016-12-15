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

Link *merge_nodes(Link *head, Node *first, Node *second, Link *merge, Node *merge_node) {
    merge_node->left = first;
    merge_node->right = second;
    merge_node->freq = first->freq + second->freq;

    merge->data = merge_node;
    merge->next = head;
    return merge;
}

Link *insert(Link *head, char letter, int freq) {
    Link *new_link = (Link*) malloc(sizeof(Link));
    Node *d = (Node*) malloc(sizeof(Node));
    d->letter = letter;
    d->freq = freq;
    d->left = d->right = NULL;
    d->del = false;
    d->use = false;
    new_link->data = d;

    new_link->next = NULL;
    new_link->next = head;
    return new_link;
   // Link *new_node = create_link(letter, freq);
   // new_node->next = head;

   // return new_node;
}
void insert2(Link **head, Link *new_link) {
    new_link->next = NULL;
    new_link->next = *head;
    *head = new_link;
}
//
//Link *insert_at_end(Link *head, char letter, int freq) {
//    if (head == NULL) {
//        return insert(head, letter, freq);
//    }
//
//    Link *cursor = head;
//    while (cursor->next != NULL) {
//        cursor = cursor->next;
//    }
//
//    cursor->next = create_link(letter, freq);
//    return head;
//}
//
Link *remove_node(Link *head) {
    if (head == NULL) {
        return head;
    }

    if (head->data->del) {
        Link *found = head;
        head = found->next;
        //free(found);
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
        //printf("Node to delete: %c\n", found->data->letter);
        cursor->next = found->next;
        //printf("New Node: %c\n", cursor->next->data->letter);
        //free(found);
    }
    return head;
}

void dive(Node *node, Hashtable **table, char dir, int path[], int pathlen) {
    if (node == NULL) {
        return;
    }
    path[pathlen] = dir;
    pathlen++;

    if (node->left == NULL && node->right == NULL) {
        int num;
        int count = 0;
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
           //num = path[i];
            num_arr[i] = num;
        }
        //printf("HERE:%llu\n", num);
        unsigned int encoding = 0;
        for (int i = 0; i < count; i++) {
            encoding = 10 * encoding + num_arr[i];
            //printf("%u\t", k);
        }
        //printf("%u\n", k);
        insert_hash_value(table, node->letter, encoding);
        //printf("%i \n", get_hash_value(table, node->letter));
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

void insert_hash_value(Hashtable **table, char letter, unsigned int encoding) {
    unsigned long bucket = hash(letter);
    if ((*table)->table[bucket].in_use == false) {
        (*table)->table[bucket].in_use = true;
        (*table)->table[bucket].value = encoding;
    }
    printf("Inside 'insert_hash_value' and after modifying table\n");
    printf("Bucket: %lu\n", bucket);
    printf("Encoding: %u\n", encoding);
    printf("Check Encoding: %u\n", (*table)->table[bucket].value);
    printf("Char: %c - %d\n\n", letter, letter);
}

int get_hash_value(Hashtable **table, char letter) {
    unsigned int c = hash(letter);
    return (*table)->table[c].value;
}
