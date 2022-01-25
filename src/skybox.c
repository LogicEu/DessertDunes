#include <DessertDunes.h>
#include <string.h>

static inline bmp_t bmp_pattern_space(const unsigned int w, const unsigned int h, const unsigned int n, const unsigned in, const unsigned int smooth)
{
    uint8_t color[] = {0, 0, 0, 0};
    bmp_t bitmap = bmp_color(w, h, 4, &color[0]);
    for (unsigned int y = 0; y < bitmap.height; y++) {
        for (unsigned int x = 0; x < bitmap.width; x++) {
            if (rand_next() % in > n) memset(px_at(&bitmap, x, y), 255, bitmap.channels);
        }
    }

    for (unsigned int i = 0; i < smooth; i++) {
        bmp_smooth(&bitmap, smooth);
    }
    
    return bitmap;
}

static inline texture_t texture_cubemap_space(const unsigned int w, const unsigned int h, const unsigned int n, const unsigned int in, const unsigned int smooth)
{
    texture_t texture;
    texture.width = w;
    texture.height = h;
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.id);

    for (int i = 0; i < 6; i++) {
        bmp_t bitmap = bmp_pattern_space(w, h, n, in, smooth);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.pixels);
        bmp_free(&bitmap);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

skybox_t skybox_space(const unsigned int w, const unsigned int h, const unsigned int n, const unsigned int in, const unsigned int smooth)
{
    skybox_t skybox;
    skybox.cubemap = texture_cubemap_space(w, h, n, in, smooth);
    skybox.VAO = glee_buffer_skybox_create();
    return skybox;
}