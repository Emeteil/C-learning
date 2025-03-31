#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dlfcn.h>
#include <stdbool.h>

typedef struct int_snode_struct {
    int data;
    struct int_snode_struct* next;
} int_snode;

typedef struct int_dnode_struct {
    int data;
    struct int_dnode_struct* right;
    struct int_dnode_struct* left;
} int_dnode;

typedef struct three_linked_struct {
    struct three_linked_struct* forwards;
    int_snode* up;
    int_snode* down;
} three_linked;

typedef bool (*__bool_window)(const char* format, ...);
typedef size_t (*__size_t_window)(const char* format, ...);
typedef int (*__int_window)(const char* format, ...);
typedef int_snode* (*__create_int_snode)(int data, int_snode* next);
typedef void (*__append_int_snode)(int_snode** head, int data);
typedef int_snode* (*__get_int_snode_by_idx)(int_snode* head, int index);
typedef void (*__print_int_snode)(int_snode* head);
typedef void (*__generate_dot_file_sl)(int_snode* head, const char* filename);
typedef int_dnode* (*__create_int_dnode)(int data, int_dnode* right, int_dnode* left);
typedef void (*__print_int_dnode)(int_dnode* current);
typedef void (*__generate_dot_file)(int_dnode* head, const char* filename);
typedef three_linked* (*__create_three_linked)(three_linked* forwards, int_snode* up, int_snode* down);
typedef void (*__generate_dot_file_tl)(three_linked* head, const char* filename);

