#include <DessertDunes.h>
#include <stdlib.h>

static inline void app_init(const unsigned int* seedptr)
{
    glee_init();
    glee_window_create("DessertDunes", 800, 600, 0, 0);

    renderer_init();
    game_init(seedptr);
}

static inline void app_update(float deltaTime)
{
    game_update(deltaTime);
    scene_render();
}

static inline void app_run()
{
    float iTime = glee_time_get();
    while (glee_window_is_open()) {
        glee_screen_clear();
        if (glee_key_pressed(GLFW_KEY_ESCAPE)) break;
        app_update(glee_time_delta(&iTime));
        glee_screen_refresh();
    }
}

static inline void app_deinit()
{
    glee_deinit();
}

int main(int argc, char** argv)
{
    unsigned int seed, *seedptr = NULL;
    if (argc > 1) {
        seed = atoi(argv[1]);
        seedptr = &seed;
    }

    app_init(seedptr);
    app_run();
    app_deinit();
    return EXIT_SUCCESS;
}