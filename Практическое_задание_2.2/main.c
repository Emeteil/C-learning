#include <stdio.h>

#include <singly_linked_int_list.h>
#include <doubly_linked_int_list.h>

void main() {
    size_t n = 0;

    printf("Write n: ");
    scanf("%zu", &n);

    int_snode* head = NULL;
    int_dnode* S = NULL;

    print_int_snode(head);

    for (int i = 0; i < n; i++) {
        int data = 0;
        printf("Write %d element: ", i);
        scanf("%d", &data);

        append_int_snode(&head, data);
    }

    print_int_snode(head);
    printf("%d %d\n", 3, get_int_snode_by_idx(head, 3)->data);

    int_dnode* pr_left = NULL;
    int_dnode* pr_right = NULL;
    for (int i = 0; i < n; i += 2) {
        // printf("%d\n", i);
        int_dnode* left = create_int_dnode(get_int_snode_by_idx(head, i)->data, NULL, NULL);
        int_dnode* right = create_int_dnode(get_int_snode_by_idx(head, i + 1)->data, NULL, NULL);
        if (S == NULL) S = right;

        if (pr_left != NULL)
            pr_left->right = left;
        if (pr_right != NULL)
            pr_right->right = right;
        
        pr_left = left;
        pr_right = right;

        right->left = left;
    }
    puts("test");
    if (n % 2 != 0)
        pr_left->right = create_int_dnode(get_int_snode_by_idx(head, n - 1)->data, NULL, NULL);
}