void main() {
    void *ext_library;
    ext_library = dlopen("./libMyDynamic.so", RTLD_LAZY); // Ленивое связывание вызовов функций 0x00001
    if (!ext_library){
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		exit(1);
	};
    
    __bool_window bool_window = (__bool_window)dlsym(ext_library, "bool_window");
    __size_t_window size_t_window = (__size_t_window)dlsym(ext_library, "size_t_window");
    __int_window int_window = (__int_window)dlsym(ext_library, "int_window");
    __create_int_snode create_int_snode = (__create_int_snode)dlsym(ext_library, "create_int_snode");
    __append_int_snode append_int_snode = (__append_int_snode)dlsym(ext_library, "append_int_snode");
    __get_int_snode_by_idx get_int_snode_by_idx = (__get_int_snode_by_idx)dlsym(ext_library, "get_int_snode_by_idx");
    __print_int_snode print_int_snode = (__print_int_snode)dlsym(ext_library, "print_int_snode");
    __generate_dot_file_sl generate_dot_file_sl = (__generate_dot_file_sl)dlsym(ext_library, "generate_dot_file_sl");
    __create_int_dnode create_int_dnode = (__create_int_dnode)dlsym(ext_library, "create_int_dnode");
    __print_int_dnode print_int_dnode = (__print_int_dnode)dlsym(ext_library, "print_int_dnode");
    __generate_dot_file generate_dot_file = (__generate_dot_file)dlsym(ext_library, "generate_dot_file");
    __create_three_linked create_three_linked = (__create_three_linked)dlsym(ext_library, "create_three_linked");
    __generate_dot_file_tl generate_dot_file_tl = (__generate_dot_file_tl)dlsym(ext_library, "generate_dot_file_tl");

    size_t n = 0;
    while (n < 2)
        n = size_t_window("Write n");
    
    int_snode* head = NULL;
    int_dnode* S = NULL;

    for (int i = 0; i < n; i++) {
        int data = int_window("Write %d element", i);

        append_int_snode(&head, data);
    }

    generate_dot_file_sl(head, "../list.dot");
    system("dot -Tpng ../list.dot -o ../list.png");
    print_int_snode(head);

    if (!bool_window("Создать список с узлами на 2 элемента?")) return;

    if (n < 4) {
        S = create_int_dnode(get_int_snode_by_idx(head, 1)->data, NULL, NULL);
        S->left = create_int_dnode(get_int_snode_by_idx(head, 0)->data, NULL, NULL);
        if (n == 3)
            S->left->right = create_int_dnode(get_int_snode_by_idx(head, 2)->data, NULL, NULL);
    }

    int_dnode* pr_left = NULL;
    int_dnode* pr_right = NULL;
    if (n >= 4)
    for (int i = 0; i < n - 1; i += 2) {
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
    
    if (n >= 4)
    if (n % 2 != 0)
        pr_left->right = create_int_dnode(get_int_snode_by_idx(head, n - 1)->data, NULL, NULL);

    generate_dot_file(S, "../list.dot");
    system("dot -Tpng ../list.dot -o ../list.png");
    print_int_dnode(S);

    if (!bool_window("Создать новый список для N и K?")) return;

    n = 0;
    size_t k = 0;

    while (n < 1)
        n = size_t_window("Write n");
    
    while (k < 1)
        k = size_t_window("Write k");
    
    size_t p_n = n;
    size_t p_k = k;

    int_dnode* Snk = NULL;
    int_dnode* right = NULL;
    int_dnode* left = NULL;

    while (n != 0 && k != 0)
    {
        int data_n = int_window("Write %d element for n", (int)(p_n - n));
        int data_k = int_window("Write %d element for k", (int)(p_k - k));

        if (left == NULL) {
            left = create_int_dnode(data_k, NULL, NULL);
        }
        else {
            left->right = create_int_dnode(data_k, NULL, NULL);
            left = left->right;
        }
        k--;

        if (right == NULL) {
            right = create_int_dnode(data_n, NULL, left);
        }
        else {
            right->right = create_int_dnode(data_n, NULL, left);
            right = right->right;
        }
        n--;

        if (Snk == NULL)
            Snk = right;
    }

    if (n == 0)
    while (k != 0)
    {
        int data_k = int_window("Write %d element for k", (int)(p_k - k));

        if (left == NULL) {
            left = create_int_dnode(data_k, NULL, NULL);
        }
        else {
            left->right = create_int_dnode(data_k, NULL, NULL);
            left = left->right;
        }
        k--;
    }

    if (k == 0)
    while (n != 0)
    {
        int data_n = int_window("Write %d element for n", (int)(p_n - n));
        
        if (right == NULL) {
            right = create_int_dnode(data_n, NULL, NULL);
        }
        else {
            right->right = create_int_dnode(data_n, NULL, NULL);
            right = right->right;
        }
        n--;
    }
    
    generate_dot_file(Snk, "../list.dot");
    system("dot -Tpng ../list.dot -o ../list.png");
    print_int_dnode(Snk);

    if (!bool_window("Создать сложную списочную структуру?")) return;

    n = 0;
    k = 0;

    while (n < 1)
        n = size_t_window("Write n");
    
    while (k < 1)
        k = size_t_window("Write k");
    
    three_linked* trS = NULL;

    int_snode* c_up = create_int_snode(n+1 - 1, NULL);
    int_snode* c_down = create_int_snode(n - 1, NULL);
    three_linked* pr = create_three_linked(
        NULL,
        c_up,
        c_down
    ); 
    trS = pr;

    int max = (n > k) ? n : k;
    for (int i = 1; i < max; i++) {
        int_snode* up = (int)(n + 1 + i) <= n+k ? create_int_snode((n + 1 + i) - 1, NULL) : NULL;
        int_snode* down = (int)(n - i) > 0 ? create_int_snode((n - i) - 1, NULL) : NULL;
        if (c_up != NULL)
            c_up->next = up;
        if (c_down != NULL)
            c_down->next = down;
        
        c_up = up;
        c_down = down;

        pr->forwards = create_three_linked(
            NULL,
            up,
            down
        );
        pr = pr->forwards;
    }
    pr->forwards = trS;
    
    generate_dot_file_tl(trS, "../list.dot");
    system("dot -Tpng ../list.dot -o ../list.png");

    dlclose(ext_library);
}