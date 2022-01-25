#include <DessertDunes.h>

static wxDirectory wxdir;

void ui_init()
{
    int w, h;
    glee_window_get_size(&w, &h);
    gluiInit(w, h, 1);

    gluiFontSet(fontLoad("assets/fonts/Pixels.ttf", 32));
    gluiFrameSet(texture_load("assets/textures/frame16.png"));
    gluiSliderSet(
        texture_load("assets/textures/slider.png"),
        texture_load("assets/textures/marker.png")
    );
    gluiSwitchSet(
        texture_load("assets/textures/switch_down.png"),
        texture_load("assets/textures/switch_up.png")
    );

    wxdir = wxDirectoryCreate();
}

void ui_push(wxGroup* group)
{
    wxDirectoryPushGroup(&wxdir, group);
}

void ui_deinit()
{
    wxDirectoryFree(&wxdir);
}

void ui_switch(unsigned int mode)
{
    wxDirectorySelect(&wxdir, mode);
}

void ui_render()
{
    wxDirectoryDraw(&wxdir);
}