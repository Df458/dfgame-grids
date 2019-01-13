#include "application/game/mainloop.h"
#include "application/game/window.h"
#include "graphics/camera.h"
#include "graphics/color.h"
#include "graphics/mesh.h"
#include "graphics/shader_init.h"

#include "grid.h"

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

bool loop(mainloop l, float dt) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(s_default.id);
    shader_bind_uniform_name(s_default, "u_transform", mat4_mul(camera_get_vp(c_main), mat4_ident));
    shader_bind_uniform_name(s_default, "u_color", color_white);
    mesh_render(s_default, grid_mesh, GL_LINES, "i_pos", VT_POSITION);

    window_redraw(win);
    return !window_get_should_close(win);
}

int main() {
    win = window_new(1280, 720, false, "Grid Demo");
    shaders_init();

    s_default  = shader_basic_untex_get();
    c_main     = window_create_2d_camera(win);

    grid_mesh = grid_generate_mesh(&demo_grid, ALIGN_CENTER);

    mainloop_create_run(loop);

    camera_free(c_main);
    window_free_final(win);
    shaders_cleanup();

    return 0;
}
