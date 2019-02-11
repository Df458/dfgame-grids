#include "application/game/mainloop.h"
#include "application/game/window.h"
#include "core/log/log.h"
#include "graphics/camera.h"
#include "graphics/color.h"
#include "graphics/mesh.h"
#include "graphics/shader_init.h"

#include "grid.h"
#include "shapes.h"

#include <stdlib.h>
#include <time.h>

window win;
camera c_main;
shader s_default;

grid demo_grid = {
    .dims = {
        .x = 24,
        .y = 24
    },
    .rows = 10,
    .columns = 10,
};
mesh grid_mesh;
mesh grid_points;
mesh line_mesh;

mesh make_line_mesh(uint16 start_x, uint16 start_y, uint16 end_x, uint16 end_y) {
    uint32 len;
    uint16* points = line_to_grid(&demo_grid, start_x, start_y, end_x, end_y, &len);
    mesh m = NULL;
    len /= 2;
    if(len > 0) {
        vt_p* verts = mscalloc(len, vt_p);

        aabb_2d box = (aabb_2d) {
            .position = vec2_mul(demo_grid.dims, -demo_grid.rows / 2),
            .dimensions = vec2_mul(demo_grid.dims, demo_grid.rows)
        };
        for(int i = 0; i < len; ++i) {
            verts[i].position = (vec3){ .x = points[i * 2] * demo_grid.dims.x + (demo_grid.dims.x * 0.5f), .y = points[i * 2 + 1] * demo_grid.dims.y + (demo_grid.dims.y * 0.5f), .z = 0 };
            verts[i].position.xy = vec_add(verts[i].position.xy, aabb_get_origin(box, ALIGN_TOP_LEFT));
        }

        m = mesh_new(len, verts, NULL);

        sfree(points);
    }

    return m;
}

bool loop(mainloop l, float dt) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glUseProgram(s_default.id);
    shader_bind_uniform_name(s_default, "u_transform", mat4_mul(camera_get_vp(c_main), mat4_ident));
    shader_bind_uniform_name(s_default, "u_color", color_white);
    mesh_render(s_default, grid_mesh, GL_LINES, "i_pos", VT_POSITION);

    glPointSize(5);
    shader_bind_uniform_name(s_default, "u_color", color_blue);
    mesh_render(s_default, grid_points, GL_POINTS, "i_pos", VT_POSITION);

    glPointSize(10);
    shader_bind_uniform_name(s_default, "u_color", color_yellow);
    mesh_render(s_default, line_mesh, GL_POINTS, "i_pos", VT_POSITION);

    window_redraw(win);
    return !window_get_should_close(win);
}

int main() {
    win = window_new(1280, 720, false, "Grid Demo");
    shaders_init();

    s_default  = shader_basic_untex_get();
    c_main     = window_create_2d_camera(win);

    grid_mesh = grid_generate_mesh(&demo_grid, ALIGN_CENTER);
    grid_points = grid_generate_points(&demo_grid, ALIGN_CENTER);

    srand(time(NULL));

    line_mesh = make_line_mesh(rand() % 10, rand() % 10, rand() % 10, rand() % 10);

    mainloop_create_run(loop);

    camera_free(c_main);
    window_free_final(win);
    shaders_cleanup();

    return 0;
}
