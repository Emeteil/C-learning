#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../translate.h"

void test_translate_word(void) {
    HashTable* dict = create_hash_table(100);
    hash_table_insert(dict, "cat", "котик");
    
    ProgramOptions options = {
        .no_internet = true,
        .auto_approve = false,
        .no_overwrite = false
    };
    
    char* trans1 = translate_word("cat", dict, &options, NULL);
    CU_ASSERT_STRING_EQUAL(trans1, "котик");
    free(trans1);
    
    char* trans2 = translate_word("unknown", dict, &options, NULL);
    CU_ASSERT_STRING_EQUAL(trans2, "unknown");
    free(trans2);
    
    free_hash_table(dict);
}

int main() {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("Translation Tests", NULL, NULL);
    CU_add_test(suite, "translate_word test", test_translate_word);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}