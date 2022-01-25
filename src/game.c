#include <DessertDunes.h>
#include <stdio.h>
#include <time.h>

#define HALF_PI 1.57079632679

static unsigned int seed;
static vec2 mouse;
static Cam3D cam;

static inline void game_input(float deltaTime)
{
    float delta_speed = deltaTime * 4.0;

    if (glee_key_down(GLFW_KEY_D)) {
        cam.position = vec3_add(cam.position, vec3_mult(cam.right, delta_speed));
    }
    if (glee_key_down(GLFW_KEY_A)) {
        cam.position = vec3_sub(cam.position, vec3_mult(cam.right, delta_speed));
    }
    if (glee_key_down(GLFW_KEY_W)) {
        cam.position = vec3_add(cam.position, vec3_mult(cam.direction, delta_speed));
    }
    if (glee_key_down(GLFW_KEY_S)) {
        cam.position = vec3_sub(cam.position, vec3_mult(cam.direction, delta_speed));
    }
    if (glee_key_down(GLFW_KEY_Z)) {
        cam.position = vec3_add(cam.position, vec3_mult(cam.up, delta_speed));
    }
    if (glee_key_down(GLFW_KEY_X)) {
        cam.position = vec3_sub(cam.position, vec3_mult(cam.up, delta_speed));
    }
    
    if (glee_key_down(GLFW_KEY_UP)) {
        cam.position.z += delta_speed;
    }
    if (glee_key_down(GLFW_KEY_DOWN)) {
        cam.position.z -= delta_speed;
    }
    
    if (glee_key_pressed(GLFW_KEY_M)) {
        renderer_switch();
    }
}

void game_init(const unsigned int* seedptr)
{
    if (seedptr != NULL) seed = *seedptr;
    else seed = rand_uint(rand_uint(time(NULL)));
    printf("Game seed is: %d\n", seed);

    scene_init();
    cam = cam3D_new(vec3_new(0.0, 30.0, 0.0), 45.0);
}

unsigned int game_seed_get()
{
    return seed;
}

void game_update(float deltaTime)
{
    glee_mouse_pos_3d(&mouse.x, &mouse.y);
    mouse = vec2_mult(mouse, 0.01);
    
    cam3D_update(&cam, mouse);
    render_camera(&cam);
    
    game_input(deltaTime);
}