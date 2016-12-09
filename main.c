#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MESSAGE_LENGTH 128

typedef struct Data Data;
struct Data {
    char letter;
    int freq;
    Data *left;
    Data *right;
};

typedef struct Node Node;
struct Node {
    Node *next;
    Data *data;
};

void insert(Node **head, void *data, size_t data_size) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(data_size);
    new_node->next = (*head);

    size_t i;
    for (i = 0; i < data_size; i++) {
        *(char *)(new_node->data + i) = *(char *)(data + i);
    }
    (*head) = new_node;
}

//void print_list(Node *node, void (*fptr)(void *)) {
void print_list(Node *node) {
        printf("Letter: %c \t Freq: %d\n",
            node->data->letter, node->data->freq);
    while (node != NULL) {
        printf("Letter: %c \t Freq: %d\n",
            node->data->letter, node->data->freq);
        //(*fptr)(node->data);
        node = node->next;
    }
}

//void print_data(void *d) {
//    printf("Letter: %c \t Freq: %d",
//            *(

int main() {
    int i, total_letters = 0, total_freq = 0;
    size_t j;
    int counts[26] = {0};
    char sentence[BUFSIZ];
    Node *start = NULL;

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

    Node nodes[total_letters];
    total_letters = 0;

    // populate our nodes list
    for (i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            char c = i + 'a';
            Data _ = {c, counts[i], NULL, NULL};
            Node n = {NULL, &_};
            nodes[total_letters++] = n;
     //       printf("Letter: %c \t Freq: %d\n",
     //           n.data->letter, n.data->freq);
        }
    }

    for(i = 0; i <= total_letters; i++) {
        insert(&start, &nodes[i], sizeof(Data));
    }
    //printf("Letter: %c \t Freq: %d\n",
    //    nodes[0].data->letter, nodes[0].data->freq);

    print_list(start);



    // sanity check to ensure that we did stuff right
   // for (i = 0; i < total_letters; i++) {
   //     printf("%c \t %d\n", struct_keeper[i].letter, struct_keeper[i].freq);
   //     total_freq += struct_keeper[i].freq;
   // }

    // finding the two lowest freq (yeah this is messy I know)
   // int first = 0;
   // int second = 1;
   // for (i = 0; i < total_letters; i++) {
   //     if (struct_keeper[i].freq < struct_keeper[first].freq) {
   //         second = first;
   //         first = i;
   //     }
   //     else if (struct_keeper[i].freq < struct_keeper[second].freq && i != first) {
   //         second = i;
   //     }
   // }
   // int total = struct_keeper[first].freq + struct_keeper[second].freq;
   // struct Data test = {'\0', total, &struct_keeper[first], &struct_keeper[second]};


	return 0;
}
