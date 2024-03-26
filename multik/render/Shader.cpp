#include "Shader.hpp"

#include <gl.h>
#include <stdexcept>
#include <fstream>

namespace multik::render
{
    unsigned int CompileShader(unsigned int type, const std::string &src);

    Shader::Shader(const std::string &vertex, const std::string &fragment)
        : id (glCreateProgram())
    {
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


    void Shader::SetUniform(const std::string &name, float value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniform1f(location, value);
    }

    void Shader::SetUniform(const std::string &name, int value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniform1i(location, value);
    }


    void Shader::SetUniform(const std::string &name, const glm::vec2 &value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniform2f(location, value.x, value.y);
    }

    void Shader::SetUniform(const std::string &name, const glm::vec3 &value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::SetUniform(const std::string &name, const glm::vec4 &value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniform4f(location, value.x, value.y, value.z, value.w);
    }


    void Shader::SetUniform(const std::string &name, const glm::mat2 &value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetUniform(const std::string &name, const glm::mat3 &value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetUniform(const std::string &name, const glm::mat4 &value)
    {
        int location = IndexUniform(name);
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    int Shader::IndexUniform(const std::string &name)
    {
        auto it = locations.find(name);
        if (it != locations.end())
            return it->second;
        int loc = glGetUniformLocation(id, name.c_str());
        locations[name] = loc;
        return loc;
    }
}
