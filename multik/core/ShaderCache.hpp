// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <map>
#include "../render/Shader.hpp"
#include "../types/reference.hpp"

namespace multik::core
{
    class ShaderCache
    {
    public:
        static Ref<render::Shader> Get(const std::string &name);
        Ref<render::Shader> GetShader(const std::string &name) const;

        ShaderCache() = default;
        virtual ~ShaderCache() = default;

    protected:
        struct ShaderSource
        {
            std::string vertexPath;
            std::string fragmentPath;
        };
    
        virtual ShaderSource resolveName(const std::string &name) const;

    private:
        ShaderCache(ShaderCache const&) = delete;
        void operator=(ShaderCache const&) = delete;

        static ShaderCache global;

        mutable std::map<std::string, Weak<render::Shader>> cache;
    };

}
