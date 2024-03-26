#pragma once

#include <gl.h>
#include <unordered_map>
#include <string>
#include "../types/reference.hpp"

namespace multik::render
{
    class Shader
    {
    public:
        Shader(const std::string &vertex, const std::string &fragment);
        Shader(const Shader &other) = delete;
        ~Shader();

        static Ref<Shader> ReadFiles(const std::string &vertex, const std::string &fragment);

        void Bind();
        void Unbind();

        void SetUniform(const std::string &name, float value);
        void SetUniform(const std::string &name, int value);

        void SetUniform(const std::string &name, const glm::vec2 &value);
        void SetUniform(const std::string &name, const glm::vec3 &value);
        void SetUniform(const std::string &name, const glm::vec4 &value);

        void SetUniform(const std::string &name, const glm::mat2 &value);
        void SetUniform(const std::string &name, const glm::mat3 &value);
        void SetUniform(const std::string &name, const glm::mat4 &value);

    private:
        const unsigned int id;
        int IndexUniform(const std::string &name);
        std::unordered_map<std::string, int> locations;
    };
}
