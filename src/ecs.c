#include <DessertDunes.h>

static Module module;
static Component position, model;
static Archetype player, dune;

Entity archetype_player(vec3 pos, Model3D* m)
{
    return archetype_entity(player, 2, &pos, m);
}

Entity archetype_dune(vec3 pos, Model3D* m)
{
    return archetype_entity(dune, 2, &pos, m);
}

static void archetypes_init()
{
    player = archetype_create(2, position, model);
    dune = archetype_create(2, position, model);
}

static inline void module_init()
{
    module = module_create(0);
    position = component_create(sizeof(vec3));
    model = component_create(sizeof(Model3D));
}

void ecs_init()
{
    ethnicInit();
    module_init();
    archetypes_init();
}