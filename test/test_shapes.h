#ifndef TEST_CORE_SHAPES
#define TEST_CORE_SHAPES

#include <CUnit/CUnit.h>

int test_shapes_init();
int test_shapes_cleanup();
void test_shapes_build_tests(CU_pSuite suite);

void test_shapes_line_invalid();
void test_shapes_line_single();
void test_shapes_line_straight();
void test_shapes_line_normal();

#endif // TEST_CORE_SHAPES
