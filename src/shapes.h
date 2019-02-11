#ifndef DF_GRIDS_SHAPES
#define DF_GRIDS_SHAPES
#include "core/types.h"

#include "grid.h"

// Get the positions on a grid between (and including) a start and end position
uint16* line_to_grid(const grid* g, uint16 start_x, uint16 start_y, uint16 end_x, uint16 end_y, uint32* len);

#endif
