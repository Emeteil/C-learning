#include "doubly_linked_int_list.h"
#include "console_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int_dnode* create_int_dnode(int data, int_dnode* right, int_dnode* left) {
    int_dnode *new_dnode = (int_dnode*)malloc(sizeof(int_dnode));
    new_dnode->data = data;
    new_dnode->right = right == NULL ? NULL : right;
    new_dnode->left = left == NULL ? NULL : left;

    return new_dnode;
}

int_dnode* max_right(int_dnode* head) {
    int_dnode* current;
    while (head->right)
        current = head->right;
    
    return head;
}

int_dnode* max_left(int_dnode* head) {
    int_dnode* current;
    while (head->left)
        current = head->left;
    
    return head;
}

void _write_dot_recursive(FILE *file, int_dnode* node, void** visited, int* visited_count) {
    if (node == NULL) return;

    for (int i = 0; i < *visited_count; i++)
        if (visited[i] == (void*)node) return;

    visited[*visited_count] = (void*)node;
    (*visited_count)++;

    fprintf(file, "  \"%p\" [label=\"%d\", color=lightblue];\n", (void*)node, node->data);

    if (node->right != NULL) {
        fprintf(file, "  \"%p\" -> \"%p\" [label=\"right\", color=blue];\n", (void*)node, (void*)node->right);
        _write_dot_recursive(file, node->right, visited, visited_count);
    }
    if (node->left != NULL) {
        fprintf(file, "  \"%p\" -> \"%p\" [label=\"left\", color=green];\n", (void*)node, (void*)node->left);
        _write_dot_recursive(file, node->left, visited, visited_count);
    }
}

void generate_dot_file(int_dnode* head, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return;

    fprintf(file, "digraph G {\n");
    fprintf(file, "  node [shape=circle, style=filled, color=lightblue, fontcolor=black];\n");
    fprintf(file, "  edge [color=gray, arrowhead=vee];\n");
    fprintf(file, "  \"S\" [label=\"S\", shape=doublecircle, color=orange, fontcolor=black]\n");
    fprintf(file, "  \"S\" -> \"%p\" [color=red];\n", (void*)head);

    void* visited[1000];
    int visited_count = 0;

    _write_dot_recursive(file, head, visited, &visited_count);

    fprintf(file, "}\n");

    fclose(file);
}

void print_int_dnode(int_dnode* current) {
    char input;
    int_dnode* head = current;
    bool exit = false;
    while (1) {
        printf("Текущий узел: %d\n", current->data);
        printf("Адрес в памяти: %p\n", (void*)current);
        printf("Введите команду (W/A/S/D, Q - выход): ");
        scanf(" %c", &input);
        input = toupper(input);

        if (input == 'Q' || exit) break;

        switch (input) {
            case 'D':
                if (current->right == NULL) {
                    if (bool_window("Достигли конца списка. Хотите ли вы вернуться к началу?"))
                        current = head;
                    else exit = true;
                    break;
                }
                current = current->right;
                break;
            case 'A':
                if (current->left == NULL) {
                    if (bool_window("Достигли конца списка. Хотите ли вы вернуться к началу?"))
                        current = head;
                    else exit = true;
                    break;
                }
                current = current->left;
                break;
            case 'W':
                current = head;
                break;
            case 'S':
                while (current->right != NULL)
                    current = current->right;
                break;
            default:
                printf("Неверная команда.\n");
                break;
        }
    }
}
