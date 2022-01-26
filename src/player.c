#include <DessertDunes.h>

static Entity player;

void player_update(Cam3D* cam, float deltaTime)
{
    deltaTime *= 5.0;

    vec3* pos = entity_get(player, COMPONENT_POSITION);

    if (glee_key_down(GLFW_KEY_D)) {
        *pos = vec3_add(*pos, vec3_mult(cam->right, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_A)) {
        *pos = vec3_sub(*pos, vec3_mult(cam->right, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_W)) {
        *pos = vec3_add(*pos, vec3_mult(cam->direction, deltaTime));
    }
    if (glee_key_down(GLFW_KEY_S)) {
        *pos = vec3_sub(*pos, vec3_mult(cam->direction, deltaTime));
    }

    pos->y = worldgen_perlin(pos->x, pos->z) + 0.5;

    cam->position = vec3_lerp(cam->position, vec3_sub(*pos, vec3_mult(cam->direction, 10.0)), 0.1);
    cam->position.y = maxf(cam->position.y, worldgen_perlin(cam->position.x, cam->position.z) + 0.2);
}

void player_init()
{
    uint8_t c[] = {255, 0, 0, 255};
    bmp_t bmp = bmp_color(1, 1, 4, c);
    Model3D model = model_new(vmesh_shape_sphere(4), texture_from_bmp(&bmp));
    player = archetype_player(vec3_new(15.0, 30.0, 15.0), &model);
    bmp_free(&bmp);
}