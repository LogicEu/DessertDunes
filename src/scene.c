#include <DessertDunes.h>
#include <string.h>

static Model3D model;
static skybox_t skybox;
static Cam3D cam;

static inline bmp_t bmp_gradient(const int gradientSize)
{
    bmp_t bmp = bmp_new(gradientSize, 1, 4);

    for (int i = 0; i < gradientSize; i++) {
        int k = i * 45;
        uint8_t c[] = {25 + k, 25 + k, 0, 255};
        memcpy(px_at(&bmp, i, 0), c, 4);
    }

    for (int i = 0; i < 4; i++) bmp_stretch(&bmp);
    return bmp;
}

void scene_init()
{
    bmp_t bmp = bmp_gradient(4);

    model = model_perlin(100, 100, &bmp, vec2_new(100.0, 100.0));
    skybox = skybox_space(1080, 1080, 998, 1000, 1);
    
    bmp_free(&bmp);
}

void scene_render()
{
    render_skybox(&skybox);
    render_model(&model, vec3_uni(0.0));
}

void scene_view(const Cam3D* restrict c)
{
    memcpy(&cam, c, sizeof(Cam3D));
}

Cam3D* scene_camera()
{
    return &cam;
}