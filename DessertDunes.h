#ifndef DESSERT_DUNES_H
#define DESSERT_DUNES_H

#ifdef __cplusplus
extern "C" {
#endif

/******************
 * DESSERT DUNES
 ****************/

#include <glui.h>
#include <mass.h>
#include <ethnic.h>

#define MODE_PAUSE 0
#define MODE_GAME 1
#define MODE_EDITOR 2

#define COMPONENT_POSITION 0
#define COMPONENT_MODEL 1

typedef struct Cam3D {
    vec3 position;
    vec3 direction;
    vec3 right;
    vec3 up;
    mat4 projection;
    mat4 view;
} Cam3D;

typedef struct Model3D {
    unsigned int id;
    unsigned int VAO;
    vmesh_t* mesh;
    texture_t texture;
} Model3D;

// ...

void bmp_smooth(bmp_t* bitmap, const unsigned int smooth);
void bmp_stretch_irregular(bmp_t* bitmap);
void bmp_stretch(bmp_t* bitmap);

skybox_t skybox_space(const unsigned int w, const unsigned int h, const unsigned int n, const unsigned int in, const unsigned int smooth);

void vmesh_perlin(vmesh_t* mesh, const vec2 off);
Model3D model_new(vmesh_t* mesh, const texture_t texture);
Model3D model_perlin(const unsigned int width, const unsigned int height, const bmp_t* bmp, const vec2 off);
void model_free(Model3D* model);
void model_rebind(const Model3D* model);

Cam3D cam3D_new(vec3 position, float fov);
void cam3D_update(Cam3D* cam, vec2 dir);
void cam3D_update_smooth(Cam3D* cam, vec2 dir);

void ecs_init();
Entity archetype_dune(vec3 pos, Model3D* m);
Entity archetype_player(vec3 pos, Model3D* m);

void renderer_init();
void render_camera(const Cam3D* camera);
void render_model(const Model3D* model, vec3 position);
void render_skybox(const skybox_t* skybox);
void renderer_switch();

void player_init();
void player_update(Cam3D* cam, float deltaTime);

void ui_init();
void ui_deinit();
void ui_render();
void ui_switch(unsigned int mode);
void ui_push(wxGroup* group);
wxGroup* ui_group(unsigned int mode);

void scene_init();
void scene_render();
void scene_deinit();
void scene_update();

void editor_update(float deltaTime);
void editor_init();

void worldgen_init(const unsigned int* restrict seedptr);
unsigned int worldgen_seed();
float worldgen_perlin(float x, float y);

vec2 runtime_mouse();
void runtime_update(float deltaTime);
void runtime_init();

void game_init();
void game_update(float deltaTime);
unsigned int game_seed_get();
void game_mode_switch();

// ...

#ifdef __cplusplus
}
#endif
#endif
