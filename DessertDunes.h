#ifndef DESSERT_DUNES_H
#define DESSERT_DUNES_H

#ifdef __cplusplus
extern "C" {
#endif

/******************
 * DESSERT DUNES
 ****************/

#include <mass.h>
#include <gleex.h>

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
    vmesh_t* mesh;
    texture_t texture;
} Model3D;

// ...

void bmp_smooth(bmp_t* bitmap, const unsigned int smooth);
void bmp_stretch_irregular(bmp_t* bitmap);
void bmp_stretch(bmp_t* bitmap);

skybox_t skybox_space(const unsigned int w, const unsigned int h, const unsigned int n, const unsigned int in, const unsigned int smooth);

Model3D model_new(vmesh_t* mesh, const texture_t texture);
Model3D model_perlin(const unsigned int width, const unsigned int height, const bmp_t* bmp, const vec2 off);
void model_free(Model3D* model);

Cam3D cam3D_new(vec3 position, float fov);
void cam3D_update(Cam3D* cam, vec2 dir);

void renderer_init();
void render_camera(const Cam3D* camera);
void render_model(const Model3D* model, vec3 position);
void render_skybox(const skybox_t* skybox);
void renderer_switch();

void scene_init();
void scene_render();

void game_init(const unsigned int* seedptr);
void game_update(float deltaTime);
unsigned int game_seed_get();

// ...

#ifdef __cplusplus
}
#endif
#endif