typedef struct int_dnode_struct {
    int data;
    struct int_dnode_struct* right;
    struct int_dnode_struct* left;
} int_dnode;

int_dnode* create_int_dnode(int data, int_dnode* right, int_dnode* left);