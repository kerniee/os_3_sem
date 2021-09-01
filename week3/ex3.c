#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

void print_list(struct Node *first) {
    while(first != NULL) {
        printf("%d ", first->value);
        first = first->next;
    }
    printf("\n");
    
}

void insert_node(struct Node *node, struct Node *new_node) {
    new_node->next = node->next;
    node->next = new_node;
}

void delete_node(struct Node *head, struct Node *node_to_delete) {
    if (head == node_to_delete) {
        struct Node *next_head = head->next;
        free(head);
        *head = *next_head;
        return;
    }

    while (head->next != node_to_delete) head = head->next;
    head->next = node_to_delete->next;
    free(node_to_delete);
}

int main(int argc, char *argv[]) {
    struct Node *linked_list = (struct Node*) malloc(sizeof(struct Node));
    linked_list->value = 11;
    print_list(linked_list);

    struct Node *node_2 = (struct Node*) malloc(sizeof(struct Node));
    node_2->value = 22;
    insert_node(linked_list, node_2);
    print_list(linked_list);

    struct Node *node_3 = (struct Node*) malloc(sizeof(struct Node));
    node_3->value = 33;
    insert_node(linked_list, node_3);
    print_list(linked_list);

    delete_node(linked_list, node_2);
    print_list(linked_list);

    delete_node(linked_list, linked_list);
    print_list(linked_list);
    return 0;
}