#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../translate.h"

void test_hash_table_operations(void) {
    HashTable* table = create_hash_table(100);
    
    hash_table_insert(table, "key1", "value1");
    hash_table_insert(table, "key2", "value2");
    
    CU_ASSERT_STRING_EQUAL(hash_table_search(table, "key1"), "value1");
    CU_ASSERT_STRING_EQUAL(hash_table_search(table, "key2"), "value2");
    CU_ASSERT_PTR_NULL(hash_table_search(table, "nonexistent"));
    
    hash_table_insert(table, "key1", "newvalue");
    CU_ASSERT_STRING_EQUAL(hash_table_search(table, "key1"), "newvalue");
    
    free_hash_table(table);
}

int main() {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("HashTable Tests", NULL, NULL);
    CU_add_test(suite, "hash_table operations test", test_hash_table_operations);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}