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
    int path[1000];

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
            head = create_link_and_push_to_front(head, i, counts[i]);
            unique_chars++;
        }
    }
    MergeSort(&head);
    
    Node *n_first = (Node*) malloc(sizeof(Node));
    Node *n_second = (Node*) malloc(sizeof(Node));

    while (unique_chars != 1) {
        int min1 = BUFSIZ - 1, min2 = BUFSIZ;
        Link *cursor = head;

        // Iterate through the linked list to determine
        // fewest occuring letters
       // while (cursor != NULL) {
       //     if (cursor->data->freq < min1) {
       //         min2 = min1;
       //         n_second = n_first;

       //         min1 = cursor->data->freq;
       //         n_first = cursor->data;
       //     }
       //     else if (cursor->data->freq < min2) {
       //         min2 = cursor->data->freq;
       //         n_second = cursor->data;
       //     }
       //     cursor = cursor->next;
       // }
       n_first = head->data;
       n_second = head->next->data;

    
        Link *merge = combine_smallest_linked_nodes(n_first, n_second); 

        n_first->del = true;
        n_second->del = true;
        head = remove_node(head);
        head = remove_node(head);
        head = push_merge_to_linked_list(head, merge);
        unique_chars--;
        MergeSort(&head);
    }

    Hashtable *table = (Hashtable*) malloc(sizeof(Hashtable));
    table = init_hashtable_table(table);

    dive(head->data, &table, ' ', path, 0);
    display_encoding_per_character(counts, table);

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error loading the file\n");
        exit(EXIT_FAILURE);
    }

    FILE *write;
    write = fopen("test.bin","w");
    while ((c = fgetc(fp))) {
        if (c == EOF) {
            break;
        }
        int value = get_hash_value(table, c);
        fwrite(&value, sizeof(value), 1, write);
        printf("%lu", get_hash_value(table, c));
    }
    fclose(fp);
    printf("\n");
    return 0;
}
