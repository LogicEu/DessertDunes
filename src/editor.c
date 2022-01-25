#include <DessertDunes.h>

static Cam3D cam;

static inline void editor_input(float deltaTime)
{
    const float speed = 4.0;
    float delta_speed = deltaTime * speed;

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
}

static inline void editor_init_ui()
{
    int w, h;
    glee_window_get_size(&w, &h);

    wxGroup group = wxGroupCreate();

    vec4 blue = {0.3, 0.3, 1.0, 1.0};
    wxTitle title = wxTitleCreate("Editor", vec3_new(32, h - 48, 2.0), blue);
    wxGroupPush(&group, &title, WIDGET_TITLE);
    
    ui_push(&group);
}

void editor_init()
{
    cam = cam3D_new(vec3_uni(0.0), 45.0);
    editor_init_ui();
}

void editor_update(float deltaTime)
{
    cam3D_update(&cam, runtime_mouse());
    render_camera(&cam);

    editor_input(deltaTime);
}