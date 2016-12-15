#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

void remove_newline(char *);

void MergeSort(Link **);
Link *SortedMerge(Link *, Link *);
void FrontBackSplit(Link *, Link**, Link**);

void traverse_tree(Node *);
void find_loop(Link *);

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

int main() {
    int total_chars = 0, unique_chars = 0;
    Link *head = NULL;
    int counts[256] = {0};
    //char letters[BUFSIZ];
    char file_name[BUFSIZ];
    FILE *fp;

    printf("Enter a filename: ");
    fgets(file_name, BUFSIZ, stdin);
    remove_newline(file_name);

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error loading the file\n");
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = fgetc(fp))) {
        if (c == EOF) {
            break;
        }
        counts[c] += 1;
        total_chars += 1;
    }
    fclose(fp);
    
    // Insert unique letters into our linked list
    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) {
            head = insert(head, i, counts[i]);
            unique_chars++;
           // printf("TRAVERSING\n");
           // traverse(head);
           // printf("Char: %c - %d times\n",
           //     head->data->letter, head->data->freq);
        }
    }
    
    //MergeSort(&head);
    //traverse(head);
    Node *n_first = (Node*) malloc(sizeof(Node));
    Node *n_second = (Node*) malloc(sizeof(Node));
   // Node *merge_node = (Node*) malloc(sizeof(Node));
   // Link *merge = (Link*) malloc(sizeof(Link));

    while (unique_chars != 1) {
        Node *merge_node = (Node*) malloc(sizeof(Node));
        Link *merge = (Link*) malloc(sizeof(Link));
        int min1 = BUFSIZ - 1, min2 = BUFSIZ;
        Link *cursor = head;
       // Node *merge_node = (Node*) malloc(sizeof(Node));

        // Iterate through the linked list to determine
        // fewest occuring letters
        while (cursor != NULL) {
            if (cursor->data->freq < min1) {
                min2 = min1;
                n_second = n_first;

                min1 = cursor->data->freq;
                n_first = cursor->data;
            }
            else if (cursor->data->freq < min2) {
                min2 = cursor->data->freq;
                n_second = cursor->data;
            }
            cursor = cursor->next;
        }
       // printf("Char: %c - %d times\n", n_first->letter, n_first->freq);
       // printf("Char: %c - %d times\n\n", n_second->letter, n_second->freq);
    
        //Link *merge = (Link*) malloc(sizeof(Link));
        //insert_at_front(&head, n_first, n_second);
        merge_node->left = n_first;
        merge_node->right = n_second;
        merge_node->freq = n_first->freq + n_second->freq;
        merge_node->letter = ' ';
        merge->data = merge_node;
        n_first->del = true;
        n_second->del = true;
        head = remove_node(head);
        head = remove_node(head);
        insert2(&head, merge);
        //merge->next = head;

        //traverse(head);
        //merge->next = head;
        //head = merge->next = head;

        unique_chars--;
    }
   // printf("%d\n", total_chars);
   // printf("SORTED TRAVERSE\n");
   // traverse(head);
   // find_loop(head);
   // traverse_tree(head->data);

    printf("worked\n");
   // printf("Char %c\n", head->data->left->letter);
   // printf("Char %c\n", head->data->right->letter);
    //traverse_tree(head->data);
   //a
    int path[1000];

    Hashtable *table = (Hashtable*) malloc(sizeof(Hashtable));
    dive(head->data, &table, ' ', path, 0);
    for (int i = 0; i < 128; i++) {
        if (counts[i] > 0) {
            printf("Char: %c - %lu encoding\n", i, get_hash_value(&table, i));
        }
    }

    printf("\n");

    return 0;
}
