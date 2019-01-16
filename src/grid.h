#ifndef DF_GRIDS_GRID
#define DF_GRIDS_GRID
#include "math/alignment.h"
#include "math/vector.h"
#include "graphics/mesh.h"

// Represents a rectangular grid
typedef struct grid {
    vec2 dims;
    uint16 rows;
    uint16 columns;
} grid;

// Generate a mesh for rendering a grid
// -> g: A reference to the grid struct to generate from
// -> align: The alignment of the mesh origin
// returns: A new mesh, or NULL on failure
mesh grid_generate_mesh(const grid* g, alignment_2d align);

// Generate a mesh for rendering a grid's points
// -> g: A reference to the grid struct to generate from
// -> align: The alignment of the mesh origin
// returns: A new mesh, or NULL on failure
mesh grid_generate_points(const grid* g, alignment_2d align);

#endif
