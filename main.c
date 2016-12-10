#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked.h"
int main() {
    int i, total_letters = 0, total_freq = 0;
    size_t j;
    Link *head = NULL;
    int counts[26] = {0};
    char sentence[BUFSIZ];

    printf("Enter a sentence: ");
    fgets(sentence, BUFSIZ, stdin);

    printf("%s\n", sentence);

    for (j = 0; j < strlen(sentence); j++) {
        char c = sentence[j];
        if (!isalpha(c) && c != ' ') {
            continue;
        }
        counts[(int)(tolower(c) - 'a')]++;
        total_letters++;
    }

   // head = insert(head, 'l', 3);
   // head = insert(head, 't', 3);
   // head = insert(head, 'z', 3);
   // head = insert_at_end(head, 'H', 1);
   // traverse(head);
   // head = remove_via_letter(head, 'z');
   // printf("\n");
   // traverse(head);

    return 0;
}
