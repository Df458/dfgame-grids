#include "test_shapes.h"

#include "shapes.h"

#include <stdlib.h>

int test_shapes_init() {
    return 0;
}
int test_shapes_cleanup() {
    return 0;
}
void test_shapes_build_tests(CU_pSuite suite) {
    CU_ADD_TEST(suite, test_shapes_line_invalid);
    CU_ADD_TEST(suite, test_shapes_line_single);
    CU_ADD_TEST(suite, test_shapes_line_straight);
}

void test_shapes_line_invalid() {
    grid g = {
        .dims = {
            .x = 24,
            .y = 24
        },
        .rows = 10,
        .columns = 10,
    };

    uint32 len;
    CU_ASSERT_PTR_NULL(line_to_grid(NULL, 0, 0, 1, 1, &len));
    CU_ASSERT_EQUAL(len, 0);

    CU_ASSERT_PTR_NULL(line_to_grid(&g, 0, 0, g.rows + 1, 0, &len));
    CU_ASSERT_EQUAL(len, 0);

    CU_ASSERT_PTR_NULL(line_to_grid(&g, 0, 0, 0, g.columns + 1, &len));
    CU_ASSERT_EQUAL(len, 0);

    CU_ASSERT_PTR_NULL(line_to_grid(&g, g.rows + 1, 0, 0, 0, &len));
    CU_ASSERT_EQUAL(len, 0);

    CU_ASSERT_PTR_NULL(line_to_grid(&g, 0, g.columns + 1, 0, 0, &len));
    CU_ASSERT_EQUAL(len, 0);
}
void test_shapes_line_single() {
    grid g = {
        .dims = {
            .x = 24,
            .y = 24
        },
        .rows = 10,
        .columns = 10,
    };

    for(int i = 0; i < 20; ++i) {
        uint16 x = rand() % g.rows;
        uint16 y = rand() % g.rows;
        uint32 len;

        uint16* ptr = line_to_grid(&g, x, y, x, y, &len);
        CU_ASSERT_PTR_NOT_NULL(ptr);
        CU_ASSERT_EQUAL(len, 2);
        CU_ASSERT_EQUAL(ptr[0], x);
        CU_ASSERT_EQUAL(ptr[1], y);
        sfree(ptr);
    }
}
void test_shapes_line_straight() {
    grid g = {
        .dims = {
            .x = 24,
            .y = 24
        },
        .rows = 10,
        .columns = 10,
    };

    uint16 x = 5;
    uint16 y = 5;
    uint32 len;

    uint16* ptr = line_to_grid(&g, x, y, x + 5, y, &len);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(len, 12);
    for(int i = 0; i < len / 2; ++i) {
        CU_ASSERT_EQUAL(ptr[i * 2 + 1], y);
    }
    sfree(ptr);

    ptr = line_to_grid(&g, x, y, x - 5, y, &len);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(len, 12);
    for(int i = 0; i < len / 2; ++i) {
        CU_ASSERT_EQUAL(ptr[i * 2 + 1], y);
    }
    sfree(ptr);

    ptr = line_to_grid(&g, x, y, x, y + 5, &len);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(len, 12);
    for(int i = 0; i < len / 2; ++i) {
        CU_ASSERT_EQUAL(ptr[i * 2], x);
    }
    sfree(ptr);

    ptr = line_to_grid(&g, x, y, x, y - 5, &len);
    CU_ASSERT_PTR_NOT_NULL(ptr);
    CU_ASSERT_EQUAL(len, 12);
    for(int i = 0; i < len / 2; ++i) {
        CU_ASSERT_EQUAL(ptr[i * 2], x);
    }
    sfree(ptr);
}
