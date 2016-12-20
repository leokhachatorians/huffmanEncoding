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
    char path[10];

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
       n_first = head->data;
       n_second = head->next->data;
    Link *merge = combine_smallest_linked_nodes(n_first, n_second); 

    n_first->del = true;
    n_second->del = true;
    head = remove_node(head);
    head = remove_node(head);
    head = push_merge_to_linked_list(head, merge);
    printf("Smallest: %c Freq: %d\n",
            merge->data->left->letter,
            merge->data->left->freq);
    printf("Larger: %c Freq: %d\n",
            merge->data->right->letter,
            merge->data->right->freq);
    printf("Merge: %d\n\n", merge->data->freq);
    MergeSort(&head);
    unique_chars--;
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
    write = fopen("written.bin","wb");
    while ((c = fgetc(fp))) {
        if (c == EOF) {
            break;
        }
        Bucket bucket = get_hash_value(table, c);
        char *arr = bucket.encoding;
        //fwrite(&value, sizeof(value), 1, write);
        for (int i = 0; i < bucket.size-1; i++) {
            //char c = *(arr+i);
            char *ptr;
            long int l = strtol(arr, &ptr, 2);
            unsigned char b = l & 0xffl;
            fwrite(&b, 1, 1, write);
            printf("%c", *(arr + i));

        }
        //printf("%lu", get_hash_value(table, c));
    }
    fclose(fp);
    printf("\n");
    return 0;
}
