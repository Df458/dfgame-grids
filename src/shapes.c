#include "shapes.h"

#include "core/check.h"

#include <stdlib.h>

uint16* line_to_grid(const grid* g, uint16 start_x, uint16 start_y, uint16 end_x, uint16 end_y, uint32* len) {
    // Initialize len, just in case
    *len = 0;

    check_return(g != NULL, "Provided grid is NULL", NULL);
    check_return(start_x <= g->rows && start_y <= g->columns && end_x <= g->rows && end_y <= g->columns, "Line [%d, %d] -> [%d, %d] goes out of bounds. Grid dimensions are [%d, %d]", NULL, start_x, start_y, end_x, end_y, g->rows, g->columns);

    int32 diff_x = abs(end_x - start_x);
    int32 diff_y = abs(end_y - start_y);

    bool steep = diff_y > diff_x;

    // Force the line to go from the low to high
    uint16 true_start_x = start_x;
    uint16 true_end_x = end_x;
    uint16 true_start_y = start_y;
    uint16 true_end_y = end_y;
    if((steep && start_y > end_y) || (!steep && start_x > end_x)) {
        true_start_x = end_x;
        true_end_x = start_x;
        true_start_y = end_y;
        true_end_y = start_y;
    }

    *len = steep ? (diff_y + 1) * 2 : (diff_x + 1) * 2;
    uint16* points = mscalloc(*len, uint16);

    uint16 x = true_start_x;
    uint16 y = true_start_y;

    int32 err;
    if(steep) {
        err = diff_y / 2;
        int8 step = (true_start_x < true_end_x) ? 1 : -1;
        for(uint16 i = 0; i <= diff_y; ++i) {
            points[i * 2] = x;
            points[(i * 2) + 1] = y;

            err -= diff_x;
            if(err < 0) {
                x += step;
                err += diff_y;
            }

            ++y;
        }
    } else {
        err = diff_x / 2;
        int8 step = (true_start_y < true_end_y) ? 1 : -1;
        for(uint16 i = 0; i <= diff_x; ++i) {
            points[i * 2] = x;
            points[(i * 2) + 1] = y;

            err -= diff_y;
            if(err < 0) {
                y += step;
                err += diff_x;
            }

            ++x;
        }
    }

    return points;
}
