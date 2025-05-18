#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include <curl/curl.h>
#include <jansson.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

typedef struct HashNode {
    char *key;
    char *value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **nodes;
    size_t size;
} HashTable;

typedef struct {
    char *input_path;
    char *dict_path;
    char *output_path;
    bool overwrite;
    bool no_overwrite;
    bool auto_approve;
    bool no_internet;
    char *file_extension;
    int thread_count;
} ProgramOptions;

typedef struct {
    char *input_file;
    char *output_file;
    HashTable *dictionary;
    ProgramOptions *options;
} ThreadData;

HashTable *create_hash_table(size_t size);
void free_hash_table(HashTable *table);
void hash_table_insert(HashTable *table, const char *key, const char *value);
char *hash_table_search(HashTable *table, const char *key);

ProgramOptions parse_arguments(int argc, char *argv[]);
void print_help();

void process_file_translation(const char *input_file, const char *output_file, HashTable *dictionary, ProgramOptions *options);
void process_directory(const char *input_dir, const char *output_dir, HashTable *dictionary, ProgramOptions *options);

char *search_translation_online(const char *word, const char *source_lang, const char *target_lang);
void add_word_to_dictionary(const char *word, const char *translation, HashTable *dictionary, const char *dict_path);

char *translate_word(const char *word, HashTable *dictionary, ProgramOptions *options, const char *dict_path);
char *translate_text(const char *text, HashTable *dictionary, ProgramOptions *options, const char *dict_path);