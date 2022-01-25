#include <DessertDunes.h>
#include <string.h>

static inline uint8_t lerpu8(uint8_t a, uint8_t b, float f)
{
    return (uint8_t)lerpf((float)a, (float)b, f);
}

static inline void px_lerp(uint8_t* dst, uint8_t* a, uint8_t* b, uint8_t channels)
{
    for (int i = 0; i < channels; i++) {
        dst[i] = lerpu8(a[i], b[i], 0.5f);
    }
}

void bmp_stretch(bmp_t* bitmap)
{
    bmp_t b = bmp_new(bitmap->width * 2 - 1, 1, bitmap->channels);
    for (unsigned int i = 0; i < b.width; i++) {
        if (i % 2 == 0) {
            memcpy(px_at(&b, i, 0), px_at(bitmap, i / 2, 0), b.channels);
        } else {
            unsigned int min = (i - 1) / 2;
            unsigned int max = (i + 1) / 2;
            min *= (min > 0);
            if (max > bitmap->width) max = bitmap->width;
            px_lerp(px_at(&b, i, 0), px_at(bitmap, min, 0), px_at(bitmap, max, 0), b.channels);
        }
    }
    bmp_free(bitmap);
    *bitmap = b;
}

void bmp_stretch_irregular(bmp_t* bitmap)
{
    bmp_t b = bmp_new(bitmap->width * 2 - 1, 1, bitmap->channels);
    for (unsigned int i = 0; i < b.width; i++) {
        if (i % 2 == 0) {
            memcpy(px_at(&b, i, 0), px_at(bitmap, i / 2, 0), b.channels);
        } else {
            unsigned int min = i / 2 - 1;
            unsigned int max = i / 2 + 1;
            min *= (min > 0);
            if (max > bitmap->width) max = bitmap->width;
            px_lerp(px_at(&b, i, 0), px_at(bitmap, min, 0), px_at(bitmap, max, 0), b.channels);
        }
    }
    bmp_free(bitmap);
    *bitmap = b;
}

void bmp_smooth(bmp_t* bitmap, const unsigned int smooth)
{
    for (unsigned int y = 0; y < bitmap->height; y++) {
        for (unsigned int x = 0; x < bitmap->width; x++) {
            if (*px_at(bitmap, x, y) > 105 && rand_next() % smooth != 0) {
                if (x + 1 < bitmap->width) px_lerp(px_at(bitmap, x + 1, y), px_at(bitmap, x + 1, y), px_at(bitmap, x, y), bitmap->channels);
                if (x > 0) px_lerp(px_at(bitmap, x - 1, y), px_at(bitmap, x - 1, y), px_at(bitmap, x, y), bitmap->channels);
                if (y + 1 < bitmap->height) px_lerp(px_at(bitmap, x, y + 1), px_at(bitmap, x, y + 1), px_at(bitmap, x, y), bitmap->channels);
                if (y > 0) px_lerp(px_at(bitmap, x, y - 1), px_at(bitmap, x, y - 1), px_at(bitmap, x, y), bitmap->channels);
            }
        }
    }
}