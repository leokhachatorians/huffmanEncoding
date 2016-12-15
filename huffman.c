#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

Link *insert(Link *head, char letter, int freq) {
    Link *new_link = (Link*) malloc(sizeof(Link));
    Node *d = (Node*) malloc(sizeof(Node));
    d->letter = letter;
    d->freq = freq;
    d->left = d->right = NULL;
    d->del = false;
    new_link->data = d;

    new_link->next = head;
    return new_link;
}

void insert2(Link **head, Link *new_link) {
    new_link->next = *head;
    *head = new_link;
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
        unsigned long int encoding = 0;
        for (int i = 0; i < count; i++) {
            encoding = 10 * encoding + num_arr[i];
            //printf("%u\t", k);
        }
        //printf("Encoding: %lu - Letter %c\n", encoding, node->letter);
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

void insert_hash_value(Hashtable **table, char letter, unsigned long int encoding) {
    unsigned long bucket = hash(letter);
    for (int i = 0; i < 500; i++) {
        if ((*table)->table[bucket].in_use == false) {
            (*table)->table[bucket].in_use = true;
            (*table)->table[bucket].value = encoding;
            return;
        }
        bucket = (bucket + 1) % 500;
    }
   // printf("Inside 'insert_hash_value' and after modifying table\n");
   // printf("Bucket: %lu\n", bucket);
   // printf("Encoding: %llu\n", encoding);
   // printf("Check Encoding: %llu\n", (*table)->table[bucket].value);
   // printf("Char: %c - %d\n\n", letter, letter);
}

unsigned long int get_hash_value(Hashtable **table, char letter) {
    unsigned int c = hash(letter);
    return (*table)->table[c].value;
}


void find_loop(Link *head) {
    Link *slow, *fast;
    slow = fast = head;
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            printf("looped\n");
            return;
        }
    }
    printf("no loop\n");
}
    

void MergeSort(Link** headRef) {
    Link *head = *headRef;
    Link *a;
    Link *b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    FrontBackSplit(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);

    *headRef = SortedMerge(a,b);
}

Link *SortedMerge(Link *a, Link *b) {
    Link *result = NULL;
    
    if (a == NULL) {
        return b;
    }
    else if (b == NULL) {
        return a;
    }
    
    if (a->data->freq <= b->data->freq) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return result;
}

void FrontBackSplit(Link *source, Link **frontRef, Link **backRef) {
    Link *fast;
    Link *slow;
    if (source == NULL || source->next == NULL) {
        *frontRef = source;
        *backRef = NULL;
    }
    else {
        slow = source;
        fast = source->next;

        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

void traverse_tree(Node *node) {
    if (node == NULL) {
        return;
    }
    printf("Char -  %i - Times\n", node->freq);
    traverse_tree(node->left);
    traverse_tree(node->right);
}

void remove_newline(char *array) {
    int length = strlen(array);
    for (int i = 0; i < length; i++) {
        if (array[i] == '\n') {
            array[i] = '\0';
        }
    }
}
