#include "translate.h"

char *translate_word(const char *word, HashTable *dictionary, ProgramOptions *options, const char *dict_path);
char *translate_text(const char *text, HashTable *dictionary, ProgramOptions *options, const char *dict_path);