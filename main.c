#include <stdlib.h>
#include <stdio.h>
#include "linked.h"
int main() {
    Link *head = NULL;
    head = insert(head, 'l', 3);
    head = insert(head, 't', 3);
    head = insert(head, 'z', 3);
    head = insert_at_end(head, 'H', 1);
    traverse(head);
    head = remove_via_letter(head, 'z');
    printf("\n");
    traverse(head);

    return 0;
}
