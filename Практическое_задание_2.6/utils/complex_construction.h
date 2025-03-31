#include "singly_linked_int_list.h"

typedef struct three_linked_struct {
    struct three_linked_struct* forwards;
    int_snode* up;
    int_snode* down;
} three_linked;

three_linked* create_three_linked(three_linked* forwards, int_snode* up, int_snode* down);
void generate_dot_file_tl(three_linked* head, const char* filename);