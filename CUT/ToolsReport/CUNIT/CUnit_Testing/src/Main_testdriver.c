#include <CUnit/Basic.h>

#include "../include/result.h"
#include "../include/result_suite.h"
#include "../include/valid.h"
#include "../include/valid_suite.h"

int main() {
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite 1 to the registry */
    CU_pSuite pSuite1 = NULL;
    pSuite1 = CU_add_suite("Suite Valid file", init_suite_valid, clean_suite_valid);
    if (NULL == pSuite1) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite1, "test of valid() in Sunny cases", testSunnyCases1)) || (NULL == CU_add_test(pSuite1, "test of valid() in Rainy cases", testRainyCases1))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite 2 to the registry */
    CU_pSuite pSuite2 = NULL;
    pSuite2 = CU_add_suite("Suite Result file", init_suite_result, clean_suite_result);
    if (NULL == pSuite2) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite2, "Test of result_valid() in Sunny cases", testSunnyCases2)) || (NULL == CU_add_test(pSuite2, "Test of result_Valid() in Rainy cases", testRainyCases2))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
