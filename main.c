#include <stdlib.h>
#include <stdio.h>

typedef struct Data Data;
struct Data {
    char letter;
    int freq;
    Data *left;
    Data *right;
};

int main() {
    Data test = {'a', 2, NULL, NULL};
    Data test2 = {'b', 3, NULL, NULL};
    test.left = &test2;
    printf("%c\t%c\n", test.letter, test.left->letter);

	return 0;
}
