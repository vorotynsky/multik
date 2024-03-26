#include "GlfwApplication.hpp"

#include <gl.h>

namespace multik::platform
{
    GlfwApplication::GlfwApplication(int width, int height)
        : width(width), height(height), multik::core::Application() { }

    GlfwApplication::~GlfwApplication()
    {
        glfwTerminate();
    }

    void GlfwApplication::Loop()
    {
        glfwPollEvents();

        if (glfwWindowShouldClose(window))
            Close();

        Draw();
        
        glfwSwapBuffers(window);
    }

    void GlfwApplication::Init()
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        this->window = glfwCreateWindow(width, height, "Multik", nullptr, nullptr);
        if (window == nullptr)
            throw "glfw window creation failed";
        
        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
            throw "glew initialization failed";

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }
}
