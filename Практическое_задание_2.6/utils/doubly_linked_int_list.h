typedef struct int_dnode_struct {
    int data;
    struct int_dnode_struct* right;
    struct int_dnode_struct* left;
} int_dnode;

int_dnode* create_int_dnode(int data, int_dnode* right, int_dnode* left);
void print_int_dnode(int_dnode* current);
void generate_dot_file(int_dnode* head, const char* filename);
int_dnode* max_right(int_dnode* head);
int_dnode* max_left(int_dnode* head);