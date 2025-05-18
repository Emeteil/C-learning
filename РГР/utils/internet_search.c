#include "internet_search.h"
#include <curl/curl.h>

struct MemoryStruct {char *memory; size_t size;};
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

char *search_translation_online(const char *word, const char *source_lang, const char *target_lang) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl = curl_easy_init();
    if(!curl) {
        printf("Ошибка: Не удалось инициализировать CURL\n");
        free(chunk.memory);
        return NULL;
    }

    char url[256];
    snprintf(url, sizeof(url), "https://api.mymemory.translated.net/get?q=%s&langpair=%s|%s", word, source_lang, target_lang);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        printf("Ошибка CURL: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        free(chunk.memory);
        return NULL;
    }

    curl_easy_cleanup(curl);

    json_error_t error;
    json_t *root = json_loads(chunk.memory, 0, &error);
    free(chunk.memory);

    if(!root) {
        printf("Ошибка JSON: %s\n", error.text);
        return NULL;
    }

    // В ответе json'ка в которой нужно получить ["responseData"]["translatedText"]

    json_t *responseData = json_object_get(root, "responseData");
    if(!responseData) {
        printf("Ошибка: Нет responseData в ответе\n");
        json_decref(root);
        return NULL;
    }

    json_t *translatedText = json_object_get(responseData, "translatedText");
    if(!json_is_string(translatedText)) {
        printf("Ошибка: Нет перевода в ответе\n");
        json_decref(root);
        return NULL;
    }

    const char *translation = json_string_value(translatedText);
    char *result = strdup(translation);

    json_decref(root);
    return result;
}

void add_word_to_dictionary(const char *word, const char *translation, HashTable *dictionary, const char *dict_path) {
    if (word == NULL || translation == NULL || dict_path == NULL) return;

    FILE *dict_file = fopen(dict_path, "a");
    if (!dict_file) {
        printf("Ошибка: Не удалось открыть файл словаря для добавления слова\n");
        return;
    }

    fprintf(dict_file, "%s - %s\n", word, translation);
    fclose(dict_file);

    hash_table_insert(dictionary, word, translation);
}