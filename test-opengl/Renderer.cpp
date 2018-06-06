
#include <time.h>

#include "Renderer.h"
#include "LoadShaders.h"

float random_1()
{
    return (float)rand() / RAND_MAX;
}

Renderer::Renderer()
{
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(3, vbo_array_buffer);
    glCreateBuffers(1, &vbo_element_array_buffer);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(3, vbo_array_buffer);
    glDeleteBuffers(1, &vbo_element_array_buffer);
}

void Renderer::Init()
{
    //add shaders
    ShaderInfo shader_info[] =
    {
        { GL_VERTEX_SHADER, "pointsprites.vs.glsl" },
        { GL_FRAGMENT_SHADER, "pointsprites.fs.glsl" },
        { GL_NONE, NULL }
    };
    prog = LoadShaders(shader_info);
    //other initialization
}

void Renderer::SetData()
{
    //set data
    vector<glm::vec3> vertex;

    srand((unsigned)time(NULL));
    int count = 100;
    vertex.resize(count);
    for (int i = 0; i < count; i++)
    {
        vertex[i] = glm::vec3(2 * random_1() - 1,
                              2 * random_1() - 1,
                              random_1());
    }

    vertex_count = (unsigned int)vertex.size();
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_array_buffer[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glNamedBufferStorage(vbo_array_buffer[0], vertex_count * sizeof(glm::vec3), vertex.data(), 0);

    glBindVertexArray(0);
}

void Renderer::SetUniforms()
{
    glUseProgram(prog);

    //set uniforms
    GLuint _loc = glGetUniformLocation(prog, "");

    //glUniform*

    glUseProgram(0);
}

void Renderer::Draw()
{
    glUseProgram(prog);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, vertex_count);
    glUseProgram(0);
    glBindVertexArray(0);
}