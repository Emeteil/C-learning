#include "singly_linked_int_list.h"
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

    puts("Not Found!");
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

void _write_dot_recursive_sl(FILE *file, int_snode* node, void** visited, int* visited_count) {
    if (node == NULL) return;

    for (int i = 0; i < *visited_count; i++)
        if (visited[i] == (void*)node) return;

    visited[*visited_count] = (void*)node;
    (*visited_count)++;

    fprintf(file, "  \"%p\" [label=\"%d\", color=lightblue];\n", (void*)node, node->data);

    if (node->next != NULL) {
        fprintf(file, "  \"%p\" -> \"%p\" [label=\"next\", color=green];\n", (void*)node, (void*)node->next);
        _write_dot_recursive_sl(file, node->next, visited, visited_count);
    }
}

void generate_dot_file_sl(int_snode* head, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return;

    fprintf(file, "digraph G {\n");
    fprintf(file, "  node [shape=circle, style=filled, color=lightblue, fontcolor=black];\n");
    fprintf(file, "  edge [color=gray, arrowhead=vee];\n");
    fprintf(file, "  \"S\" [label=\"S\", shape=doublecircle, color=orange, fontcolor=black]\n");
    fprintf(file, "  \"S\" -> \"%p\" [color=red];\n", (void*)head);

    void* visited[1000];
    int visited_count = 0;

    _write_dot_recursive_sl(file, head, visited, &visited_count);

    fprintf(file, "}\n");

    fclose(file);
}