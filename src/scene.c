#include <DessertDunes.h>
#include <string.h>

const static int grid_size = 30;

static skybox_t skybox;
static Cam3D cam;
static Entity dune[9];

static inline vec2 vec3_flat(vec3 v)
{
    return (vec2){v.x, v.z};
}

static inline bmp_t bmp_gradient(const int gradientSize)
{
    bmp_t bmp = bmp_new(gradientSize, 1, 4);

    for (int i = 0; i < gradientSize; i++) {
        int k = i * 45;
        uint8_t c[] = {145, 145, 0, 255};
        //uint8_t c[] = {45 + k, 45 + k, 0, 255};
        memcpy(px_at(&bmp, i, 0), c, 4);
    }

    for (int i = 0; i < 4; i++) bmp_stretch(&bmp);
    return bmp;
}

void scene_update()
{
    static int posx = 0, posy = 0;

    int x = floorf(cam.position.x / (float)grid_size);
    int y = floorf(cam.position.z / (float)grid_size);

    if (posx == x && posy == y) return;

    posx = x;
    posy = y;

    Model3D* m = entity_get(dune[0], COMPONENT_MODEL);
    vec3* p = entity_get(dune[0], COMPONENT_POSITION);
    for (int i = 0; i < 9; i++) {
        int yy = i / 3;
        int xx = i % 3;

        *p = vec3_new((x + xx) * grid_size, p->y, (y + yy) * grid_size);
        vmesh_perlin(m->mesh, vec3_flat(*p));
        model_rebind(m);
        
        p++;
        m++;
    }
}

void scene_init()
{
    bmp_t bmp = bmp_gradient(4);
    Model3D model;

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            vec2 p = {(float)(grid_size * (x)), (float)(grid_size * (y))};
            model = model_perlin(grid_size, grid_size, &bmp, p);
            dune[y * 3 + x] = archetype_dune(vec3_new(p.x, 0.0, p.y), &model);
        }
    }
    
    skybox = skybox_space(1080, 1080, 998, 1000, 1);
    
    bmp_free(&bmp);
}

void scene_deinit()
{
    unsigned int size = component_entity_count(COMPONENT_MODEL);
    Model3D* m = component_get(COMPONENT_MODEL);
    for (unsigned int i = 0; i < size; i++) {
        model_free(m++);
    }
}

void scene_render()
{
    render_skybox(&skybox);

    unsigned int size = component_entity_count(COMPONENT_MODEL);
    Model3D* m = component_get(COMPONENT_MODEL);
    for (unsigned int i = 0; i < size; i++) {
        Entity e = entity_find(COMPONENT_MODEL, i);
        vec3* pos = entity_get(e, COMPONENT_POSITION); 
        render_model(m++, *pos);
    }
}

void scene_view(const Cam3D* restrict c)
{
    memcpy(&cam, c, sizeof(Cam3D));
}

Cam3D* scene_camera()
{
    return &cam;
}