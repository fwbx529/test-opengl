
#include "Renderer.h"

float aspect;

void Initialize(Renderer& renderer)
{
    renderer.Init();
    renderer.SetData();
}

void Display(Renderer& renderer)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);

    renderer.SetUniforms();
    renderer.Draw();
}

int main()
{
    const int width = 800;
    const int height = 600;
    aspect = float(height) / float(width);

    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(width, height, "test-opengl", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    Renderer renderer;
    Initialize(renderer);
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
    {
        Display(renderer);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}