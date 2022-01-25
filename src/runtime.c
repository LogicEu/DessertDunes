#include <DessertDunes.h>

static unsigned int mode;
static void (*func_update)(float);
static vec2 mouse;

static inline void runtime_switch()
{
    if (mode) {
        mode--;
        func_update = &game_update;
    } else {
        mode++;
        func_update = &editor_update;
    }

    ui_switch(mode);
}

static inline void runtime_input()
{
    if (glee_key_down(GLFW_KEY_LEFT_CONTROL)) {
        if (glee_key_pressed(GLFW_KEY_M)) {
            runtime_switch();
        }
        if (glee_key_pressed(GLFW_KEY_C)) {
            renderer_switch();
        }
    }
}

vec2 runtime_mouse()
{
    return mouse;
}

void runtime_update(float deltaTime)
{
    glee_mouse_pos_3d(&mouse.x, &mouse.y);
    mouse = vec2_mult(mouse, 0.01);

    runtime_input();

    func_update(deltaTime);
    scene_render();
    ui_render();
}

void runtime_init()
{
    mode = 0;
    func_update = &game_update;

    ui_init();
    scene_init();
    game_init();
    editor_init();
    ui_switch(mode);
}