#include "translation.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char *strdup_lower(const char *s) {
    if (!s) return NULL;
    char *result = strdup(s);
    for (int i = 0; result[i]; i++) {
        result[i] = tolower(result[i]);
    }
    return result;
}

bool is_letter(char c) { // Только так работает с русскими символами.
    return !(c == '.' || c == ',' || c == ';' || c == ':' || c == '!' || c == '?' || 
             c == '"' || c == '\'' || c == '`' || c == '~' || c == '@' || c == '#' || 
             c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '(' || 
             c == ')' || c == '-' || c == '_' || c == '+' || c == '=' || c == '{' || 
             c == '}' || c == '[' || c == ']' || c == '|' || c == '\\' || c == '/' || 
             c == '<' || c == '>' || c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool islower_rus(int c) {
    switch (c) {
        case -48: case -103: case -90: case -93: case -102: case -107: case -99: case -109:
        case -88: case -87: case -105: case -91: case -86: case -83: case -106: case -108:
        case -101: case -98: case -96: case -97: case -112: case -110: case -85: case -92:
        case -81: case -89: case -95: case -100: case -104: case -94: case -84: case -111:
        case -82:
            return false;
        case -71: case -122: case -125: case -70: case -75: case -67: case -77: case -120:
        case -119: case -73: case -123: case -118: case -124: case -117: case -78: case -80:
        case -65: case -128: case -66: case -69: case -76: case -74: case -115: case -113:
        case -121: case -127: case -68: case -72: case -126: case -116: case -79: case -114:
            return true;
            
        default:
            return islower(c);
    }
}

char *apply_case(const char *word, const char *translation) {
    if (!word || !translation) return strdup(word ? word : "");

    bool all_upper = true;
    bool first_upper = isupper(word[0]);
    
    for (int i = 0; word[i]; i++) {
        if (islower_rus(word[i])) {
            all_upper = false;
            break;
        }
    }

    char *result = strdup(translation);
    if (all_upper) {
        for (int i = 0; result[i]; i++) {
            result[i] = toupper(result[i]);
        }
    }
    else if (first_upper && result[0]) {
        result[0] = toupper(result[0]);
        for (int i = 1; result[i]; i++) {
            result[i] = tolower(result[i]);
        }
    } else {
        for (int i = 0; result[i]; i++) {
            result[i] = tolower(result[i]);
        }
    }

    return result;
}

char *translate_word(const char *word, HashTable *dictionary, ProgramOptions *options, const char *dict_path) {
    if (!word || strlen(word) == 0) return strdup("");

    char *lower_word = strdup_lower(word);
    char *translation = hash_table_search(dictionary, lower_word);

    if (!translation && options && !options->no_internet) {
        if (options->auto_approve) {
            char *online_translation = search_translation_online(lower_word, "ru", "en");
            if (online_translation) {
                char *proper_case = apply_case(word, online_translation);
                add_word_to_dictionary(lower_word, online_translation, dictionary, dict_path);
                free(online_translation);
                free(lower_word);
                return proper_case;
            }
        } else if (!options->no_overwrite) {
            printf("Слово '%s' не найдено в словаре. Искать в интернете? (y/n): ", word);
            char response;
            scanf(" %c", &response);
            if (response == 'y' || response == 'Y') {
                char *online_translation = search_translation_online(lower_word, "ru", "en");
                if (online_translation) {
                    char *proper_case = apply_case(word, online_translation);
                    add_word_to_dictionary(lower_word, online_translation, dictionary, dict_path);
                    free(online_translation);
                    free(lower_word);
                    return proper_case;
                }
            }
        }
    }

    char *result = translation ? apply_case(word, translation) : strdup(word);
    free(lower_word);
    return result;
}

char *translate_text(const char *text, HashTable *dictionary, ProgramOptions *options, const char *dict_path) {
    if (!text) return strdup("");

    size_t text_len = strlen(text);
    char *result = calloc(text_len * 3 + 1, 1);
    size_t result_pos = 0;
    
    size_t word_start = 0;
    bool in_word = false;
    
    for (size_t i = 0; i <= text_len; i++) {
        char c = text[i];
        bool is_let = is_letter(c);

        if (!in_word && is_let) {
            word_start = i;
            in_word = true;
        } else if (in_word && (!is_let || c == '\0')) {
            size_t word_len = i - word_start;
            char *word = malloc(word_len + 1);
            strncpy(word, text + word_start, word_len);
            word[word_len] = '\0';
            
            char *translated = translate_word(word, dictionary, options, dict_path);
            size_t trans_len = strlen(translated);
            strncpy(result + result_pos, translated, trans_len);
            result_pos += trans_len;
            
            free(translated);
            free(word);
            in_word = false;
        }
        
        if (!is_let && c != '\0') {
            result[result_pos++] = c;
        }
    }
    
    result[result_pos] = '\0';
    return result;
}