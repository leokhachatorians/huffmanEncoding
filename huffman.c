#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

Link *combine_smallest_linked_nodes(Node *first, Node *second) {
    Link *merge = (Link*) malloc(sizeof(Link));
    Node *merge_node = (Node*) malloc(sizeof(Node));

    // Initialise our node
    merge_node->left = merge_node->right = NULL;
    merge_node->letter = ' ';
    merge_node->freq = 0;
    merge_node->del = false;
    
    // Populate our node
    merge_node->left = first;
    merge_node->right = second;
    merge_node->freq = first->freq + second->freq;
    merge_node->letter = ' ';
    merge->data = merge_node;
    return merge;
}

Link *create_link_and_push_to_front(Link *head, char letter, int freq) {
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

Link *push_merge_to_linked_list(Link *head, Link *new_link) {
    new_link->next = head;
    return new_link;
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
    char second[pathlen];

    if (node->left == NULL && node->right == NULL) {
        for (int i = 1; i < pathlen; i++) {
            second[i-1] = path[i];
        }
        path[pathlen] = '\0';

        insert_hash_value(table, node->letter, second, pathlen);
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

//void insert_hash_value(Hashtable **table, char letter, unsigned long int encoding) {
void insert_hash_value(Hashtable **table, char letter, char arr[], int size) {
    unsigned long bucket = hash(letter);
    if ((*table)->table[bucket].in_use == false) {
        for (int i = 0; i < size; i++) {
            (*table)->table[bucket].encoding[i] = arr[i];
            (*table)->table[bucket].size = size;
        }
        (*table)->table[bucket].in_use = true;
    }
}

//unsigned long int get_hash_value(Hashtable *table, char letter) {
Bucket get_hash_value(Hashtable *table, char letter) {
    unsigned int c = hash(letter);
    return table->table[c];
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

Hashtable *init_hashtable_table(Hashtable *table) {
    for (int i = 0; i < 500; i++) {
        table->table[i].in_use = false;
    }
    return table;
}

void display_encoding_per_character(int counts[], Hashtable *table) {
    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) {
            Bucket bucket = get_hash_value(table, i);
            for (int i = 0; i < bucket.size -1; i++) {
            }
        }
    }
}
