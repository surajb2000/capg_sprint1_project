#include "../include/result.h"
#include "CUnit/Basic.h"

int init_suite_result(void) {
    return 0;
}

int clean_suite_result(void) {
    return 0;
}

void testSunnyCases2(void) {
    CU_ASSERT_EQUAL(result_Valid("Artificial Intelligence"), 3);
    CU_ASSERT_EQUAL(result_Valid("Computer technology"), 2);
    CU_ASSERT_EQUAL(result_Valid("Intelligent system"), 3);
}
void testRainyCases2(void) {
    CU_ASSERT_EQUAL(result_Valid("Transporthhhhh"), 0);
    CU_ASSERT_EQUAL(result_Valid("Capgemini"), 0);
    CU_ASSERT_EQUAL(result_Valid("testCase"), 0);
}
