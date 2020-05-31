// Copyright 2020 Vorotynsky Maxim
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

        glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}
