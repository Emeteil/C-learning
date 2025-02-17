#include <doubly_linked_int_list.h>
#include <stdlib.h>
#include <stdio.h>

int_dnode* create_int_dnode(int data, int_dnode* right, int_dnode* left) {
    int_dnode *new_dnode = (int_dnode*)malloc(sizeof(int_dnode));
    new_dnode->data = data;
    new_dnode->right = right == NULL ? NULL : right;
    new_dnode->left = left == NULL ? NULL : left;

    return new_dnode;
}