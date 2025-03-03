#include <complex_construction.h>
#include <stdlib.h>
#include <stdio.h>

three_linked* create_three_linked(three_linked* forwards, int_snode* up, int_snode* down) {
    three_linked *new_node = (three_linked*)malloc(sizeof(three_linked));
    new_node->forwards = forwards == NULL ? NULL : forwards;
    new_node->up = up == NULL ? NULL : up;
    new_node->down = down == NULL ? NULL : down;

    return new_node;
}

void _write_dot_recursive_tl(FILE *file, three_linked* node, void** visited, int* visited_count) {
    if (node == NULL) return;

    for (int i = 0; i < *visited_count; i++)
        if (visited[i] == (void*)node) return;

    visited[*visited_count] = (void*)node;
    (*visited_count)++;

    fprintf(file, "  \"%p\" [label=\" \", color=green];\n", (void*)node);

    if (node->forwards != NULL) {
        fprintf(file, "  \"%p\" -> \"%p\" [label=\"forwards\", color=red];\n", (void*)node, (void*)node->forwards);
        _write_dot_recursive_tl(file, node->forwards, visited, visited_count);
    }
    if (node->up != NULL) {
        fprintf(file, "  \"%p\" -> \"%p\" [label=\"up\", color=blue];\n", (void*)node, (void*)node->up);
        _write_dot_recursive_sl(file, node->up, visited, visited_count);
    }
    if (node->down != NULL) {
        fprintf(file, "  \"%p\" -> \"%p\" [label=\"down\", color=orange];\n", (void*)node, (void*)node->down);
        _write_dot_recursive_sl(file, node->down, visited, visited_count);
    }
}

void generate_dot_file_tl(three_linked* head, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return;

    fprintf(file, "digraph G {\n");
    fprintf(file, "  node [shape=circle, style=filled, color=lightblue, fontcolor=black];\n");
    fprintf(file, "  edge [color=gray, arrowhead=vee];\n");
    fprintf(file, "  \"S\" [label=\"S\", shape=doublecircle, color=orange, fontcolor=black]\n");
    fprintf(file, "  \"S\" -> \"%p\" [color=red];\n", (void*)head);

    void* visited[1000];
    int visited_count = 0;

    _write_dot_recursive_tl(file, head, visited, &visited_count);

    fprintf(file, "}\n");

    fclose(file);
}