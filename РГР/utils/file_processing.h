#include "translate.h"

void process_file_translation(const char *input_file, const char *output_file, HashTable *dictionary, ProgramOptions *options);
void process_directory(const char *input_dir, const char *output_dir, HashTable *dictionary, ProgramOptions *options);