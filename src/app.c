#include <DessertDunes.h>
#include <stdlib.h>
#include <string.h>

static inline void app_init(unsigned int fullscreen, const unsigned int* seedptr)
{
    glee_init();
    glee_window_create("DessertDunes", 800, 600, fullscreen, 0);

    worldgen_init(seedptr);
    renderer_init();
    runtime_init();
}

static inline void app_run()
{
    float iTime = glee_time_get();
    while (glee_window_is_open()) {
        glee_screen_clear();
        if (glee_key_pressed(GLFW_KEY_ESCAPE)) break;
        runtime_update(glee_time_delta(&iTime));
        glee_screen_refresh();
    }
}

static inline void app_deinit()
{
    scene_deinit();
    ui_deinit();
    ethnicExit();
    glee_deinit();
}

int main(int argc, char** argv)
{
    unsigned int fullscreen = 0;
    unsigned int seed, *seedptr = NULL;

    if (argc > 1) {
        if (!strcmp(argv[1], "-f")) {
            fullscreen++;
        } else {
            seed = atoi(argv[1]);
            seedptr = &seed;
        }
    }

    app_init(fullscreen, seedptr);
    app_run();
    app_deinit();
    return EXIT_SUCCESS;
}