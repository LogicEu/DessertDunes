#include <DessertDunes.h>
#include <stdio.h>
#include <time.h>

static unsigned int seed;

unsigned int worldgen_seed()
{
    return seed;
}

void worldgen_init(const unsigned int* restrict seedptr)
{
    if (seedptr != NULL) seed = *seedptr;
    else seed = rand_uint(rand_uint(time(NULL)));
    printf("Worldgen seed: %u\n", seed);
}