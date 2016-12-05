#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE_LENGTH 128

typedef struct Data Data;
struct Data {
    char letter[MESSAGE_LENGTH];
    int freq;
    Data *left;
    Data *right;
};

int main() {
    int i;
    size_t j;
    int counts[26] = {0};
    char sentence[BUFSIZ];

    printf("Enter a sentence: ");
    fgets(sentence, BUFSIZ, stdin);
    printf("%s\n", sentence);

    size_t len = strlen(sentence);

    for (j = 0; j < len; j++) {
        char c = sentence[j];
        if (!isalpha(c)) {
            continue;
        }
        counts[(int)(tolower(c) - 'a')]++;
    }

    for (i = 0; i < 26; i++) {
        printf("'%c' has %2d occurences.\n", i + 'a', counts[i]);
    }


    //Data test = {{'a', '\0'}, 2, NULL, NULL};
    //Data test2 = {{'b', '\0'}, 3, NULL, NULL};
    //test.left = &test2;

    //printf("%s\t%s\n", test.letter, test.left->letter);

	return 0;
}
