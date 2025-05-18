#include "translate.h"

unsigned long hash_function(const char *str);
HashTable *create_hash_table(size_t size);
void free_hash_table(HashTable *table);
void hash_table_insert(HashTable *table, const char *key, const char *value);
char *hash_table_search(HashTable *table, const char *key);