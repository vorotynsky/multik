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

#include "Shader.hpp"

#include <gl.h>
#include <stdexcept>
#include <fstream>

namespace multik::core
{
    unsigned int CompileShader(unsigned int type, const std::string &src);

    Shader::Shader(const std::string &vertex, const std::string &fragment)
    {
        this->id = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

        glAttachShader(this->id, vs);
        glAttachShader(this->id, fs);
        glLinkProgram(this->id);
        glValidateProgram(this->id);

        glDeleteShader(vs);
        glDeleteShader(fs);

        this->Bind();
    }

    Shader::~Shader()
    {
        glDeleteProgram(this->id);
    }

    void Shader::Bind()
    {
        glUseProgram(this->id);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    Ref<Shader> Shader::ReadFiles(const std::string &vertex, const std::string &fragment)
    {
        std::ifstream vertexFile(vertex);
        std::string vstr((std::istreambuf_iterator<char>(vertexFile)),
                        std::istreambuf_iterator<char>());
        vertexFile.close();

        std::ifstream fragmentFile(fragment);
        std::string fstr((std::istreambuf_iterator<char>(fragmentFile)),
                        std::istreambuf_iterator<char>());
        fragmentFile.close();

        return MakeRef<Shader>(vstr, fstr);
    }

    unsigned int CompileShader(unsigned int type, const std::string &src)
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

            throw std::runtime_error(message);
        }

        return shader;
    }


}