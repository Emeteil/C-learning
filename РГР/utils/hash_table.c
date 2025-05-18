#include "hash_table.h"

// https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
// Djb2 hash function
unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

HashTable *create_hash_table(size_t size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->nodes = calloc(size, sizeof(HashNode*));
    table->size = size;
    return table;
}

void free_hash_table(HashTable *table) {
    for (size_t i = 0; i < table->size; i++) {
        HashNode *node = table->nodes[i];
        while (node != NULL) {
            HashNode *temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table->nodes);
    free(table);
}

void hash_table_insert(HashTable *table, const char *key, const char *value) {
    unsigned long index = hash_function(key) % table->size;
    HashNode *node = table->nodes[index];
    
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            free(node->value);
            node->value = strdup(value);
            return;
        }
        node = node->next;
    }
    
    HashNode *new_node = malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = table->nodes[index];
    table->nodes[index] = new_node;
}

char *hash_table_search(HashTable *table, const char *key) {
    unsigned long index = hash_function(key) % table->size;
    HashNode *node = table->nodes[index];
    
    while (node != NULL) {
        if (strcmp(node->key, key) == 0)
            return node->value;

        node = node->next;
    }
    
    return NULL;
}