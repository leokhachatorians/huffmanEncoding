#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked.h"
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
        int first = BUFSIZ, second = BUFSIZ;
        char c_first = '\0', c_second = '\0';
        Link *cursor = head;
        Node *n_first = (Node*) malloc(sizeof(Node));
        Node *n_second = (Node*) malloc(sizeof(Node));

        // Iterate through the linked list to determine
        // fewest occuring letters
        while (cursor != NULL) {
            if (cursor->data->freq < first) {
                second = first;
                c_second = c_first;

                first = cursor->data->freq;
                c_first = cursor->data->letter;
                n_first = cursor->data;
            }
            //else if (cursor->data->freq < second && cursor->data->letter != c_first) {
            else if (cursor->data->freq < second) {
                second = cursor->data->freq;
                c_second = cursor->data->letter;
                n_second = cursor->data;
            }
            cursor = cursor->next;
        }

        printf("First: %c - %d\n", c_first, first);
        printf("Second: %c - %d\n", c_second, second);

        head = merge_nodes(head, n_first, n_second);
        n_first->del = true;
        n_second->del = true;
        //printf("Count: %d\n\n", n_first->freq + n_second->freq);
        head = remove_node(head);
        head = remove_node(head);
        free(n_first);
        free(n_second);
        traverse(head);
        unique_letters--;
        printf("\n");
    }
    printf("%d\n", total_letters);
    traverse(head);
    

    return 0;
}
