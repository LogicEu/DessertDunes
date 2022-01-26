#include <DessertDunes.h>
#include <stdio.h>

static unsigned int mode;
static float time_speed;
static void (*func_update)(float);
static vec2 mouse;

static void runtime_pause()
{
    static unsigned int prevMode;

    if (mode != MODE_PAUSE) {
        prevMode = mode;
        mode = MODE_PAUSE;
    } else {
        mode = prevMode;
    }
}

static inline void runtime_switch()
{
    if (mode == MODE_EDITOR) {
        mode = MODE_GAME;
        func_update = &game_update;
    } else if (mode == MODE_GAME) {
        mode = MODE_EDITOR;
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
        if (glee_key_pressed(GLFW_KEY_P)) {
            runtime_pause();
        }
        if (glee_key_pressed(GLFW_KEY_Z)) {
            time_speed *= 0.5;
            printf("Time Speed: %f\n", time_speed);
        }
        if (glee_key_pressed(GLFW_KEY_X)) {
            time_speed *= 2.0;
            printf("Time Speed: %f\n", time_speed);
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

    if (mode != MODE_PAUSE) {
        func_update(deltaTime * time_speed);
    }
    
    scene_render();
    ui_render();
}

void runtime_init()
{
    mode = MODE_GAME;
    func_update = &game_update;
    time_speed = 1.0;

    ecs_init();
    ui_init();
    scene_init();
    game_init();
    editor_init();
    ui_switch(mode);
}