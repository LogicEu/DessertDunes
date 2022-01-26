#include <DessertDunes.h>
#include <stdio.h>
#include <time.h>

static unsigned int seed;

float worldgen_perlin(float x, float y)
{
    return perlin2d(x + 1000.0, y + 1000.0, 0.05, 4, seed) * 32.0;
}

unsigned int worldgen_seed()
{
    return seed;
}

void worldgen_init(const unsigned int* restrict seedptr)
{
    if (seedptr != NULL) seed = *seedptr;
    else seed = rand_uint(rand_uint(time(NULL)));
    
    rand_seed(seed);
    printf("Worldgen seed: %u\n", seed);
}