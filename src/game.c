#include <DessertDunes.h>

static Cam3D cam;

static inline void game_init_ui()
{
    int w, h;
    glee_window_get_size(&w, &h);

    wxGroup group = wxGroupCreate();

    vec4 red = {1.0, 0.0, 0.0, 1.0};
    wxTitle title = wxTitleCreate("DessertDunes", vec3_new(32, h - 48, 2.0), red);
    wxGroupPush(&group, &title, WIDGET_TITLE);
    ui_push(&group);
}

void game_init()
{
    cam = cam3D_new(vec3_new(15.0, 30.0, 15.0), 45.0);
    game_init_ui();
    player_init();
}

void game_update(float deltaTime)
{   
    cam3D_update_smooth(&cam, runtime_mouse());
    player_update(&cam, deltaTime);
    scene_update();
    render_camera(&cam);
}