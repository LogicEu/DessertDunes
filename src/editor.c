#include <DessertDunes.h>
#include <stdio.h>

#define WX_TITLE 0
#define WX_FPS 1

static Cam3D cam;

static inline void editor_input(float deltaTime)
{
    deltaTime *= 5.0;

    if (glee_key_down(GLFW_KEY_D)) {
        cam.position = vec3_add(cam.position, vec3_mult(cam.right, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_A)) {
        cam.position = vec3_sub(cam.position, vec3_mult(cam.right, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_W)) {
        cam.position = vec3_add(cam.position, vec3_mult(cam.direction, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_S)) {
        cam.position = vec3_sub(cam.position, vec3_mult(cam.direction, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_Z)) {
        cam.position = vec3_add(cam.position, vec3_mult(cam.up, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_X)) {
        cam.position = vec3_sub(cam.position, vec3_mult(cam.up, deltaTime));
    }
    
    if (glee_key_down(GLFW_KEY_UP)) {
        cam.position.z += deltaTime;
    }
    if (glee_key_down(GLFW_KEY_DOWN)) {
        cam.position.z -= deltaTime;
    }
}

static inline void editor_update_ui(float deltaTime)
{
    wxGroup* wxgroup = ui_group(MODE_EDITOR);
    wxTitle* fps = wxgroup->widgets[WX_FPS].widget;

    static unsigned int counter = 1;
    if (counter % 100 == 0) sprintf(fps->string, "FPS: %.01f", 1.0 / deltaTime);
    counter++;
}

static inline void editor_init_ui()
{
    int w, h;
    glee_window_get_size(&w, &h);

    wxGroup group = wxGroupCreate();

    vec4 blue = {0.3, 0.3, 1.0, 1.0};
    wxTitle title = wxTitleCreate("Editor", vec3_new(32, h - 48, 2.0), blue);
    wxGroupPush(&group, &title, WIDGET_TITLE);
    title = wxTitleCreate("Fps: 0.0", vec3_new(32, h - 74, 2.0), blue);
    wxGroupPush(&group, &title, WIDGET_TITLE);

    ui_push(&group);
}

void editor_init()
{
    cam = cam3D_new(vec3_new(15.0, 30.0, 15.0), 45.0);
    editor_init_ui();
}

void editor_update(float deltaTime)
{
    cam3D_update(&cam, runtime_mouse());
    render_camera(&cam);

    editor_input(deltaTime);
    editor_update_ui(deltaTime);
}