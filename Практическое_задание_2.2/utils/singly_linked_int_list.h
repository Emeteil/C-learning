#include <stdio.h>

typedef struct int_snode_struct {
    int data;
    struct int_snode_struct* next;
} int_snode;

int_snode* create_int_snode(int data, int_snode* next);
void append_int_snode(int_snode** head, int data);
int_snode* get_int_snode_by_idx(int_snode* head, int index);
void print_int_snode(int_snode* head);
void _write_dot_recursive_sl(FILE *file, int_snode* node, void** visited, int* visited_count);
void generate_dot_file_sl(int_snode* head, const char* filename);