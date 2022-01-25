#include <DessertDunes.h>

extern void scene_view(const Cam3D* restrict c);
extern Cam3D* scene_camera();

static mat4 matId;
static unsigned int drawMode;
static unsigned int lightshader, skyboxshader;

static inline void shaders_init()
{
    lightshader = glee_shader_load("assets/shaders/lightv.frag", "assets/shaders/light.frag");
    glUniform3f(glGetUniformLocation(lightshader, "global_light.direction"), -0.5f, -1.0f, -0.5f);
    glUniform3f(glGetUniformLocation(lightshader, "global_light.ambient"), 0.0f, 0.0f, 0.0f);
    glUniform3f(glGetUniformLocation(lightshader, "global_light.diffuse"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(lightshader, "global_light.specular"), 0.7f, 0.7f, 0.7f);

    glUniform3f(glGetUniformLocation(lightshader, "point_light.position"), 4.0f, 8.0f, 4.0f); 
    glUniform3f(glGetUniformLocation(lightshader, "point_light.ambient"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(lightshader, "point_light.diffuse"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(lightshader, "point_light.specular"), 1.0f, 1.0f, 1.0f);

    glUniform1f(glGetUniformLocation(lightshader, "point_light.constant"), .01f);
    glUniform1f(glGetUniformLocation(lightshader, "point_light.linear"), 0.01f);
    glUniform1f(glGetUniformLocation(lightshader, "point_light.quadratic"), 0.01f);
    glUniform1f(glGetUniformLocation(lightshader, "shininess"), 32.0f);

    skyboxshader = glee_shader_load("assets/shaders/skyboxvert.frag", "assets/shaders/skyboxfrag.frag");
}

void renderer_init()
{
    int w, h;
    glee_window_get_size(&w, &h);
    
    drawMode = GL_TRIANGLES;
    matId = mat4_id();

    shaders_init();
    glee_set_3d_mode();
}

void render_camera(const Cam3D* restrict cam)
{
    scene_view(cam);
    glUseProgram(lightshader);
    glUniformMatrix4fv(glGetUniformLocation(lightshader, "view"), 1, GL_FALSE, &cam->view.data[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(lightshader, "projection"), 1, GL_FALSE, &cam->projection.data[0][0]);
    glUniform3f(glGetUniformLocation(lightshader, "viewPos"), cam->position.x, cam->position.y, cam->position.z);
}

void render_model(const Model3D* restrict model, vec3 position)
{
    mat4 m = mat4_translate(matId, position);

    glUseProgram(lightshader);
    glBindVertexArray(model->id);
    glBindTexture(GL_TEXTURE_2D, model->texture.id);
    glUniformMatrix4fv(glGetUniformLocation(lightshader, "model"), 1, GL_FALSE, &m.data[0][0]);
    glDrawElements(drawMode, model->mesh->indices->used, GL_UNSIGNED_INT, 0);
}

void render_skybox(const skybox_t* restrict skybox)
{
    Cam3D* cam = scene_camera();
    mat4 m = mat4_mult(cam->projection, mat4_mult(mat4_look_at(vec3_uni(0.0), cam->direction, cam->up), mat4_id()));
    
    glDepthMask(GL_FALSE);
    glUseProgram(skyboxshader);
    glBindVertexArray(skybox->VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->cubemap.id);
    glUniformMatrix4fv(glGetUniformLocation(skyboxshader, "MVP"), 1, GL_FALSE, &m.data[0][0]);
    glDrawArrays(drawMode, 0, 36);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthMask(GL_TRUE);
}

void renderer_switch()
{
    if (drawMode == GL_TRIANGLES) drawMode = GL_LINES;
    else drawMode = GL_TRIANGLES;
}