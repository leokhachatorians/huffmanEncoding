#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked.h"
int main() {
    int total_letters = 0;
    int first = BUFSIZ, second = BUFSIZ;
    char c_first = ' ', c_second = ' ';
    Link *head = NULL;
    int counts[26] = {0};
    char sentence[BUFSIZ];

    printf("Enter a sentence: ");
    fgets(sentence, BUFSIZ, stdin);

    printf("%s\n", sentence);

    // Gather the occuring letters
    for (size_t j = 0; j < strlen(sentence); j++) {
        char c = sentence[j];
        if (!isalpha(c) && c != ' ') {
            continue;
        }
        counts[(int)(tolower(c) - 'a')]++;
        total_letters++;
    }

    // Insert unique letters into our linked list
    for (int i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            char c = i + 'a';
            head = insert(head, c, counts[i]);
        }
    }
    traverse(head);
    
    Link *cursor = head;

    // Iterate through the linked list to determine
    // fewest occuring letters
    while (cursor != NULL) {
        if (cursor->data->freq < first) {
            second = first;
            c_second = c_first;

            first = cursor->data->freq;
            c_first = cursor->data->letter;
        }
        else if (cursor->data->freq < second && cursor->data->letter != c_first) {
            second = cursor->data->freq;
            c_second = cursor->data->letter;
        }
        cursor = cursor->next;
    }

    printf("First: %c-%d\n", c_first, first);
    printf("Second: %c-%d\n", c_second, second);



    return 0;
}
