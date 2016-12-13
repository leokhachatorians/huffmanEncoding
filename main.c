#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

int main() {
    int total_letters = 0, unique_letters = 0;
    Link *head = NULL;
    int counts[256] = {0};
    char sentence[BUFSIZ];

    printf("Enter a sentence: ");
    fgets(sentence, BUFSIZ, stdin);

    // Gather the occuring letters
    for (int i = 0; sentence[i] != '\0'; i++) {
        counts[(int)sentence[i]]++;
        total_letters++;
    }

    // Insert unique letters into our linked list
    for (int i = 0; i < 256; i++) {
        if (counts[i] > 0) {
            head = insert(head, i, counts[i]);
            unique_letters++;
        }
    }

    while (unique_letters != 1) {
        int min1 = BUFSIZ, min2 = BUFSIZ;
        char c_first = '\0', c_second = '\0';
        Link *cursor = head;
        Node *n_first = (Node*) malloc(sizeof(Node));
        Node *n_second = (Node*) malloc(sizeof(Node));

        // Iterate through the linked list to determine
        // fewest occuring letters
        while (cursor != NULL) {
            if (cursor->data->freq < min1) {
                min2 = min1;
                c_second = c_first;
                n_second = n_first;

                min1 = cursor->data->freq;
                c_first = cursor->data->letter;
                n_first = cursor->data;
            }
            else if (cursor->data->freq < min2) {
                min2 = cursor->data->freq;
                c_second = cursor->data->letter;
                n_second = cursor->data;
            }
            cursor = cursor->next;
        }

        head = merge_nodes(head, n_first, n_second);
        n_first->del = true;
        n_second->del = true;
        head = remove_node(head);
        head = remove_node(head);
        unique_letters--;
    }
    //printf("Final Count - %d\n", head->data->freq);
    char path[1000];

    Hashtable *table = (Hashtable*) malloc(sizeof(Hashtable));
    dive(head->data, &table, ' ', path, 0);

    for (int i = 0; sentence[i] != '\0'; i++) {
        printf("%i ", get_hash_value(&table, sentence[i]));
    }
    printf("\n");

    //printf("%lu\n", hash('a'));

    return 0;
}
