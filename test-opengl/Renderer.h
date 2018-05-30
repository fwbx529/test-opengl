#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Renderer 
{
public:
    Renderer();
    ~Renderer();

    void Init();
    void SetData();
    void SetUniforms();
    void Draw();
private:
    GLuint vao;
    GLuint vbo_array_buffer[3];
    GLuint vbo_element_array_buffer;
    unsigned int vertex_count;
    unsigned int face_count;

    GLuint prog;
};