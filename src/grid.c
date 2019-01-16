#define LOG_CATEGORY "Grids"

#include "grid.h"

#include "core/check.h"

// Generate a mesh for rendering a grid
// -> g: A reference to the grid struct to generate from
// -> align: The alignment of the mesh origin
// returns: A new mesh, or NULL on failure
mesh grid_generate_mesh(const grid* g, alignment_2d align) {
    check_return(g != NULL, "Provided grid is NULL", NULL);
    check_return(g->rows >= 1 && g->columns >= 1, "Provided grid is invalid: Must have at least 1 row/column", NULL);

    // Create a bounding box from the grid size and alignment
    aabb_2d bounds = {
        .position = vec2_zero,
        .dimensions = {
            .x = g->dims.x * g->columns,
            .y = g->dims.y * g->rows
        }
    };
    bounds = aabb_align_point(bounds, vec2_zero, align);

    vt_p mesh_data[(g->rows + g->columns + 2) * 2];

    // Generate the vertices
    for(uint16 i = 0; i < g->rows + 1; ++i) {
        float pos = (i * g->dims.y);

        mesh_data[i * 2] = (vt_p) {
            .position = {
                .x = bounds.position.x,
                .y = bounds.position.y + pos
            }
        };
        mesh_data[(i * 2) + 1] = (vt_p) {
            .position = {
                .x = bounds.position.x + bounds.dimensions.x,
                .y = bounds.position.y + pos
            }
        };
    }

    for(uint16 i = 0; i < g->columns + 1; ++i) {
        float pos = (i * g->dims.x);
        uint16 index = (g->rows + 1 + i);

        mesh_data[index * 2] = (vt_p) {
            .position = {
                .x = bounds.position.x + pos,
                .y = bounds.position.y
            }
        };
        mesh_data[(index * 2) + 1] = (vt_p) {
            .position = {
                .x = bounds.position.x + pos,
                .y = bounds.position.y + bounds.dimensions.y
            }
        };
    }

    // Create and return the mesh
    return mesh_new((g->rows + g->columns + 2) * 2, mesh_data, NULL);
}

// Generate a mesh for rendering a grid's points
// -> g: A reference to the grid struct to generate from
// -> align: The alignment of the mesh origin
// returns: A new mesh, or NULL on failure
mesh grid_generate_points(const grid* g, alignment_2d align) {
    check_return(g != NULL, "Provided grid is NULL", NULL);
    check_return(g->rows >= 1 && g->columns >= 1, "Provided grid is invalid: Must have at least 1 row/column", NULL);

    // Create a bounding box from the grid size and alignment
    aabb_2d bounds = {
        .position = vec2_zero,
        .dimensions = {
            .x = g->dims.x * g->columns,
            .y = g->dims.y * g->rows
        }
    };
    bounds = aabb_align_point(bounds, vec2_zero, align);

    vt_p mesh_data[(g->rows + 1) * (g->columns + 1)];

    // Generate the vertices
    for(uint16 i = 0; i < g->rows + 1; ++i) {
        for(uint16 j = 0; j < g->columns + 1; ++j) {
            mesh_data[i * (g->columns + 1) + j] = (vt_p) {
                .position = {
                    .x = bounds.position.x + (j * g->dims.x),
                    .y = bounds.position.y + (i * g->dims.y)
                }
            };
        }
    }

    // Create and return the mesh
    return mesh_new((g->rows + 1) * (g->columns + 1), mesh_data, NULL);
}
