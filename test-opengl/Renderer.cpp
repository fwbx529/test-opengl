
#include "Renderer.h"
#include "LoadShaders.h"

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
        { GL_VERTEX_SHADER, "vs.glsl" },
        { GL_FRAGMENT_SHADER, "fs.glsl" },
        { GL_NONE, NULL }
    };
    prog = LoadShaders(shader_info);
}

void Renderer::SetData()
{
    //set data
    vector<glm::vec3> vertex;
    vector<glm::ivec3> face;
    vector<glm::vec3> normal;
    {

    }

    vertex_count = (unsigned int)vertex.size();
    face_count = (unsigned int)face.size();

    //calculate normal
    normal = vector<glm::vec3>(vertex_count, glm::vec3(0, 0, 0));
    for (unsigned int f = 0; f < face_count; f++)
    {
        glm::ivec3 f_id(face[f]);
        glm::vec3 vx(vertex[f_id.x]);
        glm::vec3 vy(vertex[f_id.y]);
        glm::vec3 vz(vertex[f_id.z]);
        glm::vec3 n = glm::cross(vy - vx, vz - vx);
        normal[f_id.x] += n;
        normal[f_id.y] += n;
        normal[f_id.z] += n;
    }
    for (unsigned int v = 0; v < vertex_count; v++)
    {
        normal[v] = glm::normalize(normal[v]);
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_array_buffer[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glNamedBufferStorage(vbo_array_buffer[0], vertex_count * sizeof(glm::vec3), vertex.data(), 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_array_buffer[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glNamedBufferStorage(vbo_array_buffer[1], vertex_count * sizeof(glm::vec3), normal.data(), 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_element_array_buffer);
    glNamedBufferStorage(vbo_element_array_buffer, face_count * sizeof(glm::ivec3), face.data(), 0);

    glBindVertexArray(0);
}

void Renderer::SetUniforms()
{
    glUseProgram(prog);

    //set uniforms
    GLuint _loc = glGetUniformLocation(prog, "");

    //glUniformMatrix*

    glUseProgram(0);
}

void Renderer::Draw()
{
    glUseProgram(prog);
    glBindVertexArray(vao);
    //draw function
    {

    }
    glUseProgram(0);
    glBindVertexArray(0);
}