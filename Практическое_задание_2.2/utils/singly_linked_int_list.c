#include <singly_linked_int_list.h>
#include <stdlib.h>
#include <stdio.h>

int_snode* create_int_snode(int data, int_snode* next) {
    int_snode *new_node = (int_snode*)malloc(sizeof(int_snode));
    new_node->data = data;
    new_node->next = next == NULL ? NULL : next;

    return new_node;
}

void append_int_snode(int_snode** head, int data) {
    if (*head == NULL) {
        *head = create_int_snode(data, NULL);
        return;
    }

    int_snode* current = *head;
    while (current->next)
        current = current->next;
    
    current->next = create_int_snode(data, NULL);
}

int_snode* get_int_snode_by_idx(int_snode* head, int index) {
    int i = 0;
    while (head != NULL) {
        if (index == i)
            return head;
        head = head->next;
        i++;
    }

    return NULL;
}

void print_int_snode(int_snode* head) {
    if (head == NULL) {
        puts("NULL");
        return;
    }

    int_snode* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    puts("NULL");
}