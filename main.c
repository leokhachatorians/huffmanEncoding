#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE_LENGTH 128

typedef struct Data Data;
struct Data {
    char letter;
    int freq;
    Data *left;
    Data *right;
};

int main() {
    int i, total_letters = 0, total_freq = 0;
    size_t j;
    int counts[26] = {0};
    char sentence[BUFSIZ];

    printf("Enter a sentence: ");
    fgets(sentence, BUFSIZ, stdin);
    printf("%s\n", sentence);

    size_t len = strlen(sentence);

    // populate our occurence list
    for (j = 0; j < len; j++) {
        char c = sentence[j];
        if (!isalpha(c)) {
            continue;
        }
        counts[(int)(tolower(c) - 'a')]++;
        total_letters++;
    }

    Data struct_keeper[total_letters];
    total_letters = 0;

    // populate our 'struct keeper'
    for (i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            char c = i + 'a';
            Data _ = {c, counts[i], NULL, NULL};
            struct_keeper[total_letters++] = _;
        }
    }

    // sanity check to ensure that we did stuff right
    for (i = 0; i < total_letters; i++) {
        printf("%c \t %d\n", struct_keeper[i].letter, struct_keeper[i].freq);
        total_freq += struct_keeper[i].freq;
    }

    // finding the two lowest freq (yeah this is messy I know)
    //while (struct_keeper[0].freq != total_freq) {
    int first = 1000;
    int second = 1000;
    for (i = 0; i < total_letters; i++) {
        if (struct_keeper[i].freq < struct_keeper[first].freq) {
            second = first;
            first = i;
        }
        else if (struct_keeper[i].freq < struct_keeper[second].freq && i != first) {
            second = i;
        }
    }
    int total = struct_keeper[first].freq + struct_keeper[second].freq;
    struct Data test = {'\0', total, &struct_keeper[first], &struct_keeper[second]};

    printf("Total Freq: %d\n", test.freq);
    printf("Lowest: %c %d\n", struct_keeper[first].letter, struct_keeper[first].freq);
    printf("Second Lowest: %c %d\n", struct_keeper[second].letter, struct_keeper[second].freq);

    //}
        


    //printf("%s\t%s\n", test.letter, test.left->letter);

	return 0;
}
