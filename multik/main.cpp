// Copyright 2020 vorotynsky
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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "core/VertexBuffer.hpp"
#include "core/IndexBuffer.hpp"
#include "core/VertexArray.hpp"
#include "core/Shader.hpp"
#include "types/reference.hpp"
#include "types/GLTypes.hpp"


const int HEIGHT = 480;
const int WIDTH = 640;

void mainLoop(GLFWwindow *window)
{
    namespace mltcore = multik::core;
    namespace mltype = multik::types;

    auto shader = mltcore::Shader::ReadFiles("shaders/square/color.vertex.glsl", "shaders/square/color.fragment.glsl");

    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
    };
    unsigned int indeces[] = {
            0, 1, 2,
            2, 3, 0
    };

    mltcore::VertexArray array;

    mltcore::BufferLayout layout({
        mltcore::BufferElement::createBuffer<mltype::Float2>()
    });

    auto vb = multik::MakeRef<mltcore::VertexBuffer>(vertices, 4 * 2 * sizeof(float), layout);
    auto ib = multik::MakeRef<mltcore::IndexBuffer>(indeces, 6);

    array.AppendVertexBuffer(vb);
    array.ResetIndexBuffer(ib);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glClearColor(0.255f, 0.063f, 0.127f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        array.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        array.Unbind();

        glfwSwapBuffers(window);
    }
}

int main(const int argc, const char **argv)
{    
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Multik", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    mainLoop(window);


    glfwTerminate();

    return 0;
}
