#include "translate.h"

char *search_translation_online(const char *word, const char *source_lang, const char *target_lang);
void add_word_to_dictionary(const char *word, const char *translation, HashTable *dictionary, const char *dict_path);