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
#include "types/GLTypes.hpp"

const int HEIGHT = 480;
const int WIDTH = 640;

static unsigned int CompileShader(unsigned int type, const std::string &src)
{
    unsigned int shader = glCreateShader(type);
    const char *ps = src.c_str();
    glShaderSource(shader, 1, &ps, nullptr);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        char *message = new char[len + 1];
        glGetShaderInfoLog(shader, len, &len, message);
        std::cerr << "compile shader error: " << message << std::endl;
        delete[] message;
    }

    return shader;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

static unsigned int LoadShader(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::ifstream vertexFile(vertexPath);
    std::string vstr((std::istreambuf_iterator<char>(vertexFile)),
                    std::istreambuf_iterator<char>());

    std::ifstream fragmentFile(fragmentPath);
    std::string fstr((std::istreambuf_iterator<char>(fragmentFile)),
                    std::istreambuf_iterator<char>());

    unsigned int result = CreateShader(vstr, fstr);
    vertexFile.close();
    fragmentFile.close();
    return result;
}

void mainLoop(GLFWwindow *window)
{
    namespace mltcore = multik::core;
    namespace mltype = multik::types;

    unsigned int program =
            LoadShader("shaders/square/color.vertex.glsl", "shaders/square/color.fragment.glsl");
    glUseProgram(program);

    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
    };
    unsigned int indexes[] = {
            0, 1, 2,
            2, 3, 0
    };
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    mltcore::BufferLayout layout({
        mltcore::BufferElement::createBuffer<mltype::Float2>()
    });

    mltcore::VertexBuffer buffer(vertices, 4 * 2 * sizeof(float), layout);

    auto element = *layout.begin();
    glVertexAttribPointer(0, 
        element.Type.Count, 
        mltype::gl::toEnum(element.Type.Type),
        mltype::gl::boolean(element.Normalized), 
        element.Type.Size,
        (GLvoid*) element.Offset);
    glEnableVertexAttribArray(0);

    mltcore::IndexBuffer indexBuffer(indexes, 6);

    glBindVertexArray(vertexArray);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glClearColor(0.255f, 0.063f, 0.127f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        buffer.Bind();
        indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        buffer.Unbind();
        indexBuffer.Unbind();

        glfwSwapBuffers(window);

    }
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertexArray);
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
