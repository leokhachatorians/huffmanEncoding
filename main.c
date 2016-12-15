#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

int main() {
    int total_chars = 0, unique_chars = 0;
    Link *head = NULL;
    int counts[256] = {0};
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
        }
    }
    
    Node *n_first = (Node*) malloc(sizeof(Node));
    Node *n_second = (Node*) malloc(sizeof(Node));

    while (unique_chars != 1) {
        Node *merge_node = (Node*) malloc(sizeof(Node));
        merge_node->left = merge_node->right = NULL;
        merge_node->letter = ' ';
        merge_node->freq = 0;
        merge_node->del = false;
        Link *merge = (Link*) malloc(sizeof(Link));

        int min1 = BUFSIZ - 1, min2 = BUFSIZ;
        Link *cursor = head;

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
        unique_chars--;
    }

    int path[1000];

    Hashtable *table = (Hashtable*) malloc(sizeof(Hashtable));
    for (int i = 0; i < 500; i++) {
        table->table[i].in_use = false;
        table->table[i].value = 0;
    }

    dive(head->data, &table, ' ', path, 0);
    for (int i = 0; i < 128; i++) {
        if (counts[i] > 0) {
            printf("Char: %c - %lu encoding\n", i, get_hash_value(&table, i));
        }
    }
    printf("\n");
    return 0;
}
