#include "../include/valid.h"
#include "CUnit/Basic.h"

int init_suite_valid(void) {
    return 0;
}

int clean_suite_valid(void) {
    return 0;
}

void testSunnyCases1(void) {
    CU_ASSERT_EQUAL(validation("data/unit_testcases/t1.txt"), 1);
    CU_ASSERT_EQUAL(validation("data/unit_testcases/t2.txt"), 1);
    CU_ASSERT_EQUAL(validation("data/unit_testcases/t3.txt"), 1);
}
void testRainyCases1(void) {
    CU_ASSERT_EQUAL(validation("data/unit_testcases/t4.txt"), 0);
    CU_ASSERT_EQUAL(validation("data/unit_testcases/t5.txt"), 0);
    CU_ASSERT_EQUAL(validation("data/unit_testcases/t6.txt"), 0);
}
