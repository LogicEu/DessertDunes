#include <DessertDunes.h>

static inline void vertex_array_bind(unsigned int id, array_t* vertices, array_t* indices, obj_flag type)
{
    if (!vertices || !indices) return;
    unsigned int VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices->used * vertices->bytes, vertices->data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->used * indices->bytes, indices->data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices->bytes, (void*)0);
    if (type == OBJ_VTN) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertices->bytes, (void*)offsetof(vertex_t, uv));
    }
    if (type != OBJ_V) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertices->bytes, (void*)offsetof(vertex_t, normal));
    }
}

static inline void vmesh_bind(unsigned int id, vmesh_t* mesh)
{
    if (!mesh) return;
    vertex_array_bind(id, mesh->vertices, mesh->indices, mesh->type);
}

static inline void vmesh_perlin(vmesh_t* mesh, const vec2 off, const float mult)
{
    const unsigned int seed = worldgen_seed();
    for (unsigned int i = 0; i < mesh->vertices->used; i++) {
        vertex_t* v = (vertex_t*)array_index(mesh->vertices, i);
        vec3 pos = v->position;
        v->position.y = perlin2d(pos.x + off.x, pos.z + off.y, 0.01, 4, seed) * mult;
    }
    mesh->type = OBJ_VN;
    vertex_array_set_face_normal(mesh->vertices, mesh->indices);
}

Model3D model_new(vmesh_t* mesh, const texture_t texture)
{
    Model3D model;
    model.id = glee_buffer_id();
    model.mesh = mesh;
    model.texture = texture;
    vmesh_bind(model.id, model.mesh);
    return model;
}

Model3D model_perlin(const unsigned int width, const unsigned int height, const bmp_t* restrict bmp, const vec2 off)
{
    vmesh_t* mesh = vmesh_shape_plane(width, height);
    vmesh_perlin(mesh, off, 32.0);
    vmesh_smooth_optim(&mesh);
    vmesh_height_color_gradient(mesh);
    mesh->type = OBJ_VTN;
    return model_new(mesh, texture_from_bmp(bmp));
}

void model_free(Model3D* model)
{
    vmesh_free(model->mesh);
}